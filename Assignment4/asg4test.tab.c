/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 17 "asg4test.y" /* yacc.c:339  */

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


#line 306 "asg4test.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "asg4test.tab.h".  */
#ifndef YY_YY_ASG4TEST_TAB_H_INCLUDED
# define YY_YY_ASG4TEST_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    MAIN = 259,
    MACRO = 260,
    TYPEDEF = 261,
    SEMICOLON = 262,
    GLOBAL = 263,
    COMMA = 264,
    AMP = 265,
    VOID = 266,
    CHAR = 267,
    BOOL_DATATYPE = 268,
    DATATYPE = 269,
    ID = 270,
    BOOL = 271,
    DIGITS = 272,
    NEGATIVENUMBER = 273,
    ADD = 274,
    SUB = 275,
    MUL = 276,
    DIV = 277,
    MOD = 278,
    LT = 279,
    GT = 280,
    ASG = 281,
    FOR = 282,
    WHILE = 283,
    DO = 284,
    IF = 285,
    ELSE = 286,
    THEN = 287,
    BREAK = 288,
    CONTINUE = 289,
    RETURN = 290,
    GOTO = 291,
    ASSIGN = 292,
    CLB = 293,
    CRB = 294,
    RLB = 295,
    RRB = 296,
    SLB = 297,
    SRB = 298,
    AND = 299,
    OR = 300,
    EQ = 301,
    NEQ = 302,
    LTEQ = 303,
    GTEQ = 304
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_ASG4TEST_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 407 "asg4test.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   135

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  147

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   274,   274,   291,   291,   274,   304,   308,   308,   322,
     323,   330,   333,   334,   337,   338,   339,   340,   342,   342,
     354,   355,   356,   359,   360,   363,   397,   399,   403,   435,
     437,   441,   442,   443,   447,   448,   451,   451,   451,   463,
     464,   464,   464,   475,   475,   475,   511,   512,   513,   514,
     518,   518,   538,   539,   542,   546,   550,   551,   553,   554,
     561,   562,   571,   580,   554,   582,   583,   583,   583,   590,
     591,   591,   594,   595,   596,   597,   601,   602,   603,   604,
     605,   606,   607,   608,   611,   636,   639,   643,   647,   651,
     655,   659
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "MAIN", "MACRO", "TYPEDEF",
  "SEMICOLON", "GLOBAL", "COMMA", "AMP", "VOID", "CHAR", "BOOL_DATATYPE",
  "DATATYPE", "ID", "BOOL", "DIGITS", "NEGATIVENUMBER", "ADD", "SUB",
  "MUL", "DIV", "MOD", "LT", "GT", "ASG", "FOR", "WHILE", "DO", "IF",
  "ELSE", "THEN", "BREAK", "CONTINUE", "RETURN", "GOTO", "ASSIGN", "CLB",
  "CRB", "RLB", "RRB", "SLB", "SRB", "AND", "OR", "EQ", "NEQ", "LTEQ",
  "GTEQ", "$accept", "prog", "$@1", "$@2", "$@3", "var_decl", "exps", "@4",
  "comma_exps", "empty", "stmt_list", "stmt", "assignment", "@5",
  "assignment_prime", "expressions", "expr_rel", "op", "expr_binary",
  "op_bin", "op_rel", "cond_loop", "if", "$@6", "$@7", "else", "$@8",
  "$@9", "while", "$@10", "$@11", "bin_op_for", "fn_call", "@12",
  "fn_call_args", "bool_prod", "fn_call_args_prime", "fn_def", "@13",
  "$@14", "@15", "$@16", "$@17", "func_args", "@18", "$@19",
  "func_args_prime", "@20", "datatype", "relop", "id_or_digits", "comma",
  "semi_colon", "rlb", "rrb", "clb", "crb", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF -78

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-78)))

