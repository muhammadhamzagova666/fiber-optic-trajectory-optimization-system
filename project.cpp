#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <functional>

using namespace std;

/**
 * @brief Moves the console cursor to the specified coordinates.
 *
 * Uses Windows API functions to set the cursor position, allowing for
 * dynamic text placement in the console interface.
 *
 * @param x Column value.
 * @param y Row value.
 */
void gotoxy(int x, int y)  
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

/**
 * @class Log_Sign
 * @brief Provides user login and registration functionality.
 *
 * This class implements methods for authenticating existing users 
 * and registering new users. It uses a simple file-based approach to 
 * store and retrieve user credentials.
 */
class Log_Sign 
{
    private:
        string UserName;        ///< Stores the username input by the user.
        string Password = "";   ///< Stores the password input (masked during entry).
        string User;            ///< Temporary holder for file username data.
        string Pass;            ///< Temporary holder for file password data.
    public:
        Log_Sign() { }   // Default constructor
    
        /**
         * @brief Prompts the user for login credentials and validates them.
         *
         * Clears the console before prompting and hides the entered password.
         * Reads credentials from "userData.txt" and compares them with
         * the provided input. Allows up to three attempts before failing.
         *
         * @return true if credentials match; false otherwise.
         */
        bool Login()  
        {
            int count = 0;
            static int temp = 1;  // Static variable to track login attempt count
            system("CLS");
            gotoxy(15,2);
            cout << "Enter User Name: ";
            fflush(stdin);
            getline(cin, UserName);
            
            gotoxy(15,3);
            cout << "Enter User Password: ";
            fflush(stdin);
            // Hide password characters for security
            char ch;
            ch = _getch();
            Password.clear();
            while (ch != 13) // ASCII 13 is the Enter key
            {
                Password.push_back(ch);
                cout << '*';
                ch = _getch();
            }
            
            ifstream myfile("userData.txt");
            while (myfile >> User >> Pass)
            {
                if (User == UserName && Pass == Password)
                {
                    count = 1;
                }
            }
            myfile.close();
            
            if (count == 1)
            {
                cout << "\nLOGIN APPROVED" << endl;
                system("PAUSE");
                return true;
            }
            else
            {
                temp += 1;
                if (temp > 3) // Limit login attempts to 3
                {
                    temp = 1;
                    return false;
                }
                else
                {
                    cout << "\nInvalid Input! Please try again." << endl;
                    system("PAUSE");
                    system("CLS");
                }
            }
            return false; // Default return if conditionals fall through
        }
    
        /**
         * @brief Registers a new user by collecting a username and password.
         *
         * Clears the console and prompts the user to enter new credentials.
         * The password is masked during input. Credentials are appended to "userData.txt".
         */
        void Signup() 
        {
            system("CLS");
            gotoxy(40,8);
            cout << "\nEnter User Name: ";
            cin >> UserName;
            cout << "\nEnter User Password: ";
            fflush(stdin);
            char ch;
            ch = _getch();
            while (ch != 13) // Continue until Enter key is pressed
            {
                Password.push_back(ch);
                cout << '*';
                ch = _getch();
            }
    
            ofstream file("userData.txt", ios::app);
            file << UserName << " " << Password << endl;
            file.close();
            
            cout << "\nRegistration Successful" << endl;
            system("PAUSE");
        }
};

/**
 * @struct listNode
 * @brief Node for use in a linked list.
 *
 * Represents an edge in the graph with a target vertex and corresponding weight.
 */
struct listNode 
{
    int target;         ///< Target vertex.
    int weight;         ///< Edge weight.
    listNode * next;    ///< Pointer to the next node.
    
    /**
     * @brief Constructs a new listNode.
     *
     * @param t Target vertex.
     * @param w Weight of the edge.
     */
    listNode(int t, int w) { target = t, weight = w, next = NULL; }
    ~listNode() { next = NULL; }
};

/**
 * @class List
 * @brief A simple linked list implementation used for representing adjacency lists.
 */
class List 
{
    private:
        listNode * head;   ///< Pointer to the first node of the list.
    public:
        List() { head = NULL; }
        
