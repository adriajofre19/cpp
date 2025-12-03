#ifndef VOL_H
#define VOL_H
#include <string>

using namespace std;

class Vol
{
public:
    Vol(int id, char tipus, int hores, int minuts);

    // Getters
    int get_id() const;
    char get_tipus() const;
    int get_hores() const;
    int get_minuts() const;

    int getMinutsTotals() const;

    void imprimir_vol() const;

private:
    int id;
    char tipus;   // 'r' o 'i'
    int hores;
    int minuts;
};

#endif // VOL_H
