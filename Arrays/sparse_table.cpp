template<typename T=int>
class sparse_table {
    int log2(long long x) { return 63 - __builtin_clzl(x); }
    int log2(int x) { return 31 - __builtin_clz(x); }
    
    public:
    vector<vector<T>> tbl;
    int n;
    sparse_table(){}
    void build(vector<T> vec) {
        n = vec.size();
        int lg = log2(n);
        tbl.assign(n, vector<T>(lg+1));
        for (int i = 0; i < n; i++) tbl[i][0] = vec[i];
        for (int j = 1; j <= lg; j++) {
            for (int i = 0; i+(1<<(j-1)) < n; i++) {
                tbl[i][j] = min(tbl[i][j-1], tbl[i+(1<<(j-1))][j-1]);
            }
        }
    }
    
    T query(int l, int r) {
        int lg = log2(r-l+1);
        return min(tbl[l][lg], tbl[r-(1<<(lg))+1][lg]);
    }
};