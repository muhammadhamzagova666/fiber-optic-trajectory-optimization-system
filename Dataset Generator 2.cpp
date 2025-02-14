// C++: Dataset Generator 2.cpp
// Fiber Optic Trajectory Optimization System
//
// This module reads an existing dataset ("file.txt") and generates a new dataset ("file2.txt").
// For each edge, it recalculates weights to ensure that every weight is at least 1000.
// This extra step assures that the graph constructed later in the system has valid weights.

#include <bits/stdc++.h>
#include <fstream>

#define nodes 100          // Total number of nodes for the graph (must match the original dataset)
#define weight 10000       // Maximum possible weight value; new weights will be in the range [1000, weight)

using namespace std;

/**
 * @brief Main entry point for the Dataset Generator 2 module.
 *
 * This function opens the original dataset file ("file.txt") for reading and creates a new dataset file ("file2.txt").
 * It reads the number of vertices from the first line, then processes each subsequent line (edge data).
 * For every edge, it reads source, destination, and weight; however, it recalculates the weight until it satisfies
 * the minimum threshold of 1000. This ensures all edges used further in the project have valid weight values.
 *
 * @return int Exit status of the program.
 */
int main()
{
    // Open file streams for reading from the original dataset and writing to the new dataset.
    fstream myfile, myfile2;
    myfile.open("file.txt", ios::in);
    myfile2.open("file2.txt", ios::out);
    
    int vertices, x, y, z;
    // Read the total number of vertices from the input file.
    myfile >> vertices;
    // Write the total number of vertices to the new dataset's first line.
    myfile2 << vertices;
    
    // Process each edge in the input file until reaching the end.
    while (!(myfile.eof()))
    {
        // Start a new line for each edge in the output file.
        myfile2 << "\n";
        
        // Read an edge's source, destination, and original weight.
        myfile >> x >> y >> z;
        // Write the source and destination directly to the output.
        myfile2 << x << " " << y << " ";
        
        // Recalculate the weight to ensure it meets the minimum threshold of 1000.
        // This loop guarantees that even if the original weight is below the threshold,
        // a valid weight will be generated.
        do {
            z = rand() % weight;
        } while(z < 1000);
        
        // Write the recalculated, valid weight to the new dataset.
        myfile2 << z;
    }
    
    // Close the file streams after processing is complete.
    myfile.close();
    myfile2.close();
    
    return 0;
}