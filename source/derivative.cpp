#include <vector>
#include <iostream>
#include "block.hpp"
#include "trmat.hpp"
#include "derivative.hpp"

using namespace std;

// Constructors

// B is assumed to be tracified
Derivative::Derivative(const Block& B, const int& k)
{
    // keep on generating TrMats from
    // cyclic permutations of B
    Block B_cpy = B;
    for(unsigned i=0; i<B_cpy.size_LHS(); ++i)
    {
        B_cpy.cycle_LHS();
        TM.push_back( B_cpy.take_derivative(k, "LHS") );
    }
    for(unsigned i=0; i<B_cpy.size_RHS(); ++i)
    {
        B_cpy.cycle_RHS();
        TM.push_back( B_cpy.take_derivative(k, "RHS") );
    }

    gather();
}

Derivative::Derivative(const Derivative& D)
{
    for(unsigned i=0; i<D.size(); ++i)
        TM.push_back(D.get_TM(i));
}

Derivative& Derivative::operator=(const Derivative& D)
{
    TM.clear();

    for(unsigned i=0; i<D.size(); ++i)
        TM.push_back(D.get_TM(i));

    return *this;
}

ostream& operator<<(ostream& out, const Derivative& D)
{
    for(unsigned i=0; i<D.size(); ++i)
    {
        if(i!=0)
            out << " + ";
        out << D.get_TM(i);
    }

    return out;
}

Derivative& Derivative::t()
{
    for(vector<TrMat>::iterator iter=TM.begin(); iter!=TM.end(); ++iter)
        (*iter).t();

    return *this;
}

Derivative& Derivative::T()
{
    for(vector<TrMat>::iterator iter=TM.begin(); iter!=TM.end(); ++iter)
        (*iter).T();

    return *this;
}

void Derivative::delete_vanishing()
{
    for(vector<TrMat>::iterator iter=TM.begin(); iter!=TM.end(); ++iter)
    {
        if((*iter).is_zero())
        {
            TM.erase(iter);
            --iter;
        }
    }
}


void Derivative::gather()
{
    for(vector<TrMat>::iterator iter1=TM.begin(); iter1!=TM.end(); ++iter1)
    {
        if((*iter1).is_nonzero())
        {
            for(vector<TrMat>::iterator iter2=iter1+1; iter2!=TM.end(); ++iter2)
            {
                if(same(*iter1, *iter2))
                {
                    (*iter1).add_to_C((*iter2).get_C());
                    (*iter2).make_vanish();
                }
            }
        }
    }

    delete_vanishing();
}
























