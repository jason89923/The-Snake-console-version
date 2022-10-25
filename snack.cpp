#include <conio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int choice = 0;  // 記憶上次選項

int highest_record = 0;

static const int num_of_option = 4;

int score = 0;

class MyCOORD {
   public:
    int X;
    int Y;
    MyCOORD() {
        X = 0;
        Y = 0;
    }  // Constructor
    MyCOORD(int x, int y) {
        X = x;
        Y = y;
    }  // Constructor

    MyCOORD(COORD temp) {
        X = temp.X;
        Y = temp.Y;
    }  // Constructor

    bool operator==(const MyCOORD a) const {
        if (a.X == X && a.Y == Y) {
            return true;
        }  // if

        return false;
    }  // operator==

    COORD to_COORD() {
        COORD temp;
        temp.X = X;
        temp.Y = Y;
        return temp;
    }  // to_COORD
};     // MyCOORD

enum Direction { UP = 0,
                 DOWN = 1,
                 LEFT = 2,
                 RIGHT = 3 };

void gotoxy(int xpos, int ypos) {
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos;
    scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}  // gotoxy

void gotoxy(COORD loc) {
    COORD scrn = loc;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOuput, scrn);
}  // gotoxy

COORD GetConsoleCursorPosition() {
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi)) {
        return cbsi.dwCursorPosition;
    }  // if
    else {
        // The function failed. Call GetLastError() for details.
        COORD invalid = {0, 0};
        return invalid;
    }  // else
}  // GetConsoleCursorPosition

void clrscr(int x, int width) {
    string str, str2;
    str.clear();
    str2.clear();
    for (int i = 0; i < width; i++) {
        str = str + " ";
    }  // for

    for (int i = 0; i <= 30; i++) {
        gotoxy(x, i);
        printf("%s", str.c_str());
    }  // for

    gotoxy(0, 0);
}  // clrscr

void clrscr(COORD start, COORD end) {
    int width = abs(end.X - start.X) + 1;
    string str;
    str.clear();
    for (int i = 0; i < width; i++) {
        str = str + " ";
    }  // for

    int length = abs(end.Y - start.Y) + 1;
    for (int i = 0; i < length; i++) {
        gotoxy(start);
        printf("%s", str.c_str());
        start.Y++;
    }  // for

}  // clrscr

COORD Create_COORD(int X, int Y) {
    COORD coord;
    coord.X = X;
    coord.Y = Y;
    return coord;
}  // Create_COORD

void RemoveElement(string& str, const char ch) {
    if (!str.empty()) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == ch) {
                str.erase(str.begin() + i);
                i--;
            }  // if
        }      // for
    }          // if
}  // RemoveElement

void Print_symbol(const char ch, const int amount) {
    for (int i = 0; i < amount; i++) {
        cout << ch;
    }  // for

    cout << endl;
}  // Print_symbol

void Print_THE_SNAKE(COORD location) {
    gotoxy(location);
    string str = "T H E   S N A K E";
    puts(str.c_str());
}  // Print_THE_SNAKE

void Print_Highest_score(COORD location) {
    gotoxy(location);
    string str = "HIGHEST SCORE : ";
    printf("%s%d", str.c_str(), highest_record);
}  // Print_Highest_score

void Print_Choose(COORD location) {
    gotoxy(location);
    string str = "Please Choose Difficulty";
    puts(str.c_str());
}  // Print_Choose

void Print_Hard(COORD location) {
    gotoxy(location);
    string str = "HARD";
    puts(str.c_str());
}  // Print_Hard

void Print_Normal(COORD location) {
    gotoxy(location);
    string str = "NORMAL";
    puts(str.c_str());
}  // Print_Normal

void Print_Easy(COORD location) {
    gotoxy(location);
    string str = "EASY";
    puts(str.c_str());
}  // Print_Normal

void Print_Exit(COORD location) {
    gotoxy(location);
    string str = "EXIT";
    puts(str.c_str());
}  // Print_Exit

