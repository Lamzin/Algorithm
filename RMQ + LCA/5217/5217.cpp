#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <map>

using namespace std;

vector<vector<int> > graph, RMQ;
vector<int> first, order, height_order;
queue<pair<int, int> > get_LCA_queue;
map<int, int> vertex_index, vertex_index_old;

int q, a, b;
string command;

void dfs(int vertex, int height);
void RMQPreprocessing();
int getRMQ(int left, int right);

int main(){

	ios::sync_with_stdio(false);


	cin >> q;

	while (q--){
		cin >> command >> a >> b;


		if (vertex_index.find(a) == vertex_index.end()){
			vertex_index[a] = graph.size();
			vertex_index_old[graph.size()] = a;
			graph.push_back(vector<int>());
		}
		if (vertex_index.find(b) == vertex_index.end()){
			vertex_index[b] = graph.size();
			vertex_index_old[graph.size()] = b;
			graph.push_back(vector<int>());
		}
		a = vertex_index[a];
		b = vertex_index[b];


		if (command == "ADD"){
			graph[a].push_back(b);
		}
		else if (command == "GET"){
			get_LCA_queue.push(make_pair(a, b));
		}

	}


	first.resize(graph.size(), -1);
	dfs(0, 0);
	RMQPreprocessing();


	while (!get_LCA_queue.empty()){
		auto top = get_LCA_queue.front();
		get_LCA_queue.pop();

		cout << vertex_index_old[order[getRMQ(first[top.first], first[top.second])]] << endl;
	}

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

int getRMQ(int left, int right){

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