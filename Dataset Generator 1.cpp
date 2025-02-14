// C++: Dataset Generator 1.cpp
// Fiber Optic Trajectory Optimization System
//
// This module generates a random dataset for graph construction.
// The dataset consists of a fixed number of nodes and edges with weights 
// no less than a minimum threshold. This generated file ("file.txt") is later
// used by the main project to construct graph structures.

#include <bits/stdc++.h>
#include <fstream>

#define NODES 100          // Total number of nodes/vertices for the graph
#define MAX_WEIGHT 10000   // Upper limit for edge weights; weight values will be in the range [1000, MAX_WEIGHT)

using namespace std;

/**
 * @brief Entry point for the Dataset Generator.
 *
 * Generates a random dataset and writes it to "file.txt". The first line contains the
 * total number of nodes. Subsequent lines each represent an edge between two nodes with an associated
 * weight. For better randomness and to ensure edges have a minimum weight, this module verifies that every
 * generated weight is at least 1000.
 *
 * @return int Exit status of the program.
 */
int main()
{
    // Output file stream for writing the dataset.
    fstream myfile;
    myfile.open("file.txt", ios::out);
    
    // Write total number of nodes as the first line.
    myfile << NODES << "\n";
    
    int x = 0, y = 1, z;
    
    // Generate the first edge explicitly, ensuring the weight meets the minimum threshold.
    do {
        z = rand() % MAX_WEIGHT;
    } while(z < 1000);
    
    // Write the first edge from node 0 to node 1.
    myfile << x << " " << y << " " << z << "\n";
    
    // Generate subsequent edges ensuring that:
    // 1. Source and destination nodes are not the same.
    // 2. Neither of the two nodes is the '0' node (reserved for the initial edge).
    for (int i = 0; i < NODES - 1; i++)
    {
        // Keep generating random nodes until they form a valid unique edge.
        do {
            x = rand() % NODES;
            y = rand() % NODES;
        } while(x == y || x == 0 || y == 0);
        
        // Generate a valid weight that is no less than 1000.
        do {
            z = rand() % MAX_WEIGHT;
        } while(z < 1000);
        
        // Write the valid edge to the file in the format: source destination weight.
        myfile << x << " " << y << " " << z << "\n";
    }
    
    // Close file after dataset generation is complete.
    myfile.close();
    
    return 0;
}