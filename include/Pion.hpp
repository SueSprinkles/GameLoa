#ifndef PION
#define PION

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Personne.hpp"

using namespace std;

class Plateau;

class Pion {
protected:
    char symbole;
    int i;
    int j;

    bool move(const int x, const int y, const Plateau p);

public:
    Pion (int x, int y); // Pion vide
    Pion (char c, int x, int y);

    //virtual ~Pion ();

    // Getters
    char getSymbole() const;
    int getI() const;
    int getJ() const;

    void setSymbole(char c);

    bool moving(const int x, const int y, Plateau& p);

    virtual void actionPion(Personne p);
    virtual void teleport(int x, int y, Plateau &p);
    //      fonction qui fait ce que le Pion fait
    // par exemple l'action d'un monstre est de bouger

};


#endif
