#ifndef SOLUCIO_H
#define SOLUCIO_H

#include <vector>
#include "Vol.h"
#include "Candidats.h"

using namespace std;

class Solucio
{
    public:
        Solucio();

        Solucio(const vector<Vol>& vols, int maxReg, int maxInt);

        Candidats<int> inicialitzar_candidats() const;

        bool acceptable(const Candidats<int>& candidats) const;

        void anotar(const Candidats<int>& candidats);

        void desanotar(const Candidats<int>& candidats);

        bool completa() const;

        bool potSerMillor(const Solucio& solucioOpt, const Candidats<int>& candidats) const;
        // Diu si la solucio actual es millor que solucioOpt
        bool esMillor(const Solucio& solucioOpt) const;

        int numPortesUsades() const;

        const vector<vector<Vol>>& getPortes() const;

    private:
        vector<Vol> vols;
        vector<vector<Vol>> portes;
        vector<char> tipusPorta; // 'r' o 'i'

        int idx;
        int maxReg;
        int maxInt;

        int comptarPortesUsades() const;
};

#endif // SOLUCIO_H