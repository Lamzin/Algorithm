#include <stdio.h>

#define scanf scanf_s

#define SIZE 1000000

int n, k;
int b, c;
char a;
long long fenwick[SIZE], arr[SIZE];

void update(int index, long long value){
	value -= arr[index];
	arr[index] += value;

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
	scanf("%d%d", &n, &k);

	while (k--){
		a = getchar();
		a = getchar();
		scanf("%d%d", &b, &c);
		if (a == 'A')
			update(b - 1, c);
		else
			printf("%lld\n", get(c - 1) - get(b - 2));
	}

	return 0;
}