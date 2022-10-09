#include <stdio.h>
#include <stdlib.h>

// ---------------- CONSTANTS ----------------

#define TRUE 1;
#define FALSE 0;

// ---------------- DATA STRUCTURES ----------------

struct Stack {
  int maxsize; 
  int top;
  int *items;
};

/**
 * @brief Stack factory, responsible for receiving the capacity and retrieving
 * a Stack instance with the provided capacity.
 * 
 * @param capacity Max number of elements in the stack
 * @returns Pointer for a Stack instance with the provided capacity.
 */
struct Stack* newStack(int capacity);

/**
 * @brief Stack helper function, responsible for returning true in the case of
 * the parameter instance of one Stack has nos elements.
 * 
 * @param pt Pointer for a Stack instance.
 * @returns Boolean value indicating if the Stack is empty.
 */
int stackIsEmpty(struct Stack *pt);

/**
 * @brief Stack helper function, responsible for returning true in the case of
 * the parameter instance of one Stack is with it's capacity full of elements.
 * 
 * @param pt Pointer for a Stack instance.
 * @returns Boolean value indicating if the Stack is full.
 */
int stackIsFull(struct Stack *pt);

/**
 * @brief Stack helper function, responsible for stacking an provided element in
 * the top of the parameter Stack instance.
 * 
 * @param pt Pointer for a Stack instance.
 * @param element Integer value to be added to the Stack.
 */
void stackPush(struct Stack *pt, int element);

/**
 * @brief Stack helper function, responsible for removing the top element of the
 * provided Stack instance and return it.
 * 
 * @param pt Pointer for a Stack instance.
 * @returns The value of the popped element.
 */
int stackPop(struct Stack *pt);

struct Node {
  int value;
  struct Node *next;
};

struct List {
  struct Node *head;
  struct Node *tail;
  int size;
};

/**
 * @brief Linked list factory, responsible for retrieving a empty List instance.
 * List head is not considered a List member in that implementation.
 * 
 * @returns Pointer for a List instance.
 */
struct List* newList();

/**
 * @brief List helper function, responsible for adding the provided value in the 
 * end of the parameter List instance.
 * 
 * @param list Pointer for a List instance.
 * @param value Integer value to be added in the end of the List.
 */
void listPushBack(struct List* list, int value);

// ---------------- HELPERS ----------------

/**
 * @brief Helper function, responsible for creating an Array of Lists (Adjacency
 * List) with the provided dimension.
 * 
 * @param listDimension The size of the Array of Lists.
 * @returns An Array with empty Lists (Adjacency List).
 */
struct List** createEmptyAdjacencyList(int listDimension);

/**
 * @brief Helper function, responsible for receiving a Adjacency List and retrieve
 * it as another Adjacency List with inverted connections(Ex: x -> y turns into
 * y -> x).
 * 
 * @param L And Adjacency List instance.
 * @param listSize The size of the Array of Lists.
 * @returns The inverted Adjacency List.
 */
struct List** invertAdjacencyList(struct List** L, int listSize);

// ---------------- ALGORITHMS ----------------

struct Graph {
  struct List **adjacencyList;
  int verticesAmount;
};

/**
 * @brief Kosaraju Algorithm internal function, responsible for executing an DFS
 * in the provided graph and push the vertex value to the Stack when finish
 * visiting all it's neighbors.
 * 
 * @param G An Graph instance that uses Adjacency List representation.
 * @param vertex The vertex being currently visited.
 * @param markedVector A boolean array that represents the visited vertexes.
 * @param S A Stack instance to push the vertexes values after visiting.
 */
void _dfsFillOrder(struct Graph G, int vertex, int* markedVector, struct Stack* S);

/**
 * @brief Kosaraju Algorithm internal function, responsible for executing an DFS
 * in the provided graph and assign for the ended visited vertexes it's SCC code.
 * 
 * @param inverseGraph An Inverse Graph instance that uses Adjacency List representation.
 * @param vertex The vertex being currently visited.
 * @param markedVector A boolean array that represents the visited vertexes.
 * @param SCCArr A array containing the SCC code for each Graph Vertex.
 * @param SCCCount The code of the SCC currently being visited.
 */
void _dfsGetSCCs(struct Graph inverseGraph, int vertex, int* markedVector, int* SCCArr, int SCCCount);

/**
 * @brief Kosaraju Algorithm implementation, responsible for receiving an arbitrary
 * 2-SAT Graph and providing the boolean value about it's satisfiability.
 * 
 * @param G An 2-SAT Graph instance that uses Adjacency List representation.
 * @returns True if the represented CNF expression is satisfiable and False otherwise.
 */
int Kosaraju(struct Graph G);

// ---------------- BUSINESS RULES ----------------

/**
 * @brief Business Rule function, responsible for receiving an vertex idx and the
 * information if it's value is inverted and then retrieve a transformed consistent
 * value.
 * 
 * @param initialIdx The initial value of the idx before being transformed.
 * @param neg The information if the value is inverted.
 * @returns The new value that represents the vertex.
 */
int handleCalculateVertexValue(int initialIdx, int neg);

struct ProposalSurveyInfo {
  unsigned int firstProposal;
  unsigned int secondProposal;
  int proposalsWereRejected;
};

/**
 * @brief Business Rule function, responsible for receiving a ProposalSurveyInfo 
 * instance and create connections using it on the parameter Adjacency List.
 * 
 * @param adjList And Adjacency List instance that will contain the proposals connections.
 * @param info An instance of ProposalSurveyInfo containing the two involved proposal
 * and the information about if they were rejected.
 */
void handleAddAdjacencyList(struct List** adjList, struct ProposalSurveyInfo info);