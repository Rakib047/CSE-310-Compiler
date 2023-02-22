#!/bin/bash

flex 1905047.l     # generate the C++ code for the lexer
g++ -w lex.yy.c     # compile the lexer
