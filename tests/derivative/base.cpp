#include <iostream>
#include <fstream>
#include "block.hpp"
#include "block_sum.hpp"
#include "derivative.hpp"

using namespace std;

int main()
{

    ifstream in;
    in.open("init.txt");
    BlockSum BS(in);
    in.close();

    cout << BS << endl;
    
    BlockSum BS2 = BS*BS;

    cout << BS2 << endl;

    BS2.tracify();
    
    Derivative D = BS2.take_derivative(0);

    cout << D << endl;



    return 0;
}