#define YYTABLE_NINF -71

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      55,   -78,   -78,   -78,   -78,     6,    21,    -5,   -78,   -78,
     -78,   -24,   -24,   -78,   -20,   -78,   -78,   -12,    -6,   -78,
     -78,   -20,    55,     8,   -78,    28,   -78,   -24,   -24,    40,
     -78,   -78,    52,   -78,   -78,   -78,   -78,    45,   -12,   -78,
     -24,    12,    12,   -78,   -78,    22,   -78,     8,   -78,   -78,
       8,    59,    31,   -78,   -78,    35,   -78,    39,   -20,   -78,
      16,   -20,    43,   -78,   -78,   -78,    70,   -78,   -78,    70,
     -78,   -78,   -20,    70,    70,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,    16,   -12,   -20,   -78,   -78,    53,    90,
      16,    60,    17,   -78,   -78,   -78,    45,    56,    -6,   -78,
     -78,    31,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
      16,   -20,   -12,    57,   -78,   -78,   -78,    86,    16,   -78,
      80,   -78,   -78,     8,   -78,   -78,   -78,   -78,   -20,    22,
     -78,     8,   -78,    22,   -78,    55,   -78,    22,   -78,    65,
     -12,   -78,   -78,     8,   -78,    22,   -78
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      58,    72,    73,    74,    75,     0,     0,     0,     1,     2,
      59,     0,     0,    88,     0,    60,    89,     0,    66,    90,
       3,     0,     0,    12,    61,     0,    50,     0,     0,     0,
      14,     4,     0,    16,    34,    35,    17,     0,     0,    67,
       0,     0,     0,    18,    15,     0,    87,    12,     7,     6,
      12,    69,    52,    84,    32,    85,    33,     0,     0,    26,
       0,     0,     0,    91,     5,    13,    11,    62,    68,     0,
      55,    85,     0,    56,    56,    82,    83,    76,    78,    81,
      77,    79,    80,     0,     0,     0,    23,    24,     0,    26,
       0,     0,     0,    86,     8,     9,     0,     0,    66,    51,
      54,    52,    53,    25,    43,    27,    46,    47,    48,    49,
       0,     0,     0,    84,    19,    22,    21,    29,     0,    10,
       0,    71,    57,    12,    28,    29,    30,    36,     0,     0,
      44,    12,    63,     0,    37,    58,    45,     0,    64,    39,
       0,    38,    40,    12,    41,     0,    42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,   -78,   -78,   -78,   -78,   -78,     3,   -78,   -78,   -78,
     -42,   -78,   -78,   -78,   -78,   -78,   -51,    19,   -77,    -3,
      61,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,    23,   -78,    13,   -78,    30,   -22,   -78,   -78,
     -78,   -78,   -78,    18,   -78,   -78,   -78,   -78,     0,   -78,
     -48,   -29,   -78,   -10,    -7,   -35,   -39
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,    11,    23,    45,    30,    49,    66,    94,    95,
      31,    32,    44,    62,   114,    85,    56,    57,    87,    88,
      58,    33,    34,   131,   137,   141,   143,   145,    35,   123,
     133,   110,    36,    40,    72,    73,   100,     6,    12,    18,
      38,    97,   135,    21,    22,    51,    68,    69,    37,    83,
      59,   101,    47,    60,   126,    20,    64
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    14,    15,    50,    74,    65,     8,    17,    67,    86,
      10,     1,    89,   111,    24,   115,    13,    41,    42,     2,
       3,    16,    25,    26,     4,     9,    19,    53,    54,    55,
      52,    53,   113,    71,    71,   -65,    27,    96,    28,    86,
      98,   128,    89,    39,   117,    29,    53,    70,    71,   104,
      90,    84,    13,    74,    91,    43,    13,    13,     1,    46,
      48,    63,   125,    75,    76,    99,     2,     3,   -70,    92,
     125,     4,   106,   107,   108,   109,   -31,   127,   105,    93,
      90,   130,   118,    77,    78,    79,    80,    81,    82,   134,
     132,   120,   112,   -20,   136,   129,   140,   -50,   139,   119,
     118,   144,   103,    61,   102,   142,   146,   124,   118,   -29,
     -29,   -29,   -29,   138,   122,   116,   121,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7
};

