#include <stdio.h>

#define scanf scanf_s

#define SIZE 1000001

int n, k, kk, kkk;
int left, right, value;
char a;
int fenwick[SIZE];

void update(int index, int value){
	while (index < n){
		fenwick[index] += value;
		index |= index + 1;
	}
}

int G(int x){
	return x & (x + 1);
}

int get(int index){
	int result = 0;
	while (index >= 0){
		result += fenwick[index];
		index = G(index) - 1;
	}
	return result;
}

int main(){
	scanf("%d%d%d", &n, &kk, &kkk);
	k = kk + kkk;

	while (k--){
		a = getchar();
		a = getchar();
		if (a == 'A'){
			scanf("%d%d%d", &left, &right, &value);
			update(left, value);
			update(right + 1, -value);
		}
		else{
			scanf("%d", &value);
			printf("%d\n", get(value));
		}
	}

	return 0;
}