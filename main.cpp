#include <iostream>
#include<windows.h>
#include <conio.h>
using namespace std;

///////////////////////////////////////////////////////////
//Helper
///////////////////////////////////////////////////////////

void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

void endprogramm(boolean *continueprogramme) {
    cout <<"Ending programm";
    for(int i = 0; i < 3;i++)  {
        cout<<".";
        Sleep(500);
    }
    *continueprogramme = false;
}

string decoder (string input) {
    return input;
}

string inputpassword() {
    string password;
    char ch;
    cout << "Enter Password:";
    ch = _getch();
    while(ch != 13){//character 13 is enter
        password.push_back(ch);
        ch = _getch();
    }
    string response = (password);
    return password;
}

///////////////////////////////////////////////////////////
//Userdatabase
///////////////////////////////////////////////////////////

typedef struct Elm {
	struct Data* pData;
	struct Elm* pNext;
}struElm;

typedef struct Data {
	std::string username;
	std::string password;
}struDataElm;


struElm* createuserlist() {

    struElm pNew;
    pNew.pNext = NULL;
    pNew.pData->username = "admin";
    pNew.pData->password = "1234";

    return &pNew;
}

///////////////////////////////////////////////////////////
//Login
///////////////////////////////////////////////////////////

boolean checklogin(struElm* pFirst, string username, string password) {
    do{
        if(pFirst->pData->username == username && pFirst->pData->password == password){
            return true;
        }
    }while(pFirst->pNext != NULL);
    return false;
}

void login(struElm* pFirst) {
    string username;
    string password;
    string test;

    cout << "Login" << endl;
    cout << "Please enter your username and password." << endl;
    cout << "Username: ";
    cin >> username;
    password = decoder(inputpassword());

    if(checklogin(pFirst,username, password)){
        cout << "Login successful" << endl;
        cin >> test;
    } else {
        cout << "Login failed" << endl;
        cin >> test;
    }
}

///////////////////////////////////////////////////////////
//Registration
///////////////////////////////////////////////////////////

void registration() {

}

///////////////////////////////////////////////////////////
//Menu
///////////////////////////////////////////////////////////

void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int menu(struElm* pFirst) {

    boolean continueprogramm = true;
    clear();
    int Set[] = {7,7,7};
    int counter = 2;
    char key;

    while(continueprogramm) {
        
        gotoxy(10,5);
        color(Set[0]);
        cout<<"Login";

        gotoxy(10,6);
        color(Set[1]);
        cout<<"Registration";

        gotoxy(10,7);
        color(Set[2]);
        cout<<"Exit Programm";
        color(7);

        key = _getch();

        if(key == 72 && (counter >= 2 && counter <=3)) { //72= up arrow key
            counter--;
        }
        if(key == 80 && (counter >=1 && counter <=2)) {
            counter++;
        }
        if(key == '\r') { //carrage return = enter key
            if(counter == 1)
            {
                clear();
                login(pFirst);
                clear();

            }
            if(counter == 2)
            {
                clear();
                cout << "Menu 2 is Open";
                clear();
            }
            if(counter == 3)
            {
                clear();
                endprogramm(&continueprogramm);
                clear();
            }
        }
        if(counter == 1) {
            Set[0] = 12;
            Set[1] = 7;
            Set[2] = 7;
        }
        if(counter == 2) {
            Set[1] = 12;
            Set[0] = 7;
            Set[2] = 7;
        }
        if(counter == 3) {
            Set[2] = 12;
            Set[0] = 7;
            Set[1] = 7;
        }
    }
    return 0;
}

///////////////////////////////////////////////////////////
//Main
///////////////////////////////////////////////////////////

int main() {
    menu(createuserlist());
    return 0;
}

