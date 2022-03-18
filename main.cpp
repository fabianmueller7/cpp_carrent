#include <iostream>
#include<windows.h>
#include <conio.h>
using namespace std;

void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

int menu() {

    clear();
    int Set[] = {7,7,7};
    int counter = 2;
    char key;

    for(int i = 0;;) {
        
        gotoxy(10,5);
        color(Set[0]);
        cout<<"Login";

        gotoxy(10,6);
        color(Set[1]);
        cout<<"Registration";

        gotoxy(10,7);
        color(Set[2]);
        cout<<"Exit Programm";

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
                cout << "Menu 1 is Open";
            }
            if(counter == 2)
            {
                cout << "Menu 2 is Open";
            }
            if(counter == 3)
            {
                cout << "Menu 3 is Open";
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

int main() {
        
    menu();
    return 0;
}

