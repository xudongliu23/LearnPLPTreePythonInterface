#!/usr/bin/python

import os
import sys
cwd = os.getcwd()
print cwd
sys.path.append(cwd + '/../out/gccdarwin64/')

import mytypes
import helper
import utils
import permutation
import cicp_plptree

cicpPlpTree = mytypes.CicpPlptree()
parNode = mytypes.CicpPlptree()
parNode = None
numTrainStrictExamplesSatisfied = mytypes.vi()
numTrainStrictExamplesSatisfied.resize(1)
bitMapTrainStrictExamples = mytypes.vi()
trainStrictExamples = mytypes.vpii()
bitMapIssues = mytypes.vi()
domains = mytypes.vpIssDom()
domainDescriptionFile = '/Users/xudong/Codes/PrefLearnLibGenerator/PrefLearnLib/UCI/CarEvaluation/domain_description.txt'
outcomes = mytypes.umIntVstring()
outcomesFile = '/Users/xudong/Codes/PrefLearnLibGenerator/PrefLearnLib/UCI/CarEvaluation/outcomes.csv'
testStrictExamples = mytypes.vpii()
strictExamplesFile = '/Users/xudong/Codes/PrefLearnLibGenerator/PrefLearnLib/UCI/CarEvaluation/strict_examples.csv'
numTrainStrictExamples = 10

utils.getDomains(bitMapIssues, domains, domainDescriptionFile)
utils.getOutcomes(outcomes, outcomesFile)
utils.getExamples(bitMapTrainStrictExamples, trainStrictExamples, testStrictExamples,
  strictExamplesFile, numTrainStrictExamples)

valsOnPathAbove = mytypes.vstring()
valsOnPathAbove.resize(bitMapIssues.size())
orderOfIndsForValsOnPathAbove = mytypes.vstring()

#for p in trainStrictExamples:
#  print '(%d,%d)' % (p.first, p.second)

cicp_plptree.trainCICPPLPTree_MH(0, valsOnPathAbove, orderOfIndsForValsOnPathAbove,
  cicpPlpTree, parNode, 0, cicpPlpTree, numTrainStrictExamplesSatisfied,
  domains, bitMapIssues, outcomes, trainStrictExamples, bitMapTrainStrictExamples)

cicp_plptree.displayCICPPLPTreeRecursive(cicpPlpTree)
