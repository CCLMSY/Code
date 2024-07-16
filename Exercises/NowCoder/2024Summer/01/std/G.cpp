#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ull, ull> Pr;
const ll md = 998244353;
const int maxn = 2e5 + 50;
struct StrHash{
    ull p[maxn], h[maxn];
    int mod, buf;
    StrHash(int _buf, int _mod){
        buf = _buf;
        mod = _mod;
    }
    void Init(char *s, int n){
        p[0] = 1;
        h[0] = 0;
        for (int i = 1; i <= n; i++){
            p[i] = p[i - 1] * buf % mod;
            h[i] = (h[i - 1] * buf + s[i] - 'a' + 1) % mod;
        }
    }
    bool tl(int u, int v, int len){
        return (h[u] - h[v] + mod + (h[v - len] - h[u - len] + mod) * p[len] % mod) % mod == 0;
    }
    bool tr(int u, int v, int len){
        return (h[u + len - 1] - h[v + len - 1] + mod + (h[v - 1] - h[u - 1] + mod) * p[len] % mod) % mod == 0;
    }
    ull get(int l, int r){
        return (h[r] -h[l - 1] * p[r - l + 1] % mod + mod) % mod;
    }
} h1(103, 1e9+7), h2(105, 1e9+9);
char t[maxn];
int m;
int extl(int u, int v){
    if (t[u] != t[v])
        return 0;
    int l = 1, r = min(u, v), mid;
    while (l < r){
        mid = (l + r + 1) >> 1;
        if (h1.tl(u, v, mid) && h2.tl(u, v, mid))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}
int extr(int u, int v){
    if (t[u] != t[v])
        return 0;
    int l = 1, r = m - max(u, v) + 1, mid;
    while (l < r){
        mid = (l + r + 1) >> 1;
        if (h1.tr(u, v, mid) && h2.tr(u, v, mid))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}
struct Runs{
    int l, r, p;
};
struct Square{
    int r, len, cnt;
};
vector<Runs> raw_runs(0);
int chk(int u, int v){
    int tl = extl(u, v), tr = extr(u, v);
    if (tl + tr >= v - u + 1){
        raw_runs.push_back({u - tl + 1, v + tr - 1, v - u});
        return v + tr - 1;
    }
    return 0;
}
vector<Runs> getRuns(){
    vector<Runs> b(0);
    for (int p = 1; p <= m; p++)
        for (int k = p, mx = 0; k + p <= m; k += p)
            if (mx < k)
                mx = max(mx, chk(k, k + p) - p);
    sort(raw_runs.begin(), raw_runs.end(), [](const Runs &A, const Runs &B) { return A.l == B.l ? (A.r == B.r ? A.p < B.p : A.r < B.r) : A.l < B.l; });
    for (const Runs &r : raw_runs)
        if (b.empty() || r.l != b.back().l || r.r != b.back().r)
            b.push_back(r);
    return b;
}

struct Suffix_Automaton{
    // basic
    int nxt[maxn * 2][26], fa[maxn * 2], l[maxn * 2];
    int last, cnt;
    // extension
    int cntA[maxn * 2], A[maxn * 2]; /*??????*/
    int num[maxn * 2];               /*???????????????*/
    int pos[maxn];
    int match[maxn];
    int st[maxn * 2][20];
    Suffix_Automaton() { clear(); }
    void clear(){
        last = cnt = 1;
        fa[1] = l[1] = 0;
        memset(nxt[1], 0, sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            add(*s - 'a');
            s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt], 0, sizeof nxt[cnt]);
        l[np] = l[p] + 1;
        last = np;
        while (p && !nxt[p][c]) nxt[p][c] = np, p = fa[p];
        if (!p) fa[np] = 1;
        else{
            int q = nxt[p][c];
            if (l[q] == l[p] + 1) fa[np] = q;
            else{
                int nq = ++cnt;
                l[nq] = l[p] + 1;
                memcpy(nxt[nq], nxt[q], sizeof(nxt[q]));
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while (nxt[p][c] == q) nxt[p][c] = nq, p = fa[p];
            }
        }
    }
    void build(char *s, int n){
        // memset(cntA, 0, sizeof cntA);
        // memset(num, 0, sizeof num);
        for (int i = 1; i <= cnt; i++) cntA[l[i]]++;
        for (int i = 1; i <= cnt; i++) cntA[i] += cntA[i - 1];
        for (int i = cnt; i >= 1; i--) A[cntA[l[i]]--] = i;
        /*??????*/
        int temp = 1;
        for (int i = 1; i <= n; i++){
            num[temp = nxt[temp][s[i] - 'a']] = 1;
        }
        /*????*/
        for (int i = cnt; i >= 1; i--){
            int x = A[i];
            num[fa[x]] += num[x];
        }

        for (int i = 1; i <= cnt; i ++){
            int x = A[i];
            st[x][0] = fa[x];
            for (int j = 1; j < 20 && st[x][j-1]; j ++){
                st[x][j] = st[st[x][j-1]][j-1];
            }
        }
    }
    void run(char *s, int n){
        int temp = 1;
        int len = 0;
        for (int i = 1; i <= n; i ++){
            while (temp != 1 && !nxt[temp][s[i] - 'a']){
                temp = fa[temp];
                len = min(len, l[temp]);
            }
            if (nxt[temp][s[i] - 'a']){
                temp = nxt[temp][s[i] - 'a'];
                len++;
            }
            pos[i] = temp; 
            match[i] = len;
        }
    }
    int get(int r, int len){
        int temp = pos[r];
        //printf("temp=%d\n", temp);
        //printf("match=%d\n", match[r]);
        if (match[r] < len) return 0;
        if (len > l[fa[temp]]){
            return num[temp];
        }
        for (int j = 19; j >=0; j--){
            int nxt = st[temp][j];
            if (nxt == 0) continue;
            if (l[nxt] >= len){
                temp = nxt;
            }
            //printf("temp=%d\n", temp);
        }
        //cerr<<len <<" "<< l[fa[temp]] <<" "<< l[temp]<<endl;
        assert(len > l[fa[temp]] && len <= l[temp]);
        return num[temp];
    }
    void debug(){
        for (int i = 1; i <= cnt; i++){
            printf("[debug] %d: fa=%d, l=%d, num=%d\n", i, fa[i], l[i], num[i]);
        }

        for (int i = 1; i <= cnt; i++){
            printf("[debug] %d: ", i);
            for (int j = 0; j < 26; j++){
                if (nxt[i][j]){
                    printf("%c->%d, ", j + 'a', nxt[i][j]);
                }
            }
            printf("\n");
        }

        for (int i = 1; i <= cnt; i ++){
            for (int j = 0; j < 20 && st[i][j]; j ++){
                printf("[debug] %d: st[%d][%d]=%d\n", i, i, j, st[i][j]);
            }
        }
    }
} sam;
map<Pr,Square> square;
long long solve(char *s){
    int n = strlen(s + 1);
    sam.init(s + 1);
    sam.build(s, n);
    sam.run(t, m);
    //sam.debug();
    long long ans = 0;
    for (auto pr : square){
    //    cerr<<"working: "<<pr.second.r<<" "<<pr.second.len<<" "<<pr.second.cnt<<endl;
        ans += 1ll * pr.second.cnt * sam.get(pr.second.r, pr.second.len) % md;
    }

    return ans % md;
}
char s[maxn];
int main(){
    int tot = 0;
    scanf("%s", s + 1);
    scanf("%s", t + 1);
    m = strlen(t + 1);
    h1.Init(t, m);
    h2.Init(t, m);
    vector<Runs> runs = getRuns();
    // for (const Runs &run : runs){
    //     int l = run.l, r = run.r, p = run.p;
    //     cout<<l<<" "<<r<<" "<<p<<endl;
    // }
    // cout<<runs.size()<<endl;
    for (const Runs &run : runs){
        int l = run.l, r = run.r, p = run.p;
        for (int len = 2 * p; len <= r - l + 1; len += 2 * p){
            for (int i = l; i + len - 1 <= r && i < l + p; i++){
                int j = i + len - 1;
                Pr now = {h1.get(i, j), h2.get(i, j)};
                if (square.find(now) == square.end()){
                    square[now] = {j, len/2, (r - j) / p + 1};
                }else{
                    square[now].cnt += (r - j) / p + 1;
                }
            }
        }
    }

   // cout<<square.size()<<endl;
    cout<<solve(s);
    
    return 0;
}
