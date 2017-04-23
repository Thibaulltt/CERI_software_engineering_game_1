#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <typeinfo>
#include "../headers/fonctionsjeu.h"
#include "../headers/carte.h"
#include "../headers/io.h"

using namespace io;
using namespace std;

int main()
{
	//Phase préparation partie
	jeu a;
	a.preparation_partie();

	//Combat
//	vector<entite> vect_entite;
//	vector<entite>::iterator ite;
//	vector<entite>::iterator death;
//
//	vect_entite.push_back(a.getPerso());
//	vect_entite.push_back(a.getMonstres()[0]);
//
//	sort(vect_entite.begin(), vect_entite.end(), sort_speed);
//
//	vector<int> vect_p;
//
//	for (int i = 0; i < vect_entite.size(); i++)		//Identification acteurs personnages
//	{
//		if (vect_entite[i].getID().substr(0, 1) == "p")	//Si Id personnage
//		{
//			vect_p.push_back(i);						//Rajout indice personnage
//		}
//	}
//
//	int nb_players = vect_p.size();						//Nombre personnages
//	int nb_monsters = vect_entite.size() - nb_players;	//Nombre monstres
//
//	cout << "nb joueurs: " << nb_players << endl;
//	cout << "nb monstres: " << nb_monsters << endl;
//
//
//	while (true)
//	{
//		competence comp_util;
//		entite target;
//
//		for (ite = vect_entite.begin(); ite != vect_entite.end(); ite++)
//		{
//			string type = (* ite).getID().substr(0,1);
//
//			if (type == "p")			//Si personnage (choix manuel compétence)
//			{
//				choix:
//				cout << "Choix compétence personnage: " << endl;
//				comp_util = choix_unique_element((* ite).getSkillVect());
//			}
//			else												//Si monstre (choix aléatoire compétence)
//			{
//				cout << "Choix compétence aléatoire monstre: " << endl;
//				comp_util = (* ite).getSkillVect()[rand() % (* ite).getSkillVect().size()];
//				cout << "Compétence utilisée: ";
//				comp_util.printCompetence();
//			}
//
//			if (!(* ite).enleverMana(comp_util.getManaCost()))	//Mana insuffisant pour lancer compétence
//			{
//				cout << "Vous n'avez pas assez de mana pour utiliser cette compétence!";
//				cout << "Choisissez-en une autre!";
//				goto choix;
//			}
//			else												//Mana suffisant pour lancer compétence
//			{
//					Choix cible
//				if ((* ite).getID().substr(0, 1) == "p")		//Si personnage (choix manuel cible)
//				{
//					cout << "Choix cible personnage: " << endl;
//                    target = choix_unique_element(vect_entite);
//				}
//				else											//Si monstre (choix aléatoire cible)
//				{
//					cout << "Choix cible aléatoire monstre: " << endl;
//					int cible = rand() % vect_p.size();
//					target = vect_entite[cible];
//				}
//
//                if (target.enleverVie(comp_util.getDamage()))	//Application attaque + état mort
//				{
//                    if (target.getID().substr(0, 1) == "p")		//Si personnage
//					{
//						cout << "Un personnage est mort" << endl;
//                        nb_players--;							//Personnage mort
//					}
//					else
//					{
//						cout << "Un monstre est mort" << endl;
//						nb_monsters--;							//Monstre mort
//					}
//				}
//				else if (!target.enleverVie(comp_util.getDamage()))
//				{
//					cout << target.getName() << " subit " << comp_util.getDamage() << " dégâts" << endl;
//					cout << target.getName() << " a désormais " << target.getHpCurrent() << " points de vie" << endl;
//
//				}
//
//				if (nb_players == 0)							//Tous personnages morts
//				{
//					cout << "Tous les personnages sont morts" << endl;
//					return 1;
//				}
//				else if (nb_monsters == 0)						//Tous monstres morts
//				{
//					cout << "Tous les monstres sont morts" << endl;
//					return 1;
//				}
//			}
//		}
//	}

	return 0;
}
