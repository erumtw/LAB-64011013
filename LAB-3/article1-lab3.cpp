#include<iostream>
using namespace std;

int sum(string x){
    int total=0;
    
    for(int i=0; i<x.size(); i++){
        total +=  x[i] - '0';
    }
    cout << total << endl;

    if(total >9){
        int total2=0;
        
        while(total!=0){
            total2= total2 + total % 10;
            total= total / 10;
        }
        cout << total2 << endl;
    }
    

    return 0;
}

int main() {
    string x;
    cin >> x ;
    // cout << sum(x);
    sum(x);
    
    
}