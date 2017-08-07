#include "include/cicp_plptree.h"
#include "include/utils.h"
#include "include/permutation.h"
#include <iostream>
#include <stdio.h>      /* NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <queue>        /* priority queue*/
#include <fstream>      /* read/write files */

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
        vi *bitMapTrainStrictExamples)
{
    if (getNumUnusedExamples(bitMapTrainStrictExamples) == 0 || getNumUnusedIssues(&bitMapIssues) == 0) {
        if (parNode) {  // curNode is not root
            curNode->level = level;
            curNode->pathIssNames = parNode->pathIssNames;
            curNode->pathIssVals = parNode->pathIssVals;
            curNode->pathIssVals.push_back(parNode->pref[parIssValInd]);
        }
        return;
    }

    vpIssDom available_issues;
    computeAvailableIssueCICPPLPTree_MH(&available_issues, &valuesOnInstIssuesAbove, &orderOfInstIssuesAbove,
                                         numTrainStrictExamplesSatisfied, domains,
                                         &bitMapIssues, outcomes,
                                         trainStrictExamples, bitMapTrainStrictExamples, root);
    if (!available_issues.size()) {
        if (parNode) {  // curNode is not root
            curNode->level = level;
            curNode->pathIssNames = parNode->pathIssNames;
            curNode->pathIssVals = parNode->pathIssVals;
            curNode->pathIssVals.push_back(parNode->pref[parIssValInd]);
        }
        return;
    }
    pIssDom issueWithPref;
    getRandIssueCICPPLPTree(&issueWithPref, &available_issues);
    curNode->level = level;
    curNode->name = issueWithPref.first;
    curNode->pref = issueWithPref.second;
    if (!parNode) { // curNode is root
        curNode->pathIssNames.push_back(curNode->name);
        //curNode->pathIssVals.push_back(parNode->pref[parIssValInd]);
    } else {        // curNode is not root
        curNode->pathIssNames = parNode->pathIssNames;
        curNode->pathIssNames.push_back(curNode->name);

        curNode->pathIssVals = parNode->pathIssVals;
        curNode->pathIssVals.push_back(parNode->pref[parIssValInd]);
    }

//    cout << "pref: ";
//    printVstring(&issueWithPref.second);
//    cout << "number: " << (*numTrainStrictExamplesSatisfied)[0] << endl;

    orderOfInstIssuesAbove.push_back(issueWithPref.first);
    REP (i, 0, issueWithPref.second.size()-1) {
        CicpPlptree *treeNode = new CicpPlptree();
        curNode->subtrees.push_back(treeNode);
        updateBitMapTrainStrictExampleCICPPLPTree(trainStrictExamples, bitMapTrainStrictExamples,
                                                  root, domains, outcomes);
        updateBitMapIssueCICPPLPTree(&bitMapIssues, domains, &issueWithPref);
        //            cout << "AAA              : ";
//        printVi(bitMapTrainStrictExamples);
        valuesOnInstIssuesAbove[getIssIndFromName(issueWithPref.first, domains)] = issueWithPref.second.at(i);
        trainCICPPLPTree_MH(level+1, valuesOnInstIssuesAbove, orderOfInstIssuesAbove,
                            treeNode, curNode, i, root, numTrainStrictExamplesSatisfied,
                            domains, bitMapIssues,
                            outcomes, trainStrictExamples, bitMapTrainStrictExamples);
    }
}

