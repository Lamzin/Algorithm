#include <iostream>
#include <vector>

using namespace std;

int n, m, a, b;
vector<vector<int> > g, g_t;
vector<int> list, used, color, toans;

void dfs(int v);
void dfs_t(int v, int clr);

int main(){

	ios::sync_with_stdio(false);
	cin >> n >> m;
	g.resize(n, vector<int>());
	g_t.resize(n, vector<int>());
	used.resize(n, 0);
	color.resize(n, -1);

	for (int i = 0; i < m; i++){
		cin >> a >> b;
		g[a - 1].push_back(b - 1);
		g_t[b - 1].push_back(a - 1);
	}

	for (int i = 0; i < n; i++){
		if (!used[i]){
			dfs(i);
		}
	}

	int color_cnt = 0;
	for (int i = list.size() - 1; i >= 0; i--){
		if (color[list[i]] == -1){
			dfs_t(list[i], color_cnt);
			color_cnt++;
		}
	}
	toans.resize(color_cnt, 1);

	for (int i = 0; i < n; i++){
		for (int j = 0; j < g[i].size(); j++){
			if (color[i] != color[g[i][j]]){
				toans[color[g[i][j]]] = 0;
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < toans.size(); i++){
		ans += toans[i];
	}

	cout << ans << endl;

	return 0;
}

void dfs(int v){
	used[v] = 1;
	for (int i = 0; i < g[v].size(); i++){
		if (!used[g[v][i]]){
			dfs(g[v][i]);
		}
	}
	list.push_back(v);
}

void dfs_t(int v, int clr){
	color[v] = clr;

	for (int i = 0; i < g_t[v].size(); i++){
		if (color[g_t[v][i]] == -1){
			dfs_t(g_t[v][i], clr);
		}
	}
}