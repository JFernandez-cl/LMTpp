#ifndef COMMENT_ITEM_TABLE_H
#define COMMENT_ITEM_TABLE_H

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>

using namespace std ;

//struct CommentItem ;
#include "commentitem.h"
#include "visitorcommentitem.h"

struct CommentItemTable : public CommentItem { 
    CommentItemTable( string& header ) ;
    virtual void print( std::ostream &os ) const { /*os << txt << endl ;*/ }
    virtual void display( std::ostream &os ) ;
    //virtual void apply_on_related_to( const std::string &s, Op *op ) { op->apply( txt ); } ;
    virtual void execute_function( VisitorCommentItem *v ) { v->function_at_CommentItemTable( this ) ;  }
    void addLine( string& s ) ;
    virtual ~CommentItemTable() {} ;

    string titre ;
    vector<vector<string> > tableau ;
};

#endif



