#include <iostream>
#include "Vol.h"
#include "Candidats.h"
#include <list>

using namespace std;

void imprmir_help() {
    cout << "Us: ./e5 [-h] | [-m] [-r <int>] [-i <int>] fitxer\n\n"
         << "Opcions:\n"
         << "-h, --help   Mostra aquest missatge i surt\n"
         << "-m           Cerca la solucio que minimitza el nombre de portes\n"
         << "-r <int>     Nombre de portes regionals (default 3)\n"
         << "-i <int>     Nombre de portes internacionals (default 2)\n\n"
         << "fitxer       Fitxer de text amb els vols\n";
}

int main() {
    for(int i = 0; i < 10; i++) {
        Vol v(i,'i',10,30);
        v.imprimir_vol();
    }

    cout << "------------------------" << endl;

    // Prova de la classe Candidats amb enters
    list<int> nums = {10, 20, 30, 40};
    Candidats<int> c(nums);
    while (!c.fi()) {
        cout << "  actual = " << c.actual() << '\n';
        c.seguent();
    }

    cout << "------------------------" << endl;

    return 0;
}