void computeAvailableIssueCICPPLPTree_MH(
        vpIssDom *available_issues,
        vstring *valuesOnInstIssuesAbove,
        vstring *orderOfInstIssuesAbove,
        vi *numTrainStrictExamplesSatisfied,
        vpIssDom *domains,
        vi *bitMapIssues,
        umIntVstring *outcomes,
        vpii *trainStrictExamples,
        vi *bitMapTrainStrictExamples,
        CicpPlptree *head)
{
    int maxNumTrainStrictExamplesSatsified = 0;

    /* For each issue left, for each local order of values,
       compute the number of strict examples statisfied. */
    /* NOTE: If maxNumTrainStrictExamplesSatsified is 0, return an empty available_issues */
    REP (i, 0, bitMapIssues->size()-1) {
        if (!bitMapIssues->at(i))
            continue;
        vvstring perms;
        computePerms(&perms, domains->at(i).second);
        REP (j, 0, perms.size()-1) {
            int num = computeNumTrainStrictExamplesSatsifiedCICPPLPTree(
                        i, perms[j], valuesOnInstIssuesAbove, orderOfInstIssuesAbove,
                        domains, bitMapIssues, outcomes,
                        trainStrictExamples, bitMapTrainStrictExamples, head);
            if (num > maxNumTrainStrictExamplesSatsified) {
                maxNumTrainStrictExamplesSatsified = num;
                available_issues->clear();
                available_issues->push_back(make_pair(domains->at(i).first, perms[j]));
            } else if (num == maxNumTrainStrictExamplesSatsified && maxNumTrainStrictExamplesSatsified > 0) {
                available_issues->push_back(make_pair(domains->at(i).first, perms[j]));
            }
        }
    }

    (*numTrainStrictExamplesSatisfied)[0] += maxNumTrainStrictExamplesSatsified;
//    cout << "maxNumTrainStrictExamplesSatsified: " << maxNumTrainStrictExamplesSatsified << endl;
//    REP (n, 0, bitMapTrainStrictExamples->size()-1)
//        cout << bitMapTrainStrictExamples->at(n) << " ";
//    cout << endl;
}

int computeNumTrainStrictExamplesSatsifiedCICPPLPTree(
        int issInd,
        vstring issPref,
        vstring *valuesOnInstIssuesAbove,
        vstring *orderOfInstIssuesAbove,
        vpIssDom *domains,
        vi *bitMapIssues,
        umIntVstring *outcomes,
        vpii *trainStrictExamples,
        vi *bitMapTrainStrictExamples,
        CicpPlptree *head)
{
    int numSat = 0;

    REP (i, 0, bitMapTrainStrictExamples->size()-1) {
        if (!bitMapTrainStrictExamples->at(i))
            continue;

        /* check if a strict example is satisfied by tree from head to tail
           plus issInd and issPref below tail. */
        // 1. check if the two outcomes in this example are same from head to tail.
        bool eqHeadToTail = true;
        vstring partialOutcome1(bitMapIssues->size());
        getPartialOutcomeCICPPLPTree(&partialOutcome1, "first", head,
                                     domains, outcomes, &(trainStrictExamples->at(i)));
        vstring partialOutcome2(bitMapIssues->size());
        getPartialOutcomeCICPPLPTree(&partialOutcome2, "second", head,
                                     domains, outcomes, &(trainStrictExamples->at(i)));
        if (!consistentCICPPLPTree(&partialOutcome1, &partialOutcome2,
                                   valuesOnInstIssuesAbove, orderOfInstIssuesAbove,
                                   domains))
            eqHeadToTail = false;

        // 2. if 1 holds, check if one outcome is better than the other according to issPref.
        bool betterOnIss = false;
        if (!eqHeadToTail)
            continue;
        string value1 = (*outcomes)[trainStrictExamples->at(i).first].at(issInd);
        string value2 = (*outcomes)[trainStrictExamples->at(i).second].at(issInd);
        if (agree(value1, value2, &issPref)) {
            betterOnIss = true;
        }

        // 3. numSat++ if both 2 holds.
        if(betterOnIss)
            numSat++;
    }

//cout << "orderOfInstIssuesAbove: ";
//printVstring(orderOfInstIssuesAbove);

    return numSat;
}

void getPartialOutcomeCICPPLPTree(vstring *partialOutcome,
                                  string pos,
                                  CicpPlptree *head,
                                  vpIssDom *domains,
                                  umIntVstring *outcomes,
                                  pii *trainStrictExample)
{
    CicpPlptree *ptr = head;
    while (ptr != NULL) {
        if (ptr->name == "")
            break;
        int ind = getIssIndFromName(ptr->name, domains);
        string val = (pos == "first"?
                          (*outcomes)[trainStrictExample->first].at(ind):
                          (*outcomes)[trainStrictExample->second].at(ind));
        partialOutcome->at(ind) = val;
        if (getValIndInPref(val, ptr->pref) < ptr->subtrees.size()) {
            ptr = ptr->subtrees[getValIndInPref(val, ptr->pref)];
        } else {
            break;
        }
    }
}

