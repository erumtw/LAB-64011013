#include<iostream>
using namespace std;

int main()
{   
    int x=1;
    while (x <= 10000)
    {
        int total=0;
        for (int i = 1; i < x; i++)
        {
            if(x % i == 0)
            {
                    total += i;
            }
        }
        if (total == x)
        {
                cout <<  total << endl;
        }  
        x++;
    }
    return 0;
}


            
            