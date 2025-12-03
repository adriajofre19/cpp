#ifndef SOLUCIONADOR_H
#define SOLUCIONADOR_H
#include "Solucio.h"

class Solucionador
{

    public:
        // Constructor que determina el tipus de solucio
        Solucionador(int tipus);
        // Retorna la solucio tornada
        Solucio obtenirSolucio() const;
        // Inicialitza la solucio inicial i executa backtracking
        bool solucionar(const Solucio& inicial);


    private:
        // Guarda si ha trobat o no una solucio
        bool _trobada;

        int _tipus;
        // Solucio que construeix i solucio optima
        Solucio _solucio, _solucioOpt;

        // Implementa l'esquema (recursiu)
        // Pot haver-ne  una per cada variant de l'esquema
        void backtracking_Totes();
        bool backtracking_Una();
        void backtracking_Millor();

};

#endif // SOLUCIONADOR_H
