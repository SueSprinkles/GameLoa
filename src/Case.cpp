#include "Case.hpp"

// Constructeurs
Case::Case(): pion(VIDE){}
Case::Case(Pion p): pion(p) {}

// Getter
Pion Case::getPion() const
{
    return pion;
}

// add/remove Pion
void Case::addPion(const Pion p)
{
    pion = p;
}

void Case::removePion()
{
    pion = VIDE;
}

// Affichage
ostream& operator<<(ostream& out, Case c)
{
    out << c.pion.getSymbole();
    return out;
}
