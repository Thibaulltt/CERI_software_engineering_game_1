#include "../headers/interface.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


bool interface::checkInput(int x) //Verifie que l'utilisateur entre bien un entier
{
	if (!cin)
	{
		cin.clear();
		cin.ignore(256,'\n');
		cout << "Veuillez entrer un entier." << endl;
		return false;
	}
	return true;
}


competence interface::createCompetence() //Permet à l'utilisateur de créer une compétence pour personnage
{
	string skillName;
	int damage;
	int manaCost;

	cout << "Entrez le nom de la compétence : ";
	cin >> skillName;

	cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
	cin >> damage;
	while(!checkInput(damage))
	{
		cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
		cin >> damage;
	}

	cout << "Entrez le cout en mana de la competence : ";
	cin >> manaCost;
	while(!checkInput(manaCost))
	{
		cout << "Entrez le cout en mana de la competence : ";
		cin >> manaCost;
	}

	competence creation(skillName, damage, manaCost);

	return creation;
}

competence interface::createCompetenceMonstre() //Permet à l'utilisateur de créer une compétence pour monstre
{
	string skillName;
	int damage;
	int manaCost;

	cout << "Entrez le nom de la compétence : ";
	cin >> skillName;

	cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
	cin >> damage;
	while(!checkInput(damage))
	{
		cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
		cin >> damage;
	}

	competence creation(skillName, damage);

	return creation;
}


monstre interface::createMonstre() //Permet à l'utilisateur de créer un monstre avec des caractéristiques choisies
{
	string name;
	int hpMax;
	int speed;

	cout << "Entrez le nom du monstre : ";
	cin >> name;
	cout << endl;

	cout << "Entrez son nombre de points de vie : ";
	cin >> hpMax;
	while(!checkInput(hpMax))
	{
		cout << "Entrez son nombre de points de vie : ";
		cin >> hpMax;
	}

	cout << "Entrez sa vitesse : ";
	cin >> speed;
	while(!checkInput(speed))
	{
		cout << "Entrez sa vitesse : ";
		cin >> speed;
	}

	monstre creation(name, hpMax, speed); //Créé le monstre

	vector<competence> skills = creation.getSkillVect();

	for (int i=0 ; i<3 ; i++) //Rempli le tableau de compétences avec de nouvelles compétences
	{
		// PREVOIR UN SWITCH POUR SAVOIR SI L'USER VEUT CONTINUER A RENTRER DES COMPETENCES
		// PENSER A CHANGER LE 3 DANS LA BOUCLE EN 11
	   skills.push_back(this->createCompetenceMonstre());
	}

	creation.printMonstre();

	creation.saveInFile(); //Le sauvegarde dans le fichier texte

	return creation;
}


