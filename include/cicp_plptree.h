#ifndef CICP_PLPTREE_H
#define CICP_PLPTREE_H

/** \mainpage  @brief Dummy class used for illustration purposes. Doing something with it.
 *
 * @author Xudong Liu
 * @date 5/24/2017
*/

#include "mytypes.h"

/**
 * @brief Train a CICP PLP-tree using the greedy heuristic MH from trainStrictExamples.
 *        The learned tree is at root.
 *
 * @param level
 * @param valuesOnInstIssuesAbove
 * @param orderOfInstIssuesAbove
 * @param curNode
 * @param parNode
 * @param parIssValInd: index of the value in the pref order in the parent node
 * @param root
 * @param numTrainStrictExamplesSatisfied
 * @param domains
 * @param bitMapIssues
 * @param outcomes
 * @param trainStrictExamples
 * @param bitMapTrainStrictExamples
 */
void trainCICPPLPTree_MH(
        int level,
        vstring valuesOnInstIssuesAbove,
        vstring orderOfInstIssuesAbove,
        CicpPlptree *curNode,
        CicpPlptree *parNode,
        int parIssValInd,
        CicpPlptree *root,
        vi *numTrainStrictExamplesSatisfied,
        vpIssDom *domains,
        vi bitMapIssues,
        umIntVstring *outcomes,
        vpii *trainStrictExamples,
        vi *bitMapTrainStrictExamples);

void computeAvailableIssueCICPPLPTree_MH(vpIssDom *available_issues, vstring *valuesOnInstIssuesAbove,
                                          vstring *orderOfInstIssuesAbove,
        vi *numTrainStrictExamplesSatisfied,
        vpIssDom *domains,
        vi *bitMapIssues,
        umIntVstring *outcomes,
        vpii *trainStrictExamples,
        vi *bitMapTrainStrictExamples,
        CicpPlptree *head);

int computeNumTrainStrictExamplesSatsifiedCICPPLPTree(int issInd,
        vstring issPref,
        vstring *valuesOnInstIssuesAbove, vstring *orderOfInstIssuesAbove,
        vpIssDom *domains, vi *bitMapIssues,
        umIntVstring *outcomes,
        vpii *trainStrictExamples,
        vi *bitMapTrainStrictExamples,
        CicpPlptree *head);

void getPartialOutcomeCICPPLPTree(vstring *partialOutcome, string pos,
                                  CicpPlptree *head,
                                  vpIssDom *domains,
                                  umIntVstring *outcomes, pii *trainStrictExample);

/* Check if po1 and po2 are same, and both has prefix valuesOnInstIssuesAbove according to order specified
   by orderOfInstIssuesAbove */
bool consistentCICPPLPTree(vstring *partialOutcome1, vstring *partialOutcome2,
                           vstring *valuesOnInstIssuesAbove, vstring *orderOfInstIssuesAbove,
                           vpIssDom *domains);

void getRandIssueCICPPLPTree(pIssDom *issueWithPref, vpIssDom *available_issues);

void updateBitMapTrainStrictExampleCICPPLPTree(vpii *trainStrictExamples,
                                vi *bitMapTrainStrictExamples,
                                CicpPlptree *head,
                                vpIssDom *domains,
                                umIntVstring *outcomes);

/**
 * @brief Check the order of o1Ind and o2Ind in the CICP PLP-tree noted by head
 *
 * @param head
 * @param o1Ind: index of o1
 * @param o2Ind: index of o2
 * @param domains
 * @param outcomes
 *
 * @return 1: o1Ind is strictly better than o2Ind, 0: they are equivalent,
 *         -1: o2Ind is strictly better.
 */
int satisfyCICPPLPTree(
        CicpPlptree *head,
        int o1Ind,
        int o2Ind,
        vpIssDom *domains,
        umIntVstring *outcomes);

/**
 * @brief Check the order of o1Ind and o2Ind in the CICP PLP-tree noted by head
 *        NOTE that o1Ind and o2Ind are indices from the combinatorial domain
 * @param head
 * @param o1Ind
 * @param o2Ind
 * @param domains
 *
 * @return 1: o1Ind is strictly better than o2Ind, 0: they are equivalent,
 *         -1: o2Ind is strictly better.
 */
int satisfyCICPPLPTreeCD(
        CicpPlptree *head,
        int o1Ind,
        int o2Ind,
        vpIssDom *domains);

/**
 * @brief Check if outcome oInd is in the top cluster of the induced order by the tree
 *
 * @param head
 * @param oInd: index of o
 * @param domains
 * @param outcomes
 * @param topCluster: (the address of) the left most leaf
 *
 * @return true: oInd is in the top cluster,
 *         false: is not.
 */
