#include "../headers/competence.h"

using namespace std;

// --------------------CONSTRUCTEURS

competence::competence()       //Constructeur de compétence ventiteIde
{
	this->skillName = "Inconnu";
	this->skillDamage = 0;
	this->skillManaCost = 0;
}


competence::competence(string skillName, int skillDamage, int skillManaCost) //Constructeur de competence
{
	this->skillName = skillName;
	this->skillDamage = skillDamage;
	this->skillManaCost = skillManaCost;
}


competence::competence(string skillName, int skillDamage) //Constructeur de competence sans mana (pour monstre)
{
	this->skillName = skillName;
	this->skillDamage = skillDamage;
	this->skillManaCost = 0;
}


competence::~competence()
{

}



// --------------------FONCTIONS


//GET ATTRIBUTS COMPETENCE

string competence::getEntiteName() //Retourne le nom d'une compétence
{
	return this->skillName;
}

string competence::getEntiteDescription()
{
	return "";
}

int competence::getskillDamage() //Retourne le nb de dégats d'une compétence
{
	return this->skillDamage;
}

int competence::getskillManaCost() //Retourne le cout en mana d'une compétence
{
	return this->skillManaCost;
}



template<typename T>string competence::toString( const T & valeur ) //Convertit n'importe quoi en string
{
	ostringstream flux;
	flux << valeur;
	return flux.str();
}


string competence::competenceString() //Convertit une compétence en une ligne de string formatée
{
	string sskillDamage;
	sskillDamage = toString(this->skillDamage);

	string sskillManaCost;
	sskillManaCost = toString(this->skillManaCost);

	string ligneCompetence;
	ligneCompetence = skillName + "(" + sskillDamage + "_" + sskillManaCost + ")";

	return ligneCompetence;
}


void competence::printCompetence() //Affichage pour test
{
	cout << "skill entiteName : " << this->skillName << endl;
	cout << "skill skillDamage : " << this->skillDamage<< endl;
	cout << "skill skillManaCost : " << this->skillManaCost<< endl;
}

