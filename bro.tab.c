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
FILE *icg;
#define MAX_SYMBOLS 100
int temp_count = 1;
int loop_depth = 0;

typedef struct ExprNode ExprNode;
ExprNode* make_expr(const char *text, int type);

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

#line 183 "bro.tab.c"

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
  YYSYMBOL_31_ = 31,                       /* '>'  */
  YYSYMBOL_32_ = 32,                       /* '<'  */
  YYSYMBOL_YYACCEPT = 33,                  /* $accept  */
  YYSYMBOL_program = 34,                   /* program  */
  YYSYMBOL_statements = 35,                /* statements  */
  YYSYMBOL_statement = 36,                 /* statement  */
  YYSYMBOL_break_statement = 37,           /* break_statement  */
  YYSYMBOL_return_statement = 38,          /* return_statement  */
  YYSYMBOL_input_statement = 39,           /* input_statement  */
  YYSYMBOL_declaration = 40,               /* declaration  */
  YYSYMBOL_declaration_init = 41,          /* declaration_init  */
  YYSYMBOL_string_assignment = 42,         /* string_assignment  */
  YYSYMBOL_increment_statement = 43,       /* increment_statement  */
  YYSYMBOL_decrement_statement = 44,       /* decrement_statement  */
  YYSYMBOL_assignment = 45,                /* assignment  */
  YYSYMBOL_if_head = 46,                   /* if_head  */
  YYSYMBOL_if_statement = 47,              /* if_statement  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_loop_statement = 49,            /* loop_statement  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_51_3 = 51,                      /* $@3  */
  YYSYMBOL_condition = 52,                 /* condition  */
  YYSYMBOL_print_statement = 53,           /* print_statement  */
  YYSYMBOL_expression = 54                 /* expression  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  43
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   130

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  33
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  51
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  99

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
      27,    28,    22,    20,     2,    21,     2,    23,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    25,
      32,    26,    31,     2,     2,     2,     2,     2,     2,     2,
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
       0,   137,   137,   141,   142,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   161,   172,   177,
     185,   196,   201,   206,   211,   219,   230,   241,   252,   261,
     275,   289,   303,   319,   326,   331,   330,   342,   346,   341,
     357,   363,   369,   378,   386,   393,   398,   411,   421,   431,
     441,   451
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
  "'*'", "'/'", "'%'", "';'", "'='", "'('", "')'", "'{'", "'}'", "'>'",
  "'<'", "$accept", "program", "statements", "statement",
  "break_statement", "return_statement", "input_statement", "declaration",
  "declaration_init", "string_assignment", "increment_statement",
  "decrement_statement", "assignment", "if_head", "if_statement", "$@1",
  "loop_statement", "$@2", "$@3", "condition", "print_statement",
  "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-54)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     113,    10,    18,    19,    31,    14,    46,    37,    38,   -15,
     -54,    24,    12,   113,   -54,    41,    42,    43,    44,    45,
      49,    50,    51,    52,    20,   -54,   -54,    53,    54,    55,
      65,    69,   -54,   -54,   -54,   -15,   -15,   -54,   -54,    22,
     -54,   -54,    -1,   -54,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,   -54,   -54,   113,   -54,   -15,   -15,   -15,    60,
      68,    83,    72,   -15,   -15,   -15,   -15,   -15,   -54,    22,
       2,    22,    22,    22,   -54,   -54,   -15,   -15,   -15,   -54,
      32,    32,   -54,   -54,   -54,    87,    22,    22,    22,    73,
     -54,   -54,    79,   113,   113,    17,    81,   -54,   -54
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,    18,
      17,     0,     0,     2,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    14,    15,     0,    21,    22,
      23,    24,    43,    44,    20,     0,     0,    46,    45,    19,
      30,    31,     0,     1,     4,    12,    13,    11,     5,     6,
       8,     9,    10,     7,     0,    16,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,    32,
       0,    25,    26,    27,    28,    33,     0,     0,     0,    37,
      47,    48,    49,    50,    51,    34,    42,    40,    41,     0,
      35,    38,     0,     0,     0,     0,     0,    39,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -54,   -54,   -53,   -13,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,    74,
     -54,    -5
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    92,    26,    89,    93,    60,
      27,    61
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,    70,    37,    38,    39,     1,     2,     3,     4,     5,
       6,     7,    43,     8,     9,    10,    37,    38,    68,    11,
       1,     2,     3,     4,     5,     6,     7,    28,     8,     9,
      10,    32,    85,    33,    11,    29,    30,    69,    40,    41,
      95,    96,    63,    64,    65,    66,    67,    97,    31,    54,
      42,    71,    72,    73,    65,    66,    67,    44,    80,    81,
      82,    83,    84,    34,    35,    36,    45,    46,    47,    48,
      49,    86,    87,    88,    50,    51,    52,    53,    55,    74,
      56,    57,    44,    44,     1,     2,     3,     4,     5,     6,
       7,    58,     8,     9,    10,    59,    75,    90,    11,    76,
      79,     0,    91,    63,    64,    65,    66,    67,    94,     0,
      62,    98,     0,     0,    77,    78,     1,     2,     3,     4,
       5,     6,     7,     0,     8,     9,    10,     0,     0,     0,
      11
};

static const yytype_int8 yycheck[] =
{
      13,    54,    17,    18,     9,     3,     4,     5,     6,     7,
       8,     9,     0,    11,    12,    13,    17,    18,    19,    17,
       3,     4,     5,     6,     7,     8,     9,    17,    11,    12,
      13,    17,    30,    19,    17,    17,    17,    42,    14,    15,
      93,    94,    20,    21,    22,    23,    24,    30,    17,    29,
      26,    56,    57,    58,    22,    23,    24,    70,    63,    64,
      65,    66,    67,    17,    27,    27,    25,    25,    25,    25,
      25,    76,    77,    78,    25,    25,    25,    25,    25,    19,
      26,    26,    95,    96,     3,     4,     5,     6,     7,     8,
       9,    26,    11,    12,    13,    26,    28,    10,    17,    16,
      28,    -1,    29,    20,    21,    22,    23,    24,    29,    -1,
      36,    30,    -1,    -1,    31,    32,     3,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    -1,    -1,    -1,
      17
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    11,    12,
      13,    17,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    49,    53,    17,    17,
      17,    17,    17,    19,    17,    27,    27,    17,    18,    54,
      14,    15,    26,     0,    36,    25,    25,    25,    25,    25,
      25,    25,    25,    25,    29,    25,    26,    26,    26,    26,
      52,    54,    52,    20,    21,    22,    23,    24,    19,    54,
      35,    54,    54,    54,    19,    28,    16,    31,    32,    28,
      54,    54,    54,    54,    54,    30,    54,    54,    54,    50,
      10,    29,    48,    51,    29,    35,    35,    30,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    33,    34,    35,    35,    36,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    36,    37,    38,    38,
      39,    40,    40,    40,    40,    41,    41,    41,    41,    42,
      43,    44,    45,    46,    47,    48,    47,    50,    51,    49,
      52,    52,    52,    53,    53,    54,    54,    54,    54,    54,
      54,    54
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     1,     1,     2,     1,     1,     2,
       2,     2,     2,     2,     2,     4,     4,     4,     4,     3,
       2,     2,     3,     4,     4,     0,     9,     0,     0,     9,
       3,     3,     3,     2,     2,     1,     1,     3,     3,     3,
       3,     3
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
  case 17: /* break_statement: BREAK  */
