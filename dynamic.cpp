#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

// Function to generate a random matrix with 10% '1's and 30% of them are '2's
vector<vector<int>> generateRandomMatrix(int rows, int cols, int &zeroCount, int &oneCount, int &twoCount)
{
    vector<vector<int>> matrix(rows, vector<int>(cols, 0));

    int totalCells = rows * cols;
    int onePercentage = 20;
    int twoPercentage = 30;
    int zeroPercentage = 100 - onePercentage - twoPercentage;

    oneCount = ((totalCells * onePercentage) / 100.0);
    twoCount = ((oneCount * twoPercentage) / 100.0);
    zeroCount = totalCells - oneCount - twoCount;

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

    int startX, startY;
    cout << "Enter the starting X-coordinate of the moving element: ";
    cin >> startX;
    cout << "Enter the starting Y-coordinate of the moving element: ";
    cin >> startY;

    if (startX < 0 || startX >= rows || startY < 0 || startY >= cols || matrix[startX][startY] != 2)
    {
        cout << "Invalid starting coordinates for the moving element." << endl;
        return 1;
    }

    int numMovements;
    cout << "Enter the number of movements: ";
    cin >> numMovements;

    cout << "\nCounts in the Initial Matrix:" << endl;
    cout << "Number of '0's: " << zeroCount << endl;
    cout << "Number of '1's: " << oneCount << endl;
    cout << "Number of '2's: " << twoCount << endl;

    // Perform movements
    int currentX = startX, currentY = startY;
    for (int movement = 1; movement <= numMovements; ++movement)
    {
        int dx = rand() % 3 - 1; // Random movement in x direction (-1, 0, 1)
        int dy = rand() % 3 - 1; // Random movement in y direction (-1, 0, 1)

        // Calculate the new position
        int newX = currentX + dx;
        int newY = currentY + dy;

        // Check if the new position is within bounds
        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols)
        {
            // Check if the new position is a valid move (0) or the same position
            if (matrix[newX][newY] == 0 || (newX == currentX && newY == currentY))
            {
                if (newX == currentX && newY == currentY)
                {
                    cout << "Same Position" << endl;
                }

                matrix[currentX][currentY] = 0;
                matrix[newX][newY] = 2;
                currentX = newX;
                currentY = newY;
            }
        }
        else
        {
            // If the new position is out of bounds, print the same position
            cout << "\nMovement " << movement << ": Staying at (" << currentX << ", " << currentY << ")" << endl;
            cout << endl;
        }

        // Print the updated matrix after the movement
        cout << "\nMovement " << movement << ":" << endl;
        cout << endl;
        printMatrix(matrix, rows, cols);
    }

    return 0;
}
