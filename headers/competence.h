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
	int damage;
	int manaCost;

public:
	competence();
	competence(std::string skillName, int damage, int manaCost);
	competence(std::string skillName, int damage);
	~competence();

	std::string getName();
	std::string getDescription();
	int getDamage();
	int getManaCost();

	template<typename T> std::string toString(const T & valeur);

	void printCompetence(); //Test

	std::string competenceString(); //Convertit les carac. d'une comp�tence en une string format�e
};


#endif
