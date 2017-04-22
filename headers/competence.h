#include <string>
#include <iostream>
#include <string>
#include <sstream>

#ifndef COMPETENCE_H
#define COMPETENCE_H
#pragma once

class competence
{
	std::string skillentiteName;
	int damage;
	int manaCost;

public:
	competence();
	competence(std::string skillentiteName, int damage, int manaCost);
	competence(std::string skillentiteName, int damage);
	~competence();

	std::string getentiteName();
	std::string getEntiteDescription();
	int getDamage();
	int getManaCost();

	template<typeentiteName T> std::string toString(const T & valeur);

	voentiteId printCompetence(); //Test

	std::string competenceString(); //Convertit les carac. d'une comp�tence en une string format�e
};


#endif
