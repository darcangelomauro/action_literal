#ifndef BLOCK_SUM_HPP
#define BLOCK_SUM_HPP

#include <vector>
#include <iostream>
#include "block.hpp"
#include "derivative.hpp"

class BlockSum
{
    public:

        // ============== CONSTRUCTORS, ASSIGNMENT, DESTRUCTOR
        BlockSum(){}
        BlockSum(const Block& B1);
        BlockSum(std::istream& in) { read_block_sum(in); }
        BlockSum(const BlockSum& BS);
        BlockSum& operator=(const BlockSum& BS);
        ~BlockSum(){}
        // ============== CONSTRUCTORS, ASSIGNMENT, DESTRUCTOR


        // ============== OPERATORS
        BlockSum& operator+=(const BlockSum& BS)
        {
            for(unsigned i=0; i<BS.size(); ++i)
                B.push_back(BS.get_B(i));

            gather();

            return *this;
        }
        friend BlockSum operator+(BlockSum BS1, const BlockSum& BS2){ BS1+=BS2; return BS1; }

        BlockSum& operator*=(const BlockSum& BS)
        {
            std::vector<Block> temp;
            for(unsigned i=0; i<B.size(); ++i)
            {
                for(unsigned j=0; j<BS.size(); ++j)
                    temp.push_back(B[i]*BS.get_B(j));
            }
            B = temp;

            gather();

            return *this;
        }
        friend BlockSum operator*(BlockSum BS1, const BlockSum& BS2){ BS1*=BS2; return BS1; }
        // ============== OPERATORS


        // ============== GET METHODS
        Block get_B(const unsigned& i) const { return B[i]; }
        unsigned size() const { return B.size(); }
        // ============== GET METHODS


        // ============== OTHER METHODS
        std::istream& read_block_sum(std::istream&);
        Derivative take_derivative(const int&) const;
        void delete_vanishing();
        void gather();
        void tracify();
        // ============== OTHER METHODS

    private:
        
        std::vector<Block> B; 

};

std::ostream& operator<<(std::ostream&, const BlockSum&);


#endif

