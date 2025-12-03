#include "Solucio.h"
#include <iostream>

using namespace std;

Solucio::Solucio() : idx(0), maxReg(0), maxInt(0) {}

Solucio::Solucio(const vector<Vol>& vols, int maxReg, int maxInt)
    : vols(vols), maxReg(maxReg), maxInt(maxInt), idx(0)
{
    int total = maxReg + maxInt;
    portes.resize(total);
    tipusPorta.resize(total);

    for (int i = 0; i < maxReg; ++i) {
        tipusPorta[i] = 'r';
    }
    for (int i = maxReg; i < total; ++i) {
        tipusPorta[i] = 'i';
    }
}

Candidats<int> Solucio::inicialitzar_candidats() const {
    list<int> candidats;
    // Cal generar candidats basats en el nombre de portes disponibles
    for (size_t i = 0; i < portes.size(); ++i) {
        candidats.push_back(i);
    }
    return Candidats<int>(candidats);
}

bool Solucio::acceptable(const Candidats<int>& candidats) const {
    int p = candidats.actual();
    const Vol& v = vols[idx];

    // 1. Compatibilitat r / i
    if (v.get_tipus() == 'i' && tipusPorta[p] == 'r')
        return false;

    // 2. Comprovació de solapament (intervals de 60 minuts)
    int tNew = v.getMinutsTotals();
    int startNew = tNew - 60;
    int endNew   = tNew;

    for (const Vol& altre : portes[p]) {

        int tOld = altre.getMinutsTotals();
        int startOld = tOld - 60;
        int endOld   = tOld;

        bool solapen = !(endNew <= startOld || endOld <= startNew);

        if (solapen)
            return false;
    }

    return true;
}

void Solucio::anotar(const Candidats<int>& candidats) {
    int p = candidats.actual();
    portes[p].push_back(vols[idx]);
    idx++;
}

void Solucio::desanotar(const Candidats<int>& candidats) {
    int p = candidats.actual();
    portes[p].pop_back();
    idx--;
}

bool Solucio::completa() const {
    return idx >= static_cast<int>(vols.size());
}

int Solucio::comptarPortesUsades() const {
    int count = 0;
    for (const auto& porta : portes) {
        if (!porta.empty())
            count++;
    }
    return count;
}

bool Solucio::potSerMillor(const Solucio& solOpt, const Candidats<int>&) const
{
    return comptarPortesUsades() <= solOpt.comptarPortesUsades();
}

bool Solucio::esMillor(const Solucio& solOpt) const
{
    return comptarPortesUsades() < solOpt.comptarPortesUsades();
}

int Solucio::numPortesUsades() const {
    return portes.size();
}

const vector<vector<Vol>>& Solucio::getPortes() const {
    return portes;
}
