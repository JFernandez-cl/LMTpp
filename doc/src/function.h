#ifndef FUNCTION_H
#define FUNCTION_H

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>

using namespace std;

#include "tagcomment.h"
#include "visitorbloc.h"

enum TypeFunctionID {
    UNKNOW_TYPE_FUNCTION_ID = 0,
    TYPE_FUNCTION_CONSTRUCTEUR_ID = 1,
    TYPE_FUNCTION_DESTRUCTOR_ID = 2,
    TYPE_FUNCTION_OPERATOR_ID = 3,
    TYPE_FUNCTION_METHOD_ID = 4,
    TYPE_FUNCTION_FUNCTION_ID = 5,
};



struct Function : public Bloc {
    Function( ) { }
    ~Function();
    virtual void display( std::ostream &os );
    virtual void exec( VisitorBloc *v ) { v->exec( this );  }
    //void apply_on_related_to( const std::string &s, Op *op );

    /// méthode virtuelle de target
    virtual bool of_function() { return true; }

    string listAttribut; // static, const, ...
    ListParameter listParameter;
    Names returnType;
    //string referencement;
};


#endif

