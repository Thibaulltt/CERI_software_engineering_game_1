#include "../headers/io.h"
#include <vector>
#include <termios.h>	// Needed for terminal input manipulation
#include <stdio.h>	// Needed for terminal input manipulation
#include <fstream>
#include <iostream>

// Notes :
// Get the terminal column number :
// 	> stty -a | grep "col" | tail -c 22 | tail -c 13 | head -c 3
// Get the terminal rows number :
// 	> stty -a | grep "col" | tail -c 22 | head -c 2

using namespace std;

namespace io
{
	void ChangeTerminal(bool Ech)
	{
		tcgetattr(0, &before);			/* Grab old terminal i/o settings */
		after = before;				/* Make new settings same as old settings */
		after.c_lflag &= ~ICANON;		/* Disable buffered i/o */
		after.c_lflag &= Ech==1 ? ECHO:~ECHO;	/* Set echo mode */
		tcsetattr(0, TCSANOW, &after);		/* Use these new terminal i/o settings now */
	}

	void ResetTerminal()
	{
		tcsetattr(0, TCSANOW, &before);		// Restore old terminal I/O settings
	}

	char de()
	{
		char ch;				// Return character
		ChangeTerminal();
		ch = getchar();				// getchar() now takes only one char
		ResetTerminal();
		return ch;
	}

	std::string long_input()
	{
		std::stringstream input;
		char charInput,deletedChar;
		ChangeTerminal(1);
		do {
			charInput = getchar();
			if (charInput != 127)
				input << charInput;
			else
				removeLastChar(input);
			//	if (input.tellp() > 0)
			//		input.seekp(-1, input.cur);
		} while(charInput != 10);
		ResetTerminal();
		return input.str().length() == 1 ? long_input() : input.str();
	}

	void removeLastChar(std::stringstream& input)
	{
		std::stringstream str;
		std::string s = input.str();
		if (s.size() != 0)
		{
			s.erase(s.end()-1);
			input.str("");
			input << s;
		}
	}

	void bienvenue()
	{
		std::puts("\n");
		std::puts("                                         Welcome to");
		std::puts(" __________   ___    ___   __________     __________   __________   ___    ___   __________");
		std::puts("/___   ___/  /  /   /  /  /  _______/    /  _______/  /  ____   /  /  /__ /  /  /  _______/");
		std::puts("   /  /     /  /__ /  /  /  /__         /  /  __     /  /___/  /  /         /  /  /__");
		std::puts("  /  /     /   __    /  /   __/        /  /  /  \\   /  ____   /  /  / - /  /  /   __/");
		std::puts(" /  /     /  /   /  /  /  /______     /  /___/  /  /  /   /  /  /  /   /  /  /  /______");
		std::puts("/_ /     /_ /   /_ /  /_________/    /_________/  /_ /   /_ /  /_ /   /_ /  /_________/");
		std::puts("\n");

		std::puts("Dans The Game, vous devez débusquer et tuer tous les monstres présents sur la carte. Bonne chance!");
		std::puts("\n");
	}

	int getTerminalWidth()
	{
		FILE * r;
		std::string w1,w2;
		char * ww1 = new char[6];
		char * ww2 = new char[6];
		system("stty -a | grep row | cut -d\' \' -f 7 >> dump.txt");
		r = fopen("dump.txt", "r");
		w1 = fgets(ww1,5,r);
		fclose(r);
		system("rm dump.txt");
		system("stty -a | grep row | cut -d\' \' -f 6 >> dump.txt");
		r = fopen("dump.txt", "r");
		w2 = fgets(ww2,5,r);
		fclose(r);
		system("rm dump.txt");
		if (w1[0] == 'c')
			return std::stoi(w2.substr(0,w2.size()-1));
		else
			return std::stoi(w1.substr(0,w1.size()-1));
	}

	int getTerminalHeight()
	{
		FILE * r;
		std::string h1,h2;
		char * hh1 = new char[6];
		char * hh2 = new char[6];
		system("stty -a | grep row | cut -d\' \' -f 5 >> dump.txt");
		r = fopen("dump.txt", "r");
		h1 = fgets(hh1,5,r);
		fclose(r);
		system("rm dump.txt");
		system("stty -a | grep row | cut -d\' \' -f 4 >> dump.txt");
		r = fopen("dump.txt", "r");
		h2 = fgets(hh2,5,r);
		fclose(r);
		system("rm dump.txt");
		if (h1[0] == 'r')
			return std::stoi(h2.substr(0,h2.size()-1));
		else
			return std::stoi(h1.substr(0,h1.size()-1));
	}
	bool checkInput(int x) //Verifie que l'utilisateur entre bien un entier
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


	competence createCompetence() //Permet à l'utilisateur de créer une compétence pour personnage
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

	competence createCompetenceMonstre() //Permet à l'utilisateur de créer une compétence pour monstre
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


	monstre createMonstre() //Permet à l'utilisateur de créer un monstre avec des caractéristiques choisies
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


	vector<competence> loadCompetenceFromFile(string nomFichier,int numLigne)
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

	vector<monstre> loadAllMonstreFromFile()
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


	vector<personnage> loadAllPersonnageFromFile()
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
}
