#include <iostream>
#include <algorithm>

using namespace std;

#define SIZE 100000
#define SIZEln 20

int RMQ[SIZE][SIZEln], arr[SIZE], n, q, l, r;

void RMQPreprocessing();
int getRMQ(int left, int right);

int RMQ_main(){
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];
	
	RMQPreprocessing();

	cin >> q;
	for (int i = 0; i < q; i++){
		cin >> l >> r;
		cout << arr[getRMQ(l - 1, r - 1)] << endl;
	}

	return 0;
}

void RMQPreprocessing(){
	for (int i = 0; i < n; i++)
		RMQ[i][0] = i;

	int indexLeft, indexRight;
	for (int j = 1; (1 << j) <= n; j++){
		for (int i = 0; i + (1 << j) - 1 < n; i++){
			indexLeft  = RMQ[i][j - 1];
			indexRight = RMQ[i + (1 << (j - 1))][j - 1];

			RMQ[i][j] = (arr[indexLeft] < arr[indexRight]) ? indexLeft : indexRight;
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

	int indexleft  = RMQ[left][k];
	int indexright = RMQ[right - (1 << k) + 1][k];
	return (arr[indexleft] < arr[indexright]) ? indexleft : indexright;
}