bool consistentCICPPLPTree(vstring *partialOutcome1, vstring *partialOutcome2,
                           vstring *valuesOnInstIssuesAbove, vstring *orderOfInstIssuesAbove,
                           vpIssDom *domains)
{
//    printVstring(partialOutcome1);
//    printVstring(partialOutcome2);
//    printVstring(valuesOnInstIssuesAbove);
//    printVstring(orderOfInstIssuesAbove);
//    cout << "====================================================" << endl;

    bool same = true;
    REP (i, 0, partialOutcome1->size()-1) {
        if (partialOutcome1->at(i) != partialOutcome2->at(i)) {
            same = false;
            break;
        }
    }

    bool consistent = true;
    if (!same) {
        consistent = false;
    } else {
        REP (i, 0, orderOfInstIssuesAbove->size()-1) {
            if (partialOutcome1->at(getIssIndFromName(orderOfInstIssuesAbove->at(i), domains)) !=
                    valuesOnInstIssuesAbove->at(getIssIndFromName(orderOfInstIssuesAbove->at(i), domains))) {
                consistent = false;
                break;
            }
        }
    }

    return consistent;
}

void getRandIssueCICPPLPTree(pIssDom *issueWithPref, vpIssDom *available_issues)
{
    //srand (time(NULL));

    int iSecret = rand() % (available_issues->size());

    issueWithPref->first = available_issues->at(iSecret).first;
    issueWithPref->second = available_issues->at(iSecret).second;
}

void updateBitMapTrainStrictExampleCICPPLPTree(vpii *trainStrictExamples,
                                vi *bitMapTrainStrictExamples,
                                CicpPlptree *head,
                                vpIssDom *domains,
                                umIntVstring *outcomes)
{
    REP (i, 0, bitMapTrainStrictExamples->size()-1) {
        if (!bitMapTrainStrictExamples->at(i))
            continue;
        if (satisfyCICPPLPTree(head, trainStrictExamples->at(i).first, trainStrictExamples->at(i).second, domains, outcomes) == 1)
            bitMapTrainStrictExamples->at(i) = 0;
//cout << "-----------------" << endl;
    }
}

int satisfyCICPPLPTree(
        CicpPlptree *head,
        int o1Ind,
        int o2Ind,
        vpIssDom *domains,
        umIntVstring *outcomes)
{
    int res = 0;
    CicpPlptree *ptr = head;

    while (ptr != NULL && ptr->name != "") {    // second condition due to trailing empty node
        int ind = getIssIndFromName(ptr->name, domains);
        string value1 = (*outcomes)[o1Ind].at(ind);
        string value2 = (*outcomes)[o2Ind].at(ind);

        if (value1 == value2) {
            if (getValIndInPref(value1, ptr->pref) < ptr->subtrees.size()) {
                //                    cout << getValIndInPref(value1, ptr->pref) << ",";
                //                    cout << ptr->subtrees.size() << endl;
                ptr = ptr->subtrees[getValIndInPref(value1, ptr->pref)];
            } else {
                break;
            }
            continue;
        }

        if (agree(value1, value2, &ptr->pref)) {
            res = 1;
        } else {
            res = -1;
        }
        break;
    }

    return res;
}

int satisfyCICPPLPTreeCD(
        CicpPlptree *head,
        int o1Ind,
        int o2Ind,
        vpIssDom *domains)
{
    int res = 0;
    CicpPlptree *ptr = head;

    while (ptr != NULL && ptr->name != "") {    // second condition due to trailing empty node
        int ind = getIssIndFromName(ptr->name, domains);
        string value1 = computeOutcomeFromIndInCombDomain(o1Ind, domains).at(ind);
        string value2 = computeOutcomeFromIndInCombDomain(o2Ind, domains).at(ind);

        if (value1 == value2) {
            if (getValIndInPref(value1, ptr->pref) < ptr->subtrees.size()) {
                ptr = ptr->subtrees[getValIndInPref(value1, ptr->pref)];
            } else {
                break;
            }
            continue;
        }

        if (agree(value1, value2, &ptr->pref)) {
            res = 1;
        } else {
            res = -1;
        }
        break;
    }

    return res;
}

