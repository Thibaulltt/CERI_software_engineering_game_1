#include <vector>
#include <termios.h>	// Needed for terminal input manipulation
#include <stdio.h>	// Needed for terminal input manipulation
#include <fstream>
#include <iostream>
#include "../headers/carte.h"
#include "../headers/io.h"

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

		vector<competence> skills = creation.getSkillVect();

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

						if(nbSeparateur < 4) //Recherche du champ compétence sur la ligne
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


	vector <Carte> loadAllCarteFromFile(string nomFichier)
	{
		vector<Carte> selectionnable ;
		ifstream fichier(nomFichier, ios :: in) ;

		if (fichier)
		{
			string current_line;

	//cerr << "1" << endl ;
	//cerr << "current_line : " << current_line << endl ;
			while (getline(fichier, current_line))
			{
	//cerr << "2" << endl ;
				bool init = false;
				bool fait = false ;
				Carte carte_temporaire ;
				string id = "" ;
				string nom = "" ;
				string description = "" ;
				string taille= "";
				string coordonnee1 = "" ;
				string coordonnee2 = "" ;
				string type = "" ;
				int count_c = 0 ;
				int count_coordonnee = 0 ;
				int i = 0 ;
	//cerr << "id : " << id << endl ;
	//cerr << "nom : " << nom << endl ;
	//cerr << "description : " << description << endl ;
	//cerr << "taille : " << taille << endl ;
	//cerr << "coordonnée 1 : " << coordonnee1 << endl ;
	//cerr << "coordonnée 2 : " << coordonnee2 << endl ;
	//cerr << "type : " << type << endl ;
	//cerr << "count_c : " << count_c << endl ;
	//cerr << "count_coordonnee : " << count_coordonnee << endl ;
	//cerr << "i : " << i << endl ;
				while (current_line[i+1] != '\0')
				{
					char tmp = current_line[i] ;
	//cerr << "3" << endl ;
	//cerr << "tmp : " << tmp << endl ;
					if (tmp == '|')
					{
						count_c++ ;
						i++ ;
	//cerr << "4_1 : " << endl ;
	//cerr << "count_c : " << count_c << endl ;
	//cerr << "i : " << i << endl ;
					}
					else if (count_c == 0)
					{
						id = id + tmp ;
						i++ ;
	//cerr << "4_2 : " << endl ;
	//cerr << "id : " << id << endl ;
	//cerr << "i : " << i << endl ;
					}
					else if (count_c == 1)
					{
						nom = nom + tmp ;
						i++ ;
	//cerr << "4_3 : " << endl ;
	//cerr << "nom : " << nom << endl ;
	//cerr << "i : " << i << endl ;
					}
					else if (count_c == 2)
					{
						description = description + tmp ;
						i++ ;
	//cerr << "4_4 : " << endl ;
	//cerr << "description : " << description << endl ;
	//cerr << "i : " << i << endl ;
					}
					else if (count_c == 3)
					{
						taille = taille + tmp ;
						i++ ;
	//cerr << "4_5 : " << endl ;
	//cerr << "taille : " << taille << endl ;
	//cerr << "i : " << i << endl ;
					}
	//cerr << "5 : " << endl ;
	//cerr << "t : " << t << endl ;
	//cerr << "taille : " << carte_temporaire.taille << endl ;
	//cerr << "nom : " << carte_temporaire.nom << endl ;
	//cerr << "description : " << carte_temporaire.description << endl ;
					if (count_c == 4)
					{
					int t = atoi(taille.c_str());

					if (init == false)
					{
						init = true;
						carte_temporaire.setName(nom);
						carte_temporaire.setDescription(description);
						carte_temporaire.setPlateau(t);

					}

	//cerr << "6 : " << endl ;
	//cerr << "count_c : " << count_c << endl ;
						if (fait)
						{
							type = "";
							coordonnee1 = "" ;
							coordonnee2 = "" ;
							if (current_line[i+1] != '\0') fait = false ;
						}
						else if (tmp == ')')
						{
							fait = true ;
							count_coordonnee = 0 ;
							i++ ;
							int coor1 = atoi(coordonnee1.c_str()) ;
							int coor2 = atoi(coordonnee2.c_str()) ;
							carte_temporaire.setCase(coor1, coor2, type);

	//cerr << "7_1 : " << endl ;
	//cerr << "count_c_coordonnee : " << count_c_coordonnee << endl ;
	//cerr << "i : " << i << endl ;
	//cerr << "coor1 : " << coor1 << endl ;
	//cerr << "coor2 : " << coor2 << endl ;
	//cerr << "plateau : " << carte_temporaire.plateau[coor1][coor2] << endl ;

						}
						else if (tmp == ',')
						{
							count_coordonnee ++ ;
							i++ ;
	//cerr << "7_2 : " << endl ;for (int i = 0; i < taille; i++)
	//cerr << "count_coordonnee : " << count_coordonnee << endl ;
	//cerr << "i : " << i << endl ;
						}
						else if (tmp == '(')
						{
							i ++ ;
	//cerr << "7_3 : " << endl ;
	//cerr << "i : " << i << endl ;
						}
						else if ((tmp != '(') && (tmp != ')') && (tmp != ','))
						{
	//cerr << "7_4 : " << endl ;
							if (count_coordonnee == 0)
							{
								coordonnee1 = coordonnee1 + tmp ;
								i ++ ;
	//cerr << "7_4_1 : " << endl ;
	//cerr << "coordonnée 1 : " << coordonnee1 << endl ;
	//cerr << "i : " << i << endl ;
							}
							else if (count_coordonnee == 1)
							{
								coordonnee2 = coordonnee2 + tmp ;
								i++ ;
	//cerr << "7_4_2 : " << endl ;
	//cerr << "coordonnée 2 : " << coordonnee2 << endl ;
	//cerr << "i : " << i << endl ;
							}
							else if (count_coordonnee == 2)
							{
								type = type + tmp ;
								i++ ;
	//cerr << "7_4_3 : " << endl ;
	//cerr << "type : " << type << endl ;
	//cerr << "i : " << i << endl ;
							}
						}
					}
				}


	//cerr << "enregistrement dans selectionnable" << endl ;
				selectionnable.push_back(carte_temporaire) ;

	//			for (int i = 0; i < carte_temporaire.taille; i++)
	//			{
	//				for (int j = 0; j < carte_temporaire.taille; j++)
	//				{
	//					cout << carte_temporaire.plateau[i][j];
	//				}
	//				cout << endl;
	//			}
			}
		}
		return selectionnable ;
	}
}
