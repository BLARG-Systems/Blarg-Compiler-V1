@echo off
:: $env:PATH += ";C:\Users\rkispert\Downloads\gcc-13.2.0-no-debug\bin"
gcc src/Source.c src/Lexer.c src/List.c -o blargify.exe
pause
