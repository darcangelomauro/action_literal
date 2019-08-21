#include <vector>

using namespace std;


bool cyclic_equality(vector<int> A, const vector<int>& B)
{
    vector<int>::size_type sA = A.size();
    
    if(sA != B.size())
        return false;
    else
    {
        for(unsigned i=0; i<sA; ++i)
        {
            if(A == B)
                return true;
            else
                A.rotate(A.begin(), A.begin()+1, A.end());
        }
    }

    return false;
}





