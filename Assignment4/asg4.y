/*
	%{
	  Prologue: Syntax and usage of the prologue.
	  The Prologue section contains 
	  macro definitions and declarations of functions and variables 
	  that are used in the actions in the grammar rules. 
	%}

	Bison declarations: Syntax and usage of the Bison declarations section. 
3
	%%
	Grammar rules: Syntax and usage of the grammar rules section. 
	%%

	Epilogue: Syntax and usage of the epilogue. 
*/
%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "iostream"
	#include <vector>
	#include <string>
	#include "sstream"
	#include <map>
	#include <vector>
	#include <string.h>
	int yylex(void);
	void yyerror(char *msg);
 	using namespace std;
 	extern int	yylex();
 	extern int lineNo;
 	extern char* yytext;
 	extern int yyleng;

 	class varEntry
 	{
 		public:
 		string name;
 		string type;
 		string tag;
 		int level;
 		string ele;
 		string val;
 		varEntry(string name, string type, string tag, int level, string ele,string val="")
 		{
 			this->val = val;
 			this->name = name;
 			this->type = type;
 			this->tag = tag;
 			this->level = level;
 			this->ele = ele;
 		}
 	};

 	class entry
 	{
 		public:
 		string name; 
 		string resultType;
 		vector<varEntry> parameter; 	
 		vector<varEntry> variable;
 		int paramNum; 	
 	};

	vector<entry> func_table;
	vector<entry>::iterator active_func, call_func;
	int glob_level;

	void symbolTable()
	{
 		printf("Name\tType\tParameters\tVariables\n");
		for(int i=0;i<func_table.size();i++)
		{
			printf("Entry Number: %d\n",i+1 );
			cout<<func_table[i].name<<"\t"<<func_table[i].resultType<<endl;
			printf("Parameters:\n");
			for(int j =0;j<func_table[i].parameter.size();j++)
				cout<<func_table[i].parameter[j].name<<"\t"<<func_table[i].parameter[j].type<<"\t"<<func_table[i].parameter[j].tag<<"\t"<<func_table[i].parameter[j].level<<"\t"<<func_table[i].parameter[j].ele<<endl;

			printf("Variables:\n");
			for(int j =0;j<func_table[i].parameter.size();j++)
				cout<<func_table[i].variable[j].name<<"\t"<<func_table[i].variable[j].type<<"\t"<<func_table[i].variable[j].tag<<"\t"<<func_table[i].variable[j].level<<"\t"<<func_table[i].variable[j].ele<<endl;
		}
	}
	int searchFunction(string name, vector<entry>::iterator func)
	{
		vector<entry>::iterator itr;
		for(itr=func_table.begin(); itr!=func_table.end();itr++)
		{
			if ((*itr).name == name)
			{	
				func = itr;
				return 1;
			}
		}
		return 0;
	}

	void enter_func(string name, string type, vector<entry>::iterator func)
	{
		vector<entry>::iterator temp;
		temp->name = name;
		temp->resultType = type;
		func_table.push_back(*temp);
		func = temp;
	}

	int search_param(string name, entry *func, vector<varEntry>::iterator var_ptr)
	{
		vector<varEntry>::iterator itr;
		for(itr = (func->parameter).begin(); itr != (func->parameter).end(); itr++)
		{
			if ((*itr).name == name)
			{
				var_ptr = itr;
				return 1;
			}
		}
		return 0;
	}

	void enter_param(string name, varEntry *var_ptr, string type, string ele, int arr_size)
	{
		varEntry *temp;
		(*temp).name = name;
		(*temp).ele = ele;
		(*temp).type = type;
		(*temp).level = 1; /*glob_level needs to be 1*/
		(*temp).val="0";
		(active_func->parameter).push_back(*temp);
		var_ptr = temp;
	}

	int search_var(string name, entry *func, vector<varEntry>::iterator var_ptr)
	{
		vector<varEntry>::iterator itr;
		for(itr = (func->variable).begin(); itr != (func->variable).end(); itr++)
		{
			if ((*itr).name == name)
			{
				var_ptr = itr;
				return 1;
			}
		}
		return 0;
	}

	void enter_var(string name, varEntry *var_ptr, string type, string ele, int arr_size)
	{
		varEntry *temp;
		(*temp).name = name;
		(*temp).ele = ele;
		(*temp).type = type;
		(*temp).level = glob_level;
		(*temp).val="0";
		(active_func->variable).push_back(*temp);
		var_ptr = temp;
	}
	int update_var(varEntry *var_ptr, string val, int index, string type )
	{
		if(type != (*var_ptr).type)
			return -1;
		(*var_ptr).val = val;
		return 1;
	}
	int update_param(vector<entry>::iterator func_ptr, string val, int index)
	{
		//(*func_ptr).parameter[(*func_ptr).parameter.size()-index].val[0] = val;
		(*func_ptr).parameter[index].val = val;
		return 1;
	}
	int coercible(string type1, string type2)
	{
		if (type1=="errortype" || type2=="errortype")
			return 0;
		return 1;
	}

	int compatibleBinOp(string type1, string type2)
	{
		if (type1=="errortype" || type2=="errortype" || type1=="bool" || type2=="bool")
			return 0;
		return 1;	
	}

	int compatibleRelOp(string type1, string type2)
	{
		if (type1=="errortype" || type2=="errortype" || type1=="char" || type2=="char")
			return 0;
		return 1;	
	}
	void patchtype(string type, vector<string> var_types ){
		vector<string>::iterator itr;
		vector<varEntry> temp;
		for(itr=var_types.begin(); itr!=var_types.end(); itr++)
		{
			varEntry temp1((*itr), "simple", "variable", glob_level, type);
			temp.push_back(temp1);
		}
		active_func->variable = temp;
	}
	vector<string> append_list(vector<string> var_types, string name){
		var_types.push_back(name);
		return var_types;
	}
	string compareTypes(string type1, string type2)
	{
		if((type1 == "char" && type2 == "char") || (type1 == "int" && type2 == "char") || (type1 == "char" && type2 == "int"))
			return "char";
		else if (type1 == "int" && type2 == "int")
			return "int";
		return "errortype";
	}
	/*void insertSymTable(string name, string type, string tag, int level, string value)
	{
		vector<entry>::iterator itr1;
		vector<varEntry>::iterator itr2;
		for(itr1 = func.begin(); itr1!=func.end(); itr1++)
		{
			for(itr2)
		}		
	}*/

	struct sattr
 	{
 		string name = "" ;
 		string type = "";
 		int val = -1;
 		vector<varEntry> param_types;
 		vector<string> var_types;
 		int pno;
  	};
  	union deftype
	{
		sattr* node;
	};
	#define YYSTYPE deftype

