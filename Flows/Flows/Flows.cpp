#include <iostream>
#include <deque>
#include <string.h>
#include <algorithm>
#include <fstream>

using namespace std;

#define SIZE 100
#define LL_MAX 1152921504606846976
#define cin in
#define cout out


typedef long long ll;


fstream in("input.txt", ios::in);
fstream out("output.txt", ios::out);

deque <ll> que;

int n, m, a, b, c;
ll arr[SIZE][SIZE];
ll max_flow = 0, current_flow;
int source, dest;
int parent[SIZE], used[SIZE];

void bfs();
ll find_flow();
void rebuild();

int main(){

	cin >> n >> m;
	for (int i = 0; i < m; i++){
		cin >> a >> b >> c;
		a--;
		b--;
		arr[a][b] += c;
		arr[b][a] += c;
	}

	source = 0;
	dest = n - 1;

	while (true){
		que.clear();
		memset(parent, -1, sizeof(parent));
		memset(used, 0, sizeof(parent));

		bfs();
		current_flow = find_flow();
		if (current_flow == LL_MAX){
			break;
		}

		max_flow += current_flow;
		rebuild();
	}

	cout << max_flow << endl;

	return 0;
}

void bfs(){
	int i, top;
	que.push_front(source);

	while (!que.empty()){
		top = que.front();
		if (top == dest) return;

		que.pop_front();
		used[top] = true;

		for (i = 0; i < n; i++){
			if (arr[top][i] > 0 && !used[i]){
				parent[i] = top;
				que.push_back(i);
			}
		}
	}
}

ll find_flow(){
	if (parent[dest] == -1) return LL_MAX;

	ll res = LL_MAX;
	int current_index = dest;

	while (parent[current_index] != -1){
		res = min(res, arr[parent[current_index]][current_index]);
		current_index = parent[current_index];
	}

	return res;
}

void rebuild(){
	int current_index = dest;
	int to;

	while (parent[current_index] != -1){
		to = parent[current_index];
		arr[current_index][to] += current_flow;
		arr[to][current_index] -= current_flow;
		current_index = to;
	}

}