#include <vector>
#include "trmat.hpp"
#include "derivative.hpp"

using namespace std;

Derivative compute_B4(const int& k, const int& i2, const int& i3, const int& i4, int* eps)
{
    // return value
    vector<TrMat> res;

    // OMG is fixed by k, i2, i3, i4
    vector<int> omg;
    omg.push_back(k);
    omg.push_back(i2);
    omg.push_back(i3);
    omg.push_back(i4);

    int e = eps[k]*eps[i2]*eps[i3]*eps[i4];

    if(e<0)
    {
        int c;
        vector<int> tr;
        vector<int> mat;

        // First
        c = eps[k];
        tr.push_back(i2);
        tr.push_back(i3);
        tr.push_back(i4);
        TrMat tm1(c, omg, tr, mat);
        res.push_back(tm1);
        tm1 *= -1;
        res.push_back(tm1.t());

        // Second
        tr.clear();
        mat.clear();
        c = 1;
        mat.push_back(i2);
        mat.push_back(i3);
        mat.push_back(i4);
        TrMat tm2(c, omg, tr, mat);
        res.push_back(tm2);
        tm2 *= -1;
        res.push_back(tm2.t());

        // Third
        tr.clear();
        mat.clear();
        c = eps[i2];
        tr.push_back(i2);
        mat.push_back(i3);
        mat.push_back(i4);
        TrMat tm3(c, omg, tr, mat);
        res.push_back(tm3);
        tm3 *= -1;
        res.push_back(tm3.t());

        // Fourth
        tr.clear();
        mat.clear();
        c = eps[i3];
        tr.push_back(i3);
        mat.push_back(i2);
        mat.push_back(i4);
        TrMat tm4(c, omg, tr, mat);
        res.push_back(tm4);
        tm4 *= -1;
        res.push_back(tm4.t());

        // Fifth
        tr.clear();
        mat.clear();
        c = eps[i4];
        tr.push_back(i4);
        mat.push_back(i2);
        mat.push_back(i3);
        TrMat tm5(c, omg, tr, mat);
        res.push_back(tm5);
        tm5 *= -1;
        res.push_back(tm5.t());
        
        Derivative D(res);
        return D;
    }
    else
    {
        int c;
        vector<int> tr;
        vector<int> mat;

        // First
        c = eps[k];
        tr.push_back(i2);
        tr.push_back(i3);
        tr.push_back(i4);
        TrMat tm1(c, omg, tr, mat);
        res.push_back(tm1);
        res.push_back(tm1.t());

        // Second
        tr.clear();
        mat.clear();
        c = 1;
        mat.push_back(i2);
        mat.push_back(i3);
        mat.push_back(i4);
        TrMat tm2(c, omg, tr, mat);
        res.push_back(tm2);
        res.push_back(tm2.t());

        // Third
        tr.clear();
        mat.clear();
        c = eps[i2];
        tr.push_back(i2);
        mat.push_back(i3);
        mat.push_back(i4);
        TrMat tm3(c, omg, tr, mat);
        res.push_back(tm3);
        res.push_back(tm3.t());

        // Fourth
        tr.clear();
        mat.clear();
        c = eps[i3];
        tr.push_back(i3);
        mat.push_back(i2);
        mat.push_back(i4);
        TrMat tm4(c, omg, tr, mat);
        res.push_back(tm4);
        res.push_back(tm4.t());

        // Fifth
        tr.clear();
        mat.clear();
        c = eps[i4];
        tr.push_back(i4);
        mat.push_back(i2);
        mat.push_back(i3);
        TrMat tm5(c, omg, tr, mat);
        res.push_back(tm5);
        res.push_back(tm5.t());
        
        // Sixth
        tr.clear();
        mat.clear();
        c = 2*eps[k]*eps[i2];
        tr.push_back(i3);
        tr.push_back(i4);
        mat.push_back(i2);
        TrMat tm6(c, omg, tr, mat);
        res.push_back(tm6);
        
        // Seventh
        tr.clear();
        mat.clear();
        c = 2*eps[k]*eps[i3];
        tr.push_back(i2);
        tr.push_back(i4);
        mat.push_back(i3);
        TrMat tm7(c, omg, tr, mat);
        res.push_back(tm7);
        
        // Eighth
        tr.clear();
        mat.clear();
        c = 2*eps[k]*eps[i4];
        tr.push_back(i2);
        tr.push_back(i3);
        mat.push_back(i4);
        TrMat tm8(c, omg, tr, mat);
        res.push_back(tm8);
        
        Derivative D(res);
        return D;
    }
}


