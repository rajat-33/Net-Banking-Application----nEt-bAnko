#include <iostream>      //for stands for standard input-output stream.
#include <conio.h>       // to provide console input/output.
#include <string.h>      // for strings
#include <algorithm>     // for algorithms
#include <iterator>      // for iterating
#include <unordered_map> // for maps
#include <unordered_set>
#include <vector> //for vectors
#include <fstream>
using namespace std;

vector<bool> refUserIDs(1000, 0); //for unique user IDs

string takeInputPassword()
{
    vector<char> passcode(10); //default password size is 10
    int i;
    cout << "Enter password: \n";
    cout << "_";
    for (i = 0; i < 10 && (passcode[i] = getch()) != '\r'; i++)
    {
        if (passcode[i] == 32)
        {
            cout << "\nInvalid Password!\n";
            break;
        }
        if (passcode[i] == 8)
        {
            i -= 2;
        }
        cout << "\n";
        for (int k = 0; k <= i; k++)
        {
            cout << "* ";
        }
        cout << "_";
    }
    cout << "\n";
    string ref;
    for (int k = 0; k <= i; k++)
    {
        ref.push_back(passcode[k]);
    }
    ref.pop_back(); //to eliminate the '\0' character from the end for easy insertion in files and operations
    return ref;
}


class User
{
public:
    string password;
    string first_name;
    string surname;
    string user_name;
    int user_id;
    int balance;
    void createUserDatabase(string);
    User(){}
    bool signUp(string);
    bool signIn(string);
    User()
    {
        //id and balance can inserted here
    } //costructor
};

class Admin
{
public:
    unordered_map<string, User*> username_user; //map for mapping
    unordered_set<string> ref_usernames;       //for includeInDatabase
    User current_user;
    User *all_user = new User[200];

    void restoreDatabase();
    void includeInDatabase(string inp_username, unordered_set<string> ref_usernames);
    void modifyUser(string);
    void topPart();
    void bottomPart();
    void displayPage0();
    void displayPage1();
    void displayPage2();
};

void Admin ::restoreDatabase()
{
    int temp_int;
    string temp_string1, temp_string2;

    //Restoring the data into the maps for access
    //reading the data -1
    fstream file_read;
    file_read.open("database_Username.txt", ios::in);

    while (!file_read.eof())
    {
        file_read >> temp_string1;
        username_user[temp_string1]->createUserDatabase(temp_string1);
    }
    file_read.close();
    int choice = 1;
    while (choice)
    {
        displayPage0();
        cout << "Enter 1 to continue OR enter 0 to exit: ";
        cin >> choice;
    }
};

void Admin ::includeInDatabase(string inp_username, unordered_set<string> ref_usernames)
{
    fstream file_open;
    file_open.open("database_Username.txt", ios::out);
    for (auto it = ref_usernames.begin(); it != ref_usernames.end(); it++)
    {
        file_open << *it << "\n";
    }
    file_open.close();
}


void Admin :: topPart()
{
    cout << "\n\n\n\n\n";
    for (int i = 1; i <= 70; i++)
    {
        cout << "= ";
    }
    cout << "\n";
    cout << "\t   DATE\t\t\t\t\t\t\t";
    cout << "nEt bAnko\t\t\t\t\t\t";
    cout << "  TIME\n\n\n\n";
}

void Admin :: bottomPart()
{
    cout << "\n\n\n\n\n";
    for (int i = 1; i <= 70; i++)
    {
        cout << "= ";
    }
    cout << "\n\n\n\n\n";
}

void Admin :: displayPage0()
{
    displayPage1();
    int choice;
    while (1)
    {
        topPart();
        cout << "\t\tMAIN PAGE (Page 1)\n\n\n\n";
        cout << "Enter '1' to continue OR enter '0' to discontinue: ";
        cin >> choice;
        if (choice == 0)
        {
            break;
        }
        else if (choice == 1)
        {
            break;
        }
        else
        {
            cout << "Invalid Operation!\n\n";
        }
    }
    bottomPart();
}