vector<competence> interface::loadCompetenceFromFile(string nomFichier,int numLigne)
{
	int nbSeparateur = 0;
	string sSkillName;
	string sDamage;
	string sManaCost;

	string laLigne="";

	vector<competence> allSkills;

	char parcoursSkill;
	int cptLigne=0;
	string lesCompetences;
	int nbParenthese=0;
	int nbUnderscore=0;

	ifstream fichierMonstre(nomFichier.c_str(), ios::in); //Ouverture en mode lecture

	if(fichierMonstre)
	{
		while (getline(fichierMonstre, laLigne)) //Parcours des lignes
		{
			cptLigne++;
			if (cptLigne==numLigne) //Si on est sur la ligne recherchée
			{
				for(int i=0; i<laLigne.length() ; i++) //Boucle de parcours de toute la ligne
				{
					parcoursSkill = laLigne[i]; //Variable de parcours de la ligne

					if(nbSeparateur <4) //Recherche du champ compétence sur la ligne
					{
						if (parcoursSkill == '/')
						{
							nbSeparateur++;
						}
					}

					if (nbSeparateur==4) //Si le curseur est sur le champ compétence.
					{
						if (parcoursSkill == '/')  continue; //Dernier séparateur

						if ((parcoursSkill !='(') && (parcoursSkill != ':') && (nbParenthese == 0) )//Champ nom de compétence
						{
							sSkillName += parcoursSkill;
							continue;
						}

						if (parcoursSkill == '(') //Detection du champ de dégats
						{
							nbParenthese++;
							continue;
						}

						if ((parcoursSkill !='(') && (parcoursSkill != ':') && (nbParenthese == 1) ) //Champ de dégats
						{
							sDamage+= parcoursSkill;
						}

						if ((parcoursSkill !='(') && (parcoursSkill != ':') && (nbParenthese == 1) && (parcoursSkill == '_'))//Detection du champ de cout en mana
						{
							nbUnderscore++;
							continue;
						}

						if ((parcoursSkill !='(') && (parcoursSkill != ':') && (nbParenthese == 1) && (nbUnderscore == 1)) //Champ de cout en mana
						{
							sManaCost+=parcoursSkill;
							continue;
						}

						if (parcoursSkill == ')') //Fin du champ de dégats
						{
							continue;
						}

						if (parcoursSkill == ':') //Fin de l'analyse d'une compétence
						{
							int damage;
							istringstream (sDamage) >> damage; //Conversion string to int

							int manaCost;
							istringstream (sManaCost) >> manaCost;

							competence skill(sSkillName, damage, manaCost); //On crée la compétence
							allSkills.push_back(skill); //On la met dans le vecteur

							sSkillName=""; // On reset tout pour passer à la prochaine compétence
							sDamage="";
							sManaCost="";
							nbParenthese=0;
							nbUnderscore=0;
							damage=0;
							manaCost=0;
							continue;
						}
						if (parcoursSkill== '|')
						{
							break;
						}
					}
				}
			}
		}

		fichierMonstre.close(); //Fermeture du fichier
	}
	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}
	return allSkills;
}

// FONCTION DE CHARGEMENT D'UN MONSTRE

vector<monstre> interface::loadAllMonstreFromFile()
{
	vector<monstre> allMonsters; //Vecteur de retour

	string uneLigne=""; //Variable stockant une ligne

	int nbSeparateur = 0;
	string sID;
	string sName;
	string sHpMax;
	string sSpeed;
	int hpMax;
	int speed;
	int cptLigne=0;
	vector<competence> allSkills;

	char parcoursCarac; //Parcours de la ligne

	ifstream fichierMonstre("fichierMonstre.txt", ios::in); //Ouverture en mode lecture

	if(fichierMonstre)
	{
		while (getline(fichierMonstre, uneLigne)) //Parcours de tout le fichier et stockage d'une ligne
		{
			cptLigne++;
			sName=""; //Reset de toutes les variables afin de stocker une nouvelle ligne
			sID="";
			sHpMax="";
			hpMax=0;
			sSpeed="";
			speed=0;
			nbSeparateur=0;
			allSkills.clear();


			for(int i=0; i<uneLigne.length(); i++) //Analyse de la ligne
			{
				parcoursCarac = uneLigne[i];
				if(nbSeparateur <4) // Récupération des carac. d'un monstre
				{
					if (parcoursCarac == '/')
					{
						nbSeparateur++;
					}

					if (nbSeparateur == 0) // Champ ID
					{
						sID+=parcoursCarac;
					}

					if (nbSeparateur == 1) //Champ Nom
					{
						if (parcoursCarac == '/')
						{
							continue;
						}
						sName+=parcoursCarac;
					}

					if (nbSeparateur == 2) //Champ hpMax
					{
						if (parcoursCarac == '/')  continue;
						sHpMax+=parcoursCarac;
					}

					if (nbSeparateur == 3) //Champ vitesse
					{
						if (parcoursCarac == '/')  continue;
						sSpeed+=parcoursCarac;
					}
				}
			}


			istringstream (sHpMax) >> hpMax; //Conversion string to int

			istringstream (sSpeed) >> speed; //Conversion string to int

			allSkills = this->loadCompetenceFromFile("fichierMonstre.txt",cptLigne); //Récupération des compétences

			monstre creation(sName, hpMax, speed, allSkills); //Création du monstre

			allMonsters.push_back(creation); //Stockage du monstre dans le vecteur de retour

		}

		return allMonsters;

		fichierMonstre.close();
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}
}



