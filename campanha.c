#include <stdio.h>
#include <stdlib.h>
#include "campanha.h"
 
// ---------------- DATA STRUCTURES ----------------

struct Stack* newStack(int capacity) {
  struct Stack *newStackPt = (struct Stack*) malloc(sizeof(struct Stack));

  newStackPt->maxsize = capacity;
  newStackPt->top = -1;
  newStackPt->items = (int*) malloc(capacity * sizeof(int));

  return newStackPt;
}
 
int stackCurrentSize(struct Stack *pt) {
  return pt->top + 1;
}

int stackIsEmpty(struct Stack *pt) {
  return pt->top == -1;
}

int stackIsFull(struct Stack *pt) {
  return pt->top == pt->maxsize - 1;
}

void stackPush(struct Stack *pt, int element) {
  if (stackIsFull(pt)) {
    printf("Overflow\nProgram Terminated\n");
    exit(EXIT_FAILURE);
  }

  pt->items[++pt->top] = element;
}
 
int stackPop(struct Stack *pt) {
  if (stackIsEmpty(pt)) {
    printf("Underflow\nProgram Terminated\n");
    exit(EXIT_FAILURE);
  }

  return pt->items[pt->top--];
}

struct List* newList() {
  struct List *newList;
  struct Node *temp;
  newList = (struct List *) malloc(sizeof(struct List));
  temp = (struct Node *) malloc(sizeof(struct Node));

  if(temp == NULL) {
    printf("nOut of Memory Space:n\n");
    exit(EXIT_FAILURE);
  }

  temp->value = -1;
  temp->next = NULL;

  newList->head = temp;
  newList->tail = newList->head;
  newList->size = 0;
  
  return newList;
}

void listPushBack(struct List* list, int value) {
  struct Node *temp;
  temp = (struct Node *)malloc(sizeof(struct Node));

  if(temp==NULL) {
    printf("nOut of Memory Space:n\n");
    return;
  }

  temp->next = NULL;
  temp->value = value;

  list->tail->next = temp;
  list->tail = temp;
}

// int* listRetrieveAsVector(struct List* list) {
//   int* newVector = (int*) malloc(list->size * sizeof(int));
//   struct Node* nodePtr = list->head;

//   if(list->size == 0) {
//     printf("nCan't retrieve empty list as vector:n\n");
//     return newVector;
//   }

//   for(int i = 0; i < list->size - 1; i++) {
//     nodePtr = nodePtr->next;
//     newVector[i] = nodePtr->value;
//   }

//   return newVector;
// }
// ---------------- HELPERS ----------------

int** createNullSquareMatrix(int matrixDimension) {
  int i,j;

  int** mat = (int**) malloc(matrixDimension* sizeof(int*));
  for(i = 0; i < matrixDimension; i++) {
    mat[i] = (int*) malloc(matrixDimension * sizeof(int));
    for(j = 0; j < matrixDimension; j++)
      mat[i][j] = 0;
  }

  return mat;
}

struct List** createEmptyAdjacentList(int listDimension) {
  struct List** list = (struct List**) malloc(listDimension * sizeof(struct List*));
  for(int i = 0; i < listDimension; i++) {
    list[i] = newList();
  }

  return list;
}

struct List** invertAdjacentList(struct List** L, int listSize) {
  struct List** newList = createEmptyAdjacentList(listSize);

  for(int i = 0; i < listSize; i++) {
    for(struct Node* it = L[i]->head->next; it != NULL; it = it->next)
      listPushBack(newList[it->value], i);
  }

  return newList;
}

int handleMatrixIdx(int initialIdx, int neg) {
  int newIndex = initialIdx * 2;
  newIndex = neg ? newIndex + 1 : newIndex;

  return newIndex;
}

