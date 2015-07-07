#include <stdio.h>

#define scanf scanf_s

#define SIZE 1000000

int n, k;
int b, c, tmp;
char a, tmpch;
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
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++){
		scanf("%d", &tmp);
		update(i, tmp);
	}

	while (k--){
		a = getchar();
		a = getchar();
		scanf("%d%d", &b, &c);
		if (a == '+')
			update(b - 1, c);
		else
			printf("%d\n", get(c - 1) - get(b - 2));
	}

	return 0;
}