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

// ---------------- HELPERS ----------------

struct List** createEmptyAdjacencyList(int listDimension) {
  struct List** list = (struct List**) malloc(listDimension * sizeof(struct List*));
  for(int i = 0; i < listDimension; i++) {
    list[i] = newList();
  }

  return list;
}

struct List** invertAdjacencyList(struct List** L, int listSize) {
  struct List** newList = createEmptyAdjacencyList(listSize);

  for(int i = 0; i < listSize; i++) {
    for(struct Node* it = L[i]->head->next; it != NULL; it = it->next)
      listPushBack(newList[it->value], i);
  }

  return newList;
}

// ---------------- ALGORITHMS ----------------

void _dfsFillOrder(struct Graph G, int vertex, int* markedVector, struct Stack* S) {
  markedVector[vertex] = TRUE;

  for(struct Node* it = G.adjacencyList[vertex]->head->next; it != NULL; it = it->next) {
    if(!markedVector[it->value]) {
      _dfsFillOrder(G, it->value, markedVector, S);
    }
  }

  stackPush(S, vertex);
}

void _dfsGetSCCs(struct Graph inverseGraph, int vertex, int* markedVector, int* SCCArr, int SCCCount) {
  markedVector[vertex] = TRUE;

  for(struct Node* it = inverseGraph.adjacencyList[vertex]->head->next; it != NULL; it = it->next) {
    if(!markedVector[it->value]) {
      _dfsGetSCCs(inverseGraph, it->value, markedVector, SCCArr, SCCCount);
    }
  }

  SCCArr[vertex] = SCCCount;
}

int Kosaraju(struct Graph G) {
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
  inverseGraph.adjacencyList = invertAdjacencyList(G.adjacencyList, G.verticesAmount);
  inverseGraph.verticesAmount = G.verticesAmount;

  while(!stackIsEmpty(S)) {
    int currentVertex = stackPop(S);

    if(!markedVector[currentVertex]) {
      _dfsGetSCCs(inverseGraph, currentVertex, markedVector, StronglyConnectedComponents, counter);
      counter++;
    }
  }

  for (int i = 0; i < G.verticesAmount; i += 2) {
    if(StronglyConnectedComponents[i] == StronglyConnectedComponents[i+1])
      return FALSE;    
  }

  return TRUE;
}

// ---------------- BUSINESS RULES ----------------

int handleCalculateVertexValue(int initialVert, int neg) {
  int newVertex = initialVert * 2;
  newVertex = neg ? newVertex + 1 : newVertex;

  return newVertex;
}

void handleAddAdjacencyList(struct List** adjList, struct ProposalSurveyInfo info) {
  const int NULL_PROPOSAL_VOTE = 0;

  if(info.firstProposal == NULL_PROPOSAL_VOTE) {
    if(info.secondProposal != NULL_PROPOSAL_VOTE)
      info.firstProposal = info.secondProposal;
    else
      return;
  } else if(info.secondProposal == NULL_PROPOSAL_VOTE)
    info.secondProposal = info.firstProposal;

  listPushBack(adjList[handleCalculateVertexValue(info.firstProposal - 1, !info.proposalsWereRejected)], handleCalculateVertexValue(info.secondProposal - 1, info.proposalsWereRejected));
  listPushBack(adjList[handleCalculateVertexValue(info.secondProposal - 1, !info.proposalsWereRejected)], handleCalculateVertexValue(info.firstProposal - 1, info.proposalsWereRejected));
}