void Draw_frame(int delay) {
    int x = 59;
    int y = 4;
    for (int i = 0; i < 13; i++) {
        gotoxy(x, y);
        putchar('*');
        x++;
        Sleep(delay);
    }  // for

    x--;
    y++;
    for (int i = 0; i < 2; i++) {
        gotoxy(x, y);
        putchar('*');
        y++;
        Sleep(delay);
    }  // for

    y--;
    x--;

    for (int i = 0; i < 24; i++) {
        gotoxy(x, y);
        putchar('*');
        x--;
        Sleep(delay);
    }  // for

    x++;
    y--;

    for (int i = 0; i < 2; i++) {
        gotoxy(x, y);
        putchar('*');
        y--;
        Sleep(delay);
    }  // for

    x++;
    y++;

    for (int i = 0; i < 11; i++) {
        gotoxy(x, y);
        putchar('*');
        x++;
        Sleep(delay);
    }  // for

}  // Draw_frame

void Initial_animation() {
    for (int i = 0; i <= 5; i++) {
        clrscr(Create_COORD(48, 0), Create_COORD(70, 8));
        Print_THE_SNAKE(Create_COORD(51, i));
        Sleep(100);
    }  // for

    Draw_frame(15);

    for (int i = 28; i >= 10; i--) {
        clrscr(Create_COORD(46, 10), Create_COORD(71, 28));
        Print_Highest_score(Create_COORD(52, i));
        Sleep(60);
    }  // for

    for (int i = 28; i >= 15; i--) {
        clrscr(Create_COORD(46, 15), Create_COORD(71, 28));
        Print_Choose(Create_COORD(48, i));
        Sleep(60);
    }  // for

    for (int i = 28; i >= 18; i--) {
        clrscr(Create_COORD(46, 17), Create_COORD(71, 28));
        Print_Hard(Create_COORD(58, i));
        Sleep(60);
    }  // for

    for (int i = 28; i >= 21; i--) {
        clrscr(Create_COORD(46, 19), Create_COORD(71, 28));
        Print_Normal(Create_COORD(57, i));
        Sleep(60);
    }  // for

    for (int i = 28; i >= 24; i--) {
        clrscr(Create_COORD(46, 23), Create_COORD(71, 28));
        Print_Easy(Create_COORD(58, i));
        Sleep(60);
    }  // for

    for (int i = 28; i >= 27; i--) {
        clrscr(Create_COORD(46, 26), Create_COORD(71, 28));
        Print_Exit(Create_COORD(58, i));
        Sleep(60);
    }  // for

}  // Initial_animation

void Initial_animation(int delay) {
    Print_THE_SNAKE(Create_COORD(51, 5));
    Draw_frame(delay);
    Print_Highest_score(Create_COORD(52, 10));
    Print_Choose(Create_COORD(48, 15));
    Print_Hard(Create_COORD(58, 18));
    Print_Normal(Create_COORD(57, 21));
    Print_Easy(Create_COORD(58, 24));
    Print_Exit(Create_COORD(58, 27));

}  // Initial_animation

struct _choice {
    COORD first;
    COORD last;
};

class choice_location {
   public:
    _choice location[4];
    choice_location() {
        for (int i = 0; i < 4; i++) {
            location[i].first = Create_COORD(55, 18 + i * 3);
            location[i].last = Create_COORD(64, 18 + i * 3);
        }  // for
    }      // Constructor

    _choice operator[](int index) {
        return location[index];
    }  // operator []
};

void Set_Choice_Location(choice_location loc) {
    COORD now;
    now = GetConsoleCursorPosition();
    gotoxy(55, now.Y);
    putchar(' ');
    gotoxy(64, now.Y);
    putchar(' ');
    gotoxy(loc[choice].first);
    putchar('<');
    gotoxy(loc[choice].last);
    putchar('>');
}  // Set_Choice_Location

int Menu() {
    choice_location loc;
    Set_Choice_Location(loc);
    while (true) {
        char ch = getch();
        if (ch == -32) {
            ch = getch();
            if (ch == 72) {
                choice--;
                if (choice < 0) {
                    choice = 3;
                }  // if
            }      // if
            else if (ch == 80) {
                choice++;
                if (choice > 3) {
                    choice = 0;
                }  // if
            }      // else if
        }          // if

        else if (ch == '\r') {
            return choice;
        }  // else if

        Set_Choice_Location(loc);
    }  // while
}  // Menu

