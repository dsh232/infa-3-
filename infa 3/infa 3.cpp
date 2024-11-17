#include <iostream>
#include <string>
#include <vector>

using namespace std;

//bool loh = false;

bool isValidChar(char c) {
    const vector<char> validChars = { '1', '2', '3', '4', '?' };
    return find(validChars.begin(), validChars.end(), c) != validChars.end();
}

bool isMyManOkay(string text) {
    for (char c : text) {
        if (!isValidChar(c)) {
            return false; // Если хотя бы один символ недопустимый, возвращаем false
        }
    }
    return text.size() == 4; // Проверяем, что длина строки равна 4
}

string** createArray() {
    string** array = new string * [4];
    for (int i = 0; i < 4; ++i) {
        array[i] = new string[4];
    }
    return array;
}

void inputArray(string** array) {
    bool uhHuh = true;
    while (uhHuh) {
        for (int i = 0; i < 4; ++i) {  // on the row walk walk
            string n;   //enter thing  
            int uhHuhs = 0;
            bool normalAnswer = false;   //proverka na dolboeba
            while (!normalAnswer) {  //poka ne dolbaeb
                int s = 1;
                cout << "Input the row " << "#" << i + 1 << "> ";
                getline(cin, n);
                if (isMyManOkay(n) && n.size() == 4) {     //poka ne dolbaeb^2
                    for (int j = 0; j < 4; ++j) {     //putting in index of column symbol of enter thing
                        array[i][j] = n[j];
                    }
                    normalAnswer = true;
                }
                else {
                    cout << "uh-huh.\nenter 1 or 2 or 3 or 4 or ? and just normal size of line please (it's 4)." << endl;    //if dolbaeb
                    uhHuhs++;
                }
                if (uhHuhs > 10) {
                    cout << endl << "don't play with me." << endl;
                    /*loh = true;*/
                    return;
                    
                    
                }

            }

        }
    }
}

// Функция для вывода элементов массива
void printArray(string** array) {
    cout << "Your ahh: " << endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция для освобождения памяти
void deleteArray(string** array) {
    for (int i = 0; i < 4; ++i) {
        delete[] array[i];
    }
    delete[] array;
}

int main() {

    string** array = createArray();

    inputArray(array);

    /*if (loh) {
        cout << "   __\n| |\n|_|__\n  | |\n__| |" << endl;
        return 0;
    }*/

    printArray(array);

    deleteArray(array);

    return 0;
}