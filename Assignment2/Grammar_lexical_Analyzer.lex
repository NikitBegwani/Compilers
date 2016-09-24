##############################################
		LEX Code for lexical analyser
##############################################
%option noyywrap
%{
	int lineNo=0;
	void countNewLine();
%}

%s HASH

library			("#include"[ \t]+.*)
macro 			("#define"[ \t]+.*)
binaryOp 		("+"|"-"|"/"|"*"|"%"|"=")
relOp 			("=="|"<"|">"|"<="|">="|"!=")
logicalOp 		("&&"|"||"|"!")
rLB				"("
rRB 			")"
cLB 			"{"  
cRB 			"}" 
sLB				"["
sRB				"]"
amp				"&"
delimiter		(";"|",")

lineComment		"//".*
blockComment	"/*"((("*"[^/])?)|[^*])*"*/"
string			\"([^\"]|\\.)*\"
char			\'([^\']|\\.)?\'
negativenumber {sLB}{ws}*"-"{ws}*{digits}{ws}*{sRB}
letter 	[a-zA-Z]
digit [0-9]
ws [ \n\t]
digits {digit}+
bool ("true"|"false"|"TRUE"|"FALSE")

illegal {`~@#$_\':?}

reserved ("switch"|"break"|"case"|"continue"|"default"|"do"|"else"|"extern"|"for"|"goto"|"if"|"else"|"return"|"typedef"|"while")

dataType ("bool"|"int"|"char"|"float"|"void")

id {letter}({letter}|{digit})*

funcArgs ({rLB}{ws}*{rRB}|{rLB}{ws}*{dataType}{ws}+{id}{ws}*({delimiter}{ws}*{dataType}{ws}+{id}{ws}*)*{rRB})
funcCall ({rLB}{ws}*{rRB}|{rLB}{ws}*({string}|{id}|{char}){ws}*({delimiter}{ws}*({string}|{id}|{char}){ws}*)*{rRB})

%%

{lineComment} 		{printf("TOKEN:		lineComment,"); printf("VALUE:		");ECHO; printf("\n");  }
{blockComment}  	{printf("TOKEN:		blockComment,"); printf("VALUE:		");ECHO; printf("\n");   countNewLine();}

{string}			{printf("TOKEN:		string,"); printf("VALUE:		");ECHO; printf("\n");   countNewLine();}
{char}			{printf("TOKEN:		char,"); printf("VALUE:		");ECHO; printf("\n");  }

{reserved}			{printf("TOKEN:		reserved,"); printf("VALUE:		");ECHO; printf("\n");  }
{dataType}			{printf("TOKEN:		dataType,"); printf("VALUE:		");ECHO; printf("\n");  }
{library}			{printf("TOKEN:		library,"); printf("VALUE:		");ECHO; printf("\n");  }
{macro}				{printf("TOKEN:		macro,"); printf("VALUE:		");ECHO; printf("\n");  }
{digits}			{printf("TOKEN:		digits,"); printf("VALUE:		");ECHO; printf("\n");  }

{digits}{letter}({letter}|{digit})*		{printf("ILLEGAL IDENTIFIER => "); printf("VALUE:		");ECHO; printf("\n"); printf(" > at line no.%d\n",lineNo+1);}
{negativenumber}			{printf("TOKEN:		negativenumber,"); printf("VALUE:		");ECHO; printf("\n");  }
{id}				{printf("TOKEN:		id,"); printf("VALUE:		");ECHO; printf("\n");  }
{binaryOp}			{printf("TOKEN:		binaryOp,"); printf("VALUE:		");ECHO; printf("\n");  }
{relOp}				{printf("TOKEN:		relOp,"); printf("VALUE:		");ECHO; printf("\n");  }
{logicalOp}			{printf("TOKEN:		logicalOp,"); printf("VALUE:		");ECHO; printf("\n");  }
{rLB}				{printf("TOKEN:		rLB,"); printf("VALUE:		");ECHO; printf("\n");  }
{rRB}				{printf("TOKEN:		rRB,"); printf("VALUE:		");ECHO; printf("\n");  }
{cLB}				{printf("TOKEN:		cLB,"); printf("VALUE:		");ECHO; printf("\n");  }
{cRB}				{printf("TOKEN:		cRB,"); printf("VALUE:		");ECHO; printf("\n");  }
{sLB}				{printf("TOKEN:		sLB,"); printf("VALUE:		");ECHO; printf("\n");  }
{sRB}				{printf("TOKEN:		sRB,"); printf("VALUE:		");ECHO; printf("\n");  }
{amp}				{printf("TOKEN:		amp,"); printf("VALUE:		");ECHO; printf("\n");  }
{delimiter}			{printf("TOKEN:		delimiter,"); printf("VALUE:		");ECHO; printf("\n");  }
{funcArgs}			{printf("TOKEN:		funcArgs,"); printf("VALUE:			");ECHO; printf("\n");}
{funcCall}			{printf("TOKEN:		funcCall,"); printf("VALUE:			");ECHO; printf("\n");}
"\n"				{lineNo++;}
{ws}				{}
.					{printf("Illegal symbol TOKEN:		"); printf("VALUE:		");ECHO; printf("\n"); printf(" > at line no.%d\n",lineNo+1);}


%%
int main()
{
	yylex();
	printf("Total Lines=%d\n",lineNo);
	return 0;
}

void countNewLine()
{
	int i;
	for(i=0; i<yyleng; i++)
	{
		if(*(yytext+i)=='\n') lineNo++;
	}
}

###################################################
				GRAMMAR
###################################################
PROG -> G_DECL int main rLB rRB cLB STMT_LIST cRB FN_DEF
G_DECL -> LIBRARIES MACROS FN_DECL VAR_DECL  

LIBRARIES ->  library LIBRARIES |	EPSILON
MACROS ->	macro MACROS	|	EPSILON
FN_DECL	->	dataType id rLB FUNC_ARGS rRB;	FN_DECL	|	EPSILON
VAR_DECL	->	dataType EXPS VAR_DECL | EPSILON
EXPS -> id, EXPS | id; | id = digits, EXPS | id = digits; | id = bool, EXPS | id = bool;
FUNC_ARGS -> dataType id, FUNC_ARGS | EPSILON | dataType id

STMT_LIST -> STMT; STMT_LIST | EPSILON
STMT -> VAR_DECL | EXPRESSIONS | COND_LOOP | FN_CALL

EXPRESSIONS -> EXPR_REL | EXPR_BINARY | EPSILON
EXPR_REL -> OP relOp OP
OP -> id | digits | rLB EXPRESSIONS rRB
EXPR_BINARY -> E' + EXPR_BINARY | E' - EXPR_BINARY | E'
E' -> OP_BIN * E'| OP_BIN / E' | OP_BIN
OP_BIN -> id | digits | rLB EXPR_BINARY rRB

OP_REL -> digits | id | EXPR_REL | bool
COND_LOOP -> IF | WHILE | DO_WHILE | FOR | EPSILON
/* statement lists should always be inside brackets*/
IF -> if rLB OP_REL rRB then cLB STMT_LIST cRB | if rLB OP_REL rRB then cLB STMT_LIST cRB else cLB STMT_LIST cRB
WHILE -> while rLB OP_REL rRB cLB STMT_LIST cRB
DO_WHILE -> do cLB STMT_LIST cRB while rLB OP_REL rRB
FOR -> for rLB INIT; TERMINATE; INCR rRB
INIT -> id = id | id = digits | EPSILON
TERMINATE -> id relOp digits | id relOp id | digits relOp id | digits relOp digits | EPSILON
BIN_OP_FOR -> + | - | * | / 
INCR -> id = id BIN_OP_FOR digits | id = id BIN_OP_FOR id | EPSILON 

FN_CALL -> id rLB FN_CALL_ARGS rRB
FN_CALL_ARGS -> id, FN_CALL_ARGS | EPSILON | id | digits, FN_CALL_ARGS | digits | bool, FN_CALL_ARGS | bool

FN_DEF -> dataType id rLB FUNC_ARGS rRB cLB STMT_LIST cRB FN_DEF | EPSILON
