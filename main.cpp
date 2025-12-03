#include <iostream>
#include "Vol.h"
#include "Candidats.h"

using namespace std;

int main() {
    
    for(int i = 0; i < 10; i++) {
        Vol v(i,'i',10,30);
        v.imprimir_vol();
    }
    
    return 0;
}