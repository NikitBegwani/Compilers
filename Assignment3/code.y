
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
    extern int  yylex();
    extern int lineNo;
    extern char* yytext;
    extern int yyleng;

    struct tree_node
    {
        string code;
        vector<tree_node*> v;
    };
    tree_node* root;
    union deftype
    {
        tree_node* node;
    };
    #define YYSTYPE deftype

%}


/*%token <i> DIGITS NEGATIVENUMBER*/
/* %type <node> prog expr_binary e_prime op_bin rlb rrb crb clb semi_colon comma id_or_digits relop fn_def fn_call_args fn_call incr bin_op_for terminate init for do_while while op_rel stmt_list if cond_loop expr_rel op func_args expressions stmt var_decl exps global_var_decl fn_decl macros g_decl
comma_exps exps_value_type  */
/* %type */
%token INT MAIN MACRO TYPEDEF SEMICOLON GLOBAL COMMA AMP
%token DATATYPE ID BOOL DIGITS NEGATIVENUMBER
%token ADD SUB MUL DIV MOD LT GT
%token FOR WHILE DO IF ELSE THEN
%token BREAK CONTINUE RETURN GOTO
%token CLB CRB RLB RRB SLB SRB
%token AND OR EQ NEQ LTEQ GTEQ
%start  prog 


%%

prog:   g_decl MAIN rlb rrb clb stmt_list crb fn_def        { tree_node* temp = new tree_node;
                                                            tree_node* main = new tree_node;
                                                            temp->code = "prog";
                                                            main->code = "MAIN";
                                                            (temp->v).push_back($1.node);
                                                            (temp->v).push_back(main);
                                                            (temp->v).push_back($3.node);
                                                            (temp->v).push_back($4.node);
                                                            (temp->v).push_back($5.node);
                                                            (temp->v).push_back($6.node);   
                                                            (temp->v).push_back($7.node);
                                                            (temp->v).push_back($8.node);
                                                            root = temp;
                                                            $$.node = root;}        
    | g_decl error rlb rrb clb stmt_list crb fn_def {printf("No main function in this program\n");}
    ;

g_decl: macros fn_decl global_var_decl                      {tree_node* temp = new tree_node;
                                                            temp->code = "g_decl";
                                                            (temp->v).push_back($1.node);
                                                            (temp->v).push_back($2.node);
                                                            (temp->v).push_back($3.node);
                                                            $$.node = temp;
                                                            }
    ;

macros: /* empty */                                         { tree_node* temp = new tree_node;
                                                            temp->code = "EPSILON";
                                                            $$.node = temp;
                                                            }
    |    MACRO macros                                       { tree_node* temp = new tree_node;
                                                            temp->code = "MACRO";
                                                            tree_node* macro = new tree_node;
                                                            macro->code = "MACRO";
                                                            (temp->v).push_back(macro);                                             
                                                            (temp->v).push_back($2.node);
                                                            $$.node = temp;}
    ;

fn_decl: /* empty  */                                       { tree_node* temp = new tree_node;
                                                            temp->code = "EPSILON";
                                                            $$.node = temp;}
    | DATATYPE ID rlb func_args rrb semi_colon fn_decl      { tree_node* temp = new tree_node;
                                                            temp->code = "FN_DECL";
                                                            tree_node* datatype = new tree_node;
                                                            datatype->code = "DATATYPE";
                                                            (temp->v).push_back(datatype);
                                                            tree_node* id = new tree_node;
                                                            id->code = "ID";
                                                            (temp->v).push_back(id);
                                                            (temp->v).push_back($3.node);
                                                            (temp->v).push_back($4.node);
                                                            (temp->v).push_back($5.node);
                                                            (temp->v).push_back($6.node);
                                                            (temp->v).push_back($7.node);
                                                            $$.node = temp;}

    | error ID rlb func_args rrb semi_colon fn_decl {printf("Expecting a function datatype at lineNo %d\n", lineNo);}
    ;

global_var_decl: /* empty */                                { tree_node* temp = new tree_node;
                                                            temp->code = "EPSILON";
                                                            $$.node = temp;}
    | GLOBAL DATATYPE exps semi_colon global_var_decl       { tree_node* temp = new tree_node;
                                                            temp->code = "GLOBAL_VAR_DECL";
                                                            tree_node* global = new tree_node;
                                                            global->code = "GLOBAL";
                                                            tree_node* datatype = new tree_node;
                                                            datatype->code = "DATATYPE";
                                                            (temp->v).push_back(global);
                                                            (temp->v).push_back(datatype);
                                                            (temp->v).push_back($3.node);
                                                            (temp->v).push_back($4.node);
                                                            (temp->v).push_back($5.node);
                                                            $$.node = temp;}
    ;

