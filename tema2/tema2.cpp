#include<bits/stdc++.h>
using namespace std;

int pasi1 = -1, pasi2 = -1;

//functia F
double F(double x) {
    double x2 = x*x;
    return  x2*x2-6*x2*x+13*x2-12*x+4;
}

//var 1 aproximare F'
double G1(double x, double h) {
    return (3.0*F(x) - 4.0*F(x-h) + F(x-2*h)) / (2.0*h);
}

//var 2 aproximare F'
double G2(double x, double h) {
    return (-F(x+2.0*h) + 8*F(x+h) - 8*F(x-h) + F(x-2.0*h)) / (12.0*h);
}

//aproximare derivata a doua
double F_secund(double x, double h) {
    return (-F(x+2.0*h)+16.0*F(x+h)-30.0*F(x)+16.0*F(x-h)-F(x-2.0*h)) / (12.0*h*h);
}

void metoda_secantei(int metoda_derivata, double h, double epsilon, int max_interatii) {
    bool ok = 0;
    double x0, x1; //primele 2 valori random

    while (!ok) {
        double min = 0.5, max = 3.0;
        x0 = min + (max - min) * ((double)std::rand() / RAND_MAX);
        x1 = min + (max - min) * ((double)std::rand() / RAND_MAX);
        
        while (x0 == x1) {
            x1 = min + (max - min) * ((double)std::rand() / RAND_MAX);
        }
        int pasi = 0;
        double rez = 0;
        double delta;
        double numitor, gx1, gx0;
        do {
            
            if (metoda_derivata == 1) {
                gx0 = G1(x0, h);
                gx1 = G1(x1, h);
            } else {
                gx0 = G2(x0, h);
                gx1 = G2(x1, h);
            }
            numitor = gx1 - gx0;
            
            if (abs(numitor) <= epsilon) {
                if (abs(gx1) <= epsilon / 100.0) {
                    delta = 0;
                    break;
                } else {
                    delta = 1e-5;
                }
            } else {
                delta = (x1-x0) * gx1 / numitor;
            }

            x0 = x1;
            x1 = x1 - delta;
            pasi++;

        } while (pasi <= max_interatii && epsilon <= abs(delta) && abs(delta) <= 1e8);

        if (abs(delta) < epsilon) {
            rez = x1;
            if (F_secund(rez, h) > 0) {
                cout << "Punct de minim: " << rez << '\n';
                if (metoda_derivata == 1) pasi1 = pasi;
                else pasi2 = pasi;
                ok = 1;
            } else {
                cout << "Punct de maxim: " << rez << '\n';
            }
        } else {
            cout << "Divergenta\n";
        }
    }
    

    //do{
        //calculez delta
        //calculez numitorul
        //daca este < epsilon
            //conditii
        //x0 = x1
        //x1 -= delta
        //pasi++

    //} while(/*delta > epsilon, pasi<=nrmaxpasi, delta <= 1e8*/);
    //if (/*delta < epsilon*/) //am o valoare
    //else //divergenta, trebuie sa schimb x0, x1
}

int main() {
    int max_iteratii = 1000;
    double epsilon = 1e-4;
    double h = 1e-5;
    metoda_secantei(1, h, epsilon, max_iteratii);
    cout << endl;
    metoda_secantei(2, h, epsilon, max_iteratii);

    if (pasi1 != -1 && pasi2 != -1) {
        cout << "Diferenta de pasi: " << abs(pasi1 - pasi2) << '\n';
    }

    return 0;
}