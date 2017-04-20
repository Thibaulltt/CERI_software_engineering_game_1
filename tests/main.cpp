#include "../headers/fonctionsjeu.h"
#include "../headers/carte.h"
#include "../headers/competence.h"
#include "../headers/interface.h"
#include "../headers/monstre.h"
#include "../headers/personnage.h"
#include "../headers/io.h"
#include <iostream>

using namespace io;
using namespace std;

int main()
{
    //Phase préparation partie
	jeu a;
	a.demarrer_jeu();

        //Choix personnage
    interface inter;
    vector<personnage> tous_persos;
    tous_persos = inter.loadAllPersonnageFromFile();

    personnage perso_jeu = personnage();
    perso_jeu = choix_unique_element(tous_persos, true);

        //Choix carte
    Carte map_jeu(8, "map_1");
    Carte map_jeu2(10, "map_2");
    Carte map_jeu3(10, "map_3");

    vector<Carte> vect_map;

    vect_map.push_back(map_jeu);
    vect_map.push_back(map_jeu2);
    vect_map.push_back(map_jeu3);

    Carte carte_jeu = Carte();
    carte_jeu = choix_unique_element(vect_map, true);

        //Chargement monstres
    vector<monstre> monstres_jeu;

    monstres_jeu = inter.loadAllMonstreFromFile();

    /*
    Todo:
    Gérer l'assignation des monstres à la carte (choix aléatoire dans le vecteur pour chaque case contenant un monstre).
    Afficher la carte et lancer la partie.
    Se déplacer
    Combattre
    Mourir
    */

	return 0;
}
