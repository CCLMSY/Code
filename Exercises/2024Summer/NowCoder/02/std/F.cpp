#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
const int MAXN = 500005;
int temp[MAXN];
struct ALL_BINARY_ANS
{
    long long sumw{};
    long long sumv{};
    pair<int, int> line{};
};

class LINE_DISCRETIZATIONER
{
   private:
    vector<pair<int, int>> _data;
    unordered_map<i64, int> _mp;

    static i64 _h(pair<int, int> p)
    {
        return 2000000000LL * p.first + p.second;
    }

   public:
    void discretized(bool fn(const pair<int, int>&, const pair<int, int>&))
    {
        sort(_data.begin(), _data.end(), fn);
        for (int i = 0; i < _data.size(); ++i)
        {
            _mp[_h(_data[i])] = i;
        }
    }

    void add(const pair<int, int>& x)
    {
        _data.push_back(x);
    }

    pair<int, int> operator()(int x)
    {
        return _data[x];
    }

    int operator()(const pair<int, int>& x)
    {
        return _mp[_h(x)];
    }

    size_t size()
    {
        return _data.size();
    }
};

struct
{
    int l, r, L, R;
} a[MAXN];
struct ALL_BINARY_DATA
{
    int op;  //1修改 2查询
    union
    {
        struct
        {
            int l, r;              //查询的区间是lr
            i64 w;                 //查询的水分是w
            ALL_BINARY_ANS* data;  //数据
        } query;
        struct
        {
            int pos;      //第几个位置
            int line_id;  //线id
            int w;        //水分w
            int v;        //糖分v
        } modify;
    };
};

struct QUERY
{
    i64 w, v;
    bool flag;

    QUERY() = default;

    QUERY(i64 _w, i64 _v, bool _flag) : w(_w), v(_v), flag(_flag) {}

    ALL_BINARY_ANS l;
    ALL_BINARY_ANS r;
};

vector<QUERY> Q;
struct
{
    int op;
    int x, l, r, L, R;
} input[MAXN];

class BIT
{
   private:
    vector<i64> _data;
    vector<unsigned char> _vis;
    vector<unsigned int> _stk;
    unsigned int _top;

    int lowbit(int x)
    {
        return x & -x;
    }

   public:
    void clear()
    {
        while (_top)
        {
            _vis[_stk[_top]] = 0;
            _data[_stk[_top]] = 0;
            _top--;
        }
    }

    explicit BIT(size_t sz)
    {
        _data.resize(sz + 1);
        _stk.resize(sz + 1);
        _vis.resize(sz + 1);
        _top = 0;
    }

    void add(int x, i64 v)
    {
        while (x < _data.size())
        {
            _data[x] += v;
            if (!_vis[x])
            {
                _vis[x] = 1;
                _stk[++_top] = x;
            }
            x += lowbit(x);
        }
    }

    i64 operator()(int x)
    {
        i64 ans = 0;
        while (x)
        {
            ans += _data[x];
            x -= lowbit(x);
        }
        return ans;
    }

    i64 operator()(int l, int r)
    {
        return this->operator()(r) - this->operator()(l - 1);
    }
};

int n, m, q;
int bl;
ALL_BINARY_DATA buffer[MAXN << 3];

long long div_up(long long x, long long y)
{
    return (x + y - 1) / y;
}

void add_binary_query(const ALL_BINARY_DATA& data, queue<ALL_BINARY_DATA*>& que)
{
    buffer[bl] = data;
    que.push(&buffer[bl]);
    bl++;
}

