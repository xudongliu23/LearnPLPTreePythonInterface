#!/usr/bin/python

import os
import sys
cwd = os.getcwd()
#print cwd
if sys.platform.startswith('darwin'):
	sys.path.append(cwd + '/../out/gccdarwin64/')
elif sys.platform.startswith('linux'):
	sys.path.append(cwd + '/../out/gcclinux64/')
else:
	sys.path.append(cwd + '/../out/gcccygwin64/')

import socket
if socket.gethostname() == 'CIS-3211-64950':
	user_dir = '/Users/n01237497'
elif socket.gethostname() == 'Xudongs-MacBook-Pro':
	user_dir = '/Users/xudong'
elif socket.gethostname() == 'cisvm-xudong-1':
	user_dir = '/home/xudong'
elif socket.gethostname() == 'cisvm-xudong-2':
	user_dir = '/home/xudong'
else:
	sys.exit('Wrong user!')

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
domainDescriptionFile = user_dir + '/Codes/PrefLearnLibGenerator/PrefLearnLib/UCI/CarEvaluation/domain_description.txt'
outcomes = mytypes.umIntVstring()
outcomesFile = user_dir + '/Codes/PrefLearnLibGenerator/PrefLearnLib/UCI/CarEvaluation/outcomes.csv'
testStrictExamples = mytypes.vpii()
strictExamplesFile = user_dir + '/Codes/PrefLearnLibGenerator/PrefLearnLib/UCI/CarEvaluation/strict_examples.csv'
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
