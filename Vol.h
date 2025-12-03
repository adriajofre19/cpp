#ifndef VOL_H
#define VOL_H

#include <string>
using namespace std;

class Vol {
private:
    int id, hora, minut;
    char tipus;

public:
    // Constructor
    Vol(int id, int hora, int minut, char tipus);

    // Getters
    int get_id() const;
    int get_hora() const;
    int get_minut() const;
    char get_tipus() const;

    void print() const;
};

#endif