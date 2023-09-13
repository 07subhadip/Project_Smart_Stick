#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <time.h>
#include <random>
#include <string.h>

using namespace std;

vector<vector<int>> generateRandomMatrix(int row, int col, int no_of_obs)
{
    vector<vector<int>> matrix(row, vector<int>(col, 0));

    srand(time(0));
    while (no_of_obs > 0)
    {
        int rows = rand() % row;
        int cols = rand() % col;

        if (matrix[rows][cols] == 0)
        {
            matrix[rows][cols] = 1;
            no_of_obs--;
        }
    }
    return matrix;
}

int main()
{
    int n, row, col;
    cout << "Enter No of row :";
    cin >> row;
    cout << "Enter no of columns :";
    cin >> col;
    cout << "Enter no of cells you need :";
    cin >> n;
    int cells = row * col;
    cout << "cells :" << cells << endl;
    int red_col = (row - (n - 1)) * (col - (n - 1));
    cout << "No of reduced cells : " << red_col << endl;

    int no_of_obs = round(red_col / 3);
    cout << "No of objects are :" << no_of_obs<<endl;

    vector<vector<int>> random_generated_matrix = generateRandomMatrix(row, col, no_of_obs);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout<<random_generated_matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}