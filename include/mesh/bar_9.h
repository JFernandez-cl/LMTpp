//
// C++ Interface: node
//
// Description: 
//
//
// Author: Hugo LECLERC <leclerc@lmt.ens-cachan.fr>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LMTBAR9_H
#define LMTBAR9_H

#include "containers/staticassert.h"
#include "nodalelement.h"

namespace LMT {

// --------------------------------------------------------------------------------------------------------
/*!
    Bar_9 représente une barre sans dimension ou segment avec neuf noeud dessus.  
    \verbatim
    .                    0--2--3--4--5--6--7--8--1
    \relates Mesh
    \relates Element
    \keyword Maillage/Elément
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/

struct Bar_9 {
    static const unsigned nb_var_inter = 1;
    static const unsigned nb_nodes = 9;
    static const char *name() { return "Bar_9"; }
    static const char *can_directly_be_represented_by() { return "Bar_9"; }
};

// --------------------------------------------------------------------------------------------------------
template<> struct NbChildrenElement<Bar_9,1> { static const unsigned res = 2; };

template<unsigned n> struct TypeChildrenElement<Bar_9,1,n> { typedef NodalElement T; };

template<class TN,class TNG,class TD,unsigned NET,class TC,class HET>
void append_skin_elements(Element<Bar_9,TN,TNG,TD,NET> &e,TC &ch,HET &het,Number<1> nvi_to_subs) {
    het.add_element(e,ch,NodalElement(),e.node(0));
    het.add_element(e,ch,NodalElement(),e.node(1));
}

// --------------------------------------------------------------------------------------------------------

template<class TN,class TNG,class TD,unsigned NET>
typename TNG::Pvec sample_normal(const Element<Bar_9,TN,TNG,TD,NET> &e) {
    DEBUGASSERT( (TNG::dim==2) );
    typename TNG::Pvec res;
    res.assign_and_complete_with_last( e.pos(1)[1]-e.pos(0)[1], e.pos(0)[0]-e.pos(1)[0] );
    res /= length(res);
    return res;
}


/* TODO : exact computation */
template<class TN,class TNG,class TD,unsigned NET>
typename TNG::T measure( const Element<Bar_9,TN,TNG,TD,NET> &e ) {
    return length( e.node(1)->pos - e.node(0)->pos );
}


};

#endif