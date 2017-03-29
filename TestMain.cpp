#include <iostream>
#include "fMatrix.h"
#include "ParamEstimator.h"

using namespace std;

void testVectorFuns()
{
    Float A[3] = {1.1, 2.2, 3.3};
    Float B[3] = {4.4, 5.5, 6.6};

    fVector VecA(A, 3);
    fVector VecB(B, 3);

    cout << "\nVecA = " << endl;
    VecA.Show(RowVec);

    cout << "\nVecB = " << endl;
    VecB.Show();

    cout << "\nStarts to test vector operators..." << endl;

    // 1. A+B
    cout << "\n1. A+B" << endl;
    (VecA + VecB).Show();

    // 2. A-B
    cout << "\n2. A-B" << endl;
    (VecA - VecB).Show();

    // 3. -A
    cout << "\n3. -A" << endl;
    (-VecA).Show();

    // 4. A-2
    cout << "\n4. A-2" << endl;
    (VecA - 2).Show();

    // 5. 2-A
    cout << "\n5. 2-A" << endl;
    (2 - VecA).Show();

    // // 6. A*2
    cout << "\n6. A*2" << endl;
    (VecA * 2).Show();

    // 7. 0.5*B
    cout << "\n7. 0.5*B" << endl;
    (0.5 * VecB).Show();

    // 8. A/4
    cout << "\n8. A/4" << endl;
    (VecA / 4).Show();

    // 9. A/B
    cout << "\n9. A/B" << endl;
    (VecA / VecB).Show();

    // 10. A*B
    cout << "\n10. A*B" << endl;
    cout << "A*B = " << VecA * VecB << endl;

    // // 11. A^B
    cout << "\n11. A^B" << endl;
    (VecA ^ VecB).Show();

    // 12. A+=B
    cout << "\n12. A+=B" << endl;
    (VecA += VecB).Show();

    // 13. A-=B
    cout << "\n13. A-=B" << endl;
    (VecA -= VecB).Show();

    // 14. A*=5
    cout << "\n14. A*=5" << endl;
    (VecA *= 5).Show();

    // 15. A/=5
    cout << "\n15. A/=5" << endl;
    (VecA /= 5).Show();

    cout << "\nStarts to test vector functions..." << endl;

    // 16. Min(A,B)
    cout << "\n16. Min(A,B)" << endl;
    (Min(VecA, VecB)).Show();

    // 17. Max(A,B)
    cout << "\n17. Max(A,B)" << endl;
    (Max(VecA, VecB)).Show();

    // 18. Dist(A,B)
    cout << "\n18. Dist(A,B)" << endl;
    cout << "Dist(A,B) = " << Dist(VecA, VecB) << endl;

    // 19. Normalize(A,B)
    cout << "\n19. Normalize(A)" << endl;
    (Normalize(VecA)).Show();

    // 20. OneNorm(A)
    cout << "\n20. OneNorm(A)" << endl;
    cout << "OneNorm(A) = " << OneNorm(VecA) << endl;

    // 21. TwoNorm(A)
    cout << "\n21. TwoNorm(A)" << endl;
    cout << "TwoNorm(A) = " << TwoNorm(VecA) << endl;

    // 22. TwoNormSqr(A)
    cout << "\n22. TwoNormSqr(A)" << endl;
    cout << "TwoNormSqr(A) = " << TwoNormSqr(VecA) << endl;

    // 23. Sqrt(A,B)
    cout << "\n23. Sqrt(A)" << endl;
    (Sqrt(VecA)).Show();

    // 24. Mean(A)
    cout << "\n24. Mean(A)" << endl;
    cout << "Mean(A) = " << Mean(VecA) << endl;

    // 25. Var(A)
    cout << "\n25. Var(A)" << endl;
    cout << "Var(A) = " << Var(VecA) << endl;

    // 26. Std(A)
    cout << "\n26. Std(A)" << endl;
    cout << "Std(A) = " << Std(VecA) << endl;
}

