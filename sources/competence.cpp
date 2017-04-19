#include "competence.h"


// --------------------CONSTRUCTEURS

competence::competence()       //Constructeur de compétence vide
{
    this->skillName = "Inconnu";
    this->damage = 0;
    this->manaCost = 0;
}


competence::competence(string skillName, int damage, int manaCost) //Constructeur de competence
{
    this->skillName = skillName;
    this->damage = damage;
    this->manaCost = manaCost;
}


competence::competence(string skillName, int damage) //Constructeur de competence sans mana (pour monstre)
{
    this->skillName = skillName;
    this->damage = damage;
    this->manaCost = 0;
}



// --------------------FONCTIONS

template<typename T>string competence::toString( const T & valeur )
{
    ostringstream flux;
    flux << valeur;
    return flux.str();
}


void competence::printCompetence()
{
        cout << "skill name : " << this->skillName << endl;
        cout << "skill damage : " << this->damage<< endl;
        cout << "skill manacost : " << this->manaCost<< endl;
}


string competence::competenceString()
{
    string sDamage;
    sDamage = toString(this->damage);

    string sManaCost;
    sManaCost = toString(this->manaCost);

    string ligneCompetence;
    ligneCompetence = skillName + "(" + sDamage + ")";

    return ligneCompetence;
}