#line 162 "bro.y"
    {
        if(loop_depth <= 0) {
            printf("Error: rip used outside loop\n");
        } else {
            fprintf(out, "    break;\n");
        }
    }
#line 1298 "bro.tab.c"
    break;

  case 18: /* return_statement: RETURN  */
#line 173 "bro.y"
    {
        fprintf(icg, "return 0\n");
        fprintf(out, "    return 0;\n");
    }
#line 1307 "bro.tab.c"
    break;

  case 19: /* return_statement: RETURN expression  */
#line 178 "bro.y"
    {
        fprintf(icg, "return %s\n", (yyvsp[0].expr)->text);
        fprintf(out, "    return %s;\n", (yyvsp[0].expr)->text);
    }
#line 1316 "bro.tab.c"
    break;

  case 20: /* input_statement: CIN IDENTIFIER  */
#line 186 "bro.y"
    {
        if(!lookup((yyvsp[0].str))) {
            printf("Error: variable %s not declared\n", (yyvsp[0].str));
        } else {
            fprintf(out, "    cin >> %s;\n", (yyvsp[0].str));
        }
    }
#line 1328 "bro.tab.c"
    break;

  case 21: /* declaration: INT IDENTIFIER  */
#line 197 "bro.y"
    {
        insert((yyvsp[0].str), TYPE_INT);
        fprintf(out, "    int %s;\n", (yyvsp[0].str));
    }
