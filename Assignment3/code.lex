#######################################################################################################
lex file code: 
#######################################################################################################
%option noyywrap
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "asg3.tab.h"
    int lineNo=0;
    void countNewLine();
%}

%s HASH

macro           ("#define"[ \t]+.*)
dataType ("bool"|"int"|"char"|"float"|"void")
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
negativenumber {sLB}{ws}*"-"{ws}*{digits}{ws}*{sRB}
letter  [a-zA-Z]
digit [0-9]
ws [ \n\t]
digits {digit}+
bool ("true"|"false"|"TRUE"|"FALSE")

illegal {`~@#$_\':?}


id {letter}({letter}|{digit})*


%%

"&&"                                    {printf(" AND ");return(AND); }
"!="                                    {printf(" NEQ ");return(NEQ); }
"||"                                    {printf(" OR ");return(OR); }
"<="                                    {printf(" LTEQ ");return(LTEQ); }
">="                                    {printf(" GTEQ ");;return(GTEQ); }
"=="                                    {printf(" EQ ");;return(EQ); }
"-"                                 {printf(" SUB ");return(SUB); }
"="                                 {printf(" ASG ");return('='); }
"+"                                 {printf(" ADD ");return(ADD); }
"*"                                 {printf(" MUL ");return(MUL); }
"/"                                 {printf(" DIV ");return(DIV); }
"%"                                 {printf(" MOD ");return(MOD);}
"<"                                 {printf(" LT ");return(LT); }
">"                                 {printf(" GT ");return(GT); }

%{ /* 
{lineComment}                               {printf(" VALUE: ");return COMMENT; }
{blockComment}                              {printf(" VALUE: ");return BLOCKCOMMENT;}

{string}                                {printf(" VALUE: ");return STRING;}
{char}                                  {printf(" VALUE: ");return CHAR;}
 "switch"                               {printf(" VALUE: ");return SWITCH;} 
 "case"                             {printf(" VALUE: ");return CASE;} 
 "default"                          {printf(" VALUE: ");return DEFAULT;} 
 "extern"                               {printf(" VALUE: ");return EXTERN;}  
 */ %}

"\n"                                    {printf(" \n");lineNo++;}

"goto"                                  {printf(" GOTO ");return GOTO;}
"if"                                    {printf(" IF ");return IF;}
"else"                                  {printf(" ELSE ");return ELSE;}
"then"                                  {printf(" THEN ");return THEN;}
"while"                                 {printf(" WHILE ");return WHILE;}
"do"                                    {printf(" DO ");return DO;}
"for"                                   {printf(" FOR ");return FOR;}
"return"                                {printf(" RETURN ");return RETURN;}
"continue"                              {printf(" CONTINUE ");return CONTINUE;}
"global"                                {printf(" GLOBAL ");return GLOBAL;}
"break"                                 {printf(" BREAK ");return BREAK;}
"main"                                  {printf(" MAIN ");return MAIN;}
{dataType}                              {printf(" <DATATYPE: ");ECHO;printf(" > ");return DATATYPE;  }
{bool}                              {printf(" BOOL ");return BOOL;  }
{macro}                                 {printf(" MACRO ");return MACRO;  }
{digits}                                {printf(" <DIGITS: ");ECHO;printf(" > ");return DIGITS;}

{negativenumber}            {printf(" <NEGATIVE_NUMBER: ");ECHO;printf(" > ");return NEGATIVENUMBER;}
{id}                {printf(" <ID: ");ECHO;printf(" > ");return ID;  }

{rLB}               {printf(" ROUNDLP ");return RLB;  }
{rRB}               {printf(" ROUNDRP ");return RRB;  }
{cLB}               {printf(" CURLYLP ");return CLB;  }
{cRB}               {printf(" CURLYRP ");return CRB;  }
{sLB}               {printf(" SQUARELP ");return SLB;  }
{sRB}               {printf(" SQUARERP ");return SRB;  }
{amp}               {printf(" AMPERSAND ");return AMP;  }
{semicolon}         {printf(" SEMICOLON ");return SEMICOLON;  }
{comma}         {printf(" COMMA ");return COMMA;  }
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

