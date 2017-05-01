#include "../headers/entite.h"

#ifndef MONSTRE_H
#define MONSTRE_H
#pragma once

//! Classe créant un monstre en mémoire. hérite des propriétés ainsi que des attributs de la classe entite
class monstre : public entite
{

public:

	static int nbElemProt;

	//! Constructeur vide
	/*!
		Crée un monstre vide.
		\warning Le monstre sera vide. Cela signifie qu'il ne sera pas utilisable pour le jeu, sa vie étant égale à 0
		\post Le monstre crée aura les paramètres suivants:
		- entiteName = "Inconnu"
		- entiteHpMax = 0
		- entiteHpCurrent = 0
		- entiteSpeed = 0
		- entiteAlive = true (sera changé immédiatement en false)
		- entiteSkillVect = <vecteur vide>
	*/
	monstre();


	//! Constructeur avec tout
	/*!
		\param entiteId L'identifiant du monstre
		\param entiteName Le nom du monstre
		\param entiteHpMax Les points de vie max du monstre
		\param entiteSpeed La vitesse du monstre
		\param entiteManaMax Les points de mana max du monstre
		\param entiteDescription La description du monstre
		\param allSkills Un vecteur (std::vector) contenant toutes les compétences de ce monstre.
	*/
	monstre(std::string entiteId, std::string entiteName, int entiteHpMax, int entiteSpeed, int entiteManaMax, std::string entiteDescription, std::vector<competence> allSkills) : entite(entiteId, entiteName, entiteHpMax, entiteSpeed, entiteManaMax, entiteDescription, allSkills){};


	//! Pour tester
	void printMonstre();

};

#endif // MONSTRE_H
