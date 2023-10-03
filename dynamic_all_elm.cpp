#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

// Function to generate a random matrix with specified percentages of elements
vector<vector<int>> generateRandomMatrix(int rows, int cols, int &zeroCount, int &oneCount, int &twoCount)
{
    vector<vector<int>> matrix(rows, vector<int>(cols, 0));

    int totalCells = rows * cols;
    int zeroPercentage = 80;
    int onePercentage = 12;
    int twoPercentage = 8;

    zeroCount = (totalCells * zeroPercentage) / 100;
    oneCount = (totalCells * onePercentage) / 100;
    twoCount = (totalCells * twoPercentage) / 100;

    // Set '1's (fixed elements)
    while (oneCount > 0)
    {
        int x = rand() % rows;
        int y = rand() % cols;
        if (matrix[x][y] == 0)
        {
            matrix[x][y] = 1;
            oneCount--;
        }
    }

    // Set '2's (moving elements)
    while (twoCount > 0)
    {
        int x = rand() % rows;
        int y = rand() % cols;
        if (matrix[x][y] == 0)
        {
            matrix[x][y] = 2;
            twoCount--;
        }
    }

    return matrix;
}

// Function to print the matrix
void printMatrix(const vector<vector<int>> &matrix, int rows, int cols)
{
    cout << "          ";
    for (int i = 0; i < cols; i++)
    {
        cout << i << "     ";
    }
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    int j = 0;

    for (const auto &row : matrix)
    {
        cout << j << "         ";
        for (int val : row)
        {
            cout << val << "     ";
        }
        cout << endl;
        cout << endl;
        cout << endl;
        j++;
    }
}

int main()
{
    srand(static_cast<unsigned>(time(0)));

    int rows, cols;
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    int zeroCount, oneCount, twoCount;
    vector<vector<int>> matrix = generateRandomMatrix(rows, cols, zeroCount, oneCount, twoCount);

    cout << "Initial Random Matrix:" << endl;
    printMatrix(matrix, rows, cols);

    int numMovements;
    cout << "Enter the number of movements: ";
    cin >> numMovements;

     // Recalculate the counts of '1's, '2's, and '0's in the updated matrix
        int updatedOneCount = 0, updatedTwoCount = 0, updatedZeroCount = 0;
        for (int x = 0; x < rows; ++x)
        {
            for (int y = 0; y < cols; ++y)
            {
                if (matrix[x][y] == 1)
                {
                    updatedOneCount++;
                }
                else if (matrix[x][y] == 2)
                {
                    updatedTwoCount++;
                }
                else if (matrix[x][y] == 0)
                {
                    updatedZeroCount++;
                }
            }
        }

        // Print the updated counts
        cout << "\nCounts before any Movement "<< endl;
        cout << "Number of '0's: " << updatedZeroCount << endl;
        cout << "Number of '1's: " << updatedOneCount << endl;
        cout << "Number of '2's: " << updatedTwoCount << endl;


    for (int movement = 1; movement <= numMovements; ++movement)
    {
        // Find new positions for all '2's and update the matrix
        vector<vector<int>> newMatrix(rows, vector<int>(cols, 0));

        for (int x = 0; x < rows; ++x)
        {
            for (int y = 0; y < cols; ++y)
            {
                if (matrix[x][y] == 2)
                {
                    int dx = rand() % 3 - 1; // Random movement in x direction (-1, 0, 1)
                    int dy = rand() % 3 - 1; // Random movement in y direction (-1, 0, 1)

                    int newX = x + dx;
                    int newY = y + dy;

                    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && newMatrix[newX][newY] == 0)
                    {
                        newMatrix[newX][newY] = 2;
                    }
                    else
                    {
                        newMatrix[x][y] = 2; // If the move is invalid, stay in the same position
                    }
                }
                else if (matrix[x][y] ==1)
                {
                    newMatrix[x][y] = 1;
                }
            }
        }

        matrix = newMatrix;

        // Print the updated matrix after the movement
        cout << "\nMovement " << movement << ":" << endl;
        cout << endl;
        printMatrix(matrix, rows, cols);
    }

    return 0;
}
