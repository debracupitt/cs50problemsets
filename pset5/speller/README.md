# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

An obscure term ostensibly referring to a lung disease caused by silica dust,
sometimes cited as one of the longest words in the English language. (dictionary.com)

## According to its man page, what does `getrusage` do?

`int getrusage(int who, struct rusage *r_usage);`

getrusage is "benchmarking" (i.e., timing the execution of) implementations of
check, load, size, and unload. It returns resource usage measures for the calling process,
the children of the calling process, or the calling thread, like CPU time and memory used.

## Per that same man page, how many members are in a variable of type `struct rusage`?

There are 16 members in a variable of type `struct rusage` - 2 structs and 14 long types.
A list of the members can be found here:
http://linux.die.net/man/2/getrusage

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

We pass before and after by reference (instead of by value) to the function `calculate`
because if we pass them by value, the entire two structures will be copied into `calculate`
which is slow and takes up a lot of memory. Copying structs will get placed on the stack, potentially
causing stack overflow.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Main takes the following steps:

1. opens the file to read and checks that the file exists and has not overloaded the memory.
2. creates int variables to track the number of words in the file, how many words are misspelled
and which index in each word the pointer is at as it reads each word.
3. loops over every character in the text in a for loop. Within the loop:
    1. if the character being read is alphabetic or an apostrophe (but not as it's first character):
    the character is appended to a `word[LENGTH]` variable.
    This repeats until the character being read is non-alphabetical. Then:
        1. Append `'\0'` to the end of `word`, +1 to the words counter
        2. check whether the word is misspelled and, if true, print the word and +1 to the misspelled counter
        3. reset `index` to 0 to prepare for the next word.
    If the number of characters in `word` (i.e. the `index`) becomes greater than the `LENGTH` of word being read,
    it is assumed the word is too long and `index` is reset to 0 to prepare for the next word.
    2. if at any point the character being read is a number, read the rest of the string (or word) being checked,
    then reset `index` to 0.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fgetc reads the file character by character. With this approach,
it is easy to identify anything that isn't alphabetical or an apostrophe proceeded by a character.

fscanf adds complexity and is less flexible.

Why:
1. in fscanf, you have to allocate a memory for a string before reading it from file,
and there are no limits of a length of a word in a text file. So, if long string is read using fscanf,
it could overwrite important data in memory or cause a segmentation fault.
2. fscanf reads until white space - because words within the txt files sometimes end with punctuation,
fscanf will view them as being part of the word, which makes reading and spell-checking more complicated.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

`const`s ensure that the parameter cannot be modified - this adds an extra layer of protection to make sure
that neither the dictionary's contents, nor the word being checked, can be changed in the function - 
if they can be changed, the spellcheck wouldn't be very accurate!
