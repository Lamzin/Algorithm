#include <vector>
#include <iostream>

using namespace std;

int n, k;
int a, b, c;
vector <int> vect, fenwick;

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
	cin >> n;
	vect.resize(n, 0);
	fenwick.resize(n, 0);
	for (int i = 0; i < n; i++){
		cin >> vect[i];
		update(i, vect[i]);
	}

	cin >> k;
	while (k--){
		cin >> a >> b >> c;
		if (a == 1)
			update(b - 1, c);
		else
			cout << get(c - 1) - get(b - 2) << endl;
	}

	return 0;
}