static const yytype_int16 yycheck[] =
{
       0,    11,    12,    38,    52,    47,     0,    14,    50,    60,
      15,     3,    60,    90,    21,    92,    40,    27,    28,    11,
      12,    41,    22,    15,    16,     4,    38,    15,    16,    17,
      40,    15,    15,    17,    17,    41,    28,    66,    30,    90,
      69,   118,    90,    15,    92,    37,    15,    16,    17,    84,
      60,    58,    40,   101,    61,    15,    40,    40,     3,     7,
      15,    39,   110,    24,    25,    72,    11,    12,     9,    26,
     118,    16,    19,    20,    21,    22,    41,   112,    85,     9,
      90,   123,    92,    44,    45,    46,    47,    48,    49,   131,
     129,    35,    32,     7,   133,    15,    31,    40,   137,    96,
     110,   143,    83,    42,    74,   140,   145,   110,   118,    19,
      20,    21,    22,   135,   101,    92,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   135
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    11,    12,    16,    51,    87,    98,     0,     4,
      15,    52,    88,    40,   103,   103,    41,   104,    89,    38,
     105,    93,    94,    53,   104,    98,    15,    28,    30,    37,
      55,    60,    61,    71,    72,    78,    82,    98,    90,    15,
      83,   103,   103,    15,    62,    54,     7,   102,    15,    56,
     105,    95,   103,    15,    16,    17,    66,    67,    70,   100,
     103,    70,    63,    39,   106,    60,    57,    60,    96,    97,
      16,    17,    84,    85,   100,    24,    25,    44,    45,    46,
      47,    48,    49,    99,   104,    65,    66,    68,    69,   100,
     103,   104,    26,     9,    58,    59,   101,    91,   101,   104,
      86,   101,    86,    67,   105,   104,    19,    20,    21,    22,
      81,    68,    32,    15,    64,    68,    82,   100,   103,    56,
      35,    93,    84,    79,    69,   100,   104,   105,    68,    15,
      60,    73,   106,    80,    60,    92,   106,    74,    87,   106,
      31,    75,   105,    76,    60,    77,   106
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    52,    53,    54,    51,    55,    57,    56,    58,
      58,    59,    60,    60,    61,    61,    61,    61,    63,    62,
      64,    64,    64,    65,    65,    66,    67,    67,    68,    69,
      69,    70,    70,    70,    71,    71,    73,    74,    72,    75,
      76,    77,    75,    79,    80,    78,    81,    81,    81,    81,
      83,    82,    84,    84,    84,    85,    86,    86,    87,    88,
      89,    90,    91,    92,    87,    93,    94,    95,    93,    96,
      97,    96,    98,    98,    98,    98,    99,    99,    99,    99,
      99,    99,    99,    99,   100,   100,   101,   102,   103,   104,
     105,   106
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     0,     0,    10,     2,     0,     3,     1,
       2,     0,     0,     3,     1,     2,     1,     1,     0,     4,
       1,     1,     1,     1,     1,     3,     1,     3,     3,     1,
       3,     1,     1,     1,     1,     1,     0,     0,    11,     0,
       0,     0,     6,     0,     0,     9,     1,     1,     1,     1,
       0,     5,     0,     2,     2,     1,     0,     2,     0,     0,
       0,     0,     0,     0,    16,     0,     0,     0,     5,     0,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 274 "asg4test.y" /* yacc.c:1646  */
    { sattr* temp = new sattr;
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
    					(yyvsp[0]).node = temp;
    			}
#line 1616 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 291 "asg4test.y" /* yacc.c:1646  */
    {glob_level++;}
#line 1622 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 291 "asg4test.y" /* yacc.c:1646  */
    {
														vector<varEntry>::iterator itr;
														for(itr=active_func->variable.begin(); itr!=active_func->variable.end();itr++)
														{
															cout<<"Variable "<<(*itr).name<<endl;
															if((*itr).level == glob_level)
															{itr=active_func->variable.erase(itr);itr--;}
														}
												glob_level--;}
#line 1636 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 300 "asg4test.y" /* yacc.c:1646  */
    {printf("----------------\n\n");symbolTable();}
#line 1642 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 304 "asg4test.y" /* yacc.c:1646  */
    {fflush(stdout);patchtype((yyvsp[-1]).node->type, varName);varName.clear();}
#line 1648 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 308 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;
		(yyvsp[0]).node = new sattr;
		(yyvsp[0]).node->name = strdup(yytext);
		varName.push_back((yyvsp[0]).node->name);}
#line 1657 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 312 "asg4test.y" /* yacc.c:1646  */
    {cout<<(yyvsp[-1]).node->name<<endl;fflush(stdout);
					(yyval).node->var_types = append_list((yyvsp[-1]).node->var_types, (yyvsp[-2]).node->name);
					vector<string>::iterator itr;
					for(itr=(yyval).node->var_types.begin();itr!=(yyval).node->var_types.end();itr++)
						cout<<(*itr)<<" Value"<<endl;
				}
