#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "Vol.h"
#include "Solucio.h"
#include "Solucionador.h"

using namespace std;

void mostrarAjuda() {
    cout << "Us: ./e5 [-h] | [-m] [-r <int>] [-i <int>] fitxer\n\n"
         << "Opcions:\n"
         << "-h, --help   Mostra aquest missatge i surt\n"
         << "-m           Cerca la solucio que minimitza el nombre de portes\n"
         << "-r <int>     Nombre de portes regionals (default 3)\n"
         << "-i <int>     Nombre de portes internacionals (default 2)\n\n"
         << "fitxer       Fitxer de text amb els vols\n";
}

void imprimirSolucio(const Solucio& sol, int maxInt) {
    const auto& portes = sol.getPortes();

    int numUsades = 0;
    for (const auto& p : portes)
        if (!p.empty()) numUsades++;

    int comptaINT = 0;

    // Imprimir cada porta
    for (int i = 0; i < portes.size(); i++) {
        if (portes[i].empty()) continue;

        cout << "*************************\n";
        cout << "* Porta " << (i + 1) << " (";

        if (portes[i].size() > 0 && portes[i][0].get_tipus() == 'i')
            cout << "INT";
        else
            cout << "REG";

        cout << "): " << portes[i].size() << " vols *\n";
        cout << "*-----------------------*\n";

        for (const auto& v : portes[i]) {
            cout << "* Vol: " << v.get_id()
                 << " [" << (v.get_hores() < 10 ? "0" : "") << v.get_hores()
                 << ":" << (v.get_minuts() < 10 ? "0" : "") << v.get_minuts()
                 << "] " << (v.get_tipus() == 'i' ? "INT" : "REG") << " *\n";
        }
        cout << "*************************\n\n";

        // comptar INT per la l�nia final
        if (!portes[i].empty() && portes[i][0].get_tipus() == 'i')
            comptaINT++;
    }

    cout << "Num. portes : " << numUsades
         << " (INT.: " << comptaINT << ")\n";
}

int main(int argc, char* argv[]) {

    if (argc == 1) {
        cout << "Falten arguments (\"./e5 --help\" per ajuda)\n";
        return 1;
    }

    // Defaults
    int r = 3;
    int i = 2;
    bool modeMillor = false;
    string fitxer = "";

    // Llegim arguments
    int k = 1;
    while (k < argc) {

        string arg = argv[k];

        if (arg == "-h" || arg == "--help") {
            mostrarAjuda();
            return 0;
        }

        else if (arg == "-m") {
            modeMillor = true;
        }

        else if (arg == "-r") {
            if (k + 1 >= argc) {
                cout << "Error: El valor associat a l'opcio '-r' es incorrecte.\n";
                return 1;
            }
            try { r = stoi(argv[++k]); }
            catch (...) {
                cout << "Error: El valor associat a l'opcio '-r' es incorrecte.\n";
                return 1;
            }
        }

        else if (arg == "-i") {
            if (k + 1 >= argc) {
                cout << "Error: El valor associat a l'opcio '-i' es incorrecte.\n";
                return 1;
            }
            try { i = stoi(argv[++k]); }
            catch (...) {
                cout << "Error: El valor associat a l'opcio '-i' es incorrecte.\n";
                return 1;
            }
        }

        else {
            // �s el nom del fitxer
            fitxer = arg;
        }

        k++;
    }

    if (fitxer == "") {
        cout << "Error: Falta el nom del fitxer.\n";
        return 1;
    }

    // Obrir fitxer
    ifstream fin(fitxer);

    if (!fin) {
        cout << "Error: El fitxer [" << fitxer << "] no es pot obrir. "
             << "Repassa el nom i permisos.\n";
        return 1;
    }

    // Llegir vols
    vector<Vol> vols;
    string line;

    getline(fin, line); // ignorem la cap�alera

    while (getline(fin, line)) {
        if (line == "") continue;

        stringstream ss(line);
        int id;
        char tipus;
        string hora;

        ss >> id >> tipus >> hora;

        int HH = stoi(hora.substr(0, 2));
        int MM = stoi(hora.substr(3, 2));

        vols.push_back(Vol(id, tipus, HH, MM));
    }

    fin.close();

    cout << "==> " << vols.size() << " vols llegits.\n\n";

    // Ordenar per hora
    sort(vols.begin(), vols.end(),
         [](const Vol& a, const Vol& b){
             return a.getMinutsTotals() < b.getMinutsTotals();
         });

    // Soluci� inicial
    Solucio inicial(vols, r, i);

    // Crear solucionador
    Solucionador solver(modeMillor ? 1 : 0);

    auto t0 = chrono::high_resolution_clock::now();
    solver.solucionar(inicial);
    auto t1 = chrono::high_resolution_clock::now();

    Solucio solFinal = solver.obtenirSolucio();

    // Imprimir soluci�
    imprimirSolucio(solFinal, i);

    double temps = chrono::duration<double>(t1 - t0).count();
    cout << "Temps : " << temps << " segons\n";

    return 0;
}