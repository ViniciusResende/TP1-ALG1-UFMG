#include <stdio.h>
#include <stdlib.h>
#include <campanha.h>

/// @brief 
/// @param argc 
/// @param argv 
/// @return 
int main() {
  const int FALSE = 0;
  const int TRUE = 1;
  int scanfRes = 0;

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

    Kosaraju(proposalGraph);
  } while((followersAmount != 0) && (governmentProposalAmount != 0));
  
  return 0;
}