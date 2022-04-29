# Machine-code_Markup_Language


  <h3 align="center">Machine-code Markup Language</h3>

  <p align="center">
    A declarative and imperative, interpreted and "compiled" (assembled somewhat) programming language based on a single structure type, implementing variables, macros and more!
  </p>
  

## Warnings

This programming language is meant for educationnal purposes, OS making and low level software creation. It does not, at the moment, have a standard library. The makefile target will compile the go-to application for use in this language, acting as both a sort of compiler (which it isn't, as the language is not compiled or assembled) and an interpreter. By default, the amount of nodes total per program is limited, as the goal of the MML parser was to be as small as possible, without using much of the kernel dependent C Libs. Thus, the general input/output/code buffer is limited to 4096 bytes, and the "program expression" which holds nodes is limited to 512 samples of nodes. The language should be able to produce x86, ARM or other architecture's code, since it requires developpers to define their own runtime, framework and symbols (used as code). This could be prevented when using the standard library which will abstract most of the unnecessary low level instructions and sets of functions.


## About (App design)

The target application will be able to run (interprate) code sent through a seamingly unlimited amount of source files. It is also possible to enter code to be executed directly (inspired by many interpreted languages consoles) without passing any arguent to the app or by requesting the "interprate" (run) function. More details in the "usage" section. An output file can be precised and debugger flags can be triggered, allowing extremely basic debugging (the nodes, tokens and code will be printed out).


## Usage

# Basics
./mml -args
or 
./mml (easy access to the interpreter, same as "-i")

# Arguments
-f FILE   precise an input file. Multiple files can be specified. Files will be read in order of declaration.
-i        invokes the interpreter (requests user input).
-d        call for debugging functions (prints tokens, nodes and code generated).
-o FILE   output file. Only a single file can be entered.

WARNING : There is no "-h" option, the only documentation at the moment is this github page.


## Language design and philosophy

This languages is meant to be built on itself. Once the main implementation is complete, it should be possible to write extensions inside of any new code written in MML. The main idea is : Everything is a node. A node contains a symbol (similar to Lisp's atoms) that are (by default) a stream of 16 characters.
A node is also linked to 16 other nodes using a pointer. This "node invoking nodes" idea is the main principle of the language as every component and unique features present are planned to work that way. For example, when declaring a node, the name of the node is actually its symbol. It is then possible to enter other nodes (which could be linked themeselves to more nodes). There exists 3 types of nodes : the classic "node", the "monode" composed only of it's symbol, all of its pointers are NULL and the "nullnode" which can either have its pointer redirected to an instance of itself or NULL. Its symbol should be empty. A lot of other specifications can be added using that principle. A node write call to an undefined node will create this node (when a node should be written to the code buffer). Declaring a new node containing an undeclared one will also declare it (as a monode).


## The problem of static memory

Obviously, using as little C as possible brings issues. Being able to allocate and free memory is one of the most important features of an operating system and kernel. Not using it is a pain that needs to be dealt with. That's why the program counter exists (called expression). This expression is basically an array of nullnodes that shall be defined as your code progress. A node can be grepped using its symbol from the main program expression. This comes in handy multiple times in the application.

## But how does it work? How is it possible to manage actual code if the only way possible to write code is on 16 bytes characters that are NAMES?!

