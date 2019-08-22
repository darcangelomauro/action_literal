#include <vector>
#include <iostream>
#include "block.hpp"
#include "block_sum.hpp"

using namespace std;

// Constructors

BlockSum::BlockSum(const Block& B1)
{
    B.push_back(B1);
}
    
BlockSum::BlockSum(const BlockSum& BS)
{
    for(unsigned i=0; i<BS.size(); ++i)
        B.push_back(BS.get_B(i));
}

BlockSum& BlockSum::operator=(const BlockSum& BS)
{
    B.clear();

    for(unsigned i=0; i<BS.size(); ++i)
        B.push_back(BS.get_B(i));

    return *this;
}

istream& BlockSum::read_block_sum(istream& in)
{
    if(in)
    {
        int idx;
        string sgn;
        while(in >> idx >> sgn)
        {
            if(sgn=="+")
            {
                Block B1(1, idx, 1);
                Block B2(1, idx, 0);
                B.push_back(B1);
                B.push_back(B2);
            }
            else if(sgn=="-")
            {
                Block B1(1, idx, 1);
                Block B2(-1, idx, 0);
                B.push_back(B1);
                B.push_back(B2);
            }
        }
         
        // clear input stream state
        in.clear();
    }

    return in;
}

ostream& operator<<(ostream& out, const BlockSum& BS)
{
    for(unsigned i=0; i<BS.size(); ++i)
    {
        if(i!=0)
            out << " + ";
        out << BS.get_B(i);
    }

    return out;
}


void BlockSum::delete_vanishing()
{
    for(vector<Block>::iterator iter=B.begin(); iter!=B.end(); ++iter)
    {
        if((*iter).is_zero())
        {
            B.erase(iter);
            --iter;
        }
    }
}

Derivative BlockSum::take_derivative(const int& k) const
{
    Derivative D;
    for(vector<Block>::const_iterator iter=B.begin(); iter!=B.end(); ++iter)
        D += Derivative(*iter, k);

    return D;
}

void BlockSum::gather()
{
    for(vector<Block>::iterator iter1=B.begin(); iter1!=B.end(); ++iter1)
    {
        if((*iter1).is_nonzero())
        {
            for(vector<Block>::iterator iter2=iter1+1; iter2!=B.end(); ++iter2)
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

void BlockSum::tracify()
{
    for(vector<Block>::iterator iter=B.begin(); iter!=B.end(); ++iter)
        (*iter).tracify();
    gather();
}



























