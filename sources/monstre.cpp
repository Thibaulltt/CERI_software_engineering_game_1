#include "monstre.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


// --------------------CONSTRUCTEURS

monstre::monstre()                                                 //Constructeur vide
{
    this->name = "Inconnu";
    this->hpMax = 0;
    this->hpCurrent = hpMax;
    this->speed = 0;
    this->alive = true;
    vector<competence> skillVect;
}


monstre::monstre(string name, int hpMax, int speed)           //Constructeur avec arguments de statut du monstre
{
    this->name = name;
    this->hpMax = hpMax;
    this->hpCurrent = this->hpMax;
    this->speed = speed;
    this->alive = true;
    vector<competence> skillVect;
}


monstre::monstre(string name, int hpMax, int speed, vector<competence> allSkills)               //Constructeur avec arguments de statut du monstre
{
    this->name = name;
    this->hpMax = hpMax;
    this->hpCurrent = this->hpMax;
    this->speed = speed;
    this->alive = true;
    this->skillVect = allSkills;
}


//----------------------FONCTIONS


template<typename T>string monstre::toString( const T & valeur ) //Conversion de n'importe quoi en string
{
    ostringstream flux;
    flux << valeur;
    return flux.str();
}


int monstre::nbLigneFichier() //Compte le nb de ligne du fichier pour créer l'identifiant unique d'un monstre
{
    ifstream fichier("fichierMonstre.txt"); //Ouverture en mode lecture
    int nbLigne = 0;
    if(fichier)
    {
        string ligne="";

        while(getline(fichier, ligne)) //Stockage de chaque ligne du fichier
        {
             nbLigne++;
        }
        fichier.close(); //On ferme le fichier
    }

    else
    {
        cerr << "Impossible d'ouvrir le fichier." << endl;
    }

    return nbLigne;

}


string monstre::monstreString() //Convertit toutes les caracs. d'un monstre en string
{
    string ligneFichier;

    int nbMonstre = this->nbLigneFichier();
    string sNbMonstre;
    sNbMonstre = toString(nbMonstre);

    string ID;
    ID = "m" + sNbMonstre;

    string sHpMax;
    sHpMax = toString(this->hpMax);

    string sSpeed;
    sSpeed = toString(this->speed);

    string allSkill="";
    for (int i=0 ; i< skillVect.size() ; i++) //Conversion de toutes les compétences en une ligne de string
    {
        allSkill += skillVect[i].competenceString() + ":";
    }

    ligneFichier = ID + "/" +this->name + "/" + sHpMax + "/" + sSpeed + "/" + allSkill + '\n'; //Création de la ligne compléte

    return ligneFichier;
}


void monstre::saveInFile() //Ecrit les carac d'un monstre dans un fichier
{
    ofstream fichierMonstre("fichierMonstre.txt", ios::out | ios::app); // Ouverture du fichier en écriture, avec curseur en fin de fichier.

    string monstreLigne = this->monstreString();

    if(fichierMonstre) //Vérification ouverture du fichier
    {
        fichierMonstre << monstreLigne; //Ecriture de la ligne
        fichierMonstre.close();
    }

    else
    {
        cerr << "Impossible d'ouvrir le fichier." << endl;
    }
}


bool monstre::enleverVie(int degats)
{
    this->hpCurrent-=degats;

    if(this->hpCurrent <= 0)
    {
        return true; //Si mort, return true
    }
    return false;
}



void monstre::printMonstre()
{
    cout << "nom : " << this->name<< endl;
    cout << "hp max : " << this->hpMax<< endl;
    cout << "speed : " << this->speed<< endl;

    for (int i=0 ; i<3 ; i++)
    {
        this->skillVect[i].printCompetence();
    }

    cout << endl;
}
