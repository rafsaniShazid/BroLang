/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "bro.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);
extern int yylineno;
extern char *yytext;

FILE *out;
FILE *main_out;
FILE *func_out;
FILE *icg;
#define MAX_SYMBOLS 100
#define MAX_FUNCTIONS 100
#define MAX_PARAMS 20
int temp_count = 1;
int loop_depth = 0;

typedef struct ExprNode ExprNode;
typedef struct ArgList ArgList;
ExprNode* make_expr(const char *text, int type);
ArgList* make_arglist_empty(void);
ArgList* make_arglist_single(const char *text, int type);
ArgList* merge_arglists(ArgList *left, ArgList *right);
void dump_stream(FILE *src, FILE *dst);

char function_names[MAX_FUNCTIONS][50];
int function_return_types[MAX_FUNCTIONS];
int function_param_counts[MAX_FUNCTIONS];
int function_param_types[MAX_FUNCTIONS][MAX_PARAMS];
int function_count = 0;

int function_scope_base = 0;
int current_function_return_type = 1;

enum {
    TYPE_INT = 1,
    TYPE_LONG_LONG,
    TYPE_FLOAT,
    TYPE_STRING
};

char* new_temp() {
    char *temp = malloc(10);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

char symbol_table[MAX_SYMBOLS][50];
int symbol_types[MAX_SYMBOLS];
int symbol_count = 0;

int lookup_index(char *var) {
    for(int i = 0; i < symbol_count; i++) {
        if(strcmp(symbol_table[i], var) == 0)
            return i;
    }
    return -1;
}

int lookup(char *var) {
    return lookup_index(var) != -1;
}

int can_assign_numeric(int target, int source);

const char* cpp_type_name(int type) {
    if (type == TYPE_INT) return "int";
    if (type == TYPE_LONG_LONG) return "long long";
    if (type == TYPE_FLOAT) return "float";
    if (type == TYPE_STRING) return "string";
    return "int";
}

int find_function(char *name) {
    for (int i = 0; i < function_count; i++) {
        if (strcmp(function_names[i], name) == 0) return i;
    }
    return -1;
}

void insert_function(char *name, int return_type, int param_count, int param_types[]) {
    strcpy(function_names[function_count], name);
    function_return_types[function_count] = return_type;
    function_param_counts[function_count] = param_count;
    for (int i = 0; i < param_count; i++) {
        function_param_types[function_count][i] = param_types[i];
    }
    function_count++;
}

int can_pass_argument(int expected, int actual) {
    if (expected == TYPE_STRING || actual == TYPE_STRING) {
        return expected == actual;
    }
    return can_assign_numeric(expected, actual);
}

int is_numeric_type(int type) {
    return type == TYPE_INT || type == TYPE_LONG_LONG || type == TYPE_FLOAT;
}

const char* type_name(int type) {
    if (type == TYPE_INT) return "bro";
    if (type == TYPE_LONG_LONG) return "bigbro";
    if (type == TYPE_FLOAT) return "lowkey";
    if (type == TYPE_STRING) return "textbro";
    return "unknown";
}

int promote_numeric_type(int a, int b) {
    return (a > b) ? a : b;
}

int can_assign_numeric(int target, int source) {
    if (!is_numeric_type(target) || !is_numeric_type(source)) return 0;
    if (target == TYPE_FLOAT) return 1;
    if (target == TYPE_LONG_LONG) return source == TYPE_INT || source == TYPE_LONG_LONG;
    if (target == TYPE_INT) return source == TYPE_INT;
    return 0;
}

int literal_numeric_type(const char *literal) {
    return strchr(literal, '.') ? TYPE_FLOAT : TYPE_INT;
}

int get_type(char *var) {
    int idx = lookup_index(var);
    if (idx == -1) return 0;
    return symbol_types[idx];
}

void insert(char *var, int type) {
    strcpy(symbol_table[symbol_count], var);
    symbol_types[symbol_count] = type;
    symbol_count++;
}

int is_identifier_like(const char *tok) {
    if (!tok || !tok[0]) return 0;
    return ((tok[0] >= 'a' && tok[0] <= 'z') ||
            (tok[0] >= 'A' && tok[0] <= 'Z') ||
            tok[0] == '_');
}

int is_statement_starter(const char *tok) {
    if (!tok || !tok[0]) return 0;
    return strcmp(tok, "bro") == 0 ||
           strcmp(tok, "bigbro") == 0 ||
           strcmp(tok, "lowkey") == 0 ||
           strcmp(tok, "textbro") == 0 ||
           strcmp(tok, "saybro") == 0 ||
           strcmp(tok, "askbro") == 0 ||
           strcmp(tok, "ifbro") == 0 ||
           strcmp(tok, "loopbro") == 0 ||
           strcmp(tok, "rip") == 0 ||
           strcmp(tok, "yeet") == 0 ||
           strcmp(tok, "elsebro") == 0 ||
           is_identifier_like(tok);
}

#line 235 "bro.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "bro.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_LONG_LONG = 4,                  /* LONG_LONG  */
  YYSYMBOL_FLOAT = 5,                      /* FLOAT  */
  YYSYMBOL_STR = 6,                        /* STR  */
  YYSYMBOL_COUT = 7,                       /* COUT  */
  YYSYMBOL_CIN = 8,                        /* CIN  */
  YYSYMBOL_IF = 9,                         /* IF  */
  YYSYMBOL_ELSE = 10,                      /* ELSE  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_RETURN = 12,                    /* RETURN  */
  YYSYMBOL_BREAK = 13,                     /* BREAK  */
  YYSYMBOL_INC = 14,                       /* INC  */
  YYSYMBOL_DEC = 15,                       /* DEC  */
  YYSYMBOL_EQ = 16,                        /* EQ  */
  YYSYMBOL_IDENTIFIER = 17,                /* IDENTIFIER  */
  YYSYMBOL_NUMBER = 18,                    /* NUMBER  */
  YYSYMBOL_STRING = 19,                    /* STRING  */
  YYSYMBOL_20_ = 20,                       /* '+'  */
  YYSYMBOL_21_ = 21,                       /* '-'  */
  YYSYMBOL_22_ = 22,                       /* '*'  */
  YYSYMBOL_23_ = 23,                       /* '/'  */
  YYSYMBOL_24_ = 24,                       /* '%'  */
  YYSYMBOL_25_ = 25,                       /* ';'  */
  YYSYMBOL_26_ = 26,                       /* '='  */
  YYSYMBOL_27_ = 27,                       /* '('  */
  YYSYMBOL_28_ = 28,                       /* ')'  */
  YYSYMBOL_29_ = 29,                       /* '{'  */
  YYSYMBOL_30_ = 30,                       /* '}'  */
  YYSYMBOL_31_ = 31,                       /* ','  */
  YYSYMBOL_32_ = 32,                       /* '>'  */
  YYSYMBOL_33_ = 33,                       /* '<'  */
  YYSYMBOL_YYACCEPT = 34,                  /* $accept  */
  YYSYMBOL_program = 35,                   /* program  */
  YYSYMBOL_items = 36,                     /* items  */
  YYSYMBOL_item = 37,                      /* item  */
  YYSYMBOL_38_1 = 38,                      /* $@1  */
  YYSYMBOL_39_2 = 39,                      /* $@2  */
  YYSYMBOL_statement_no_decl = 40,         /* statement_no_decl  */
  YYSYMBOL_type_spec = 41,                 /* type_spec  */
  YYSYMBOL_param_list_opt = 42,            /* param_list_opt  */
  YYSYMBOL_param_list = 43,                /* param_list  */
  YYSYMBOL_param_decl = 44,                /* param_decl  */
  YYSYMBOL_statements = 45,                /* statements  */
  YYSYMBOL_statement = 46,                 /* statement  */
  YYSYMBOL_function_call_statement = 47,   /* function_call_statement  */
  YYSYMBOL_break_statement = 48,           /* break_statement  */
  YYSYMBOL_return_statement = 49,          /* return_statement  */
  YYSYMBOL_input_statement = 50,           /* input_statement  */
  YYSYMBOL_declaration = 51,               /* declaration  */
  YYSYMBOL_declaration_init = 52,          /* declaration_init  */
  YYSYMBOL_string_assignment = 53,         /* string_assignment  */
  YYSYMBOL_increment_statement = 54,       /* increment_statement  */
  YYSYMBOL_decrement_statement = 55,       /* decrement_statement  */
  YYSYMBOL_assignment = 56,                /* assignment  */
  YYSYMBOL_if_head = 57,                   /* if_head  */
  YYSYMBOL_if_statement = 58,              /* if_statement  */
  YYSYMBOL_59_3 = 59,                      /* $@3  */
  YYSYMBOL_loop_statement = 60,            /* loop_statement  */
  YYSYMBOL_61_4 = 61,                      /* $@4  */
  YYSYMBOL_62_5 = 62,                      /* $@5  */
  YYSYMBOL_condition = 63,                 /* condition  */
  YYSYMBOL_print_statement = 64,           /* print_statement  */
  YYSYMBOL_expression = 65,                /* expression  */
  YYSYMBOL_arg_list_opt = 66,              /* arg_list_opt  */
  YYSYMBOL_arg_list = 67                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  34
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  159

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   274


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    24,     2,     2,
      27,    28,    22,    20,    31,    21,     2,    23,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
      33,    26,    32,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   199,   199,   202,   204,   208,   213,   227,   239,   247,
     238,   262,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   280,   281,   282,   283,   288,   291,   298,
     302,   309,   319,   320,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   340,   366,   377,
     382,   390,   401,   406,   411,   416,   424,   435,   446,   457,
     466,   480,   494,   508,   524,   531,   536,   535,   547,   551,
     546,   562,   568,   574,   583,   591,   598,   603,   635,   648,
     658,   668,   678,   688,   701,   704,   711,   715
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "LONG_LONG",
  "FLOAT", "STR", "COUT", "CIN", "IF", "ELSE", "WHILE", "RETURN", "BREAK",
  "INC", "DEC", "EQ", "IDENTIFIER", "NUMBER", "STRING", "'+'", "'-'",
  "'*'", "'/'", "'%'", "';'", "'='", "'('", "')'", "'{'", "'}'", "','",
  "'>'", "'<'", "$accept", "program", "items", "item", "$@1", "$@2",
  "statement_no_decl", "type_spec", "param_list_opt", "param_list",
  "param_decl", "statements", "statement", "function_call_statement",
  "break_statement", "return_statement", "input_statement", "declaration",
  "declaration_init", "string_assignment", "increment_statement",
  "decrement_statement", "assignment", "if_head", "if_statement", "$@3",
  "loop_statement", "$@4", "$@5", "condition", "print_statement",
  "expression", "arg_list_opt", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-113)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -113,    19,   122,  -113,  -113,  -113,  -113,  -113,    -2,    -6,
       3,     7,   -16,  -113,    11,  -113,  -113,    10,    15,    17,
      18,    39,    57,    72,    91,    93,     6,  -113,  -113,    95,
    -113,  -113,  -113,   -16,   -16,    50,  -113,    52,  -113,  -113,
      51,   -16,    61,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,   137,  -113,   119,     0,   123,   -16,   -16,   -16,   -16,
     -16,   -16,  -113,    52,    52,   124,    81,  -113,    84,  -113,
     104,   136,   142,   143,     1,  -113,   138,   139,   140,   141,
     144,   145,   146,   147,   148,   149,  -113,  -113,   150,  -113,
     -16,   -16,   -16,  -113,   133,   114,   114,  -113,  -113,  -113,
    -113,   -16,   151,    30,   152,   153,   154,   155,   156,   157,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,    52,    52,    52,   158,  -113,    52,  -113,  -113,
     160,   134,   159,  -113,   -16,   -16,   -16,   164,  -113,  -113,
    -113,  -113,   152,    52,    52,    52,  -113,   162,   137,   163,
    -113,   137,    54,   137,    87,  -113,   102,  -113,  -113
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,    23,    24,    25,    26,     0,     0,
       0,     0,    49,    48,     0,     4,    11,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,     0,
      74,    75,    51,     0,     0,    78,    76,    50,    61,    62,
       0,    84,     0,    14,    18,    19,    17,    13,    15,    16,
      12,     0,    22,     0,     0,     0,    84,     0,     0,     0,
       0,     0,    60,    63,    86,     0,    85,     5,     0,     8,
       0,     0,     0,     0,     0,    32,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    44,    45,     0,    64,
       0,     0,     0,    68,     0,    79,    80,    81,    82,    83,
      47,     0,     0,     0,    27,    52,    53,    54,    55,    65,
      33,    38,    42,    43,    41,    34,    35,    37,    39,    40,
      36,    46,    73,    71,    72,     0,    77,    87,     7,     6,
       0,     0,    28,    29,     0,     0,     0,     0,    66,    69,
      31,     9,     0,    56,    57,    58,    59,     0,     0,     0,
      30,     0,     0,     0,     0,    70,     0,    67,    10
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -113,  -113,  -113,  -113,  -113,  -113,  -113,   166,  -113,  -113,
      36,  -112,   -71,   182,   183,   184,   186,  -113,  -113,   187,
     191,   192,   193,  -113,   194,  -113,   195,  -113,  -113,   165,
     196,   -12,   161,  -113
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    15,   104,   149,    16,   130,   131,   132,
     133,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    26,    86,   147,    87,   125,   148,    53,
      88,    54,    65,    66
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      37,    35,    36,   110,    70,    71,    72,    73,     8,     9,
      10,    32,    11,    12,    13,    30,    90,    31,    14,     3,
      57,    58,    59,    60,    61,    38,    39,    42,    63,    64,
      33,   109,    91,    92,    34,    51,   152,    40,    41,   154,
      43,   156,    44,    45,    64,    95,    96,    97,    98,    99,
      57,    58,    59,    60,    61,   129,   103,    70,    71,    72,
      73,     8,     9,    10,    46,    11,    12,    13,    35,    36,
      62,    14,    57,    58,    59,    60,    61,    56,   122,   123,
     124,   110,    47,   110,   155,   110,    67,    68,    69,   127,
      70,    71,    72,    73,     8,     9,    10,    48,    11,    12,
      13,    35,    36,   102,    14,    70,    71,    72,    73,     8,
       9,    10,   101,    11,    12,    13,    49,   157,    50,    14,
      52,   105,   143,   144,   145,     4,     5,     6,     7,     8,
       9,    10,   158,    11,    12,    13,    59,    60,    61,    14,
      70,    71,    72,    73,     8,     9,    10,    89,    11,    12,
      13,    93,   100,   106,    14,     4,     5,     6,     7,   107,
     108,   126,   141,   111,   112,   113,   114,   138,    17,   115,
     116,   117,   118,   119,   120,   121,   128,   140,   150,   134,
     135,   136,   137,   146,    18,    19,    20,   139,    21,    22,
     142,   151,   153,    23,    24,    25,    27,    28,    29,    55,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94
};