void Admin :: displayPage1()
{
    int temp_int = 1, choice = 1;
    string temp_string1;
    User temp_obj;
    while (choice)
    {
        topPart();
        cout << "\t\tLOGIN PAGE (Page 2)\n\n\n\n";
        cout << "\t***OPERTAIONS***\n\n";
        cout << "'1': To Sign-Up\n'2': To Sign-In\n\n\tEnter your choice: ";
        cin >> temp_int;
        cout << "\n\n";
        switch (temp_int)
        {
            //sign-up
        case 1:
            cout << "Enter a desired USERNAME: ";
            cin >> temp_string1;
            if (username_user.find(temp_string1) == username_user.end())
            {
                if (!temp_obj.signUp(temp_string1))
                {
                    cout << "\n\tUnable to create account!";
                    break;
                }
                username_user[temp_string1] = temp_obj;
                ref_usernames.insert(temp_string1);
                includeInDatabase(temp_string1, ref_usernames);
                cout << "\n\tAccount has been created sucessfully!";
            }
            else
            {
                cout << "\n\tAn account already exists with the same USERNAME!";
            }
            break;

            //sign-in
        case 2:
            cout << "Enter USERNAME: ";
            cin >> temp_string1;
            if (username_user.find(temp_string1) != username_user.end())
            {
                if (!username_user[temp_string1].signIn(temp_string1))
                {
                    cout << "\n\tUnable to Sign-In!";
                }
                else
                {
                    cout << "\n\tSigned-In sucessfully!";
                    bottomPart();
                    displayPage2();
                }
            }
            else
            {
                cout << "\n\tIncorrect USERNAME!";
            }
            break;

            //get out
        default:
            cout << "\n\tInvalid operation!";
        }
        bottomPart();
        while (1)
        {
            topPart();
            cout << "\t\tLOGIN PAGE (Page 2)\n\n\n\n";
            cout << "\n\nEnter '1' to continue OR enter '0' to discontinue: ";
            cin >> choice;
            if (choice == 0)
            {
                break;
            }
            else if (choice == 1)
            {
                break;
            }
            else
            {
                cout << "Invalid Operation!\n\n";
            }
        }
        bottomPart();
    }
}




void User ::createUserDatabase(string inp_username)
{
    string temp_name = inp_username + ".txt", temp_string1;
    int temp_int;
    fstream file_read;
    file_read.open(temp_name, ios::in);

    file_read >> temp_string1 >> first_name >> surname;
    cout << first_name << " " << surname << "\n";
    file_read >> temp_string1 >> user_name;
    file_read >> temp_string1 >> user_id;
    file_read >> temp_string1 >> password;
    cout << "restored password is: " << password << "\n";
    file_read >> temp_string1 >> balance;
    cout << "restored password is: " << balance << "\n";
    file_read.close();
}

bool User ::signUp(string inp_username)
{
    int temp_int;
    fstream file_create;
    string temp_name = inp_username + ".txt", temp_string, temp_string2;
    file_create.open(temp_name, ios::out);
    if (!file_create)
    {
        cout << "\n\tAccount can't be created :-< Please try again later!";
        return 0;
    }
    cout << "Enter your name: ";
    cin >> first_name >> surname;
    file_create << "Name: " << first_name << " " << surname << "\n";
    user_name = inp_username;
    file_create << "UserName: " << user_name << "\n";
    user_id = rand() % 100000;
    while (refUserIDs[user_id]) //creating unique ID for all users
    {
        user_id = (user_id + 1) % 100000;
    }
    refUserIDs[user_id] = 1;
    file_create << "UserID: " << user_id << "\n";
    temp_string2 = takeInputPassword();
    password = temp_string2;
    file_create << "Password: " << password << "\n"; //password is temp_string
    balance = 25000;
    file_create << "Balance: " << balance;
    file_create.close();
    return 1;
}

