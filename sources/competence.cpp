#include "../headers/competence.h"

using namespace std;

// --------------------CONSTRUCTEURS

competence::competence()       //Constructeur de compétence vide
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

string competence::getName() //Retourne le nom d'une compétence
{
	return this->skillName;
}

string competence::getDescription()
{
	return "";
}

int competence::getDamage() //Retourne le nb de dégats d'une compétence
{
	return this->skillDamage;
}

int competence::getManaCost() //Retourne le cout en mana d'une compétence
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

void competence::afficher_detail()
{
	cout << this->skillName;

	if (this->skillDamage < 0)
	{
		cout << ", soins: " << -1 * (this->skillDamage);
	}
	else
	{
		cout << ", dégâts: " << this->skillDamage;
	}

	if (this->skillManaCost < 0)
	{
		cout << ", gain de mana: " << -1 * (this->skillManaCost) << endl;
	}
	else
	{
		cout << ", coût en mana: " << this->skillManaCost << endl;
	}
}
