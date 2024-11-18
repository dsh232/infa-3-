#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool censored = false;

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
    for (int i = 0; i < 4; ++i) {  // on the row walk walk
        string n;   //enter thing  
        int uhHuhs = 0;
        bool normalAnswer = false;   //proverka na dolboeba
        while (!normalAnswer) {  //poka ne censored

            cout << "Input the row " << "#" << i + 1 << "> ";
            getline(cin, n);

            if (isMyManOkay(n)) {     //poka ne censored^2
                for (int j = 0; j < 4; ++j) {     //putting in index of column symbol of enter thing
                    array[i][j] = n[j];
                }
                normalAnswer = true;
            }
            else {
                    cout << "uh-huh.\nenter 1 or 2 or 3 or 4 or ? and just normal size of line please (it's 4)." << endl;    //if censored
                    uhHuhs++;
            }

            if (uhHuhs > 10) {
                    cout << endl << "don't play with me." << endl;
                    censored = true;
                    return;                                        
            }

        }

    }
    
}

// Проверка, можно ли вставить число
bool isValid(string** board, int row, int col, const string& num) {
    // Проверка строки и столбца
    for (int x = 0; x < 4; x++) {
        if (board[row][x] == num || board[x][col] == num) {
            return false;
        }
    }

    // Проверка 2x2 квадрата
    int startRow = row - row % 2;
    int startCol = col - col % 2;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Функция для поиска пустой ячейки
bool findEmptyLocation(string** board, int& row, int& col) {
    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (board[row][col] == "?") { 
                return true;
            }
        }
    }
    return false;
}

// Основная функция для решения шидоку
bool solveSudoku(string** board) {
    int row, col;

    // Если нет пустых мест, значит, решение найдено
    if (!findEmptyLocation(board, row, col)) {
        return true;
    }

    // Пробуем числа от "1" до "4"
    for (int num = 1; num <= 4; num++) {
        string strNum = to_string(num); // Преобразуем число в строку
        if (isValid(board, row, col, strNum)) {
            board[row][col] = strNum; // Вставляем число

            // Рекурсивный вызов для следующей ячейки
            if (solveSudoku(board)) {
                return true;
            }

            // Если число не подходит, очищаем ячейку
            board[row][col] = "?"; // Обозначаем как пустую ячейку
        }
    }

    return false; 
}

// Функция для вывода элементов массива
void printArray(string** array) {
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

    string** userArray = createArray();

    inputArray(userArray);

    /*if (loh) {
        cout << "   __\n| |\n|_|__\n  | |\n__| |" << endl;
        return 0;
    }*/
    if (censored) {
        deleteArray(userArray);
        return 0;
    }

    if (solveSudoku(userArray)) {
        cout << "\nResult: \n";
        printArray(userArray);
    }
    else {
        cout << "\nNo solution.\n";
    }
    deleteArray(userArray);

    return 0;
}