/*****************************************************************
 *  Copyright (c) 2017, Xudong Liu.                              *
 *  All rights reserved.                                         *
 *****************************************************************/

/*                                                                
 * mytypes.h
 */

#ifndef TYPES_                                            
#define TYPES_                                            

#include <pybind11/pybind11.h>                                                  
#include <pybind11/stl.h>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <set>
using namespace std;

typedef unsigned int                    UInt32;
typedef int                             Int32;
typedef unsigned char                   UInt8;
typedef char                            Int8;

typedef vector<string>                  vstring;
typedef vector<vector<string> >         vvstring;
typedef vector<int>                     vi;
typedef vector<bool>                    vb;
typedef vector<float>                   vf;
typedef vector<unsigned int>            vui;
typedef long long                       ll;
typedef unsigned long long              ull;
typedef vector<ll>                      vll;

typedef pair<string,vstring>            pIssDom;
typedef vector<pIssDom>                 vpIssDom;  /* type of the domain description */
typedef pair<int,int>                   pii;
typedef vector<pii>                     vpii;      /* type of the examples */
typedef pair<string,string>             pss;
typedef pair<int,double>                pid;
typedef vector<pid>                     vpid;
typedef pair<int,float>                 pif;
typedef vector<pif>                     vpif;

typedef pair<vstring,vstring>           pVstringVstring;
typedef vector<pVstringVstring>         vpVstringVstring;
typedef pair<int,vstring>               pIntVstring;
typedef vector<pIntVstring>             vpIntVstring;

typedef unordered_map<int,vstring>      umIntVstring;
typedef unordered_map<int,int>          umIntInt;
typedef unordered_map<int,float>        umIntFloat;
typedef unordered_map<int,double>       umIntDouble;
typedef unordered_map<int,ull>          umIntULL;
typedef unordered_map<string,int>       umStringInt;

typedef map<int,vstring>                mIntVstring;

typedef unordered_set<int>              usInt;
typedef vector<usInt>                   vUsInt;
typedef set<int>                        sInt;

typedef struct CicpPlptree{
    int                         level;  /* start from 0 */
    string                      name;
    vstring                     pref;
    vstring                     pathIssNames;
    vstring                     pathIssVals;
    vector<CicpPlptree*>        subtrees;
} CicpPlptree;

typedef vector<CicpPlptree*>        vCicpPlptreePtr;

#define REP(i,a,b) \
    for(int i=(int)a; i<=(int)b; i++)

#define cMaxLengthFileName 64


#endif