void all_binary(int l, int r, queue<ALL_BINARY_DATA*>& que, BIT& bit_w,
                BIT& bit_v, LINE_DISCRETIZATIONER& lines)
{
    //cout << "all binary " << l << " " << r << endl;
    if (l == r)
    {
        while (!que.empty())
        {
            auto now = que.front();
            que.pop();
            if (now->op == 2)
            {
                now->query.data->line = lines(l);
            }
        }
        return;
    }
    queue<ALL_BINARY_DATA*> quel;
    queue<ALL_BINARY_DATA*> quer;
    int mid = (l + r) >> 1;
    bit_w.clear();
    bit_v.clear();
    while (!que.empty())
    {
        auto now = que.front();
        que.pop();
        if (now->op == 1)
        {
            if (now->modify.line_id <= mid)
            {
                bit_w.add(now->modify.pos, now->modify.w);
                bit_v.add(now->modify.pos, now->modify.v);
                //cout << "add " << now->modify.w << endl;
                quel.push(now);
            }
            else
            {
                quer.push(now);
            }
        }
        else
        {
            auto check_ans = bit_w(now->query.l, now->query.r);
            /*
			cout << "get ans " << check_ans << endl;
            cout << "w " << now->query.w << endl;
			*/
            if (check_ans < now->query.w)
            {
                now->query.w -= check_ans;
                now->query.data->sumw += check_ans;
                now->query.data->sumv += bit_v(now->query.l, now->query.r);
                quer.push(now);
            }
            else
            {
                quel.push(now);
            }
        }
    }
    all_binary(l, mid, quel, bit_w, bit_v, lines);
    all_binary(mid + 1, r, quer, bit_w, bit_v, lines);
}

