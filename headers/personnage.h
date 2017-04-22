#include "../headers/monstre.h"

#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#pragma once

class personnage : public monstre //Classe personnage héritant de la classe monstre
{
	int manaMax;
	int manaCurrent;
	std::string description;

public:

	//! Constructeur vide
	/*!
		Le personnage créé aura 0 de mana, et n'aura aucune description. Mais il sera crée.
	*/
	personnage():monstre()
	{
		this->manaMax=0;
		this->manaCurrent=this->manaMax;
		this->description="Inconnu";
	};

	//! Constructeur avec caractéristiques
	personnage(std::string name, int hpMax, int speed, int manaMax, std::string description):monstre(name, hpMax, speed)
	{
		this->manaMax=manaMax;
		this->manaCurrent=this->manaMax;
		this->description=description;
	};

	//! Constructeur avec caractéristiques + vecteur de compétences
	personnage(std::string name, int hpMax, int speed, int manaMax, std::string description, std::vector<competence> allSkills):monstre(name, hpMax, speed, allSkills)
	{
		this->manaMax=manaMax;
		this->manaCurrent=this->manaMax;
		this->description=description;
	};

	//! Getter pour la mana maximum du personnage
	int getManaMax();
	//! Getter pour la mana actuelle du personnage
	int getManaCurrent();
	//! Getter pour la description du personnage
	std::string getDescription();

	//! Convertit toutes les caracs. d'un personnage en string
	std::string personnageString();
	//! Ecrit toutes les carac. d'un perso dans un fichier
	void savePersoInFile();

	//! Return true si le personnage a toujours du mana
	bool enleverMana(int manaCost);

	//! Fonction de test
	void printPersonnage();
};

#endif
