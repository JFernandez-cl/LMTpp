#ifndef OP_LIST_TARGET_H
#define OP_LIST_TARGET_H


//#include "pagecomment.h"
#include "op.h"

struct PageComment ;
struct VisitorBloc_NameBaseClass ;
struct ListTarget ;



struct OpListTarget : Op {
    OpListTarget( ListTarget* pt  ) { ptr_list_target = pt ; }
    virtual ~OpListTarget() {}
    virtual void operator()( PageComment* page ) ;
    //void setStartId( const char* n) ;
    //void getStartId( string& n) ;
  


    ListTarget* ptr_list_target ;
};

#endif

