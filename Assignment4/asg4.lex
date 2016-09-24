%option noyywrap
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "backup.tab.h"
    int lineNo=0;
    void countNewLine();
%}

%s HASH

macro           ("#define"[ \t]+.*)
rLB             "("
rRB             ")"
cLB             "{"  
cRB             "}" 
sLB             "["
sRB             "]"
amp             "&"
semicolon       (";")
comma       (",")

lineComment     "//".*
blockComment    "/*"((("*"[^/])?)|[^*])*"*/"
string          \"([^\"]|\\.)*\"
char            \'([^\']|\\.)?\'
negativenumber "~".{digits}
letter  [a-zA-Z]
digit [0-9]
ws [ \n\t]
digits {digit}+
bool ("true"|"false"|"TRUE"|"FALSE")
illegal {`@#$_\':?}


id {letter}({letter}|{digit})*
funcName ("func1"|"fib"|"sum"|"func2"|"func3")

%%

"&&"                                    {printf(" AND ");fflush(stdout);return(AND); }
"!="                                    {printf(" NEQ ");fflush(stdout);return(NEQ); }
"||"                                    {printf(" OR ");fflush(stdout);return(OR); }
"<="                                    {printf(" LTEQ ");fflush(stdout);return(LTEQ); }
">="                                    {printf(" GTEQ ");;fflush(stdout);return(GTEQ); }
"=="                                    {printf(" EQ ");;fflush(stdout);return(EQ); }
"-"                                 {printf(" SUB ");fflush(stdout);return(SUB); }
"="                                 {printf(" ASG ");fflush(stdout);return(ASG); }
"+"                                 {printf(" ADD ");fflush(stdout);return(ADD); }
"*"                                 {printf(" MUL ");fflush(stdout);return(MUL); }
"/"                                 {printf(" DIV ");fflush(stdout);return(DIV); }
"%"                                 {printf(" MOD ");fflush(stdout);return(MOD);}
"<"                                 {printf(" LT ");fflush(stdout);return(LT); }
">"                                 {printf(" GT ");fflush(stdout);return(GT); }

%{ /* 
{lineComment}                               {printf(" VALUE: ");fflush(stdout);return COMMENT; }
{blockComment}                              {printf(" VALUE: ");fflush(stdout);return BLOCKCOMMENT;}

{string}                                {printf(" VALUE: ");fflush(stdout);return STRING;}
{char}                                  {printf(" VALUE: ");fflush(stdout);return CHAR;}
 "switch"                               {printf(" VALUE: ");fflush(stdout);return SWITCH;} 
 "case"                             {printf(" VALUE: ");fflush(stdout);return CASE;} 
 "default"                          {printf(" VALUE: ");fflush(stdout);return DEFAULT;} 
 "extern"                               {printf(" VALUE: ");fflush(stdout);return EXTERN;}  
 */ %}

"\n"                                    {printf(" \n");lineNo++;}

"goto"                                  {printf(" GOTO ");fflush(stdout);return GOTO;}
"assign"                                {printf(" ASSIGN ");fflush(stdout);return ASSIGN;}
"if"                                    {printf(" IF ");fflush(stdout);return IF;}
"else"                                  {printf(" ELSE ");fflush(stdout);return ELSE;}
"then"                                  {printf(" THEN ");fflush(stdout);return THEN;}
"while"                                 {printf(" WHILE ");fflush(stdout);return WHILE;}
"do"                                    {printf(" DO ");fflush(stdout);return DO;}
"for"                                   {printf(" FOR ");fflush(stdout);return FOR;}
"continue"                              {printf(" CONTINUE ");fflush(stdout);return CONTINUE;}
"global"                                {printf(" GLOBAL ");fflush(stdout);return GLOBAL;}
"break"                                 {printf(" BREAK ");fflush(stdout);return BREAK;}
"main"                                  {printf(" MAIN ");fflush(stdout);return MAIN;}
"void"                                  {printf(" VOID ");fflush(stdout);return VOID;}
"int"                                   {printf(" INT ");fflush(stdout);return INT;}
"char"                                  {printf(" CHAR ");fflush(stdout);return CHAR;}
"bool"                                  {printf(" BOOL ");fflush(stdout);return BOOL_DATATYPE;}
"return"                                {printf(" RETURN ");fflush(stdout);return RETURN;}
{bool}                                  {printf(" BOOL ");fflush(stdout);return BOOL;  }
{funcName}                              {printf(" FUNCNAME ");fflush(stdout);return FUNCNAME;  }
{macro}                                 {printf(" MACRO ");fflush(stdout);return MACRO;  }
{digits}                                {printf(" <DIGITS: ");ECHO;printf(" > ");fflush(stdout);return DIGITS;}

{negativenumber}            {printf(" <NEGATIVE_NUMBER: ");ECHO;printf(" > ");fflush(stdout);return NEGATIVENUMBER;}
{id}                {printf(" <ID: ");ECHO;printf(" > ");fflush(stdout);return ID;  }

{rLB}               {printf(" ROUNDLP ");fflush(stdout);return RLB;  }
{rRB}               {printf(" ROUNDRP ");fflush(stdout);return RRB;  }
{cLB}               {printf(" CURLYLP ");fflush(stdout);return CLB;  }
{cRB}               {printf(" CURLYRP ");fflush(stdout);return CRB;  }
{sLB}               {printf(" SQUARELP ");fflush(stdout);return SLB;  }
{sRB}               {printf(" SQUARERP ");fflush(stdout);return SRB;  }
{amp}               {printf(" AMPERSAND ");fflush(stdout);return AMP;  }
{semicolon}         {printf(" SEMICOLON ");fflush(stdout);return SEMICOLON;  }
{comma}         {printf(" COMMA ");fflush(stdout);return COMMA;  }
{ws}                {}

{digits}{letter}({letter}|{digit})*     {printf(" <Invalid ID: ");ECHO;printf("  |Cant start with a number>");}
.                   {printf(" <Illegal: "); ECHO; printf(" > "); }


%%

void countNewLine()
{
    int i;
    for(i=0; i<yyleng; i++)
    {
        if(*(yytext+i)=='\n') lineNo++;
    }
}