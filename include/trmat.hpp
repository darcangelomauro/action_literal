#ifndef TRMAT_HPP
#define TRMAT_HPP

#include <vector>
#include <iostream>

class TrMat
{
    public:

        // ============== CONSTRUCTORS, ASSIGNMENT, DESTRUCTOR
        TrMat(const int& C_p, const std::vector<int>& OMG_p, const std::vector<int>& TR_p, const std::vector<int>& MAT_p): C(C_p), OMG(OMG_p), TR(TR_p), MAT(MAT_p) {}
        TrMat(const TrMat&);
        TrMat& operator=(const TrMat&);
        ~TrMat(){}
        // ============== CONSTRUCTORS, ASSIGNMENT, DESTRUCTOR

        // ============== OPERATORS
        TrMat& operator*=(const int& n) { C *= n; return *this; }
        // ============== OPERATORS

        // ============== GET METHODS
        int get_C() const { return C; }
        int get_OMG(const unsigned& i) const { return OMG[i]; }
        int get_TR(const unsigned& i) const { return TR[i]; }
        int get_MAT(const unsigned& i) const { return MAT[i]; }
        unsigned size_OMG() const { return OMG.size(); }
        unsigned size_TR() const { return TR.size(); }
        unsigned size_MAT() const { return MAT.size(); }
        bool is_nonzero() const { return C; }
        bool is_zero() const { return !C; }
        // ============== GET METHODS


        // ============== OTHER METHODS
        TrMat& t(); 
        TrMat& T();
        void make_vanish() { C=0; }
        void add_to_C(const int& n) { C+=n; }
        // ============== OTHER METHODS


    private:
        
        int C; 
        std::vector<int> OMG; 
        std::vector<int> TR; 
        std::vector<int> MAT; 

};


std::ostream& operator<<(std::ostream&, const TrMat&);
bool same(const TrMat&, const TrMat&);

#endif

