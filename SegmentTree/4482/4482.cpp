#include <stdio.h>
#include <algorithm>

#define SIZE 1001000
#define MAX 1000000001
#define MIN -1

#define scanf scanf_s

using namespace std;

struct Node{
	int Min, Max;
	Node(int __min, int __max) : Min(__min), Max(__max){}
	Node(int param){
		Min = Max = param;
	}
	Node(){
		Min = MAX;
		Max = MIN;
	}
	Node(Node a, Node b){
		Min = min(a.Min, b.Min);
		Max = max(a.Max, b.Max);
	}
};

int n, m, a, b, c;
int mas[SIZE];
Node tree[4 * SIZE];

void SegmentTreeBuild(int v, int tl, int tr);
void SegmentTreeUpdate(int v, int tl, int tr, int pos, int new_val);
Node SegmentTreeFunction(int v, int tl, int tr, int l, int r);

int main(){
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", mas + i);

	SegmentTreeBuild(1, 0, n - 1);

	scanf("%d", &m);
	while (m--){
		scanf("%d%d%d", &a, &b, &c);
		if (a == 1){
			Node tmp = SegmentTreeFunction(1, 0, n - 1, b - 1, c - 1);
			if (tmp.Min == tmp.Max)
				printf("draw\n");
			else
				printf("wins\n");
		}
		else
			SegmentTreeUpdate(1, 0, n - 1, b - 1, c);
	}

	return 0;
}

void SegmentTreeBuild(int v, int tl, int tr){
	if (tr == tl) tree[v] = Node(mas[tr]);
	else{
		int middle = (tr + tl) / 2;
		SegmentTreeBuild(2 * v, tl, middle);
		SegmentTreeBuild(2 * v + 1, middle + 1, tr);
		tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
	}
}

void SegmentTreeUpdate(int v, int tl, int tr, int pos, int new_val){
	if (tl == tr) tree[v] = Node(new_val);
	else{
		int m = (tl + tr) / 2;
		if (pos <= m)
			SegmentTreeUpdate(2 * v, tl, m, pos, new_val);
		else
			SegmentTreeUpdate(2 * v + 1, m + 1, tr, pos, new_val);

		tree[v] = Node(tree[2 * v], tree[2 * v + 1]);
	}
}

Node SegmentTreeFunction(int v, int tl, int tr, int l, int r){
	if (l > r) return Node();
	else if (tl == l && tr == r) return tree[v];
	else{
		int m = (tl + tr) / 2;
		return Node(SegmentTreeFunction(2 * v, tl, m, l, min(m, r)), SegmentTreeFunction(2 * v + 1, m + 1, tr, max(m + 1, l), r));
	}
}