//
// C++ Interface: Bar_6
//
// Description: 
//
//
// Author: Hugo LECLERC <leclerc@lmt.ens-cachan.fr>, (C) 2004
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef LMTBAR_6_H
#define LMTBAR_6_H

#include "../containers/staticassert.h"
#include "NodalElement.h"

namespace LMT {

// --------------------------------------------------------------------------------------------------------
/*!
    Barre sans dimension ou segment à 6 noeuds
    \verbatim
    .                    0--2--3--4--5--1
    \relates Mesh
    \relates Element
    \keyword Maillage/Elément
    \friend hugo.leclerc@lmt.ens-cachan.fr
*/
struct Bar_6 {
    static const unsigned nb_var_inter = 1;
    static const unsigned nb_nodes = 6;
    static const char *name() { return "Bar_6"; }
    static const char *can_directly_be_represented_by() { return "Bar_6"; }
};

// --------------------------------------------------------------------------------------------------------
template<> struct NbChildrenElement<Bar_6,0> { static const unsigned res = 1; };
template<> struct NbChildrenElement<Bar_6,1> { static const unsigned res = 2; };

template<unsigned n> struct TypeChildrenElement<Bar_6,0,n> { typedef Bar_6 T; };
template<unsigned n> struct TypeChildrenElement<Bar_6,1,n> { typedef NodalElement T; };

template<class TN,class TNG,class TD,unsigned NET,class TC,class HET>
void append_skin_elements(Element<Bar_6,TN,TNG,TD,NET> &e,TC &ch,HET &het,Number<0> nvi_to_subs) {
    het.add_element(e,ch,Bar_6(),e.node(0),e.node(1),node(2),e.node(3),node(4),e.node(5));
}
template<class TN,class TNG,class TD,unsigned NET,class TC,class HET>
void append_skin_elements(Element<Bar_6,TN,TNG,TD,NET> &e,TC &ch,HET &het,Number<1> nvi_to_subs) {
    het.add_element(e,ch,NodalElement(),e.node(0));
    het.add_element(e,ch,NodalElement(),e.node(1));
}

// --------------------------------------------------------------------------------------------------------
/* TODO : exact computation */
template<class TN,class TNG,class TD,unsigned NET>
typename TypePromote<Abs,typename TNG::T>::T measure( const Element<Bar_6,TN,TNG,TD,NET> &e ) {
    return abs ( length( e.node(1)->pos - e.node(0)->pos ) );
}

template<class TN,class TNG,class TD,unsigned NET>
typename TNG::Pvec sample_normal(const Element<Bar_6,TN,TNG,TD,NET> &e) {
    DEBUGASSERT( (TNG::dim==2) );
    typename TNG::Pvec res;
    res.assign_and_complete_with_last( e.pos(1)[1]-e.pos(0)[1], e.pos(0)[0]-e.pos(1)[0] );
    res /= length(res);
    return res;
}

inline unsigned vtk_num( StructForType<Bar_6> ) { return 4; }

}

//#include "element_Bar_6.h"

#endif // LMTBAR_6_H
