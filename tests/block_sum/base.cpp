#include <iostream>
#include <fstream>
#include "block.hpp"
#include "block_sum.hpp"

using namespace std;

int main()
{

    ifstream in1;
    in1.open("1.txt");
    ifstream in2;
    in2.open("2.txt");
    ifstream in3;
    in3.open("3.txt");
    ifstream in4;
    in4.open("4.txt");
    
    Block B1(in1);
    Block B2(in2);
    Block B3(in3);
    Block B4(in4);

    in1.close();
    in2.close();
    in3.close();
    in4.close();


    cout << B1 << endl;
    cout << B2 << endl;
    cout << B3 << endl;
    cout << B4 << endl;


    BlockSum BS1(B1);
    BlockSum BS2(B2);
    BlockSum BS3(B3);
    BlockSum BS4(B4);

    BlockSum BS5 = BS1+BS2+BS3+BS4;

    cout << BS5 << endl;

    BlockSum BS6 = BS5*BS5;

    cout << BS6 << endl;

    BS6.tracify();

    cout << BS6 << endl;



    return 0;
}
