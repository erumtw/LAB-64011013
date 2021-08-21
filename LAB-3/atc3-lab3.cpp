#include <iostream>
using namespace std;

int main () {
    int a, b;
    cout << "enter number : ";
    cin >> a;
    b=a*2-1; // made 3 to 5, 5 to 9
    
    int r=1, n=0;
    while (r<=a) //top row  1 to a
    {
        int c=1;
        while(c<=b)
        {
            if(c<=r || c>=b-n)
            {
                cout << "* ";
            }
            else 
            {
                cout << "  ";
            }
            c++;
        }
        n++;
        r++;
        cout << endl;
    }

    r=1, n=a+1; // reset values
    int  m=a; 

    while (r<=a-1) //bottom row a+1 to b
    {
        int c=1; 
        while(c<=b) //column
        {
            if(c<=b-m || c>=n)
            {
                cout << "* ";
            }
            else 
            {
                cout << "  ";
            }
            c++;
        }
        
        m++;
        n++;
        r++;
        cout << endl;
    }
}



