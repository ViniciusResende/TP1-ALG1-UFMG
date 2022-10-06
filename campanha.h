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

// ---------------- HELPERS ----------------

int** createNullSquareMatrix(int matrixDimension);

int handleMatrixIdx(int initialIdx, int neg);

void printMatrix(int** matrix, int matrixDimension);

void printArray(int* array, int size);

// ---------------- ALGORITHMS ----------------

struct Graph {
  int **adjacentMatrix;
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