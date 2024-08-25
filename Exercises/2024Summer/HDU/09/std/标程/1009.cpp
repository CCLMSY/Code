#include<bits/stdc++.h>

#define ll long long

struct Node{
	int k;
	int b;

	ll get(ll x){
		return x * k + b;
	}
}s[100010], s2[100010];

bool cmp(Node a, Node b){
    if(a.k == b.k)
        return a.b > b.b;
	return a.k > b.k;
}

std::pair<ll, int> tmp[3];
int convex[3][100010], convex_top[3];
bool inc[100010];

bool better(Node a, Node b, Node c){
	// (b2 - b1) / (k1 - k2) > (b3 - b1) / (k1 - k3)
	// (b2 - b1) * (k1 - k3) > (b3 - b1) * (k1 - k2)
	return 1ll * (b.b - a.b) * (a.k - c.k) > 1ll * (c.b - a.b) * (a.k - b.k);
}
int main(){
    // freopen("1.in", "r", stdin);
	std::ios::sync_with_stdio(false);
	int T;
	std::cin >> T;
	s[0] = (Node){0, 0};
	while(T--){
		convex_top[0] = convex_top[1] = convex_top[2] = 0;
		int n, k;
		std::cin >> n >> k;
		for(int i = 1; i <= n; i++){
			std::cin >> s[i].b >> s[i].k;
			inc[i] = false;
		}
		std::sort(s + 1, s + n + 1, cmp);
		ll max = -1;
		inc[1] = true;
		for(int i = 1; i <= n; i++){
			if(s[i].b > max){
				max = s[i].b;
				while(better(s[i], s[convex[0][convex_top[0]]], s[convex[0][convex_top[0] - 1]]) && convex_top[0] >= 2)
					convex_top[0]--;
				convex[0][++convex_top[0]] = i;
			}
		}
		for(int i = 1; i <= convex_top[0]; i++)
			inc[convex[0][i]] = true;
		max = -1;
		for(int i = 1; i <= n; i++){
			if(!inc[i]){
				if(s[i].b > max){
					max = s[i].b;
					while(better(s[i], s[convex[1][convex_top[1]]], s[convex[1][convex_top[1] - 1]]) && convex_top[1] >= 2)
						convex_top[1]--;
					convex[1][++convex_top[1]] = i;
				}
			}
		}
        
		for(int i = 1; i <= convex_top[1]; i++)
			inc[convex[1][i]] = true;
		max = -1;
		for(int i = 1; i <= n; i++){
			if(!inc[i]){
				if(s[i].b > max){
					max = s[i].b;
					while(better(s[i], s[convex[2][convex_top[2]]], s[convex[2][convex_top[2] - 1]]) && convex_top[2] >= 2)
						convex_top[2]--;
					convex[2][++convex_top[2]] = i;
				}
			}
		}


		max = 0;
		int max_pos = -1;
		ll sec = 0;
		int sec_pos = -1;

		int cur0 = convex_top[0];
		int cur1 = convex_top[1];
        int cur2 = convex_top[2];

		// for(int i = 1; i <= convex_top[0]; i++)
		// 	printf("%d, ", convex[0][i]);
		// printf("\n");

        std::vector<std::pair<ll, int> > vec;
		for(int i = 1; i <= k; i++){
            vec.clear();

			while(cur0 > 1 && s[convex[0][cur0]].get(i) <= s[convex[0][cur0 - 1]].get(i))
				cur0--;
			while(cur1 > 1 && s[convex[1][cur1]].get(i) <= s[convex[1][cur1 - 1]].get(i))
				cur1--;
			while(cur2 > 1 && s[convex[1][cur2]].get(i) <= s[convex[2][cur2 - 1]].get(i))
				cur2--;

            for(int j = cur0 - 2; j <= cur0 + 2; j++)
                if(j > 0 && j <= convex_top[0])
                    vec.push_back(std::make_pair(s[convex[0][j]].get(i), convex[0][j]));
            
            for(int j = cur1 - 1; j <= cur1 + 1; j++)
                if(j > 0 && j <= convex_top[1])
                    vec.push_back(std::make_pair(s[convex[1][j]].get(i), convex[1][j]));
            vec.push_back(std::make_pair(s[convex[2][cur2]].get(i), convex[2][cur2]));

            // printf("cur0 = %d, cur1 = %d, cur2 = %d\n", cur0, cur1, cur2);
            std::sort(vec.begin(), vec.end(), std::greater<std::pair<ll, int> >());
            // for(auto it : vec)
            //     printf("{%lld, %d}\n", it.first, it.second);

			// printf("cmax = %lld, cmax_pos = %d | csec = %lld, csec_pos = %d\n", cmax, cmax_pos, csec, csec_pos);

            for(int j = 0; j <= 2; j++)
                tmp[j] = std::make_pair(((vec[j].second != max_pos) ? (max + vec[j].first) : (sec + vec[j].first)), vec[j].second);
            std::sort(tmp, tmp + 3, std::greater<std::pair<ll, int> >());
			max = tmp[0].first;
			max_pos = tmp[0].second;
			sec = tmp[1].first;
			sec_pos = tmp[1].second;

			// printf("max = %lld, max_pos = %d, sec = %lld, sec_pos = %d\n", max, max_pos, sec, sec_pos);
		}

		std::cout << max << '\n';
	}
}