module  src.manager;



class Manager( K, T )
{
    T get( K key ) 
    {
        return data[ key ];
    }

    void set( K key, T val )
    {
        data[ key ] = val;
    }

    T opCall( K key ) { return data[ key ]; }
    void opCall( T val, K key ) { data[ key ] = val; }

    bool empty() { return data.length == 0; }

    void clear() { data.clear; }

    protected:
        T[K]    data;


}
