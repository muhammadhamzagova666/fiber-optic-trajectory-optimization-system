# Fiber Optic Trajectory Optimization System

**Tagline:** Streamline Fiber Optic Network Planning with Advanced Graph Algorithms

## Overview

The Fiber Optic Trajectory Optimization System is a C++ console application designed to optimize the routing of fiber optic networks. By leveraging graph algorithms such as Prim's algorithm for Minimum Spanning Tree (MST) generation, the system efficiently computes optimal network paths and validates data through dynamically generated datasets.

Key features include:
- **Graph Construction:** Build a graph from edge datasets.
- **Dataset Generation:** Two modules to create and validate randomized datasets with minimum weight constraints.
- **Network Optimization:** Compute the MST to determine the most efficient routing paths.
- **User Interface:** Interactive console-based menus for login, registration, and graph visualization.
- **Dynamic Output:** Use of Windows API for animated text and cursor positioning to enhance user interaction.

## Technology Stack

- **Language:** C++
- **Platform:** Windows console application
- **Libraries:** Standard C++ library, Windows API

## Target Users

This project is intended for developers, network engineers, and researchers who are interested in fiber optic network design and optimization. Contributors with experience in C++ and graph algorithms are welcome to help enhance the system.

## Installation & Setup

1. **Clone the Repository:**

   ```sh
   git clone https://github.com/muhammadhamzagova666/fiber-optic-trajectory-optimization-system.git
   cd fiber-optic-trajectory-optimization-system
   ```

2. **Build the Project:**

   Open the project in your preferred IDE (e.g., Visual Studio Code). Ensure you have a C++ compiler installed.

   For a quick build via command line:
   ```sh
   g++ project.cpp -o FiberOpticTrajectoryOptimizationSystem -std=c++11
   ```

3. **Dataset Generation:**

   Generate the dataset using the provided modules:
   ```sh
   g++ "Dataset Generator 1.cpp" -o DatasetGenerator1 -std=c++11
   ./DatasetGenerator1

   g++ "Dataset Generator 2.cpp" -o DatasetGenerator2 -std=c++11
   ./DatasetGenerator2
   ```

4. **Run the Main Application:**

   ```sh
   ./FiberOpticTrajectoryOptimizationSystem
   ```

## Usage Example

1. **Launch the system:**  
   Run the compiled executable. You will be greeted with an animated introduction screen.

2. **User Authentication:**  
   Choose to login or register. Credentials are verified against a file-based database.

3. **Graph Operations:**  
   After a successful login, the system loads the dataset from `file.txt` and allows you to:
   - Create a Minimum Spanning Tree (MST)
   - Print the MST details and calculate its total weight
   - Visualize the entire graph structure

4. **Exiting:**  
   Use the menu option to exit the program safely.

## Contribution Guidelines

Contributions to the Fiber Optic Trajectory Optimization System are welcome! To contribute:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Write clear, concise, and well-commented code. Follow the existing documentation style.
4. Submit a pull request with a detailed explanation of your changes.
5. Ensure all new features or changes include appropriate tests and documentation updates.

---

For any questions or additional information, please open an issue or contact [muhammadhamzagova666](https://github.com/muhammadhamzagova666).

Enjoy optimizing your fiber optic trajectories!
