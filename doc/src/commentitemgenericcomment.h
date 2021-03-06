#ifndef COMMENT_ITEM_GENERIC_COMMENT_H
#define COMMENT_ITEM_GENERIC_COMMENT_H

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>

using namespace std;

//struct CommentItem;
#include "commentitem.h"
#include "visitorcommentitem.h"
#include "target.h"

// CommentItemGenericComment est une structure permettant de stocker des informations sur une fonction ou une classe template ou encore une fonction surdéfinie.
struct CommentItemGenericComment : public CommentItem { 
    CommentItemGenericComment( string& sref);
    virtual void print( std::ostream &os ) const { /*os << txt << endl;*/ }
    virtual void display( std::ostream &os );
    virtual void execute_function( VisitorCommentItem *v ) { v->function_at_CommentItemGenericComment( this );  }
    virtual ~CommentItemGenericComment() {}
    virtual bool of_generic_comment() { return true; }

    std::vector<CommentItem*> items;
};

#endif