%}


/*%token <i> DIGITS NEGATIVENUMBER*/
/* %type <node> prog expr_binary e_prime assignment op_bin rlb rrb crb clb semi_colon comma id_or_digits relop fn_def fn_call_args fn_call incr bin_op_for terminate init for do_while while op_rel stmt_list if cond_loop expr_rel op func_args expressions stmt var_decl exps global_var_decl fn_decl macros g_decl
comma_exps exps_value_type  */
/* %type */
%token INT MAIN MACRO TYPEDEF SEMICOLON GLOBAL COMMA AMP VOID CHAR BOOL_DATATYPE
%token DATATYPE ID BOOL DIGITS NEGATIVENUMBER
%token ADD SUB MUL DIV MOD LT GT
%token FOR WHILE DO IF ELSE THEN
%token BREAK CONTINUE RETURN GOTO
%token CLB CRB RLB RRB SLB SRB
%token AND OR EQ NEQ LTEQ GTEQ
%start  prog 


%%

prog:   {printf("Hi\n");} fn_def  MAIN {
					printf("Hi\n");glob_level++;
					$2.node->name="main";
					vector<entry>::iterator funcPtr;
					if(searchFunction($2.node->name,funcPtr)==1)
						{yyerror("Function Name already exists.\n");
						}
					$2.node->pno = 0;
    				$2.node->type = "void";
    				if(searchFunction($2.node->name,funcPtr)==0){
    					enter_func($2.node->name,$2.node->type,funcPtr);
    						}
    					active_func = funcPtr; 
    					printf("\nI am in main \n");
    			} rlb rrb clb  {glob_level++;} stmt_list crb 
    // | fn_def error rlb rrb clb stmt_list crb {printf("No main function in this program\n");}
    ;

