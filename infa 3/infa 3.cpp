﻿#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class ArrayManager {
private:
    string** board;

public:
    ArrayManager(int size) {

        board = new string * [size];
        for (int i = 0; i < size; ++i) {
            board[i] = new string[size];
            for (int j = 0; j < size; ++j) {
                board[i][j] = "?"; // Инициализация пустыми ячейками
            }
        }
    }

    ~ArrayManager() {
        for (int i = 0; i < 4; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }

    void inputBoard() {
        for (int i = 0; i < 4; ++i) {  // on the row walk walk
            string n;   //enter thing  
            int uhHuhs = 0;
            bool normalAnswer = false;   //proverka na censored
            while (!normalAnswer) {  //poka ne censored
                cout << "Input the row " << "#" << i + 1 << "> ";
                getline(cin, n);
                if (isMyManOkay(n)) {     //poka ne censored^2
                    for (int j = 0; j < 4; ++j) {     //putting in index of column symbol of enter thing
                        board[i][j] = n[j];
                    }
                    normalAnswer = true;
                }
                else {
                    cout << "uh-huh.\nenter 1 or 2 or 3 or 4 or ? and just normal size of line please (it's 4)." << endl;    //if censored
                    uhHuhs++;
                }
                if (uhHuhs == 5) {
                    cout << endl << "Please, enter your matrix more carefully. Thank you. " << endl << endl;                 
                }
                if (uhHuhs > 10) {
                    cout << endl << "don't play with me." << endl;
                                                                                                                                                                                            /*cout << "   __\n| |\n|_|__\n  | |\n__| |" << endl;*/
                    exit(1);
                }
            }
        }

    }

    void printBoard() const {
        cout << "Current board:\n";
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                cout << board[i][j] << " "; 
            }
            cout << endl;
        }
    }

    string** getBoard() const {     //pointer on board
        return board;
    }

private:
    bool isValidChar(char c) const {
        const vector<char> validChars = { '1', '2', '3', '4', '?' };
        return find(validChars.begin(), validChars.end(), c) != validChars.end();
    }

    bool isMyManOkay(const string& text) const {
        if (text.size() != 4) return false; // Проверяем, что длина строки равна 4
        for (char c : text) {
            if (!isValidChar(c)) {
                return false; // Если хотя бы один символ недопустимый, возвращаем false
            }
        }
        return true;
    }
};

class Sudoku {
private:
    ArrayManager* arrayManager;

public:
    Sudoku() {
        arrayManager = new ArrayManager(4); // Создаем объект ArrayManager для управления массивом
    }

    ~Sudoku() {
        delete arrayManager; // Освобождение памяти
    }

    bool solve() {
        int row, col;
        string** board = arrayManager->getBoard();  //calling method from arrayManager

        if (!findEmptyLocation(row, col, board)) {
            return true; // Решение найдено
        }

        for (int num = 1; num <= 4; num++) {
            string strNum = to_string(num); // Преобразуем число в строку
            if (isValid(row, col, strNum, board)) {
                board[row][col] = strNum; // Вставляем число

                if (solve()) {
                    return true;
                }

                board[row][col] = "?"; // Обозначаем как пустую ячейку
            }
        }

        return false; // Нет решения
    }

    bool isValidSolution() const {
        string** board = arrayManager->getBoard();

        // Проверка строк
        for (int i = 0; i < 4; ++i) {
            vector<bool> seen(5, false); // Индексы от 1 до 4
            for (int j = 0; j < 4; ++j) {
                if (board[i][j] != "?") {
                    int num = stoi(board[i][j]);
                    if (seen[num]) return false;
                    seen[num] = true;
                }
            }
        }

        // Проверка столбцов
        for (int j = 0; j < 4; ++j) {
            vector<bool> seen(5, false);
            for (int i = 0; i < 4; ++i) {
                if (board[i][j] != "?") {
                    int num = stoi(board[i][j]);
                    if (seen[num]) return false;
                    seen[num] = true;
                }
            }
        }

        // Проверка квадратов 2x2
        for (int startRow = 0; startRow < 4; startRow += 2) {
            for (int startCol = 0; startCol < 4; startCol += 2) {
                vector<bool> seen(5, false);
                for (int i = startRow; i < startRow + 2; ++i) {
                    for (int j = startCol; j < startCol + 2; ++j) {
                        if (board[i][j] != "?") {
                            int num = stoi(board[i][j]);
                            if (seen[num]) return false;
                            seen[num] = true;
                        }
                    }
                }
            }
        }

        return true;
    }

    void inputBoard() {
        arrayManager->inputBoard(); // Ввод данных от пользователя
    }

    void printBoard() const {
        arrayManager->printBoard(); // Вывод текущего состояния доски
    }

private:
    bool isValid(int row, int col, const string& num, string** board) const {
        for (int x = 0; x < 4; x++) {
            if (board[row][x] == num || board[x][col] == num) {
                return false; // Проверка на дублирование в строке и столбце
            }
        }

        int startRow = row - row % 2;
        int startCol = col - col % 2;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (board[i + startRow][j + startCol] == num) {
                    return false; // Проверка на дублирование в квадрате
                }
            }
        }

        return true;
    }

    bool findEmptyLocation(int& row, int& col, string** board) const {
        for (row = 0; row < 4; row++) {
            for (col = 0; col < 4; col++) {
                if (board[row][col] == "?") { // Пустая ячейка обозначается как "?"
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Sudoku sudoku;

    cout << "Shidoku is a 4x4 square matrix filled only with the numbers 1, 2, 3 and 4,\nso that the numbers in each column, in  each row and in each corner square of 2x2 \nare not repeated." << endl;
    cout << "you need to enter a 4x4 square matrix filled with only the numbers 1, 2, 3, 4. If it's an unknown number put '?'.\nenter 4 characters ROW BY ROW.\n\n";
    sudoku.inputBoard(); // Ввод данных от пользователя

    if (sudoku.solve()) {
        cout << "\nSolution found..\n";

        if (!sudoku.isValidSolution()) { // Проверка финальной матрицы на допустимость
            cout << "\nSolution found, but it's not allowed!\n";
        }
        else {
            sudoku.printBoard(); // Вывод решения, если оно найдено и допустимо
        }
    }
    else {
        cout << "\nNo solution.\n"; // Сообщение о том, что решение невозможно
    }

    return 0;
}