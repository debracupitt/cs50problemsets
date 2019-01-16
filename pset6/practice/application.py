from flask import Flask

app = Flask(__name__)

@app.route("/")
def index():
    return "you are at the index page"

@app.route("/sample")
def sample():
    return "you are at the sample page"

@app.route("/show/<number>")
def show(number):
    return "you passed in {}".format(number)

# Three steps to run your flask app. Run steps 1 and 2 only the first time.
# 1. export FLASK_APP=application.py
# 2. export FLASK_DEBUG=1
# 3. flask run

# @app.route("/login", methods=['GET', 'POST'])
# def login():
#     if not request.form.get("username")
#         return apology("must provide username")

# @app.route("/login", methods=['GET', 'POST'])
# def login():
#   if not request.method == "POST":
#       do one thing
#   else:
#       do another thing


# Useful Flask Functions

# flask.url_for()
# Generates a URL to the given endpoint with the method provided.

# flask.redirect()
# Returns a response object (a WSGI application) that, if called, redirects the client to the target location. Supported codes are 301, 302, 303, 305, and 307. 300 is not supported because it’s not a real redirect and 304 because it’s the answer for a request with a request with defined If-Modified-Since headers.

# flask.session()
# The session object works pretty much like an ordinary dict, with the difference that it keeps track on modifications.
# Can be used to continually check that a user is logged in when they switch between different pages
# you can store data in the session

# flask.render_template()
# Renders a template from the template folder with the given context.

