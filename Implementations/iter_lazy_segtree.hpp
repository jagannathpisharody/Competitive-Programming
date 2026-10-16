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
    int n,h;
    T ide; vector<T> t;
    S idt; vector<S> lazy;
    T (*merge) (T,T); T (*upd) (S,T); S (*comp) (S,S);
    lazysegtree(vector<T> &a, T _merge(T,T), T _upd(S,T), S _comp(S,S), T _ide, S _idt){
        n=a.size(); t.resize(2*n,_ide);
        idt=_idt; ide=_ide; lazy.assign(n,_idt);
        merge=_merge; upd=_upd; comp=_comp;
        h=32-__builtin_clz((int32_t)(n<<1));
        rep(i,0,n) t[n+i]=a[i];
        rrep(i,n-1,0) t[i]=merge(t[i<<1],t[i<<1|1]);
    }
    void push(int v){
        rrep(s,h,0){
            int i=v>>s;
            if (i>0 and lazy[i]!=idt){
                t[i<<1]=upd(lazy[i],t[i<<1]);
                if ((i<<1)<n) lazy[i<<1]=comp(lazy[i],lazy[i<<1]);
                t[i<<1|1]=upd(lazy[i],t[i<<1|1]);
                if ((i<<1|1)<n) lazy[i<<1|1]=comp(lazy[i],lazy[i<<1|1]);
                lazy[i]=idt;
            }
        }
    }
    void update(int l, int r, S val){
        l+=n; r+=n+1;
        int l0=l, r0=r-1;
        push(l0); push(r0);
        for (;l<r;l>>=1,r>>=1) {
            if (l&1){
                t[l]=upd(val,t[l]);
                if (l<n) lazy[l]=comp(val,lazy[l]);
                l++;
            }
            if (r&1){
                --r;
                t[r]=upd(val,t[r]);
                if (r<n) lazy[r]=comp(val,lazy[r]);
            }
        }
        while (l0>1){
            l0>>=1;
            t[l0]=upd(lazy[l0],merge(t[l0<<1],t[l0<<1|1]));
        }
        while (r0>1){
            r0>>=1;
            t[r0]=upd(lazy[r0],merge(t[r0<<1],t[r0<<1|1]));
        }
    }
    T query(int l, int r){ 
        l+=n; r+=n+1; 
        push(l); push(r-1);
        T rl=ide, rr=ide;
        for (;l<r; l>>=1, r>>=1) {
            if (l&1) rl=merge(rl,t[l++]);
            if (r&1) rr=merge(t[--r],rr);
        }
        return merge(rl,rr);
    }
};
