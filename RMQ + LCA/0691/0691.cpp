#include <fstream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

fstream in("input.txt", ios::in);
fstream out("output.txt", ios::out);

#define SIZE 100000
#define lnSIZE 30
#define what_is(x) out << #x << ": " << x << endl;

int n, m, u, v, ans;
int rmq[SIZE][lnSIZE], vect[SIZE];
int xx, yy, k;

void RMQPreprocessing();
int RMQ(int l, int r);

int main(){
	in >> n >> m >> vect[0] >> u >> v;
	
	for (int i = 1; i < n; i++)
		vect[i] = (23 * vect[i - 1] + 21563) % 16714589;

	RMQPreprocessing();

	RMQ(0, 1);

	ans = vect[RMQ(u - 1, v - 1)];
	for (int i = 1; i < m; i++){
		u = (17 * u + 751 + ans + 2 * i) % n + 1;
		v = (13 * v + 593 + ans + 5 * i) % n + 1;
		ans = vect[RMQ(u - 1, v - 1)];
	}

	out << u << " " << v << " " << ans << endl;

	return 0;
}

void RMQPreprocessing(){
	for (int i = 0; i < n; i++) rmq[i][0] = i;

	for (int j = 1; (1 << j) <= n; j++){
		for (int i = 0; i + (1 << j) - 1 < n; i++){
			xx = rmq[i][j - 1];
			yy = rmq[i + (1 << (j - 1))][j - 1];
			rmq[i][j] = (vect[xx] < vect[yy]) ? xx : yy;
		}
	}
}

int RMQ(int l, int r){
	if (r < l) swap(l, r);
	k = 1;
	while ((1 << k) <= r - l + 1) k++;
	k--;

	xx = rmq[l][k];
	yy = rmq[r - (1 << k) + 1][k];
	return (vect[xx] < vect[yy]) ? xx : yy;
}