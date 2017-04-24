#include <iostream>	// à remplacer avec notre librairie I/O plus tard
#include <vector>
#include "../headers/carte.h"
#include "../headers/fonctionsjeu.h"

using namespace std;

jeu::jeu()
{
//	jeu_perso = new personnage();		// À COMPLÉTER UNE FOIS QUE CLASSE PERSO FINIE
//	jeu_carte = new Carte();			// À COMPLÉTER UNE FOIS QUE CLASSE CARTE FINIE
//	jeu_nombre_monstre = 0;				// À COMPLÉTER UNE FOIS QUE CLASSE CARTE FINIE
}

jeu::~jeu()
{}

Carte jeu::getCarte()
{
	return jeu_carte;
}

personnage jeu::getPerso()
{
	return jeu_perso;
}

vector<monstre> jeu::getMonstres()
{
	return jeu_monstres;
}

int jeu::getNbMonstres()
{
	return jeu_nombre_monstres;
}

void jeu::preparation_partie()
{
	bienvenue();

		//Choix personnage
	vector<personnage> tous_persos;							//Vecteur personnages
	personnage pers;										//Dummy identification type template
	string nom_file = "fichierPersonnage.txt";				//Nom fichier source personnages
	tous_persos = loadAllEntiteFromFile(pers, nom_file);	//Remplissage vecteur personnages depuis fichier
	jeu_perso = choix_unique_element(tous_persos);			//Choix + assignation personnage partie

		//Choix carte
	vector<Carte> toutes_cartes;							//Vecteur cartes
	nom_file = "fichierCarte.txt";							//Nom fichier source cartes
	toutes_cartes = loadAllCarteFromFile(nom_file);			//Chargement carte depuis fichier
	Carte jeu_carte = choix_unique_element(toutes_cartes);	//Choix + assignation carte partie

		//Chargement monstres
	monstre mons;											//Dummy identification type template
	nom_file = "fichierMonstre.txt";						//Nom fichier source monstres
	jeu_monstres = loadAllEntiteFromFile(mons, nom_file);	//Chargement monstres depuis fichier
}

int jeu::combat(string id_monstre)	///mb argument vecteur pour prévoir évolution (plusieurs monstres par case)
{
	vector<entite> vect_entite;
	vector<entite>::iterator ite;
	vector<entite>::iterator death;

	cout << vect_entite.size();

	bool loading = chargement_entite(vect_entite, id_monstre);

	if (loading == false)
	{
        puts("Un problème au niveau du chargement des entités est intervenu. Retour à la carte...");
        return 1;
	}

	vector<int> vect_p;
	vect_p = orga_entites(vect_entite);					//Indices personnages

	int nb_players = vect_p.size();						//Nombre personnages
	int nb_monsters = vect_entite.size() - nb_players;	//Nombre monstres
	int sortie = 0;

	while (sortie == 0)	//Boucle de combat
	{
		competence comp_util;
		entite target;

		for (ite = vect_entite.begin(); ite != vect_entite.end(); ite++)
		{
			comp_util = choix_comp(* ite);	//Choix compétence

			target = choix_target(comp_util, (* ite), vect_entite, vect_p);	//Choix cible

			sortie = appliquer_comp(target, comp_util, nb_players, nb_monsters);	//Effet compétence
		}
	}
}

vector<monstre>::iterator jeu::cherche_monstre(string id_monstre)
{
	vector<monstre>::iterator itm;

	for (itm = jeu_monstres.begin(); itm != jeu_monstres.end(); itm++)
	{
		if ((* itm).getID() == id_monstre)
		{
			break;
		}
	}
	return itm;
}

bool jeu::chargement_entite(vector<entite> & vect_entite, string id_monstre)
{
	if (jeu_perso.getID() == "")			//Si problème avec personnage
	{
		return 0;
	}
	else
	{
		vect_entite.push_back(jeu_perso);
	}

	std::vector<monstre>::iterator itm;
	itm = cherche_monstre(id_monstre);

	if (itm == jeu_monstres.end())			//Si problème avec monstre
	{
		return 0;
	}
	else
	{
		vect_entite.push_back(* itm);
	}

	return 1;
}

bool sort_speed(entite a, entite b)
{
	return a.getSpeed() > b.getSpeed();
}

bool jeu::is_personnage(entite indiv)
{
	if (indiv.getID().substr(0, 1) == "p")
	{
		return true;
	}
	return false;
}

vector<int> jeu::orga_entites(vector<entite> vect_entite)
{
	sort(vect_entite.begin(), vect_entite.end(), sort_speed);

	vector<int> vect_p;
	cout << vect_entite.size() << endl;

	for (int i = 0; i < vect_entite.size(); i++)		//Identification acteurs personnages
	{
		if (is_personnage(vect_entite[i]))	//Si personnage
		{
			vect_p.push_back(i);						//Rajout indice personnage
		}
	}

	return vect_p;
}

competence jeu::choix_comp(entite & indiv)
{
	competence comp_util;

	if (is_personnage(indiv))	//Personnage
	{
		puts("\n- Choix de compétence -");
		comp_util = choix_unique_element(indiv.getSkillVect());	//Choix manuel

		while (indiv.enleverMana(comp_util.getManaCost()) == false)
		{
			puts("Vous n'avez pas assez de mana pour utiliser cette compétence!");
			puts("- Choix de compétence -");
			comp_util = choix_unique_element(indiv.getSkillVect());	//Choix manuel
		}
	}
	else	//Monstre
	{
		comp_util = indiv.getSkillVect()[rand() % indiv.getSkillVect().size()];	//Choix aléatoire
	}

	cout << endl << "La compétence choisie par " << indiv.getName() << " est la compétence ";
	cout << comp_util.getName() << "." << endl;

	return comp_util;
}

entite jeu::choix_target(competence comp_util, entite indiv, vector<entite> vect_entite, vector<int> vect_p)
{
	entite target;

	if (is_personnage(indiv))	//Personnage
	{
		cout << "- Choix de la cible pour la compétence " << comp_util.getName() << " -" << endl;
		target = choix_unique_element(vect_entite);	///Souci de passage: modifications non répercutées sur l'objet du vecteur
		cout << "Le personnage ";
	}
	else	//Monstre
	{
		int cible = rand() % vect_p.size();	//Choix aléatoire
		target = vect_entite[cible];
		cout << "Le monstre ";
	}

	cout << indiv.getName() << " utilise la compétence ";
	cout << comp_util.getName();
	cout << " sur " << target.getName() << " (" << comp_util.getDamage() << " dégâts)." << endl;

	return target;
}

int jeu::appliquer_comp(entite & target, competence comp_util, int & nb_players, int & nb_monsters)
{
	target.enleverVie(comp_util.getDamage());	//Application attaque

    cout << "La cible " << target.getName() << " est touchée par ";
    cout << comp_util.getName();
    cout << ". Son total de points de vie s'élève désormais à " << target.getHpCurrent() << "." << endl;

	if (target.getAlive() == false)	//Si cible morte
	{
		if (is_personnage(target))	//Si personnage
		{
			cout << "Le personnage " << target.getName() << " est mort." << endl;
			nb_players--;
		}
		else	//Si monstre
		{
			cout << "Le monstre " << target.getName() << " est mort." << endl;
			nb_monsters--;
		}
	}

	//Check conséquences combat
	if (nb_players == 0)
	{
		return 1;
	}
	else if (nb_monsters == 0)
	{
		return 2;
	}

	return 0;
}
