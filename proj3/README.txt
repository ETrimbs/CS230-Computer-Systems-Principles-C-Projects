Video demonstration: https://youtu.be/9PJxOqIuT0E

I will now go through project requirements and explain how and where they are satisfied.



---------------------Code flow
Files are organized into word.h and word.c, then wordfreak.h and wordfreak.c, and lastly a main.c file.
wordfreak.c is called from main with arg and argv. The job of wordfreak is to call countWords with either a file pointer
if the file is being read in from stdin, or a file descriptor if the file is being read in from env or argv.
It checks argv first, else env, else pipe/stdin. From there, the file is opened and a file descriptor is passed into
countWordsFD. The loop in this section reads in chars from the file, and if it is a letter, it begins to construct a word string,
until a non-letter char is reached. Then, the word string is either added to an array of words, or, if the word has been encountered
before, the word's count is incremented. If the word is new, it is sent into a WordFrequency object constructor. The (typedef) word object
stores a string, its frequency in the file, and the length of the word for formatting. Lastly, the list of words
is formatted and sent to stdout and the word objects / other malloc constructs are freed.

Methods which fulfill the project requirements are listed below.



---------------------Project Requirements
-Includes a Makefile that compiles your submitted code.

-Compiles a program that will accept 0 to n command line arguments. If your program receives 0 command 
line arguments it will read from standard input (using the bash pipe operator) for analysis. If your
program receives 1 to n command line arguments it will open the provided files for analysis.

This logic is included in wordFreak() function, which checks the val of arg, then
the return value of getenv(WORD_FREAK), and finally reads from stdin if nothing else is supplied.

-Compiles a program that will use a specified WORD_FREAK environment variable to parse and analyze a text 
file and produce the proper output.  
See above.

-Uses dynamic allocation and freeing (e.g., malloc(), free()).
I use this in freeWords() and constructWord().

-Uses structs and typedef.
I use this for the WordFrequency struct, which I typedef to word.

-Uses pointers.
Several times, including for calls to read, strcat, strcpy, the word array, words, and WordFrequency object
stores a char pointer. Also, calls to free().

-Uses only system calls for I/O.
Yes, for open in countWordsPointer, read in countWordsFD, write in printWords and close, in countWordsPointer.

-Aligns output using only system calls for I/O.
Yes, check printWords()

-Provides error checking for all system and library calls.
Yes, on all read, write, close, malloc calls