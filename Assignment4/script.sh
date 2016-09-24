bison -vtd -r all backup.y
flex asg4.lex
g++  -std=c++11 backup.tab.c lex.yy.c -w