bool inTopClusterCICPPLPTree(
        CicpPlptree *head,
        int oInd,
        vpIssDom *domains,
        umIntVstring *outcomes,
        CicpPlptree *topCluster)
{
    CicpPlptree *ptr = head;

    while (ptr != NULL && ptr->name != "") {    // second condition due to trailing empty node
        string value = (*outcomes)[oInd].at(getIssIndFromName(ptr->name, domains));
        if (getValIndInPref(value, ptr->pref)) return false;

        ptr = ptr->subtrees[0];
    }

    topCluster->pathIssNames = ptr->pathIssNames;
    return true;
}

bool inSecondClusterCICPPLPTree(
        CicpPlptree *head,
        int oInd,
        vpIssDom *domains,
        umIntVstring *outcomes,
        CicpPlptree *secondCluster)
{
    CicpPlptree *ptr = head;
    bool makeRight = false;  // make sure the make-right is a one time deal

    while (ptr != NULL && ptr->name != "") {    // second condition due to trailing empty node
        string value = (*outcomes)[oInd].at(getIssIndFromName(ptr->name, domains));
        if (ptr->subtrees[0]==NULL || ptr->subtrees[0]->name=="") {
            if (!makeRight) {
                if (getValIndInPref(value, ptr->pref) != 1) return false;
                ptr = ptr->subtrees[1];
                makeRight = true;
            } else {
                if (getValIndInPref(value, ptr->pref) != 0) return false;
                ptr = ptr->subtrees[0];
            }
        } else {
            if (getValIndInPref(value, ptr->pref) != 0) return false;
            ptr = ptr->subtrees[0];
        }
    }

    secondCluster->pathIssNames = ptr->pathIssNames;
    return true;
}

CicpPlptree* clusterOfOutcomeCICPPLPTree(
        CicpPlptree *head,
        vstring outcome,
        vpIssDom *domains)
{
    CicpPlptree *ptr = head;
    while (ptr) {
        if (ptr->name == "") {
					return ptr;
        }
        int ind = getIssIndFromName(ptr->name, domains);
        string val = outcome[ind];
        if (getValIndInPref(val, ptr->pref) < ptr->subtrees.size()) {
            ptr = ptr->subtrees[getValIndInPref(val, ptr->pref)];
        } else {
            break;
        }
    }
}

void betterClustersCICPPLPTree(
        CicpPlptree *head,
        CicpPlptree *cluster,
        vector<CicpPlptree *> *clusters)
{
    bool flag = false;
    betterClustersCICPPLPTreeRecur(head, cluster, clusters, &flag);
}

void betterClustersCICPPLPTreeRecur(
        CicpPlptree *head,
        CicpPlptree *cluster,
        vector<CicpPlptree*> *clusters,
        bool *flag)
{
    if (head->name == "") {
        if (head == cluster) *flag=true;
        if (*flag == false) clusters->push_back(head);
        return;
    }

    for (int i=0; i<head->subtrees.size(); i++)
        betterClustersCICPPLPTreeRecur(head->subtrees[i], cluster, clusters, flag);
}

void allClustersCICPPLPTree(
        CicpPlptree *head,
        vector<CicpPlptree*> *clusters)
{
    if (head->name == "") {
        clusters->push_back(head);
        return;
    }

    for (int i=0; i<head->subtrees.size(); ++i)
        allClustersCICPPLPTree(head->subtrees[i], clusters);
}

void totalPreorderFromCICPPLPTree(
        CicpPlptree *head,
        vpIssDom *domains,
        umIntVstring *outcomes,
        vector<usInt> *totalPreorder,
        umIntInt *outcomeToCluster)
{
    umIntInt counts;  // oInd => number of outcomes oInd defeats

    for (auto& it1 : *outcomes) {
        for (auto& it2 : *outcomes) {
            if (it1.first != it2.first) {
                if (satisfyCICPPLPTree(head, it1.first, it2.first, domains, outcomes) >= 0) {
                    counts[it1.first]++;
                }
            }
        }
    }

    // Make a max heap to order the outcomes by the numbers of their defeated outcomes
    struct Order {
        bool operator()(pii& p1, pii& p2) {
            return p1.second<p2.second || (p1.second==p2.second && p1.first>p2.first);
        }
    };
    priority_queue<pii, vpii, Order> Q;
    for (auto& c : counts) Q.push(c);

    // Pop from the max heap to build the totalPreorder
    int ind = 0;
    usInt S;
    int count = Q.top().second;
    while (!Q.empty()) {
        pii p = Q.top(); Q.pop();
        if (p.second == count) {
            S.insert(p.first);
            (*outcomeToCluster)[p.first] = ind;
        } else {
            totalPreorder->push_back(S);
            S.clear();
            ind++;

            (*outcomeToCluster)[p.first] = ind;
            count = p.second;
            S.insert(p.first);
        }
    }
    // take care of the last set
    totalPreorder->push_back(S);

    /*for (auto& s:*totalPreorder) {
        for (auto& e:s) cout<<e<<" ";
        cout << "END" << endl;
    }
    cout << endl;*/
}

