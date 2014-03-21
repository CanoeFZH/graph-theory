#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int N = 512;
const int INF = 1 << 30;

vector <int> E[N];
int out[N], in[N], loop[N];
int match[N], vis[N], stamp;

int find(int u) {
	if (vis[u] == stamp) {
		return 0;
	}
	vis[u] = stamp;
	for (int v: E[u]) {
		if (match[v] == -1 || find(match[v])) {
			match[v] = u;
			return 1;
		}
	}
	return 0;
}

int matching(int n) {
	memset(match, -1, sizeof(match));
	int ret = 0;
	for (int i = 0; i < n; i++) {
		++stamp;
		ret += find(i);
	}
	return ret;
}

int main() {
    int n, m;
    vector <pair <int, int> > raw_edges;
    while (cin >> n >> m) {
        raw_edges.clear();
        memset(in, 0, sizeof(in));
        memset(out, 0, sizeof(out));
        memset(loop, 0, sizeof(loop));
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            raw_edges.push_back(make_pair(u, v));
            if (u != v) {
                out[u]++;
                in[v]++;
            } else {
                loop[u]++;
            }
        }
        int ans = INF;
        for (int i = 0; i < n; i++) {
            int change_number = m + 2 * n - 1 - 2 * in[i] - 2 * out[i] - 2 * loop[i];
            for (int j = 0; j < n; j++) {
                E[j].clear();
            }
            for (int j = 0; j < m; j++) {
                int u = raw_edges[j].first, v = raw_edges[j].second;
                if (u == i || v == i) {
                    continue;
                } 
                u -= u > i ? 1 : 0;
                v -= v > i ? 1 : 0;
                E[u].push_back(v);
            }
            int match_number = matching(n - 1);
            change_number += n - 1 - 2 * match_number;
            ans = min(ans, change_number);
        }
        cout << ans << endl;
    }
    return 0;
}