        /**
         * @brief Inserts a new node at the beginning of the list.
         *
         * This method is used for quick insertion when building the adjacency list.
         *
         * @param x Target vertex.
         * @param w Weight associated with the vertex.
         */
        void insertAtStart(int, int);
        
        /**
         * @brief Retrieves the head of the list.
         *
         * @return Pointer to the first listNode.
         */
        listNode* getHead() { return head; }
        
        ~List();
};

void List::insertAtStart(int x, int w)
{
    listNode * n = new listNode(x, w);
    if (!head)
        head = n;
    else
    {
        n->next = head;
        head = n;
    }
}

List::~List()
{
    while (head)
    {
        listNode * n = head->next;
        delete head;
        head = n;
    }
}

/**
 * @struct heapItem
 * @brief Represents an item in the min-heap.
 *
 * Stores a value and its key used for heap comparisons.
 */
struct heapItem 
{
    int value;  ///< Vertex identifier.
    int key;    ///< Key value used to determine heap order.
    
    /**
     * @brief Constructs a new heapItem.
     *
     * @param v Vertex index.
     * @param k Associated key value.
     */
    heapItem(int v, int k) { value = v, key = k; }
};

/**
 * @struct minHeap
 * @brief Implements a minimum heap for use in Prim's algorithm.
 *
 * The min heap is used to efficiently retrieve the vertex with the minimum key value.
 */
struct minHeap 
{
    int size;         ///< Current number of elements.
    int capacity;     ///< Maximum capacity of the heap.
    int *position;    ///< Helps track the position of vertices in the heap.
    heapItem** heapArray;   ///< Array of pointers to heapItem objects.
    
    /**
     * @brief Constructs a minHeap with the given capacity.
     *
     * @param c Capacity for the heap.
     */
    minHeap(int);
    
    /**
     * @brief Swaps two heap items.
     *
     * @param x Pointer to the first heap item.
     * @param y Pointer to the second heap item.
     */
    void swapHeapItem(heapItem **, heapItem **);
    
    /**
     * @brief Maintains the min-heap property beginning at index i.
     *
     * @param i Starting index for heapify.
     */
    void minHeapify(int);
    
    /**
     * @brief Extracts the minimum element from the heap.
     *
     * @return Pointer to the minimum heapItem.
     */
    heapItem* extractMin();
    
    /**
     * @brief Decreases the key value of a given vertex.
     *
     * Updates the key and reorders the heap to maintain the heap property.
     *
     * @param v Vertex index.
     * @param k New key value.
     */
    void decreaseKey(int v, int k);
    
    ~minHeap();
};

minHeap::minHeap(int c) 
{
    capacity = c;
    size = 0;
    position = new int[capacity];
    heapArray = new heapItem*[capacity];
    for (int i = 0; i < capacity; i++)
        heapArray[i] = NULL;
}

void minHeap::swapHeapItem(heapItem** x, heapItem** y)
{
    heapItem* aux = *x;
    *x = *y;
    *y = aux;
}

void minHeap::minHeapify(int i)
{
    int index = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    // Compare left child with current minimum
    if (l < size && heapArray[l]->key < heapArray[index]->key)
        index = l;
    // Compare right child with current minimum
    if (r < size && heapArray[r]->key < heapArray[index]->key)
        index = r;
    if (index != i)
    {
        heapItem * indexItem = heapArray[index], *iItem = heapArray[i];
        // Update positions for swapped nodes
        position[indexItem->value] = i;
        position[iItem->value] = index;
        // Swap nodes
        swapHeapItem(&heapArray[index], &heapArray[i]);
        minHeapify(index);
    }
}

heapItem* minHeap::extractMin() 
{
    if (size == 0)
        return NULL;
    heapItem * rootItem = heapArray[0];
    heapItem * lastItem = heapArray[size - 1];
    heapArray[0] = lastItem;
    // Update positions for correct ordering
    position[rootItem->value] = size - 1;
    position[lastItem->value] = 0;
    --size;
    minHeapify(0);
    return rootItem;
}

