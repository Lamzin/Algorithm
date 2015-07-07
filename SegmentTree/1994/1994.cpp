#include <stdio.h>
#include <string.h>
#include <algorithm>

#define SIZE 100000

#define scanf scanf_s
#define gets gets_s


using namespace std;

struct Node{
	int Min, Add;
	Node(int __min){
		Min = __min;
		Add = 0;
	}
	Node(){
		Min = 2 * SIZE;
		Add = 0;
	}
	Node(int __min, int __add){
		Min = __min;
		Add = __add;
	}
};

int n, test, index, m1, m2;
int mas[SIZE];
Node tree[4 * SIZE];
char str[SIZE];

void SegmentTreeBuild(int v, int tl, int tr);
int SegmentTreeFunction(int v, int tl, int tr, int l, int r);
void SegmentTreePush(int v);
void SegmentTreeAddValue(int v, int tl, int tr, int l, int r, int value);

int main(){
	gets(str);
	n = strlen(str);
	scanf("%d", &test);

	mas[0] = (str[0] == '(') ? 1 : -1;
	for (int i = 1, k; i < n; i++){
		(str[i] == '(') ? k = 1 : k = -1;
		mas[i] = mas[i - 1] + k;
	}

	SegmentTreeBuild(1, 0, n - 1);

	while (test--){
		scanf("%d", &index);
		if (str[index] == '('){
			SegmentTreeAddValue(1, 0, n - 1, index, n - 1, -2);
			str[index] = ')';
		}
		else{
			SegmentTreeAddValue(1, 0, n - 1, index, n - 1, 2);
			str[index] = '(';
		}

		m1 = SegmentTreeFunction(1, 0, n - 1, 0, n - 1);
		m2 = SegmentTreeFunction(1, 0, n - 1, n - 1, n - 1);
		if (m1 == m2 && m2 == 0)
			printf("+\n");
		else
			printf("-\n");
	}

	return 0;
}

void SegmentTreeBuild(int v, int tl, int tr){
	if (tr == tl) tree[v] = mas[tl];
	else{
		int middle = (tr + tl) / 2;
		SegmentTreeBuild(2 * v, tl, middle);
		SegmentTreeBuild(2 * v + 1, middle + 1, tr);
		tree[v].Min = min(tree[2 * v].Min, tree[2 * v + 1].Min);
	}
}

void SegmentTreeAddValue(int v, int tl, int tr, int l, int r, int value){
	if (l > r) return;
	else if (tl == l && tr == r){
		tree[v].Add += value;
		tree[v].Min += value;
	}
	else{
		int m = (tl + tr) / 2;
		SegmentTreePush(v);
		SegmentTreeAddValue(2 * v, tl, m, l, min(m, r), value);
		SegmentTreeAddValue(2 * v + 1, m + 1, r, max(m + 1, l), r, value);
		tree[v] = min(tree[2 * v].Min, tree[2 * v + 1].Min);
	}
}

void SegmentTreePush(int v){
	if (tree[v].Add){
		tree[2 * v].Add += tree[v].Add;
		tree[2 * v].Min += tree[v].Add;
		tree[2 * v + 1].Add += tree[v].Add;
		tree[2 * v + 1].Min += tree[v].Add;
		
		tree[v].Add = 0;
	}
}

int SegmentTreeFunction(int v, int tl, int tr, int l, int r){
	if (l > r) return 2 * SIZE;
	else if (tl == l && tr == r) return tree[v].Min;
	else{
		int m = (tl + tr) / 2;
		SegmentTreePush(v);
		
		return min(SegmentTreeFunction(2 * v, tl, m, l, min(m, r)), SegmentTreeFunction(2 * v + 1, m + 1, tr, max(m + 1, l), r));
	}
}