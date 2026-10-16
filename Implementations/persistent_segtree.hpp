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

template<typename T> struct persegtree{
    int n;
    T id;
    T (*merge) (T,T);
    struct node{
        node *l, *r;
        T val;
        node(T val=0) : val(val), l(nullptr), r(nullptr) {}
    };
    node* makenode(node* l, node* r){
        node* ans=new node(id);
        ans->l=l;
        ans->r=r;
        if (l) ans->val=merge(ans->val,l->val);
        if (r) ans->val=merge(ans->val,r->val);
        return ans;
    }
    vector<node*> roots;
    persegtree(vector<T> &a, T func(T,T), T i){
        n=a.size();
        id=i;
        merge=func;
        if (n>0) roots.push_back(build(a,0,n-1));
    }
    node* build(vector<T> &a, int tl, int tr){
        if (tl==tr) return new node(a[tl]);
        int tm=(tl+tr)/2;
        return makenode(build(a,tl,tm),build(a,tm+1,tr));
    }
    T query(node* v, int tl, int tr, int l, int r){
        if (l>r) return id;
        if (l==tl and r==tr) return v->val;
        int tm=(tl+tr)/2;
        return merge(query(v->l,tl,tm,l,min(r,tm)),query(v->r,tm+1,tr,max(l,tm+1),r));
    }
    T query(int time, int l, int r){ 
        return query(roots[time],0,n-1,l,r);
    }
    T query(int l, int r){ 
        return query(roots.back(),0,n-1,l,r);
    }
    node* update(node* v, int tl, int tr, int pos, T new_val){
        if (tl==tr) return new node(new_val);
        int tm=(tl+tr)/2;
        if (pos<=tm) return makenode(update(v->l,tl,tm,pos,new_val),v->r);
        else return makenode(v->l,update(v->r,tm+1,tr,pos,new_val));
    }
    void update(int pos, T new_val){
        roots.push_back(update(roots.back(),0,n-1,pos,new_val));
    }
};
