#include<bits/stdc++.h>
using namespace std;
#ifdef __LOCAL_DEBUG__
#define _debug(fmt, ...) fprintf(stdout, "\033[91m[%s %3d]: " fmt "\n\033[0m", \
                                 __func__, __LINE__, ##__VA_ARGS__)
#else
# define _debug(...) (void(0))
#endif
const int maxn = 100 + 5;
typedef double db;
bool temp[maxn];
int x, n, m;
db a[2 * maxn];
db b[2 * maxn];
int alive[maxn][maxn];

// vector<tuple<int, int,int,int, db, db, db, db, db>>verbose;
struct Comp{
    int id;
    // ???A*X + B
    int A,B;
    // ?? C*X + D
    int C,D;
    // ??? E*X + F
    int E,F;
    // ?? G*X + H.
    // I ????
    int G,H,I;
    // ??????
    int U, V;
    //???? U*X+V
    int J, K;
    // ????????
    int L,R;
    // ??n???????
    int P[maxn];
    
    // ?i????j??,?????
    db stock_const[maxn][maxn];
    db stock_x[maxn][maxn];
    vector<pair<int,int>> trans;
    void input(){
        cin>>A>>B>>C>>D>>E>>F>>G>>H>>I>>U>>V>>J>>K>>L>>R;
        for (int i = 1; i <= n; i ++){
            cin>>P[i];
        }
    }
    void init_stock(){
        // i ????
        for (int i = max(1, L); i <= min(n, R); i ++){
            memset(a, 0, sizeof a);
            memset(b, 0, sizeof b);
            // ????????
            for (int j = i; j <= min(n, R); j ++){
                //???? ????(X??)
                db annual =  H + (j - i) * G;
                annual /= I;
                a[j + 1] += annual;
                a[j + I + 1] -= annual;

                //???? x??(??x)
                db inc = 1.0 * G / I;
                b[j + 1] += inc;
                b[j + I + 1] -= inc;

                a[j] += a[j-1];
                b[j] += b[j-1];

                if (i == 1 && j == 7 && id == 1){
                    for (int i = 1; i <= n; i ++){
                        _debug("a[%d] = %.2lf\n", i, a[i]);
                    }
                    for (int i = 1; i <= n; i ++){
                        _debug("b[%d] = %.2lf\n", i, b[i]);
                    }
                }
            }

            // <price, const shares sold at price, x shares>
            stack<tuple<int, db, db>> stk;
            for (int j = i; j <= min(n, R); j ++){
                db shares = 0, shares_x = 0;
                db income = 0, income_x = 0;
                while (!stk.empty() && get<0>(stk.top()) <= P[j]){
                    int pre_price;
                    db shares_sold;;
                    db shares_sold_x;
                    tie(pre_price, shares_sold, shares_sold_x) = stk.top();
                    stk.pop();
                    db delta_income = (P[j] - pre_price) * shares_sold;
                    db delta_income_x = (P[j] - pre_price) * shares_sold_x;
                    shares += shares_sold;
                    shares_x += shares_sold_x;
                    income += delta_income;
                    income_x += delta_income_x;
                }

                db shares_new = a[j];
                income += shares_new * P[j];
                db shares_new_x = b[j];
                income_x += shares_new_x * P[j];
                stk.push({P[j], shares_new + shares, shares_new_x + shares_x});
                stock_const[i][j] = income + stock_const[i][j-1];
                stock_x[i][j] = income_x + stock_x[i][j-1];

                if (i == 1 && j == 7 && id == 1){
                    for (int i = 1; i <= n; i ++){
                        _debug("stock_const[%d][%d] = %.2lf\n", i, j, stock_const[i][j]);
                    }
                    for (int i = 1; i <= n; i ++){
                        _debug("stock_x[%d][%d] = %.2lf\n", i, j, stock_x[i][j]);
                    }
                }
            }
        }
    }
    void init(){
        _debug("Job %d INIT:\n", id);
        _debug("Base Salary: %d + %d*X\n", D, C);
        _debug("Bonus: %d + %d*X\n", F, E);
        _debug("Stock: %d + %d*X / %d\n", H, G, I);
        _debug("Signon: %d + %d*X\n", B, A);
        _debug("Layoff: %d + %d*X\n", H, G);
        _debug("Compete: [%d, %d]\n", U, V);
        _debug("Compete Compensation: %d + %d*X\n", K, J);
        _debug("Alive: [%d, %d]\n", L, R);
        for (int i = 1; i <= m + 1; i ++) temp[i] = 1;
        for (int i = U; i <= V; i ++) temp[i] = 0;
        temp[id] = 0;
        for (int i = 1; i <= m + 1;){
            if (!temp[i]){
                i++;
                continue;
            }
            int j = i;
            while (j + 1 <= m && temp[j+1]) j ++;
            trans.push_back({i, j});
            i = j + 1;
        }

        init_stock();
    }
    db get_stock_income(int l, int r, int x){
        return stock_const[l][r] + stock_x[l][r] * x;
    }

