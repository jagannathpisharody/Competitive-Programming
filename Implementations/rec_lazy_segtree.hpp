#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds; 
template<typename T> inline void input(T& x) {cin>>x;}
template<typename T, typename... S> inline void input(T& x, S&... args) {cin>>x; input(args ...);}
template<typename T> inline void print(T x) {cout<<x<<'\n';}
template<typename T, typename... S> inline void print(T x, S... args) {cout<<x<<' '; print(args ...);}
#define arrput(l) for (auto &i : l) {cin>>i;}
#define arrprint(l) for (auto i : l) {cout<<i<<' ';} cout << '\n'
#define debug(...) cout<<#__VA_ARGS__<<": "; print(__VA_ARGS__);
#define rep1(a) for(int i=0; i<a; i++)
#define rep2(i,a) for(int i=0; i<a; i++)
#define rep3(i,a,b) for(int i=a; i<b; i++)
#define rep4(i,a,b,c) for(int i=a; i<b; i+=c)
#define Overload4(a,b,c,d,e,...) e
#define rep(...) Overload4(__VA_ARGS__,rep4,rep3,rep2,rep1)(__VA_ARGS__)
#define rrep1(a) for(int i=0; i<a; i++)
#define rrep2(i,a) for(int i=a; i>0; i--)
#define rrep3(i,a,b) for(int i=a; i>b; i--)
#define rrep4(i,a,b,c) for(int i=a; i>b; i-=c)
#define rrep(...) Overload4(__VA_ARGS__,rrep4,rrep3,rrep2,rrep1)(__VA_ARGS__)
template<class... T> constexpr auto min(T... a) {return std::min(initializer_list<common_type_t<T...>>{a...});}
template<class... T> constexpr auto max(T... a) {return std::max(initializer_list<common_type_t<T...>>{a...});}
#define sz(x) int(size(x))
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define sor(x) sort(all(x))
#define rsor(x) sort(rall(x))
#define llog(x) (63-__builtin_clzll(x)) 
#define ilog(x) (31-__builtin_clz(x))
#define _add [](int a, int b){return a+b;}
#define _sub [](int a, int b){return a-b;}
#define _mul [](int a, int b){return a*b;}
#define _div [](int a, int b){return a/b;}
#define _max [](int a, int b){return max(a,b);}
#define _min [](int a, int b){return min(a,b);}
#define _xor [](int a, int b){return a^b;}
#define setup() ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define int long long
#define str string
#define i128 __int128
typedef vector<int> vi; typedef array<int,2> pi;
template<typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = (int) 1e9 + 7; //998244353;
const int INF = (int) 1e18;
const int MAXN = (int) 5e5 + 5; 
const double EPS=1e-9;
const double PI=acos(-1.0);

template<typename T, typename S> struct lazysegtree{
    int n;
    T ide; vector<T> t;
    S idt; vector<S> lazy;
    T (*merge) (T,T); T (*upd) (S,T); S (*comp) (S,S);
    lazysegtree(vector<T> &a, T _merge(T,T), T _upd(S,T), S _comp(S,S), T _ide, S _idt){
        n=a.size(); t.resize(4*n+5);
        idt=_idt; ide=_ide; lazy.resize(4*n+5,idt);
        merge=_merge; upd=_upd; comp=_comp;
        build(a,1,0,n-1);
    }
    void build(vector<T> &a, int v, int tl, int tr){
        if (tl==tr) t[v]=a[tl];
        else{
            int tm=(tl+tr)/2;
            build(a,2*v,tl,tm);
            build(a,2*v+1,tm+1,tr);
            t[v]=merge(t[2*v],t[2*v+1]);
        }
    }
    void push(int v){
        if (lazy[v]==idt) return;
        t[2*v]=upd(lazy[v],t[2*v]);
        lazy[2*v]=comp(lazy[v],lazy[2*v]);
        t[2*v+1]=upd(lazy[v],t[2*v+1]);
        lazy[2*v+1]=comp(lazy[v],lazy[2*v+1]);
        lazy[v]=idt;
    }
    void update(int v, int tl, int tr, int l, int r, S val){
        if (l>r) return;
        if (l==tl and r==tr){
            t[v]=upd(val,t[v]);
            lazy[v]=comp(val,lazy[v]);
            return;
        }
        push(v);
        int tm=(tl+tr)/2;
        update(2*v,tl,tm,l,min(r,tm),val);
        update(2*v+1,tm+1,tr,max(l,tm+1),r,val);
        t[v]=merge(t[2*v],t[2*v+1]);
    }
    void update(int l, int r, S val){
        update(1,0,n-1,l,r,val);
    }
    T query(int v, int tl, int tr, int l, int r){
        if (l>r) return ide;
        if (l==tl and r==tr) return t[v];
        push(v);
        int tm=(tl+tr)/2;
        return merge(query(2*v,tl,tm,l,min(r,tm)),query(2*v+1,tm+1,tr,max(l,tm+1),r));
    }
    T query(int l, int r){ 
        return query(1,0,n-1,l,r);
    }
};