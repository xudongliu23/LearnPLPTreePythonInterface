# LearnPLPTreePythonInterface

This project provides a Python interface that one can use to expose PLP-tree 
learning methods written in C++ to Python.

## pybind11
This project relies on [pybind11] (http://pybind11.readthedocs.io/en/latest/)


## How to use it?

### Compile
To compile the shared object libraries (.so) for Python to use, 
one needs to follow the steps below.

We will assume you have Python 2.7 installed.

Download [pybind11 on github] (https://github.com/xudongliu23/pybind11).
**Note** that you'd want it cloned at your home directory (~).

Then, to build, follow these [instructions] (http://pybind11.readthedocs.io/en/latest/basics.html).

Then execute command on a command line:
```
make
```


### Use the compiled libraries in Python

On a command line:
```
cd test/
python test.py
python learnCICP.py
```

## Versioning

We use [github](https://github.com/) for version control.

## Authors

* [Xudong Liu](https://www.unf.edu/~xudong.liu/)


## License

This project is currently not under any license.

## Acknowledgments

* Pybind11
* GitHub Flavored Markdown
* Doxygen
* etc
