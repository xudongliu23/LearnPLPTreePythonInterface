#include "include/utils.h"

PYBIND11_MAKE_OPAQUE(vi);
PYBIND11_MAKE_OPAQUE(vstring);
PYBIND11_MAKE_OPAQUE(vvstring);
PYBIND11_MAKE_OPAQUE(pIssDom);
PYBIND11_MAKE_OPAQUE(vpIssDom);
PYBIND11_MAKE_OPAQUE(umIntVstring);
PYBIND11_MAKE_OPAQUE(pii);
PYBIND11_MAKE_OPAQUE(vpii);
PYBIND11_MAKE_OPAQUE(usInt);

namespace py = pybind11;

PYBIND11_RUNTIME_EXCEPTION(index_error, PyExc_IndexError)
PYBIND11_RUNTIME_EXCEPTION(key_error, PyExc_KeyError)

PYBIND11_MODULE (utils, m) {
	m.doc() = "pybind11 for utils.h";

	m.def("getDomains", &getDomains, 
				"Get domain info for all issues from the description data file");
	m.def("displayDomains", &displayDomains, 
				"Display domains of all issues");
	m.def("getOutcomes", &getOutcomes, 
				"Get outcomes from the outcomes data file");
	m.def("displayOutcomes", &displayOutcomes, 
				"Display outcomes");
	m.def("getExamples", &getExamples, 
				"Get training and testing examples from the examples data file");
	m.def("getExamplesWithReplacement", &getExamplesWithReplacement, 
				"sampling with replacement");
	m.def("getAllExamples", &getAllExamples, 
				"Get all examples from the examples data file");
	m.def("displayExamples", &displayExamples, 
				"Display examples");
	m.def("displayExamplesDetails", &displayExamplesDetails, 
				"Display examples in details");
	m.def("displayPerms", &displayPerms, 
				"Display permuations of strings");
	m.def("getNumUnusedExamples", &getNumUnusedExamples, 
				"");
	m.def("getNumUnusedIssues", &getNumUnusedIssues, 
				"");
	m.def("getNumOnesInBitMap", &getNumOnesInBitMap, 
				"");
	m.def("getIssIndFromName", &getIssIndFromName, 
				"");
	m.def("getValIndInIssDomain", &getValIndInIssDomain, 
				"get the index of value val in an issue's domain");
	m.def("agree", &agree, 
				"");
	m.def("getValIndInPref", &getValIndInPref, 
				"");
	m.def("printVstring", &printVstring, 
				"");
	m.def("printVi", &printVi, 
				"");
	m.def("sumVi", &sumVi, 
				"");
	m.def("getTrainStrictExamplesPerTree", &getTrainStrictExamplesPerTree, 
				"Get numTrainStrictExamplesPerTree examples from trainStrictExamples starting from position startingPos, if possible; Otherwise, get whatever that is left.");
	m.def("getTrainStrictExamplesPerTreeRandom", &getTrainStrictExamplesPerTreeRandom, 
				"Get numTrainStrictExamplesPerTree examples randomly from trainStrictExamples");
	m.def("getTrainStrictExamplesPerTreeRandomWithReplacement", &getTrainStrictExamplesPerTreeRandomWithReplacement, 
				"");
	m.def("getNumLinesInFile", &getNumLinesInFile, 
				"");
	m.def("getLinesInFile", &getLinesInFile, 
				"");
	m.def("getRandStrings", &getRandStrings, 
				"Get number strings randomly from strings");
	m.def("computeSizeOfCombDomain", &computeSizeOfCombDomain, 
				"compute the size of the combinatorial domain (i.e., total number of outcomes)");
	m.def("computeSpearmanRhoBetweenTotalOrders", &computeSpearmanRhoBetweenTotalOrders, 
				"compute the Spearman's Rho between two total orders");
	m.def("computeTotalOrderFromTotalPreorder", &computeTotalOrderFromTotalPreorder, 
				"linearize a given total preorder to compute a total order tie breaking rule is applied in favor of smaller-indexed outcomes");
	m.def("computeOutcomeFromIndInCombDomain", &computeOutcomeFromIndInCombDomain, 
				"compute the outcome at ind position in the combinatorial space");
	m.def("computeIndFromOutcomeInCombDomain", &computeIndFromOutcomeInCombDomain, 
				"compute the index of a given outcome o in the combinatorial domain");
	m.def("tabs", &tabs, 
				"generate tabs of count many and return them as a string");
}
