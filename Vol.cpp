#include "Vol.h"
#include <iostream>

Vol::Vol(int id, int hora, int minut, char tipus) 
    :id(id), hora(hora), minut(minut), tipus(tipus)
{

}

int Vol::get_id() const {
    return id;
}

int Vol::get_hora() const {
    return hora;
}

int Vol::get_minut() const {
    return minut;
}

char Vol::get_tipus() const {
    return tipus;
}

void Vol::print() const {
    cout << id << " " << tipus << " " << hora << ":" << minut << endl;
}