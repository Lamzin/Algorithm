#include <fstream>
#include <string>

using namespace std;

int main(){
  fstream in("input.txt", ios::in), out("output.txt", ios::out);

  int ans = 0, cur = 0;
  string s;
  in >> s;
  for (int i = 0; i < n; i++){
    if (s[i] == '0'){
      cur++;
      ans = max(ans, cur);
    }
    else cur = 0;
  }
  
  out << ans << endl;
}