void testMatrixFuns()
{
    Float A[3] = {1.1, 2.2, 3.3};
    Float B[3] = {4.4, 5.5, 6.6};

    Float C[9] = {0.9649, 0.9572, 0.1419,
                  0.1576, 0.4854, 0.4218,
                  0.9706, 0.8003, 0.9157};

    Float D[9] = {0.8147, 0.9134, 0.2785,
                  0.9058, 0.6324, 0.5469,
                  0.1270, 0.0975, 0.9575};

    Float X[15] = {0.7922, 0.9340, 0.6555,
                   0.9595, 0.6787, 0.1712,
                   0.6557, 0.7577, 0.7060,
                   0.0357, 0.7431, 0.0318,
                   0.8491, 0.3922, 0.2769};

    fVector VecA(A, 3);
    fVector VecB(B, 3);
    fVector VecC(VecA);

    fMatrix MatA(C, 3, 3);
    fMatrix MatB(D, 3, 3);
    fMatrix MatC(MatA);
    fMatrix MatX(X, 5, 3);
    fMatrix MatXt = Transp(MatX);

    cout << "\nMatA = " << endl;
    MatA.Show();

    cout << "\nMatB = " << endl;
    MatB.Show();

    cout << "\nMatX = " << endl;
    MatX.Show();

    cout << "\nMatXt = " << endl;
    MatXt.Show();

    cout << "\nStarts to test matrix operators..." << endl;
    // 1. A+B
    cout << "\n1. A+B" << endl;
    (MatA + MatB).Show();

    // 2. A-B
    cout << "\n2. A-B" << endl;
    (MatA - MatB).Show();

    // 3. -B
    cout << "\n3. -B" << endl;
    (-MatB).Show();

    // 4. 2*A
    cout << "\n4. 2*A" << endl;
    (2 * MatA).Show();

    // 5. A*0.5
    cout << "\n5. A*0.5" << endl;
    (MatA * 0.5).Show();

    // 6. A/2
    cout << "\n6. A/2" << endl;
    (MatA / 2).Show();

    // 7. A*B
    cout << "\n7. A*B" << endl;
    (MatA * MatB).Show();

    // 8. MatA*VecA
    cout << "\n8. MatA*VecA" << endl;
    (MatA * VecA).Show();

    // 9. VecA*MatA
    cout << "\n9. VecA*MatA" << endl;
    (VecA * MatA).Show(RowVec);

    // 10. A+=B
    cout << "\n10. A+=B" << endl;
    (MatA += MatB).Show();

    // 11. A-=B
    cout << "\n11. A-=B" << endl;
    (MatA -= MatB).Show();

    // 12. A*=2
    cout << "\n12. A*=2" << endl;
    (MatA *= 2).Show();

    // 13. A/=2
    cout << "\n13. A/=2" << endl;
    (MatA /= 2).Show();

    // 14. A*=B
    cout << "\n14. A*=B" << endl;
    (MatA *= MatB).Show();

    // 15. VecA*=MatA
    cout << "\n15. VecA*=MatA" << endl;
    (VecA *= MatA).Show(RowVec);

    MatA = MatC;
    VecA = VecC;

    cout << "\nStarts to test matrix functions..." << endl;

    // 16. Xt
    cout << "\n16. Xt" << endl;
    Transp(MatX).Show();

    // 17. X*Xt
    cout << "\n17. X*Xt" << endl;
    AATransp(MatX).Show();

    // 18. Xt*X
    cout << "\n18. Xt*X" << endl;
    ATranspA(MatX).Show();

    // 19, VecA*VecBt
    cout << "\n19. VecA*VecBt" << endl;
    (Outer(VecA, VecB)).Show();

    // 20, Identity(4)
    cout << "\n20. Identity(4)" << endl;
    (Identity(4)).Show();

    // 21, Diag(VecA)
    cout << "\n21. Diag(VecA)" << endl;
    (Diag(VecA)).Show();

    // 22, Diag(MatA)
    cout << "\n22. Diag(MatA)" << endl;
    (Diag(MatA)).Show();

    // 23, Diag(0.1, 0.2, 0.3)
    cout << "\n23. Diag(0.1, 0.2, 0.3)" << endl;
    (Diag(0.1, 0.2, 0.3)).Show();

    // 24. Determinant(MatA)
    cout << "\n24. Determinant(MatA) = " << Determinant(MatA) << endl;

    // 25. Trace(MatA)
    cout << "\n25. Trace(MatA) = " << Trace(MatA) << endl;

    // 26. OneNorm(MatA)
    cout << "\n26. OneNorm(MatA) = " << OneNorm(MatA) << endl;

    // 27. InfNorm(MatA)
    cout << "\n27. InfNorm(MatA) = " << InfNorm(MatA) << endl;

    // 28. Inverse(MatA)
    cout << "\n28. Inverse(MatA) = " << endl;
    (Inverse(MatA)).Show();

    // 29. Cholesky(AATransp(MatA))
    cout << "\n29. Cholesky(AATransp(MatA)) = " << endl;
    (Cholesky(AATransp(MatA), 0)).Show();

    // 30. Mean(MatA)
    cout << "\n30. Mean(MatA) = " << endl;
    (Mean(MatA)).Show();

    // 31. Cov(MatA)
    cout << "\n31. Cov(MatA) = " << endl;
    (Cov(MatA)).Show();

    // 32. Cov(VecA)
    cout << "\n32. Cov(VecA) = " << endl;
    (Cov(VecA)).Show();
}

