#include "../headers/fonctionsjeu.h"
#include "../headers/carte.h"
#include "../headers/interface.h"
#include "../headers/io.h"
#include <algorithm>
#include <iostream>

using namespace io;
using namespace std;

int main()
{
	//Phase préparation partie
	jeu a;
	a.demarrer_jeu();

		//Choix personnage
	vector<personnage> tous_persos;
	tous_persos = loadAllPersonnageFromFile();

	personnage perso_jeu = personnage();
	perso_jeu = choix_unique_element(tous_persos);

		//Choix carte
	vector<Carte> toutes_cartes;
	Carte map_jeu = Carte();
//	toutes_cartes = map_jeu.chargement();	//Core dump pour l'instant (22/04, 01:04)
//	cout << "test taille vecteur map: " << toutes_cartes.size();
//	map_jeu = choix_unique_element(toutes_cartes);

		//Chargement monstres
	vector<monstre> monstres_jeu;
	vector<monstre>::iterator itm;

	monstres_jeu = loadAllMonstreFromFile();

//	for (itm = monstres_jeu.begin(); itm != monstres_jeu.end(); itm++)
//	{
//        itm -> printMonstre();
//	}

		//Combat (création pile, tri acteurs, empilage, application compétences, dépilage).

///Pas convaincu par la pile. Le problème vient du dépilage. Lorsqu'un acteur a joué, on le dépile.
///Mais comment appliquer à l'acteur dépilé les effets de l'acteur suivant qui le cible, puisqu'il n'est plus dans la pile?
///Peut-être passer à un stockage + tri dans un vecteur (ce qui est déjà fait), avec un parcours simple.
///Permet du coup d'économiser l'utilisation d'une pile.
	stack<monstre> pile_combat;

	vector<monstre> vect_entite;
	vector<monstre>::iterator ite;

	vect_entite.push_back(perso_jeu);
	vect_entite.push_back(monstres_jeu[0]);

	sort(vect_entite.begin(), vect_entite.end(), sort_speed);

	while (1)
	{
		for (ite = vect_entite.begin(); ite != vect_entite.end(); ite++)
		{
			pile_combat.push(* ite);
		}

		monstre current = pile_combat.top();

		competence comp_util;

		if (current.getId().substr(1,1) == "p")
		{
			choix:
			comp_util = choix_unique_element(current.getSkillVect());
		}
		else
		{
			comp_util = current.getSkillVect()[rand()%current.getSkillVect().size()];
		}

		if (current.enleverMana(comp_util.getManaCost()))
		{

		}
		else
		{
			cout << "Vous n'avez pas assez de mana pour utiliser cette compétence!";
			cout << "Choisissez-en une autre!";
			goto choix;
		}
	}



	/*
	Todo:
	Gérer l'assignation des monstres à la carte (choix aléatoire dans le vecteur pour chaque case contenant un monstre).
	Afficher la carte et lancer la partie.
	Se déplacer
	Combattre
	Mourir
	*/

	return 0;
}
