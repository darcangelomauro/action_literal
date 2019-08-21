#include <iostream>
#include <fstream>
#include "block.hpp"

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


    cout << B1*B2 << endl;
    cout << B3*B2 << endl;
    cout << B1 << endl;
    cout << B2 << endl;
    cout << B4 << endl;
    cout << B1*B2*B4 << endl;

    B1.tracify();
    B2.tracify();
    B3.tracify();
    B4.tracify();

    cout << B1 << endl;
    cout << B2 << endl;
    cout << B3 << endl;
    cout << B4 << endl;
    
    return 0;
}
