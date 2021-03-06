//
// C++ Interface: lexer
//
// Description: 
//
//
// Author: LECLERC <leclerc@lmt.ens-cachan.fr>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LEXER_H
#define LEXER_H

#include "splittedvec.h"
#include "usual_strings.h"
#include "lexem.h"
#include "lexemnumber.h"
#include "lexemdefinition.h"

/**
    @author Grover <hugo@gronordi>
 */
class Lexer {
public:
    Lexer( const char *txt, const char *provenance, ErrorList *error_list ); /// txt must point to the first non null char
    ~Lexer();

    const Lexem *root() const { return first_tok.next; }

    Lexem *app_tok( int type, const char *s, unsigned si, int num );
    void make_flat_token_list();
    void set_next_prev_fields(); /// assign next and prev field in all tokens
    void parenthesis_hierarchisation(); /// mark data into (), [] and {} as children
    void make_unit_hierarchy();        
    void remove_cr();
    void assemble___calc_name__();
    void assemble___string_assembly__();
    void assemble_par___getattr__();   
    void assemble_op();                
    void parse_definitions();
    void add_child_to_info( int stn );
    template<bool stop_condition> void read_s(const char *limit=NULL);
    void read_dollar( const char *old_str, unsigned nb_spaces = 0 );

    bool assemble_2_args(Lexem *o,int need_left,int need_right);
    bool assemble_right_arg(Lexem *o);
    bool assemble_left_arg(Lexem *o);

    Lexem* first_def() { return first_of_type[STRING___def___NUM+16]; }
    Lexem* first_class() { return first_of_type[STRING___class___NUM+16]; }
    Lexem* first_assign() { return first_of_type[STRING_assign_NUM+16]; }

    Lexem *first_of_type[NB_OPERATORS+16]; ///
    Lexem *last_of_type[NB_OPERATORS+16]; ///
    Lexem first_tok;

    const char *s, *provenance;
    ErrorList *error_list;
    SplittedVec<Lexem,1024,4096,true> tokens;
    SplittedVec<LexemNumber,256,1024,true> numbers;
    SplittedVec<LexemDefinition,256,1024,true> defs;
};

#endif
