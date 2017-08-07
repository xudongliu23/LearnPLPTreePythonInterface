#include "include/helper.h"
namespace py = pybind11;

PYBIND11_MODULE (helper, m) {
	m.doc() = "pybind11 for helper.h";

	m.def("numberToString", numberToString<char>);
	m.def("numberToString", numberToString<int>);
	m.def("numLinesInFile", &numLinesInFile, 
				"Returns the number of lines in file");
	m.def("split", &split, 
				"Splits a string to a vector of strings based on a character");
	m.def("LevenshteinDistance", &LevenshteinDistance, 
				"Returns the edit distance of two int vectors");
	m.def("computeSizeOfIntersection", &computeSizeOfIntersection, 
				"Computes the size of the intersections of two int vectors");
	m.def("eqVectors", &eqVectors, 
				"Check if two string vectors are equal");
}
