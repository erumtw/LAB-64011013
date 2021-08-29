#include<iostream>
#include <cmath>
using namespace std;

int main ()
{
    double a,b,c,s,S;
    cout << "Enter the length \"a\" of the triangle : " ;
    cin >> a;
    cout << "Enter the length \"b\" of the triangle : " ;
    cin >> b;
    cout << "Enter the length \"c\" of the triangle : " ;
    cin >> c;
    // #1
    // s = a+b+c / 2; // wrong one
    s = (a+b+c)/2; //is the right one
    cout << "s= " << s << endl;
    S = s*(s-a)*(s-b)*(s-c);
    cout << "S= " << S << endl;
    // #2
    if (a + b > c) 
    {
        if (a + c > b) 
        {
            if (b + c > a) 
            {
                cout << "The area of the triangle is " << sqrt(S) << endl; // #3
            }
            else 
            { 
                cout << "0 ";
            }
        }
        else 
        { 
            cout << "0"; 
        }
    }
    else 
    { 
       cout << "0 ";
    }
    return 0;
}