void test_ls()
{
    double g_PH[20 * 5] = {
        0.387672857227010, 1.12718635198620, 0.343792666564358, -0.346292878031393, -1.16256240410332,
        -0.782775420572307, 0.508790271452601, 1.05106471460986, 0.149849412946617, 0.130223527365399,
        -1.70242431307364, -0.157880225490610, -0.849052630824456, 0.0720276445630019, -0.386369509952482,
        1.07711560629106, 0.845072541390849, -0.152043242485238, -0.613611436092609, 1.60065297773492,
        0.959586761686633, 0.639190912808983, 1.75056647060533, -1.18209482753559, 0.591273376749004,
        -0.597041409719408, 0.739136547804016, -0.0779942926905295, -1.23084842772030, 0.491505313295882,
        -0.0719811615343259, 0.00274368931479601, -0.522082400789671, 0.389896262474429, -0.647570852929537,
        0.480767738696790, -1.85689659346880, 0.0629818308717170, -0.477893718467461, 0.992770927195342,
        -0.260799673956048, 0.350106183006019, -2.22275454690370, 0.605879114509728, -0.790452750807849,
        0.159828019312723, 1.17377683150027, 0.898260198917533, 0.540679016153091, 1.22723883358347,
        1.87624202150408, -0.448486546809128, -0.569020370694908, 0.933670043027275, -2.20138782545931,
        -0.00370271435426153, -0.628679515874492, -1.00564110769562, 0.625574317134019, 1.48751069681045,
        1.26311967946653, -0.0974178684256868, -0.488240472130906, -0.293320195411723, -0.703724126450506,
        0.904984108933125, 0.524311724551763, -0.324495316856492, 0.0634401030481035, -0.184618630003257,
        -0.749300285989674, 0.338867183774623, -0.695323926049477, 0.292503944236043, -0.143768351922331,
        1.26372444539365, -0.418156490556024, -2.00672858542293, -0.0854239970978128, 0.311851530254381,
        -0.614774492162787, 1.52261319582141, -0.805373674520454, -1.00681184244266, 0.291563145008077,
        0.441163974588469, -1.32444882132573, -0.0720252112570499, -0.470653637336070, 1.61750294741629,
        -0.0297946834036647, -1.39064173785740, -0.977598275616295, 1.80721498146898, -0.0822444970920521,
        -0.356444277257048, 2.48762432453425, -0.577288126559509, -0.432642701248300, 0.252172248624306,
    };

    double g_PZ[20] = {
        -0.994146552487485,
        5.04994196768473,
        -6.05437468956733,
        8.50730434968539,
        1.26748490919021,
        -3.76708345909094,
        -0.910325693681669,
        -3.65999640592272,
        -2.88287528257142,
        13.3847742027202,
        -6.86296013862037,
        5.76066772910074,
        -5.12816550326088,
        -1.34811075660676,
        -0.315876870653230,
        -3.65944933297374,
        -4.76981775764919,
        -3.68303004347931,
        1.75343153385567,
        8.53781536200926,
    };
    double g_PX[5] = {0.0, 0.0, 0.0, 0.0, 0.0}; // estimates

    fMatrix MatH(20, 5, g_PH);
    fVector VecZ(20, g_PZ);
    fVector VecX(5, g_PX);

    LS_Param Param = {&MatH, &VecZ, NULL};

    CParamEstimator pe;
    pe.SetMethodParameters(LS, &Param);

    fMatrix *MatErrVar = pe.SolveOptParam(&VecX);

    cout << "LS:" << endl;
    cout << "Param:" << endl;
    VecX.Show();

    cout << "Var:" << endl;
    MatErrVar->Show();
}
int main(int argc, char **argv)
{
    // testVectorFuns();
    // testMatrixFuns();
    test_ls();
    return 0;
}
