#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <queue>
#include <stdlib.h>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Define a structure for nodes
struct Node
{
    int x, y;     // Coordinates of the node
    int g, h, f;  // Cost and heuristic values used in pathfinding
    Node *parent; // Pointer to the parent node

    Node(int _x, int _y) : x(_x), y(_y), g(0), h(0), f(0), parent(nullptr) {}
};

// Check if coordinates are valid and the position is traversable
bool isValid(int x, int y, int m, int n, const vector<vector<int>> &matrix)
{
    return x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] == 0;
}

// Calculate the heuristic value based on coordinates
int calculateHeuristic(int x, int y, int destX, int destY)
{
    return abs(destX - x) + abs(destY - y); // Manhattan distance as heuristic
}

// Construct the path from the goal node
vector<pair<int, int>> constructPath(Node *node)
{
    vector<pair<int, int>> path;

    while (node)
    {
        path.emplace_back(node->x, node->y);
        node = node->parent;
    }

    reverse(path.begin(), path.end());
    return path;
}

// Find the path using A* algorithm
vector<pair<int, int>> findPath(const vector<vector<int>> &matrix, int srcX, int srcY, int destX, int destY)
{
    int m = matrix.size();
    int n = matrix[0].size();

    priority_queue<Node *, vector<Node *>, function<bool(Node *, Node *)>> openList([](Node *a, Node *b)
                                                                                    { return a->f > b->f; });

    vector<vector<bool>> closedList(m, vector<bool>(n, false));

    Node *startNode = new Node(srcX, srcY);
    startNode->h = calculateHeuristic(srcX, srcY, destX, destY);
    startNode->f = startNode->h;
    openList.push(startNode);

    while (!openList.empty())
    {
        Node *currentNode = openList.top();
        openList.pop();

        int x = currentNode->x;
        int y = currentNode->y;
        closedList[x][y] = true;

        if (x == destX && y == destY)
        {
            return constructPath(currentNode);
        }

        int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
        int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

        for (int i = 0; i < 8; ++i)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (!isValid(newX, newY, m, n, matrix) || closedList[newX][newY])
            {
                continue;
            }

            int newG = currentNode->g + 1;
            int newH = calculateHeuristic(newX, newY, destX, destY);
            int newF = newG + newH;

            Node *neighbour = new Node(newX, newY);
            neighbour->g = newG;
            neighbour->h = newH;
            neighbour->f = newF;
            neighbour->parent = currentNode;

            openList.push(neighbour);
        }
    }
    return {};
}

// Function to generate a random matrix with specified percentages of elements
vector<vector<int>> generateRandomMatrix(int rows, int cols, int &zeroCount, int &oneCount, int &twoCount)
{
    vector<vector<int>> matrix(rows, vector<int>(cols, 0));

    int totalCells = rows * cols;
    int zeroPercentage = 80;
    int onePercentage = 8;
    int twoPercentage = 12;

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

// void pass(vector<vector<char>>matrix){
//         for (int  i = 0; i < row; i++)
//         {
//             /* code */
//         }
        
// }

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

    int srcX, srcY, destX, destY;
    cout << "Enter the source coordinate " << endl;
    cin >> srcX >> srcY;
    cout << "Enter the destination coordinate " << endl;
    cin >> destX >> destY;

    int path_length = 0;
    vector<pair<int, int>> path = findPath(matrix, srcX, srcY, destX, destY);
    
    int currentPathIndex = 0;

    if (!path.empty())
    {
        cout << "Path found :" << endl;
        for (const auto &point : path)
        {
            cout << "(" << point.first << ", " << point.second << ") " << endl;
            path_length++;
        }
        cout << endl;
    }
    else
    {
        cout << "No path found." << endl;
    }

    cout << "Path length is " << path_length << endl;

    for (int movement = 1; movement <= path_length+1; ++movement)
    {
        vector<vector<int>> newMatrix(rows, vector<int>(cols, 0));

        for (int x = 0; x < rows; ++x)
        {
            for (int y = 0; y < cols; ++y)
            {
                if (matrix[x][y] == 2)
                {
                    int dx = rand() % 3 - 1;
                    int dy = rand() % 3 - 1;

                    int newX = x + dx;
                    int newY = y + dy;

                    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && newMatrix[newX][newY] == 0)
                    {
                        newMatrix[newX][newY] = 2;
                    }
                    else
                    {
                        newMatrix[x][y] = 2;
                    }
                }
                else if (matrix[x][y] == 1)
                {
                    newMatrix[x][y] = 1;
                }
            }
        }

        matrix = newMatrix;

        cout << "\nMovement " << movement << ":" << endl;
        cout << endl;
        
        // Display the updated matrix with '#' at the source position
        for (int x = 0; x < rows; ++x)
        {
            for (int y = 0; y < cols; ++y)
            {
                if (x == srcX && y == srcY)
                {
                    cout << "#     ";
                }
                else
                {
                    cout << matrix[x][y] << "     ";
                }
            }
            cout << endl << endl << endl;
        }

        vector<pair<int, int>> updatePath = findPath(matrix, srcX, srcY, destX, destY);

        if (!updatePath.empty())
        {
            cout << "Path found after movement " << movement << ":" << endl;
            for (const auto &point : updatePath)
            {
                cout << "(" << point.first << ", " << point.second << ")" << endl;
            }
            cout << endl;
        }
        else
        {
            cout << "No path found after Movement " << movement << "." << endl;

            cout << "Waiting for 3 seconds..." << endl;
            cout << "Please wait." << endl;
            cout.flush();

#ifdef _WIN32
            Sleep(3000);
#else
            sleep(3);
#endif
            cout << "Delay complete" << endl;
            continue;
        }

        if (currentPathIndex < path.size())
        {
            // Update the source coordinate to the next path coordinate
            srcX = path[currentPathIndex].first;
            srcY = path[currentPathIndex].second;
            currentPathIndex++;
        }
        // pass(newMatrix);
    }
    // vector<vector<char>>char_matrix = newMatrix;
    // char_matrix[destX][destY] = static_cast<int>('#');
    // cout<<"\nFinal Grid : "<<endl;
    // printMatrix(matrix,rows,cols);

    return 0;
}
