#include "../headers/entite.h"

#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#pragma once
//! Classe personnage héritant de la classe entité
class personnage : public entite
{

public:

	static int nbElemProt;

	//! Constructeur vide
	/*!
		Le personnage créé aura 0 de mana, et n'aura aucune description. Mais il sera créé.
	*/
	personnage();

	//! Constructeur avec arguments
	/*!
		Permet de créer un personnage en affectant toutes ses caractéristiques.
		\param entiteId L'identifiant du personnage
		\param entiteName Le nom du personnage
		\param entiteHpMax Les points de vie max du personnage
		\param entiteSpeed La vitesse du personnage
		\param entiteManaMax Les points de mana max du personnage
		\param entiteDescription La description du personnage
		\param allSkills Un vecteur (std::vector) contenant toutes les compétences de ce personnage.
	*/
	personnage(std::string entiteId, std::string entiteName, int entiteHpMax, int entiteSpeed, int entiteManaMax, std::string entiteDescription, std::vector<competence> allSkills) : entite(entiteId, entiteName, entiteHpMax, entiteSpeed, entiteManaMax, entiteDescription, allSkills)
	{
	};

	//! Fonction de test
	void printPersonnage();
};

#endif
