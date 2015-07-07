#include <stdio.h>

using namespace std;

#define SIZE 20000
#define scanf scanf_s
#define what_is(x) cerr  << #x << ": " << (x) << endl;
int test, n, k, l, r, tmp, ans, ii;
int vect[SIZE], index[32];

int main(){
	scanf("%d", &test);

	while (test--){
		scanf("%d%d", &n, &k);
		for (int i = 0; i < n; i++)
			scanf("%d", vect + i);

		k = (k > n) ? n / 2 + 1 : k;
		l = -k; 
		r = k;
		for (int i = 0; i < 32; i++) index[i] = -2 * k; //INF;

		for (int i = l; i <= r; i++){
			ii = i % n;
			while (ii < 0) ii += n;
			tmp = vect[ii];

			for (int bit = 0; bit < 32; bit++)
				if (!((1 << bit) & tmp))
					index[bit] = i;
		}

		for (int i = 0; i < n; i++){
			ii = (r + 1) % n;
			while (ii < 0) ii += n;
			ans = 0;
			tmp = vect[ii]; // next number
			for (int bit = 0; bit < 32; bit++){
				if (index[bit] < l)
					ans += (1 << bit); // i-bit == 1 !!!
				if (!((1 << bit) & tmp))
					index[bit] = r + 1;
			}

			if (i) printf(" ");
			printf("%d", ans);
			l++;
			r++;
		}
		printf("\n");
	}

	return 0;
}