var_decl: datatype exps  					{patchtype($1.node->type, $2.node->var_types);}		                     
    // | error exps {printf("Expecting a datatype at lineNo %d\n", lineNo);}
    ;

exps: ID {$1.node->name = strdup(yytext);} exps_prime	{$$.node->var_types = append_list($2.node->var_types, $1.node->name);}			
exps_prime: comma_exps							{$$.node->var_types = $1.node->var_types;}	
            | slb DIGITS srb comma_exps 		{$$.node->var_types = $4.node->var_types;}
            ;	

comma_exps:  /* empty */                                        
    | comma exps         						{$$.node->var_types = $2.node->var_types;}                       
    ;
stmt_list: /* empty */                          
    | stmt semi_colon stmt_list                 
    ;

stmt: var_decl    					                              
    | assignment                                
    | cond_loop                                 
    | fn_call                                   
    ;
assignment: /* empty */							
            | ID {$1.node->name = strdup(yytext);}EQ assignment_prime		{ 
            																if($1.node->type != "errortype" && $3.node->type != "errortype"){
            																	if(!coercible($1.node->type, $3.node->type)){
            																	yyerror("type mismatch of operands in assignment");
            																	}

            																}}
            ;
assignment_prime: id_or_digits						{$$.node->type = $1.node->type;}	
                | fn_call 							{$$.node->type = $1.node->type;}	
                ;
expressions: expr_rel                           	{$$.node->type = $1.node->type;}	
    | expr_binary                               	{$$.node->type = $1.node->type;}	
    ;

expr_rel: op relop op     							{$$.node->type = "bool";
													if(compatibleRelOp($1.node->type,$3.node->type)){
														if($2.node->name == "AND"){
															$$.node->val = $1.node->val && $3.node->val;
														}
													if($2.node->name == "OR"){
															$$.node->val = $1.node->val || $3.node->val;
														}
													if($2.node->name == "NEQ"){
															$$.node->val = ($1.node->val != $3.node->val);
														}
													if($2.node->name == "LTEQ"){
															$$.node->val = $1.node->val <= $3.node->val;
														}
													if($2.node->name == "GTEQ"){
															$$.node->val = $1.node->val >= $3.node->val;
														}
													if($2.node->name == "LT"){
															$$.node->val = $1.node->val < $3.node->val;
														}
													if($2.node->name == "GT"){
															$$.node->val = $1.node->val > $3.node->val;
														}
													if($2.node->name == "EQ"){
															$$.node->val = ($1.node->val == $3.node->val);
														}
													}
													}                      
    ;

op: id_or_digits                                {$$.node->val = $1.node->val;
												$$.node->type = $1.node->type;}
    | rlb expressions rrb                       {$$.node->val = $2.node->val;
												$$.node->type = $2.node->type;}
    ;

 expr_binary: op_bin bin_op_for op_bin {$$.node->type = compareTypes($1.node->type,$3.node->type);	
 										if (compatibleBinOp($1.node->type,$3.node->type)){
	 										if($2.node->name == "ADD"){
	 											$$.node->val = $1.node->val + $3.node->val;
	 										}
	 										if($2.node->name == "SUB"){
	 											$$.node->val = $1.node->val - $3.node->val;
	 										}
	 										if($2.node->name == "MUL"){
	 											$$.node->val = $1.node->val * $3.node->val;
	 										}
	 										if($2.node->name == "DIV"){
	 											$$.node->val = $1.node->val / $3.node->val;
	 										}
	 									}
 										}//expr_binary_prime			{}
