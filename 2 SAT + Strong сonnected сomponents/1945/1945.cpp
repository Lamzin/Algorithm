#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > g;
vector<int> tin, fup, ans;
int n, m, a, b, timer = 0;

void dfs(int v, int p = -1);

int main(){

	ios::sync_with_stdio(false);

	cin >> n >> m;
	g.resize(n, vector<int>());
	tin.resize(n, -1);
	fup.resize(n, -1);

	for (int i = 0; i < m; i++){
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	for (int i = 0; i < n; i++){
		if (tin[i] == -1){
			dfs(i);
		}
	}

	if (ans.size() == 0)
		cout << 0 << endl;
	else{
		sort(ans.begin(), ans.end());
		int cnt = 1;
		for (int i = 1; i < ans.size(); i++){
			if (ans[i] != ans[i - 1]) cnt++;
		}
		
		cout << cnt << endl;
		cout << ans[0] + 1<< endl;

		for (int i = 1; i < ans.size(); i++){
			if (ans[i] != ans[i - 1]){
				cout << ans[i] + 1 << endl;
			}
		}
			
	}

	return 0;
}

void dfs(int v, int p){
	int children = 0;
	tin[v] = fup[v] = timer++;

	for (int i = 0; i < g[v].size(); i++){
		int to = g[v][i];

		if (to == p) {
			continue;
		}
		else if (tin[to] != -1){
			fup[v] = min(fup[v], tin[to]);
		}
		else{
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if (fup[to] >= tin[v] && p != -1){
				ans.push_back(v);
			}
			children++;
		}
	}
	if (p == -1 && children > 1){
		ans.push_back(v);
	}
}