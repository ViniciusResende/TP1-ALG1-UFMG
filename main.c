#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

struct ConfigStruct {
  char inputFile[100];
};

struct ConfigStruct config;

struct Graph {
  int **adjacentMatrix;
  int verticesAmount;
};

void menu() {
  fprintf(stderr,"Vota certo\n");
  fprintf(stderr,"-[i|I] <file>\t(Input File)\n");
}

void parse_args(int argc,char ** argv) {
  extern char * optarg;

  int c;

  config.inputFile[0] = 0;

  // getopt - letra indica a opcao, : junto a letra indica parametro
  // no caso de escolher mais de uma operacao, vale a ultima
  while ((c = getopt(argc, argv, "i:I:")) != EOF)
    switch(tolower(c)) {
      case 'i': 
        strcpy(config.inputFile, optarg);
        break;
      default:
        menu();
        exit(1);
        break;
    }
}

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

void _recursiveDFS(struct Graph G, int vertex, int* markedVector) {
  markedVector[vertex] = 1;

  // linha -> coluna
  for(int i = 0; i < G.verticesAmount; i++) {
    // printf("%d looks to %d \n", vertex, i);
    if(G.adjacentMatrix[vertex][i] && !markedVector[i]) {
      // printf("%d visits %d \n", vertex, i);
      _recursiveDFS(G, i, markedVector);
    }
  }
}

int* DFS(struct Graph G, int startVertex) {
  int* markedVector = (int*) malloc(G.verticesAmount * sizeof(int));
  for(int i = 0; i < G.verticesAmount; i++) markedVector[i] = 0;

  _recursiveDFS(G, startVertex, markedVector);

  return markedVector;
}

struct ProposalSurveyInfo {
  unsigned int firstProposal;
  unsigned int secondProposal;
  int proposalsWereRejected;
};

void handleAddAdjacentMatrix(int** matrix, struct ProposalSurveyInfo info) {
  const int NULL_PROPOSAL_VOTE = 0;

  if(info.firstProposal == NULL_PROPOSAL_VOTE)
    info.firstProposal = info.secondProposal;
  else if(info.secondProposal == NULL_PROPOSAL_VOTE)
    info.secondProposal = info.firstProposal;

  // if(!info.proposalsWereRejected) {
  //   printf("!%d -> %d \n", info.firstProposal, info.secondProposal);
  //   printf("!%d -> %d \n", info.secondProposal, info.firstProposal);
  // } else {
  //   printf("%d -> !%d \n", info.firstProposal, info.secondProposal);
  //   printf("%d -> !%d \n", info.secondProposal, info.firstProposal);
  // }

  matrix[handleMatrixIdx(info.firstProposal - 1, !info.proposalsWereRejected)][handleMatrixIdx(info.secondProposal - 1, info.proposalsWereRejected)] = 1;
  matrix[handleMatrixIdx(info.secondProposal - 1, !info.proposalsWereRejected)][handleMatrixIdx(info.firstProposal - 1, info.proposalsWereRejected)] = 1;
}

/// @brief 
/// @param argc 
/// @param argv 
/// @return 
int main(int argc, char ** argv) {
  const int FALSE = 0;
  const int TRUE = 1;
  int scanfRes = 0;

  parse_args(argc,argv);

  unsigned int followersAmount = 0;
  unsigned int governmentProposalAmount = 0;

  do {
    scanfRes = scanf("%u", &followersAmount);
    scanfRes = scanf("%u", &governmentProposalAmount);

    if(!scanfRes) return 0;

    if((followersAmount == 0) && (governmentProposalAmount == 0)) return 0;

    int matrixDimension = (governmentProposalAmount * 2); 
    int** adjacentMatrix = createNullSquareMatrix(matrixDimension);

    struct Graph proposalGraph;
    proposalGraph.adjacentMatrix = adjacentMatrix;
    proposalGraph.verticesAmount = matrixDimension;

    struct ProposalSurveyInfo currentProposalSurveyInfo;

    for(unsigned int i = 0; i < followersAmount; i++) {
      scanfRes = scanf("%u", &currentProposalSurveyInfo.firstProposal);
      scanfRes = scanf("%u", &currentProposalSurveyInfo.secondProposal);
      currentProposalSurveyInfo.proposalsWereRejected = FALSE;
      handleAddAdjacentMatrix(proposalGraph.adjacentMatrix, currentProposalSurveyInfo);

      scanfRes = scanf("%u", &currentProposalSurveyInfo.firstProposal);
      scanfRes = scanf("%u", &currentProposalSurveyInfo.secondProposal);
      currentProposalSurveyInfo.proposalsWereRejected = TRUE;
      handleAddAdjacentMatrix(proposalGraph.adjacentMatrix, currentProposalSurveyInfo);
    }

    int solutionFound = FALSE;

    for(int i = 0; i < matrixDimension; i += 2) {
      int* graphMarkedVisits = DFS(proposalGraph, i);
      int* graphMarkedVisits2 = DFS(proposalGraph, i + 1);

      if((graphMarkedVisits[i] == graphMarkedVisits[i+1]) && (graphMarkedVisits2[i] == graphMarkedVisits2[i+1])) {
        printf("nao \n");
        solutionFound = TRUE;
        break;
      }
    }

    if(!solutionFound) printf("sim \n");

    // printf("\n");
    // printMatrix(proposalGraph.adjacentMatrix, matrixDimension);
  } while((followersAmount != 0) && (governmentProposalAmount != 0));
  
  return 0;
}