#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "block.hpp"

using namespace std;

// Constructors
Block::Block(const int& c, const int& idx, const int& pos): C(c)
{
    OMG.push_back(idx);
    if(pos)
        LHS.push_back(idx);
    else
        RHS.push_back(idx);
}

Block::Block(const Block& B)
{
    C = B.get_C();
    for(unsigned i=0; i<B.size_OMG(); ++i)
        OMG.push_back(B.get_OMG(i));
    for(unsigned i=0; i<B.size_LHS(); ++i)
        LHS.push_back(B.get_LHS(i));
    for(unsigned i=0; i<B.size_RHS(); ++i)
        RHS.push_back(B.get_RHS(i));
}
    
Block& Block::operator=(const Block& B)
{
    OMG.clear();
    LHS.clear();
    RHS.clear();

    C = B.get_C();
    for(unsigned i=0; i<B.size_OMG(); ++i)
        OMG.push_back(B.get_OMG(i));
    for(unsigned i=0; i<B.size_LHS(); ++i)
        LHS.push_back(B.get_LHS(i));
    for(unsigned i=0; i<B.size_RHS(); ++i)
        RHS.push_back(B.get_RHS(i));
    
    return *this;
}

istream& Block::read_block(istream& in)
{
    if(in)
    {
        string term;
        int idx=0;
        int pos=0;
        bool sgn=false;
        
        while(in >> term)
        {
            if(term == "IDX:")
                in >> idx;
            else if(term == "POS:")
                in >> pos;
            else if(term == "SGN:")
                in >> sgn;
        }

        if(sgn)
            C = -1;
        OMG.push_back(idx);
        if(pos)
            LHS.push_back(idx);
        else
            RHS.push_back(idx);
         
        // clear input stream state
        in.clear();
    }

    return in;
}

//Delete adjacent pairs of identical indices
void Block::cleanup_omega()
{
    if(OMG.size() > 1)
    {
        // First mark pairs to be deleted by assigning to them the value -1
        // (the loop stops at end-1 because the last omega doesn't have
        // anything to be compared with)
        for(vector<int>::iterator iter=OMG.begin(); iter!=OMG.end()-1; ++iter)
        {
            vector<int>::iterator iter1 = iter+1;
            if( *iter == *iter1 )
            {
                // mark
                *iter = -1;
                *iter1 = -1;
                
                // increment iter to avoid comparing something already marked
                // at the next iteration
                ++iter;

                // unless doing so causes iter to reach the end
                if(iter == OMG.end()-1)
                    --iter;
            }
            
        }

        // After that, erase marked elements
        for(vector<int>::iterator iter=OMG.begin(); iter!=OMG.end(); ++iter)
        {
            if(*iter == -1)
            {
                OMG.erase(iter);
                --iter;
            }
        }
    }
}

void Block::decimate_omega()
{
    // Check whether the first cancels with the last
    // (which cleanup_omega doesn't do)
    if(OMG.size() > 1)
    {
        if( *(OMG.begin()) == *(OMG.end()-1) )
        {
            OMG.erase(OMG.end()-1);
            OMG.erase(OMG.begin());
        }
    }

    // Check if only one or two omegas remain
    if(OMG.size() == 1 || OMG.size() == 2)
        make_vanish();

    // Check if only one or two omegas remain
    // modulo permutations
    if(is_nonzero())
    {
        // create a copy
        vector<int> OMG_cpy = OMG;

        // sort omegas
        sort(OMG_cpy.begin(), OMG_cpy.end());

        // remove duplicates
        OMG_cpy.erase( unique( OMG_cpy.begin(), OMG_cpy.end() ), OMG_cpy.end() );

        // now for each omega count how many there are,
        // and if they are an even number erase it
        for(vector<int>::iterator iter=OMG_cpy.begin(); iter!=OMG_cpy.end(); ++iter)
        {
            int n = count(OMG.begin(), OMG.end(), *iter) % 2;
            if(!n)
            {
                OMG_cpy.erase(iter);
                --iter;
            }
        }

        // finally count how many elements remain in
        // the copy and make it vanish if it's 1 or 2
        if(OMG_cpy.size() == 1 || OMG_cpy.size() == 2)
            make_vanish();
    }
}

void cycle(vector<int>& vec)
{
    vector<int> vec_cpy = vec;
    for(unsigned i=0; i<vec_cpy.size(); ++i)
    {
        rotate(vec_cpy.begin(), vec_cpy.begin()+1, vec_cpy.end());
        if(vec_cpy < vec)
            vec = vec_cpy;
    }
}


void Block::tracify()
{
    decimate_omega();
    cycle(OMG);
    cycle(LHS);
    reverse(RHS.begin(), RHS.end());
    cycle(RHS);
    if(RHS<LHS)
        RHS.swap(LHS);
}

TrMat Block::take_derivative(const int& k, const string& side) const
{
    // If the first index of the chosen side
    // matches the index to be derived,
    // return the corresponding TrMat
    if(side == "LHS" && LHS.size() && *(LHS.begin())==k)
    {
        if(LHS.size() == 1)
        {
            vector<int> empty;
            TrMat TM(C, OMG, RHS, empty); 
            return TM;
        }
        else
        {
            vector<int> mat(LHS.begin()+1, LHS.end());
            TrMat TM(C, OMG, RHS, mat);
            return TM;
        }
    }
    if(side == "RHS" && RHS.size() && *(RHS.begin())==k)
    {
        if(RHS.size() == 1)
        {
            vector<int> empty;
            TrMat TM(C, OMG, LHS, empty); 
            return TM;
        }
        else
        {
            vector<int> mat(RHS.begin()+1, RHS.end());
            TrMat TM(C, OMG, LHS, mat);
            return TM;
        }
    }
    
    // In all other cases return a vanishing TrMat
    int c = 0;
    vector<int> empty;
    TrMat TM(c, empty, empty, empty);
    return TM;
}




bool same(const Block& B1, const Block& B2)
{
    if(B1.size_LHS() != B2.size_LHS())
        return false;
    if(B1.size_RHS() != B2.size_RHS())
        return false;
    if(B1.size_OMG() != B2.size_OMG())
        return false;

    for(unsigned i=0; i<B1.size_LHS(); ++i)
    {
        if(B1.get_LHS(i) != B2.get_LHS(i))
            return false;
    }
    for(unsigned i=0; i<B1.size_RHS(); ++i)
    {
        if(B1.get_RHS(i) != B2.get_RHS(i))
            return false;
    }
    for(unsigned i=0; i<B1.size_OMG(); ++i)
    {
        if(B1.get_OMG(i) != B2.get_OMG(i))
            return false;
    }
    
    return true;
}






ostream& operator<<(ostream& out, const Block& B)
{
    if(B.get_C() != 1)
        out << B.get_C() << ".";
    
    if(B.size_OMG())
    {
        for(unsigned i=0; i<B.size_OMG(); ++i)
            out << B.get_OMG(i);
    }
    else
        out << "I";

    out << "x";
    
    if(B.size_LHS())
    {
        for(unsigned i=0; i<B.size_LHS(); ++i)
            out << B.get_LHS(i);
    }
    else
        out << "I";

    out << "x";
    
    if(B.size_RHS())
    {
        for(unsigned i=0; i<B.size_RHS(); ++i)
            out << B.get_RHS(i);
    }
    else
        out << "I";


    return out;
}
