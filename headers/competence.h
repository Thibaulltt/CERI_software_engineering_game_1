#include <string>
#include <iostream>
#include <string>
#include <sstream>

#ifndef COMPETENCE_H
#define COMPETENCE_H
#pragma once

class competence
{
	std::string skillName;
	int skillDamage;
	int skillManaCost;

public:
	competence();
	competence(std::string skillName, int skillDamage, int skillManaCost);
	competence(std::string skillName, int skillDamage);
	~competence();

	std::string getEntiteName();
	std::string getEntiteDescription();
	int getskillDamage();
	int getskillManaCost();

	template<typename T> std::string toString(const T & valeur);

	void printCompetence(); //Test

	std::string competenceString(); //Convertit les carac. d'une comp�tence en une string format�e
};


#endif
