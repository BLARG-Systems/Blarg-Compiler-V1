@echo off
:: ;C:\Users\Ryan\Downloads\winlibs-x86_64-posix-seh-gcc-13.2.0-llvm-18.1.3-mingw-w64msvcrt-11.0.1-r7\mingw64\bin
gcc src/Source.c src/Lexer.c src/Parser.c -o blargify.exe
pause
