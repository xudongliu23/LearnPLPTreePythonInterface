#include "include/mytypes.h"

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

PYBIND11_MODULE (mytypes, m) {
	m.doc() = "pybind11 for mytypes.h";

	py::class_<CicpPlptree>(m, "CicpPlptree")
		.def(py::init<>())
		.def_readwrite("level", &CicpPlptree::level)
		.def_readwrite("name", &CicpPlptree::name)
		.def_readwrite("pref", &CicpPlptree::pref)
		.def_readwrite("pathIssNames", &CicpPlptree::pathIssNames)
		.def_readwrite("pathIssVals", &CicpPlptree::pathIssVals)
		.def_readwrite("substrees", &CicpPlptree::subtrees);

  py::class_<vCicpPlptreePtr>(m, "vCicpPlptreePtr")                                   
    .def(py::init<>())                                                          
    .def("empty", &vCicpPlptreePtr::empty)                                         
    .def("size", &vCicpPlptreePtr::size)                                           
    .def("clear", &vCicpPlptreePtr::clear)                                         
    .def("swap", &vCicpPlptreePtr::swap)                                           
    .def("pop_back", &vCicpPlptreePtr::pop_back)                                   
    /* There are multiple versions of push_back(), etc. Select the right ones. */
    .def("push_back", (void (vCicpPlptreePtr::*)(CicpPlptree* const&)) &vCicpPlptreePtr::push_back)
    .def("resize", (void (vCicpPlptreePtr::*)(unsigned long)) &vCicpPlptreePtr::resize)                                           
    .def("front", (CicpPlptree* &(vCicpPlptreePtr::*)()) &vCicpPlptreePtr::front)     
    .def("back", (CicpPlptree* &(vCicpPlptreePtr::*)()) &vCicpPlptreePtr::back)       
    .def("__len__", [](const vCicpPlptreePtr &v) { return v.size(); })             
    .def("__iter__", [](vCicpPlptreePtr &v) {                                      
       return py::make_iterator(v.begin(), v.end());                            
    }, py::keep_alive<0, 1>());

  py::class_<vi>(m, "vi")                                                       
    .def(py::init<>())                                                          
    .def("empty", &vi::empty)                                                   
    .def("size", &vi::size)                                                     
    .def("clear", &vi::clear)                                                   
    .def("swap", &vi::swap)                                                     
    .def("pop_back", &vi::pop_back)                                             
    /* There are multiple versions of push_back(), etc. Select the right ones. */
    .def("push_back", (void (vi::*)(const int &)) &vi::push_back)               
    .def("resize", (void (vi::*)(unsigned long)) &vi::resize)                                           
    .def("front", (int &(vi::*)()) &vi::front)                                  
    .def("back", (int &(vi::*)()) &vi::back)                                    
    .def("at", (int &(vi::*)(unsigned long)) &vi::at)                                    
    .def("__len__", [](const vi &v) { return v.size(); })                       
    .def("__iter__", [](vi &v) {                                                
       return py::make_iterator(v.begin(), v.end());                            
    }, py::keep_alive<0, 1>())
    .def("__getitem__",                                                       
        [](vi &v, vi::size_type i) -> vi::value_type & { 
            if (i >= v.size())                                                  
                throw index_error();                                            
            return v[i];                                                        
        },                                                                      
        py::return_value_policy::reference_internal // ref + keepalive              
    )
    .def("__setitem__",                                                       
        [](vi &v, vi::size_type i, const int &t) {                                 
            if (i >= v.size())                                                  
                throw index_error();                                            
            v[i] = t;                                                           
        }                                                                       
    );

  py::class_<vstring>(m, "vstring")                                                       
    .def(py::init<>())                                                          
    .def("empty", &vstring::empty)                                                   
    .def("size", &vstring::size)                                                     
    .def("clear", &vstring::clear)                                                   
    .def("swap", &vstring::swap)                                                     
    .def("pop_back", &vstring::pop_back)                                             
    /* There are multiple versions of push_back(), etc. Select the right ones. */
    .def("push_back", (void (vstring::*)(const string &)) &vstring::push_back)               
    .def("resize", (void (vstring::*)(unsigned long)) &vstring::resize)                                           
    .def("front", (string &(vstring::*)()) &vstring::front)                                  
    .def("back", (string &(vstring::*)()) &vstring::back)                                    
    .def("at", (string &(vstring::*)(unsigned long)) &vstring::at)                                    
    .def("__len__", [](const vstring &v) { return v.size(); })                       
    .def("__iter__", [](vstring &v) {                                                
       return py::make_iterator(v.begin(), v.end());                            
    }, py::keep_alive<0, 1>())
    .def("__getitem__",                                                       
        [](vstring &v, vstring::size_type i) -> vstring::value_type & { 
            if (i >= v.size())                                                  
                throw index_error();                                            
            return v[i];                                                        
        },                                                                      
        py::return_value_policy::reference_internal // ref + keepalive              
    )
    .def("__setitem__",
        [](vstring &v, vstring::size_type i, const string &t) {
            if (i >= v.size())
                throw index_error();
            v[i] = t;
        }
    );

  py::class_<vvstring>(m, "vvstring")                                                       
    .def(py::init<>())                                                          
    .def("empty", &vvstring::empty)                                                   
    .def("size", &vvstring::size)                                                     
    .def("clear", &vvstring::clear)                                                   
    .def("swap", &vvstring::swap)                                                     
    .def("pop_back", &vvstring::pop_back)                                             
    /* There are multiple versions of push_back(), etc. Select the right ones. */
    .def("push_back", (void (vvstring::*)(const vstring &)) &vvstring::push_back)
    .def("resize", (void (vvstring::*)(unsigned long)) &vvstring::resize)                                           
    .def("front", (vstring &(vvstring::*)()) &vvstring::front) 
    .def("back", (vstring &(vvstring::*)()) &vvstring::back)
    .def("at", (vstring &(vvstring::*)(unsigned long)) &vvstring::at)
    .def("__len__", [](const vvstring &v) { return v.size(); })                       
    .def("__iter__", [](vvstring &v) {                                                
       return py::make_iterator(v.begin(), v.end());                            
    }, py::keep_alive<0, 1>())
    .def("__getitem__",                                                       
        [](vvstring &v, vvstring::size_type i) -> vvstring::value_type & { 
            if (i >= v.size())                                                  
                throw index_error();                                            
            return v[i];                                                        
        },                                                                      
        py::return_value_policy::reference_internal // ref + keepalive              
    )
    .def("__setitem__",
        [](vvstring &v, vvstring::size_type i, const vstring &t) {
            if (i >= v.size())
                throw index_error();
            v[i] = t;
        }
    );

  py::class_<pii>(m, "pii")                                                     
    .def(py::init<>())                                                          
    .def_readwrite("first", &pii::first)                                        
    .def_readwrite("second", &pii::second);

  py::class_<vpii>(m, "vpii")                                                       
    .def(py::init<>())                                                          
    .def("empty", &vpii::empty)                                                   
    .def("size", &vpii::size)                                                     
    .def("clear", &vpii::clear)                                                   
    .def("swap", &vpii::swap)                                                     
    .def("pop_back", &vpii::pop_back)                                             
    /* There are multiple versions of push_back(), etc. Select the right ones. */
    .def("push_back", (void (vpii::*)(const pii &)) &vpii::push_back)               
    .def("resize", (void (vpii::*)(unsigned long)) &vpii::resize)                                           
    .def("front", (pii &(vpii::*)()) &vpii::front)                                  
    .def("back", (pii &(vpii::*)()) &vpii::back)                                    
    .def("at", (pii &(vpii::*)(unsigned long)) &vpii::at)                                    
    .def("__len__", [](const vpii &v) { return v.size(); })                       
    .def("__iter__", [](vpii &v) {                                                
       return py::make_iterator(v.begin(), v.end());                            
    }, py::keep_alive<0, 1>())
    .def("__getitem__",                                                       
        [](vpii &v, vpii::size_type i) -> vpii::value_type & { 
            if (i >= v.size())                                                  
                throw index_error();                                            
            return v[i];                                                        
        },                                                                      
        py::return_value_policy::reference_internal // ref + keepalive              
    )
    .def("__setitem__",
        [](vpii &v, vpii::size_type i, const pii &t) {
            if (i >= v.size())
                throw index_error();
            v[i] = t;
        }
    );

  py::class_<pIssDom>(m, "pIssDom")                                                     
    .def(py::init<>())                                                          
    .def_readwrite("first", &pIssDom::first)                                        
    .def_readwrite("second", &pIssDom::second);

  py::class_<vpIssDom>(m, "vpIssDom") 
    .def(py::init<>())                                                          
    .def("empty", &vpIssDom::empty)                                                   
    .def("size", &vpIssDom::size)                                                     
    .def("clear", &vpIssDom::clear)                                                   
    .def("swap", &vpIssDom::swap)                                                     
    .def("pop_back", &vpIssDom::pop_back)                                             
    /* There are multiple versions of push_back(), etc. Select the right ones. */
    .def("push_back", (void (vpIssDom::*)(const pIssDom &)) &vpIssDom::push_back)               
    .def("resize", (void (vpIssDom::*)(unsigned long)) &vpIssDom::resize)                                           
    .def("front", (pIssDom &(vpIssDom::*)()) &vpIssDom::front)                                  
    .def("back", (pIssDom &(vpIssDom::*)()) &vpIssDom::back)                                    
    .def("at", (pIssDom &(vpIssDom::*)(unsigned long)) &vpIssDom::at)                                    
    .def("__len__", [](const vpIssDom &v) { return v.size(); })                       
    .def("__iter__", [](vpIssDom &v) {                                                
       return py::make_iterator(v.begin(), v.end());                            
    }, py::keep_alive<0, 1>())
    .def("__getitem__",                                                       
        [](vpIssDom &v, vpIssDom::size_type i) -> vpIssDom::value_type & { 
            if (i >= v.size())                                                  
                throw index_error();                                            
            return v[i];                                                        
        },                                                                      
        py::return_value_policy::reference_internal // ref + keepalive              
    )
    .def("__setitem__",
        [](vpIssDom &v, vpIssDom::size_type i, const pIssDom &t) {
            if (i >= v.size())
                throw index_error();
            v[i] = t;
        }
    );

  py::class_<umIntVstring>(m, "umIntVstring") 
    .def(py::init<>())
    .def("empty", &umIntVstring::empty)
    .def("size", &umIntVstring::size)
    .def("__iter__", [](umIntVstring &v) {                                                
       return py::make_iterator(v.begin(), v.end());
    }, py::keep_alive<0, 1>())
    .def("__getitem__",
        [](umIntVstring &v, const umIntVstring::key_type &k) -> umIntVstring::mapped_type & {
            auto it = v.find(k);
            if (it == v.end())
              throw key_error();
           return it->second;
        },
        py::return_value_policy::reference_internal // ref + keepalive
    )
    .def("__setitem__",
           [](umIntVstring &n, const umIntVstring::key_type &k, const umIntVstring::mapped_type &v) {
               auto it = n.find(k);
               if (it != n.end()) it->second = v;
               else n.emplace(k, v);
           }
    );

  py::class_<usInt>(m, "usInt")                                                 
    .def(py::init<>())                                                          
    .def("empty", &usInt::empty)                                                
    .def("size", &usInt::size)                                                  
    .def("clear", &usInt::clear)                                                
    //.def("insert", (pair<iterator, bool> (usInt::*)(const int &)) &usInt::insert)
    .def("__iter__", [](usInt &s) {                                             
       return py::make_iterator(s.begin(), s.end());                            
    }, py::keep_alive<0, 1>());

  py::class_<vUsInt>(m, "vUsInt")                                                       
    .def(py::init<>())                                                          
    .def("empty", &vUsInt::empty)                                                   
    .def("size", &vUsInt::size)                                                     
    .def("clear", &vUsInt::clear)                                                   
    .def("swap", &vUsInt::swap)                                                     
    .def("pop_back", &vUsInt::pop_back)                                             
    /* There are multiple versions of push_back(), etc. Select the right ones. */
    .def("push_back", (void (vUsInt::*)(const usInt &)) &vUsInt::push_back)               
    .def("resize", (void (vUsInt::*)(unsigned long)) &vUsInt::resize)                                           
    .def("front", (usInt &(vUsInt::*)()) &vUsInt::front)                                  
    .def("back", (usInt &(vUsInt::*)()) &vUsInt::back)                                    
    .def("at", (usInt &(vUsInt::*)(unsigned long)) &vUsInt::at)                                    
    .def("__len__", [](const vUsInt &v) { return v.size(); })                       
    .def("__iter__", [](vUsInt &v) {                                                
       return py::make_iterator(v.begin(), v.end());                            
    }, py::keep_alive<0, 1>())
    .def("__getitem__",                                                       
        [](vUsInt &v, vUsInt::size_type i) -> vUsInt::value_type & { 
            if (i >= v.size())                                                  
                throw index_error();                                            
            return v[i];                                                        
        },                                                                      
        py::return_value_policy::reference_internal // ref + keepalive              
    );
}

