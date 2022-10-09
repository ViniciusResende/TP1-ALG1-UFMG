#include <stdio.h>
#include <stdlib.h>
#include <campanha.h>

/// @brief 
/// @param argc 
/// @param argv 
/// @return 
int main() {
  int scanfRes = 0;

  unsigned int followersAmount = 0;
  unsigned int governmentProposalAmount = 0;

  do {
    scanfRes = scanf("%u", &followersAmount);
    scanfRes = scanf("%u", &governmentProposalAmount);

    if(!scanfRes) return 0;

    if((followersAmount == 0) && (governmentProposalAmount == 0)) return 0;

    int listDimension = (governmentProposalAmount * 2); 
    struct List** adjacentList = createEmptyAdjacencyList(listDimension);

    struct Graph proposalGraph;
    proposalGraph.adjacencyList = adjacentList;
    proposalGraph.verticesAmount = listDimension;

    struct ProposalSurveyInfo currentProposalSurveyInfo;

    for(unsigned int i = 0; i < followersAmount; i++) {
      scanfRes = scanf("%u", &currentProposalSurveyInfo.firstProposal);
      scanfRes = scanf("%u", &currentProposalSurveyInfo.secondProposal);
      currentProposalSurveyInfo.proposalsWereRejected = FALSE;
      handleAddAdjacencyList(proposalGraph.adjacencyList, currentProposalSurveyInfo);

      scanfRes = scanf("%u", &currentProposalSurveyInfo.firstProposal);
      scanfRes = scanf("%u", &currentProposalSurveyInfo.secondProposal);
      currentProposalSurveyInfo.proposalsWereRejected = TRUE;
      handleAddAdjacencyList(proposalGraph.adjacencyList, currentProposalSurveyInfo);
    }

    int graphIsSatisfiable = Kosaraju(proposalGraph);

    if(graphIsSatisfiable)
      printf("sim\n");
    else
      printf("nao\n");
  } while((followersAmount != 0) && (governmentProposalAmount != 0));
  
  return 0;
}