#ifndef CANDIDATS_H
#define CANDIDATS_H

#include <list>
using namespace std;

template <typename T>
class Candidats
{
public:
    // Constructor amb un llistat d'elements
    Candidats(const list<T>& elems) : elements(elems) {
        it = elements.begin();
    }

    // Retorna l'element actual
    T actual() const {
        return *it;
    }

    // Diu si s'ha arribat ja a l'ultim candidat
    bool fi() const {
        return it == elements.end();
    }

    // Passa l'apuntador al seguent candidat
    void seguent() {
        if (it != elements.end())
            ++it;
    }

private:
    list<T> elements;
    typename list<T>::iterator it;
};

#endif // CANDIDATS_H