void minHeap::decreaseKey(int v, int k) 
{
    int index = position[v];
    heapArray[index]->key = k;
    // Bubble up until the heap property is restored
    while (index && heapArray[index]->key < heapArray[(index - 1) / 2]->key)
    {
        // Swap with parent
        position[heapArray[index]->value] = (index - 1) / 2;
        position[heapArray[(index - 1) / 2]->value] = index;
        swapHeapItem(&heapArray[index], &heapArray[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

minHeap::~minHeap()
{
    for (int i = 0; i < capacity; i++)
    {
        if (heapArray[i])
            delete heapArray[i];
    }
    delete[] heapArray;
}

/**
 * @class Graph
 * @brief Represents an undirected graph and provides MST functionalities.
 *
 * The Graph class supports edge insertion, printing the graph,
 * and generating a Minimum Spanning Tree (MST) using Prim's algorithm.
 */
class Graph 
{
        int numOfVertices;  ///< Total number of vertices in the graph.
        List *adjList;      ///< Array of adjacency lists for each vertex.
    public:
        /**
         * @brief Constructs a new Graph.
         *
         * @param n Number of vertices.
         */
        Graph(int n) { numOfVertices = n, adjList = new List[numOfVertices]; }
        
        /**
         * @brief Inserts an undirected edge between two vertices.
         *
         * Updates the adjacency list for both vertices.
         *
         * @param x Vertex one.
         * @param y Vertex two.
         * @param w Weight of the edge.
         */
        void insertEdge(int, int, int);
        
        /**
         * @brief Returns the number of vertices in the graph.
         *
         * @return Number of vertices.
         */
        int getNumOfVertices() { return numOfVertices; }
        
        /**
         * @brief Constructs the MST using Prim's algorithm.
         *
         * @return Pointer to an integer array representing the MST.
         */
        int * make_MST_via_PrimAlgo();
        
        /**
         * @brief Returns the weight of the edge between given vertices.
         *
         * @param x Vertex one.
         * @param y Vertex two.
         * @return Edge weight.
         */
        int getWeightOfEdge(int x, int y);
        
        /**
         * @brief Prints the edges and weights of the MST.
         *
         * @param MST Array representing the MST.
         */
        void printMST(int []);
        
        /**
         * @brief Calculates the total weight of the MST.
         *
         * @param MST Array representing the MST.
         * @return Total weight.
         */
        int getMSTWeight(int []);
        
        /**
         * @brief Prints the entire graph.
         */
        void printGraph(); 
        
        ~Graph() { delete[] adjList; }
};

void Graph::insertEdge(int x, int y, int w)
{
    // Insert the edge in both directions as the graph is undirected
    adjList[y].insertAtStart(x, w);
    adjList[x].insertAtStart(y, w);
}

int* Graph::make_MST_via_PrimAlgo() 
{
    // MST[] will store the parent array which represents the MST.
    int* MST = new int[numOfVertices];
    // k[] stores the minimum weight edge to connect each vertex.
    int* k = new int[numOfVertices];
    minHeap* h = new minHeap(numOfVertices);
    
    // Initialize all vertices with infinite key value except first vertex.
    for (int i = 1; i < numOfVertices; i++)
    {
        MST[i] = 0;
        k[i] = INT_MAX;
        h->heapArray[i] = new heapItem(i, k[i]);
        h->position[i] = i;
    }
    k[0] = 0; // Start with the first vertex
    h->heapArray[0] = new heapItem(0, 0);
    h->position[0] = 0;
    h->size = numOfVertices;
    
    // Extract minimum key vertex and update adjacent vertices.
    while (h->size != 0)
    {
        heapItem* minItem = h->extractMin();
        int num = minItem->value;
        listNode* curr = adjList[num].getHead();
        while (curr)
        {
            int t = curr->target;
            // Check if the target is still in heap and if current edge offers a lower weight.
            if (h->position[t] < h->size && curr->weight < k[t])
            {
                k[t] = curr->weight;
                MST[t] = num;
                h->decreaseKey(t, k[t]);
            }
            curr = curr->next;
        }
    }
    return MST;
}

int Graph::getWeightOfEdge(int x, int y)
{
    listNode * n = adjList[x].getHead();
    while (n)
    {
        if (n->target == y)
            return n->weight;
        n = n->next;
    }
    return -1; // Return error value if no edge exists
}

void Graph::printGraph() 
{
    // Iterate through each vertex and print its adjacent nodes.
    for (int i = 0; i < numOfVertices; i++)
    {
        listNode* temp = adjList[i].getHead();
        cout << "\nNode (" << i << ")";
        while (temp != NULL)
        {
            cout << " --- (" << temp->target << ", " << temp->weight << ")";
            temp = temp->next;
        }
        cout << endl;
    }
}

void Graph::printMST(int MST[]) 
{
    // Check if an MST has been computed before printing.
    if (MST)
    {
        cout << "\nEdge           Weight\n";
        for (int i = 1; i < numOfVertices; ++i)
        {
            cout << MST[i] << " - " << i;
            // Adjust spacing for readability.
            int x = 0;
            if (MST[i] > 9)
                x = 1;
            else if (MST[i] > 99)
                x = 2;
            else if (MST[i] > 999)
                x = 3;
            if (i > 9)
                x += 1;
            else if (i > 99)
                x += 2;
            else if (i > 999)
                x += 3;
            for (int j = 0; j < 12 - x; j++)
                cout << " ";
            cout << getWeightOfEdge(MST[i], i) << endl;
        }
        cout << endl;
    }
    else
    {
        cout << "\n<ERROR! NO MST HAS BEEN MADE YET>\n\n";
    }
}

int Graph::getMSTWeight(int MST[])
{
    int totalWeight = -1;
    if (MST)
    {
        totalWeight = 0;
        for (int i = 1; i < numOfVertices; i++)
            totalWeight += getWeightOfEdge(MST[i], i);	
    }
    return totalWeight;
}

/**
 * @brief Displays the main menu and receives the user's choice.
 *
 * Provides options for creating an MST, printing the MST,
 * calculating the MST weight, or printing the entire graph.
 *
 * @return Integer representing the user-selected menu option.
 */
int printMenu() 
{
    int n = 0;
    cout << "                                      -----------------\n"
         << "                                      | PROJECT FOTOS |\n"
         << "                                      -----------------\n"
         << "---------------------------------------------------------------------------------------------\n"
         << "|                          FIBER OPTIC TRAJECTORY OPTIMIZING SYSTEM                         |\n"
         << "---------------------------------------------------------------------------------------------\n"
         << "| 0 = EXIT PROGRAM                                                                          |\n"
         << "| 1 = MAKE MST VIA PRIM'S ALGORITHM                                                         |\n"
         << "| 2 = PRINT MST                                                                             |\n"
         << "| 3 = CALCULATE MST WEIGHT                                                                    |\n"  
         << "| 4 = PRINT GRAPH                                                                           |\n"
         << "---------------------------------------------------------------------------------------------\n\n"
         << "Enter your choice: ";
    cin >> n;
    while (n < 0 || n > 4)
    {
        cout << "\n<ERROR! INVALID INPUT>\nEnter again: ";
        cin >> n;
    }
    return n;
}

/**
 * @brief Displays an animated introduction to the system.
 *
 * Uses cursor positioning and timed output to create a dynamic introduction
 * that includes the project title and team member names.
 */
void Intro(void) 
{
    system("CLS");
    string projectTitle = "|FIBER OPTIC TRAJECTORY OPTIMIZING SYSTEM|";
    gotoxy(50, 2);
    cout << "\n-------------------------------------------------------------------------------------------------------------------";
    gotoxy(40,4);
    // Print project title with a slight delay for each character for effect.
    for (char ch : projectTitle)
    {
        Sleep(20);
        cout << ch;
    }
    cout << "\n-------------------------------------------------------------------------------------------------------------------";
    
    string S = "Muhammad Talha 21K-3349 ";
    string I = "Muhammad Taha  21k-3316";
    string Y = "Muhammad Hamza 21K-4579";
    gotoxy(42,11);
    for (char ch : S)
    {
        Sleep(50);
        cout << ch;
    }
    gotoxy(42,12);
    for (char ch : I)
    {
        Sleep(50);
        cout << ch;
    }
    gotoxy(42,13);
    for (char ch : Y)
    {
        Sleep(50);
        cout << ch;
    }
}

/**
 * @brief Presents the login/signup menu and validates user selection.
 *
 * The user chooses to either log in or register. In case of an invalid entry,
 * the program exits with an error message.
 *
 * @return Integer indicating login success (non-zero for success).
 */
int mainMenu(void) 
{
    int choice2;
    int success;
    gotoxy(60, 15);
    cout << "\n1. Login\n2. Register\n";
    cout << "Enter desired option: ";
    cin >> choice2;
    Log_Sign A;
    switch (choice2)
    {
    case 1:
x:
        success = A.Login();
        break;
    case 2:
        A.Signup();
        goto x;
        break;
    default:
        cout << "\nInvalid Data Entry!!";
        exit(EXIT_FAILURE);
        break;
    }
    return success;	
}

/**
 * @brief Main entry point of the program.
 *
 * Initializes the system, processes user authentication, constructs the graph from file data,
 * and then allows the user to interact with the MST and graph options.
 *
 * @return Exit status.
 */
int main(void) 
{
    system("color f4");
    Intro();
z:
    if (mainMenu())
    {
        // Open file containing graph edges.
        ifstream fin("file.txt", ios::in);
        if (!fin)
        {
            cout << "\n<ERROR! UNABLE TO OPEN FILE>\n"
                 << "The required file is missing from the designated path.\n\n";
            exit(EXIT_FAILURE);
        }
        cout << endl;
        int nOfNodes = 0;
        fin >> nOfNodes;
        Graph *G = new Graph(nOfNodes);
        int x = 0, y = 0, w = 0;
        // Read and add edges until end-of-file is reached.
        while (fin >> x >> y >> w)
        {
            cout << "Adding edge '" << x << " - " << y << "' with weight " << w << "...\n";
            G->insertEdge(x, y, w);
        }
        fin.close();
        cout << "\nAll edges have been successfully added to the graph.\n\n";
        system("pause");
        system("cls");
        int * mst = NULL;
        int m = printMenu();
        // Process user's menu selections until exit option is chosen.
        while (m != 0)
        {
            if (m == 1)
            {
                mst = G->make_MST_via_PrimAlgo();
                cout << "\nMST has been created successfully using Prim's Algorithm.\n\n";
            }
            else if (m == 2)
                G->printMST(mst);
            else if (m == 3)
            {
                if (mst)
                    cout << "\nTotal weight of MST: " << G->getMSTWeight(mst) << endl << endl;
                else if(G->getMSTWeight(mst) == -1)
                    cout << "\n<ERROR! NO MST HAS BEEN CREATED YET>\n\n";
            }
            else
            {
                G->printGraph();
            }
            system("pause");
            system("cls");
            m = printMenu();
        }
        delete G;
    }
    else
    {
        system("CLS");
        goto z;
    }
    system("CLS");
    // Display final project information.
    string p1 = "|DATA STRUCTURE SEMESTER PROJECT|";
    string p2 = "|FIBER OPTIC TRAJECTORY OPTIMIZING SYSTEM|";
    gotoxy(50, 2);
    for (char ch : p1)
    {
        Sleep(15);
        cout << ch;
    }
    cout << "\n-------------------------------------------------------------------------------------------------------------------";
    gotoxy(46,4);
    for (char ch : p2)
    {
        Sleep(20);
        cout << ch;
    }
    cout << "\n-------------------------------------------------------------------------------------------------------------------";
    
    string instructor = "Dr. Jawwad Ahmed Shamsi";
    string member1 = "Muhammad Talha 21K-3349 ";
    string member2 = "Muhammad Taha  21k-3316";
    string member3 = "Muhammad Hamza 21K-4579";
    
    gotoxy(35, 11);
    cout << "Professor:" << endl;
    gotoxy(42, 12);
    for (char ch : instructor)
    {
        Sleep(50);
        cout << ch;	
    }
    cout << endl << endl;
    gotoxy(35,16);
    cout << "Group Members:" << endl;
    
    gotoxy(42,17);
    for (char ch : member1)
    {
        Sleep(50);
        cout << ch;
    }
    gotoxy(42,18);
    for (char ch : member2)
    {
        Sleep(50);
        cout << ch;
    }
    gotoxy(42,19);
    for (char ch : member3)
    {
        Sleep(50);
        cout << ch;
    }
    
    return 0;
}