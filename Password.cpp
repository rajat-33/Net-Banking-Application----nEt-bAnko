#include<iostream>
#include<conio.h>
using namespace std;
int main()
{
    char password[20];
    int i;
    cout << "Enter Password: ";

    cout << "_";
    for(i = 0;(password[i]=getch())!='\r';i++)
    {
        
        if(password[i] == 32)
        {
            cout << "\nInvalid Password!\n";
            break;
        }
        if(password[i] == 8)
        {
            i -= 2;
        }
        cout << "\n\t\t";
        for(int k = 0;k<=i;k++)
        {
            cout << "* ";
        }
        cout << "_";
    }
    cout << "\n\tPassword is: ";
    for(int j = 0;j<i;j++)
    {
        cout << password[j];
    }
}