var_decl: DATATYPE exps                                 { tree_node* temp = new tree_node;
                                                            temp->code = "VAR_DECL";
                                                            tree_node* datatype = new tree_node;
                                                            datatype->code = "DATATYPE";
                                                            (temp->v).push_back(datatype);
                                                            (temp->v).push_back($2.node);
                                                            $$.node = temp;}
    | error exps {printf("Expecting a datatype at lineNo %d\n", lineNo);}
    ;

exps: ID                                        { tree_node* temp = new tree_node;
                                                            temp->code = "EXPS";
                                                            tree_node* id = new tree_node;
                                                            id->code = "ID";
                                                            (temp->v).push_back(id);
                                                            $$.node = temp;}
    | ID comma exps                                     { tree_node* temp = new tree_node;
                                                            temp->code = "EXPS";
                                                            tree_node* id = new tree_node;
                                                            id->code = "ID";
                                                            (temp->v).push_back(id);
                                                            (temp->v).push_back($2.node);
                                                            (temp->v).push_back($3.node);
                                                            $$.node = temp;}

    | ID '=' exps_value_type comma_exps                             { tree_node* temp = new tree_node;
                                                            temp->code = "EXPS";
                                                            tree_node* id = new tree_node;
                                                            id->code = "ID";
                                                            (temp->v).push_back(id);
                                                            tree_node* equals = new tree_node;
                                                            equals->code = "=";
                                                            (temp->v).push_back(equals);
                                                            (temp->v).push_back($3.node);
                                                            (temp->v).push_back($4.node);
                                                            $$.node = temp;}
    ;

exps_value_type: DIGITS                                     { tree_node* temp = new tree_node;
                                                            temp->code = "EXPS_VALUE_TYPE";
                                                            tree_node* id = new tree_node;
                                                            id->code = "ID";
                                                            (temp->v).push_back(id);
                                                            $$.node = temp;}
    | NEGATIVENUMBER                                        { tree_node* temp = new tree_node;
                                                            temp->code = "EXPS_VALUE_TYPE";
                                                            tree_node* id = new tree_node;
                                                            id->code = "NEGATIVENUMBER";
                                                            (temp->v).push_back(id);
                                                            $$.node = temp;}
    | BOOL                                                  { tree_node* temp = new tree_node;
                                                            temp->code = "EXPS_VALUE_TYPE";
                                                            tree_node* id = new tree_node;
                                                            id->code = "BOOL";
                                                            (temp->v).push_back(id);
                                                            $$.node = temp;}
    | error {printf("Invalid value type at line no %d\n", lineNo);}
    ;

comma_exps:                                             { tree_node* temp = new tree_node;
                                                            temp->code = "EPSILON";
                                                            $$.node = temp;}
    | comma exps                                { tree_node* temp = new tree_node;
                                                            temp->code = "COMMA_EXPS";
                                                            (temp->v).push_back($1.node);
                                                            (temp->v).push_back($2.node);
                                                            $$.node = temp;}
    ;
func_args: /* empty */                                  { tree_node* temp = new tree_node;
                                                            temp->code = "EPSILON";
                                                            $$.node = temp;}
    | DATATYPE ID comma func_args                       { tree_node* temp = new tree_node;
                                                            temp->code = "FUNC_ARGS";
                                                            tree_node* datatype = new tree_node;
                                                            datatype->code = "DATATYPE";
                                                            (temp->v).push_back(datatype);
                                                            tree_node* id = new tree_node;
                                                            id->code = "ID";
                                                            (temp->v).push_back(id);
                                                            (temp->v).push_back($3.node);
                                                            (temp->v).push_back($4.node);
                                                            $$.node = temp;}
    | DATATYPE ID                                       { tree_node* temp = new tree_node;
                                                            temp->code = "FUNC_ARGS";
                                                            tree_node* datatype = new tree_node;
                                                            datatype->code = "DATATYPE";
                                                            (temp->v).push_back(datatype);
                                                            tree_node* id = new tree_node;
                                                            id->code = "ID";
                                                            (temp->v).push_back(id);
                                                            $$.node = temp;}
    
    | error ID {printf("Expecting a datatype at lineNo %d\n", lineNo);}

    | DATATYPE error {printf("Expecting ID name at lineNo %d\n", lineNo);}
    ;