#line 1337 "bro.tab.c"
    break;

  case 22: /* declaration: LONG_LONG IDENTIFIER  */
#line 202 "bro.y"
    {
        insert((yyvsp[0].str), TYPE_LONG_LONG);
        fprintf(out, "    long long %s;\n", (yyvsp[0].str));
    }
#line 1346 "bro.tab.c"
    break;

  case 23: /* declaration: FLOAT IDENTIFIER  */
#line 207 "bro.y"
    {
        insert((yyvsp[0].str), TYPE_FLOAT);
        fprintf(out, "    float %s;\n", (yyvsp[0].str));
    }
#line 1355 "bro.tab.c"
    break;

  case 24: /* declaration: STR IDENTIFIER  */
#line 212 "bro.y"
    {
        insert((yyvsp[0].str), TYPE_STRING);
        fprintf(out, "    string %s;\n", (yyvsp[0].str));
    }
#line 1364 "bro.tab.c"
    break;

  case 25: /* declaration_init: INT IDENTIFIER '=' expression  */
#line 220 "bro.y"
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
#line 1379 "bro.tab.c"
    break;

  case 26: /* declaration_init: LONG_LONG IDENTIFIER '=' expression  */
#line 231 "bro.y"
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
#line 1394 "bro.tab.c"
    break;

  case 27: /* declaration_init: FLOAT IDENTIFIER '=' expression  */
#line 242 "bro.y"
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
#line 1409 "bro.tab.c"
    break;

  case 28: /* declaration_init: STR IDENTIFIER '=' STRING  */
