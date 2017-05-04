#include <iostream>	// à remplacer avec notre librairie I/O plus tard
#include <vector>
#include "../headers/carte.h"
#include "../headers/fonctionsjeu.h"

using namespace std;

jeu::jeu()
{
	bienvenue();

		//Choix personnage
	vector<personnage> tous_persos;							//Vecteur personnages
	personnage pers;										//Dummy identification type template
	string nom_file = "fichierPersonnage.txt";				//Nom fichier source personnages
	tous_persos = loadAllEntiteFromFile(pers, nom_file);	//Remplissage vecteur personnages depuis fichier
	choix_unique_element(jeu_perso, tous_persos, 0);		//Choix + assignation personnage partie

		//Choix carte
	vector<Carte> toutes_cartes;							//Vecteur cartes
	nom_file = "fichierCarte.txt";							//Nom fichier source cartes
	toutes_cartes = loadAllCarteFromFile(nom_file);			//Chargement carte depuis fichier
	choix_unique_element(jeu_carte, toutes_cartes, 0);		//Choix + assignation carte partie
    jeu_nombre_monstres = jeu_carte.getNbrMonstres();		//Récupération du nombre de monstres total

		//Chargement monstres
	monstre mons;											//Dummy identification type template
	nom_file = "fichierMonstre.txt";						//Nom fichier source monstres
	jeu_monstres = loadAllEntiteFromFile(mons, nom_file);	//Chargement monstres depuis fichier
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

void jeu::setJeuCarte(Carte jeu_map)
{
	jeu_carte = jeu_map;
}

void jeu::afficherJeu(int & result)
{
	afficherCarte(jeu_carte, jeu_carte.getTaille(), 1);
	while (true)
		deplacement(result);
	de();
}
std::string jeu::genererDeplacement(std::vector<bool>& v)
{
	int x = currentPlayerPosition.first;
	int y = currentPlayerPosition.second;
	int max = jeu_carte.getTaille();

	std::string deplacements = "";

	// Si le joueur peut se déplacer vers le haut :
	if (y-1 >= 0 && jeu_carte.caseAccessible(x,y-1))
	{
		deplacements += "| Z - Haut ";
		v[0] = true;
	}
	else
		v[0] = false;
	// Si le joueur peut se deplacer vers la gauche :
	if(x-1 >= 0 && jeu_carte.caseAccessible(x-1,y))
	{
		deplacements += "| Q - Gauche ";
		v[1] = true;
	}
	else
		v[1] = false;
	// Si le joueur peut se déplacer vers le bas
	if (y+1 <= max && jeu_carte.caseAccessible(x,y+1))
	{
		deplacements += "| S - Bas ";
		v[2] = true;
	}
	else
		v[2] = false;
	// Si le joueur peut se déplacer vers la droite :
	if (x+1 <= max && jeu_carte.caseAccessible(x+1,y))
	{
		deplacements += "| D - Droite ";
		v[3] = true;
	}
	else
		v[3] = false;
	cout << endl;
	return deplacements + "|";
}

std::string jeu::genererInputAccepte(vector<bool> b)
{
	std::string s = "";
	if (b[0] == true)
		s += "Zz";
	if (b[1] == true)
		s += "Qq";
	if (b[2] == true)
		s += "Ss";
	if (b[3] == true)
		s += "Dd";
	return s;
}

void jeu::deplacement(int & result)
{
	std::vector<bool> b(4,false);
	std::string deplacement_possibles = genererDeplacement(b);
	std::string inputAccepte = genererInputAccepte(b);
	int x = currentPlayerPosition.first;
	int y = currentPlayerPosition.second;
	afficherMouvements(deplacement_possibles,"Dans quelle direction voulez-vous vous déplacer ?");
	char deplacement_demande = de();
	while (inputAccepte.find(deplacement_demande) == string::npos)
	{
		afficherMouvements(deplacement_possibles,"Cette case est innaccessible !");
		deplacement_demande = de();
	}
	switch (deplacement_demande) {
		case 'z':
			y--;
			break;
		case 'Z':
			y--;
			break;
		case 's':
			y++;
			break;
		case 'S':
			y++;
			break;
		case 'q':
			x--;
			break;
		case 'Q':
			x--;
			break;
		case 'd':
			x++;
			break;
		case 'D':
			x++;
			break;
	}
	updateMap(jeu_carte, std::make_pair(y,x));

	///Combat, à tester
//	string content = jeu_carte.getPlateau()[x][y];
//
//	cout << "contenu case: " << content << "\n";
//
//	if (content.substr(0, 1) == "m")
//	{
//		cout << "On rentre en mode combat\n";
//		result = combat(content);
//	}
}


int jeu::combat(string id_monstre)
{
	puts("** Combat **");

	vector<entite> vect_entite;
	vector<entite>::iterator ite;

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
	int sortie = 2;

	while (sortie == 2)	//Boucle de combat
	{
		competence comp_util;
		entite target;

		for (ite = vect_entite.begin(); ite != vect_entite.end(); ite++)	//Pour chaque acteur
		{
			if ((* ite).getAlive() == true)
			{
				aff_combat(vect_entite);	//Affichage infos utiles acteurs

				comp_util = choix_comp(* ite);	//Choix compétence

				target = choix_target(comp_util, (* ite), vect_entite, vect_p);	//Choix cible

				sortie = appliquer_comp((* ite), target, vect_entite, comp_util, nb_players, nb_monsters);	//Effet compétence
			}
		}
	}

	return sortie;
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

vector<int> jeu::orga_entites(vector<entite> & vect_entite)
{
	sort(vect_entite.begin(), vect_entite.end(), sort_speed);

	vector<int> vect_p;

	for (int i = 0; i < vect_entite.size(); i++)		//Identification acteurs personnages
	{
		if (vect_entite[i].is_personnage())				//Si personnage
		{
			vect_p.push_back(i);						//Rajout indice personnage
		}
	}

	return vect_p;
}

competence jeu::choix_comp(entite & indiv)
{
	competence comp_util;

	if (indiv.is_personnage())	//Personnage
	{
		puts("\n- Choix de compétence -");
		choix_unique_element(comp_util, indiv.getSkillVect(), 1);	//Choix manuel

		while (indiv.enleverMana(comp_util.getManaCost()) == false)
		{
			puts("Vous n'avez pas assez de mana pour utiliser cette compétence!");
			puts("- Choix de compétence -");
			choix_unique_element(comp_util, indiv.getSkillVect(), 1);	//Choix manuel
		}

		if (indiv.getManaCurrent() > indiv.getManaMax())
		{
			indiv.setManaCurrent(indiv.getManaMax());
		}
	}
	else	//Monstre
	{
		comp_util = indiv.getSkillVect()[rand() % indiv.getSkillVect().size()];	//Choix aléatoire
	}
//
//	cout << endl << "La compétence choisie par " << indiv.getName() << " est la compétence ";
//	cout << comp_util.getName() << "." << endl;

	return comp_util;
}

entite jeu::choix_target(competence comp_util, entite & indiv, vector<entite> & vect_entite, vector<int> vect_p)
{
	entite target;

	if (indiv.getAlive() == true)
	{
		if (indiv.is_personnage())	//Personnage
		{
			cout << "- Choix de la cible pour la compétence " << comp_util.getName() << " -" << endl;
			choix_unique_element(target, vect_entite, 1);
		}
		else	//Monstre
		{
			int cible = rand() % vect_p.size();	//Choix aléatoire
			target = vect_entite[cible];
		}

		cout << endl << endl << indiv.getName() << " utilise la compétence ";
		cout << comp_util.getName();
		cout << " sur " << target.getName() << endl;
	}

	return target;
}

int jeu::appliquer_comp(entite indiv, entite target, vector<entite> & vect_entite, competence comp_util, int & nb_players, int & nb_monsters)
{
	vector<entite>::iterator ite;
	int damage = 0;

	for(ite = vect_entite.begin(); ite != vect_entite.end(); ite++)
	{
		if ((* ite).getID() == target.getID())
		{
			if (indiv.is_personnage())
 			{
 				damage = target.randomizeDegat(comp_util.getDamage(), 5, 10);
 			}
 			else
 			{
 				damage = comp_util.getDamage();
 			}

			(* ite) = (* ite).enleverVie(damage);	//Application attaque
			cout << "(" << damage << " dégâts)\n";

			if ((* ite).getHpCurrent() > (* ite).getHpMax())
			{
                (* ite).setHpCurrent((* ite).getHpMax());
			}

			break;
		}
	}

	if ((* ite).getAlive() == false)	//Si cible morte
	{
		if ((* ite).is_personnage())	//Si personnage
		{
			cout << "Le personnage " << (* ite).getName() << " est mort." << endl;
			nb_players--;
		}
		else	//Si monstre
		{
			cout << "Le monstre " << (* ite).getName() << " est mort." << endl;
			nb_monsters--;
		}
	}

	//Check conséquences combat
	if (nb_players == 0)
	{
		return 0;	//Tous personnages morts, fin partie
	}
	else if (nb_monsters == 0)
	{
		return 1;	//Tous monstres morts, retour carte
	}
	return 2;
}

bool sort_speed(entite a, entite b)
{
	return a.getSpeed() > b.getSpeed();
}
