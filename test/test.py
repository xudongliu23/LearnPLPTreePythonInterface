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
import permutation
import utils
import cicp_plptree

bitMapIssues = mytypes.vi()
domains = mytypes.vpIssDom()
domainDescriptionFile = user_dir + '/Codes/PrefLearnLibGenerator/PrefLearnLib/UCI/CarEvaluation/domain_description.txt'
utils.getDomains(bitMapIssues, domains, domainDescriptionFile)

utils.displayDomains(domains)

for i in range(domains.size()):
  print domains[i].first
  for j in range(domains[i].second.size()):
    print domains[i].second[j]

v = mytypes.vi()
v.push_back(1)
v.push_back(2)
v.push_back(3)
for i in range(v.size()):
  print v[i]

outcomes = mytypes.umIntVstring()
outcomesFile = user_dir + '/Codes/PrefLearnLibGenerator/PrefLearnLib/UCI/CarEvaluation/outcomes.csv'
utils.getOutcomes(outcomes, outcomesFile)
#utils.displayOutcomes(outcomes)

print outcomes.size()
print outcomes.empty()

for i in range(outcomes[1].size()):
  print outcomes[1][i]

vstr1 = mytypes.vstring()
vstr1.push_back('hello')
vstr1.push_back('world')
vstr2 = mytypes.vstring()
vstr2.push_back('xudong')
vstr2.push_back('liu')

vvstr = mytypes.vvstring()
vvstr.push_back(vstr1)
vvstr.push_back(vstr2)
utils.displayPerms(vvstr)
vvstr[1][0] = 'Xudong'
vvstr[1][1] = 'Liu'
utils.displayPerms(vvstr)

#for o in outcomes:
#  print 'Outcome %d:' % o[0]
#  for s in o[1]:
#    print s,
#  print ''

outcomes[1] = vstr1
for s in outcomes[1]:
  print s

#S = mytypes.usInt()
#utils.createUsInt(S)
#for s in S:
#  print s

w=mytypes.vstring()
w.push_back('Patrick')
w.push_back('Johnson')
for s in w:
  print s

v=mytypes.vstring()
v.push_back('Xudong')
v.push_back('Liu')
for s in v:
  print s

p=mytypes.vstring()
permutation.generateLexPerms(p, '123')
for s in p:
  print s
print p.size()


