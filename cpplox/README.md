# CPPLOX

Cpplox is the first iteration of Robert Nystrom's Lox interpreter. It can be ran in one of two modes, <b><i>prompt</i></b> and <b><i>file</i></b> mode. To run in
<b><i>prompt</i></b> mode, simply call the interpreter like so: `cpplox`. This will "prompt" the user to supply it a line of valid Lox code, which it will then execute.
To run in <b><i>file</i></b> mode, call the interpreter like: `cpplox [textfile.txt]`. This will read the entire file at once and then execute.

Building options:
  - `make` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; This will create an executable in the bin directory
  - `make run` &nbsp;&nbsp; This will create an executable in the bin directory and run the interpreter in <b><i>prompt</i></b> mode.
  - `make clean` This will remove the bin and obj directories that are automatically created

### Notes:
Here I will make note of anything I need to do, current problems I'm facing, what I expect to needs to be done, etc., for my future self.

1. Although the Scanner, Logger, and Token classes are in place, they currently don't do anything. In the run method of the main function, a call to Scanner.ScanTokens() is
made, which stores a vector of tokens. It currently returns a vector of the Scanner, mTokens, which is empty. I expect that each valid token made will be pushed to this vector
in the upcoming sections.
2. In the run method of the main function, it iterates over all the tokens in the tokens vector from <b>Point 1</b> and prints to standard out. Currently, it just prints
"token" for each token, but should change it to print the actual token. In the future, I expect these tokens will then be passed to the Parser?
3. Probably need to pass a reference of the Logger to the Scanner, so it can report any errors.