//     ;
// expr_binary_prime:  /*empty*/
//                 |  ADD expr_binary 				{}
//                 |  SUB expr_binary
//                 ;

// e_prime: op_bin e_prime_prime
//         ;
// e_prime_prime: /*empty*/
//             | MUL e_prime
//             | DIV e_prime
//             ;
op_bin: id_or_digits      						{$$.node->val = $1.node->val;
												$$.node->type = $1.node->type;}                      
    | rlb expr_binary rrb          				{$$.node->val = $1.node->val;
												$$.node->type = $1.node->type;}             
    ;

op_rel: DIGITS     				{$$.node->type = "bool";}                       
    | BOOL                      {$$.node->type = "bool";}                                       
    | expr_rel                  {$$.node->type = "bool";}                                       
    ;

/* All condition loops must end with semi colons */
cond_loop: if                                   
    | while                                     
    ;

if: IF rlb op_rel rrb THEN clb {glob_level++;}stmt_list {glob_level--;} crb else 
    // | IF rlb error rrb THEN clb stmt_list crb else {printf("Expecting a valid expression at lineNo %d\n", lineNo);}
    ;
else:  /* empty */
    | ELSE clb {glob_level++;} stmt_list{glob_level--;} crb
    ;

while: WHILE rlb op_rel rrb clb {glob_level++;} stmt_list {glob_level--;} crb   
    // | WHILE rlb error rrb clb stmt_list crb  {printf("Expecting a relation expression at lineNo %d\n", lineNo);}                                    
    ;

//for: FOR rlb assignment semi_colon terminate semi_colon incr rrb clb stmt_list crb 
  //  ;

// terminate: /* empty */                                          
//     | id_or_digits relop id_or_digits                          
//     ;


// incr: /* empty */                                              
//     | ID {$1.node->name = strdup(yytext);} '=' bin_op_for DIGITS 						{	$4.node->val = strdup(yytext);
//     													if($3.node->name == "ADD"){
//     													$1.node->val = (atoi(($1.node->val).c_str()) + atoi(($4.node->val).c_str())).str() ;
//     												} 
//     												if($3.node->name == "SUB"){
//     													$1.node->val = (atoi(($1.node->val).c_str()) - atoi(($4.node->val).c_str())).str() ;
//     												}
//     												if($3.node->name == "MUL"){
//     													$1.node->val = (atoi(($1.node->val).c_str()) * atoi(($4.node->val).c_str())).str() ;
//     												}
//     												if($3.node->name == "DIV"){
//     													$1.node->val = (atoi(($1.node->val).c_str()) / atoi(($4.node->val).c_str())).str() ;
//     												}
//     											}
//     ;
bin_op_for: ADD                                                {$$.node->name = "ADD";}
    | SUB                                                      {$$.node->name = "SUB";}
    | MUL                                                      {$$.node->name = "MUL";}
    | DIV                                                      {$$.node->name = "DIV";}
    // | error {printf("Expecting a binary operator at line no %d\n",lineNo);}
    ;

fn_call: ID {$$.node->name = strdup(yytext); $1.node->name = strdup(yytext); 
			vector<entry>::iterator funcPtr;
			if(searchFunction(yytext, funcPtr)==0)
			{
				yyerror("Function not declared.\n");
				$$.node->type = "errortype";
			}
			if(searchFunction(yytext, funcPtr)==1){
				call_func = funcPtr;
				$$.node->type = (*funcPtr).resultType;
			}

			} rlb fn_call_args rrb { if(call_func->parameter.size() != $3.node->pno){
								yyerror("mismatch in number of parameters in declaration and call\n");
							} 
							$$.node->type = "errortype";
						}
                       
    ;

