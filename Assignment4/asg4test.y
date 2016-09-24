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
	entry *active_func, *call_func;
	int glob_level;
	vector<string> varName;

	void symbolTable()
	{
 		printf("Name\tType\tParameters\tVariables\n");
		fflush(stdout);
		for(int i=0;i<func_table.size();i++)
		{
			printf("Entry Number: %d\n",i+1 );
			cout<<func_table[i].name<<"\t"<<func_table[i].resultType<<endl;
			printf("Parameters:\n");
			for(int j =0;j<func_table[i].parameter.size();j++)
				cout<<func_table[i].parameter[j].name<<"\t"<<func_table[i].parameter[j].type<<"\t"<<func_table[i].parameter[j].tag<<"\t"<<func_table[i].parameter[j].level<<"\t"<<func_table[i].parameter[j].ele<<endl;

			printf("Variables:\n");
			for(int j =0;j<func_table[i].variable.size();j++)
				cout<<func_table[i].variable[j].name<<"\t"<<func_table[i].variable[j].type<<"\t"<<func_table[i].variable[j].tag<<"\t"<<func_table[i].variable[j].level<<"\t"<<func_table[i].variable[j].ele<<endl;
		}
	}
	int searchFunction(string name, entry** func)
	{
		vector<entry>::iterator itr;
		for(itr=func_table.begin(); itr!=func_table.end();itr++)
		{
			cout<<"I am in searchFunction "<<name<<endl;fflush(stdout);
			if ((*itr).name == name)
			{	
				*func = &(*itr);
				return 1;
			}
		}
		return 0;
	}

	void enter_func(string name, string type, entry** func)
	{
		entry temp;
		temp.name = name;
		temp.resultType = type;
		func_table.push_back(temp);
		*func = &(func_table.back());
		cout<<(*func)->name;fflush(stdout);
		
	}

	int search_param(string name, entry *func, varEntry* var_ptr)
	{
		vector<varEntry>::iterator itr;
		for(itr = (func->parameter).begin(); itr != (func->parameter).end(); itr++)
		{
			if ((*itr).name == name)
			{
				var_ptr = &(*itr);
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

	int search_var(string name, entry *func, varEntry* var_ptr)
	{
		vector<varEntry>::iterator itr;
		for(itr = (func->variable).begin(); itr != (func->variable).end(); itr++)
		{
			if ((*itr).name == name && (*itr).level == glob_level)
			{
				var_ptr = &(*itr);
				return 1;
			}
			else if (glob_level ==2)
			{
				if(search_param(name, active_func, NULL)==1)
				{
					return 1;
				}
			}
			else
				return 0;
		}
		
		return 0;
	}

	void enter_var(string name, string type, string ele, int arr_size)
	{
		varEntry temp(name, "simple", "variable", glob_level, type);
		(temp).val="0";
		(active_func->variable).push_back(temp);
	}
	int update_var(varEntry* var_ptr, string val, int index, string type )
	{
		if(type != (*var_ptr).type)
			return -1;
		(*var_ptr).val = val;
		return 1;
	}
	int update_param(entry* func_ptr, string val, int index)
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
		for(itr=var_types.begin(); itr!=var_types.end(); itr++)
		{
			varEntry* temp1;
			if(search_var((*itr), active_func, NULL)!=1)
				enter_var((*itr), type, "simple", 1);
			else
				cout<<(*itr)<<": Variable Name with same identifier already exists!\n";

		}
	}
	vector<string> append_list(vector<string> var_types, string name){
		printf("Here in append_list ");fflush(stdout);
		var_types.push_back(name);
		cout<<name<<endl;
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
 		int pno=0;
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
%token ADD SUB MUL DIV MOD LT GT ASG
%token FOR WHILE DO IF ELSE THEN
%token BREAK CONTINUE RETURN GOTO ASSIGN
%token CLB CRB RLB RRB SLB SRB
%token AND OR EQ NEQ LTEQ GTEQ
%start  prog 


%%

prog:   fn_def  MAIN { sattr* temp = new sattr;
					glob_level++;
					temp->name = "main";
					entry* funcPtr;
					if(searchFunction(temp->name,&funcPtr)==1)
						{yyerror("Function Name already exists.\n");
						}
					temp->pno = 0;
    				temp->type = "void";
    				if(searchFunction(temp->name,&funcPtr)==0){
					printf("Hi\n");fflush(stdout);
    					enter_func(temp->name,temp->type,&funcPtr);
    						}
    					active_func = funcPtr;
    					cout<<active_func->name;fflush(stdout); 
    					printf("\nI am in main \n");
    					$2.node = temp;
    			} rlb rrb clb  {glob_level++;} stmt_list {
														vector<varEntry>::iterator itr;
														for(itr=active_func->variable.begin(); itr!=active_func->variable.end();itr++)
														{
															cout<<"Variable "<<(*itr).name<<endl;
															if((*itr).level == glob_level)
															{itr=active_func->variable.erase(itr);itr--;}
														}
												glob_level--;}
												crb {printf("----------------\n\n");symbolTable();}
    // | fn_def error rlb rrb clb stmt_list crb {printf("No main function in this program\n");}
    ;

var_decl: datatype exps  					{fflush(stdout);patchtype($1.node->type, varName);varName.clear();}		                     
    // | error exps {printf("Expecting a datatype at lineNo %d\n", lineNo);}
    ;

exps: ID {$$.node = new sattr;
		$1.node = new sattr;
		$1.node->name = strdup(yytext);
		varName.push_back($1.node->name);} 
		comma_exps {cout<<$2.node->name<<endl;fflush(stdout);
					$$.node->var_types = append_list($2.node->var_types, $1.node->name);
					vector<string>::iterator itr;
					for(itr=$$.node->var_types.begin();itr!=$$.node->var_types.end();itr++)
						cout<<(*itr)<<" Value"<<endl;
				}			
// exps_prime: comma_exps							{$$.node = new sattr;$$.node->var_types = $1.node->var_types;$$.node->name="tests";cout<<$1.node->name<<endl;fflush(stdout);}	
            // | slb DIGITS srb comma_exps 		{$$.node->var_types = $4.node->var_types;}
            // ;	

comma_exps: empty /* empty */                        {$$.node = new sattr;$$.node->name = "tests1";}              
    | comma exps         						{$$.node = new sattr;
    											$$.node->var_types = $2.node->var_types;
    											$$.node->name = "tests1";
												vector<string>::iterator itr;
    										for(itr=$$.node->var_types.begin();itr!=$$.node->var_types.end();itr++)
										cout<<(*itr)<<" CommaValue"<<endl;}                       
    ;
empty: /*empty*/
    ;

stmt_list: /* empty */                          
    | stmt semi_colon stmt_list                 
    ;

stmt: var_decl    					                              
    | ASSIGN assignment                                
    | cond_loop                                 
    | fn_call                                   
    ;
assignment: ID {$$.node = new sattr;$1.node = new sattr;
            	$1.node->name = strdup(yytext);
            	if(search_var($1.node->name, active_func, NULL)==0)
            		printf("Variable not declared!\n");}
            	ASG assignment_prime		{ $3.node = new sattr;
            								if($1.node->type != "errortype" && $3.node->type != "errortype"){
            									if(!coercible($1.node->type, $3.node->type)){
            										yyerror("type mismatch of operands in assignment");
            									}

            							}}
            ;
assignment_prime: id_or_digits						{$$.node = new sattr;$$.node->type = $1.node->type;}	
                | fn_call 							{$$.node = new sattr;$$.node->type = $1.node->type;}	
                | expr_binary 						{$$.node = new sattr;$$.node->type = $1.node->type;}
                ;

expressions: expr_rel                           	{$$.node = new sattr;$$.node->type = $1.node->type;}	
    | expr_binary                               	{$$.node = new sattr;$$.node->type = $1.node->type;}	
    ;

expr_rel: op relop op     							{$$.node = new sattr;$$.node->type = "bool";
													cout<<"Type1: "<<$1.node->type<<" Type2: "<<$3.node->type<<endl;
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
													else
														{cout<<$1.node->type<<" "<<$3.node->type<<"Relative expression types mismatch!"<<endl;
														$$.node->type = "errortype";}
													}                      
    ;

op: id_or_digits                                {$$.node = new sattr;$$.node->val = $1.node->val;
												$$.node->type = $1.node->type;}
    | rlb expressions rrb                       {$$.node = new sattr;$$.node->val = $2.node->val;
												$$.node->type = $2.node->type;}
    ;

 expr_binary: op_bin bin_op_for op_bin {$$.node = new sattr;$$.node->type = compareTypes($1.node->type,$3.node->type);	
 										cout<<"Type1: "<<$1.node->type<<" Type2: "<<$3.node->type<<endl;
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
	 									else
	 									{cout<<$1.node->type<<" "<<$3.node->type<<"Binary expression types mismatch!"<<endl;
														$$.node->type = "errortype";}
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
op_bin: id_or_digits      						{$$.node = new sattr;$$.node->val = $1.node->val;
												$$.node->type = $1.node->type;}                      
    | rlb expr_binary rrb          				{$$.node = new sattr;$$.node->val = $2.node->val;
												$$.node->type = $2.node->type;}             
    ;

op_rel: DIGITS     				{$$.node = new sattr;$$.node->type = "bool";}                       
    | BOOL                      {$$.node = new sattr;$$.node->type = "bool";}                                       
    | expr_rel                  {$$.node = new sattr;$$.node->type = $1.node->type;}                                       
    ;

/* All condition loops must end with semi colons */
cond_loop: if                    {cout<<"Finished IF"<<endl;fflush(stdout);}               
    | while                                     
    ;

if: IF rlb op_rel rrb THEN clb {glob_level++;} stmt_list {
														vector<varEntry>::iterator itr;
														for(itr=active_func->variable.begin(); itr!=active_func->variable.end();itr++)
														{
															cout<<"Variable "<<(*itr).name<<endl;
															if((*itr).level == glob_level)
															{itr=active_func->variable.erase(itr);itr--;}
														}
												glob_level--;} 
														crb else {cout<<"Finished IF"<<endl;fflush(stdout);}
    // | IF rlb error rrb THEN clb stmt_list crb else {printf("Expecting a valid expression at lineNo %d\n", lineNo);}
    ;
else:  /* empty */
    | ELSE clb {glob_level++;} stmt_list{
														vector<varEntry>::iterator itr;
														for(itr=active_func->variable.begin(); itr!=active_func->variable.end();itr++)
														{
															cout<<"Variable "<<(*itr).name<<endl;
															if((*itr).level == glob_level)
															{itr=active_func->variable.erase(itr);itr--;}
														}
												glob_level--;} crb
    ;

while: WHILE rlb op_rel rrb clb {glob_level++;} stmt_list {
														vector<varEntry>::iterator itr;
														for(itr=active_func->variable.begin(); itr!=active_func->variable.end();itr++)
														{
															cout<<"Variable "<<(*itr).name<<endl;
															if((*itr).level == glob_level)
															{itr=active_func->variable.erase(itr);itr--;}
														}
												glob_level--;} crb   
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
bin_op_for: ADD                                                {$$.node = new sattr;$$.node->name = "ADD";}
    | SUB                                                      {$$.node = new sattr;$$.node->name = "SUB";}
    | MUL                                                      {$$.node = new sattr;$$.node->name = "MUL";}
    | DIV                                                      {$$.node = new sattr;$$.node->name = "DIV";}
    // | error {printf("Expecting a binary operator at line no %d\n",lineNo);}
    ;

fn_call: ID {$$.node->name = strdup(yytext); $1.node->name = strdup(yytext); 
			entry* funcPtr;
			if(searchFunction(yytext, &funcPtr)==0)
			{
				yyerror("Function not declared.\n");
				$$.node->type = "errortype";
			}
			if(searchFunction(yytext, &funcPtr)==1){
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

fn_def: /* empty */       {$$.node = new sattr;}                                      
    | datatype ID {$2.node = new sattr;$2.node->name=strdup(yytext);
    	entry* funcPtr;
    	if(searchFunction($2.node->name,&funcPtr)==1){
    		yyerror("Function Name already exists.\n");
    		$$.node->type = "errortype";
    	}
    }
		rlb {glob_level = 1;}func_args rrb
		{$$.node = new sattr;entry* funcPtr;
		if(searchFunction($2.node->name,&funcPtr)==0){
			$$.node->type = $1.node->type; 
			$$.node->param_types = $4.node->param_types;		
			enter_func($2.node->name,$1.node->type,&funcPtr);
			(*funcPtr).parameter=$4.node->param_types;
		}
		active_func = funcPtr; glob_level=2;
		}
		clb stmt_list {
														vector<varEntry>::iterator itr;
														for(itr=active_func->variable.begin(); itr!=active_func->variable.end();itr++)
														{
															cout<<"Variable "<<(*itr).name<<endl;
															if((*itr).level == glob_level)
															{itr=active_func->variable.erase(itr);itr--;}
														}
												glob_level--;}
												RETURN ID crb {searchFunction("main", &active_func);glob_level=0;} fn_def    
;
func_args: /* empty */       {$$.node = new sattr;}
    | {$$.node = new sattr;}datatype ID {$2.node = new sattr;}func_args_prime { varEntry temp($2.node->name, "simple", "parameter", 1, $1.node->type);
    								$$.node->param_types = $3.node->param_types;
    								$$.node->param_types.push_back(temp);}
    // | error ID {printf("Expecting a datatype at lineNo %d\n", lineNo);}

    // | datatype error {printf("Expecting ID name at lineNo %d\n", lineNo);}
    ;
func_args_prime: /* empty */{$$.node = new sattr;}
                | {$$.node = new sattr;}comma func_args {$$.node->param_types = $2.node->param_types;}
                ;

datatype: INT 										{$$.node = new sattr;$$.node->type = "int";}
        | VOID 										{$$.node = new sattr;$$.node->type = "void";}
        | CHAR 										{$$.node = new sattr;$$.node->type = "char";}
        | BOOL 										{$$.node = new sattr;$$.node->type = "bool";}
        ;


relop: AND                      {$$.node = new sattr;$$.node->name="AND";}
    | NEQ                       {$$.node = new sattr;$$.node->name="NEQ";}
    | OR                        {$$.node = new sattr;$$.node->name="OR";}
    | LTEQ                      {$$.node = new sattr;$$.node->name="LTEQ";}
    | GTEQ                      {$$.node = new sattr;$$.node->name="GTEQ";}
    | EQ                        {$$.node = new sattr;$$.node->name="EQ";}
    | LT                        {$$.node = new sattr;$$.node->name="LT";}
    |GT                         {$$.node = new sattr;$$.node->name="GT";}
    ;

id_or_digits: ID          						  		{$$.node = new sattr;$$.node->name = strdup(yytext);
														vector<varEntry>::reverse_iterator itr;
														int found = 0;
														for(itr=active_func->variable.rbegin(); itr!=active_func->variable.rend(); itr++)
														{
															if((*itr).level <= glob_level && (*itr).name == $$.node->name)
															{
																$$.node->type = (*itr).ele;
																found = 1;
																break;
															}
														}
														if(!found)
														{
															for(itr=active_func->parameter.rbegin(); itr!=active_func->parameter.rend(); itr++)
															{	
																if((*itr).level <= glob_level && (*itr).name == $$.node->name)
																{
																	$$.node->type = (*itr).ele;
																	break;
																}
															}
														}
														if(!found){cout<<$$.node->name<<"---Element not declared"<<endl;}
														} 
    | DIGITS                    						{$$.node = new sattr;$$.node->val = atoi(yytext);$$.node->type="int";}
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

// slb: SLB                        
    // | error {printf("Missing [ at line no %d\n",lineNo);}
    // ;

// srb: SRB                        
    // | error {printf("Missing ] at line no %d\n",lineNo);}
    // ;
%%

void yyerror(char *msg) {
    fprintf(stderr, "%s\n", msg);
    
}

int main(){
    yydebug = 1;
    yyparse();
    return 0 ;
}