stmt_list: /* empty */                                  { tree_node* temp = new tree_node;
                                                            temp->code = "EPSILON";
                                                            $$.node = temp;}
    | stmt semi_colon stmt_list                         { tree_node* temp = new tree_node;
                                                            temp->code = "STMT_LIST";
                                                            (temp->v).push_back($1.node);
                                                            (temp->v).push_back($2.node);
                                                            (temp->v).push_back($3.node);
                                                            $$.node = temp;}
    ;

stmt: var_decl                                          { tree_node* temp = new tree_node;
                                                            temp->code = "STMT";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    | expressions                                       { tree_node* temp = new tree_node;
                                                            temp->code = "STMT";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    | cond_loop                                         { tree_node* temp = new tree_node;
                                                            temp->code = "STMT";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    | fn_call                                           { tree_node* temp = new tree_node;
                                                            temp->code = "STMT";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    ;

expressions: expr_rel                                   { tree_node* temp = new tree_node;
                                                            temp->code = "EXPRESSIONS";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    | expr_binary                                       { tree_node* temp = new tree_node;
                                                            temp->code = "EXPRESSIONS";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    ;

expr_rel: op relop op                                   { tree_node* temp = new tree_node;
                                                            temp->code = "EXPR_REL";
                                                            (temp->v).push_back($1.node);
                                                            (temp->v).push_back($2.node);
                                                            (temp->v).push_back($3.node);
                                                            $$.node = temp;}
    ;

op: id_or_digits                                        { tree_node* temp = new tree_node;
                                                            temp->code = "OP";
                                                            (temp->v).push_back($1.node);}
    | rlb expressions rrb                               { tree_node* temp = new tree_node;
                                                            temp->code = "OP";
                                                            (temp->v).push_back($1.node);
                                                            (temp->v).push_back($2.node);
                                                            (temp->v).push_back($3.node);
                                                            $$.node = temp;}
    ;

expr_binary: e_prime ADD expr_binary                    { tree_node* temp = new tree_node;
                                                            temp->code = "EXPR_BINARY";
                                                            (temp->v).push_back($1.node);
                                                            tree_node* add = new tree_node;
                                                            add->code = "ADD";
                                                            (temp->v).push_back(add);
                                                            (temp->v).push_back($3.node);
                                                            $$.node = temp;}
    | e_prime SUB expr_binary                           { tree_node* temp = new tree_node;
                                                            temp->code = "EXPR_BINARY";
                                                            (temp->v).push_back($1.node);
                                                            tree_node* sub = new tree_node;
                                                            sub->code = "SUB";
                                                            (temp->v).push_back(sub);
                                                            (temp->v).push_back($3.node);
                                                            $$.node = temp;}
    | e_prime                                           { tree_node* temp = new tree_node;
                                                            temp->code = "EXPR_BINARY";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    ;

e_prime: op_bin MUL e_prime                             { tree_node* temp = new tree_node;
                                                            temp->code = "E_PRIME";
                                                            (temp->v).push_back($1.node);
                                                            tree_node* mul = new tree_node;
                                                            mul->code = "MUL";
                                                            (temp->v).push_back(mul);
                                                            (temp->v).push_back($3.node);
                                                            $$.node = temp;}    
    | op_bin DIV e_prime                                { tree_node* temp = new tree_node;
                                                            temp->code = "E_BINARY";
                                                            (temp->v).push_back($1.node);
                                                            tree_node* div = new tree_node;
                                                            div->code = "DIV";
                                                            (temp->v).push_back(div);
                                                            (temp->v).push_back($3.node);
                                                            $$.node = temp;}
    | op_bin                                            { tree_node* temp = new tree_node;
                                                            temp->code = "E_BINARY";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    ;

op_bin: id_or_digits                                    { tree_node* temp = new tree_node;
                                                            temp->code = "OP_BINARY";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    | rlb expr_binary rrb                               { tree_node* temp = new tree_node;
                                                            temp->code = "OP_BINARY";
                                                            (temp->v).push_back($1.node);
                                                            (temp->v).push_back($2.node);
                                                            (temp->v).push_back($3.node);
                                                            $$.node = temp;}
    ;

op_rel: id_or_digits                                    { tree_node* temp = new tree_node;
                                                            temp->code = "OP_RELATIVE";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    | BOOL                                              { tree_node* temp = new tree_node;
                                                            temp->code = "BOOL";
                                                            $$.node = temp;}
    | expr_rel                                          { tree_node* temp = new tree_node;
                                                            temp->code = "OP_RELATIVE";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    ;

/* All condition loops must end with semi colons */
cond_loop: if                                           { tree_node* temp = new tree_node;
                                                            temp->code = "COND_LOOP";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    | while                                             { tree_node* temp = new tree_node;
                                                            temp->code = "COND_LOOP";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    | do_while                                          { tree_node* temp = new tree_node;
                                                            temp->code = "COND_LOOP";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    | for                                               { tree_node* temp = new tree_node;
                                                            temp->code = "COND_LOOP";
                                                            (temp->v).push_back($1.node);
                                                            $$.node = temp;}
    ;

if: IF rlb expressions rrb THEN clb stmt_list crb       { tree_node* temp = new tree_node;
                                                            temp->code = "IF";
                                                            tree_node* if1 = new tree_node;
                                                            if1->code = "IF";
                                                            (temp->v).push_back(if1);
                                                            (temp->v).push_back($2.node);
                                                            (temp->v).push_back($3.node);
                                                            (temp->v).push_back($4.node);
                                                            tree_node* then = new tree_node;
                                                            then->code = "THEN";
                                                            (temp->v).push_back(then);
                                                            (temp->v).push_back($6.node);
                                                            (temp->v).push_back($7.node);
                                                            (temp->v).push_back($8.node);
                                                            $$.node = temp;}
    | IF rlb expressions rrb THEN clb stmt_list crb ELSE clb stmt_list crb { tree_node* temp = new tree_node;
                                                            temp->code = "IF";
                                                            tree_node* if1 = new tree_node;
                                                            if1->code = "IF";
                                                            (temp->v).push_back(if1);
                                                            (temp->v).push_back($2.node);
                                                            (temp->v).push_back($3.node);
                                                            (temp->v).push_back($4.node);
                                                            tree_node* then = new tree_node;
                                                            then->code = "THEN";
                                                            (temp->v).push_back(then);
                                                            (temp->v).push_back($6.node);
                                                            (temp->v).push_back($7.node);
                                                            (temp->v).push_back($8.node);
                                                            tree_node* else1 = new tree_node;
                                                            else1->code = "ELSE";
                                                            (temp->v).push_back(else1);
                                                            (temp->v).push_back($10.node);
                                                            (temp->v).push_back($11.node);
                                                            (temp->v).push_back($12.node);
                                                            $$.node = temp;}
    | IF rlb error rrb THEN clb stmt_list crb {printf("Expecting a valid expression at lineNo %d\n", lineNo);}
    | IF rlb error rrb THEN clb stmt_list crb ELSE clb stmt_list crb {printf("Expecting a valid expression at lineNo %d\n", lineNo);}
    ;

while: WHILE rlb op_rel rrb clb stmt_list crb                               {tree_node* temp = new tree_node;
                                                                              temp->code = "WHILE_LOOP";
                                                                              tree_node* while1 = new tree_node;
                                                                              while1->code = "while";
                                                                              (temp->v).push_back(while1);
                                                                              (temp->v).push_back($2.node);
                                                                              (temp->v).push_back($3.node);
                                                                              (temp->v).push_back($4.node);
                                                                              (temp->v).push_back($5.node);
                                                                              (temp->v).push_back($6.node);
                                                                              (temp->v).push_back($7.node);
                                                                              $$.node = temp;}
    | WHILE rlb error rrb clb stmt_list crb  {printf("Expecting a relation expression at lineNo %d\n", lineNo);}                                    
    ;

do_while: DO clb stmt_list crb WHILE rlb op_rel rrb                             {tree_node* temp = new tree_node;
                                                                              temp->code = "DO_WHILE_LOOP";
                                                                              tree_node* do1 = new tree_node;
                                                                              do1->code = "do";
                                                                              (temp->v).push_back(do1);
                                                                              (temp->v).push_back($2.node);
                                                                              (temp->v).push_back($3.node);
                                                                              (temp->v).push_back($4.node);
                                                                              tree_node* while1 = new tree_node;
                                                                              while1->code = "while";
                                                                              (temp->v).push_back(while1);
                                                                              (temp->v).push_back($6.node);
                                                                              (temp->v).push_back($7.node);
                                                                              (temp->v).push_back($8.node);
                                                                              $$.node = temp;}
                                                                              
                                                                             
    ;

for: FOR rlb init semi_colon terminate semi_colon incr rrb clb stmt_list crb {tree_node* temp = new tree_node;
                                                                              temp->code = "FOR_LOOP";
                                                                              tree_node* for1 = new tree_node;
                                                                              for1->code = "for";
                                                                              (temp->v).push_back(for1);
                                                                              (temp->v).push_back($2.node);
                                                                              (temp->v).push_back($3.node);
                                                                              (temp->v).push_back($4.node);
                                                                              (temp->v).push_back($5.node);
                                                                              (temp->v).push_back($6.node);
                                                                              (temp->v).push_back($7.node);
                                                                              (temp->v).push_back($8.node);
                                                                              (temp->v).push_back($9.node);
                                                                              (temp->v).push_back($10.node);
                                                                              (temp->v).push_back($11.node);
                                                                              $$.node = temp;}

    ;

init: /* empty */                                               {tree_node* temp = new tree_node;
                                                                temp->code = "EPSILON";
                                                                $$.node = temp;}
    | ID '=' id_or_digits                                       {tree_node* temp = new tree_node;
                                                                temp->code = "INIT";
                                                                tree_node* id = new tree_node;
                                                                id->code = "ID";
                                                                (temp->v).push_back(id);
                                                                tree_node* equals = new tree_node;
                                                                equals->code = "=";
                                                                (temp->v).push_back(equals);
                                                                (temp->v).push_back($3.node);
                                                                $$.node = temp;}
    ;

terminate: /* empty */                                          {tree_node* temp = new tree_node;
                                                                temp->code = "EPSILON";
                                                                $$.node = temp;}
    | id_or_digits relop id_or_digits                           {tree_node* temp = new tree_node;
                                                                temp->code = "TERMINATE";
                                                                (temp->v).push_back($1.node);
                                                                (temp->v).push_back($2.node);
                                                                (temp->v).push_back($3.node);
                                                                $$.node = temp;}
    ;

bin_op_for: ADD                                                 {tree_node* temp = new tree_node;
                                                                temp->code = "ADD";
                                                                $$.node = temp;}
    | SUB                                                       {tree_node* temp = new tree_node;
                                                                temp->code = "SUB";
                                                                $$.node = temp;}
    | MUL                                                       {tree_node* temp = new tree_node;
                                                                temp->code = "MUL";
                                                                $$.node = temp;}
    | DIV                                                       {tree_node* temp = new tree_node;
                                                                temp->code = "DIV";
                                                                $$.node = temp;}
    | error {printf("Expecting a binary operator at line no %d\n",lineNo);}
    ;

incr: /* empty */                                               {tree_node* temp = new tree_node;
                                                                temp->code = "EPSILON";
                                                                $$.node = temp;}
    | ID '=' bin_op_for id_or_digits                            {tree_node* temp = new tree_node;
                                                                temp->code = "INCR";
                                                                tree_node* id = new tree_node;
                                                                id->code = "ID";
                                                                (temp->v).push_back(id);
                                                                tree_node* equals = new tree_node;
                                                                equals->code = "=";
                                                                (temp->v).push_back(equals);
                                                                (temp->v).push_back($3.node);
                                                                (temp->v).push_back($4.node);
                                                                $$.node = temp;}
    ;

fn_call: ID rlb fn_call_args rrb                                {tree_node* temp = new tree_node;
                                                                temp->code = "FN_CALL";
                                                                tree_node* id = new tree_node;
                                                                id->code = "ID";
                                                                (temp->v).push_back(id);
                                                                (temp->v).push_back($2.node);
                                                                (temp->v).push_back($3.node);
                                                                (temp->v).push_back($4.node);
                                                                $$.node = temp;}
    ;

fn_call_args: /* empty */                                       {tree_node* temp = new tree_node;
                                                                temp->code = "EPSILON";
                                                                $$.node = temp;}
    | id_or_digits comma fn_call_args                           {tree_node* temp = new tree_node;
                                                                temp->code = "FN_CALL_ARGS";
                                                                (temp->v).push_back($1.node);
                                                                (temp->v).push_back($2.node);
                                                                (temp->v).push_back($3.node);
                                                                $$.node = temp;}
    | id_or_digits                                              {tree_node* temp = new tree_node;
                                                                temp->code = "FN_CALL_ARGS";
                                                                (temp->v).push_back($1.node);
                                                                $$.node = temp;}
    | BOOL comma fn_call_args                                   {tree_node* temp = new tree_node;
                                                                temp->code = "FN_CALL_ARGS";
                                                                tree_node* bool1 = new tree_node;
                                                                bool1->code = "BOOL";
                                                                (temp->v).push_back(bool1);
                                                                (temp->v).push_back($2.node);
                                                                (temp->v).push_back($3.node);
                                                                $$.node = temp;}
    | BOOL                                                      {tree_node* temp = new tree_node;
                                                                temp->code = "FN_CALL_ARGS";
                                                                tree_node* bool1 = new tree_node;
                                                                bool1->code = "BOOL";
                                                                (temp->v).push_back(bool1);
                                                                $$.node = temp;}
    ;

fn_def: /* empty */                                             {tree_node* temp = new tree_node;
                                                                temp->code = "EPSILON";
                                                                $$.node = temp;}
    | DATATYPE ID rlb func_args rrb clb stmt_list crb fn_def    {tree_node* temp = new tree_node;
                                                                temp->code = "FN_DEF";
                                                                tree_node* datatype = new tree_node;
                                                                datatype->code = "DATATYPE";
                                                                tree_node* id = new tree_node;
                                                                id->code = "ID";
                                                                (temp->v).push_back(datatype);
                                                                (temp->v).push_back(id);
                                                                (temp->v).push_back($3.node);
                                                                (temp->v).push_back($4.node);
                                                                (temp->v).push_back($5.node);
                                                                (temp->v).push_back($6.node);
                                                                (temp->v).push_back($7.node);
                                                            $$.node = temp;}
    ;

relop: AND                      {tree_node* temp = new tree_node;
                                temp->code = "AND";
                                $$.node = temp;}
    | NEQ                       {tree_node* temp = new tree_node;
                                temp->code = "NEQ";
                                $$.node = temp;}
    | OR                        {tree_node* temp = new tree_node;
                                temp->code = "OR";
                                $$.node = temp;}
    | LTEQ                      {tree_node* temp = new tree_node;
                                temp->code = "LTEQ";
                                $$.node = temp;}
    | GTEQ                      {tree_node* temp = new tree_node;
                                temp->code = "GTEQ";
                                $$.node = temp;}
    | EQ                        {tree_node* temp = new tree_node;
                                temp->code = "EQ";
                                $$.node = temp;}
    | LT                        {tree_node* temp = new tree_node;
                                temp->code = "LT";
                                $$.node = temp;}

    |GT                         {tree_node* temp = new tree_node;
                                temp->code = "GT";
                                $$.node = temp;}

    ;

id_or_digits: ID                {tree_node* temp = new tree_node;
                                temp->code = "ID";
                                $$.node = temp;}
    | DIGITS                    {tree_node* temp = new tree_node;
                                temp->code = "DIGITS";
                                $$.node = temp;}
    | NEGATIVENUMBER            {tree_node* temp = new tree_node;
                                temp->code = "NEGATIVENUMBER";
                                $$.node = temp;}
    ;

comma: COMMA                    { tree_node* temp = new tree_node;
                                temp->code = ",";
                                $$.node = temp;}
    | error {printf("Missing , at line no %d\n",lineNo);}
    ;

semi_colon: SEMICOLON           { tree_node* temp = new tree_node;
                                temp->code = ";";
                                $$.node = temp;}
    | error {printf("Missing ; at line no %d\n",lineNo);}
    ;

rlb: RLB                        { tree_node* temp = new tree_node;
                                temp->code = "(";
                                $$.node = temp;}
    | error {printf("Missing ( at line no %d\n",lineNo);}
    ;

rrb: RRB                        { tree_node* temp = new tree_node;
                                temp->code = ")";
                                $$.node = temp;}
    | error {printf("Missing ) at line no %d\n",lineNo);}
    ;

clb: CLB                        { tree_node* temp = new tree_node;
                                temp->code = "{";
                                $$.node = temp;}
    | error {printf("Missing { at line no %d\n",lineNo);}
    ;

crb: CRB                            { tree_node* temp = new tree_node;
                                    temp->code = "}";
                                    $$.node = temp;}
    | error {printf("Missing } at line no %d\n",lineNo);}
    ;

%%

void yyerror(char *msg) {
    fprintf(stderr, "%s\n", msg);
    
}

void print_tree(tree_node *node,int index)
{
    for(int i=0;i<index;i++) 
    cout<<"==";    
    cout<<"> ";
    
    if(node==NULL){
        cout<<"Empty Node";
        return;
    }

    cout << node->code << endl;

    for (int i = 0; i < (node->v).size(); ++i)
    {
        print_tree((node->v)[i],index+1);
    }
}
int main(){
    yydebug = 1;
    yyparse();
    print_tree(root,0);
    return 0 ;
}
