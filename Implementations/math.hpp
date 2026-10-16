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

/*
Binary Exponentiation (Non-modular/modular):
finds pow(a,b) or pow(a,b)%m in O(log(b))
*/

int binPow(int a, int b){
    int res=1;
    while (b>0){
        if (b&1) res=(res*a);
        a=(a*a);
        b>>=1;
    }
    return res;
}
int modPow(int a, int b, int mod=MOD){
    int res=1;
    a%=mod;
    while (b>0){
        if (b&1) res=(res*a)%mod;
        a=(a*a)%mod;
        b>>=1;
    }
    return res;
}

/*
Modular Inverse: 
x=modInv(a,m) iff (a*x)%m == 1
i.e. (a/x)%m = a*modInv(x,m)%m
*/
int modInv(int a, int mod=MOD){
    return modPow(a,mod-2,mod);
}

/*
Extended Euclidean GCD Algorithm:
Finds gcd(a,b) and finds x,y such that a*x+b*y = gcd(a,b)
*/
int egcd(int a, int b, int& x, int& y) {
    if (b==0) {
        x=1;
        y=0;
        return a;
    }
    int x1,y1;
    int d=egcd(b,a%b,x1,y1);
    x=y1;
    y=x1-y1*(a / b);
    return d;
}

/*
nth Fibonacci number (modular/non-modular):
Uses the recurrences 
F(2*n) = F(n) * (2*F(n+1) - F(n))
F(2*n+1) = F(n+1)^2 + F(n)^2
to calculate the nth Fibonnaci number in O(logn) using fast doubling
*/
pi fib (int n) {
    if (n==0)
        return {0,1};

    auto p=fib(n>>1);
    int c=p[0]*(2*p[1]-p[0]);
    int d=p[0]*p[0]+p[1]*p[1];
    if (n&1)
        return {d,c+d};
    else
        return {c,d};
}

pi modFib (int n, int mod=MOD) {
    if (n==0)
        return {0,1};

    auto p=modFib(n>>1);
    int c=(p[0]*((2*p[1]-p[0]+mod)%mod))%mod;
    int d=((p[0]*p[0])%mod+(p[1]*p[1])%mod)%mod;
    if (n&1)
        return {d,(c+d)%mod};
    else
        return {c,d};
}

/*
Matrices: 
2D vectors wrapped in matrix struct  
Overrides modular/non-modular multiplication (mat1*mat2) 
Overrides lookup (mat1[i][j])

If A is an m*m matrix:
matPow(A,n) computes A^n in O((m^3)*logn) using binary exponentiation
*/
struct Mat{
    vector<vector<int>> mat;
    int n,m;
    Mat(int n, int m, bool inp=false){
        this->n=n;
        this->m=m;
        mat.resize(n,vi(m,0));
        if (inp) input();
    }
    void input(){
        rep(i,0,n) arrput(mat[i]);
    }
    void print(){
        rep(i,0,n) arrprint(mat[i]);
    }
    vector<int>& operator[](int row) {
        return mat[row];
    }
    const vector<int>& operator[](int row) const {
        return mat[row];
    }
    Mat operator*(const Mat& mat2) const{
        assert(mat2.n==m);
        Mat res(n,mat2.m,0);
        rep(i,0,n){
            rep(k, 0, m) {
                if ((*this)[i][k]==0) continue;
                rep(j,0,mat2.m){
                    res[i][j]+=(*this)[i][k]*mat2[k][j];
                    //Uncomment for modular matrix multiplication
                    //res[i][j]%=MOD;
                }
            }
        }
        return res;
    }
};
Mat matPow(Mat a, int p){
    assert(a.n==a.m);
    Mat res(a.n,a.n);
    rep(i,0,a.n){
        res[i][i]=1;
    }
    while (p>0){
        if (p&1) res=res*a;
        a=a*a;
        p>>=1;
    }
    return res;
}

