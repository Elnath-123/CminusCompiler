// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "bison.tab.cxx" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "bison.tab.hxx"

// User implementation prologue.
#line 73 "bison.yxx" // lalr1.cc:412

	extern int yylex(yy::parser::semantic_type *yylval, yy::parser::location_type *yylloc);

#line 54 "bison.tab.cxx" // lalr1.cc:412
// Unqualified %code blocks.
#line 14 "bison.yxx" // lalr1.cc:413

	#include <iostream>
	#include <unistd.h>
	int yydebug=1;

#line 62 "bison.tab.cxx" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 148 "bison.tab.cxx" // lalr1.cc:479

  /// Build a parser object.
  parser::parser (Expression** root_yyarg, Statement** stmt_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      root (root_yyarg),
      stmt (stmt_yyarg)
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 78 "bison.yxx" // lalr1.cc:859
    {
								(yylhs.value.stmt_decl_list) = (yystack_[0].value.stmt_decl_list);
								Gen::genCode((yystack_[0].value.stmt_decl_list));
							}
#line 594 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 3:
#line 84 "bison.yxx" // lalr1.cc:859
    {
													  (yystack_[1].value.stmt_decl_list)->push_back((yystack_[0].value.stmt));
													  (yylhs.value.stmt_decl_list) = (yystack_[1].value.stmt_decl_list);
												}
#line 603 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 4:
#line 88 "bison.yxx" // lalr1.cc:859
    {
									(yylhs.value.stmt_decl_list) = new vector<Statement*>();
									(yylhs.value.stmt_decl_list)->push_back((yystack_[0].value.stmt));
									
								}
#line 613 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 5:
#line 95 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.stmt) = (yystack_[0].value.stmt);}
#line 619 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 6:
#line 96 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.stmt) = (yystack_[0].value.stmt);}
#line 625 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 7:
#line 99 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.stmt) = new Variable((yystack_[2].value.type), (yystack_[1].value.id), "local_id_var");}
#line 631 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 9:
#line 103 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.type) = new PrimitiveType("int");}
#line 637 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 10:
#line 104 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.type) = new PrimitiveType("float");}
#line 643 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 11:
#line 105 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.type) = new PrimitiveType("void");}
#line 649 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 12:
#line 108 "bison.yxx" // lalr1.cc:859
    {
																	(yylhs.value.stmt) = new Function((yystack_[5].value.type), (yystack_[4].value.id), (yystack_[2].value.variable_list), (yystack_[0].value.stmt), "Function");
																	/* As for code generation, we only need
																	   function name($2) and function body($6) */
																	Gen::genFunction((yylhs.value.stmt), (yystack_[4].value.id), (yystack_[0].value.stmt));
																}
#line 660 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 13:
#line 115 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.variable_list) = (yystack_[0].value.variable_list);}
#line 666 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 14:
#line 116 "bison.yxx" // lalr1.cc:859
    {
						/* Empty param list */
						(yylhs.value.variable_list) = new vector<Variable*>();
					}
#line 675 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 15:
#line 122 "bison.yxx" // lalr1.cc:859
    {
										(yystack_[2].value.variable_list)->push_back((yystack_[0].value.variable));
										(yylhs.value.variable_list) = (yystack_[2].value.variable_list);
									}
#line 684 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 16:
#line 126 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.variable_list)->push_back((yystack_[0].value.variable));}
#line 690 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 17:
#line 127 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.variable_list) = new vector<Variable*>();}
#line 696 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 18:
#line 130 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.variable) = new Variable((yystack_[1].value.type), (yystack_[0].value.id), "param_id_var");}
#line 702 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 20:
#line 134 "bison.yxx" // lalr1.cc:859
    {
										/* Need to pass ($2, $3)->code to $$->code (implemented in construct function) */
															  (yylhs.value.stmt) = new BlockStmt("block", (yystack_[2].value.stmt_decl_list), (yystack_[1].value.stmt_decl_list));
														}
#line 711 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 21:
#line 140 "bison.yxx" // lalr1.cc:859
    {
															 (yystack_[1].value.stmt_decl_list)->push_back((yystack_[0].value.stmt));
															 (yylhs.value.stmt_decl_list) = (yystack_[1].value.stmt_decl_list);		
														}
#line 720 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 22:
#line 144 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.stmt_decl_list) = new vector<Statement*>();}
#line 726 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 23:
#line 147 "bison.yxx" // lalr1.cc:859
    {
											 (yystack_[1].value.stmt_decl_list)->push_back((yystack_[0].value.stmt));
											 (yylhs.value.stmt_decl_list) = (yystack_[1].value.stmt_decl_list);
										}
#line 735 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 24:
#line 151 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.stmt_decl_list) = new vector<Statement*>();}
#line 741 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 25:
#line 154 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.stmt) = (yystack_[0].value.stmt);}
#line 747 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 26:
#line 155 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.stmt) = (yystack_[0].value.stmt);}
#line 753 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 27:
#line 156 "bison.yxx" // lalr1.cc:859
    {*stmt = (yystack_[0].value.stmt); (yylhs.value.stmt) = (yystack_[0].value.stmt);}
#line 759 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 30:
#line 161 "bison.yxx" // lalr1.cc:859
    {
						/* Need to pass $1->code to $$->code (implemented in construct function) */
											(yylhs.value.stmt) = new ExpStmt("exp", (yystack_[1].value.e));
											(yylhs.value.stmt)->code = (yystack_[1].value.e)->code;
										}
#line 769 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 31:
#line 166 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.stmt) = new EmptyStmt("empty");}
#line 775 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 32:
#line 170 "bison.yxx" // lalr1.cc:859
    {
												     (yylhs.value.stmt) = new IfStmt("if", (yystack_[2].value.e), (yystack_[0].value.stmt)); 
													 Gen::genIfStmt((yystack_[4].value.If), (yystack_[2].value.e), (yystack_[0].value.stmt));
													 (yylhs.value.stmt) = (yystack_[4].value.If);
												 }
#line 785 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 33:
#line 175 "bison.yxx" // lalr1.cc:859
    {
																    (yylhs.value.stmt) = new IfStmt("if", (yystack_[4].value.e), (yystack_[2].value.stmt), (yystack_[0].value.stmt));
																	Gen::genIfStmt((yystack_[6].value.If), (yystack_[4].value.e), (yystack_[2].value.stmt), (yystack_[0].value.stmt));
																	(yylhs.value.stmt) = (yystack_[6].value.If);
																}
#line 795 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 34:
#line 182 "bison.yxx" // lalr1.cc:859
    {
													 	(yylhs.value.stmt) = new WhileStmt("while", (yystack_[2].value.e), (yystack_[0].value.stmt));
													}
#line 803 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 35:
#line 187 "bison.yxx" // lalr1.cc:859
    {}
#line 809 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 36:
#line 188 "bison.yxx" // lalr1.cc:859
    {}
#line 815 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 37:
#line 191 "bison.yxx" // lalr1.cc:859
    {
										(yystack_[1].value.assign) = new Assign("=", (yystack_[2].value.id), (yystack_[0].value.e));
										Gen::genAssign((yystack_[1].value.assign), (yystack_[2].value.id), (yystack_[0].value.e));
										(yylhs.value.e) = (yystack_[1].value.assign); 
										*root = (yystack_[1].value.assign); 
									  }
#line 826 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 39:
#line 200 "bison.yxx" // lalr1.cc:859
    { Gen::genId((yylhs.value.id), (yystack_[0].value.id)); (yylhs.value.id) = (yystack_[0].value.id);}
#line 832 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 41:
#line 204 "bison.yxx" // lalr1.cc:859
    {
																		(yystack_[1].value.e)->left = (yystack_[2].value.e); 
																		(yystack_[1].value.e)->right = (yystack_[0].value.e); 
																		Gen::genRelop((yystack_[1].value.e), (yystack_[2].value.e), (yystack_[0].value.e), (yystack_[1].value.e)->type);
																		(yylhs.value.e) = (yystack_[1].value.e);
																	}
#line 843 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 43:
#line 213 "bison.yxx" // lalr1.cc:859
    { (yylhs.value.e) = new BinOp(">");}
#line 849 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 44:
#line 214 "bison.yxx" // lalr1.cc:859
    { (yylhs.value.e) = new BinOp("<");}
#line 855 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 45:
#line 215 "bison.yxx" // lalr1.cc:859
    { (yylhs.value.e) = new BinOp("<=");}
#line 861 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 46:
#line 216 "bison.yxx" // lalr1.cc:859
    { (yylhs.value.e) = new BinOp(">=");}
#line 867 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 47:
#line 217 "bison.yxx" // lalr1.cc:859
    { (yylhs.value.e) = new BinOp("==");}
#line 873 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 48:
#line 218 "bison.yxx" // lalr1.cc:859
    { (yylhs.value.e) = new BinOp("!=");}
#line 879 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 49:
#line 221 "bison.yxx" // lalr1.cc:859
    {
															(yystack_[1].value.e)->left = (yystack_[2].value.e); 
															(yystack_[1].value.e)->right = (yystack_[0].value.e); 
															Gen::genBinary((yystack_[1].value.e), (yystack_[2].value.e), (yystack_[0].value.e), (yystack_[1].value.e)->type);
															(yylhs.value.e) = (yystack_[1].value.e);
														}
#line 890 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 51:
#line 230 "bison.yxx" // lalr1.cc:859
    { (yylhs.value.e) = new BinOp("+");}
#line 896 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 52:
#line 231 "bison.yxx" // lalr1.cc:859
    { (yylhs.value.e) = new BinOp("_");}
#line 902 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 53:
#line 234 "bison.yxx" // lalr1.cc:859
    {
								(yystack_[1].value.e)->left = (yystack_[2].value.e);
								(yystack_[1].value.e)->right = (yystack_[0].value.e);
								Gen::genBinary((yystack_[1].value.e), (yystack_[2].value.e), (yystack_[0].value.e), (yystack_[1].value.e)->type);
								(yylhs.value.e) = (yystack_[1].value.e);
							}
#line 913 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 55:
#line 243 "bison.yxx" // lalr1.cc:859
    { (yylhs.value.e) = new BinOp("*");}
#line 919 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 56:
#line 244 "bison.yxx" // lalr1.cc:859
    { (yylhs.value.e) = new BinOp("/");}
#line 925 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 57:
#line 247 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.e) = (yystack_[1].value.e);}
#line 931 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 58:
#line 248 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.e) = (yystack_[0].value.id);}
#line 937 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 59:
#line 249 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.e) = (yystack_[0].value.e);}
#line 943 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 60:
#line 250 "bison.yxx" // lalr1.cc:859
    {Gen::genInt10((yylhs.value.e), (yystack_[0].value.int10)); (yylhs.value.e) = (yystack_[0].value.int10);}
#line 949 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 61:
#line 253 "bison.yxx" // lalr1.cc:859
    {
						   (yylhs.value.e) = new FunctionInvocation((yystack_[3].value.id), (yystack_[1].value.arg_list), "invoke");
						   Gen::genFunctionInvoke((yylhs.value.e), (yystack_[3].value.id), (yystack_[1].value.arg_list));
						}
#line 958 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 62:
#line 259 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.arg_list) = (yystack_[0].value.arg_list);}
#line 964 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 63:
#line 260 "bison.yxx" // lalr1.cc:859
    {(yylhs.value.arg_list) = new vector<Expression*>();}
#line 970 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 64:
#line 262 "bison.yxx" // lalr1.cc:859
    {
											(yystack_[2].value.arg_list)->push_back((yystack_[0].value.e));
										}
#line 978 "bison.tab.cxx" // lalr1.cc:859
    break;

  case 65:
#line 265 "bison.yxx" // lalr1.cc:859
    {
						    (yylhs.value.arg_list) = new vector<Expression*>();
							(yylhs.value.arg_list)->push_back((yystack_[0].value.e));
						}
#line 987 "bison.tab.cxx" // lalr1.cc:859
    break;


#line 991 "bison.tab.cxx" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -51;

  const signed char parser::yytable_ninf_ = -15;

  const signed char
  parser::yypact_[] =
  {
     -23,   -51,   -51,   -51,    15,   -23,   -51,   -51,     0,   -51,
     -51,   -51,    -1,    46,    42,   -51,    37,    20,    43,    34,
     -51,    50,    52,    41,   -23,    44,    57,   -51,   -51,   -51,
     -51,   -51,   -23,   -51,    40,    -9,    17,   -51,    62,    -8,
     -51,    63,    18,   -51,     3,   -51,   -51,   -51,   -51,   -51,
     -51,    49,    67,   -51,    29,    -3,   -51,   -51,    -8,    65,
      -8,   -51,    53,    -8,    -8,   -51,    -8,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   -51,    -8,    -8,   -51,   -51,    -8,
      66,   -51,    68,   -51,   -51,    69,    55,    70,   -51,   -51,
      35,    -3,   -51,    16,    16,   -51,    -8,   -51,    64,   -51,
     -51,    16,   -51
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     9,    11,    10,     0,     2,     4,     5,     0,     6,
       1,     3,     0,    17,     0,     7,    11,     0,     0,    13,
      16,     0,    18,     0,     0,     0,     0,    22,    12,    15,
       8,    19,    24,    21,     0,     0,     0,    60,     0,     0,
      20,     0,     0,    31,    39,    26,    23,    25,    27,    28,
      29,     0,    58,    38,    42,    50,    54,    59,     0,     0,
       0,    35,     0,    63,     0,    30,     0,    51,    52,    44,
      43,    47,    46,    45,    48,     0,     0,    55,    56,     0,
       0,    57,     0,    36,    65,     0,    62,     0,    37,    58,
      41,    49,    53,     0,     0,    61,     0,    40,    32,    34,
      64,     0,    33
  };

  const signed char
  parser::yypgoto_[] =
  {
     -51,   -51,   -51,    86,    60,    21,   -51,   -51,   -51,    71,
      73,   -51,   -51,   -50,   -51,   -51,   -51,   -51,   -39,    -7,
     -51,   -51,    19,   -51,    22,   -51,    14,   -51,   -51,   -51
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     4,     5,     6,     7,     8,     9,    18,    19,    20,
      45,    32,    35,    46,    47,    48,    49,    50,    51,    52,
      53,    75,    54,    76,    55,    79,    56,    57,    85,    86
  };

  const signed char
  parser::yytable_[] =
  {
      59,    37,    37,    62,     1,     2,     3,    38,    39,    39,
      77,    78,    27,    40,    41,    10,    13,    42,    14,    80,
      63,    82,    64,    43,    84,    87,    37,    88,    37,    44,
      44,    15,    38,    39,    17,    39,    14,    27,    12,    41,
      67,    68,    42,    98,    99,    17,    67,    68,    43,    15,
      61,   102,    21,    34,    44,   -14,    44,   100,    22,    69,
      70,    23,    27,    71,    72,    73,    74,    24,    89,    89,
      25,    26,    89,     1,    16,     3,    30,    31,    36,    58,
      60,    65,    66,    81,    93,    83,    94,    95,    96,   101,
      97,    11,    33,    92,    90,    29,    28,     0,    91
  };

  const signed char
  parser::yycheck_[] =
  {
      39,    10,    10,    42,    27,    28,    29,    16,    17,    17,
      13,    14,    21,    22,    23,     0,    17,    26,    19,    58,
      17,    60,    19,    32,    63,    64,    10,    66,    10,    38,
      38,    32,    16,    17,    13,    17,    19,    21,    38,    23,
      11,    12,    26,    93,    94,    24,    11,    12,    32,    32,
      32,   101,    10,    32,    38,    18,    38,    96,    38,    30,
      31,    18,    21,    34,    35,    36,    37,    33,    75,    76,
      20,    19,    79,    27,    28,    29,    32,    20,    38,    17,
      17,    32,    15,    18,    18,    32,    18,    18,    33,    25,
      20,     5,    32,    79,    75,    24,    23,    -1,    76
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    27,    28,    29,    40,    41,    42,    43,    44,    45,
       0,    42,    38,    17,    19,    32,    28,    44,    46,    47,
      48,    10,    38,    18,    33,    20,    19,    21,    49,    48,
      32,    20,    50,    43,    44,    51,    38,    10,    16,    17,
      22,    23,    26,    32,    38,    49,    52,    53,    54,    55,
      56,    57,    58,    59,    61,    63,    65,    66,    17,    57,
      17,    32,    57,    17,    19,    32,    15,    11,    12,    30,
      31,    34,    35,    36,    37,    60,    62,    13,    14,    64,
      57,    18,    57,    32,    57,    67,    68,    57,    57,    58,
      61,    63,    65,    18,    18,    18,    33,    20,    52,    52,
      57,    25,    52
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    39,    40,    41,    41,    42,    42,    43,    43,    44,
      44,    44,    45,    46,    46,    47,    47,    47,    48,    48,
      49,    50,    50,    51,    51,    52,    52,    52,    52,    52,
      53,    53,    54,    54,    55,    56,    56,    57,    57,    58,
      58,    59,    59,    60,    60,    60,    60,    60,    60,    61,
      61,    62,    62,    63,    63,    64,    64,    65,    65,    65,
      65,    66,    67,    67,    68,    68
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     1,     6,     1,     1,     3,     1,     0,     2,     4,
       4,     2,     0,     2,     0,     1,     1,     1,     1,     1,
       2,     1,     5,     7,     5,     2,     3,     3,     1,     1,
       4,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     1,     1,     1,     3,     1,     1,
       1,     4,     1,     0,     3,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "END_OF_FILE", "EOL", "REAL8", "REAL16",
  "REAL10", "INT8", "INT16", "INT10", "ADD", "SUB", "MUL", "DIV", "ASSIGN",
  "IF", "LP", "RP", "MLP", "MRP", "LLP", "LRP", "WHILE", "DO", "ELSE",
  "RETURN", "TYPE_INT", "TYPE_VOID", "TYPE_FLOAT", "LT", "GT", "SEMICOLON",
  "COMMA", "EQ", "GET", "LET", "NEQ", "ID", "$accept", "program",
  "declearation_list", "declearation", "var_declearation",
  "type_specifier", "fun_declearation", "params", "param_list", "param",
  "compound_stmt", "local_declearations", "statement_list", "statement",
  "expression_stmt", "selection_stmt", "iteration_stmt", "return_stmt",
  "expression", "var", "simple_expression", "relop", "additive_expression",
  "addop", "term", "mulop", "factor", "call", "args", "arg_list", YY_NULLPTR
  };


  const unsigned short int
  parser::yyrline_[] =
  {
       0,    78,    78,    84,    88,    95,    96,    99,   100,   103,
     104,   105,   108,   115,   116,   122,   126,   127,   130,   131,
     134,   140,   144,   147,   151,   154,   155,   156,   157,   158,
     161,   166,   170,   175,   182,   187,   188,   191,   197,   200,
     201,   204,   210,   213,   214,   215,   216,   217,   218,   221,
     227,   230,   231,   234,   240,   243,   244,   247,   248,   249,
     250,   253,   259,   260,   262,   265
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
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
      35,    36,    37,    38
    };
    const unsigned int user_token_number_max_ = 293;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1394 "bison.tab.cxx" // lalr1.cc:1167
#line 271 "bison.yxx" // lalr1.cc:1168


namespace yy{
	void
	parser::error(location const &loc, const std::string &s){
			std::cerr << "error at " << loc << ": " << s << std::endl;
	}
}