//FONCTIONS DE CHARGEMENT D'UN PERSONNAGE


vector<personnage> interface::loadAllPersonnageFromFile()
{
	vector<personnage> allPerso; //Vecteur de retour

	string uneLigne=""; //Variable stockant une ligne

	int nbSeparateur = 0; //Compteur de /
	int nbBarre = 0; //Compteur de |
	string sID;
	string sName;
	string sHpMax;
	string sSpeed;
	string sManaMax;
	string description;
	int hpMax;
	int speed;
	int manaMax;
	int cptLigne=0;
	vector<competence> allSkills;

	char parcoursCarac; //Parcours de la ligne

	ifstream fichierPersonnage("fichierPersonnage.txt", ios::in); //Ouverture en mode lecture

	if(fichierPersonnage)
	{
		while (getline(fichierPersonnage, uneLigne)) //Parcours de tout le fichier et stockage d'une ligne
		{
			cptLigne++; //Reset de toutes les variables afin de stocker une nouvelle ligne
			sName="";
			sID="";
			sHpMax="";
			hpMax=0;
			sSpeed="";
			speed=0;
			sManaMax="";
			manaMax=0;
			nbSeparateur=0;
			nbBarre=0;
			description="";
			allSkills.clear();


			for(int i=0; i<uneLigne.length(); i++) //Analyse de la ligne
			{
				parcoursCarac = uneLigne[i];
			 //   if(nbSeparateur <4) // Récupération des carac. d'un monstre
			   // {
					if ((parcoursCarac == '/') || (parcoursCarac == '|'))
					{
						nbSeparateur++;
					}

					if (nbSeparateur == 0) // Champ ID
					{
						sID+=parcoursCarac;
					}

					if (nbSeparateur == 1) //Champ Nom
					{
						if (parcoursCarac == '/')
						{
							continue;
						}
						sName+=parcoursCarac;
					}

					if (nbSeparateur == 2) //Champ hpMax
					{
						if (parcoursCarac == '/')  continue;
						sHpMax+=parcoursCarac;
					}

					if (nbSeparateur == 3) //Champ vitesse
					{
						if (parcoursCarac == '/')  continue;
						sSpeed+=parcoursCarac;
					}

					if(nbSeparateur == 4)
					{
						continue;
					}

					if(nbSeparateur >= 5) //Champ compétence + manaMax + description
					{
						if(parcoursCarac == '|')
						{
							nbBarre++;
						}

						if(nbBarre == 0) continue;

						if (nbBarre == 1) //Champ manaMax
						{
							if(parcoursCarac=='|') continue;
							sManaMax+=parcoursCarac;
						}

						if (nbBarre == 2) //Champ Description
						{
							if(parcoursCarac=='|') continue;
							description+=parcoursCarac;
						}

						if (nbBarre==3)
						{
							break;
						}

					}

			}


			istringstream (sHpMax) >> hpMax; //Conversion string to int

			istringstream (sSpeed) >> speed; //Conversion string to int

			istringstream (sManaMax) >> manaMax; //Conversion string to int

			allSkills = this->loadCompetenceFromFile("fichierPersonnage.txt",cptLigne); //Récupération des compétences

			personnage creation(sName, hpMax, speed, manaMax, description, allSkills); //Création du personnage

			allPerso.push_back(creation); //Stockage du perso dans le vecteur de retour

		}

		return allPerso;

		fichierPersonnage.close();
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}
}
