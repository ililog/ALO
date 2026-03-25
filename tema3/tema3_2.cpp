#include <iostream>
#include <cmath>
#include<iomanip>
#include<Eigen/Dense>
#include<vector>
using namespace std;

int n;
double epsilon;
//double A[100][100], LU[100][100], b[100], x[100], y[100], b_verif[100];
#define MIN -1000
#define MAX 1000

void printMatrix(vector< vector<double> > &A, int n) {
    cout << "Elementele matricei:\n";
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            cout << A[i][j] << ' ';
        }
        cout << '\n';
    }
}

int main() {

    //Citire

    cout << "Introduceti n: ";
    cin >> n;
    cout << "Introduceti precizia: ";
    cin >> epsilon;

    vector<double> b(n,0),x(n,0),y(n,0),b_verif(n,0);
    vector< vector<double> > A(n), LU(n);

    for (int i = 0; i < n; i++) 
    {
        A[i].resize(n); LU[i].resize(n);
        for (int j = 0; j < n; j++) {
            double r = MIN + (MAX-MIN) * ((double)std::rand() / RAND_MAX);
            int r2 = r;
            A[i][j] = r2;
            LU[i][j] = A[i][j];  
        }     
    }
    printMatrix(A,n);

    cout << "Introduceti termenii liberi: ";
    for (int i = 0; i < n; i++) 
    {
        cin >> b[i];
    }

    //Descompunerea LU

    for (int p = 0; p < n; p++) 
    {
        for (int i = p; i < n; i++) 
        {
            //calculam U[p][i]
            double suma = 0;
            for (int k = 0; k < p; k++) 
            {
                suma += LU[p][k] * LU[k][i];
            }
            LU[p][i] = LU[p][i] - suma;
        }

        if (abs(LU[p][p]) < epsilon) 
        {
            cout << "Matricea nu admite descompunerea LU\n";
            return 0;
        }

        for (int i = p + 1; i < n; i++) 
        {
            //calculam L[i][p]
            double suma = 0;
            for (int k = 0; k < p; k++) 
            {
                suma += LU[i][k] * LU[k][p];
            }
            LU[i][p] = (LU[i][p] - suma) / LU[p][p];
        }
    }

    double detA = 1.0;
    for (int i = 0; i < n; i++) detA *= LU[i][i];

    cout << fixed << setprecision(4) << "\nDeterminantul lui A este: " << detA << '\n';

    //A = L*U
    //A*x = b <=> L*U*x = b
    //pas 1: L*y = b
    //pas2: U*x = y

    y[0] = b[0];
    for (int p = 1; p < n; p++)
    {
        double suma = 0;
        for (int k = 0; k < p; k++)
            suma += LU[p][k] * y[k];
        y[p] = b[p] - suma;
    }

    x[n - 1] = y[n - 1] / LU[n - 1][n - 1];
    for (int p = n - 2; p >= 0; p--)
    {
        double suma = 0;
        for (int k = p + 1; k < n; k++)
            suma += LU[p][k] * x[k];
        if (abs(LU[p][p]) >= epsilon) x[p] = (y[p] - suma) / LU[p][p];
        else {
            cout << "Nu se poate calcula solutia\n";
            return 0;
        }
    }

    cout << "Solutia x calculata: ";
    for (int i = 0; i < n; i++)
        cout << x[i] << " ";
    cout << '\n';
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b_verif[i] += A[i][j] * x[j];

    double norma = 0;
    for (int i = 0; i < n; i++)
    { 
        b_verif[i] -= b[i];
        norma += b_verif[i] * b_verif[i];
    }
    norma = sqrt(norma);

    cout << "Norma ||A_init * x - b_init||_2: " << fixed << setprecision(20) << norma << '\n';

    Eigen::VectorXd b_lib(n);
    Eigen::MatrixXd A_lib(n, n);
    for (int i = 0; i<n; i++) {
        b_lib(i) = b[i];
        for (int j = 0; j<n; j++) {
            A_lib(i, j) = A[i][j];
        }
    }

    Eigen::VectorXd x_lib(n);
    x_lib = A_lib.fullPivLu().solve(b_lib);

    double norma1 = 0.0;
    for (int i = 0; i<n; i++) {
        norma1 += (x[i] - x_lib(i)) * (x[i] - x_lib(i));
    }
    norma1 = sqrt(norma1);
    cout << "Eroare fata de pivotare totala: " << fixed << setprecision(20) << norma1 << endl;

    x_lib = A_lib.partialPivLu().solve(b_lib);

    norma1 = 0.0;
    for (int i = 0; i<n; i++) {
        norma1 += (x[i] - x_lib(i)) * (x[i] - x_lib(i));
    }
    norma1 = sqrt(norma1);
    cout << "Eroare fata de pivotare partiala: " << fixed << setprecision(20) << norma1 << endl;
    
    Eigen::MatrixXd A_lib_inv(n,n);
    A_lib_inv = A_lib.inverse();
    Eigen::VectorXd ans = x_lib - A_lib_inv * b_lib;

    double norma2 = 0.0;
    for (int i = 0; i<n; i++) {
        norma2 += ans[i] * ans[i];
    }
    norma2 = sqrt(norma2);

    cout << "Norma ||x_LU - Alib^(-1) * b_init||_2 este: " << fixed << setprecision(20) << norma2 << endl;

    return 0;
}