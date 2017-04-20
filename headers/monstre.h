#include <string>
#include <vector>
#include "competence.h"

#ifndef MONSTRE_H
#define MONSTRE_H

class monstre
{
protected:
    std::string name;
    int hpMax;
    int hpCurrent;
    int speed;
    bool alive;
    std::vector<competence> skillVect;

public:

    monstre(); //Constructeut vide
    monstre(std::string name, int hpMax, int speed); //Constructeur avec carac d'un monstre
    monstre (std::string name, int hpMax, int speed, std::vector<competence> allSkills); //Constructeur avec les compétences

    template<typename T> std::string toString(const T & valeur); // Conversion de n'importe quoi en string

    std::string getName();
    int getHpMax();
    int getHpCurrent();
    int getSpeed();
    bool getAlive();
    std::vector<competence> getSkillVect();

    std::string monstreString(); //Convertit un objet monstre en une ligne de string
    int nbLigneFichier(std::string nomFichier); //Compte le nb de ligne du fichier pour créer l'identifiant unique d'un monstre
    void saveInFile(); //Permet d'écrire le monstre dans un fichier de sauvegarde
    void printMonstre(); // Pour tester

    bool enleverVie(int degats); //Permet d'enlever eds points de vie, faire mourir un montre. Retourne true si monstre mort.




};


#endif // MONSTRE_H
