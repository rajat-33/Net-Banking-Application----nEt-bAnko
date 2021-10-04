// C++ implementation to create a file
#include <bits/stdc++.h>
#include<conio.h>
using namespace std;

// Driver code
int main()
{
    // fstream is Stream class to both
    // read and write from/to files.
    // file is object of fstream class
    cout << "\n\t***Creating, Reading and Writing Files***\n\n";
    string s;
    cout << "Enter the name of the file to be created: ";
    cin >> s;
    fstream file;

    // opening file "Gfg.txt"
    // in out(write) mode
    // ios::out Open for output operations.
    s = s+".txt";
    file.open(s, ios::out);

    // If no file is created, then
    // show the error message.
    if (!file)
    {
        cout << "Error in creating file!!!";
        return 0;
    }
    file << "Rajat Agarwal\nrajat_1503\n1952114";
    cout << "File created successfully.\n\n";
    file.close();
    getch();
    cout << "Reading the file...\n";
    fstream ReadFile;
    ReadFile.open(s, ios::in);
    string x;
    int c = 0;
    while(1)
    {
        if(c == 0)
        {
            cout << "Name: ";
        }
        if(ReadFile.eof())
        {
            break;
        }
        ReadFile>>x;
        cout << x << ' ';

        c++;
        if(c == 2)
        {
            cout << "\nUserName: ";
        }
        else if(c == 3)
        {
            cout << "\nUserID: ";
        }
    }
    // closing the file.
    // The reason you need to call close()
    // at the end of the loop is that trying
    // to open a new file without closing the
    // first file will fail.
    cout << "\n";
    file.close();
    getch();
    return 0;
}