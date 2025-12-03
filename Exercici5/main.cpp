#include <iostream>
#include "Vol.h"
#include "Candidats.h"
#include <list>

using namespace std;

void imprimir_help() {
    
}

int main() {
    for(int i = 0; i < 10; i++) {
        Vol v(i,'i',10,30);
        v.imprimir_vol();
    }

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