#line 1668 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 322 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name = "tests1";}
#line 1674 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 323 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;
    											(yyval).node->var_types = (yyvsp[0]).node->var_types;
    											(yyval).node->name = "tests1";
												vector<string>::iterator itr;
    										for(itr=(yyval).node->var_types.begin();itr!=(yyval).node->var_types.end();itr++)
										cout<<(*itr)<<" CommaValue"<<endl;}
#line 1685 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 342 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyvsp[0]).node = new sattr;
            	(yyvsp[0]).node->name = strdup(yytext);
            	if(search_var((yyvsp[0]).node->name, active_func, NULL)==0)
            		printf("Variable not declared!\n");}
#line 1694 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 346 "asg4test.y" /* yacc.c:1646  */
    { (yyvsp[-1]).node = new sattr;
            								if((yyvsp[-3]).node->type != "errortype" && (yyvsp[-1]).node->type != "errortype"){
            									if(!coercible((yyvsp[-3]).node->type, (yyvsp[-1]).node->type)){
            										yyerror("type mismatch of operands in assignment");
            									}

            							}}
#line 1706 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 354 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = (yyvsp[0]).node->type;}
#line 1712 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 355 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = (yyvsp[0]).node->type;}
#line 1718 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 356 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = (yyvsp[0]).node->type;}
#line 1724 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 359 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = (yyvsp[0]).node->type;}
#line 1730 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 360 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = (yyvsp[0]).node->type;}
#line 1736 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 363 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = "bool";
													cout<<"Type1: "<<(yyvsp[-2]).node->type<<" Type2: "<<(yyvsp[0]).node->type<<endl;
													if(compatibleRelOp((yyvsp[-2]).node->type,(yyvsp[0]).node->type)){
														if((yyvsp[-1]).node->name == "AND"){
															(yyval).node->val = (yyvsp[-2]).node->val && (yyvsp[0]).node->val;
														}
													if((yyvsp[-1]).node->name == "OR"){
															(yyval).node->val = (yyvsp[-2]).node->val || (yyvsp[0]).node->val;
														}
													if((yyvsp[-1]).node->name == "NEQ"){
															(yyval).node->val = ((yyvsp[-2]).node->val != (yyvsp[0]).node->val);
														}
													if((yyvsp[-1]).node->name == "LTEQ"){
															(yyval).node->val = (yyvsp[-2]).node->val <= (yyvsp[0]).node->val;
														}
													if((yyvsp[-1]).node->name == "GTEQ"){
															(yyval).node->val = (yyvsp[-2]).node->val >= (yyvsp[0]).node->val;
														}
													if((yyvsp[-1]).node->name == "LT"){
															(yyval).node->val = (yyvsp[-2]).node->val < (yyvsp[0]).node->val;
														}
													if((yyvsp[-1]).node->name == "GT"){
															(yyval).node->val = (yyvsp[-2]).node->val > (yyvsp[0]).node->val;
														}
													if((yyvsp[-1]).node->name == "EQ"){
															(yyval).node->val = ((yyvsp[-2]).node->val == (yyvsp[0]).node->val);
														}
													}
													else
														{cout<<(yyvsp[-2]).node->type<<" "<<(yyvsp[0]).node->type<<"Relative expression types mismatch!"<<endl;
														(yyval).node->type = "errortype";}
													}
#line 1773 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 397 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->val = (yyvsp[0]).node->val;
												(yyval).node->type = (yyvsp[0]).node->type;}
#line 1780 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 399 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->val = (yyvsp[-1]).node->val;
												(yyval).node->type = (yyvsp[-1]).node->type;}
#line 1787 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 403 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = compareTypes((yyvsp[-2]).node->type,(yyvsp[0]).node->type);	
 										cout<<"Type1: "<<(yyvsp[-2]).node->type<<" Type2: "<<(yyvsp[0]).node->type<<endl;
 										if (compatibleBinOp((yyvsp[-2]).node->type,(yyvsp[0]).node->type)){
	 										if((yyvsp[-1]).node->name == "ADD"){
	 											(yyval).node->val = (yyvsp[-2]).node->val + (yyvsp[0]).node->val;
	 										}
	 										if((yyvsp[-1]).node->name == "SUB"){
	 											(yyval).node->val = (yyvsp[-2]).node->val - (yyvsp[0]).node->val;
	 										}
	 										if((yyvsp[-1]).node->name == "MUL"){
	 											(yyval).node->val = (yyvsp[-2]).node->val * (yyvsp[0]).node->val;
	 										}
	 										if((yyvsp[-1]).node->name == "DIV"){
	 											(yyval).node->val = (yyvsp[-2]).node->val / (yyvsp[0]).node->val;
	 										}
	 									}
	 									else
	 									{cout<<(yyvsp[-2]).node->type<<" "<<(yyvsp[0]).node->type<<"Binary expression types mismatch!"<<endl;
														(yyval).node->type = "errortype";}
 										}
