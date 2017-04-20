#include "monstre.h"

struct interface
{
    bool checkInput(int x); //Vérifie que l'user entre des entier
    competence createCompetence(); //Creer une competence
    competence createCompetenceMonstre(); //Créer une compétence pour monstre (sans mana)
    monstre createMonstre(); //Créer un monstre
    vector<competence> loadCompetenceFromFile(); //Récupérer les compétences d'un monstre dans le .txt

    monstre loadMonstreFromFile(); //Récupérer toutes les infos d'un monstre dans le .txt

};
