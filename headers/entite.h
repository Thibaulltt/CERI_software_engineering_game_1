#include <string>
#include <vector>
#include "competence.h"

#ifndef ENTITE_H
#define ENTITE_H


class entite
{
protected:
	std::string entiteId;
	std::string entiteName;
	std::string entiteDescription;
	int entiteHpMax;
	int entiteHpCurrent;
	int entiteManaMax;
	int entiteManaCurrent;
	int entiteSpeed;
	bool entiteAlive;
	std::vector<competence> entiteSkillVect;

public:
	//! Constructeur ventiteIde
	/*
		Crée un entite ventiteIde.
		\warning Le entite sera ventiteIde. Cela signifie qu'il ne sera pas utilisable pour le jeu, sa vie étant égale à 0
		\post Le entite crée aura les paramètres suivants:
		- entiteName = "Inconnu"
		- entiteHpMax = 0
		- entiteHpCurrent = 0
		- entiteSpeed = 0
		- entiteAlive = true (sera changé immédiatement en false)
		- entiteSkillVect = <vecteur ventiteIde>
	*/
	entite();

	//! Constructeur avec tout
	/*!
		\param entiteId L'entiteIdentifiant de l'entite
		\param entiteName Le nom de l'entite
		\param entiteHpMax Les points de vie max de l'entite
		\param entiteSpeed La vitesse de l'entite
		\param entiteManaMax Les points de mana max de l'entite
		\param entiteDescription La entiteDescription de l'entite
		\param allSkills Un vecteur (std::vector) contenant toutes les compétences de cette entite.
	*/
	entite(std::string entiteId, std::string entiteName, int entiteHpMax, int entiteSpeed, int entiteManaMax,std::string entiteDescription, std::vector<competence> allSkills);




	template<typeentiteName T> std::string toString(const T & valeur); // Conversion de n'importe quoi en string

	//!Getter pour l'entiteId.
	std::string getEntiteId();

	//! Getter pour le nom.
	std::string getentiteName();

	//! Getter pour la entiteDescription.
	std::string getEntiteDescription();

	//! Getter pour le nombre de points de vie max.
	int getEntiteHpMax();

	//! Getter pour le nombre de points de vie actuels.
	int getEntiteHpCurrent();

	//! Getter pour la vitesse d'attaque du entite.
	int getEntiteSpeed();

	//! Getter qui permet de savoir si le entite est en vie.
	bool getEntiteAlive();

	//! Getter pour la mana maximum de l'entite
	int getEntiteManaMax();

	//! Getter pour la mana actuelle de l'entite
	int getEntiteManaCurrent();

	//! Getter qui renvoie un vecteur (std::vector) de compétences.
	std::vector<competence> getEntiteSkillVect();

	//! Retour d'une string représentant un entite.
	/*!
		Convertit un objet entite en une ligne de string.
		\post La string contiendra les infos dans cet ordre :
		- entiteIdentifiant (type <code>m\<entier></code>)
		- nom du entite
		- nombre de points de vie
		- vitesse d'attaque
		- toutes les compétences , séparées par des <code>:</code>
	*/

	//! Retourne le nombre de lignes d'un fichier.
	/*!
		Compte le nb de lignes du fichier pour créer l'entiteIdentifiant unique d'un entite. L'entiteIdentifiant sera <code> nbLignes + 1 </code>
		\return Un entier représentant le nombre de lignes.
		\param nomFichier Une string (std::string) qui sera le nom du fichier à ouvrir.
	*/
	int nbLigneFichier(std::string nomFichier);

	std::string entiteString(std::string lettreEntite, std::string nomFichier);

	//! Permet d'écrire le entite dans un fichier de sauvegarde
	voentiteId saveInFile(std::string lettreEntite, std::string nomFichier);

	//! Pour tester
	voentiteId printEntite();

	//! Enlève x points de vie au entite.
	/*!
		Cette fonction permet d'enlever des points de vie. Elle permet aussi de savoir si un entite est en vie (ptsVie < 0) ou si il est mort.
		\return Un booléen qui est égal à <code>true</code> si le entite est mort, <code>false</code> sinon.
	*/
	bool enleverVie(int degats);

	//! Enlève x points de mana au entite.
	/*!
		Cette fonction ne sert à rien, à part ne pas faire bugger les autres.
		\return Un booléen vérifiant la capacité à dépenser la mana.
	*/
	bool enleverMana(int manaCost);


};

#endif // ENTITE_H
