#include <stdio.h>
#include <stdlib.h>

// ---------------- DATA STRUCTURES ----------------

struct Stack {
  int maxsize; 
  int top;
  int *items;
};

struct Stack* newStack(int capacity);

int stackCurrentSize(struct Stack *pt);

int stackIsEmpty(struct Stack *pt);

int stackIsFull(struct Stack *pt);

void stackPush(struct Stack *pt, int element);

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

struct List* newList();

void listPushBack(struct List* list, int value);

// ---------------- HELPERS ----------------

int** createNullSquareMatrix(int matrixDimension);

struct List** createEmptyAdjacentList(int listDimension);

int handleMatrixIdx(int initialIdx, int neg);

void printMatrix(int** matrix, int matrixDimension);

void printArray(int* array, int size);

// ---------------- ALGORITHMS ----------------

struct Graph {
  struct List **adjacentList;
  int verticesAmount;
};

void _dfsFillOrder(struct Graph G, int vertex, int* markedVector, struct Stack* S);

void _dfsGetSCCs(struct Graph G, int vertex, int* markedVector, int* SCCArr, int SCCCount);

void Kosaraju(struct Graph G);

// ---------------- BUSINESS RULES ----------------

struct ProposalSurveyInfo {
  unsigned int firstProposal;
  unsigned int secondProposal;
  int proposalsWereRejected;
};

void handleAddAdjacentMatrix(int** matrix, struct ProposalSurveyInfo info);

void handleAddAdjacentList(struct List** adjList, struct ProposalSurveyInfo info);