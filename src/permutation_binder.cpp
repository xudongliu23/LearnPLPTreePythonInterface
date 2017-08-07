#include "include/permutation.h"

PYBIND11_MAKE_OPAQUE(vstring);
PYBIND11_MAKE_OPAQUE(vvstring);

namespace py = pybind11;

PYBIND11_RUNTIME_EXCEPTION(index_error, PyExc_IndexError)
PYBIND11_RUNTIME_EXCEPTION(key_error, PyExc_KeyError)

PYBIND11_MODULE (permutation, m) {
	m.doc() = "pybind11 for permutation.h";

	m.def("computePerms", &computePerms, 
				"compute permutations of a vector of strings");
	m.def("generateBinaries", &generateBinaries, 
				"generate all n-digit binary sequences");
	m.def("generateLexPerms", &generateLexPerms, 
				"generate permutations of a given string, even when it has repeated characters");
	m.def("getNextLexPerm", &getNextLexPerm, 
				"");
	m.def("reverseString", &reverseString, 
				"");
}

