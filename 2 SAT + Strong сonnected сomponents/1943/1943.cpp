#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > g, numb;
vector<int> tin, fup, ans;
int n, m, a, b, timer = 0;

void dfs(int v, int p = -1);

int main(){

	ios::sync_with_stdio(false);

	cin >> n >> m;
	g.resize(n, vector<int>());
	numb.resize(n, vector<int>());
	tin.resize(n, -1);
	fup.resize(n, -1);

	for (int i = 1; i <= m; i++){
		cin >> a >> b;
		a--;
		b--;
		g[a].push_back(b);
		g[b].push_back(a);
		numb[a].push_back(i);
		numb[b].push_back(i);
	}

	for (int i = 0; i < n; i++){
		if (tin[i] == -1){
			dfs(i);
		}
	}

	sort(ans.begin(), ans.end());

	if (ans.size() == 0) 
		cout << 0 << endl << endl;
	else{
		cout << ans.size() << endl << ans[0];
		for (int i = 1; i < ans.size(); i++)
			cout << " " << ans[i];
		cout << endl;
	}


	return 0;
}

void dfs(int v, int p){
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
			if (fup[to] > tin[v]){
				ans.push_back(numb[v][i]);
			}
		}
	}
}