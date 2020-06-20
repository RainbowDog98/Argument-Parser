#!/bin/sh

g++ src/main.cpp src/argument_parser/argument_parser.cpp -o program

./program $*
