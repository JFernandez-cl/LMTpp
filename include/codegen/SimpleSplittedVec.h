#ifndef SIMPLESPLITTEDVEC_H
#define SIMPLESPLITTEDVEC_H

template<class T,unsigned atomic_size = 256>
struct SimpleSplittedVec {
    struct Atom {
        Atom() : size( 0 ), next( NULL ) {}
        T values[ atomic_size ];
        unsigned size;
        Atom *next;
    };

    SimpleSplittedVec() {
        init();
    }

    ~SimpleSplittedVec() {
        destroy();
    }

    void init() {
        first = new Atom;
        last  = first;
    }

    void destroy() {
        for(Atom *n = first; n; ) {
            Atom *o = n;
            n = n->next;
            delete o;
        }
    }

    void free() {
        destroy();
        init();
    }

    T *new_elem() {
        if ( last->size == atomic_size ) {
            Atom *n = new Atom;
            last->next = n;
            last = n;
        }
        return last->values + last->size++;
    }

    void write( const T *data, int size ) {
        for(int i=0;i<size;++i)
            *new_elem() = data[ i ];
    }

    void push_back( const T &v ) {
        *new_elem() = v;
    }

    void operator+=( const SimpleSplittedVec &v ) {
        for(unsigned i=0;i<v.size();++i)
            push_back( v[ i ] );
    }

    unsigned size() const {
        unsigned res = 0;
        for( Atom *a = first; a; a = a->next )
            res += a->size;
        return res;
    }

    T &operator[]( unsigned i ) {
        Atom *a = first;
        while( i >= atomic_size ) {
            i -= a->size;
            a = a->next;
        }
        return a->values[ i ];
    }

    const T &operator[]( unsigned i ) const {
        Atom *a = first;
        while( i >= atomic_size ) {
            i -= a->size;
            a = a->next;
        }
        return a->values[ i ];
    }

    Atom *first;
    Atom *last ;
};

#endif // SIMPLESPLITTEDVEC_H

