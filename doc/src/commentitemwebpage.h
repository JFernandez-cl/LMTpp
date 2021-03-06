#ifndef COMMENT_ITEM_WEBPAGE_H
#define COMMENT_ITEM_WEBPAGE_H

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>

using namespace std;

//struct CommentItem;
#include "commentitem.h"
#include "visitorcommentitem.h"

struct CommentItemWebPage : public CommentItem { 
    CommentItemWebPage( string& parametre  ); // parametre sera de la forme [titre]{page web} sachant que {page web} est facultatif
    virtual void print( std::ostream &os ) const { /*os << txt << endl;*/ }
    virtual void display( std::ostream &os );
    //virtual void apply_on_related_to( const std::string &s, Op *op ) { op->apply( txt ); };
    virtual void execute_function( VisitorCommentItem *v ) { v->function_at_CommentItemWebPage( this );  }
    string getTitle();
    string getName();
    string getNameHtml();
    virtual ~CommentItemWebPage() {};

    //string titre;
    //string nomHtml;
    std::vector<CommentItem*> items;
};

#endif