void printMatrix(int** matrix, int matrixDimension) {
  // print columns identifiers
  printf("%5s"," ");
  for (int i = 0; i < matrixDimension; i++) printf("%4d ", i);
  printf("\n");
  printf("\n");


  for (int i = 0; i < matrixDimension; i++) {
    printf("%4d ", i);
    for(int j = 0; j < matrixDimension; j++) {
      printf("%4d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void printArray(int* array, int size) {
  printf("\n");
  for(int i = 0; i < size; i++) printf("%2d ", array[i]);
  printf("\n");
}

// ---------------- ALGORITHMS ----------------

void _dfsFillOrder(struct Graph G, int vertex, int* markedVector, struct Stack* S) {
  markedVector[vertex] = 1;

  for(struct Node* it = G.adjacentList[vertex]->head->next; it != NULL; it = it->next) {
    if(!markedVector[it->value]) {
      _dfsFillOrder(G, it->value, markedVector, S);
    }
  }

  stackPush(S, vertex);
}

void _dfsGetSCCs(struct Graph inverseGraph, int vertex, int* markedVector, int* SCCArr, int SCCCount) {
  markedVector[vertex] = 1;

  for(struct Node* it = inverseGraph.adjacentList[vertex]->head->next; it != NULL; it = it->next) {
    if(!markedVector[it->value]) {
      _dfsGetSCCs(inverseGraph, it->value, markedVector, SCCArr, SCCCount);
    }
  }

  SCCArr[vertex] = SCCCount;
}

void Kosaraju(struct Graph G) {
  int* StronglyConnectedComponents = (int*) malloc(G.verticesAmount * sizeof(int));
  int counter = 1;

  int* markedVector = (int*) malloc(G.verticesAmount * sizeof(int));
  for(int i = 0; i < G.verticesAmount; i++) markedVector[i] = 0;

  struct Stack* S = newStack(G.verticesAmount);

  for(int i = 0; i < G.verticesAmount; i++) {
    if(!markedVector[i])
      _dfsFillOrder(G, i, markedVector, S);
  }

  for(int i = 0; i < G.verticesAmount; i++) markedVector[i] = 0;

  struct Graph inverseGraph;
  inverseGraph.adjacentList = invertAdjacentList(G.adjacentList, G.verticesAmount);
  inverseGraph.verticesAmount = G.verticesAmount;

  // printf("normal\n");
  // for(int i = 0; i < G.verticesAmount; i ++) {
  //   printf("%d -> ", i);
  //   for(struct Node* it = G.adjacentList[i]->head->next; it != NULL; it = it->next) {
  //     printf("%d ", it->value);
  //   }
  //   printf("\n");
  // }

  // printf("inverso\n");
  // for(int i = 0; i < inverseGraph.verticesAmount; i ++) {
  //   printf("%d -> ", i);
  //   for(struct Node* it = inverseGraph.adjacentList[i]->head->next; it != NULL; it = it->next) {
  //     printf("%d ", it->value);
  //   }
  //   printf("\n");
  // }

  while(!stackIsEmpty(S)) {
    int currentVertex = stackPop(S);

    if(!markedVector[currentVertex]) {
      _dfsGetSCCs(inverseGraph, currentVertex, markedVector, StronglyConnectedComponents, counter);
      counter++;
    }
  }

  for (int i = 0; i < G.verticesAmount; i += 2) {
    if(StronglyConnectedComponents[i] == StronglyConnectedComponents[i+1]) {
      printf("nao\n");
      return;
    }     
  }

  printf("sim\n");
  return;
}

// ---------------- BUSINESS RULES ----------------

void handleAddAdjacentMatrix(int** matrix, struct ProposalSurveyInfo info) {
  const int NULL_PROPOSAL_VOTE = 0;

  if(info.firstProposal == NULL_PROPOSAL_VOTE) {
    if(info.secondProposal != NULL_PROPOSAL_VOTE)
      info.firstProposal = info.secondProposal;
    else
      return;
  } else if(info.secondProposal == NULL_PROPOSAL_VOTE)
    info.secondProposal = info.firstProposal;

  matrix[handleMatrixIdx(info.firstProposal - 1, !info.proposalsWereRejected)][handleMatrixIdx(info.secondProposal - 1, info.proposalsWereRejected)] = 1;
  matrix[handleMatrixIdx(info.secondProposal - 1, !info.proposalsWereRejected)][handleMatrixIdx(info.firstProposal - 1, info.proposalsWereRejected)] = 1;
}

void handleAddAdjacentList(struct List** adjList, struct ProposalSurveyInfo info) {
  const int NULL_PROPOSAL_VOTE = 0;

  if(info.firstProposal == NULL_PROPOSAL_VOTE) {
    if(info.secondProposal != NULL_PROPOSAL_VOTE)
      info.firstProposal = info.secondProposal;
    else
      return;
  } else if(info.secondProposal == NULL_PROPOSAL_VOTE)
    info.secondProposal = info.firstProposal;

  listPushBack(adjList[handleMatrixIdx(info.firstProposal - 1, !info.proposalsWereRejected)], handleMatrixIdx(info.secondProposal - 1, info.proposalsWereRejected));
  listPushBack(adjList[handleMatrixIdx(info.secondProposal - 1, !info.proposalsWereRejected)], handleMatrixIdx(info.firstProposal - 1, info.proposalsWereRejected));
}