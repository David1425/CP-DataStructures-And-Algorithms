template <typename T>
class binary_indexed_tree {
    T (*calc)(T, T) = [](T a, T b) {
        return a+b;
    };
    
    T (*inv)(T, T) = [](T a, T b) {
        return a-b;
    };
    
    T base = 0;
    
    public:
    vector<T> bit;
    int size;
    
    binary_indexed_tree(int n, int def = 0) : size(n) {
        bit.assign(n+1, def);
    }
    
    void setCalc(T (*func)(T, T)) { calc=func; }
    void setInv(T (*func)(T, T)) { inv=func; }
    void setBase(T val) { base=val; }
    
    void update(int ind, T v) {
        for (; ind <= size; ind += ind&-ind) {
            bit[ind] = calc(bit[ind], v);
        }
    }
    
    void build(vector<T> vec) {
        for (int i = 0; i < vec.size(); i++) {
            update(i+1, vec[i]);
        }
    }
    
    T query(int pos) {
        T res = base;
        for (; pos > 0; pos -= pos&-pos) {
            res = calc(res, bit[pos]);
        }
        return res;
    }
    
    T query(int l, int r) { return inv(query(r), query(l-1)); }
};
