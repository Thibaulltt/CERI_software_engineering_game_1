#include <vector>
#include <termios.h>	// Needed for terminal input manipulation
#include <stdio.h>	// Needed for terminal input manipulation
#include <fstream>
#include <iostream>
#include "../headers/carte.h"
#include "../headers/io.h"

using namespace std;

namespace io
{
	// Variable :

	int TermWidth = 0;
	int TermHeight = 0;

	string BLANK = "\033[0m";
	string RED = "\033[91m";
	string GREEN = "\033[92m";
	string YELLOW = "\033[93m";
	string BLUE = "\033[94m";
	string MAGENTA = "\033[95m";

	int mapPositionX = 0;
	int mapPositionY = 0;

	int interactionsOverlayX = 0;

	std::pair<int,int> currentPlayerPosition(0,0);

	///////////////////////////////////////////////////
	/////////// FONCTIONS LIEES AU TERMINAL ///////////
	///////////////////////////////////////////////////

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
		ch = getchar();				// getchar() ne prends qu'un caractère
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
			{
				if (input.tellp() > 0)
					printf("\033[2D");
				else
					printf("\033[1D");
				removeLastChar(input);
			}
		} while(charInput != 10);
		ResetTerminal();
		return input.str().length() == 1 ? long_input() : input.str();
	}

	void removeLastChar(std::stringstream& input)
	{
		std::stringstream str;
		// Mode opératoire #1
		std::string s = input.str();
		// Mode opératoire #2
		if (s.size() != 0)
		{
			// Mode opératoire #2.a
			printf(" ");
			printf("\033[1D");
			// Mode opératoire #2.b
			s.erase(s.end()-1);
			// Mode opératoire #2.c
			input.str("");
			// Mode opératoire #2.d
			input << s;
		}
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
		{
			io::TermWidth = std::stoi(w2.substr(0,w2.size()-1));
			return io::TermWidth;
		}
		else
		{
			io::TermWidth = std::stoi(w1.substr(0,w1.size()-1));
			return io::TermWidth;
		}
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
		{
			io::TermHeight = std::stoi(h2.substr(0,h2.size()-1));
			return io::TermHeight;
		}
		else
		{
			io::TermHeight = std::stoi(h1.substr(0,h1.size()-1));
			return io::TermHeight;
		}
	}

	void clearScreen()
	{
		std::cout << '\n'*TermHeight;
	}

