#include <stdio.h>

#define SIZE 50000
#define INF 10000
#define INFLL 0xFFFFFFFFFFFFFFF
#define ll long long

#define scanf scanf_s

ll __max__(ll a, ll b)
{
	return (a > b) ? a : b;
}

ll __max__(ll a, ll b, ll c)
{
	return __max__(__max__(a, b), c);
}

int n, m, vect[SIZE], mod, tmp1, tmp2;

struct Node
{
	ll maxL, max, maxR, sum;

	Node(ll param = -INF)
	{
		maxL = max = maxR = sum = param;
	}

	void __Merge__(Node &L, Node &R)
	{
		maxL = __max__(L.maxL, L.sum + R.maxL);
		maxR = __max__(R.maxR, R.sum + L.maxR);
		max = __max__(L.max, R.max, L.maxR + R.maxL);
		sum = L.sum + R.sum;
	}

	static Node Merge(Node &L, Node &R)
	{
		Node Result;
		Result.__Merge__(L, R);
		return Result;
	}

	void SegmentReInit(ll param)
	{
		maxL = max = maxR = sum = param;
	}
} SegmentTree[4 * SIZE];


void buildTree(int vertix, int PosL, int PosR)
{
	if (PosL == PosR)
		SegmentTree[vertix].SegmentReInit(vect[PosL]);
	else
	{
		buildTree(2 * vertix, PosL, (PosL + PosR) / 2);
		buildTree(2 * vertix + 1, (PosL + PosR) / 2 + 1, PosR);

		SegmentTree[vertix].__Merge__(SegmentTree[2 * vertix], SegmentTree[2 * vertix + 1]);
	}
}

Node TreeNodeMax(int vertix, int PosL, int PosR, int L, int R)
{
	if (PosL == L && PosR == R) return SegmentTree[vertix];
	int PosMiddle = (PosL + PosR) / 2;

	if (L > PosMiddle) return TreeNodeMax(2 * vertix + 1, PosMiddle + 1, PosR, L, R);
	if (R <= PosMiddle) return TreeNodeMax(2 * vertix, PosL, PosMiddle, L, R);

	Node LeftNode = TreeNodeMax(2 * vertix, PosL, PosMiddle, L, PosMiddle),
		RightNode = TreeNodeMax(2 * vertix + 1, PosMiddle + 1, PosR, PosMiddle + 1, R);

	return Node::Merge(LeftNode, RightNode);
}


//#define scanf scanf_s

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", vect + i);

	buildTree(1, 0, n - 1);
	Node resultSegment;

	scanf("%d", &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &tmp1, &tmp2);

		resultSegment = TreeNodeMax(1, 0, n - 1, tmp1 - 1, tmp2 - 1);
		printf("%d\n", resultSegment.max);
	}

	return 0;
}