#line 1812 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 435 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->val = (yyvsp[0]).node->val;
												(yyval).node->type = (yyvsp[0]).node->type;}
#line 1819 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 437 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->val = (yyvsp[-1]).node->val;
												(yyval).node->type = (yyvsp[-1]).node->type;}
#line 1826 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 441 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = "bool";}
#line 1832 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 442 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = "bool";}
#line 1838 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 443 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = (yyvsp[0]).node->type;}
#line 1844 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 447 "asg4test.y" /* yacc.c:1646  */
    {cout<<"Finished IF"<<endl;fflush(stdout);}
#line 1850 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 451 "asg4test.y" /* yacc.c:1646  */
    {glob_level++;}
#line 1856 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 451 "asg4test.y" /* yacc.c:1646  */
    {
														vector<varEntry>::iterator itr;
														for(itr=active_func->variable.begin(); itr!=active_func->variable.end();itr++)
														{
															cout<<"Variable "<<(*itr).name<<endl;
															if((*itr).level == glob_level)
															{itr=active_func->variable.erase(itr);itr--;}
														}
												glob_level--;}
#line 1870 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 460 "asg4test.y" /* yacc.c:1646  */
    {cout<<"Finished IF"<<endl;fflush(stdout);}
#line 1876 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 464 "asg4test.y" /* yacc.c:1646  */
    {glob_level++;}
#line 1882 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 464 "asg4test.y" /* yacc.c:1646  */
    {
														vector<varEntry>::iterator itr;
														for(itr=active_func->variable.begin(); itr!=active_func->variable.end();itr++)
														{
															cout<<"Variable "<<(*itr).name<<endl;
															if((*itr).level == glob_level)
															{itr=active_func->variable.erase(itr);itr--;}
														}
												glob_level--;}
#line 1896 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 475 "asg4test.y" /* yacc.c:1646  */
    {glob_level++;}
#line 1902 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 475 "asg4test.y" /* yacc.c:1646  */
    {
														vector<varEntry>::iterator itr;
														for(itr=active_func->variable.begin(); itr!=active_func->variable.end();itr++)
														{
															cout<<"Variable "<<(*itr).name<<endl;
															if((*itr).level == glob_level)
															{itr=active_func->variable.erase(itr);itr--;}
														}
												glob_level--;}
#line 1916 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 511 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name = "ADD";}
#line 1922 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 512 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name = "SUB";}
#line 1928 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 513 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name = "MUL";}
#line 1934 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 514 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name = "DIV";}
#line 1940 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 518 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node->name = strdup(yytext); (yyvsp[0]).node->name = strdup(yytext); 
			entry* funcPtr;
			if(searchFunction(yytext, &funcPtr)==0)
			{
				yyerror("Function not declared.\n");
				(yyval).node->type = "errortype";
			}
			if(searchFunction(yytext, &funcPtr)==1){
				call_func = funcPtr;
				(yyval).node->type = (*funcPtr).resultType;
			}

			}
#line 1958 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 530 "asg4test.y" /* yacc.c:1646  */
    { if(call_func->parameter.size() != (yyvsp[-2]).node->pno){
								yyerror("mismatch in number of parameters in declaration and call\n");
							} 
							(yyval).node->type = "errortype";
						}
#line 1968 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 539 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node->pno = 1 + (yyvsp[0]).node->pno;
    														update_param(call_func,to_string((yyvsp[-1]).node->val),(yyval).node->pno);
    														}
#line 1976 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 542 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node->pno = 1 + (yyvsp[0]).node->pno;
    														update_param(call_func,to_string((yyvsp[-1]).node->val),(yyval).node->pno);
    														}
#line 1984 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 546 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node->name = strdup(yytext);
															if((yyval).node->name == "true" || (yyval).node->name == "TRUE") (yyval).node->val = 1; else (yyval).node->val = 0; 
															(yyval).node->type = "bool";}
