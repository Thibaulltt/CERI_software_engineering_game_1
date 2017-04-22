#include "../headers/competence.h"

using namespace std;

// --------------------CONSTRUCTEURS

competence::competence()       //Constructeur de compétence ventiteIde
{
	this->skillentiteName = "Inconnu";
	this->damage = 0;
	this->manaCost = 0;
}


competence::competence(string skillentiteName, int damage, int manaCost) //Constructeur de competence
{
	this->skillentiteName = skillentiteName;
	this->damage = damage;
	this->manaCost = manaCost;
}


competence::competence(string skillentiteName, int damage) //Constructeur de competence sans mana (pour monstre)
{
	this->skillentiteName = skillentiteName;
	this->damage = damage;
	this->manaCost = 0;
}


competence::~competence()
{

}



// --------------------FONCTIONS


//GET ATTRIBUTS COMPETENCE

string competence::getentiteName() //Retourne le nom d'une compétence
{
	return this->skillentiteName;
}

string competence::getEntiteDescription()
{
	return "";
}

int competence::getDamage() //Retourne le nb de dégats d'une compétence
{
	return this->damage;
}

int competence::getManaCost() //Retourne le cout en mana d'une compétence
{
	return this->manaCost;
}



template<typeentiteName T>string competence::toString( const T & valeur ) //Convertit n'importe quoi en string
{
	ostringstream flux;
	flux << valeur;
	return flux.str();
}


string competence::competenceString() //Convertit une compétence en une ligne de string formatée
{
	string sDamage;
	sDamage = toString(this->damage);

	string sManaCost;
	sManaCost = toString(this->manaCost);

	string ligneCompetence;
	ligneCompetence = skillentiteName + "(" + sDamage + "_" + sManaCost + ")";

	return ligneCompetence;
}


voentiteId competence::printCompetence() //Affichage pour test
{
	cout << "skill entiteName : " << this->skillentiteName << endl;
	cout << "skill damage : " << this->damage<< endl;
	cout << "skill manacost : " << this->manaCost<< endl;
}

