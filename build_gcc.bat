@echo off
:: $env:PATH += ";C:\Users\rkispert\Downloads\gcc-13.2.0-no-debug\bin"
gcc src/Lexer.c src/Source.c -o blargify.exe
pause