int main()
{
    queue<ALL_BINARY_DATA*> q_max, q_min;
    LINE_DISCRETIZATIONER line_max, line_min;
    scanf("%d %d", &n, &q);
    BIT bit_v(n), bit_w(n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d %d %d %d", &a[i].l, &a[i].r, &a[i].L, &a[i].R);
        line_max.add(make_pair(a[i].l, a[i].R));
        line_min.add(make_pair(a[i].r, a[i].L));
        temp[i] = a[i].r;
        bit_w.add(i, a[i].r);
    }
    line_max.add(make_pair(1000000000, 0));
    for (int i = 1; i <= q; ++i)
    {
        scanf("%d", &input[i].op);
        if (input[i].op == 1)
        {
            scanf("%d", &input[i].x);
            scanf("%d %d %d %d", &input[i].l, &input[i].r, &input[i].L,
                  &input[i].R);
            bit_w.add(input[i].x, -temp[input[i].x]);
            temp[input[i].x] = input[i].r;
            bit_w.add(input[i].x, temp[input[i].x]);
            line_max.add(make_pair(input[i].l, input[i].R));
            line_min.add(make_pair(input[i].r, input[i].L));
        }
        else
        {
            scanf("%d %d %d %d", &input[i].l, &input[i].r, &input[i].L,
                  &input[i].R);
            Q.emplace_back(input[i].L, input[i].R, false);
            if (bit_w(input[i].l, input[i].r) < input[i].L)
            {
                Q.rbegin()->flag = true;
            }
        }
    }
    bit_v.clear();
    line_max.discretized(
        [](const pair<int, int>& A, const pair<int, int>& B)
        {
            return 1ll * A.second * B.first > 1ll * B.second * A.first;
        });
    line_min.discretized(
        [](const pair<int, int>& A, const pair<int, int>& B)
        {
            return 1ll * A.second * B.first < 1ll * B.second * A.first;
        });
/*
    cout << "------max" << endl;
    for (int i = 0; i < line_max.size(); ++i)
    {
        cout << line_max(i).first << " " << line_max(i).second << endl;
    }
    cout << "------min" << endl;
    for (int i = 0; i < line_min.size(); ++i)
    {
        cout << line_min(i).first << " " << line_min(i).second << endl;
    }
	*/
    //---------------------
    for (int i = 1; i <= n; ++i)
    {
        ALL_BINARY_DATA all_binary_data;
        all_binary_data.op = 1;
        all_binary_data.modify.pos = i;
        all_binary_data.modify.w = a[i].l;
        all_binary_data.modify.v = a[i].R;
        all_binary_data.modify.line_id = line_max(make_pair(a[i].l, a[i].R));
        buffer[bl] = all_binary_data;
        add_binary_query(all_binary_data, q_max);
        all_binary_data.modify.w = a[i].r;
        all_binary_data.modify.v = a[i].L;
        all_binary_data.modify.line_id = line_min(make_pair(a[i].r, a[i].L));
        add_binary_query(all_binary_data, q_min);
    }
    for (int i = 1; i <= q; ++i)
    {
        if (input[i].op == 1)
        {
            ALL_BINARY_DATA all_binary_data{};
            all_binary_data.op = 1;
            all_binary_data.modify.pos = input[i].x;
            all_binary_data.modify.w = -a[input[i].x].l;
            all_binary_data.modify.v = -a[input[i].x].R;
            all_binary_data.modify.line_id =
                line_max(make_pair(a[input[i].x].l, a[input[i].x].R));
            add_binary_query(all_binary_data, q_max);
            all_binary_data.modify.w = -a[input[i].x].r;
            all_binary_data.modify.v = -a[input[i].x].L;
            all_binary_data.modify.line_id =
                line_min(make_pair(a[input[i].x].r, a[input[i].x].L));
            add_binary_query(all_binary_data, q_min);

            a[input[i].x].l = input[i].l;
            a[input[i].x].r = input[i].r;
            a[input[i].x].L = input[i].L;
            a[input[i].x].R = input[i].R;

            all_binary_data.modify.w = a[input[i].x].l;
            all_binary_data.modify.v = a[input[i].x].R;
            all_binary_data.modify.line_id =
                line_max(make_pair(a[input[i].x].l, a[input[i].x].R));
            add_binary_query(all_binary_data, q_max);
            all_binary_data.modify.w = a[input[i].x].r;
            all_binary_data.modify.v = a[input[i].x].L;
            all_binary_data.modify.line_id =
                line_min(make_pair(a[input[i].x].r, a[input[i].x].L));
            add_binary_query(all_binary_data, q_min);
        }
        else
        {
            if (!Q[m].flag)
            {
                ALL_BINARY_DATA all_binary_data{};
                all_binary_data.op = 2;
                all_binary_data.query.data = &Q[m].r;
                all_binary_data.query.l = input[i].l;
                all_binary_data.query.r = input[i].r;
                all_binary_data.query.w = input[i].L;
                add_binary_query(all_binary_data, q_max);
                all_binary_data.query.data = &Q[m].l;
                add_binary_query(all_binary_data, q_min);
            }
            m++;
        }
    }
    //cout << "ab ------max" << endl;
    all_binary(0, (int)line_max.size() - 1, q_max, bit_w, bit_v, line_max);
    //cout << "ab ------min" << endl;
    all_binary(0, (int)line_min.size() - 1, q_min, bit_w, bit_v, line_min);
    for (auto& i : Q)
    {
        if (i.flag)
        {
            printf("No\n");
            continue;
        }
        //i.l.sumv+i.l.line.second/i.l.line.first*(i.w-i.l.sumw)<=i.v
        //i.r.sumv+i.r.line.second/i.r.line.first*(i.w-i.r.sumw)>=i.v
        if (i.l.sumv + div_up((i.w - i.l.sumw) * i.l.line.second,
                              i.l.line.first) <=
                i.v &&
            i.r.sumv + (i.w - i.r.sumw) * i.r.line.second / i.r.line.first >=
                i.v)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
		/*
        cout << "query " << i.w << " " << i.v << endl;
        cout << i.l.sumw << " " << i.l.sumv << " line:" << i.l.line.first << " "
             << i.l.line.second << endl;
        cout << i.r.sumw << " " << i.r.sumv << " line:" << i.r.line.first << " "
             << i.r.line.second << endl;
			 */
    }
}
/*
3 6
2 2 3 3
1 3 1 3
1 1 1 1
1 3 4 5 6 7
2 1 1 1 2
2 1 1 2 3
2 1 3 5 9
2 1 3 7 10
2 1 3 10 11
 * */