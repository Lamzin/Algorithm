#include <iostream>
#include <deque>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;

#define SIZE 50
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
string ss[SIZE];

void bfs();
ll find_flow();
void rebuild();
ll find_max_flow();

int main(){

	ios::sync_with_stdio(false);

	while(cin){
		cin >> n;
		if (cin){
			for (int i = 0; i < n; i++){
				cin >> ss[i];
			}

			ll min_flow = LL_MAX;
			for (int i = 0; i < n; i++){
				for (int j = i + 1; j < n; j++){
					source = i;
					dest = j;
					min_flow = min(min_flow, find_max_flow());
				}
			}

			cout << min_flow << endl;
		}
	}

	return 0;
}

ll find_max_flow(){

	max_flow = 0;

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			arr[i][j] = ss[i][j] - '0';
		}
	}

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

	return max_flow;
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