#!/usr/bin/env sh
mkdir -p bin
clang main.c -I/path/to/zap -lX11 -o bin/main