fn_call_args: /* empty */                                       
    | id_or_digits fn_call_args_prime                       {$$.node->pno = 1 + $2.node->pno;
    														update_param(call_func,to_string($1.node->val),$$.node->pno);
    														}
    | bool_prod fn_call_args_prime                          {$$.node->pno = 1 + $2.node->pno;
    														update_param(call_func,to_string($1.node->val),$$.node->pno);
    														}
    ;
bool_prod: BOOL 											{$$.node->name = strdup(yytext);
															if($$.node->name == "true" || $$.node->name == "TRUE") $$.node->val = 1; else $$.node->val = 0; 
															$$.node->type = "bool";}
	;
fn_call_args_prime: /* empty */                     		        
                    | comma fn_call_args 					{$$.node->pno = $2.node->pno;}

fn_def: /* empty */                                             
    | datatype ID {$2.node->name=strdup(yytext);
    	vector<entry>::iterator funcPtr;
    	if(searchFunction($2.node->name,funcPtr)==1){
    		yyerror("Function Name already exists.\n");
    		$$.node->type = "errortype";
    	}
    }
		rlb {glob_level = 1;}func_args rrb
		{vector<entry>::iterator funcPtr;
		if(searchFunction($2.node->name,funcPtr)==0){
			$$.node->type = $1.node->type; 
			//$$.node->val = $7.node->val;
			$$.node->pno = $4.node->pno;
			$$.node->param_types = $4.node->param_types;		
			enter_func($2.node->name,$1.node->type,funcPtr);
			(*funcPtr).parameter=$4.node->param_types;
		}
		active_func = funcPtr; glob_level=2;
		}
		clb stmt_list RETURN ID crb {searchFunction("main", active_func);glob_level=0;} fn_def    
;
func_args: /* empty */       
    | datatype ID func_args_prime { varEntry temp($2.node->name, "simple", "parameter", 1, $1.node->type);
    								$$.node->param_types = $3.node->param_types;
    								$$.node->param_types.push_back(temp);}
    // | error ID {printf("Expecting a datatype at lineNo %d\n", lineNo);}

    // | datatype error {printf("Expecting ID name at lineNo %d\n", lineNo);}
    ;
func_args_prime: /* empty */
                | comma func_args {$$.node->param_types = $2.node->param_types;}
                ;

datatype: INT 										{$$.node->type = "int";}
        | VOID 										{$$.node->type = "void";}
        | CHAR 										{$$.node->type = "char";}
        | BOOL 										{$$.node->type = "bool";}
        ;


relop: AND                      {$$.node->name="AND";}
    | NEQ                       {$$.node->name="NEQ";}
    | OR                        {$$.node->name="OR";}
    | LTEQ                      {$$.node->name="LTEQ";}
    | GTEQ                      {$$.node->name="GTEQ";}
    | EQ                        {$$.node->name="EQ";}
    | LT                        {$$.node->name="LT";}
    |GT                         {$$.node->name="GT";}
    ;

id_or_digits: ID          						  		{$$.node->name = strdup(yytext);} 
    | DIGITS                    						{$$.node->val = atoi(yytext);}
    ;

comma: COMMA                    
    // | error {printf("Missing , at line no %d\n",lineNo);}
    ;

semi_colon: SEMICOLON           
    // | error {printf("Missing ; at line no %d\n",lineNo);}
    ;

rlb: RLB                        
    // | error {printf("Missing ( at line no %d\n",lineNo);}
    ;

rrb: RRB                        
    // | error {printf("Missing ) at line no %d\n",lineNo);}
    ;

clb: CLB                        
    // | error {printf("Missing { at line no %d\n",lineNo);}
    ;

crb: CRB                        
    // | error {printf("Missing } at line no %d\n",lineNo);}
    ;

slb: SLB                        
    // | error {printf("Missing [ at line no %d\n",lineNo);}
    ;

srb: SRB                        
    // | error {printf("Missing ] at line no %d\n",lineNo);}
    ;
%%

void yyerror(char *msg) {
    fprintf(stderr, "%s\n", msg);
    
}

int main(){
    yydebug = 1;
    yyparse();
    return 0 ;
}
