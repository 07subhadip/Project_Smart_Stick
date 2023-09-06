#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <queue>
#include <functional>

using namespace std;


// creating a structure 
struct Node
{
    int x, y;   // coordinates of the node
    int g, h, f;    //cost and heuristic values used in pathfinding
    Node *parent;   // pointer to the parent node

    Node(int _x, int _y) : x(_x), y(_y), g(0), h(0), f(0), parent(nullptr) {} 
    // constructor for Node struct and it takes (_x , _y) as arguments and initialize  the member variables
    // g(0), h(0), f(0)  initialize the cose and heuristic values 0 initially
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
    vector<pair<int, int>> path;       // vector to store the path

    while (node)
    {
        path.emplace_back(node->x, node->y);     // Add the current node's coordinates to the path
        node = node->parent;                  // Move to the parent node
    }
    
    reverse(path.begin(), path.end());      // Reverse the path to get the correct order
    return path;         // Return the constructed path
}

vector<pair<int, int>> findPath(const vector<vector<int>> &matrix, int srcX, int srcY, int destX, int destY)
{
    int m = matrix.size();    // calculate numebr of rows
    int n = matrix[0].size(); // claculate number of columns

    // priority queue will hold pointer to Node object
    // vector<Node *> specify the container type
    // function<bool(Node * , Node *) specifies the type of comparison function that will be used to order elements in the priority queue
    //(Node *a, Node *b) specifies the  parameter of the Lambda fucntion

    // openList is the name of the priority queue

    priority_queue<Node *, vector<Node *>, function<bool(Node *, Node *)>> openList([](Node *a, Node *b)
    { return a->f > b->f; });

    // this is the body of a lambda function it compares f value to a and b
    // If the f value of a is greater than the f value of b, the lambda returns true,
    // indicating that a should have higher priority in the queue (lower f values are higher priority).
    // If the condition is not met, the lambda returns false.

    vector<vector<bool>> closedList(m, vector<bool>(n, false));
    //  It's used to keep track of whether specific positions in the matrix have been visited or explored during the pathfinding process

    Node *startNode = new Node(srcX, srcY); // dynamically allocating the strting node
    startNode->h = calculateHeuristic(srcX, srcY, destX, destY);    // calculate the heuristic value
    startNode->f = startNode->h;    // setting estimation cose is equal to heuristic value
    openList.push(startNode);       // calling the openList function to add startNode in priority queue

    while (!openList.empty())
    {
        Node *currentNode = openList.top(); // Gets the node with the lowest total cost (f) from the priority queue openList and assigns it to the currentNode
        openList.pop();     // Removes the top node (with the lowest cost) from the priority queue openList since it's being examined

        int x = currentNode->x;
        int y = currentNode->y;
        // Extracts the x and y coordinates of the current node

        closedList[x][y] = true;    //Marks the current node as visited by setting the corresponding position in the closedList matrix to true


        // Checks if the current node's coordinates match the destination coordinates. If true, it means the destination has been reached
        if (x == destX && y == destY)
        {
            return constructPath(currentNode);  // If the destination is reached, this returns the path constructed using the constructPath function, starting from the currentNode
        }


        // These arrays define the four possible directions (up, down, left, right) to explore neighboring nodes
        int dx[4] = {-1, 1, 0, 0};
        int dy[4] = {0, 0, -1, 1};


        // this loop iterates over 4 directions
        for (int i = 0; i < 4; ++i)
        {
            //  Calculates the new coordinates for the neighboring node in the current direction
            int newX = x + dx[i];
            int newY = y + dy[i];


            // The if statement checks if the new coordinates are valid and if the position has not been visited (closedList[newX][newY])
            if (!isValid(newX, newY, m, n, matrix) || closedList[newX][newY])
            {
                continue;   // If the conditions are met, the code continues to explore the neighboring node
            }

            int newG = currentNode->g + 1;  // Calculates the new cost to reach the neighboring node (g value) by incrementing the cost of the current node
            int newH = calculateHeuristic(newX, newY, destX, destY);    // Calculates the heuristic value for the neighboring node based on its coordinates and the destination
            int newF = newG + newH; // Calculates the total estimated cost (f value) for the neighboring node

            Node *neighbour = new Node(newX, newY); //  Creates a new node (neighbour) with the calculated coordinates

            // Assigns the calculated g, h, and f values to the neighbour node and sets its parent to the currentNode
            neighbour->g = newG;
            neighbour->h = newH;
            neighbour->f = newF;
            neighbour->parent = currentNode;

            openList.push(neighbour);  //  Adds the neighboring node to the openList priority queue for further exploration

        }
    }
    return {}; // no path found
}

int main()
{
    ifstream file("obstacle .csv"); // open CSV file for reading
    string line;                   // declare a string to hold each line of the file
    vector<vector<int>> matrix;    // declare a 2D vector to store the matrix data

    // this loop reads each line from the file and precesses it

    while (getline(file, line))
    {
        vector<int> row;       // declare a vector to hold the value of a single row
        stringstream ss(line); // create a stringstream to process the line

        int value;          // declare an integer to hold the extracted value
        while (ss >> value) // this loop extracts each value from the stringstream
        {
            row.push_back(value); // add the extracted value to the current row vector
            if (ss.peek() == ',') // check if the character is a comma(',')
            {
                ss.ignore(); // if yes , ignore the comma (',')
            }
        }

        matrix.push_back(row); // add the populated row vector to the matrix
    }
    // now, 'matrix' holds the 2D matrix of the integers and read the CSV file

    int srcX, srcY, destX, destY; // collecting the source and destination co-ordinates
    cout << "Enter source X coordinate: ";
    cin >> srcX;
    cout << "Enter source Y coordinate: ";
    cin >> srcY;
    cout << "Enter destination X coordinate: ";
    cin >> destX;
    cout << "Enter destination Y coordinate: ";
    cin >> destY;


    
    // find the path using A* algorithm

    vector<pair<int, int>> path = findPath(matrix, srcX, srcY, destX, destY);
    // invoke the findPath function to compute the path using A* algo
    //  declaring a variable 'path' as a vector of pair that consists pair of int to represent coordinate in the matrix

    if (!path.empty()) // checks the path vector is empty or not
    {
        cout << "Path found :" << endl; // if no then output path found
        for (const auto &point : path)  // this initiates a loop that iterates through each coordinate point in the path vector
        // const auto &point : path  --> this defines a reference ('&') to each point in the path vector
        {
            cout << "(" << point.first << ", " << point.second << ") " << endl; // print in (row,column) format
        }
        cout << endl; // end of line
    }
    else // if empty
    {
        cout << "No path found." << endl; // print no path found
    }

    return 0; // execution complete
}