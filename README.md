# Project_Smart_Stick

# This project is based on IoT

# in this project we are trying to help blind people around us making this stick smart

# here in the obstacle.csv file we actually have taken a 2D array which represents a static area.
    # in this matrix there are combination of 0s and 1s which actually indicates that 
        # 0 are the free paths in the area 
        # 1 are the obstacles in the matrix or the area , it can be a tree or chair or table , it can be any obstacle .
    # now our aim is to direct the pointer to move in the right direction with the minimum path and reach it ot the destination without any problem 
        # here we are representing a point instead of a real human for generating the appropriate algorithm for this stick

# now in the Astar2.cpp file we actually applied the combination of A* and Dijstra's algorithm to find the shortest path throgh 0s
    # here you just have to Input a Source co-ordinate and a Destination co-ordinate
    # it will give output of the path it follow fo the destination 
    # for more info please check the code there are comment lines provided in every line

# after crating a single co-ordinate shortest path we are getting some complexity
    # if the person needs more than one coordinate to move 
    # if there are no path then we can't map for the specific person

# then we decided to make a program which will make it possible 

# but after getting some complexities we finally found out an approach in which 
    # we will take a 2D matrix as input and we will compress the matrix according to the size of the person

# in matrix_compressed.cpp we actually have solved the above problem
    # we did the column reduction and row reduction in this program
    # for more details you can check the code

# then we applied the shortest path program in this compressed matrix

# in the merged_prog2.cpp we did the above technique
    # first we included the obstacle.csv file 
    # then we compressed it and has taken the newly generated graph in a matrix
    # then we applied the concept of Astar2.cpp but in this program we make the code much short as compare to the previous code
    # and we also added 8 directions instead of 4 directions (we used 4 directions in Astar2.cpp)
    
    
