#include <string>
#include <vector>
#include "competence.h"

#ifndef MONSTRE_H
#define MONSTRE_H
#pragma once

class monstre
{
protected:
	std::string id;
	std::string name;
	int hpMax;
	int hpCurrent;
	int manaCurrent;
	int speed;
	bool alive;
	std::vector<competence> skillVect;

public:
	//! Constructeur vide
	/*
		Crée un monstre vide.
		\warning Le monstre sera vide. Cela signifie qu'il ne sera pas utilisable pour le jeu, sa vie étant égale à 0
		\post Le monstre crée aura les paramètres suivants:
		- name = "Inconnu"
		- hpMax = 0
		- hpCurrent = 0
		- speed = 0
		- alive = true (sera changé immédiatement en false)
		- skillVect = <vecteur vide>
	*/
	monstre();

	//! Constructeur avec carac d'un monstre
	/*!
		Constructeur assignant tout, sauf les compétences, qui ne seront pas rajoutées (pas de fonctions).
		\param name Le nom du monstre.
		\param hpMax Le nombre de points de vie max du monstre.
		\param speed La vitesse d'attaque du monstre.
	*/
	monstre(std::string name, int hpMax, int speed);

	//! Constructeur avec les compétences
	/*!
		\param name Le nom du monstre.
		\param hpMax Le nombre de points de vie max du monstre.
		\param speed La vitesse d'attaque du monstre.
		\param allSkills Un vecteur (std::vector) contenant toutes les compétences de ce monstre.
	*/
	monstre (std::string name, int hpMax, int speed, std::vector<competence> allSkills);

	template<typename T> std::string toString(const T & valeur); // Conversion de n'importe quoi en string

	//!Getter pour l'ID.
	std::string getId();

	//! Getter pour le nom.
	std::string getName();

	//! Getter pour le nombre de points de vie max.
	int getHpMax();

	//! Getter pour le nombre de points de vie actuels.
	int getHpCurrent();

	//! Getter pour la vitesse d'attaque du monstre.
	int getSpeed();

	//! Getter qui permet de savoir si le monstre est en vie.
	bool getAlive();

	//! Getter qui renvoie un vecteur (std::vector) de compétences.
	std::vector<competence> getSkillVect();

	//! Retour d'une string représentant un monstre.
	/*!
		Convertit un objet monstre en une ligne de string.
		\post La string contiendra les infos dans cet ordre :
		- identifiant (type <code>m\<entier></code>)
		- nom du monstre
		- nombre de points de vie
		- vitesse d'attaque
		- toutes les compétences , séparées par des <code>:</code>
	*/
	std::string monstreString();

	//! Retourne le nombre de lignes d'un fichier.
	/*!
		Compte le nb de lignes du fichier pour créer l'identifiant unique d'un monstre. L'identifiant sera <code> nbLignes + 1 </code>
		\return Un entier représentant le nombre de lignes.
		\param nomFichier Une string (std::string) qui sera le nom du fichier à ouvrir.
	*/
	int nbLigneFichier(std::string nomFichier);

	//! Permet d'écrire le monstre dans un fichier de sauvegarde
	void saveInFile();

	//! Pour tester
	void printMonstre();

	//! Enlève x points de vie au monstre.
	/*!
		Cette fonction permet d'enlever des points de vie. Elle permet aussi de savoir si un monstre est en vie (ptsVie < 0) ou si il est mort.
		\return Un booléen qui est égal à <code>true</code> si le monstre est mort, <code>false</code> sinon.
	*/
	bool enleverVie(int degats);

	//! Enlève x points de mana au monstre.
	/*!
		Cette fonction ne sert à rien, à part ne pas faire bugger les autres.
		\return Un booléen vérifiant la capacité à dépenser la mana.
	*/
	bool enleverMana(int manaCost);
};


#endif // MONSTRE_H
