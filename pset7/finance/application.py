import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, search, create_dict

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/", methods=["GET"])
@login_required
def index():
    """Show portfolio of stocks"""
    user = session["user_id"]
    portval = 0
    # Get the current Cash Balance
    cash = db.execute("SELECT cash FROM users where id = :userid", userid=user)
    cashbal = cash[0]["cash"]
    tassets = 0

    # Create a dict of all stocks the user 'owns'
    stocks_full = db.execute("SELECT stocks.stockname, stocks.symbol, history.numberofstocks FROM history JOIN stocks ON history.stockid = stocks.stockid WHERE history.userid = :userid", userid=user)

    # Create a stocks_dict combining total quantity of each stock
    stocks_dict = create_dict(stocks_full)
    stocks_final = []

    def get_sum(stock):
        sum = db.execute("SELECT stocks.stockname, stocks.symbol, SUM(history.numberofstocks) FROM history JOIN stocks ON history.stockid = stocks.stockid WHERE history.userid = :userid AND stocks.symbol = :share", userid=user, share=stock['symbol'])
        return sum[0]['SUM(history.numberofstocks)']

    # Remove stocks that = 0
    for stock in stocks_dict:
        # Add together quantity of stocks
        stocks_sum = get_sum(stock)
        if stocks_sum > 0:
            stocks_final.append(stock)

    for stock in stocks_final:
        # Add together quantity of stocks
        stocks_sum = get_sum(stock)
        quote = lookup(stock['symbol'])
        price = quote['price']
        # Calculate the current total value of each stock owned
        total = price * stocks_sum
        # Add new values to stocks_dict
        stock.update({'num': stocks_sum, 'value': usd(price), 'total': usd(total)})
        # Calculate the total value of all stocks held
        portval += total

    # Calculate the total value of all assets currently held
    tassets = cashbal + portval

    # Convert all values to usd format
    tassets = usd(tassets)
    cashbal = usd(cashbal)
    portval = usd(portval)

    return render_template("portfolio.html", stocks=stocks_final, portval=portval, cashbal=cashbal, tassets=tassets)


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user = session["user_id"]

    if request.method == "POST":
        s = request.form.get("symbol")
        n = request.form.get("shares")
        stockname = ""
        price = 0.0
        symbol = ""
        # userid = session["user_id"]
        stockid = db.execute("SELECT stockid FROM stocks WHERE symbol = :symbol", symbol=s)
        cash = db.execute("SELECT cash FROM users where id = :userid", userid=user)

        # Check that the form isn't empty
        if not s or not n:
            return apology("You must enter a stock symbol and number of shares you would like to sell", 400)

        # Render an apology if the input is not a positive integer or if the user does not own that many shares of the stock
        if not n.isnumeric() or int(n) <= 0:
            return apology("You must buy 1 or more stocks", 400)

        def get_sum(stock):
            num = db.execute("SELECT SUM(history.numberofstocks) FROM history JOIN stocks ON history.stockid = stocks.stockid WHERE history.userid = :userid AND stocks.symbol = :share", userid=user, share=stock)
            return num[0]['SUM(history.numberofstocks)']

        stocksavail = get_sum(s)

        if not int(n) <= stocksavail:
            return apology("You do not have that many stocks to sell", 400)

        # Get the current value of the stock being sold
        quote = lookup(s)

        # If stock is Valid, Display stock quote
        if quote == None:
            return apology("Stock symbol not valid", 400)

        # Save price as variables
        else:
            price = quote["price"]

        sellval = price * float(n)
        new_cash_total = cash[0]["cash"] + sellval
        numberofstocks = int(n) * (-1)

        # Add the value to the user's cashbal
        db.execute("UPDATE users SET cash = :cash WHERE id = :userid", cash=new_cash_total, userid=user)

        # Store the transaction numofshares as a negative value in the history log
        db.execute("INSERT INTO history (numberofstocks, priceperstock, totalprice, transtype, stockid, userid) VALUES(:numberofstocks, :priceperstock, :totalprice, :transtype, :stockid, :userid)", numberofstocks=numberofstocks, priceperstock=price, totalprice=sellval, transtype="SOLD", stockid=stockid[0]["stockid"], userid=user)

        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect): Display form to sell stocks
    else:

        # Create a dict of all stocks the user 'owns'
        stocks_full = db.execute("SELECT stocks.stockname, stocks.symbol, history.numberofstocks FROM history JOIN stocks ON history.stockid = stocks.stockid WHERE history.userid = :userid", userid=user)

        # Create a stocks_dict combining total quantity of each stock
        stocks_dict = create_dict(stocks_full)

        stocks_final = []

        def get_sum(stock):
            sum = db.execute("SELECT stocks.stockname, stocks.symbol, SUM(history.numberofstocks) FROM history JOIN stocks ON history.stockid = stocks.stockid WHERE history.userid = :userid AND stocks.symbol = :share", userid=user, share=stock['symbol'])
            return sum[0]['SUM(history.numberofstocks)']

        # print(stocks_dict)
        for stock in stocks_dict:
            # Add together quantity of stocks
            stocks_sum = get_sum(stock)
            if stocks_sum > 0:
                stocks_final.append(stock)

        return render_template("sell.html", stocks=stocks_final)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    """Buy shares of stock"""
    user = session["user_id"]

    if request.method == "POST":

        # Save symbol entered as a variable
        s = request.form.get("symbol")
        n = request.form.get("shares")
        stockname = ""
        price = 0.0
        symbol = ""

        # Ensure stock symbol was submitted
        if not s or not n:
            return apology("You must enter a stock symbol and number of shares you would like to purchase", 400)

        # Ensure shares is a positive number
        if not n.isnumeric() or int(n) <= 0:
            return apology("You must buy 1 or more stocks", 400)

        # Retrieve stock quote - returns a dict: name, price, symbol
        quote = lookup(s)

        # If stock is Valid, Display stock quote
        if quote == None:
            return apology("Stock symbol not valid", 400)

        # Save details as variables
        else:
            stockname = quote["name"]
            price = quote["price"]
            symbol = quote["symbol"]

        # Check whether user has enough cash to purchase
        cash = db.execute("SELECT cash FROM users where id = :userid", userid=user)
        buy_total = price * float(n)

        # Update cash
        if cash[0]["cash"] >= buy_total:
            newtotal = cash[0]["cash"] - buy_total
            db.execute("UPDATE users SET cash = :cash WHERE id = :userid", cash=newtotal, userid=user)
        else:
            return apology("You do not have enought cash to purchase these shares.", 400)

        # Check is stock is in stock database
        stock = db.execute("SELECT symbol FROM stocks WHERE symbol = :symbol", symbol=symbol)

        if not stock:
            db.execute("INSERT INTO stocks (symbol, stockname) VALUES(:symbol, :stockname)", symbol=symbol, stockname=stockname)

        stockid = db.execute("SELECT stockid FROM stocks WHERE symbol = :symbol", symbol=symbol)

        # Add stock to history and portfolio database
        db.execute("INSERT INTO history (numberofstocks, priceperstock, totalprice, transtype, stockid, userid) VALUES(:numberofstocks, :priceperstock, :totalprice, :transtype, :stockid, :userid)", numberofstocks = int(n), priceperstock = price, totalprice = buy_total, transtype = "BOUGHT", stockid = stockid[0]["stockid"], userid = user)

        return redirect("/")


    # User reached route via GET (as by clicking a link or via redirect): Display form to lookup stocks
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user = session["user_id"]

    # Create a dict of all stocks the user 'owns'
    stocks_full = db.execute("SELECT stocks.stockname, stocks.symbol, history.numberofstocks, history.priceperstock, history.time FROM history JOIN stocks ON history.stockid = stocks.stockid WHERE history.userid = :userid", userid=user)

    print(stocks_full)

    return render_template("history.html", stocks=stocks_full)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Save symbol entered as a variable
        s = request.form.get("symbol")

        # Ensure stock symbol was submitted
        if not s:
            return apology("You must enter a stock symbol")

        # Retrieve stock quote - returns a dict: name, price, symbol
        quote = lookup(s)

        # If stock is Valid, Display stock quote
        if quote == None:
            return apology("Stock symbol not valid", 400)

        # Else display quote
        else:
            name = quote["name"]
            price = usd(quote["price"])
            symbol = quote["symbol"]

        return render_template("quoted.html", name=name, price=price, symbol=symbol)

    # User reached route via GET (as by clicking a link or via redirect): Display form to lookup stocks
    else:
        return render_template("quote.html")


@app.route("/account", methods=["GET", "POST"])
@login_required
def password():
    """Change password."""
    user = session["user_id"]
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("currentpw"):
            return apology("must provide current password", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide new password", 400)

        # Ensure password is confirmed
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Ensure Current Password given is correct
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = :userid",
                          userid=user)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("currentpw")):
            return apology("current password entered incorrect", 400)

        # Ensure password and confirmed password match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Hash the user’s password
        pwd_hash = generate_password_hash(request.form.get("password"))
        db.execute("UPDATE users SET hash = :password WHERE id = :userid", password=pwd_hash, userid=user)

        # Show confirmation
        return render_template("passwordupdated.html")

    # User reached route via GET (as by clicking a link or via redirect): Display form to lookup stocks
    else:
        return render_template("account.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password is confirmed
        elif not request.form.get("confirmation"):
            return apology("must provide password confirmation", 400)

        # Ensure password and confirmed password match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        # Hash the user’s password
        pwd_hash = generate_password_hash(request.form.get("password"))

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        if rows:
            return apology("This user already exists, please login instead", 400)

        # INSERT the new user into users
        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=pwd_hash)
        # if not result:
        #     return apology("This user already exists, please login instead", 400)

        # Query database for username again
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
