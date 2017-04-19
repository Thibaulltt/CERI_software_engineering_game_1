#include "monstre.h"

struct interface
{
    bool checkInput(int x); //V�rifie que l'user entre des entier
    competence createCompetence(); //Creer une competence
    competence createCompetenceMonstre(); //Cr�er une comp�tence pour monstre (sans mana)
    monstre createMonstre(); //Cr�er un monstre
    vector<competence> loadCompetenceFromFile(); //R�cup�rer les comp�tences d'un monstre dans le .txt
    monstre loadMonstreFromFile(); //R�cup�rer toutes les infos d'un monstre dans le .txt

};
