#include <gtest/gtest.h>
#include <cstdlib>
#include "lab_7.1rek.cpp"

// Створення матриці
int** makeMatrix() {
    int** Z = new int*[8];
    for (int i = 0; i < 8; i++) {
        Z[i] = new int[6];
    }
    return Z;
}
// Видалення матриці
void deleteMatrix(int** Z) {
    for (int i = 0; i < 8; i++) {
        delete[] Z[i];
    }
    delete[] Z;
}
// Тест 1. Перевірка функції Create
TEST(Lab71Rek, CreateMatrix) {
    int** Z = makeMatrix();
    Create(Z, 8, 6, -34, 26);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            EXPECT_GE(Z[i][j], -34);
            EXPECT_LE(Z[i][j], 26);
        }
    }
    deleteMatrix(Z);
}
// Тест 2. Перевірка функції Calc
TEST(Lab71Rek, CalculateAndReplace) {
    int** Z = makeMatrix();
    int values[8][6] = {
        {-2, 4, -3, 0, 5, -6},
        {7, -8, 2, -9, 10, -11},
        {-12, 13, -14, 15, -16, 17},
        {18, -19, 20, -21, 22, -23},
        {-24, 25, -26, 27, -28, 29},
        {30, -31, 32, -33, 34, -35},
        {-32, 1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10, 11}
    };
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            Z[i][j] = values[i][j];
        }
    }
    int amount = 0;
    int togeth = 0;
    Calc(Z, 8, 6, amount, togeth, 0, 0);
    EXPECT_EQ(amount, 37);
    EXPECT_EQ(togeth, 191);
    // Перевірка заміни чисел на 0
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            if (values[i][j] > 0 || values[i][j] % 2 != 0) {
                EXPECT_EQ(Z[i][j], 0);
            } else {
                EXPECT_EQ(Z[i][j], values[i][j]);
            }
        }
    }
    deleteMatrix(Z);
}
// Тест 3. Перевірка функції Change
TEST(Lab71Rek, ChangeColumns) {
    int** Z = makeMatrix();

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            Z[i][j] = i * 10 + j;
        }
    }
    Change(Z, 8, 1, 4, 0);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(Z[i][1], i * 10 + 4);
        EXPECT_EQ(Z[i][4], i * 10 + 1);
    }
    deleteMatrix(Z);
}
// Тест 4. Перевірка сортування стовпців
TEST(Lab71Rek, SortColumns) {
    int** Z = makeMatrix();
    for (int i = 0; i < 8; i++) {
        Z[i][0] = 1;
        Z[i][1] = 6;
        Z[i][2] = 3;
        Z[i][3] = 5;
        Z[i][4] = 2;
        Z[i][5] = 4;
    }
    Sort(Z, 6, 8, 0, 1, 0);
    int expected[6] = {6, 5, 4, 3, 2, 1};
    for (int j = 0; j < 6; j++) {
        EXPECT_EQ(Z[0][j], expected[j]);
    }
    deleteMatrix(Z);
}
// Тест 5. Перевірка сортування,
// якщо перші елементи стовпців однакові
TEST(Lab71Rek, SortColumnsWithEqualFirstElements) {
    int** Z = makeMatrix();
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            Z[i][j] = 1;
        }
    }
    Z[1][0] = 3;
    Z[1][1] = 6;
    Z[1][2] = 2;
    Z[1][3] = 5;
    Z[1][4] = 1;
    Z[1][5] = 4;
    Sort(Z, 6, 8, 0, 1, 0);
    int expected[6] = {6, 5, 4, 3, 2, 1};
    for (int j = 0; j < 6; j++) {
        EXPECT_EQ(Z[1][j], expected[j]);
    }
    deleteMatrix(Z);
}
