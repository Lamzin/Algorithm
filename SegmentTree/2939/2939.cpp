#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

typedef long long ll;

#define MAXN 500001

struct node{
	ll add, sum;
	node(){
		add = -2000;
		sum = 0;
	}
	node(ll value){
		add = -1;
		sum = value;
	}
};

node tree[4 * MAXN];
ll arr[MAXN];

void SegmentTreeBuild(int vertex, int treeLeft, int treeRight){
	if (treeLeft == treeRight){
		tree[vertex].sum = arr[treeLeft];
		tree[vertex].add = -2000;
	}
	else{
		int middle = (treeLeft + treeRight) / 2;
		SegmentTreeBuild(vertex * 2, treeLeft, middle);
		SegmentTreeBuild(vertex * 2 + 1, middle + 1, treeRight);
		tree[vertex].sum = tree[vertex * 2].sum + tree[vertex * 2 + 1].sum;
	}
}

void SegmentTreePush(int vertex, int treeLeft, int treeRight){
	if (tree[vertex].add != -2000){
		int middle = (treeLeft + treeRight) / 2;
		tree[vertex * 2].add = tree[vertex].add;
		tree[vertex * 2 + 1].add = tree[vertex].add;

		tree[vertex * 2].sum = tree[vertex].add * (middle - treeLeft + 1);
		tree[vertex * 2 + 1].sum = tree[vertex].add * (treeRight - middle);

		tree[vertex].add = -2000;
	}
}

void SegmentTreeUpdate(int vertex, int treeLeft, int treeRight, int left, int right, ll value){
	if (left > right) return;
	else if (treeLeft == left && treeRight == right){
		tree[vertex].add = value;
		tree[vertex].sum = (treeRight - treeLeft + 1) * value;
	}
	else{
		int middle = (treeLeft + treeRight) / 2;
		SegmentTreePush(vertex, treeLeft, treeRight);
		SegmentTreeUpdate(vertex * 2, treeLeft, middle, left, min(middle, right), value);
		SegmentTreeUpdate(vertex * 2 + 1, middle + 1, treeRight, max(middle + 1, left), right, value);
		tree[vertex].sum = tree[vertex * 2].sum + tree[vertex * 2 + 1].sum;
	}
}

ll SegmentTreeFunction(int vertex, int treeLeft, int treeRight, int left, int right){
	if (left > right) return 0;
	else if (treeLeft == left && treeRight == right){
		return tree[vertex].sum;
	}
	else{
		int middle = (treeLeft + treeRight) / 2;
		SegmentTreePush(vertex, treeLeft, treeRight);
		return	SegmentTreeFunction(vertex * 2, treeLeft, middle, left, min(middle, right))
			+
			SegmentTreeFunction(vertex * 2 + 1, middle + 1, treeRight, max(middle + 1, left), right);
	}
}

int main(){
	ios::sync_with_stdio(false);

	int test, n, q, a, b;
	char type;
	ll c;

	cin >> n >> q;
	for (int i = 1; i <= n; i++) cin >> arr[i];

	SegmentTreeBuild(1, 1, n);

	while (q--){
		cin >> type;
		if (type == '?'){
			cin >> a >> b;
			cout << SegmentTreeFunction(1, 1, n, a, b) << endl;
		}
		else{
			cin >> a >> b >> c;
			SegmentTreeUpdate(1, 1, n, a, b, c);
		}
	}

	return 0;
}