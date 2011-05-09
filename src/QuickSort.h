/*
 ----------------------------------------------------------
|
| Software Name :HEC middleware Ver. 3.0beta
|
|   QuickSort.h
|
|                     Written by T.Takeda,    2010/06/01
|                                K.Goto,      2010/01/12
|                                K.Matsubara, 2010/06/01
|
|   Contact address : IIS, The University of Tokyo CISS
|
 ----------------------------------------------------------
*/
#include "TypeDef.h"
#include <iostream>
namespace pmw{
#ifndef _QUICKSORT_H
#define	_QUICKSORT_H
template<class T>
void QuicksortID(vector<T>& val, const uint& start, const uint& end){
    uint i= start;
    uint j= end;  
    uint base= (val[start]->getID() + val[end]->getID())/2; 
    while(true){
        while(val[i]->getID() < base) i++; 
        while(val[j]->getID() > base) j--; 
        if(i>=j) break;
        T temp = val[i];
        val[i] = val[j];
        val[j] = temp;
        i++;
        j--;
    };
    if(start < i-1) QuicksortID(val, start, i-1);
    if(end   > j+1) QuicksortID(val, j+1,   end);
};
template<class T>
void sortID(vector<T>& val, const uint& length)
{
    uint i;
    uint j;
    for(i=0; i< length-1; i++){
        for(j=i+1; j< length; j++){
            if(val[i]->getID() > val[j]->getID()){
                T temp = val[i];
                val[i] = val[j];
                val[j] = temp;
            }
        };
    };
};
#endif	/* _QUICKSORT_H */
}