#line 253 "bro.y"
    {
        insert((yyvsp[-2].str), TYPE_STRING);
        fprintf(icg, "%s = %s\n", (yyvsp[-2].str), (yyvsp[0].str));
        fprintf(out, "    string %s = %s;\n", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1419 "bro.tab.c"
    break;

  case 29: /* string_assignment: IDENTIFIER '=' STRING  */
#line 262 "bro.y"
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
#line 1434 "bro.tab.c"
    break;

  case 30: /* increment_statement: IDENTIFIER INC  */
#line 276 "bro.y"
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
#line 1449 "bro.tab.c"
    break;

  case 31: /* decrement_statement: IDENTIFIER DEC  */
#line 290 "bro.y"
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
#line 1464 "bro.tab.c"
    break;

  case 32: /* assignment: IDENTIFIER '=' expression  */
#line 304 "bro.y"
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
#line 1481 "bro.tab.c"
    break;

  case 33: /* if_head: IF '(' condition ')'  */
#line 320 "bro.y"
    {
        fprintf(out,"    if(%s) {\n",(yyvsp[-1].str));
    }
#line 1489 "bro.tab.c"
    break;

  case 34: /* if_statement: if_head '{' statements '}'  */
#line 327 "bro.y"
    {
        fprintf(out,"    }\n");
    }
#line 1497 "bro.tab.c"
    break;

  case 35: /* $@1: %empty  */
#line 331 "bro.y"
    {
        fprintf(out,"    } else {\n");
    }
#line 1505 "bro.tab.c"
    break;

  case 36: /* if_statement: if_head '{' statements '}' ELSE $@1 '{' statements '}'  */
#line 335 "bro.y"
    {
        fprintf(out,"    }\n");
    }
#line 1513 "bro.tab.c"
    break;

  case 37: /* $@2: %empty  */
#line 342 "bro.y"
    {
        fprintf(out,"    while(%s) {\n",(yyvsp[-1].str));
    }
#line 1521 "bro.tab.c"
    break;

  case 38: /* $@3: %empty  */
#line 346 "bro.y"
    {
        loop_depth++;
    }
#line 1529 "bro.tab.c"
    break;

  case 39: /* loop_statement: WHILE '(' condition ')' $@2 '{' $@3 statements '}'  */
#line 350 "bro.y"
    {
        loop_depth--;
        fprintf(out,"    }\n");
    }
#line 1538 "bro.tab.c"
    break;

  case 40: /* condition: expression '>' expression  */
#line 358 "bro.y"
      {
          char *temp = malloc(100);
                    sprintf(temp, "%s > %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
          (yyval.str) = temp;
      }
#line 1548 "bro.tab.c"
    break;

  case 41: /* condition: expression '<' expression  */
#line 364 "bro.y"
      {
          char *temp = malloc(100);
                    sprintf(temp, "%s < %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
          (yyval.str) = temp;
      }
#line 1558 "bro.tab.c"
    break;

  case 42: /* condition: expression EQ expression  */
#line 370 "bro.y"
      {
          char *temp = malloc(100);
                    sprintf(temp, "%s == %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
          (yyval.str) = temp;
      }
#line 1568 "bro.tab.c"
    break;

  case 43: /* print_statement: COUT IDENTIFIER  */
#line 379 "bro.y"
    {
        if(!lookup((yyvsp[0].str))) {
            printf("Error: variable %s not declared\n", (yyvsp[0].str));
        } else {
            fprintf(out, "    cout << %s << endl;\n", (yyvsp[0].str));
        }
    }
#line 1580 "bro.tab.c"
    break;

  case 44: /* print_statement: COUT STRING  */
#line 387 "bro.y"
    {
        fprintf(out, "    cout << %s << endl;\n", (yyvsp[0].str));
    }
#line 1588 "bro.tab.c"
    break;

  case 45: /* expression: NUMBER  */
#line 394 "bro.y"
        {
            (yyval.expr) = make_expr((yyvsp[0].str), literal_numeric_type((yyvsp[0].str)));
        }
#line 1596 "bro.tab.c"
    break;

  case 46: /* expression: IDENTIFIER  */
#line 399 "bro.y"
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
#line 1612 "bro.tab.c"
    break;

  case 47: /* expression: expression '+' expression  */
#line 412 "bro.y"
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s + %s\n", temp, (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);

    char *expr = malloc(100);
    sprintf(expr, "%s + %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
    (yyval.expr) = make_expr(expr, promote_numeric_type((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type));
}
#line 1625 "bro.tab.c"
    break;

  case 48: /* expression: expression '-' expression  */
#line 422 "bro.y"
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s - %s\n", temp, (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);

    char *expr = malloc(100);
    sprintf(expr, "%s - %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
    (yyval.expr) = make_expr(expr, promote_numeric_type((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type));
}
#line 1638 "bro.tab.c"
    break;

  case 49: /* expression: expression '*' expression  */
#line 432 "bro.y"
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s * %s\n", temp, (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);

    char *expr = malloc(100);
    sprintf(expr, "%s * %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
    (yyval.expr) = make_expr(expr, promote_numeric_type((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type));
}
#line 1651 "bro.tab.c"
    break;

  case 50: /* expression: expression '/' expression  */
#line 442 "bro.y"
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s / %s\n", temp, (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);

    char *expr = malloc(100);
    sprintf(expr, "%s / %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
    (yyval.expr) = make_expr(expr, promote_numeric_type((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type));
}
#line 1664 "bro.tab.c"
    break;

  case 51: /* expression: expression '%' expression  */
#line 452 "bro.y"
{
    char *temp = new_temp();
    fprintf(icg, "%s = %s %% %s\n", temp, (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);

    char *expr = malloc(100);
    sprintf(expr, "%s %% %s", (yyvsp[-2].expr)->text, (yyvsp[0].expr)->text);
    (yyval.expr) = make_expr(expr, promote_numeric_type((yyvsp[-2].expr)->type, (yyvsp[0].expr)->type));
}
#line 1677 "bro.tab.c"
    break;


#line 1681 "bro.tab.c"

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

#line 461 "bro.y"


ExprNode* make_expr(const char *text, int type) {
    ExprNode *node = malloc(sizeof(ExprNode));
    node->text = strdup(text);
    node->type = type;
    return node;
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
    out = fopen("output.cpp", "w");
    icg = fopen("intermediate.txt", "w");

    fprintf(out, "#include <iostream>\n");
    fprintf(out, "#include <string>\n");
    fprintf(out, "using namespace std;\n\n");
    fprintf(out, "int main() {\n");

    yyparse();

    fprintf(out, "}\n");

    fclose(out);
    fclose(icg);

    return 0;
}
