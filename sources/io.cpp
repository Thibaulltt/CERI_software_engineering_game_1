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
		std::puts(" __________   ___    ___   __________     __________   __________   __     ___   __________");
		std::puts("/___   ___/  /  /   /  /  /  _______/    /  _______/  /  ____   /  /  \\__ /  /  /  _______/");
		std::puts("   /  /     /  /__ /  /  /  /__         /  /  __     /  /___/  /  /         /  /  /__");
		std::puts("  /  /     /   __    /  /   __/        /  /  /  \\   /  ____   /  /  / - /  /  /   __/");
		std::puts(" /  /     /  /   /  /  /  /______     /  /___/  /  /  /   /  /  /  /   /  /  /  /______");
		std::puts("/_ /     /_ /   /_ /  /_________/    /_________/  /_ /   /_ /  /_ /   /_ /  /_________/");
		std::puts("\n");

		std::puts("Dans The Game, vous devez débusquer et tuer tous les monstres présents sur la carte. Bonne chance!");
		std::puts("\n");
	}

	int getTerminalWentiteIdth()
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
		int skillDamage;
		int skillManaCost;

		cout << "Entrez le nom de la compétence : ";
		cin >> skillName;

		cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
		cin >> skillDamage;
		while(!checkInput(skillDamage))
		{
			cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
			cin >> skillDamage;
		}

		cout << "Entrez le cout en mana de la competence : ";
		cin >> skillManaCost;
		while(!checkInput(skillManaCost))
		{
			cout << "Entrez le cout en mana de la competence : ";
			cin >> skillManaCost;
		}

		competence creation(skillName, skillDamage, skillManaCost);

		return creation;
	}

