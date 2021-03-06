#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

// affiche un plateau de char
//      plus tard : on aura un plateau de case donc on utilisera la fonction d'affichage de Plateau
void afficher(vector<vector<char>> v);


// crée un fichier plateau à partir des entrées consoles
void newPlateau(string str);
void newFile(vector<vector<char>> v, string str);
void newFile(int t, string str);
char parse(int n, bool *p, bool *d);


int main(int argc, char const *argv[])
{
    cout << "Creation !" << endl << endl;

    string chemin = "assets/boards/";
    string nom;
    if (argc >=2)
        nom = argv[1];
    else
        nom = "testCreation";

    chemin += nom;

    string fichier;
    int i = 1;
    bool continuer = true;
    char c;

    char* name = &chemin[0];
    mkdir(name, 0777);

    int chargeur;
    cout << "Combien de chargeur aura le joueur aura de chargeur au démarrage ?" << endl;
    cin >> chargeur;
    string set = chemin + "/setting";
    newFile(chargeur, set);

    while (continuer)
    {
        cout << "Creation d'un nouveau fichier : " << endl << endl;
        fichier = chemin + "/" + nom + to_string(i) + ".board";
        newPlateau(fichier);
        i++;
        cout << endl;
        cout << "Voulez vous faire un nouveau plateau ? (o/n) ";
        cin >> c;
        continuer = (c == 'o');
    }

    return 0;
}


void afficher(vector<vector<char>> v)
{
    cout << endl;
    for (size_t i = 0; i < v.size(); i++)
    {
        for (size_t j = 0; j < v[i].size(); j++)
            cout << v[i][j];
        cout << endl;
    }
    cout << endl;
}


void newPlateau(string str)
{
    int x;
    int y;
    cout << "Quelles dimensions voulez vous pour le nouveau plateau ?" << endl;
    cout << "largeur = " ;
    cin >> x;
    cout << "hauteur = ";
    cin >> y;
    cout << endl;

    // creation des fondations avec pose des murs porteurs
    vector<vector<char>> p;
    for (int i = 0; i < y; i++)
    {
        vector<char> v;
        for (int j = 0; j < x; j++)
        {
            if (i== 0 || i== (y-1) || j==0 || j==(x-1) )
            v.push_back('X');
            else
            v.push_back(' ');
        }
        p.push_back(v);
    }
    afficher(p);

    bool continuer = true;
    int choix;
    int i;
    int j;
    char c;
    // ajouter le joueur :
    bool isOK = false;
    while (!isOK)
    {
        cout << "Ou voulez-vous mettre le Joueur ?" << endl;
        cout << "abscisse (0 à "<< x-1 <<") = ";
        cin >> i;
        cout << "ordonnée (0 à "<< y-1 <<") = ";
        cin >> j;
        isOK = (i>=0 && i<x && j>=0 && j<y);
    }
    p[j][i] = 'J';

    afficher(p);

    // décoration intérieur
    bool porte = false;
    bool diam = false;
    cout << "ahahahha" << endl;
    while (continuer || !(porte) || !(diam))
    {
        if(!continuer)
            cout << "Mettez au moins une porte et un diamant !"<< endl << endl;
        cout << "Que voulez vous ajouter ? (Entrez un nombre)" << endl;
        cout << "1- une porte" << endl;
        cout << "2- un mur" << endl;
        cout << "3- un diamant (d'innocence)" << endl;
        cout << "4- un chargeur" << endl;
        cout << "5- un monstre" << endl;
        cout << "6- un monstre pas très intelligent" << endl;
        cout << "7- un monstre aléatoire" << endl;
        cin >> choix;
        char symbole = parse(choix, &porte, &diam);

        if (choix <=7 && choix >= 1)
        {
            cout << "À quel endroit ?" << endl;
            cout << "abscisse (0 à "<< x-1 <<") = ";
            cin >> i;
            if (i>= 0 && i<x)
            {
                cout << "ordonnée (0 à "<< y-1 <<") = ";
                cin >> j;
                if (j>=0 && j<y)
                {
                    p[j][i] = symbole;

                    afficher(p);
                    cout << "Voulez vous continuer de modifier le plateau ? (o/n) ";
                    cin >> c;
                    continuer = (c == 'o');
                }
            }
        }
    }
    newFile(p, str);
}

char parse(int n, bool *p, bool *d)
{
    switch (n) {
        case 1:
            *p = true;
            return '-';
        case 2: return 'X';
        case 3:
            *d = true;
            return '$';
        case 4: return '*';
        case 5: return 'm';
        case 6: return 'n';
        case 7: return 'M';
        default: return ' ';
    }
}

void newFile(vector<vector<char>> v, string str)
{
    ofstream fichier (str);

    if (fichier)
    {
        for (size_t i = 0; i < v.size(); i++)
        {
            for (size_t j = 0; j < v[i].size(); j++)
                fichier << v[i][j];
            fichier << endl;
        }
    }
    else
        cout << "erreur création fichier plateau" << endl;
}
void newFile(int t, string str)
{
    ofstream fichier(str);
    if (fichier)
    {
        fichier << '0';
        fichier << '\n';
        fichier << to_string(t);
        fichier << '\n';
    }
    else
        cout << "erreur création fichier setting" << endl;

}