void Print_score(int score) {
    clrscr(Create_COORD(62, 24), Create_COORD(80, 24));
    gotoxy(62, 24);
    printf("%d", score);
}  // Print_score

void Set_environment() {
    clrscr(0, 120);
    gotoxy(20, 0);
    for (int i = 0; i < 81; i++) {
        putchar('=');
    }  // for

    int x = 100;
    int y = 1;
    for (int i = 0; i < 20; i++) {
        gotoxy(x, y++);
        putchar('|');
    }  // for

    gotoxy(20, 20);
    for (int i = 0; i < 80; i++) {
        putchar('=');
    }  // for

    x = 20;
    y = 1;
    for (int i = 0; i < 20; i++) {
        gotoxy(x, y++);
        putchar('|');
    }  // for

    gotoxy(55, 24);
    printf("SCORE: ");
    Print_score(0);
}  // Set_environment

class Snake {
   public:
    int length;
    COORD head;
    COORD tail;
    COORD body[10000];
    vector<COORD> eat_list;
    Direction direction;
    Snake() {
        length = 2;
        head = Create_COORD(60, 15);
        tail = Create_COORD(61, 15);
        direction = LEFT;
        body[0] = head;
        body[1] = tail;
    }  // Constructor

    void Print_snake() {
        for (int i = 0; i < length; i++) {
            gotoxy(body[i]);
            if (i == 0) {
                putchar('@');
            }  // if
            else {
                putchar('*');
            }  // else
        }      // for
    }          // Print_snake

    void Move_snake(Direction direction) {
        bool grow = false;
        COORD temp;
        if (!eat_list.empty()) {
            temp = eat_list[0];
            if (temp.X == tail.X && temp.Y == tail.Y) {
                eat_list.erase(eat_list.begin());
                grow = true;
            }  // if
        }      // if

        for (int i = length - 1; i > 0; --i) {
            body[i] = body[i - 1];
        }  // for

        if (direction == UP) {
            body[0].Y--;
        }  // if
        else if (direction == DOWN) {
            body[0].Y++;
        }  // else if
        else if (direction == LEFT) {
            body[0].X--;
        }  // else if
        else if (direction == RIGHT) {
            body[0].X++;
        }  // else if

        head = body[0];
        if (grow) {
            length++;
            body[length - 1] = temp;
        }  // if

        tail = body[length - 1];
    }  // Move_snake

    bool Hit_wall() {
        if (head.X == 20 || head.X == 100 || head.Y == 0 || head.Y == 20) {
            return true;
        }  // if

        return false;
    }  // Hit_wall

    bool Hit_itself() {
        for (int i = 1; i < length; i++) {
            if (head.X == body[i].X && head.Y == body[i].Y) {
                return true;
            }  // if
        }      // for

        return false;
    }  // Hit_itself

    bool Eat_food(COORD food_loc) {
        MyCOORD food(food_loc);
        MyCOORD _head(head);
        if (food == _head) {
            eat_list.push_back(food_loc);
            return true;
        }  // if

        return false;
    }  // Eat_food
};     // class Snake

void Put_food(COORD& food_loc, Snake snake) {
redo:
    srand(time(NULL));
    food_loc = Create_COORD(rand() % 78 + 21, rand() % 18 + 1);
    MyCOORD food(food_loc);
    for (int i = 0; i < snake.length; i++) {
        MyCOORD temp(snake.body[i]);
        if (food == temp) {
            goto redo;
        }  // if
    }      // for
}  // Put_food

void Print_food(COORD food_loc) {
    gotoxy(food_loc);
    putchar('#');
}  // Print_food