Derivative compute_B2(const int& k, const int& i, int* eps)
{
    // return value
    vector<TrMat> res;

    // First compute OMG k, i, i, k
    vector<int> omg;
    omg.push_back(k);
    omg.push_back(i);
    omg.push_back(i);
    omg.push_back(k);

    int c;
    vector<int> tr;
    vector<int> mat;
    
    // First
    c = 4*eps[k];
    tr.push_back(i);
    tr.push_back(i);
    tr.push_back(k);
    TrMat tm1(c, omg, tr, mat);
    res.push_back(tm1);
    res.push_back(tm1);

    // Second
    tr.clear();
    mat.clear();
    c = 2;
    mat.push_back(i);
    mat.push_back(i);
    mat.push_back(k);
    TrMat tm2(c, omg, tr, mat);
    res.push_back(tm2);
    res.push_back(tm2.t());

    // Third
    tr.clear();
    mat.clear();
    c = 4*eps[i];
    tr.push_back(i);
    mat.push_back(i);
    mat.push_back(k);
    TrMat tm3(c, omg, tr, mat);
    res.push_back(tm3);
    res.push_back(tm3.t());

    // Fourth
    tr.clear();
    mat.clear();
    c = 8*eps[k]*eps[i];
    tr.push_back(i);
    tr.push_back(k);
    mat.push_back(i);
    TrMat tm4(c, omg, tr, mat);
    res.push_back(tm4);

    // Fifth
    tr.clear();
    mat.clear();
    c = 4*eps[k];
    tr.push_back(k);
    mat.push_back(i);
    mat.push_back(i);
    TrMat tm5(c, omg, tr, mat);
    res.push_back(tm5);

    // Sixth
    tr.clear();
    mat.clear();
    c = 4;
    tr.push_back(i);
    tr.push_back(i);
    mat.push_back(k);
    TrMat tm6(c, omg, tr, mat);
    res.push_back(tm6);


    // Now compute OMG k, i, k, i
    omg.clear();
    omg.push_back(k);
    omg.push_back(i);
    omg.push_back(k);
    omg.push_back(i);

    // First
    tr.clear();
    mat.clear();
    c = 2*eps[k];
    tr.push_back(i);
    tr.push_back(i);
    tr.push_back(k);
    TrMat tm7(c, omg, tr, mat);
    res.push_back(tm7);

    // Second
    tr.clear();
    mat.clear();
    c = 2;
    mat.push_back(i);
    mat.push_back(k);
    mat.push_back(i);
    TrMat tm8(c, omg, tr, mat);
    res.push_back(tm8);

    // Third
    tr.clear();
    mat.clear();
    c = 2*eps[i];
    tr.push_back(i);
    mat.push_back(i);
    mat.push_back(k);
    TrMat tm9(c, omg, tr, mat);
    res.push_back(tm9);
    res.push_back(tm9.t());

    // Fourth
    tr.clear();
    mat.clear();
    c = 4*eps[k]*eps[i];
    tr.push_back(i);
    tr.push_back(k);
    mat.push_back(i);
    TrMat tm10(c, omg, tr, mat);
    res.push_back(tm10);

    // Fifth
    tr.clear();
    mat.clear();
    c = 2*eps[k];
    tr.push_back(k);
    mat.push_back(i);
    mat.push_back(i);
    TrMat tm11(c, omg, tr, mat);
    res.push_back(tm11);

    // Sixth
    tr.clear();
    mat.clear();
    c = 2;
    tr.push_back(i);
    tr.push_back(i);
    mat.push_back(k);
    TrMat tm12(c, omg, tr, mat);
    res.push_back(tm12);
    
    Derivative D(res);
    return D;
}

Derivative compute_B(const int& k, int* eps)
{
    // return value
    vector<TrMat> res;

    // OMG is empty
    vector<int> omg;

    int c;
    vector<int> tr;
    vector<int> mat;
    
    // First
    c = 2;
    mat.push_back(k);
    mat.push_back(k);
    mat.push_back(k);
    TrMat tm1(c, omg, tr, mat);
    res.push_back(tm1);

    // Second
    tr.clear();
    mat.clear();
    c = 2*eps[k];
    tr.push_back(k);
    tr.push_back(k);
    tr.push_back(k);
    TrMat tm2(c, omg, tr, mat);
    res.push_back(tm2);

    // Third
    tr.clear();
    mat.clear();
    c = 6;
    tr.push_back(k);
    tr.push_back(k);
    mat.push_back(k);
    TrMat tm3(c, omg, tr, mat);
    res.push_back(tm3);
    
    // Fourth
    tr.clear();
    mat.clear();
    c = 6*eps[k];
    tr.push_back(k);
    mat.push_back(k);
    mat.push_back(k);
    TrMat tm4(c, omg, tr, mat);
    res.push_back(tm4);

    Derivative D(res);
    return D;
}

Derivative der_dirac4(const int& nHL, int* eps, const int& k)
{
    Derivative res;

    // four distinct indices
    for(int i1=0; i1<nHL; ++i1)
    {
        if(i1 != k)
        {
            for(int i2=i1+1; i2<nHL; ++i2)
            {
                if(i2 != k)
                {
                    for(int i3=i2+1; i3<nHL; ++i3)
                    {
                        if(i3 != k)
                        {
                            Derivative temp = compute_B4(k,i1,i2,i3, eps) + compute_B4(k,i1,i3,i2, eps) + compute_B4(k,i2,i1,i3, eps);
                            res += temp + temp.T();
                        }
                    }
                }
            }
        }
    }

    // two distinct pairs of equal indices
    for(int i=0; i<nHL; ++i)
    {
        if(i != k)
            res += compute_B2(k,i, eps);
    }

    // all indices equal
    res += compute_B(k, eps);

    // simplify
    res.gather();

    res *= 4;
    return res;
}



Derivative der_dirac2(int* eps, const int& k)
{
    vector<int> empty;
    vector<int> non_empty;

    non_empty.push_back(k);

    TrMat tm1(4, empty, empty, non_empty);
    TrMat tm2(4*eps[k], empty, non_empty, empty);

    vector<TrMat> res;
    res.push_back(tm1);
    res.push_back(tm2);

    Derivative D(res);
    return D;
}
