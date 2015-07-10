#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<vector<int> > graph, RMQ;
vector<int> first, order, height_order;

typedef long long ll;

ll n, m, tmp, ans_cur = 0;
ll ans = 0, a1, a2, a3, a4, x, y, z;
string command;

void dfs(int vertex, int height);
void RMQPreprocessing();
int getRMQ(ll left, ll right);

int main(){

	ios::sync_with_stdio(false);

	cin >> n >> m;
	graph.resize(n, vector<int>());

	for (int i = 1; i < n; i++){
		cin >> tmp;
		graph[tmp].push_back(i);
	}

	cin >> a1 >> a2 >> x >> y >> z;

	first.resize(graph.size(), -1);
	dfs(0, 0);
	RMQPreprocessing();

	for (int i = 0; i < m; i++){
		ans_cur = order[getRMQ(first[(a1 + ans_cur) % n], first[a2])];
		ans += ans_cur;

		a3 = (x * a1 + y * a2 + z) % n;
		a4 = (x * a2 + y * a3 + z) % n;
		a1 = a3;
		a2 = a4;
	}

	cout << ans << endl;

	return 0;
}

void dfs(int vertex, int height){

	first[vertex] = order.size();
	order.push_back(vertex);
	height_order.push_back(height);


	for (int i = 0; i < graph[vertex].size(); i++){
		dfs(graph[vertex][i], height + 1);
		order.push_back(vertex);
		height_order.push_back(height);
	}

}

void RMQPreprocessing(){
	int n = height_order.size(), k = 1;
	while ((1 << k) <= n) k++;
	RMQ.resize(n, vector<int>(k));


	for (int i = 0; i < n; i++)
		RMQ[i][0] = i;


	int indexLeft, indexRight;
	for (int j = 1; (1 << j) <= n; j++){
		for (int i = 0; i + (1 << j) - 1 < n; i++){
			indexLeft = RMQ[i][j - 1];
			indexRight = RMQ[i + (1 << (j - 1))][j - 1];

			RMQ[i][j] = (height_order[indexLeft] < height_order[indexRight]) ? indexLeft : indexRight;
		}
	}

}

int getRMQ(ll left, ll right){

	if (left > right)
		swap(left, right);

	int k = 1;
	while ((1 << k) <= right - left + 1)
		k++;
	k--;

	int indexleft = RMQ[left][k];
	int indexright = RMQ[right - (1 << k) + 1][k];
	return (height_order[indexleft] < height_order[indexright]) ? indexleft : indexright;

}