bool User ::signIn(string inp_username)
{
    string temp_string;
    temp_string = takeInputPassword();
    int x = password.compare(temp_string);
    if (password.size() == temp_string.size())
    {
        for (int k = 0; k < temp_string.size(); k++)
        {
            if (temp_string[k] != password[k])
            {
                break;
            }
        }
        return 1;
    }
    cout << password << "\n\n\n\n";
    cout << "\n\tIncorrect password!";
    return 0;
}

void Admin :: displayPage2()
{
    int temp_int = 1, choice = 1, temp_int2;
    string temp_string1;

    while (choice)
    {
        topPart();
        cout << "\t\t Profile Page (Page 3)\n\n\n\n";
        cout << "\t***OPERTAIONS***\n\n";
        cout << "'1': View Profile\n'2': Send Money\n'3': Request Money\n'4': Balance Enquiry "
             << "\n'5': Change Password\n'6': View Password Security Level\n\n\tEnter your choice: ";
        cin >> temp_int;
        cout << "\n\n";
        switch (temp_int)
        {
        case 1:
            cout << "\n\n\t---PROFILE---\n\n";
            cout << "User Name: " << username_user.user_name << "\n"
                 << "User ID: " << user_id << "\n";
            cout << "Name: " << first_name << " " << surname << "\n";

            //cout << "last transaction: ";
            break;
        case 2:
            cout << "\n\n\t---SEND MONEY---\n\n";
            cout << "Enter User Namer of the reciever: ";
            cin >> temp_string1;
            if (username_user.find(temp_string1) != username_user.end())
            {
                if (temp_string1 == user_name)
                {
                    cout << "\nCan't Transfer Money Into The Same Account!";
                    break;
                }
                cout << "\nEnter the amount to be sent: ";
                cin >> temp_int2;
                if (balance >= temp_int2)
                {
                    balance -= temp_int2;
                    username_user[temp_string1].balance += temp_int2;
                    modifyUser(user_name);
                    modifyUser(temp_string1);

                    cout << "\nMoney has been tranferred sucessfully!";
                }
                else
                {
                    cout << "\nInsufficient Balance!";
                }
            }
            else
            {
                cout << "Incorrect username!";
            }
            break;
        case 3:
            cout << "\n\n\t---REQUEST MONEY---\n\n";

            //modifyUser(userReqGetter);

            cout << "Money has been requested!(function not implemented)";
            break;
        case 4:
            cout << "\n\n\t---BALANCE ENQUIRY---\n\n";
            cout << "Avaliable Balance: " << balance;
            break;
        case 5:
            cout << "\n\n\t---CHANGE PASSWORD---\n\n";
            temp_string1 = takeInputPassword();
            password = temp_string1;
            modifyUser(user_name);
            cout << "Changed Password successfully!";
            break;
        case 6:
            cout << "\n\n\t---VIEW PASSWORD SECURITY LEVEL---\n\n";

            //cout << "Pasword is :" << passwordSecurityLevel(current_user.password);//string return
            break;
        default:
            cout << "Inavalid Operation";
        }
        bottomPart();
        while (1)
        {
            topPart();
            cout << "\t\t Profile Page (Page 3)\n\n\n\n";
            cout << "\n\nEnter '1' to continue OR enter '0' to discontinue: ";
            cin >> choice;
            if (choice == 0)
            {
                break;
            }
            else if (choice == 1)
            {
                break;
            }
            else
            {
                cout << "Invalid Operation!\n\n";
            }
        }
        bottomPart();
    }
}

void Admin ::modifyUser(string current_username)
{
    fstream File;
    string temp_string = current_username + ".txt";
    File.open(temp_string, ios::out);
    File << "Name: " << username_user[current_username].first_name << " " << username_user[current_username].surname << "\n";
    File << "UserName: " << username_user[current_username].user_name << "\n";
    File << "UserId: " << username_user[current_username].user_id << "\n";
    File << "Password: " << username_user[current_username].password << "\n";
    File << "Balance: " << username_user[current_username].balance << "\n";
    File.close();
}

int main()
{
    Admin obj_admin;
    obj_admin.restoreDatabase();
    return 0;
}

//use fuckin' pointers
