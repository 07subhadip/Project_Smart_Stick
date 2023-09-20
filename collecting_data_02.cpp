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
 
// to generate a random matrix of 0 and 1 in the csv file                                             function--->> 1
void generateRandomMatrix(int row, int col, int no_of_obs, const string& filename) {
    vector<vector<int>> matrix(row, vector<int>(col, 0));

    srand(time(0));
    while (no_of_obs > 0) {
        int rows = rand() % row;
        int cols = rand() % col;

        if (matrix[rows][cols] == 0) {
            matrix[rows][cols] = 1;
            no_of_obs--;
        }
    }

    // Open a file for writing
    ofstream outputFile(filename);

    // Check if the file is opened successfully
    if (!outputFile) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    // Write the matrix data to the CSV file
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            outputFile << matrix[i][j];
            if (j < col - 1) {
                outputFile << ",";
            }
        }
        outputFile << endl;
    }

    // Close the file
    outputFile.close();

    cout << "Matrix has been saved to " << filename << endl;
}

// reading the csv file                                                                         function------->>> 2
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


// to compress the generated matrix according to the size                                       function----->>> 3
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

// count 0 and 1 function                                                                         function----->>> 4
void countZeroAndOnes(const vector<vector<int>>& matrix , int &countZero, int &countOne){
    countZero = 0;
    countOne = 0;

    for (const auto& row : matrix)
    {
        for (int val:row)
        {
            if (val == 0)
            {
                countZero++;
            }
            else{
                countOne++;
            }
        }
        
    }
    
}
int main(){
    
    srand(time(0));
    int row,col;
    cout<<"Enter no of Row and Column "<<endl;

    cin>>row>>col;          // only input ----> row column

    int mainCell = row*col;

    int minValue = min(row,col);        // taking minValue for iterating the size loop upto this

    ofstream outputFile("Data_Analysis.csv",ios::app);

    for (int size = 1; size <= 5; size++)
    {
        for (int percentage = 10; percentage <= 50; percentage+=5)
        {
            int reduce_cell = (row-(size-1))*(col-(size-1));
            // int no_obstacle = round(reduce_cell*(percentage/1000.0));

            for (int i = 0; i <= 10; i++)
            {
                string filename = "random_matrix.csv";


                generateRandomMatrix(row,col,round(reduce_cell*(percentage/1000.0)),filename); // this line


                cout<<"Random matrix generated successfully"<<endl;
                cout<<"Reading CSV file..."<<endl;
                vector<vector<int>> gridData = readCsvFile(filename);
                cout<<"Reading complete."<<endl;

                vector<vector<int>> compressedMatrixData = compressMatrix(gridData,size);
                cout<<"Compression complete..."<<endl;
                
                int countZero,countOne;

                countZeroAndOnes(compressedMatrixData,countZero,countOne);


                if (!outputFile.is_open())
                {
                    cout<<"Error opening CSV file...Exiting..."<<endl;
                    return 1;
                }
                else{
                    outputFile<<percentage<<","<<size<<","<<i<<","<<countOne<<":"<<reduce_cell<<","<<endl;
                }

            }
        }
        
    }
    outputFile.close();
    
    return 0;
}