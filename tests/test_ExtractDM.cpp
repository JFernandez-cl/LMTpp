#include "../include/mesh/meshcaracstd.h"

using namespace std;
using namespace LMT;

int main() {
    typedef Mesh<MeshCaracStd<2,2> > TM;
    TM m;
    m.add_node( TM::Pvec( 0, 1 ) );
    PRINT( generate( m.node_list, ExtractDM<pos_DM>() ) );
    PRINT( generate( m.node_list, ExtractDMi<pos_DM>( 0 ) ) );
    PRINT( generate( m.node_list, ExtractDMi<pos_DM>( 1 ) ) );
}




