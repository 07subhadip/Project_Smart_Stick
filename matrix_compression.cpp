#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Read CSV file and create a grid representation
vector<vector<int>> readCsvFile(const string& filename) {
    vector<vector<int>> grid;
    ifstream file(filename);
    string line;
    
    while (getline(file, line)) {
        vector<int> row;
        istringstream ss(line);
        string cell;
        
        while (getline(ss, cell, ',')) {
            row.push_back(stoi(cell));
        }
        
        grid.push_back(row);
    }
    
    return grid;
}

vector<vector<int>> mergeGridCells(const vector<vector<int>>& grid) {
    int numRows = grid.size();
    int numCols = grid[0].size();
    vector<vector<int>> mergedGrid;
    
    for (int i = 0; i < numRows - 1; ++i) {
        mergedGrid.push_back(vector<int>());
        
        for (int j = 0; j < numCols - 1; ++j) {
            int sum = grid[i][j] + grid[i][j + 1] + grid[i + 1][j] + grid[i + 1][j + 1];
            mergedGrid[i].push_back((sum == 0) ? 0 : 1);
        }
    }
    
    return mergedGrid;
}

int main() {
    string csvFilename = "obstacle.csv";
   
    vector<vector<int>> gridData = readCsvFile(csvFilename);
    vector<vector<int>> mergedGridData = mergeGridCells(gridData);
    
    for (const auto& row : mergedGridData) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    
    return 0;
}
