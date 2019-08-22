#include <iostream>
#include <fstream>
#include "block.hpp"
#include "block_sum.hpp"
#include "derivative.hpp"
#include "utils.hpp"

using namespace std;

int main()
{

    vector<int> eps_v;

    ifstream in;
    in.open("init.txt");
    
    if(in)
    {
        int idx;
        string sgn;
        while(in >> idx >> sgn)
        {
            if(sgn=="+")
            {
                eps_v.push_back(1);
            }
            else if(sgn=="-")
            {
                eps_v.push_back(-1);
            }
        }
    }

    unsigned nHL = eps_v.size();

    int* eps = new int [nHL];

    for(unsigned i=0; i<nHL; ++i)
        eps[i] = eps_v[i];

    in.close();

    Derivative D = der_dirac4(nHL, eps, 0);

    cout << D << endl;


    delete [] eps;

    return 0;
}