    db get_income(int l, int r,int x){
        assert(L <= l && l <= r && r <= R);
        if (id == m + 1) return 0;
        db base = 1.0 * (D + C * x + 0.5 * (r - l) * C) * (r - l + 1);
        db bonus = 1.0 * (F + 0.5 * (r - l) * E) * (r - l + 1);
        db stock = get_stock_income(l, r, x);
        db signon = A * x + B;
        db layoff = 1.0 * (r - l + 2) / 12.0 * ((x + r - l)  * C + D);
        db cutoff = E*(r - l) + F;
        // verbose.push_back({id,l, r, x, base, bonus, stock, layoff, signon});
        _debug("[get_income(%d)(%d,%d,%d)]:\n base = %.2lf bonus = %.2lf stock = %.2lf signon = %.2lf layoff = %.2lf", id, l, r, x, base, bonus, stock, signon, layoff * (r == R));
        if (r == R){
            _debug("[cutoff] %.2lf", cutoff);
        }
        return base + bonus + stock + signon + (r == R ? (layoff - cutoff) : 0);
    }

    db get_compete(int l, int r){
        return (alive[r + 1][V] - alive[r + 1][U-1]) == 0 ? 0 : (r - l + 1) * J + K;
    }

} comp[maxn];
db dp[maxn][maxn][maxn];
db Events[maxn][maxn];
stack<pair<db, int>> stk;
int main(){
    // freopen("./sample.in", "r", stdin);
    // freopen(".//sample.out", "w", stdout);
    // x ??,??n?,m????
    cin>>x>>n>>m;
    for (int i = 1; i <= m; i ++){
        comp[i].input();
        comp[i].id = i;
        comp[i].init();
    }

    for (int j = 1; j <= m; j ++){
        for (int i = max(1, comp[j].L); i <= min(n + 1, comp[j].R); i ++){
            alive[i][j] ++;
        }
    }

    for (int i = 1; i <= n + 1; i ++){
        for (int j = 1; j <= m; j ++){
            alive[i][j] += alive[i][j-1];
        }
    }

    // «??????»
    comp[m + 1].L = 1;
    comp[m + 1].R = n + 1; 
    comp[m + 1].I = 1;
    comp[m+1].id = m + 1;
    comp[m+1].init();

    // for (int i = 1; i <= m + 1; i ++){
    //     _debug("trans for job %d\n", i);
    //     for (auto e : comp[i].trans){
    //         _debug("trans[%d,%d]\n", e.first, e.second);
    //     }
    // }

    for (int i = 0; i <= n + 1; i ++){
        for (int k = 0; k <= n; k ++){
            for (int j = 0; j <= m + 1; j ++){
                dp[i][k][j] = -1;
            }
        }
    }

    for (int j = 1; j <= m + 1; j ++){
        if (comp[j].L <= 1 && 1 <= comp[j].R){
            dp[1][0][j] = 0;
        }
    }

    // i??,???k?gap
    for (int i = 2; i <= n + 1; i ++){
        for (int k = 0; k <= i; k ++){
            for (int _ = 0; _ <= m + 1; _ ++){
                for (int __ = _; __ <= m + 1; __ ++){
                    Events[_][__] = -1;
                }
            }
            // ??????[pi, i-1],?j??
            for (int j = 1; j <= m + 1; j ++){
                if (i-1 < comp[j].L || i - 1 > comp[j].R) continue;
                for (int pi = max(1, comp[j].L); pi <= min(i-1, comp[j].R); pi ++){
                    int pk = k;
                    if (j == m + 1){
                        pk -= (i - pi);
                        if (pk < 0) continue;
                    }
                    int px = x + pi - 1 - pk;
                    //?????? dp[pi][pk][j]
                    if (dp[pi][pk][j] < 0) continue;
                    if (!(comp[j].L <= pi && comp[j].R >= i - 1)) continue;
                    _debug("trans from dp[%d][%d][%d] -> dp[%d][%d][..]", pi, pk, j, i, k);
                    db income = comp[j].get_income(pi, i - 1, px);
                    db val = dp[pi][pk][j] + income;
                    for (auto t : comp[j].trans){
                        _debug("update [%d,%d] with value %.2lf", t.first, t.second, val);
                        Events[t.first][t.second] = max(val, Events[t.first][t.second]);
                    }

                    // ????? 1.?? 2.????
                    if (i - 1 == n || i - 1 == comp[j].R){
                        db income_free = income;
                        val = dp[pi][pk][j] + income_free;
                        Events[1][m+1] = max(val, Events[1][m+1]);
                    }else{
                        // ??
                        db income_free = income + comp[j].get_compete(pi, i - 1);
                        val = dp[pi][pk][j] + income_free;
                        dp[i][k][m+1] = max(dp[i][k][m + 1], val);
                    }
                }
            }

            for (int lft = 0; lft <= m + 1; lft ++){
                while (!stk.empty()) stk.pop();
                for (int rgt = lft; rgt <= m + 1; rgt ++){
                    db val = Events[lft][rgt];
                    if (val >= 0){
                        while (!stk.empty() && stk.top().first <= val) stk.pop();
                        stk.push({val, rgt});
                    }
                }
                while (!stk.empty()){
                    int l, r;
                    db val;
                    tie(val, r) = stk.top();
                    stk.pop();
                    l = stk.empty() ? lft - 1 : stk.top().second;
                    for (int _ = l + 1; _ <= r; _ ++){
                        dp[i][k][_] = max(dp[i][k][_], val);
                    }
                }
            }

            for (int j = 1; j <= m; j ++){
                if (i < comp[j].L || i > comp[j].R){
                    dp[i][k][j] = -1;
                }
            }
        }
    }

    db ans = -1;
    for (int k = 0; k <= n; k ++){
        ans = max(ans, dp[n + 1][k][m + 1]);
    }

    // sort(verbose.begin(), verbose.end());
    // verbose.erase(unique(verbose.begin(), verbose.end()), verbose.end());
    // for (auto tp : verbose){
    //     int id, l, r, x;
    //     db base, bonus, stock, layoff, signon;
    //     tie(id, l, r, x, base, bonus, stock, layoff, signon) = tp;
    //     printf("[income(%d)] (%d,%d,%d) base = %.2lf bonus = %.2lf stock = %.2lf layoff = %.2lf signon = %.2lf\n", id, l, r, x, base, bonus, stock, layoff, signon);
    // }
    for (int i = 0; i <= n + 1; i ++)
        for (int k = 0; k <= i; k ++)
            for (int j = 0; j <= m + 1; j ++)
                if (dp[i][k][j] >= 0)
                    _debug("dp[%d][%d][%d]=%.2lf\n", i,k,j,dp[i][k][j]);

    printf("%.12lf\n", ans);
    // cout<<ans<<endl;
    return 0;
}