bool inTopClusterCICPPLPTree(
        CicpPlptree *head,
        int oInd,
        vpIssDom *domains,
        umIntVstring *outcomes,
        CicpPlptree *topCluster);

/**
 * @brief Check if outcome oInd is in the second cluster of the induced order by the tree
 *
 * @param head
 * @param oInd: index of o
 * @param domains
 * @param outcomes
 * @param topCluster: (the address of) the second left most leaf
 *
 * @return true: oInd is in the second cluster,
 *         false: is not.
 */
bool inSecondClusterCICPPLPTree(
        CicpPlptree *head,
        int oInd,
        vpIssDom *domains,
        umIntVstring *outcomes,
        CicpPlptree *secondCluster);

/**
 * @brief compute the cluster leaf of a given outcome index oInd
 *
 * @param head
 * @param outcome
 * @param domains
 *
 * @return: the cluster leaf
 */
CicpPlptree *clusterOfOutcomeCICPPLPTree(
        CicpPlptree *head,
        vstring outcome,
        vpIssDom *domains);

/**
 * @brief compute all better clusters than cluster in CICP tree head
 *
 * @param head
 * @param cluster
 * @param clusters: better clusters than cluster
 */
void betterClustersCICPPLPTree(
        CicpPlptree *head,
        CicpPlptree *cluster,
        vector<CicpPlptree*> *clusters);

/**
 * @brief the actual recursive function called in betterClustersCICPPLPTree
 *
 * @param head
 * @param cluster
 * @param clusters
 * @param flag: whether we have seen cluster in the search.
 */
void betterClustersCICPPLPTreeRecur(
        CicpPlptree *head,
        CicpPlptree *cluster,
        vector<CicpPlptree*> *clusters,
        bool *flag);

/**
 * @brief compute all clusters in CICP tree head
 *
 * @param head
 * @param clusters: result
 */
void allClustersCICPPLPTree(
        CicpPlptree *head,
        vector<CicpPlptree*> *clusters);

/**
 * @brief compute total preorder of outcomes for a given CICP PLP-tree
 *
 * @param head
 * @param domains
 * @param outcomes
 * @param totalPreorder: vector of sets of indices of equivalent outcomes
 * @param outcomeToCluster: map from outcome indices to cluster indices in the total preorder
 *
 * @return nothing
 */
void totalPreorderFromCICPPLPTree(
        CicpPlptree *head,
        vpIssDom *domains,
        umIntVstring *outcomes,
        vUsInt *totalPreorder,
        umIntInt *outcomeToCluster);

/**
 * @brief compute the total preorder of all outcomes in the combinatorial domain from CICP PLP-tree
 *
 * @param head
 * @param domains
 * @param totalPreorder: the result
 */
void totalPreorderOverCombDomainFromCICPPLPTree(
        CicpPlptree *head,
        vpIssDom *domains,
        vector<sInt> *totalPreorder);

/**
 * @brief the helper of totalPreorderOverCombDomainFromCICPPLPTree
 *        This function traverse the CICP PLP-tree and fill in totalPreorder
 *
 * @param head
 * @param totalPreorder: the result
 * @param clusterToOutcomeInds: map each cluster to its set of equivalent outcomes
 */
void totalPreorderOverCombDomainFromCICPPLPTreeRecur(
        CicpPlptree *head,
        vector<sInt> *totalPreorder,
        unordered_map<CicpPlptree*, sInt> *clusterToOutcomeInds);

void updateBitMapIssueCICPPLPTree(vi *bitMapIssues, vpIssDom *domains, pIssDom *issueWithPref);

int computeNumNodesCICPPLPTree(CicpPlptree *tree);

void computeNumNodesCICPPLPTreeRecursive(CicpPlptree *tree, vi *counter);

void deleteCICPPLPTree(CicpPlptree *tree);

void displayCICPPLPTree(CicpPlptree *head,
                        int numTrainStrictExamplesSatisfied,
                        vi *numTestStrictExamplesSatisfied,
                        vpIssDom *domains,
                        umIntVstring *outcomes,
                        vpii *trainStrictExamples,
                        vpii *testStrictExamples);

void displayCICPPLPTreeRecursive(CicpPlptree *head);

/**
 * @brief dump the CICP PLP-tree to an XML file
 *
 * @param head
 * @param outputDir: directory the XML file will be
 */
//void dumpToXML(CicpPlptree *head, const string outputDir);
//void dumpToXMLRecur(CicpPlptree *head, ofstream &ofs);

int computeNumSatStrictExamplesByCICPPLPTree(CicpPlptree *cicpPlpTree,
        vpii *strictExamples,
        vpIssDom *domains,
        umIntVstring *outcomes);


#endif // CICP_PLPTREE_H