void totalPreorderOverCombDomainFromCICPPLPTree(
        CicpPlptree *head,
        vpIssDom *domains,
        vector<sInt> *totalPreorder)
{
    unordered_map<CicpPlptree*, sInt> clusterToOutcomeInds;  // map a cluster to all outcome indices  in that cluster

    for (int i=0; i<computeSizeOfCombDomain(domains); i++) {
        CicpPlptree *cluster = clusterOfOutcomeCICPPLPTree(head, computeOutcomeFromIndInCombDomain(i, domains), domains);

        clusterToOutcomeInds[cluster].insert(i);
    }

    totalPreorderOverCombDomainFromCICPPLPTreeRecur(head, totalPreorder, &clusterToOutcomeInds);
}

void totalPreorderOverCombDomainFromCICPPLPTreeRecur(
        CicpPlptree *head,
        vector<sInt> *totalPreorder,
        unordered_map<CicpPlptree *, sInt> *clusterToOutcomeInds)
{
    if (head->name == "") {
        if (clusterToOutcomeInds->count(head)) {
            totalPreorder->push_back((*clusterToOutcomeInds)[head]);
        } else {  // empty cluster (cluster has no outcome in it)
            // this case is never true for PLP-trees!
        }
        return;
    }

    for (int i=0; i<head->subtrees.size(); i++)
        totalPreorderOverCombDomainFromCICPPLPTreeRecur(head->subtrees[i], totalPreorder, clusterToOutcomeInds);
}

void updateBitMapIssueCICPPLPTree(vi *bitMapIssues, vpIssDom *domains, pIssDom *issueWithPref)
{
    REP (i, 0, domains->size()-1) {
        if (domains->at(i).first == issueWithPref->first)
            bitMapIssues->at(i) = 0;
    }
}

int computeNumNodesCICPPLPTree(CicpPlptree *tree)
{
    CicpPlptree *node = tree;
    vi counter; counter.push_back(0);

    computeNumNodesCICPPLPTreeRecursive(node, &counter);

    return counter[0];
}

void computeNumNodesCICPPLPTreeRecursive(CicpPlptree *tree, vi *counter)
{
    if (tree->subtrees.size() == 0) {
        return;
    }else {
        (*counter)[0]++;
    }

    REP (i, 0, tree->subtrees.size()-1) {
        computeNumNodesCICPPLPTreeRecursive(tree->subtrees[i], counter);
    }
}

void deleteCICPPLPTree(CicpPlptree *tree)
{
    if (tree->subtrees.size() == 0 || tree->name == "")
        return;

    REP (i, 0, tree->subtrees.size()-1)
        deleteCICPPLPTree(tree->subtrees[i]);

    delete tree;
}

