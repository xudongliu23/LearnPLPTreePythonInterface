#include "include/cicp_plptree.h"

PYBIND11_MAKE_OPAQUE(CicpPlptree);
PYBIND11_MAKE_OPAQUE(vCicpPlptreePtr);
PYBIND11_MAKE_OPAQUE(vi);
PYBIND11_MAKE_OPAQUE(vstring);
PYBIND11_MAKE_OPAQUE(vvstring);
PYBIND11_MAKE_OPAQUE(pIssDom);
PYBIND11_MAKE_OPAQUE(vpIssDom);
PYBIND11_MAKE_OPAQUE(umIntVstring);
PYBIND11_MAKE_OPAQUE(pii);
PYBIND11_MAKE_OPAQUE(vpii);
PYBIND11_MAKE_OPAQUE(usInt);
PYBIND11_MAKE_OPAQUE(vUsInt);

namespace py = pybind11;

PYBIND11_RUNTIME_EXCEPTION(index_error, PyExc_IndexError)
PYBIND11_RUNTIME_EXCEPTION(key_error, PyExc_KeyError)

PYBIND11_MODULE (cicp_plptree, m) {
	m.doc() = "pybind11 for cicp_plptree.h";

	m.def("trainCICPPLPTree_MH", &trainCICPPLPTree_MH, 
				"Train a CICP PLP-tree using the greedy heuristic MH");
	m.def("computeAvailableIssueCICPPLPTree_MH", &computeAvailableIssueCICPPLPTree_MH, 
				"");
	m.def("computeNumTrainStrictExamplesSatsifiedCICPPLPTree", &computeNumTrainStrictExamplesSatsifiedCICPPLPTree, 
				"");
	m.def("getPartialOutcomeCICPPLPTree", &getPartialOutcomeCICPPLPTree, 
				"");
	m.def("consistentCICPPLPTree", &consistentCICPPLPTree, 
				"Check if po1 and po2 are same, and both has prefix valuesOnInstIssuesAbove according to order specified");
	m.def("getRandIssueCICPPLPTree", &getRandIssueCICPPLPTree, 
				"");
	m.def("updateBitMapTrainStrictExampleCICPPLPTree", &updateBitMapTrainStrictExampleCICPPLPTree, 
				"");
	m.def("satisfyCICPPLPTree", &satisfyCICPPLPTree, 
				"Check the order of o1Ind and o2Ind in the CICP PLP-tree noted by head");
	m.def("satisfyCICPPLPTreeCD", &satisfyCICPPLPTreeCD, 
				"Check the order of o1Ind and o2Ind in the CICP PLP-tree noted by head");
	m.def("inTopClusterCICPPLPTree", &inTopClusterCICPPLPTree, 
				"Check if outcome oInd is in the top cluster of the induced order by the tree");
	m.def("inSecondClusterCICPPLPTree", &inSecondClusterCICPPLPTree, 
				"Check if outcome oInd is in the second cluster of the induced order by the tree");
	m.def("clusterOfOutcomeCICPPLPTree", &clusterOfOutcomeCICPPLPTree, 
				"compute the cluster leaf of a given outcome index oInd",
				py::return_value_policy::reference);
	m.def("betterClustersCICPPLPTree", &betterClustersCICPPLPTree, 
				"compute all better clusters than cluster in CICP tree head");
	m.def("betterClustersCICPPLPTreeRecur", &betterClustersCICPPLPTreeRecur, 
				"the actual recursive function called in betterClustersCICPPLPTree");
	m.def("allClustersCICPPLPTree", &allClustersCICPPLPTree, 
				"compute all clusters in CICP tree head");
	m.def("totalPreorderFromCICPPLPTree", &totalPreorderFromCICPPLPTree, 
				"compute total preorder of outcomes for a given CICP PLP-tree");
	m.def("totalPreorderOverCombDomainFromCICPPLPTree", &totalPreorderOverCombDomainFromCICPPLPTree, 
				"compute the total preorder of all outcomes in the combinatorial domain from CICP PLP-tree");
	m.def("totalPreorderOverCombDomainFromCICPPLPTreeRecur", &totalPreorderOverCombDomainFromCICPPLPTreeRecur, 
				"traverse the CICP PLP-tree and fill in totalPreorder");
	m.def("updateBitMapIssueCICPPLPTree", &updateBitMapIssueCICPPLPTree, 
				"");
	m.def("computeNumNodesCICPPLPTree", &computeNumNodesCICPPLPTree, 
				"");
	m.def("computeNumNodesCICPPLPTreeRecursive", &computeNumNodesCICPPLPTreeRecursive, 
				"");
	m.def("deleteCICPPLPTree", &deleteCICPPLPTree, 
				"");
	m.def("displayCICPPLPTree", &displayCICPPLPTree, 
				"");
	m.def("displayCICPPLPTreeRecursive", &displayCICPPLPTreeRecursive, 
				"");
	//m.def("dumpToXML", &dumpToXML, 
	//			"dump the CICP PLP-tree to an XML file");
	//m.def("dumpToXMLRecur", &dumpToXMLRecur, 
	//			"");
	m.def("computeNumSatStrictExamplesByCICPPLPTree", &computeNumSatStrictExamplesByCICPPLPTree, 
				"");
}

