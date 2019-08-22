#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include "trmat.hpp"

class Block
{
    public:

        // ============== CONSTRUCTORS, ASSIGNMENT, DESTRUCTOR
        Block(): C(1) {}
        Block(const int&, const int&, const int&);
        Block(std::istream& in): C(1) { read_block(in); }
        Block(const Block&);
        Block& operator=(const Block&);
        ~Block(){}
        // ============== CONSTRUCTORS, ASSIGNMENT, DESTRUCTOR


        // ============== OPERATORS
        Block& operator*=(const Block& B)
        {
            C *= B.get_C();
            for(unsigned i=0; i<B.size_OMG(); ++i)
                OMG.push_back(B.get_OMG(i));
            for(unsigned i=0; i<B.size_LHS(); ++i)
                LHS.push_back(B.get_LHS(i));
            for(unsigned i=0; i<B.size_RHS(); ++i)
                RHS.push_back(B.get_RHS(i));

            cleanup_omega();
            
            return *this;
        }
        friend Block operator*(Block B1, const Block& B2){ B1*=B2; return B1; }
        // ============== OPERATORS


        // ============== GET METHODS
        int get_C() const { return C; }
        int get_OMG(const unsigned& i) const { return OMG[i]; }
        int get_LHS(const unsigned& i) const { return LHS[i]; }
        int get_RHS(const unsigned& i) const { return RHS[i]; }
        unsigned size_OMG() const { return OMG.size(); }
        unsigned size_LHS() const { return LHS.size(); }
        unsigned size_RHS() const { return RHS.size(); }
        bool is_nonzero() const { return C; }
        bool is_zero() const { return !C; }
        // ============== GET METHODS


        // ============== OTHER METHODS
        void cycle_LHS() { std::rotate(LHS.begin(), LHS.begin()+1, LHS.end()); }
        void cycle_RHS() { std::rotate(RHS.begin(), RHS.begin()+1, RHS.end()); }
        void make_vanish() { C=0; }
        void add_to_C(const int& n) { C+=n; }
        std::istream& read_block(std::istream&);
        void tracify();
        TrMat take_derivative(const int&, const std::string&) const;
        // ============== OTHER METHODS


    private:
        
        void cleanup_omega(); //deletes pairs of adjacent identical indices
        void decimate_omega(); //deletes omega as if they were inside a trace
        
        int C; 
        std::vector<int> OMG; 
        std::vector<int> LHS; 
        std::vector<int> RHS; 

};


std::ostream& operator<<(std::ostream&, const Block&);
bool same(const Block&, const Block&);
void cycle(std::vector<int>&); //puts the vector into the preferred cyclic permutation


#endif

