#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

#define SIZE 1000001

int n, k;
int b, c;
char a;
long long fenwick[SIZE], tmp;
long long ans = 0;

void update(int index, int value){
	while (index < SIZE){
		fenwick[index] += value;
		index |= index + 1;
	}
}

int G(int x){
	return x & (x + 1);
}

long long get(int index){
	long long result = 0;
	while (index >= 0){
		result += fenwick[index];
		index = G(index) - 1;
	}
	return result;
}

int main(){
	ios::sync_with_stdio(false);

	int test;
	cin >> test;
	while (test--){
		cin >> n;
		memset(fenwick, 0, SIZE * sizeof(long long));
		ans = 0;

		for (int i = 0; i < n; i++){
			cin >> tmp;
			update(tmp, tmp);
			ans += get(tmp - 1);
		}
		
		cout << ans << endl;
	}

	return 0;
}