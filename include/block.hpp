#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <vector>
#include <iostream>

class Block
{
    public:

        // ============== CONSTRUCTORS, ASSIGNMENT, DESTRUCTOR
        Block(): C(1) {}
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

            omega_cleanup();
            
            return *this;
        }
        friend Block operator*(Block B1, const Block& B2){ B1*=B2; return B1; }
        // ============== OPERATORS


        // ============== GET METHODS
        int get_C() const { return C; }
        int get_OMG(unsigned i) const { return OMG[i]; }
        int get_LHS(unsigned i) const { return LHS[i]; }
        int get_RHS(unsigned i) const { return RHS[i]; }
        unsigned size_OMG() const { return OMG.size(); }
        unsigned size_LHS() const { return LHS.size(); }
        unsigned size_RHS() const { return RHS.size(); }
        bool is_nonzero() const { return C; }
        bool is_zero() const { return !C; }
        // ============== GET METHODS


        // ============== OTHER METHODS
        void make_vanish() { C=0; }
        void add_to_C(const int& n) { C+=n; }
        void omega_cleanup();
        std::istream& read_block(std::istream&);
        // ============== OTHER METHODS


    private:
        
        int C; 
        std::vector<int> OMG; 
        std::vector<int> LHS; 
        std::vector<int> RHS; 

};


std::ostream& operator<<(std::ostream& out, const Block& B);
bool same(const Block&, const Block&);


#endif

