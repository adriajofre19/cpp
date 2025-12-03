#include "Solucionador.h"

Solucionador::Solucionador(int tipus) :_trobada(false), _tipus(tipus)
{

}

Solucio Solucionador::obtenirSolucio() const
{
    if(_tipus == 0) return _solucio;
    else return _solucioOpt;
}

bool Solucionador::solucionar(const Solucio& inicial)
{
    _solucio = inicial;
    _solucioOpt = inicial;
    _trobada = false;

    if (_tipus == 0)
        return backtracking_Una();
    else if (_tipus == 1)
        backtracking_Millor();
    else
        backtracking_Totes();

    return _trobada;
}


void Solucionador::backtracking_Totes()
{
    Candidats<int> cand = _solucio.inicialitzar_candidats();

    while (!cand.fi())
    {
        if (_solucio.acceptable(cand))
        {
            _solucio.anotar(cand);

            if (_solucio.completa()) {
                // Aqu� fas el que necessitis amb totes les solucions
                // Per exemple imprimir-les, comptar-les...
            }
            else {
                backtracking_Totes();
            }

            _solucio.desanotar(cand);
        }

        cand.seguent();
    }
}

bool Solucionador::backtracking_Una()
{
    Candidats<int> cand = _solucio.inicialitzar_candidats();

    while (!cand.fi() && !_trobada)
    {
        if (_solucio.acceptable(cand))
        {
            _solucio.anotar(cand);

            if (_solucio.completa()) {
                _trobada = true;
                _solucioOpt = _solucio;   // Opcional: guardar-la
            }
            else {
                _trobada = backtracking_Una();
            }

            if (!_trobada)
                _solucio.desanotar(cand);
        }

        cand.seguent();
    }

    return _trobada;
}

void Solucionador::backtracking_Millor()
{
    Candidats<int> cand = _solucio.inicialitzar_candidats();

    while (!cand.fi())
    {
        if (_solucio.acceptable(cand) &&
            _solucio.potSerMillor(_solucioOpt, cand))
        {
            _solucio.anotar(cand);

            if (_solucio.completa()) {
                if (!_trobada || _solucio.esMillor(_solucioOpt)) {
                    _solucioOpt = _solucio;
                    _trobada = true;
                }
            }
            else {
                backtracking_Millor();
            }

            _solucio.desanotar(cand);
        }

        cand.seguent();
    }
}

