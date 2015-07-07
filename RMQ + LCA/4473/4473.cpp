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

int n, m, uu, vv;
int vect[SIZE], rmq[SIZE][lnSIZE];

void RMQPreproccesing();
int RMQ(int u, int v);

int main(){
	in >> n;
	for (int i = 0; i < n; i++) in >> vect[i];
	RMQPreproccesing();

	in >> m;
	while (m--){
		in >> uu >> vv;
		out << RMQ(uu - 1, vv - 1) << endl;
	}
}

void RMQPreproccesing(){
	for (int i = 0; i < n; i++)
		rmq[i][0] = vect[i];

	for (int j = 1; (1 << j) <= n; j++){
		for (int i = 0; i + (1 << j) - 1 < n; i++){
			rmq[i][j] = max(rmq[i][j - 1], rmq[i + (1 << (j - 1))][j - 1]);;
		}
	}
}

int RMQ(int u, int v){
	if (v < u) swap(v, u);
	int k = (int) (log(v - u + 1.0) / log(2.0));

	return max(rmq[u][k], rmq[v - (1 << k) + 1][k]);
}