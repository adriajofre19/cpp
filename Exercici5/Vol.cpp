#include "Vol.h"
#include <iostream>

Vol::Vol(int id, char tipus, int hores, int minuts) 
    :id(id), tipus(tipus), hores(hores), minuts(minuts)
{

}

int Vol::get_id() const {
    return id;
}

int Vol::get_hores() const {
    return hores;
}

int Vol::get_minuts() const {
    return minuts;
}

char Vol::get_tipus() const {
    return tipus;
}

int Vol::getMinutsTotals() const {
    return hores * 60 + minuts;
}

void Vol::imprimir_vol() const {
    cout << id << " " << tipus << " " << hores << ":" << minuts << endl;
}