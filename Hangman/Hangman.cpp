#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <set>
#include <conio.h>
#include <windows.h>

using namespace std;

const int mistakes_max = 8;
const int length = 9;
const int words_max = 628;

vector<vector<string>> hanger;
set<char> used;
string secretWord, shownWord;
int wordSize;

int mistakes;
int lettersLeft;

string chosenLetter;

bool win, loss;

void dialogue()
{
    cout << "Welcome to Hangman!" << '\n';
    cout << "Press any key to continue. ";
    _getch();
}

void setup()
{
    ifstream fileHanger("hanger.txt");

    hanger = vector<vector<string>>(mistakes_max, vector<string>(length));
    for (int mistake = 0; mistake < mistakes_max; mistake++) {
        for (int line = 0; line < length; line++) {
            getline(fileHanger, hanger[mistake][line]);
        }
    }

    srand(time(0));
    int index = rand() % words_max;

    ifstream fileWord("words.txt");

    for (int i = 0; i <= index; i++) {
        getline(fileWord, secretWord);
    }

    lettersLeft = wordSize = secretWord.size();
    shownWord = string(wordSize, '-');

    fileWord.close();
}

void show() 
{
    // drawing
    system("cls");
    cout << "No. of mistakes: " << mistakes << '\n';
    for (string line : hanger[mistakes]) {
        cout << line << '\n';
    }

    // used letters
    cout << "Used: ";
    if (used.empty()) {
        cout << '-';
    }
    else {
        for (char c : used) {
            cout << c << ' ';
        }
    }
    cout << "\n\n";

    // current progress
    cout << shownWord << "\n\n";
}

void input() 
{
    bool flag;

    do {
        flag = false;
        cout << "Choose a letter (from a to z): ";
        cin >> chosenLetter;

        // more then 1 character or not a letter
        if (chosenLetter.size() > 1 || chosenLetter[0] < 'a' || chosenLetter[0] > 'z') {
            cout << "Invalid letter!" << '\n';
            Sleep(500);
            show();
        }
        else {
            if (used.find(chosenLetter[0]) != used.end()) { // already used
                cout << "Letter already used!" << '\n';
                flag = true;
                Sleep(500);
                show();
            }
            else { // valid
                chosenLetter[0] = tolower(chosenLetter[0]);
                used.insert(chosenLetter[0]);
            }
        }
    } while (flag || chosenLetter.size() > 1 || chosenLetter[0] < 'a' || chosenLetter[0] > 'z');
}

void logic() {
    bool found = false;
    for (int i = 0; i < wordSize; i++) {
        if (secretWord[i] == chosenLetter[0]) {
            shownWord[i] = chosenLetter[0];
            lettersLeft--;
            found = true;
        }
    }

    if (!found) {
        mistakes++;
    }

    if (lettersLeft == 0) {
        win = true;
    }

    if (mistakes == 7) {
        loss = true;    
    }
}

void gameEnd()
{
    system("cls");
    if (loss) {
        cout << "You lost!" << '\n';
        cout << "The word was: " << secretWord << "\n\n";
    }

    if (win) {
        cout << "Congrats, you won!" << '\n';
        cout << "No. of mistakes: " << mistakes << "\n\n";
    }

    cout << "Press any key to exit.";
    _getch();
}

int main()
{
    dialogue();
    setup();
    while (!win && !loss) {
        show();
        input();
        logic();
    }

    gameEnd();
}
