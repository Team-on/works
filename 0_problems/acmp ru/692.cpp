#include <iostream>
using namespace std;
 
int main(){
    int a, i;
    cin >> a;
    for(i = 1; i <= a; i*=2)
      if(a == i){
        cout << "YES";
          return 0;
    }
    cout << "NO";
    return 0;
}