#include<iostream>
using namespace std;
//Lab2 ข้อ 1 แยกตัวประกอบ

int main(){
    int x, b;
    cout << "Enter number (>1): ";
    cin >> x;
    cout << "Factoring result : ";
    while(x!=1){
        for(int i=2; i<=x; i++){
            b=x%i;
            if(b==0){
                x=x/i;

                if(x==1){
                    cout << i;
                    break;
                }
                else {
                    cout << i << " x ";
                    break;
                }
                
            }
        }
    }
    return 0;
}