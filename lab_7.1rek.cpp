#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** Z, const int rows, const int cols, const int low, const int high);
void Print(int** Z, const int rows, const int cols, int i, int j);
void Calc(int** Z, const int rows, const int cols, int &amount, int &togeth, int i, int j);
void Change(int** Z, const int rows, int c1, int c2, int i);
void Sort(int** Z, const int cols, const int rows, int i, int j, int r);

#ifndef UNIT_TEST
int main(){
    const int rows = 8, cols = 6, low = -34, high = 26;
    int amount = 0, togeth = 0;
    srand((unsigned)time(NULL));
    int** Z = new int* [rows];
    Create(Z, rows, cols, low, high);
    cout << "Початкова матриця:" << endl;
    Print(Z, rows, cols, 0, 0);
    Calc(Z, rows, cols, amount, togeth, 0, 0);
    cout << "Кількість = " << amount << endl;
    cout << "Сума = " << togeth << endl;
    cout << "Матриця після заміни:" << endl;
    Print(Z, rows, cols, 0, 0);
    Sort(Z, cols, rows, 0, 1, 0);
    cout << "Відсортована матриця:" << endl;
    Print(Z, rows, cols, 0, 0);

    for(int i = 0; i < rows; i++){
        delete[] Z[i];
    }
    delete[] Z;
    return 0;
}
#endif

void Create(int** Z, const int rows, const int cols, const int low, const int high){
    for(int i = 0; i < rows; i++){
        Z[i] = new int [cols];
    }
    for(int i =0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            Z[i][j] = low + rand() % (high - low + 1);
        }
    }
}
void Print(int** Z, const int rows, const int cols, int i, int j){
    if(i == rows)
        return;
    if(j == cols){
        cout << endl;
        Print(Z, rows, cols, i + 1, 0);
        return;
    } 
    cout << setw(4) << Z[i][j];
    Print(Z, rows, cols, i, j + 1);
}
void Calc(int** Z, const int rows, const int cols, int &amount, int &togeth, int i, int j){
    if(i == rows)
        return;
    if(j == cols){
        Calc(Z, rows, cols, amount, togeth, i + 1, 0);
        return;
    }
    if(Z[i][j] > 0 || Z[i][j] % 2 != 0){
        amount++;
        togeth += Z[i][j];
        Z[i][j] = 0;
    }
    Calc(Z, rows, cols, amount, togeth, i, j +1);
}
void Change(int** Z, const int rows, int c1, int c2, int i){
    if(i == rows)
        return;

    int temp = Z[i][c1];
    Z[i][c1] = Z[i][c2];
    Z[i][c2] = temp;
    Change(Z, rows, c1, c2, i + 1);
}
void Sort(int** Z, const int cols, const int rows, int i, int j, int r){
    if(i == cols - 1)
        return;
    if(j == cols){
        Sort(Z, cols, rows, i + 1, i + 2, 0);
        return;
    }
    if(r == rows){
        Sort(Z, cols, rows, i, j + 1, 0);
        return;
    }
    if(Z[r][i] == Z[r][j]){
        Sort(Z, cols, rows, i, j, r + 1);
        return;
    }else if(Z[r][i] < Z[r][j]){
        Change(Z, rows, i, j, 0);
        Sort(Z, cols, rows, i, j + 1, 0);
        return;
    }else{
        Sort(Z, cols, rows, i, j + 1, 0);
        return;
    }
}