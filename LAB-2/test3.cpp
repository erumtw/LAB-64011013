#include <iostream>
using namespace std;
// ข้อ 3 สร้างสี่เหลี่ยม
void firstandlast(int n){
    for(int z=0; z<n; z++){
        cout << "* ";
    }
        cout << endl;
}

int main(){
    int n;
    cout << "Enter number : ";
    cin >> n;

    firstandlast(n);
    
    int j=0;
    while(j<n-2){
        int i=1;
        while(i<=n*2){
            if(i==1 || i==(n*2)-1){
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