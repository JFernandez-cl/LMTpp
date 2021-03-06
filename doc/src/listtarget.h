#ifndef LIST_TARGET_H
#define LIST_TARGET_H

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<vector>

using namespace std ;

#include "names.h"
#include "target.h"

// tous les id pairs correspondent à des targets qui ont été spécialement instanciés et qu'il faudra désallouer.
/*
enum typeTargetID
{
    GENERIC_WITHOUT_GENERIC_COMMENT_ITEM_ID = 0,
    NON_GENERIC_ID = 1,
    NON_GENERIC_REAL_TARGET_ID = 2,
    GENERIC_WITH_GENERIC_COMMENT_ITEM_ID = 3
};
*/

struct TargetIntel {

    Target* pt ;
    bool realTarget ; // Si pt est instancié alors realTarget est vrai, et faux sinon
    //bool verify; // sert à caractériser le target pour une certaine propriété
} ;

/*
struct GenericName {


    //Target* pt_generic_comment ;
} ;
*/
//typedef std::vector<Target*> VectorTarget ;

/*
Cette structure permet de stocker les adresses d'objets Target.
Pour distinguer les adresses d'objets déjà existants (cad déjà référencé) de ceux qui
sont seulement référencé par list[i] (i indice ), j'ai ajouté un booléen realTarget

*/
struct ListTarget {
    ListTarget( ) { }
    ~ListTarget() ;
    void clear() ;
    void push_back( Target*, bool incrementID ) ;// ajoute un Target à la liste.
    void push_back_RealTarget( Target*, bool incrementID ) ;// ajoute un Target à la liste. Il est instancié par la fonction appelante.
    //void setID() ; // cette fonction donne un numéro identifiant à chaque objet Target déjà créé avant l'appel.
    Target* isName( string& nom ) ;
    int nb_principalName(int* indice, string& name);
    int isPrincipalName0( string& nom ) ;
    void set_type_of_listPrincipalName();
    void generate_listPrincipalName( string& path_generic_comment );
    void init_property();
    void update_property_of_generic_comment(); // cette fonction s'assure que si un target a une certaine propriété alors son éventuel target du type "generic comment" aura aussi la même propriété 
    friend std::ostream &operator<<( std::ostream &os, ListTarget& t ) ;
    void write_listPrincipalName(const char* filename);
    
    //private:
    vector<TargetIntel> list ;
    //vector<bool> realTarget; // correspond à la liste list. Si list[i].pt est instancié alors realTarget[i] est vrai, et faux sinon
    //vector<GenericName> listPrincipalName ;
    vector<int> listPrincipalName ; // contient les indices dans list des targets "génériques".
} ;


#endif

