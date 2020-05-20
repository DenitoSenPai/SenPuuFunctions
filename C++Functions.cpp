#include <iostream>

using namespace std;

// Function Declaration 
int File_Menu_Options (); 

class File_Functions 
{
private: 
    string lineString; 
public: 
    File_Functions ()
    {
        this->lineString = "BLANK"; 
    }
    void Count_Down_Timer_Function () 
    { 
        ifstream filePtr ("Count_Down_Timer.txt"); 
        while (!filePtr.eof())
        {
            getline (filePtr, this->lineString); 
            cout << "" << this->lineString << endl; 
        }
        filePtr.close(); 
    }
    ~ File_Functions (); 
};

// Driver
int main()
{
    File_Functions Functions; 

    return 0;
}

// Functions 
int File_Menu_Options () 
{
    fflush(stdin);
    int userOpt, flag = 0;

    while (flag != 1)
    {
        userOpt = 0;
        cout << "1. Count Down Timer" << endl;
        cout << "2. Open A File | Write Mode" << endl;
        cout << "3. Open A File | Read Mode" << endl;
        cout << "4. Class Layout" << endl;
        cin >> userOpt;

        if (userOpt == 1 || userOpt == 2 || userOpt == 3 || userOpt == 4)
            flag = 1;

        system("cls");
    }

    return userOpt;
    
}