void displayCICPPLPTree(CicpPlptree *head,
                        int numTrainStrictExamplesSatisfied,
                        vi *numTestStrictExamplesSatisfied,
                        vpIssDom *domains,
                        umIntVstring *outcomes,
                        vpii *trainStrictExamples,
                        vpii *testStrictExamples)
{
    displayCICPPLPTreeRecursive(head);

//    cout << "It says " << numTrainStrictExamplesSatisfied << ", and actually, "
//         << computeNumSatStrictExamplesByCICPPLPTree(head, trainStrictExamples, domains, outcomes)
//         << endl;
    /* For verification, compute number of satisfied strict examples */
    if (numTrainStrictExamplesSatisfied ==
            computeNumSatStrictExamplesByCICPPLPTree(head, trainStrictExamples, domains, outcomes)) {
        cout << "satisfy " << numTrainStrictExamplesSatisfied << " out of " << trainStrictExamples->size()
             << "(" << (float)numTrainStrictExamplesSatisfied/trainStrictExamples->size() << ")"
             << " training strict examples." << endl;
        (*numTestStrictExamplesSatisfied)[0] = computeNumSatStrictExamplesByCICPPLPTree(head, testStrictExamples, domains, outcomes);
        cout << "satisfy " << (*numTestStrictExamplesSatisfied)[0]
             << " out of " << testStrictExamples->size()
             << "(" << (float)(*numTestStrictExamplesSatisfied)[0]/testStrictExamples->size() << ")"
             << " testing strict examples." << endl;
    } else {
        cout << numTrainStrictExamplesSatisfied << endl;
        cout << computeNumSatStrictExamplesByCICPPLPTree(head, trainStrictExamples, domains, outcomes) << endl;
        cout << "Wrong algorithm!" << endl;
        exit(1);
    }

/* Test totalPreorderFromCICPPLPTree
    vector<usInt> tp = totalPreorderFromCICPPLPTree(head, domains, outcomes);
    int count = 0;
    for (auto& S : tp) {
        for (auto& e : S) {
            count++;
            cout << e << " ";
        }
        cout << endl;
    }
    cout << count << "," << outcomes->size() << endl;
*/
}

void displayCICPPLPTreeRecursive(CicpPlptree *head)
{
    if (head->subtrees.size() == 0 || head->name == "") {
        cout << head->level << ". Empty" << endl;
        cout << "Path issue names: ";
        for (auto& pathIssName : head->pathIssNames)
            cout << pathIssName << " ";
        cout << endl;
        cout << "Path issue values: ";
        for (auto& pathIssVal : head->pathIssVals)
            cout << pathIssVal << " ";
        cout << endl;
        return;
    }

    cout << head->level << ". ";
    cout << head->name << ": ";
    for (int i=0; i<head->pref.size(); i++) {
        cout << head->pref.at(i) << " ";
    }
    cout << endl;

    for (int i=0; i<head->subtrees.size(); i++)
        displayCICPPLPTreeRecursive(head->subtrees[i]);
}

//void dumpToXML(CicpPlptree *head, const string outputDir) {
//    const string xmlName = outputDir + "/cicp_plptree.xml";
//    ofstream ofs;
//    ofs.open(xmlName.c_str());
//
//    ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
//    dumpToXMLRecur(head, ofs);
//
//    ofs.close();
//}
//
//void dumpToXMLRecur(CicpPlptree *head, ofstream& ofs) {
//    if (!head->level) {
//        ofs << tabs(head->level) << "<child xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" << endl
//            << "\txsi:noNamespaceSchemaLocation=\"plptree_instance.xsd\">" << endl;
//    } else {
//        ofs << tabs(head->level) << "<child>" << endl;
//    }
//
//    if (head->subtrees.size() == 0 || head->name == "") {
//        ofs << tabs(head->level+1) << "<!-- -->" << endl;
//        ofs << tabs(head->level) << "</child>" << endl;
//        return;
//    }
//
//    ofs << tabs(head->level+1) << "<attribute>" << head->name << "</attribute>" << endl;
//    for (int i=0; i<head->pref.size()-1; i++) {
//        ofs << tabs(head->level+1) << "<preference>" << head->pref[i] << ":" << head->pref[i+1] << "</preference>" << endl;
//    }
//
//    for (int i=0; i<head->subtrees.size(); i++) {
//        dumpToXMLRecur(head->subtrees[i], ofs);
//    }
//
//    ofs << tabs(head->level) << "</child>" << endl;
//}

int computeNumSatStrictExamplesByCICPPLPTree(
        CicpPlptree *cicpPlpTree,
        vpii *strictExamples,
        vpIssDom *domains,
        umIntVstring *outcomes)
{
    int num = 0;

    REP (i, 0, strictExamples->size()-1) {
        if (satisfyCICPPLPTree(cicpPlpTree, strictExamples->at(i).first, strictExamples->at(i).second, domains, outcomes) == 1)
            num++;
    }
    return num;
}
