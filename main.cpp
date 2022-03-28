#include <iostream>
#include<windows.h>
#include <conio.h>
#include <vector>
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
        if(ch != '\b') {
            password.push_back(ch);
        }
        else {
            password.pop_back();
        }
        ch = _getch();
    }
    string response = (password);
    return password;
}

void gotoxy(int x, int y) {
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

///////////////////////////////////////////////////////////
//Field
///////////////////////////////////////////////////////////

enum fieldstate {border, head, tail, fruit, board};
enum direction {dleft, dup, ddown, dright};

void gamesetup(fieldstate (*field)[12]){
    for(int l = 0; l < 12; l++) {
        for(int c = 0; c < 12; c++) {
            if(l == 0 || l == 11 || c == 0 || c == 11){
                *(*(field + c)+ l) =  border;
            }
            else {
                *(*(field + c)+ l) = board;
            }
        }
    }
}

vector<COORD> updatefield(fieldstate (*field)[12], direction direction, vector<COORD> vtail, int snakelength) {
    COORD chead = vtail.front();
    
    switch (direction)
    {
    case dup:
        chead.Y = chead.Y-1;
        break;
    case ddown:
        chead.Y = chead.Y+1;
        break;
    case dleft:
        chead.X = chead.X-1;
        break;
    case dright:
        chead.X = chead.X+1;
        break;
    }

    vtail.insert(vtail.begin(),chead);
    
    for(size_t i = 0; i < vtail.size(); i++) {
        if(snakelength >= i) {
            if(i == 0) {
                *(*(field + vtail[i].X)+ vtail[i].Y) = head;
            }
            else {
                *(*(field + vtail[i].X)+ vtail[i].Y) = tail;
            }
        } else {
            *(*(field + vtail[i].X)+ vtail[i].Y) = board;
        }
    }

    return vtail;
}

void displayfield(fieldstate (*field)[12]) {
    for(int l = 0; l < 12; l++) {
        for(int c = 0; c < 12; c++) {
            gotoxy(c+1 , l+1);
            switch(*(*(field + c)+ l)) {
                case border : cout << "#";
                case head : cout << "X";
                case tail : cout << "O";
                case fruit : cout << "S";
                case board : cout << " ";
            }
            if(c == 11) {
                cout << "\n";
            }
        }
    }
}

void startgame() {
    fieldstate field[12][12];
    fieldstate (*fieldpointer)[12];
    fieldpointer = field;
    boolean gameover = false;
    direction direction = dleft;
    vector<COORD> tail;
    COORD ca;
    ca.X = 8;
    ca.Y = 6;
    tail.insert(tail.begin(),ca);
    COORD cb;
    cb.X = 7;
    cb.Y = 6;
    tail.insert(tail.begin(),cb);
    int snakelength = 2;

    gamesetup(fieldpointer);
    clear();

    while(gameover == false){
        _getch();
        displayfield(fieldpointer);
        Sleep(500);
        tail = updatefield(fieldpointer, direction, tail, snakelength);
    }
    
    
}

///////////////////////////////////////////////////////////
//Userdatabase
///////////////////////////////////////////////////////////

typedef struct Elm {
	struct Data* pData;
	struct Elm* pNext;
}struElm;

typedef struct Data {
	char username[20];
	char password[20];
}struDataElm;

struElm* createNewContainer(string username, string password) {
    struElm* pNew = NULL;
	pNew = (struElm*)malloc(sizeof(struElm));
	if (pNew == NULL) exit(-1);
	pNew->pNext = NULL;
    pNew->pData = NULL; 
    pNew->pData = (struDataElm*)malloc(sizeof(struDataElm));
    strcpy(pNew->pData->username, username.c_str());
    strcpy(pNew->pData->password, password.c_str());
    return pNew;
}

struElm* createuserlist() {
    return createNewContainer("admin", "1234");
}

void adduser(struElm* pFirst, string username, string password) {
    struElm* pCurrent = pFirst;
    while(pCurrent->pNext != NULL) {
        pCurrent = pCurrent->pNext;
    }
    pCurrent->pNext = createNewContainer(username, password);
}

struElm* getUserbyUsername(struElm* pFirst, string username) {
    struElm* pCurrent = pFirst;
    do {
        string pCurrentusername = pCurrent->pData->username;
        if(pCurrentusername.compare(username) == 0){
            return pCurrent;
        }
    }while(pCurrent->pNext != NULL);
}

//////////////////////////////////////////////////////////
//Login
///////////////////////////////////////////////////////////

boolean checklogin(struElm* pFirst, string username, string password) {
    struElm* pCurrent = pFirst;
    do{
        string pCurrentusername = pCurrent->pData->username;
        string pCurrentpassword = pCurrent->pData->password;
        if(pCurrentusername.compare(username) == 0 && pCurrentpassword.compare(password) == 0){
            return true;
        }
        pCurrent = pCurrent->pNext;
    }while(pCurrent != NULL);
    return false;
}

int login(struElm* pFirst) {
    string username;
    string password;

    cout << "Login" << endl;
    cout << "Please enter your username and password." << endl;
    cout << "Username: ";
    cin >> username;
    password = decoder(inputpassword());

    if(checklogin(pFirst,username, password)){
        clear();
        cout << "Login successful" << endl;
        Sleep(500);
        startgame();
    } else {
        cout << '\n';
        cout << "Try again" << endl;
        if(checklogin(pFirst,username, decoder(inputpassword()))) {
            clear();
            cout << "Login successful" << endl;
            Sleep(500);
            startgame();
        } else {
            cout << '\n';
            cout << "Login failed";
             _getch();
            return 0;
        }
    }
    return 0;
}

///////////////////////////////////////////////////////////
//Registration
///////////////////////////////////////////////////////////

int registration(struElm* pFirst) {
    string username;
    string firstpassword;
    string secondpassword;

    clear();
    cout << "Accountcreation" << endl;
    cout << "Enter your new username and password." << endl;
    cout << "Username: ";
    cin >> username;
    firstpassword = inputpassword();
    cout << "\n";
    cout << "again..." << endl;
    secondpassword = inputpassword();
    cout << "\n";

    if(firstpassword.compare(secondpassword) == 0) {
        adduser(pFirst, username, firstpassword);
        cout << "Registration succeeded!";
         _getch();
        clear();
        return 0;

    } else {
        cout << "Registration failed!";
         _getch();
        clear();
        return 0;
    }

    return 0;
}

///////////////////////////////////////////////////////////
//Menu
///////////////////////////////////////////////////////////

void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
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
                registration(pFirst);
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
    //startgame();
    menu(createuserlist());
    return 0;
}

