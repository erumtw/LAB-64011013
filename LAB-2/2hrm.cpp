// using Euclidean algorithm****
// 252, 105 = 147
// 147, 105 = 42
// 105, 42 = 63
// 63, 42 = 21
// 42, 21 = 21 // ;แสดงว่า 21 คือ หรม ของ 252,105 

#include<iostream>
using namespace std;

//Lab-2 ข้อ 2 หาหรม

int gcd(int a, int b) {
    while(a!=b){
        if(a>b){
            a=a-b;
        } else { 
            b=b-a;
            }
    }
    return a;
}

int main() {
    int a,b;
    cout << "Enter first nummber : ";
    cin >> a;
    cout << "Enter second number : ";
    cin >> b;
    cout << "Greatest common divisor = " << gcd(a,b) << endl;
    return 0;
}