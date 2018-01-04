@echo off
bison -d SQLParser.y -o SQLParser.cpp
flex SQLLexer.l
g++ SQLParser.cpp -o par.exe
pause
