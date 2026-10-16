#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds; 
template<typename T> inline void input(T& x) {cin>>x;}
template<typename T, typename... S> inline void input(T& x, S&... args) {cin>>x; input(args ...);}
template<typename T> inline void print(T x) {cout<<x<<'\n';}
template<typename T, typename... S> inline void print(T x, S... args) {cout<<x<<' '; print(args ...);}
#define arrput(l) for (auto &bs : l) {cin>>bs;}
#define arrprint(l) for (auto bss : l) {cout<<bss<<' ';} cout << '\n'
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
typedef vector<int> vi; typedef array<int,2> pi;
template<typename T> using ordered_set =  tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int MOD = (int) 1e9 + 7; //998244353;
const int INF = (int) 1e18;
const int MAXN = (int) 5e5 + 5; 
const double EPS=1e-9;
const double PI=acos(-1.0);

void dfs(int s, int p, vector<vi> &adj){
    //process s
    for (auto u:adj[s]){
        if (u==p) continue;
        dfs(u,s,adj);
        //process dp if any
    }
}

/*
DSU on trees/Heavy-to-Light merging/Sack: 
count number of nodes satisfying a certain property in the subtree of v

answer offline queries:

maintain a data structure that can help you answer the queries for one node
Allows calculation of the data structure for each node in O(n*log(n))
*/

void dfs1(int s, int p, vector<vi> &adj, vi& siz, vector<bool>& heavy){ //sizes
    siz[s]=1;
    int h=-1;
    for (auto u:adj[s]){
        if (u==p) continue;
        dfs1(u,s,adj,siz,heavy);
        siz[s]+=siz[u];
        if (h==-1 or siz[u]>siz[h]) h=u;
    }
    if (h!=-1) heavy[h]=true;
}

void add(int u, int p, vector<vi> &adj){
    //add the contribution of u to the data structure
    for (auto v: adj[u]){
        if (v!=p) add(v,u,adj);
    }
}

void erase(int u, int p, vector<vi> &adj){
    //erase the contribution of u to the data structure
    for (auto v: adj[u]){
        if (v!=p) erase(v,u,adj);
    }
}

void dfs2(int s, int p, vector<vi> &adj, vi& siz, vector<bool>& heavy){
    int h=-1;
    for (auto u:adj[s]){
        if (u==p) continue;
        if (heavy[u]){
            h=u;
            continue;
        }
        dfs2(u,s,adj,siz,heavy);
        erase(u,s,adj);
    }
    if (h!=-1){
        dfs2(h,s,adj,siz,heavy);
    }

    for (auto u:adj[s]){
        if (u==p or heavy[u]) continue;
        add(u,s,adj);
    }

    //add contribution of s

    //answer queries here
}


/*
Heavy-Light Decomposition of trees:

REQUIREMENT: Segment Tree

Edges are heavy if they connect half of the subtree to the parent
Else, edges are light.

For a tree with n nodes:
Heavy chains are the longest possible chains of heavy edges on a path from a node to the root
It can be proved that there are O(log(n)) light edges on the path from any node to the root
It follows that there are O(log(n)) heavy chains on the path from any node to the root

Therefore, we can build a segment tree on a special ordering of vertices to query properties of paths
*/
template<typename T> struct HLD{
    int n,cidx;
    T id;
    vector<vi> adj;
    vi siz,depth,heavy,parent,idx,head;
    vector<T> a;
    T (*merge)(T,T);
    HLD(int n, vector<T>& arr, T func(T,T), T id): n(n),adj(n+1),a(n),siz(n+1),depth(n+1),heavy(n+1,-1),parent(n+1),idx(n+1),head(n+1),id(id),seg(a,func,id){
        rep(i,0,n) a[i]=arr[i];
        cidx=1;
        idx[1]=0;
        merge=func;
    }
    void inpEdge(){
        int x,y; input(x,y);
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    void addEdge(int x, int y){
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    void dfs1(int s, int p){
        siz[s]=1;
        for (auto u:adj[s]){
            if (u==p) continue;
            depth[u]=depth[s]+1;
            parent[u]=s;
            dfs1(u,s);
            siz[s]+=siz[u];
        }
        for (auto u:adj[s]){
            if (u==p) continue;
            if (2*siz[u]>=siz[s]) heavy[s]=u;
        }
    }
    void dfs2(int s, int p){
        if (!head[s]) head[s]=s;
        if (heavy[s]!=-1){
            idx[heavy[s]]=cidx++;
            head[heavy[s]]=head[s];
            dfs2(heavy[s],s);
        }
        for (auto u:adj[s]){
            if (u==p or u==heavy[s]) continue;
            idx[u]=cidx++;
            dfs2(u,s);
        }
    }
 
    segtree<T> seg;
    void build(){
        dfs1(1,0);
        dfs2(1,0);
        vector<T> b(n);
        rep(i,0,n) b[idx[i+1]]=a[i];
        seg=segtree<T>(b,merge,id);
    }
    void update(int v, int val){
        seg.update(idx[v],val);
    }
    T query(int u, int v){
        T res=id;
        while (head[u]!=head[v]){
            if (depth[head[u]]>depth[head[v]]) swap(u,v);
            res=merge(res,seg.query(idx[head[v]],idx[v]));
            v=parent[head[v]];
        }
        if (depth[u]>depth[v]){
            swap(u,v);
        }
        res=merge(res,seg.query(idx[u],idx[v]));
        return res;
    }
};