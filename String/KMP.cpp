/**********************************************************/
/*  File name: KMP.cpp                                    */
/*                                                        */
/*  Author: Lamzin Oleh                                   */
/*          olehtomas@gmail.com                           */
/*                                                        */
/*  Time: 19:51:20 04/27/15                               */
/*                                                        */
/*  Knuth–Morris–Pratt algorithm                          */
/*                                                        */
/**********************************************************/

#include <iostream>
#include <vector>

using namespace std;

vector <int> prefix_function(string s){
	int n = s.length();
	vector <int> pi(n);
	for(int i = 1; i<n; i++){
		int j = pi[i-1];
		while(j > 0 && s[i] != s[j]) j = pi[j - 1];
		if (s[i] == s[j]) j++;
		pi[i] = j;
	}
	return pi;
}

int main(){
	//search "s" in "text"
	string text, s, kmp;
	getline(cin, text);
	getline(cin, s);

	kmp = s + "#" + text;

	vector <int> pre_func = prefix_function(kmp);
	for(int i = s.length() + 1; i<pre_func.size(); i++){
		if (pre_func[i] == s.length()) 
			cout << i - 2*(int)s.length() << " ";
	}
}
