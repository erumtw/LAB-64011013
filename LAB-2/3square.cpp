#include <iostream>
using namespace std;

void firstandlast(int n){
    for(int z=0; z<n; z++){
        cout << "*";
    }
        cout << endl;
}
int main(){
    int n;
    cin >> n;

    firstandlast(n);
    
    int j=0;
    while(j<n-2){
        int i=1;
        while(i<=n){
            if(i==1 || i==n){
            cout << "*";
            }
            else {
            cout << " ";
            }
            i++;
        }
    
        cout << endl;
        j++;
    }

    firstandlast(n);
    
   
    return 0;
}