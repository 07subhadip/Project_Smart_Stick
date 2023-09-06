#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// Read CSV file and create a graph representation
vector<vector<int>> readCsvFile(const string &filename)
{
    vector<vector<int>> grid;
    ifstream file(filename);
    string line;

    while (std::getline(file, line))
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

// print the graph to the console
void printGraph(const vector<vector<int>> &graph)
{
    for (const auto &row : graph)
    {
        for (int cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> getMergedGrid(const vector<vector<int>> &grid)
{
    int numRows = grid.size();
    int numCols = grid[0].size();
    vector<vector<int>> graph;

    for (int i = 0; i < numRows - 1; ++i)
    {
        graph.push_back(vector<int>());

        for (int j = 0; j < numCols - 1; ++j)
        {
            int sum = grid[i][j] + grid[i][j + 1] + grid[i + 1][j] + grid[i + 1][j + 1];
            graph[i].push_back((sum == 0) ? 0 : 1);
        }
    }

    return graph;
}

// Dijkstra's algorithm
vector<pair<int, int>> dijkstra(const vector<vector<int>> &graph, const pair<int, int> &start, const pair<int, int> &goal)
{
    int rows = graph.size();
    int cols = graph[0].size();
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
    set<pair<int, int>> visited;
    map<pair<int, int>, int> distances;
    pq.push({0, start});
    distances[start] = 0;

    while (!pq.empty())
    {
        pair<int, int> current_node = pq.top().second;
        int current_distance = pq.top().first;
        pq.pop();

        if (visited.find(current_node) != visited.end())
        {
            continue;
        }
        visited.insert(current_node);

        if (current_node == goal)
        {
            break;
        }

        int dr[8] = {1, -1, 0, 0, -1, 1, -1, 1}; // making the movements in 8 different directions
        int dc[8] = {0, 0, 1, -1, 1, 1, -1, -1};

        for (int i = 0; i < 8; ++i)
        {
            int new_row = current_node.first + dr[i];
            int new_col = current_node.second + dc[i];
            pair<int, int> neighbor = {new_row, new_col};

            if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols && graph[new_row][new_col] == 0)
            {
                int new_distance = current_distance + 1; // Assuming each step has a cost of 1

                if (distances.find(neighbor) == distances.end() || new_distance < distances[neighbor])
                {
                    distances[neighbor] = new_distance;
                    pq.push({new_distance, neighbor});
                }
            }
        }
    }

    vector<pair<int, int>> path;
    pair<int, int> current_node = goal;

    while (current_node != start)
    {
        path.push_back(current_node);
        int dr[8] = {1, -1, 0, 0, -1, 1, -1, 1};
        int dc[8] = {0, 0, 1, -1, 1, 1, -1, -1};
        for (int i = 0; i < 8; ++i)
        {
            int new_row = current_node.first + dr[i];
            int new_col = current_node.second + dc[i];
            pair<int, int> new_node = {new_row, new_col};
            if (distances.find(new_node) != distances.end() && distances[new_node] == distances[current_node] - 1)
            {
                current_node = new_node;
                break;
            }
        }
    }

    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}

int main()
{
    string csvFilename = "obstacle.csv";

    vector<vector<int>> gridData = readCsvFile(csvFilename);
    vector<vector<int>> mergedGridData = getMergedGrid(gridData);

    cout << "Graph : " << endl;
    printGraph(mergedGridData);

    pair<int, int> start, goal;

    cout << "Enter the source coordinates (row col): ";
    cin >> start.first >> start.second;

    cout << "Enter the destination coordinates (row col): ";
    cin >> goal.first >> goal.second;

    vector<pair<int, int>> shortestPath = dijkstra(mergedGridData, start, goal);

    cout << "Shortest Path:";
    for (const auto &node : shortestPath)
    {
        cout << " (" << node.first << "," << node.second << ")";
    }
    cout << endl;

    return 0;
}