#line 1992 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 551 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node->pno = (yyvsp[0]).node->pno;}
#line 1998 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 553 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;}
#line 2004 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 554 "asg4test.y" /* yacc.c:1646  */
    {(yyvsp[0]).node = new sattr;(yyvsp[0]).node->name=strdup(yytext);
    	entry* funcPtr;
    	if(searchFunction((yyvsp[0]).node->name,&funcPtr)==1){
    		yyerror("Function Name already exists.\n");
    		(yyval).node->type = "errortype";
    	}
    }
#line 2016 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 561 "asg4test.y" /* yacc.c:1646  */
    {glob_level = 1;}
#line 2022 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 562 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;entry* funcPtr;
		if(searchFunction((yyvsp[-5]).node->name,&funcPtr)==0){
			(yyval).node->type = (yyvsp[-6]).node->type; 
			(yyval).node->param_types = (yyvsp[-3]).node->param_types;		
			enter_func((yyvsp[-5]).node->name,(yyvsp[-6]).node->type,&funcPtr);
			(*funcPtr).parameter=(yyvsp[-3]).node->param_types;
		}
		active_func = funcPtr; glob_level=2;
		}
#line 2036 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 571 "asg4test.y" /* yacc.c:1646  */
    {
														vector<varEntry>::iterator itr;
														for(itr=active_func->variable.begin(); itr!=active_func->variable.end();itr++)
														{
															cout<<"Variable "<<(*itr).name<<endl;
															if((*itr).level == glob_level)
															{itr=active_func->variable.erase(itr);itr--;}
														}
												glob_level--;}
#line 2050 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 580 "asg4test.y" /* yacc.c:1646  */
    {searchFunction("main", &active_func);glob_level=0;}
#line 2056 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 582 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;}
#line 2062 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 583 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;}
#line 2068 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 583 "asg4test.y" /* yacc.c:1646  */
    {(yyvsp[-1]).node = new sattr;}
#line 2074 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 583 "asg4test.y" /* yacc.c:1646  */
    { varEntry temp((yyvsp[-3]).node->name, "simple", "parameter", 1, (yyvsp[-4]).node->type);
    								(yyval).node->param_types = (yyvsp[-2]).node->param_types;
    								(yyval).node->param_types.push_back(temp);}
#line 2082 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 590 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;}
#line 2088 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 591 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;}
#line 2094 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 591 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node->param_types = (yyvsp[-1]).node->param_types;}
#line 2100 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 594 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = "int";}
#line 2106 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 595 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = "void";}
#line 2112 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 596 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = "char";}
#line 2118 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 597 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->type = "bool";}
#line 2124 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 601 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name="AND";}
#line 2130 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 602 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name="NEQ";}
#line 2136 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 603 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name="OR";}
#line 2142 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 604 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name="LTEQ";}
#line 2148 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 605 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name="GTEQ";}
#line 2154 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 606 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name="EQ";}
#line 2160 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 607 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name="LT";}
#line 2166 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 608 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name="GT";}
#line 2172 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 611 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->name = strdup(yytext);
														vector<varEntry>::reverse_iterator itr;
														int found = 0;
														for(itr=active_func->variable.rbegin(); itr!=active_func->variable.rend(); itr++)
														{
															if((*itr).level <= glob_level && (*itr).name == (yyval).node->name)
															{
																(yyval).node->type = (*itr).ele;
																found = 1;
																break;
															}
														}
														if(!found)
														{
															for(itr=active_func->parameter.rbegin(); itr!=active_func->parameter.rend(); itr++)
															{	
																if((*itr).level <= glob_level && (*itr).name == (yyval).node->name)
																{
																	(yyval).node->type = (*itr).ele;
																	break;
																}
															}
														}
														if(!found){cout<<(yyval).node->name<<"---Element not declared"<<endl;}
														}
#line 2202 "asg4test.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 636 "asg4test.y" /* yacc.c:1646  */
    {(yyval).node = new sattr;(yyval).node->val = atoi(yytext);(yyval).node->type="int";}
#line 2208 "asg4test.tab.c" /* yacc.c:1646  */
    break;


#line 2212 "asg4test.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 670 "asg4test.y" /* yacc.c:1906  */


void yyerror(char *msg) {
    fprintf(stderr, "%s\n", msg);
    
}

int main(){
    yydebug = 1;
    yyparse();
    return 0 ;
}