void Play(int initial_delay, int magnification, int amplitude) {
    score = 0;
    Set_environment();
    Snake snake;
    Direction direction = LEFT;
    bool score_change = false;
    snake.Print_snake();
    COORD food_loc;
    Put_food(food_loc, snake);
    Print_food(food_loc);
    Print_Highest_score(Create_COORD(81, 24));
    while (true) {
        if (kbhit()) {
            char ch;
            char ch2;
            while (kbhit()) {
                ch = getch();
                if (ch < 0) {
                    ch2 = getch();
                }  // if
            }      // while 清除緩衝區

            if (ch == -32) {
                if (ch2 == 72) {
                    if (direction != DOWN) {
                        direction = UP;
                    }  // if
                }      // if
                else if (ch2 == 80) {
                    if (direction != UP) {
                        direction = DOWN;
                    }  // if
                }      // else if
                else if (ch2 == 75) {
                    if (direction != RIGHT) {
                        direction = LEFT;
                    }  // if
                }      // else if
                else if (ch2 == 77) {
                    if (direction != LEFT) {
                        direction = RIGHT;
                    }  // if
                }      // else if
            }          // if
        }              // if
        snake.Move_snake(direction);
        clrscr(Create_COORD(21, 1), Create_COORD(99, 19));
        snake.Print_snake();
        if (snake.Hit_wall() || snake.Hit_itself()) {
            gotoxy(53, 10);
            puts("G A M E   O V E R");
            break;
        }  // if

        if (snake.Eat_food(food_loc)) {
            initial_delay = initial_delay - amplitude;
            if (initial_delay < 20) {
                initial_delay = 20;
            }  // if

            Put_food(food_loc, snake);
            score = score + magnification;
            score_change = true;
        }  // if

        Print_food(food_loc);
        if (score_change) {
            Print_score(score);
        }  // if

        Sleep(initial_delay);
        score_change = false;
    }  // while

    if (score > highest_record) {
        highest_record = score;
    }  // if

    while (kbhit()) {
        getch();
    }  // while 清除緩衝區

    time_t time;
    time = clock();
    while (true) {
        if (clock() - time >= 2000) {
            break;
        }  // if
        else if (kbhit()) {
            break;
        }  // else if
    }      // while
}  // Play

void Read_record() {
    fstream file;
    file.open("C:\\_snake.log", ios::in);
    if (!file) {
        file.open("C:\\_snake.log", ios::out);
        file << 0;
    }  // if
    else {
        string record;
        file >> record;
        bool error = false;
        for (int i = 0; i < record.size(); i++) {
            if (record[i] < '0' || record[i] > '9') {
                error = true;
                break;
            }  // if
            highest_record = highest_record * 10 + (int)(record[i] - '0');
        }  // for

        if (error) {
            file.open("C:\\_snake.log", ios::out);
            highest_record = 0;
        }  // if
    }      // else

    file.close();
}  // Read_record

void Write_Record() {
    fstream file;
    file.open("C:\\_snake.log", ios::out);
    file << highest_record;
    file.close();
}  // Write_Record

void SetKeyBoard(int num) {
    HWND hCon = GetConsoleWindow();
    DWORD dwNewKeybLayout = num;  // Layout must be already loaded!
    PostMessage(hCon, WM_INPUTLANGCHANGEREQUEST, 0, (LPARAM)dwNewKeybLayout);
    PostMessage(hCon, WM_INPUTLANGCHANGE, 0, (LPARAM)dwNewKeybLayout);
}  // SetKeyBoard

int main() {
    int difficulty = 0;
    LoadKeyboardLayout("0x0409", KLF_ACTIVATE | KLF_SETFORPROCESS);
    SetKeyBoard(0x00000409) ;
    Read_record();
    Initial_animation();
    do {
        while (kbhit()) {
            getch();
        }  // while 清除緩衝區

        difficulty = Menu();
        if (difficulty == 0) {
            Play(50, 30, 2);
        }  // if HARD
        else if (difficulty == 1) {
            Play(100, 20, 3);
        }  // if NORMAL
        else if (difficulty == 2) {
            Play(150, 10, 5);
        }  // if EASY

        clrscr(0, 120);
        Write_Record();
        Initial_animation(0);
    } while (difficulty != 3);

    SetKeyBoard(0x00000404) ;
    LoadKeyboardLayout("0x0404", KLF_ACTIVATE | KLF_SETFORPROCESS);
}  // main