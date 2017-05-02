#include <iostream>
#include <sstream>
#include <string>

#ifndef COMPETENCE_H
#define COMPETENCE_H
#pragma once

//!
/*!
	Permet de contenir une compétence en mémoire.

	Une compétence est formée grâce à :
	- un nom (`skillName`)
	- un nombre de points de dégâts à appliquer (si ce nombre est négatif, la compétence permet de soigner une cible)
	- un coût en points de magie (si ce nombre est négatif, la compétence permet de régénerer des points de magie)

	NOTE : Par convention, une compétence qui contient un nombre de points de mana sera utilisée sur un joueur. Un monstre n'a pas de magie à gérer.
*/
class competence
{
	//! Nom de la compétence.
	std::string skillName;
	//! Coût en points de vie (si ce nombre est négatif, la compétence permet de soigner une cible)
	int skillDamage;
	//! Coût en points de magie (si ce nombre est négatif, la compétence permet de régénerer des points de magie)
	int skillManaCost;

public:
	//! Constructeur sans arguments.
	/*!
		En sortant de ce constructeur, la compétence aura :
		- skillName = "Inconnu"
		- skillDamage = 0
		- skillManaCost = 0
	*/
	competence();
	//! Constructeur permettant de créer une compétence pour un personnage.
	/*!
		Les compétences créées avec ce constructeur seront utilisées pour un personnage.
		La compétence aura donc comme données :
		- competence::skillName = skillName
		- competence::skillDamage = skillDamage
		- competence::skillManaCost = skillManaCost
		\param skillName Nom à assigner à la compétence
		\param skillDamage Nombre de points de vie à assigner à la compétence (si ce nombre est négatif, la compétence permet de soigner une cible)
		\param skillManaCost Nombre de points de magie à assigner à la compétence (si ce nombre est négatif, la compétence permet de régénerer des points de magie)
	*/
	competence(std::string skillName, int skillDamage, int skillManaCost);

	//! Constructeur permettant de créer une compétence pour un monstre.
	/*!
		Les compétences créées avec ce constructeur seront utilisées pour un monstre.
		La compétence aura donc comme données :
		- competence::skillName = skillName
		- competence::skillDamage = skillDamage
		\param skillName Nom à assigner à la compétence
		\param skillDamage Nombre de points de vie à assigner à la compétence (si ce nombre est négatif, la compétence permet de soigner une cible)
		\note Les compétences créées utilisant ce constructeur seront assignées à des monstres. Par convention, un monstre n'a pas à gérer de magie.
	*/
	competence(std::string skillName, int skillDamage);
	//! Destructeur de compétence.
	~competence();

	//! Fonction retournant le nom d'une compétence.
	/*!
		Est utilisée notemment pour l'affichage des possibilités du joueur pendant le combat contre un (des) monstre(s).
		\return Une string (`std::string`) contenant le nom.
	*/
	std::string getName();
	//! Fonction retournant la description d'une compétence.
	/*!
		Est utilisée notemment pour l'affichage des possibilités du joueur pendant le combat contre un (des) monstre(s).
		\return Une string (`std::string`) contenant la description.
	*/
	std::string getDescription();
	//! Fonction retournant le nombre de points de dégâts à appliquer à une cible.
	/*!
		Est utilisée notemment pour l'affichage des possibilités du joueur pendant le combat contre un (des) monstre(s).
		\return Un entier (`int`) contenant le nombre de points de dégâts à appliquer à une cible.
	*/
	int getDamage();
	//! Fonction retournant le nombre de points de magie à utiliser.
	/*!
		Est utilisée notemment pour l'affichage des possibilités du joueur pendant le combat contre un (des) monstre(s).
		\return Un entier (`int`) contenant le nombre de points de magie à utiliser.
	*/
	int getManaCost();

	//! Template permettant de retourner une string contenant un élément.
	/*!
		Template permettant de retourner une string (`std::string`) contenant un élément de la classe `T` en forme de string.
		\return Une string (`std::string`) rerésentant l'élément `T`.
	*/
	template<typename T> std::string toString(const T & valeur);

	//! Affichage d'une compétence
	/*!
		Affiche les éléments détaillés d'une compétence (nom, dégâts, coût).
		Si les dégâts sont négatifs, affiche "soins".
		Si le coût est négatif, affiche "gain".
	*/
	void afficher_detail();

	//! Conversion en string
	/*!
        Permet de convertir les caractéristiques d'une compétence en chaîne de caractère en vue de son écriture dans un fichier
		\return Un string correspondant à la compétence
	*/
	std::string competenceString(); //Convertit les carac. d'une compétence en une string formatée
};

#endif
