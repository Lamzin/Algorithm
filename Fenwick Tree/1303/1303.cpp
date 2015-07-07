#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

#define SIZE 500000

int n, k;
int b, c;
char a;
int fenwick[SIZE], arr[SIZE], tmp;
long long ans = 0;

void update(int index, int value){
	while (index < n){
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

	while (scanf("%d", &n) && n){
		for (int i = 0; i < n; i++){
			scanf("%d", arr + i);
			fenwick[i] = arr[i];
		}
		sort(fenwick, fenwick+ n);

		for (int i = 0; i < n; i++){
			arr[i] = lower_bound(fenwick, fenwick+ n, arr[i]) - fenwick;
		}
		memset(fenwick, 0, n * sizeof(int));

		ans = 0;
		for (int i = n - 1; i >= 0; i--){
			ans += get(arr[i]);
			update(arr[i], 1);
		}

		printf("%lld\n", ans);
	}

	return 0;
}