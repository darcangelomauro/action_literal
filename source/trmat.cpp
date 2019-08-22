#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "trmat.hpp"

using namespace std;

// Constructors
TrMat::TrMat(const TrMat& M)
{
    C = M.get_C();
    for(unsigned i=0; i<M.size_OMG(); ++i)
        OMG.push_back(M.get_OMG(i));
    for(unsigned i=0; i<M.size_TR(); ++i)
        TR.push_back(M.get_TR(i));
    for(unsigned i=0; i<M.size_MAT(); ++i)
        MAT.push_back(M.get_MAT(i));
}
    
TrMat& TrMat::operator=(const TrMat& M)
{
    OMG.clear();
    TR.clear();
    MAT.clear();

    C = M.get_C();
    for(unsigned i=0; i<M.size_OMG(); ++i)
        OMG.push_back(M.get_OMG(i));
    for(unsigned i=0; i<M.size_TR(); ++i)
        TR.push_back(M.get_TR(i));
    for(unsigned i=0; i<M.size_MAT(); ++i)
        MAT.push_back(M.get_MAT(i));
    
    return *this;
}

bool same(const TrMat& M1, const TrMat& M2)
{
    if(M1.size_TR() != M2.size_TR())
        return false;
    if(M1.size_MAT() != M2.size_MAT())
        return false;
    if(M1.size_OMG() != M2.size_OMG())
        return false;

    for(unsigned i=0; i<M1.size_TR(); ++i)
    {
        if(M1.get_TR(i) != M2.get_TR(i))
            return false;
    }
    for(unsigned i=0; i<M1.size_MAT(); ++i)
    {
        if(M1.get_MAT(i) != M2.get_MAT(i))
            return false;
    }
    for(unsigned i=0; i<M1.size_OMG(); ++i)
    {
        if(M1.get_OMG(i) != M2.get_OMG(i))
            return false;
    }
    
    return true;
}


ostream& operator<<(ostream& out, const TrMat& M)
{
    if(M.get_C() != 1)
        out << M.get_C();
    
    if(M.size_OMG())
    {
        out << "Tr_omg(";
        for(unsigned i=0; i<M.size_OMG(); ++i)
            out << M.get_OMG(i);
        out << ")";
    }
    else
        out << "c";

    if(M.size_TR())
    {
        out << "Tr(";
        for(unsigned i=0; i<M.size_TR(); ++i)
            out << M.get_TR(i);
        out << ")";
    }
    else
        out << "n";

    if(M.size_MAT())
    {
        out << "(";
        for(unsigned i=0; i<M.size_MAT(); ++i)
            out << M.get_MAT(i);
        out << ")^t";
    }
    else
        out << "I";


    return out;
}