static const yytype_int16 yycheck[] =
{
      12,    17,    18,    74,     3,     4,     5,     6,     7,     8,
       9,    17,    11,    12,    13,    17,    16,    19,    17,     0,
      20,    21,    22,    23,    24,    14,    15,    17,    40,    41,
      27,    30,    32,    33,    27,    29,   148,    26,    27,   151,
      25,   153,    25,    25,    56,    57,    58,    59,    60,    61,
      20,    21,    22,    23,    24,    25,    68,     3,     4,     5,
       6,     7,     8,     9,    25,    11,    12,    13,    17,    18,
      19,    17,    20,    21,    22,    23,    24,    27,    90,    91,
      92,   152,    25,   154,    30,   156,    25,    26,    27,   101,
       3,     4,     5,     6,     7,     8,     9,    25,    11,    12,
      13,    17,    18,    19,    17,     3,     4,     5,     6,     7,
       8,     9,    31,    11,    12,    13,    25,    30,    25,    17,
      25,    17,   134,   135,   136,     3,     4,     5,     6,     7,
       8,     9,    30,    11,    12,    13,    22,    23,    24,    17,
       3,     4,     5,     6,     7,     8,     9,    28,    11,    12,
      13,    28,    28,    17,    17,     3,     4,     5,     6,    17,
      17,    28,    28,    25,    25,    25,    25,    10,     2,    25,
      25,    25,    25,    25,    25,    25,    25,    17,   142,    26,
      26,    26,    26,    19,     2,     2,     2,    29,     2,     2,
      31,    29,    29,     2,     2,     2,     2,     2,     2,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    35,    36,     0,     3,     4,     5,     6,     7,     8,
       9,    11,    12,    13,    17,    37,    40,    41,    47,    48,
      49,    50,    53,    54,    55,    56,    57,    58,    60,    64,
      17,    19,    17,    27,    27,    17,    18,    65,    14,    15,
      26,    27,    17,    25,    25,    25,    25,    25,    25,    25,
      25,    29,    25,    63,    65,    63,    27,    20,    21,    22,
      23,    24,    19,    65,    65,    66,    67,    25,    26,    27,
       3,     4,     5,     6,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    58,    60,    64,    28,
      16,    32,    33,    28,    66,    65,    65,    65,    65,    65,
      28,    31,    19,    65,    38,    17,    17,    17,    17,    30,
      46,    25,    25,    25,    25,    25,    25,    25,    25,    25,
      25,    25,    65,    65,    65,    61,    28,    65,    25,    25,
      41,    42,    43,    44,    26,    26,    26,    26,    10,    29,
      17,    28,    31,    65,    65,    65,    19,    59,    62,    39,
      44,    29,    45,    29,    45,    30,    45,    30,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    34,    35,    36,    36,    37,    37,    37,    38,    39,
      37,    37,    40,    40,    40,    40,    40,    40,    40,    40,
      40,    40,    40,    41,    41,    41,    41,    42,    42,    43,
      43,    44,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    47,    48,    49,
      49,    50,    51,    51,    51,    51,    52,    52,    52,    52,
      53,    54,    55,    56,    57,    58,    59,    58,    61,    62,
      60,    63,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    66,    67,    67
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     5,     5,     0,     0,
      10,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     2,     1,     1,     1,     1,     0,     1,     1,
       3,     2,     1,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     1,     2,     4,     1,     1,
       2,     2,     2,     2,     2,     2,     4,     4,     4,     4,
       3,     2,     2,     3,     4,     4,     0,     9,     0,     0,
       9,     3,     3,     3,     2,     2,     1,     4,     1,     3,
       3,     3,     3,     3,     0,     1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 5: /* item: type_spec IDENTIFIER ';'  */
#line 209 "bro.y"
    {
        insert((yyvsp[-1].str), (yyvsp[-2].ival));
        fprintf(out, "    %s %s;\n", cpp_type_name((yyvsp[-2].ival)), (yyvsp[-1].str));
    }
#line 1407 "bro.tab.c"
    break;

  case 6: /* item: type_spec IDENTIFIER '=' expression ';'  */
#line 214 "bro.y"
    {
        insert((yyvsp[-3].str), (yyvsp[-4].ival));
        if ((yyvsp[-4].ival) == TYPE_STRING) {
            printf("Type error: use string literal initializer for textbro variable %s\n", (yyvsp[-3].str));
            fprintf(out, "    string %s;\n", (yyvsp[-3].str));
        } else if(!can_assign_numeric((yyvsp[-4].ival), (yyvsp[-1].expr)->type)) {
            printf("Type error: cannot assign %s expression to %s variable %s\n", type_name((yyvsp[-1].expr)->type), type_name((yyvsp[-4].ival)), (yyvsp[-3].str));
            fprintf(out, "    %s %s;\n", cpp_type_name((yyvsp[-4].ival)), (yyvsp[-3].str));
        } else {
            fprintf(icg, "%s = %s\n", (yyvsp[-3].str), (yyvsp[-1].expr)->text);
            fprintf(out, "    %s %s = %s;\n", cpp_type_name((yyvsp[-4].ival)), (yyvsp[-3].str), (yyvsp[-1].expr)->text);
        }
    }
#line 1425 "bro.tab.c"
    break;

  case 7: /* item: type_spec IDENTIFIER '=' STRING ';'  */
#line 228 "bro.y"
    {
        insert((yyvsp[-3].str), (yyvsp[-4].ival));
        if ((yyvsp[-4].ival) != TYPE_STRING) {
            printf("Type error: cannot assign string literal to %s variable %s\n", type_name((yyvsp[-4].ival)), (yyvsp[-3].str));
            fprintf(out, "    %s %s;\n", cpp_type_name((yyvsp[-4].ival)), (yyvsp[-3].str));
        } else {
            fprintf(icg, "%s = %s\n", (yyvsp[-3].str), (yyvsp[-1].str));
            fprintf(out, "    string %s = %s;\n", (yyvsp[-3].str), (yyvsp[-1].str));
        }
    }
#line 1440 "bro.tab.c"
    break;

  case 8: /* $@1: %empty  */
#line 239 "bro.y"
    {
        if (find_function((yyvsp[-1].str)) != -1) {
            printf("Error: function %s already declared\n", (yyvsp[-1].str));
        }
        function_scope_base = symbol_count;
        symbol_count = 0;
    }
#line 1452 "bro.tab.c"
    break;

  case 9: /* $@2: %empty  */
#line 247 "bro.y"
    {
        if (find_function((yyvsp[-4].str)) == -1) {
            insert_function((yyvsp[-4].str), (yyvsp[-5].ival), (yyvsp[-1].alist)->count, (yyvsp[-1].alist)->types);
        }
        current_function_return_type = (yyvsp[-5].ival);
        out = func_out;
        fprintf(out, "%s %s(%s) {\n", cpp_type_name((yyvsp[-5].ival)), (yyvsp[-4].str), (yyvsp[-1].alist)->text);
    }
#line 1465 "bro.tab.c"
    break;

  case 10: /* item: type_spec IDENTIFIER '(' $@1 param_list_opt ')' $@2 '{' statements '}'  */
#line 256 "bro.y"
    {
        fprintf(out, "}\n\n");
        symbol_count = function_scope_base;
        current_function_return_type = TYPE_INT;
        out = main_out;
    }
#line 1476 "bro.tab.c"
    break;

  case 23: /* type_spec: INT  */
#line 280 "bro.y"
        { (yyval.ival) = TYPE_INT; }
#line 1482 "bro.tab.c"
    break;

  case 24: /* type_spec: LONG_LONG  */
#line 281 "bro.y"
                { (yyval.ival) = TYPE_LONG_LONG; }
#line 1488 "bro.tab.c"
    break;

  case 25: /* type_spec: FLOAT  */
#line 282 "bro.y"
            { (yyval.ival) = TYPE_FLOAT; }
#line 1494 "bro.tab.c"
    break;

  case 26: /* type_spec: STR  */
#line 283 "bro.y"
          { (yyval.ival) = TYPE_STRING; }
#line 1500 "bro.tab.c"
    break;

  case 27: /* param_list_opt: %empty  */
#line 288 "bro.y"
    {
        (yyval.alist) = make_arglist_empty();
    }
#line 1508 "bro.tab.c"
    break;

  case 28: /* param_list_opt: param_list  */
#line 292 "bro.y"
    {
        (yyval.alist) = (yyvsp[0].alist);
    }
#line 1516 "bro.tab.c"
    break;

  case 29: /* param_list: param_decl  */
#line 299 "bro.y"
    {
        (yyval.alist) = (yyvsp[0].alist);
    }
#line 1524 "bro.tab.c"
    break;

  case 30: /* param_list: param_list ',' param_decl  */
#line 303 "bro.y"
    {
        (yyval.alist) = merge_arglists((yyvsp[-2].alist), (yyvsp[0].alist));
    }
#line 1532 "bro.tab.c"
    break;

  case 31: /* param_decl: type_spec IDENTIFIER  */
#line 310 "bro.y"
    {
        char buf[128];
        sprintf(buf, "%s %s", cpp_type_name((yyvsp[-1].ival)), (yyvsp[0].str));
        insert((yyvsp[0].str), (yyvsp[-1].ival));
        (yyval.alist) = make_arglist_single(buf, (yyvsp[-1].ival));
    }
#line 1543 "bro.tab.c"
    break;

  case 47: /* function_call_statement: IDENTIFIER '(' arg_list_opt ')'  */
#line 341 "bro.y"
    {
        int idx = find_function((yyvsp[-3].str));
        if (idx == -1) {
            printf("Error: function %s not declared\n", (yyvsp[-3].str));
        } else {
            if (function_param_counts[idx] != (yyvsp[-1].alist)->count) {
                printf("Type error: function %s expects %d arguments but got %d\n", (yyvsp[-3].str), function_param_counts[idx], (yyvsp[-1].alist)->count);
            } else {
                int ok = 1;
                for (int i = 0; i < (yyvsp[-1].alist)->count; i++) {
                    if (!can_pass_argument(function_param_types[idx][i], (yyvsp[-1].alist)->types[i])) {
                        ok = 0;
                        printf("Type error: argument %d of function %s has incompatible type\n", i + 1, (yyvsp[-3].str));
                        break;
                    }
                }
                if (ok) {
                    fprintf(out, "    %s(%s);\n", (yyvsp[-3].str), (yyvsp[-1].alist)->text);
                }
            }
        }
    }
#line 1570 "bro.tab.c"
    break;

  case 48: /* break_statement: BREAK  */
#line 367 "bro.y"
    {
        if(loop_depth <= 0) {
            printf("Error: rip used outside loop\n");
        } else {
            fprintf(out, "    break;\n");
        }
    }
#line 1582 "bro.tab.c"
    break;

  case 49: /* return_statement: RETURN  */
#line 378 "bro.y"
    {
        fprintf(icg, "return 0\n");
        fprintf(out, "    return 0;\n");
    }
#line 1591 "bro.tab.c"
    break;

  case 50: /* return_statement: RETURN expression  */
#line 383 "bro.y"
    {
        fprintf(icg, "return %s\n", (yyvsp[0].expr)->text);
        fprintf(out, "    return %s;\n", (yyvsp[0].expr)->text);
    }
#line 1600 "bro.tab.c"
    break;

  case 51: /* input_statement: CIN IDENTIFIER  */
#line 391 "bro.y"
    {
        if(!lookup((yyvsp[0].str))) {
            printf("Error: variable %s not declared\n", (yyvsp[0].str));
        } else {
            fprintf(out, "    cin >> %s;\n", (yyvsp[0].str));
        }
    }
#line 1612 "bro.tab.c"
    break;

  case 52: /* declaration: INT IDENTIFIER  */
#line 402 "bro.y"
    {
        insert((yyvsp[0].str), TYPE_INT);
        fprintf(out, "    int %s;\n", (yyvsp[0].str));
    }
#line 1621 "bro.tab.c"
    break;

  case 53: /* declaration: LONG_LONG IDENTIFIER  */
#line 407 "bro.y"
    {
        insert((yyvsp[0].str), TYPE_LONG_LONG);
        fprintf(out, "    long long %s;\n", (yyvsp[0].str));
    }
#line 1630 "bro.tab.c"
    break;

  case 54: /* declaration: FLOAT IDENTIFIER  */
#line 412 "bro.y"
    {
        insert((yyvsp[0].str), TYPE_FLOAT);
        fprintf(out, "    float %s;\n", (yyvsp[0].str));
    }
#line 1639 "bro.tab.c"
    break;

  case 55: /* declaration: STR IDENTIFIER  */
#line 417 "bro.y"
    {
        insert((yyvsp[0].str), TYPE_STRING);
        fprintf(out, "    string %s;\n", (yyvsp[0].str));
    }
#line 1648 "bro.tab.c"
    break;

  case 56: /* declaration_init: INT IDENTIFIER '=' expression  */
#line 425 "bro.y"
    {
        insert((yyvsp[-2].str), TYPE_INT);
        if(!can_assign_numeric(TYPE_INT, (yyvsp[0].expr)->type)) {
            printf("Type error: cannot assign %s expression to bro variable %s\n", type_name((yyvsp[0].expr)->type), (yyvsp[-2].str));
            fprintf(out, "    int %s;\n", (yyvsp[-2].str));
        } else {
            fprintf(icg, "%s = %s\n", (yyvsp[-2].str), (yyvsp[0].expr)->text);
            fprintf(out, "    int %s = %s;\n", (yyvsp[-2].str), (yyvsp[0].expr)->text);
        }
    }
#line 1663 "bro.tab.c"
    break;

  case 57: /* declaration_init: LONG_LONG IDENTIFIER '=' expression  */
#line 436 "bro.y"
    {
        insert((yyvsp[-2].str), TYPE_LONG_LONG);
        if(!can_assign_numeric(TYPE_LONG_LONG, (yyvsp[0].expr)->type)) {
            printf("Type error: cannot assign %s expression to bigbro variable %s\n", type_name((yyvsp[0].expr)->type), (yyvsp[-2].str));
            fprintf(out, "    long long %s;\n", (yyvsp[-2].str));
        } else {
            fprintf(icg, "%s = %s\n", (yyvsp[-2].str), (yyvsp[0].expr)->text);
            fprintf(out, "    long long %s = %s;\n", (yyvsp[-2].str), (yyvsp[0].expr)->text);
        }
    }
#line 1678 "bro.tab.c"
    break;

  case 58: /* declaration_init: FLOAT IDENTIFIER '=' expression  */
#line 447 "bro.y"
    {
        insert((yyvsp[-2].str), TYPE_FLOAT);
        if(!can_assign_numeric(TYPE_FLOAT, (yyvsp[0].expr)->type)) {
            printf("Type error: cannot assign %s expression to lowkey variable %s\n", type_name((yyvsp[0].expr)->type), (yyvsp[-2].str));
            fprintf(out, "    float %s;\n", (yyvsp[-2].str));
        } else {
            fprintf(icg, "%s = %s\n", (yyvsp[-2].str), (yyvsp[0].expr)->text);
            fprintf(out, "    float %s = %s;\n", (yyvsp[-2].str), (yyvsp[0].expr)->text);
        }
    }
#line 1693 "bro.tab.c"
    break;

  case 59: /* declaration_init: STR IDENTIFIER '=' STRING  */
#line 458 "bro.y"
    {
        insert((yyvsp[-2].str), TYPE_STRING);
        fprintf(icg, "%s = %s\n", (yyvsp[-2].str), (yyvsp[0].str));
        fprintf(out, "    string %s = %s;\n", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1703 "bro.tab.c"
    break;

  case 60: /* string_assignment: IDENTIFIER '=' STRING  */
#line 467 "bro.y"
    {
        if(!lookup((yyvsp[-2].str))) {
            printf("Error: variable %s not declared\n", (yyvsp[-2].str));
        } else if(get_type((yyvsp[-2].str)) != TYPE_STRING) {
            printf("Error: variable %s is not string type\n", (yyvsp[-2].str));
        } else {
            fprintf(icg, "%s = %s\n", (yyvsp[-2].str), (yyvsp[0].str));
            fprintf(out, "    %s = %s;\n", (yyvsp[-2].str), (yyvsp[0].str));
        }
    }
#line 1718 "bro.tab.c"
    break;

  case 61: /* increment_statement: IDENTIFIER INC  */
#line 481 "bro.y"
    {
        if(!lookup((yyvsp[-1].str))) {
            printf("Error: variable %s not declared\n", (yyvsp[-1].str));
        } else if(get_type((yyvsp[-1].str)) == TYPE_STRING) {
            printf("Error: cannot increment string variable %s\n", (yyvsp[-1].str));
        } else {
            fprintf(icg, "%s = %s + 1\n", (yyvsp[-1].str), (yyvsp[-1].str));
            fprintf(out, "    %s++;\n", (yyvsp[-1].str));
        }
    }
#line 1733 "bro.tab.c"
    break;

  case 62: /* decrement_statement: IDENTIFIER DEC  */
#line 495 "bro.y"
    {
        if(!lookup((yyvsp[-1].str))) {
            printf("Error: variable %s not declared\n", (yyvsp[-1].str));
        } else if(get_type((yyvsp[-1].str)) == TYPE_STRING) {
            printf("Error: cannot decrement string variable %s\n", (yyvsp[-1].str));
        } else {
            fprintf(icg, "%s = %s - 1\n", (yyvsp[-1].str), (yyvsp[-1].str));
            fprintf(out, "    %s--;\n", (yyvsp[-1].str));
        }
    }
#line 1748 "bro.tab.c"
    break;

  case 63: /* assignment: IDENTIFIER '=' expression  */
#line 509 "bro.y"
    {
        if(!lookup((yyvsp[-2].str))) {
            printf("Error: variable %s not declared\n", (yyvsp[-2].str));
        } else if(get_type((yyvsp[-2].str)) == TYPE_STRING) {
            printf("Type error: cannot assign numeric expression to textbro variable %s\n", (yyvsp[-2].str));
        } else if(!can_assign_numeric(get_type((yyvsp[-2].str)), (yyvsp[0].expr)->type)) {
            printf("Type error: cannot assign %s expression to %s variable %s\n", type_name((yyvsp[0].expr)->type), type_name(get_type((yyvsp[-2].str))), (yyvsp[-2].str));
        } else {
            fprintf(icg, "%s = %s\n", (yyvsp[-2].str), (yyvsp[0].expr)->text);
            fprintf(out, "    %s = %s;\n", (yyvsp[-2].str), (yyvsp[0].expr)->text);
        }
    }
#line 1765 "bro.tab.c"
    break;

  case 64: /* if_head: IF '(' condition ')'  */
#line 525 "bro.y"
    {
        fprintf(out,"    if(%s) {\n",(yyvsp[-1].str));
    }
#line 1773 "bro.tab.c"
    break;

  case 65: /* if_statement: if_head '{' statements '}'  */
#line 532 "bro.y"
    {
        fprintf(out,"    }\n");
    }
#line 1781 "bro.tab.c"
    break;

  case 66: /* $@3: %empty  */
#line 536 "bro.y"
    {
        fprintf(out,"    } else {\n");
    }
#line 1789 "bro.tab.c"
    break;

  case 67: /* if_statement: if_head '{' statements '}' ELSE $@3 '{' statements '}'  */
#line 540 "bro.y"
    {
        fprintf(out,"    }\n");
    }
#line 1797 "bro.tab.c"
    break;

  case 68: /* $@4: %empty  */
#line 547 "bro.y"
    {
        fprintf(out,"    while(%s) {\n",(yyvsp[-1].str));
    }
#line 1805 "bro.tab.c"
    break;

  case 69: /* $@5: %empty  */
#line 551 "bro.y"
    {
        loop_depth++;
    }
#line 1813 "bro.tab.c"
    break;

  case 70: /* loop_statement: WHILE '(' condition ')' $@4 '{' $@5 statements '}'  */
#line 555 "bro.y"
    {
        loop_depth--;
        fprintf(out,"    }\n");
    }
#line 1822 "bro.tab.c"
    break;

  case 71: /* condition: expression '>' expression  */
#line 563 "bro.y"
      {
          char *temp = malloc(100);
                    sprintf(temp, "%s > %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
          (yyval.str) = temp;
      }
#line 1832 "bro.tab.c"
    break;

  case 72: /* condition: expression '<' expression  */
#line 569 "bro.y"
      {
          char *temp = malloc(100);
                    sprintf(temp, "%s < %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
          (yyval.str) = temp;
      }
#line 1842 "bro.tab.c"
    break;

  case 73: /* condition: expression EQ expression  */
#line 575 "bro.y"
      {
          char *temp = malloc(100);
                    sprintf(temp, "%s == %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
          (yyval.str) = temp;
      }
#line 1852 "bro.tab.c"
    break;

  case 74: /* print_statement: COUT IDENTIFIER  */
#line 584 "bro.y"
    {
        if(!lookup((yyvsp[0].str))) {
            printf("Error: variable %s not declared\n", (yyvsp[0].str));
        } else {
            fprintf(out, "    cout << %s << endl;\n", (yyvsp[0].str));
        }
    }
#line 1864 "bro.tab.c"
    break;

  case 75: /* print_statement: COUT STRING  */
#line 592 "bro.y"
    {
        fprintf(out, "    cout << %s << endl;\n", (yyvsp[0].str));
    }
#line 1872 "bro.tab.c"
    break;

  case 76: /* expression: NUMBER  */
#line 599 "bro.y"
        {
            (yyval.expr) = make_expr((yyvsp[0].str), literal_numeric_type((yyvsp[0].str)));
        }
#line 1880 "bro.tab.c"
    break;

  case 77: /* expression: IDENTIFIER '(' arg_list_opt ')'  */
#line 604 "bro.y"
        {
            int idx = find_function((yyvsp[-3].str));
            if (idx == -1) {
                printf("Error: function %s not declared\n", (yyvsp[-3].str));
                (yyval.expr) = make_expr("0", TYPE_INT);
            } else if (function_return_types[idx] == TYPE_STRING) {
                printf("Type error: textbro function %s cannot be used in numeric expression\n", (yyvsp[-3].str));
                (yyval.expr) = make_expr("0", TYPE_INT);
            } else if (function_param_counts[idx] != (yyvsp[-1].alist)->count) {
                printf("Type error: function %s expects %d arguments but got %d\n", (yyvsp[-3].str), function_param_counts[idx], (yyvsp[-1].alist)->count);
                (yyval.expr) = make_expr("0", TYPE_INT);
            } else {
                int ok = 1;
                for (int i = 0; i < (yyvsp[-1].alist)->count; i++) {
                    if (!can_pass_argument(function_param_types[idx][i], (yyvsp[-1].alist)->types[i])) {
                        ok = 0;
                        printf("Type error: argument %d of function %s has incompatible type\n", i + 1, (yyvsp[-3].str));
                        break;
                    }
                }

                if (!ok) {
                    (yyval.expr) = make_expr("0", TYPE_INT);
                } else {
                    char call[256];
                    sprintf(call, "%s(%s)", (yyvsp[-3].str), (yyvsp[-1].alist)->text);
                    (yyval.expr) = make_expr(call, function_return_types[idx]);
                }
            }
        }
#line 1915 "bro.tab.c"
    break;

  case 78: /* expression: IDENTIFIER  */
#line 636 "bro.y"
        {
            if(!lookup((yyvsp[0].str))) {
                printf("Error: variable %s not declared\n", (yyvsp[0].str));
                (yyval.expr) = make_expr("0", TYPE_INT);
            } else if(get_type((yyvsp[0].str)) == TYPE_STRING) {
                printf("Error: string variable %s cannot be used in numeric expression\n", (yyvsp[0].str));
                (yyval.expr) = make_expr("0", TYPE_INT);
            } else {
                (yyval.expr) = make_expr((yyvsp[0].str), get_type((yyvsp[0].str)));
            }
        }
#line 1931 "bro.tab.c"
    break;

  case 79: /* expression: expression '+' expression  */
#line 649 "bro.y"
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s + %s\n", temp, (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);

    char *expr = malloc(100);
    sprintf(expr, "%s + %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
    (yyval.expr) = make_expr(expr, promote_numeric_type((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type));
}
#line 1944 "bro.tab.c"
    break;

  case 80: /* expression: expression '-' expression  */
#line 659 "bro.y"
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s - %s\n", temp, (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);

    char *expr = malloc(100);
    sprintf(expr, "%s - %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
    (yyval.expr) = make_expr(expr, promote_numeric_type((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type));
}
#line 1957 "bro.tab.c"
    break;

  case 81: /* expression: expression '*' expression  */
#line 669 "bro.y"
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s * %s\n", temp, (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);

    char *expr = malloc(100);
    sprintf(expr, "%s * %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
    (yyval.expr) = make_expr(expr, promote_numeric_type((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type));
}
#line 1970 "bro.tab.c"
    break;

  case 82: /* expression: expression '/' expression  */
#line 679 "bro.y"
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s / %s\n", temp, (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);

    char *expr = malloc(100);
    sprintf(expr, "%s / %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
    (yyval.expr) = make_expr(expr, promote_numeric_type((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type));
}
#line 1983 "bro.tab.c"
    break;

  case 83: /* expression: expression '%' expression  */
#line 689 "bro.y"
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s %% %s\n", temp, (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);

    char *expr = malloc(100);
    sprintf(expr, "%s %% %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
    (yyval.expr) = make_expr(expr, promote_numeric_type((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type));
}
#line 1996 "bro.tab.c"
    break;

  case 84: /* arg_list_opt: %empty  */
#line 701 "bro.y"
    {
        (yyval.alist) = make_arglist_empty();
    }
#line 2004 "bro.tab.c"
    break;

  case 85: /* arg_list_opt: arg_list  */
#line 705 "bro.y"
    {
        (yyval.alist) = (yyvsp[0].alist);
    }
#line 2012 "bro.tab.c"
    break;

  case 86: /* arg_list: expression  */
#line 712 "bro.y"
    {
        (yyval.alist) = make_arglist_single((yyvsp[0].expr)->text, (yyvsp[0].expr)->type);
    }
#line 2020 "bro.tab.c"
    break;

  case 87: /* arg_list: arg_list ',' expression  */
#line 716 "bro.y"
    {
        ArgList *right = make_arglist_single((yyvsp[0].expr)->text, (yyvsp[0].expr)->type);
        (yyval.alist) = merge_arglists((yyvsp[-2].alist), right);
    }
#line 2029 "bro.tab.c"
    break;


#line 2033 "bro.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 721 "bro.y"


ExprNode* make_expr(const char *text, int type) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->text = strdup(text);
    node->type = type;
    return node;
}

ArgList* make_arglist_empty(void) {
    ArgList *list = malloc(sizeof(ArgList));
    list->text = strdup("");
    list->count = 0;
    return list;
}

ArgList* make_arglist_single(const char *text, int type) {
    ArgList *list = malloc(sizeof(ArgList));
    list->text = strdup(text);
    list->count = 1;
    list->types[0] = type;
    return list;
}

ArgList* merge_arglists(ArgList *left, ArgList *right) {
    ArgList *list = malloc(sizeof(ArgList));
    list->count = 0;

    for (int i = 0; i < left->count; i++) {
        list->types[list->count++] = left->types[i];
    }
    for (int i = 0; i < right->count; i++) {
        list->types[list->count++] = right->types[i];
    }

    int size = strlen(left->text) + strlen(right->text) + 3;
    list->text = malloc(size);
    if (left->count == 0) {
        sprintf(list->text, "%s", right->text);
    } else if (right->count == 0) {
        sprintf(list->text, "%s", left->text);
    } else {
        sprintf(list->text, "%s, %s", left->text, right->text);
    }
    return list;
}

void dump_stream(FILE *src, FILE *dst) {
    int ch;
    rewind(src);
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }
}

void yyerror(const char *s) {
    const char *tok = (yytext && yytext[0]) ? yytext : "EOF";
    if (strcmp(tok, "}") == 0 || strcmp(tok, "EOF") == 0 || is_statement_starter(tok)) {
        printf("Syntax error at line %d near '%s': possible missing ';' before this token\n", yylineno, tok);
    } else {
        printf("Syntax error at line %d near '%s'\n", yylineno, tok);
    }
}

int main() {
    FILE *final_out = fopen("output.cpp", "w");
    main_out = tmpfile();
    func_out = tmpfile();
    out = main_out;
    icg = fopen("intermediate.txt", "w");

    yyparse();

    fprintf(final_out, "#include <iostream>\n");
    fprintf(final_out, "#include <string>\n");
    fprintf(final_out, "using namespace std;\n\n");

    dump_stream(func_out, final_out);

    fprintf(final_out, "int main() {\n");
    dump_stream(main_out, final_out);
    fprintf(final_out, "}\n");

    fclose(final_out);
    fclose(main_out);
    fclose(func_out);
    fclose(icg);

    return 0;
}
