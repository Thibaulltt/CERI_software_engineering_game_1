#include "../headers/monstre.h"

#ifndef PERSONNAGE_H
#define PERSONNAGE_H

class personnage : public monstre //Classe personnage héritant de la classe monstre
{
    int manaMax;
    int manaCurrent;
    std::string description;

public:
    //Constructeur vide
    personnage():monstre()
    {
        this->manaMax=0;
        this->manaCurrent=this->manaMax;
        this->description="Inconnu";
    };

    //Constructeur avec caractéristiques
    personnage(std::string name, int hpMax, int speed, int manaMax, std::string description):monstre(name, hpMax, speed)
    {
        this->manaMax=manaMax;
        this->manaCurrent=this->manaMax;
        this->description=description;
    };

    //Constructeur avec caractéristiques + vecteur de compétences
    personnage(std::string name, int hpMax, int speed, int manaMax, std::string description, std::vector<competence> allSkills):monstre(name, hpMax, speed, allSkills)
    {
        this->manaMax=manaMax;
        this->manaCurrent=this->manaMax;
        this->description=description;
    };


   int getManaMax();
   int getManaCurrent();
   std::string getDescription();


    std::string personnageString(); //Convertit toutes les caracs. d'un personnage en string
    void savePersoInFile(); //Ecrit toutes les carac. d'un perso dans un fichier

    bool enleverMana(int manaCost); //Return true si le personnage a toujours du mana

    void printPersonnage(); //Pour test



};

#endif
