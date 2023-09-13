#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <queue>
#include <climits>
#include <cmath>
#include <string>
#include <functional>

using namespace std;

// to generate a random matrix of 0 and 1 in the csv file
void generateRandomMatrix(int row, int col, const string filename)
{
    ofstream outputFile(filename);

    if (!outputFile.is_open())
    {
        cout << "Error opening file..." << filename << endl;
        cout << "Exiting..." << endl;
        return;
    }

    srand(time(0));

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            int randomValue = rand() % 2;
            outputFile << randomValue;

            if (j < col - 1)
            {
                outputFile << ',';
            }
        }
        outputFile << endl;
    }
    outputFile.close();
}

// to print the generated matrix
void printMatrix(string &filename)
{
    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cout << "Error opening the file..." << filename << endl;
        // return 1;
    }

    string line;
    while (getline(inputFile, line))
    {
        cout << line << endl;
    }
    inputFile.close();
}

// reading the csv file
vector<vector<int>> readCsvFile(const string &filename)
{
    vector<vector<int>> grid;
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        vector<int> row;
        istringstream ss(line);
        string cell;

        while (getline(ss, cell, ','))
        {
            row.push_back(stoi(cell));
        }
        grid.push_back(row);
    }
    return grid;
}

// to compress the generated matrix according to the size
vector<vector<int>> compressMatrix(const vector<vector<int>> gridData, int size)
{
    int numRows = gridData.size();
    int numCols = gridData[0].size();

    vector<vector<int>> graph;

    for (int i = 0; i < numRows - (size - 1); ++i)
    {
        graph.push_back(vector<int>());
        for (int j = 0; j < numCols - (size - 1); ++j)
        {
            int sum = 0;
            for (int k = 0; k < size; ++k)
            {
                for (int l = 0; l < size; ++l)
                {
                    sum += gridData[i + k][j + l];
                }
            }
            graph[i].push_back((sum == 0) ? 0 : 1);
        }
    }
    return graph;
}

// to print any matrix
void printGraph(const vector<vector<int>> data)
{
    int numRows = data.size();
    int numCols = data[0].size();

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

struct Node
{
    int x, y;
    int g, h, f;
    Node *parent;

    Node(int _x, int _y) : x(_x), y(_y), g(0), h(0), f(0), parent(nullptr) {}
};

// The function returns true if the given (x, y) coordinates are valid and the position is traversable according to the matrix data.
// It returns false otherwise
bool isValid(int x, int y, int m, int n, const vector<vector<int>> &matrix)
{
    return x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] == 0;
}

// calculates the heuristic value according to the current coordinate
int calculateHeuristic(int x, int y, int destX, int destY)
{
    return abs(destX - x) + abs(destY - y); // manhattan distance as heuristic
}

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
    return vector<pair<int, int>>(); // no path found
}

int main()
{
    srand(time(0));
    int row, col, n;
    cout << "Enter no of rows you want :";
    cin >> row;
    cout << "Enter no of columns you want:";
    cin >> col;

    string filename = "random_matrix.csv";

    generateRandomMatrix(row, col, filename);

    cout << "Random matrix generated successful and saved in " << filename << endl;

    printMatrix(filename);

    cerr << "Reading csv file..." << endl;
    vector<vector<int>> gridData = readCsvFile(filename);
    cerr << "Reading completed !!!" << endl;

    int size;
    cout << "Enter number of column or row you need to move : ";
    cin >> size;

    vector<vector<int>> compressedMatrixData = compressMatrix(gridData, size);
    cout << "Compression Complete" << endl;

    cout << "Graph :" << endl;
    printGraph(compressedMatrixData);
    cout << "Printing Completed successfully..." << endl;

    int srcX, srcY, destX, destY;
    cout << "Enter source coordinate X : ";
    cin >> srcX;
    cout << "Enter source coordinate Y : ";
    cin >> srcY;
    cout << "Enter destination coordinate X : ";
    cin >> destX;
    cout << "Enter destination coordinate Y : ";
    cin >> destY;

    vector<pair<int, int>> path = findPath(compressedMatrixData, srcX, srcY, destX, destY);

    if (!path.empty())
    {
        cout << "Path found :" << endl;
        for (const auto &point : path)
        {
            cout << "(" << point.first << ", " << point.second << ") " << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "No path found." << endl;
    }

    return 0;
}