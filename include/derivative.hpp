#ifndef DERIVATIVE_HPP
#define DERIVATIVE_HPP

#include <vector>
#include <iostream>
#include "block.hpp"
#include "trmat.hpp"

class Derivative
{
    public:

        // ============== CONSTRUCTORS, ASSIGNMENT, DESTRUCTOR
        Derivative(){}
        Derivative(const std::vector<TrMat>& v): TM(v) {}
        Derivative(const Block&, const int&);
        Derivative(const Derivative& D);
        Derivative& operator=(const Derivative& D);
        ~Derivative(){}
        // ============== CONSTRUCTORS, ASSIGNMENT, DESTRUCTOR


        // ============== OPERATORS
        Derivative& operator*=(const int& n)
        {
            for(std::vector<TrMat>::iterator iter=TM.begin(); iter!=TM.end(); ++iter)
                (*iter) *= n;

            return *this;
        }
        Derivative& operator+=(const Derivative& D)
        {
            for(unsigned i=0; i<D.size(); ++i)
                TM.push_back(D.get_TM(i));

            gather();

            return *this;
        }
        friend Derivative operator+(Derivative D1, const Derivative& D2){ D1+=D2; return D1; }
        // ============== OPERATORS


        // ============== GET METHODS
        TrMat get_TM(const unsigned& i) const { return TM[i]; }
        unsigned size() const { return TM.size(); }
        // ============== GET METHODS


        // ============== OTHER METHODS
        Derivative& t();
        Derivative& T();
        void delete_vanishing();
        void gather();
        // ============== OTHER METHODS

    private:
        
        std::vector<TrMat> TM; 

};

std::ostream& operator<<(std::ostream&, const Derivative&);


#endif