/*	void afficherCarte(Carte& c, int t)
	{
		// On prends le plateau en copie
		std::string ** map = c.plateau;					// ATTENTE D'UN PARTAGE DU PLATEAU

		// On (re)vérifie la taille du terminal
		checkTerminalSize();

		// On efface l'écran
		clearScreen();

		// Prendre la position de la carte
		// currentPlayerPosition = c.playerPosition();			// ATTENTE DE LA FONCTION

		// Si le joueur est plus bas que l'affichage de la carte
		while (currentPlayerPosition.first >= TermWidth)
			mapPositionX += TermWidth;

		// Si le joueur est plus sur la droite que la carte
		while (currentPlayerPosition.second >= TermHeight)
			mapPositionY += TermHeight;

		int displayX = mapPositionX;
		int displayY = mapPositionY;
		int TermPosX = 0;
		int TermPosY = 0;

		// On affiche les petites cases WUBBA LUBBA DUB DUB
		while (TermPosY < TermHeight && displayY < t)
		{
			while (TermPosX < TermWidth && displayX < t)
			{
				std::cout << map[displayX][displayY];		// RESTE A AJOUTER LA COULEUR
				TermPosX++;
				displayX++;
			}
			if (TermPosY != TermHeight-1)
				std::cout << std::endl;
			TermPosY++;
			TermPosX=0;
			displayY++;
			displayX=0;
		}
	}
*/
	void afficherMouvements()
	{													///////////////////////////////////
		afficherMouvements("");
	}

	void afficherMouvements(std::string erreur_deplacement)
	{													///////////////////////////////////
		// Si vous voulez changer le caractère délimiteur,
		// ainsi que la couleur de ces délimiteurs, faites
		// le ici.
		char delimiteur = '%';
		std::string couleurDelimiteur = BLUE;

		// Si le joueur est dans le bas de la carte, on affiche les
		// interactions possibles sur le haut de la fenêtre Terminal
		if (currentPlayerPosition.first >= (mapPositionY+TermHeight-5))
			interactionsOverlayX = 0;
		else
			interactionsOverlayX = (TermHeight - 5);

		if (erreur_deplacement.size() >= TermWidth-2)
			erreur_deplacement = "";

		std::string message_affiche = "Voici les déplacements possibles à ce point dans le jeu :";

		int deplacementNecessaire = (TermWidth - 2 - taille_str(message_affiche));

		// Pour une raison X ou Y, cet appel printf(positionDansTerminal) ne marchait pas.
		// ¯\_(ツ)_/¯
		std::string s = "printf \"\033["+std::to_string(interactionsOverlayX)+";0H\"";
		system(s.c_str());

		// Affiche une ligne entière de délimiteurs, à la couleur demandée.
		cout << couleurDelimiteur << std::string(TermWidth, delimiteur) << BLANK;

		// Affiche la deuxième ligne de l'overlay, qui demande le mouvement au joueur.
		cout << couleurDelimiteur << delimiteur << BLANK << std::string(deplacementNecessaire/2, ' ') << message_affiche << std::string(deplacementNecessaire/2+deplacementNecessaire%2, ' ') << couleurDelimiteur << delimiteur << BLANK << std::endl;

		// Affiche la troisième ligne de l'overlay, qui affiche les choix possibles aux joueurs.
		cout << couleurDelimiteur << delimiteur << BLANK << std::string(((TermWidth-46-2)/2), ' ') << " Z - Haut | Q - Gauche | S - Bas | D - Droite " << std::string(((TermWidth-46-2)/2)+(TermWidth%2), ' ') << couleurDelimiteur << delimiteur << BLANK << std::endl;

		cout << couleurDelimiteur << delimiteur << BLANK << std::string(TermWidth-2, ' ') << couleurDelimiteur << delimiteur << BLANK << std::endl;

		deplacementNecessaire = (TermWidth - 2 - taille_str(erreur_deplacement));

		// Affiche une ligne vide et / ou un message d'erreur.
		cout << couleurDelimiteur << delimiteur << BLANK << std::string(deplacementNecessaire/2, ' ') << erreur_deplacement << std::string(deplacementNecessaire/2+deplacementNecessaire%2, ' ') << couleurDelimiteur << delimiteur << BLANK << std::endl;

		// Affiche la ligne de fin.
		cout << couleurDelimiteur << std::string(TermWidth, delimiteur) << BLANK << '\r' << flush;

		// Remet le curseur dans l'overlay
		printf("\033[6A");			// Haut de deux lignes
		printf("\033[%dD", TermWidth - 2);	// Gauche de TermWidth-2 cases
	}

	void checkTerminalSize()
	{
		// Met à jour la taille du terminal
		getTerminalHeight();
		getTerminalWidth();
		while (TermHeight < 15 || TermWidth < 91)
		{
			std::cout << "Votre terminal n'est pas dimensionné correctement.";
			std::cout << "Veuillez redimensionner votre terminal afin d'avoir";
			std::cout << "une taille d'au moins 15 lignes par 91 colonnes." << std::endl;
			getTerminalWidth();
			getTerminalHeight();
		}
	}

	int taille_str(std::string s)
	{
		int j = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (int(s[i] < 0))
			{
				j++;
				i++;
			}
			else
				j++;
		}
		return j;
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
	bool checkSeparatorEntite(string uneLigne) //Retourne false si le nb de séparateurs dans une ligne n'est pas le nombre définit
	{
		int cptBarre=0;
		int cptSlash=0;
		char parcours;

		for (int i=0; i<uneLigne.length(); i++)
		{
			parcours = uneLigne[i];
			if(parcours=='/')
			{
				cptSlash++;
			}

			if(parcours=='|')
			{
				cptBarre++;
			}
		}

		if((cptSlash == 4) && (cptBarre == 3))
		{
			return true;
		}

		return false;
	}

	vector<competence> loadCompetenceFromFile(std::string nomFichier,int numLigne)
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
						carte_temporaire.setTaille(t);
						carte_temporaire.setName(nom);
						carte_temporaire.setDescription(description);
						carte_temporaire.setPlateau(t);
						///carte_temporaire.setNbrMonstre();
						///carte_temporaire.setCaseDispo();

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