/*	competence createCompetenceMonstre() //Permet à l'utilisateur de créer une compétence pour monstre
	{
		string skillName;
		int skillDamage;
		int skillManaCost;

		cout << "Entrez le nom de la compétence : ";
		cin >> skillName;

		cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
		cin >> skillDamage;
		while(!checkInput(skillDamage))
		{
			cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
			cin >> skillDamage;
		}

		competence creation(skillName, skillDamage);

		return creation;
	}


	monstre createMonstre() //Permet à l'utilisateur de créer un monstre avec des caractéristiques choisies
	{
		string entiteName;
		int entiteHpMax;
		int entiteSpeed;

		cout << "Entrez le nom du monstre : ";
		cin >> entiteName;
		cout << endl;

		cout << "Entrez son nombre de points de vie : ";
		cin >> entiteHpMax;
		while(!checkInput(entiteHpMax))
		{
			cout << "Entrez son nombre de points de vie : ";
			cin >> entiteHpMax;
		}

		cout << "Entrez sa vitesse : ";
		cin >> entiteSpeed;
		while(!checkInput(entiteSpeed))
		{
			cout << "Entrez sa vitesse : ";
			cin >> entiteSpeed;
		}

		monstre creation = monstre(entiteName, entiteHpMax, entiteSpeed); //Crée le monstre

		vector<competence> skills = creation.getEntiteSkillVect();

		for (int i=0 ; i<3 ; i++) //Remplit le tableau de compétences avec de nouvelles compétences
		{
			// PREVOIR UN SWITCH POUR SAVOIR SI L'USER VEUT CONTINUER A RENTRER DES COMPETENCES
			// PENSER A CHANGER LE 3 DANS LA BOUCLE EN 11
		   skills.push_back(createCompetenceMonstre());
		}

		creation.printMonstre();

		creation.saveInFile(); //Le sauvegarde dans le fichier texte

		return creation;
	}
*/

	vector<competence> loadCompetenceFromFile(string nomFichier,int numLigne)
	{
		int nbSeparateur = 0;
		string sskillName;
		string sskillDamage;
		string sskillManaCost;

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
								sskillName += parcoursSkill;
								continue;
							}

							if (parcoursSkill == '(') //Detection du champ de dégats
							{
								nbParenthese++;
								continue;
							}

							if ((parcoursSkill !='(') && (parcoursSkill != ':') && (nbParenthese == 1) ) //Champ de dégats
							{
								sskillDamage+= parcoursSkill;
							}

							if ((parcoursSkill !='(') && (parcoursSkill != ':') && (nbParenthese == 1) && (parcoursSkill == '_'))//Detection du champ de cout en mana
							{
								nbUnderscore++;
								continue;
							}

							if ((parcoursSkill !='(') && (parcoursSkill != ':') && (nbParenthese == 1) && (nbUnderscore == 1)) //Champ de cout en mana
							{
								sskillManaCost+=parcoursSkill;
								continue;
							}

							if (parcoursSkill == ')') //Fin du champ de dégats
							{
								continue;
							}

							if (parcoursSkill == ':') //Fin de l'analyse d'une compétence
							{
								int skillDamage;
								istringstream (sskillDamage) >> skillDamage; //Conversion string to int

								int skillManaCost;
								istringstream (sskillManaCost) >> skillManaCost;

								competence skill(sskillName, skillDamage, skillManaCost); //On crée la compétence
								allSkills.push_back(skill); //On la met dans le vecteur

								sskillName=""; // On reset tout pour passer à la prochaine compétence
								sskillDamage="";
								sskillManaCost="";
								nbParenthese=0;
								nbUnderscore=0;
								skillDamage=0;
								skillManaCost=0;
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


	//FONCTIONS DE CHARGEMENT D'UNE ENTITE


	vector<entite> loadAllentiteFromFile(string nomFichier)
	{
		vector<entite> allPerso; //Vecteur de retour

		string uneLigne=""; //Variable stockant une ligne

		int nbSeparateur = 0; //Compteur de /
		int nbBarre = 0; //Compteur de |
		string sentiteId;
		string sentiteName;
		string sentiteHpMax;
		string sentiteSpeed;
		string sentiteManaMax;
		string entiteDescription;
		int entiteHpMax;
		int entiteSpeed;
		int entiteManaMax;
		int cptLigne=0;
		vector<competence> allSkills;

		char parcoursCarac; //Parcours de la ligne

		ifstream fichierEntite(nomFichier.c_str(), ios::in); //Ouverture en mode lecture

		if(fichierEntite)
		{
			while (getline(fichierEntite, uneLigne)) //Parcours de tout le fichier et stockage d'une ligne
			{
				cptLigne++; //Reset de toutes les variables afin de stocker une nouvelle ligne
				sentiteName="";
				sentiteId="";
				sentiteHpMax="";
				entiteHpMax=0;
				sentiteSpeed="";
				entiteSpeed=0;
				sentiteManaMax="";
				entiteManaMax=0;
				nbSeparateur=0;
				nbBarre=0;
				entiteDescription="";
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

					if (nbSeparateur == 0) // Champ entiteId
					{
						sentiteId+=parcoursCarac;
					}

					if (nbSeparateur == 1) //Champ Nom
					{
						if (parcoursCarac == '/')
						{
							continue;
						}
						sentiteName+=parcoursCarac;
					}

					if (nbSeparateur == 2) //Champ entiteHpMax
					{
						if (parcoursCarac == '/')  continue;
						sentiteHpMax+=parcoursCarac;
					}

					if (nbSeparateur == 3) //Champ vitesse
					{
						if (parcoursCarac == '/')  continue;
						sentiteSpeed+=parcoursCarac;
					}

					if(nbSeparateur == 4)
					{
						continue;
					}

					if(nbSeparateur >= 5) //Champ compétence + entiteManaMax + entiteDescription
					{
						if(parcoursCarac == '|')
						{
							nbBarre++;
						}

						if(nbBarre == 0) continue;

						if (nbBarre == 1) //Champ entiteManaMax
						{
							if(parcoursCarac=='|') continue;
							sentiteManaMax+=parcoursCarac;
						}

						if (nbBarre == 2) //Champ entiteDescription
						{
							if(parcoursCarac=='|') continue;
							entiteDescription+=parcoursCarac;
						}

						if (nbBarre==3)
						{
							break;
						}
					}
				}


				istringstream (sentiteHpMax) >> entiteHpMax; //Conversion string to int

				istringstream (sentiteSpeed) >> entiteSpeed; //Conversion string to int

				istringstream (sentiteManaMax) >> entiteManaMax; //Conversion string to int

				allSkills = loadCompetenceFromFile("fichierEntite.txt",cptLigne); //Récupération des compétences

				entite creation(sentiteId, sentiteName, entiteHpMax, entiteSpeed, entiteManaMax, entiteDescription, allSkills); //Création du entite

				allPerso.push_back(creation); //Stockage du perso dans le vecteur de retour

			}

			return allPerso;

			fichierEntite.close();
		}

		else
		{
			cerr << "Impossible d'ouvrir le fichier." << endl;
		}
	}
}
