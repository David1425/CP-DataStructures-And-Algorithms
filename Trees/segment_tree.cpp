template <typename T>
struct segment_tree {
    vector<T> o;
    
    T (*calc)(T, T) = [](T a, T b) {
        return min(a, b);
    };
    
    T base = T(2e9);
    
    void build(int i, int l, int r) {
        if (l == r) {
            if (l < int(o.size())) st[i] = o[l];
            return;
        }
        
        int mid = (l+r)/2;
        build(i*2, l, mid);
        build(i*2+1, mid+1, r);
        st[i] = calc(st[i*2], st[i*2+1]);
    }
    
    void update(int ind, T v, int i, int l, int r) {
        if (l == r) {
            st[i] = v;
            return;
        }
        
        int mid = (l+r)/2;
        if (ind <= mid) update(ind, v, i*2, l, mid);
        else update(ind, v, i*2+1, mid+1, r);
        st[i] = calc(st[i*2], st[i*2+1]);
    }
    
    T query(int lx, int rx, int i, int l, int r) {
        if (r < lx || l > rx) return base;
        if (l >= lx && r <= rx) return st[i];
        int mid = (l+r)/2;
        T a = query(lx, rx, i*2, l, mid);
        T b = query(lx, rx, i*2+1, mid+1, r);
        return calc(a, b);
    }
    
    vector<T> st;
    int size;
    
    segment_tree(int n) : size(n) { st.assign(1<<(int(ceil(log2(n)))+1), 0); }
    
    void setCalc(T (*func)(T, T)) { calc=func; }
    void setBase(T val) { base=val; }
    
    void build(vector<T> v) { o=v; build(1, 0, size-1); }
    
    void update(int ind, T v) { update(ind, v, 1, 0, size-1); }
    
    T query(int l, int r) { return query(l, r, 1, 0, size-1); }
};