/*
Modular/non-modular Gauss=Jordan elimination to solve linear equations in O(n^3)
*/
int gauss(Mat a, vi &ans){
    int n=a.n;
    int m=a.m-1;
    vector<int> where(m,-1);
    for (int col=0,row=0; col<m and row<n; ++col) {
        int sel=row;
        while (sel<n and a[sel][col]%MOD==0) sel++;
        if (sel==n) continue;
        for (int i=col; i<=m; ++i)
            swap(a[sel][i],a[row][i]);
        where[col]=row;
        for (int i=0; i<n; ++i)
            if (i!=row and a[i][col]!=0) {
                int c=(a[i][col]*modInv(a[row][col]))%MOD;
                for (int j=col; j<=m; ++j) a[i][j]=(a[i][j]+MOD-(a[row][j]*c)%MOD)%MOD;
            }
        ++row;
    }
    ans.assign(m,0);
    for (int i=0; i<m; ++i)
        if (where[i]!=-1)
            ans[i]=(a[where[i]][m]*modInv(a[where[i]][i]))%MOD;
    for (int i=0; i<n; ++i) {
        int sum=0;
        for (int j=0; j<m; ++j)
            sum=(sum+(ans[j]*a[i][j]))%MOD;
        if (sum!=a[i][m]%MOD) return 0;
    }
    for (int i=0; i<m; ++i)
        if (where[i]==-1)
            return INF;
    return 1;
}
int gauss(vector<vector<double>> a, vector<double> &ans){
    int n=(int)a.size();
    int m=(int)a[0].size()-1;

    vector<int> where(m,-1);
    for (int col=0, row=0; col<m && row<n; ++col){
        int sel=row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col])>abs(a[sel][col]))
                sel=i;
        if (abs (a[sel][col])<EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i],a[row][i]);
        where[col]=row;

        for (int i=0; i<n; ++i)
            if (i!=row){
                double c=a[i][col]/a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j]-=a[row][j]*c;
            }
        ++row;
    }
    ans.assign(m,0);
    for (int i=0; i<m; ++i)
        if (where[i]!=-1)
            ans[i]=a[where[i]][m]/a[where[i]][i];
    for (int i=0; i<n; ++i){
        double sum=0;
        for (int j=0; j<m; ++j)
            sum+=ans[j]*a[i][j];
        if (abs(sum-a[i][m])>EPS)
            return 0;
    }
    for (int i=0; i<m; ++i)
        if (where[i]==-1)
            return INF;
    return 1;
}

/*
Sieve of Eratosthenes:
Checks primality of all primes in the range [1...MAXN] in O(MAXN*log(log(MAXN)))
*/
bool p[MAXN+1];
void sieve(){
    fill(p,p+MAXN+1,true);
    p[0]=p[1]=false;
    for (int i=2;i*i<=MAXN;i++){
        if (p[i]){
            for(int j=i*i;j<=MAXN;j+=i) p[j]=false;
        }
    }
}

/*
Linear Sieve:
Finds the smallest prime factor of all numbers in the range [1...MAXN] in O(MAXN)
Hence finds primality, since lp(x)==x --> x is prime
*/
int lp[MAXN+1];
void lsieve(){
    vi pr;
    rep(i,2,MAXN+1){
        if (lp[i]==0){
            lp[i]=i;
            pr.push_back(i);
        }
        for (int j=0;i*pr[j]<=MAXN;++j) {
            lp[i*pr[j]]=pr[j];
            if (pr[j]==lp[i]) break;
        }
    }
}

/*
Divisor Sieve:
Calculates the number of divisors of all numbers from [1...MAXN-1] in O(MAXN*log(MAXN))
*/
int D[MAXN];
void dsieve(){
	rep(i,1,MAXN){
		for (int j=i; j<MAXN; j+=i){
			D[j]++;
		}
	}
}

/*
Calculates the Eulers Totient Function phi(n) in O(sqrt(n));
*/
int Phi(int n){
    int res=n;
    for (int i=2;i*i<=n;i++){
        if (n%i==0){
            while (n%i==0) n/=i;
            res-=res/i;
        }
    }
    if (n>1) res-=res/n;
    return res;
}

/*
Totient Sieve:
Calculates phi(n) of all numbers from [1...MAXN-1] in O(MAXN*log(log(MAXN)))
*/
int phi[MAXN];
void allphi(){
    rep(i,0,MAXN) phi[i]=i;
    rep(i,2,MAXN){
        if (phi[i]==i){
            for (int j=i;j<=MAXN;j+=i) 
                phi[j]-=phi[j]/i;
        }
    }
}

/*
Precomputes all factorials and modular inverses to all factorials from [1...MAXN-1] in O(MAXN)
*/
int fact[MAXN];
int invfact[MAXN];
void Fact(){
    fact[0]=invfact[0]=1;
    rep(i,1,MAXN) fact[i]=(fact[i-1]*i)%MOD;
    invfact[MAXN-1]=modInv(fact[MAXN-1]);
    rrep(i,MAXN-2,0) invfact[i]=(invfact[i+1]*(i+1))%MOD;
}