#!/usr/bin/env sh
mkdir -p bin
clang main.c -g -O0 -I/path/to/zap -lX11 -lXrandr -o bin/main
