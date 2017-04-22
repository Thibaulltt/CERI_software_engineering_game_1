#include "../headers/entite.h"

#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#pragma once

class personnage : public entite //Classe personnage héritant de la classe monstre
{

public:

	//! Constructeur ventiteIde
	/*!
		Le personnage créé aura 0 de mana, et n'aura aucune entiteDescription. Mais il sera crée.
	*/
	personnage():entite()
	{
	};


	personnage(std::string entiteId, std::string entiteName, int entiteHpMax, int entiteSpeed, int entiteManaMax, std::string entiteDescription, std::vector<competence> allSkills) : entite(entiteId, entiteName, entiteHpMax, entiteSpeed, entiteManaMax, entiteDescription, allSkills )
	{
	};

	//! Fonction de test
	void printPersonnage();
};

#endif
