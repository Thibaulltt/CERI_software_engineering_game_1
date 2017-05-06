#include <fstream>
#include <iostream>
#include <stdio.h>	// Needed for terminal input manipulation
#include <termios.h>	// Needed for terminal input manipulation
#include <vector>
#include "../headers/carte.h"
#include "../headers/io.h"

using namespace std;

namespace io
{
	// Variables :

	int TermWidth = 0;
	int TermHeight = 0;

	string BLANK = "\033[0m";		// Séquences d'échappement
	string RED = "\033[91m";		// pour afficher des
	string GREEN = "\033[92m";		// couleurs sur un
	string YELLOW = "\033[93m";		// terminal configuré avec
	string BLUE = "\033[94m";		// xterm ou xterm-256 pour
	string MAGENTA = "\033[95m";		// l'affichage.

	int mapPositionX = 0;
	int mapPositionY = 0;

	int interactionsOverlayY = 0;

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
		if (ch == 27)
			throw 27;
		return ch;
	}

	std::string long_input()
	{
		std::string charRejette = "|/,:_()\177";		// Les caractères rejettés dans l'input.
		std::stringstream input;
		char charInput,deletedChar;
		ChangeTerminal(1);
		do {
			charInput = getchar();
			if (charInput == '\033')
				throw 27;
			if (charRejette.find(charInput) == std::string::npos)
				input << charInput;
			else
			{
				printf("\033[1D");
				std::cout << ' ';
				printf("\033[1D");
				if (input.tellp() > 0 && charInput == 127)
				{
					printf("\033[1D");
					removeLastChar(input);
				}
			}
		} while(charInput != 10);
		ResetTerminal();
		std::string resultat = input.str();
		if (int(resultat[resultat.size()-1]) == 10)
			resultat = resultat.substr(0,resultat.size()-1);
		return resultat.size() == 0 ? long_input() : resultat;
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
		for (int i = 0; i <= TermHeight+1; i++)
		cout << "\n";
	}

	void afficherCarte(Carte& c, int t, bool reset)
	{
		// On prends le plateau en copie
		std::string ** map = c.getPlateau();

		try
		{
			// On (re)vérifie la taille du terminal
			checkTerminalSize();
		}
		catch (int checkTerminalError)
		{
			throw checkTerminalError;
		}

		getTerminalWidth();
		getTerminalHeight();

		// Si le joueur est plus bas que l'affichage de la carte
		while (currentPlayerPosition.first >= mapPositionX+TermWidth)
			mapPositionX += TermWidth;
		while (currentPlayerPosition.first < mapPositionX)
			mapPositionX -= TermWidth;

		// Si le joueur est plus sur la droite que la carte
		while (currentPlayerPosition.second >= mapPositionY+TermHeight-6)
			mapPositionY += TermHeight-6;
		while (currentPlayerPosition.second < mapPositionY)
			mapPositionY -= TermHeight-6;

		int displayX = mapPositionX;
		int displayY = mapPositionY;
		int TermPosX = 0;
		int TermPosY = 0;

		if (reset == 1)
		{
			// On efface l'écran
			clearScreen();
		}
		else
			printf("\033[1;1H");

		printf("\033[1;1H");	// Remet le curseur au debut

		// On affiche les petites cases WUBBA LUBBA DUB DUB
		while (TermPosY < TermHeight - 6 && displayY < t)
		{
			while (TermPosX < TermWidth && displayX < t)
			{
				if (map[displayX][displayY] == "joueur")
					std::cout << RED << 'X' << BLANK;
				else if (map[displayX][displayY][0] == 'm')
					std::cout << BLUE << ' ' << BLANK;
				else if (map[displayX][displayY][0] == 'a')
					std::cout << GREEN << 'A' << BLANK;
				else if (map[displayX][displayY][0] == 'e')
					std::cout << BLUE << '~' << BLANK;
				else
					std::cout << ' ';
				TermPosX++;
				displayX++;
			}
			while (TermPosX < TermWidth - 1)
			{
				std::cout << ' ';
				TermPosX++;
			}
			if (TermPosY != TermHeight-7)
				std::cout << std::endl;
			TermPosY++;
			TermPosX=0;
			displayY++;
			displayX=mapPositionX;
		}
	}

	void updateMap(Carte& jeu_carte, std::pair<int,int> newPlayerPos)
	{
		int x = currentPlayerPosition.first;
		int y = currentPlayerPosition.second;
		// Si le joueur sort des "barrières" de la map affichée
		if (    newPlayerPos.first >= mapPositionY + TermHeight - 6
			|| newPlayerPos.first < mapPositionY
			|| newPlayerPos.second >= mapPositionX + TermWidth
			|| newPlayerPos.second < mapPositionX)
		{
			jeu_carte.echangerContenuCase(currentPlayerPosition.first, currentPlayerPosition.second, newPlayerPos.second, newPlayerPos.first);
			currentPlayerPosition.first = newPlayerPos.second;
			currentPlayerPosition.second = newPlayerPos.first;
			try
			{
				afficherCarte(jeu_carte, jeu_carte.getTaille(),0);
			}
			catch (int afficherCarteError)
			{
				throw afficherCarteError;
			}
			return;
		}
		jeu_carte.echangerContenuCase(currentPlayerPosition.first, currentPlayerPosition.second, newPlayerPos.second, newPlayerPos.first);
		printf("\033[0;0H");
		if (currentPlayerPosition.second != mapPositionY)
			printf("\033[%iB", currentPlayerPosition.second - mapPositionY);
		printf("\033[%iC", currentPlayerPosition.first - mapPositionX);
		if (currentPlayerPosition.first == mapPositionX)
			printf("\033[1D");
		switch (jeu_carte.getPlateau()[x][y][0])
		{
			case 'x':
				cout << RED << 'x' << BLANK << flush;
				break;
			default:
				cout << BLANK << ' ' << BLANK << flush;
				break;
		}
		printf("\033[0;0H");
		if (newPlayerPos.first != mapPositionY)
			printf("\033[%iB", newPlayerPos.first - mapPositionY);
		printf("\033[%iC", newPlayerPos.second - mapPositionX);
		if (newPlayerPos.second == mapPositionX)
			printf("\033[1D");
		cout << RED << 'X' << BLANK << flush;
		currentPlayerPosition.first = newPlayerPos.second;
		currentPlayerPosition.second = newPlayerPos.first;
		return;
	}

	void afficherMouvements()
	{
		afficherMouvements("Z - Haut | Q - Gauche | S - Bas | D - Droite","");
	}

	void afficherMouvements(std::string s)
	{
		afficherMouvements("Z - Haut | Q - Gauche | S - Bas | D - Droite",s);
	}

	void afficherMouvements(std::string deplacements_possibles, std::string erreur_deplacement)
	{
		afficherMouvements("Voici les déplacements possibles à ce point là :",deplacements_possibles,erreur_deplacement);
	}

	void afficherMouvements(std::string message, std::string deplacements_possibles, std::string erreur_deplacement)
	{
		// Dans cette fonction, les sorties utilisées avec std::cout sont
		// mises à la ligne après chaque élément pour pouvoir faciliter
		// la lecture du code.

		// Si vous voulez changer le caractère délimiteur,
		// ainsi que la couleur de ces délimiteurs, faites
		// le ici.
		char delimiteur = '%';
		std::string couleurDelimiteur = BLUE;

		// Si le joueur est dans le bas de la carte, on affiche les
		// interactions possibles sur le haut de la fenêtre Terminal
		interactionsOverlayY = (TermHeight - 5);
		printf("\033[%i;0H", interactionsOverlayY);

		// Si le message d'accueil est trop grand, on le coupe
		if (message.size() > TermWidth-2)
			message = message.substr(0,TermWidth-2-3)+"...";

		// Si le message d'erreur est trop grand, on le coupe
		if (erreur_deplacement.size() > TermWidth-2)
			erreur_deplacement = erreur_deplacement.substr(0,TermWidth-2-3)+"...";

		int deplacementNecessaire;

		// Pour une raison X ou Y, cet appel printf(positionDansTerminal) ne marchait pas.
		// ¯\_(ツ)_/¯ .Je pense que c'est plutôt pour la raison Y, mais ça n'engage que moi

		// Affiche une ligne entière de délimiteurs, à la couleur demandée.
		cout << couleurDelimiteur;
		cout << std::string(TermWidth, delimiteur);
		cout << BLANK;

		// Calcule la place à allouer sur chaque côté
		deplacementNecessaire = (TermWidth - 2 - taille_str(message));

		// Affiche la deuxième ligne de l'overlay, qui demande le mouvement au joueur.
		cout << couleurDelimiteur;
		cout << delimiteur;
		cout << BLANK;
		cout << std::string(deplacementNecessaire/2, ' ');
		cout << message;
		cout << std::string(deplacementNecessaire/2 + deplacementNecessaire%2, ' ');
		cout << couleurDelimiteur;
		cout << delimiteur;
		cout << BLANK;
		cout << std::endl;

		// Calcule la place à allouer sur châque côté du message
		deplacementNecessaire = (TermWidth - 2 - taille_str(deplacements_possibles));

		// Affiche la troisième ligne de l'overlay, qui affiche les choix possibles aux joueurs.
		cout << couleurDelimiteur;
		cout << delimiteur;
		cout << BLANK;
		cout << std::string(deplacementNecessaire/2, ' ');
		cout << deplacements_possibles;
		cout << std::string(deplacementNecessaire/2 + deplacementNecessaire%2, ' ');
		cout << couleurDelimiteur;
		cout << delimiteur;
		cout << BLANK;
		cout << std::endl;

		cout << couleurDelimiteur;
		cout << delimiteur;
		cout << BLANK;
		cout << std::string(TermWidth-2, ' ');
		cout << couleurDelimiteur;
		cout << delimiteur;
		cout << BLANK;
		cout << std::endl;

		// Calcule la place à allouer sur châque côté du message
		deplacementNecessaire = (TermWidth - 2 - taille_str(erreur_deplacement));

		// Affiche une ligne vide et / ou un message d'erreur.
		cout << couleurDelimiteur;
		cout << delimiteur;
		cout << BLANK;
		cout << std::string(deplacementNecessaire/2, ' ');
		cout << erreur_deplacement;
		cout << std::string(deplacementNecessaire/2 + deplacementNecessaire%2, ' ');
		cout << couleurDelimiteur;
		cout << delimiteur;
		cout << BLANK;
		cout << std::endl;

		// Affiche la ligne de fin.
		cout << couleurDelimiteur;
		cout << std::string(TermWidth, delimiteur);
		cout << BLANK;
		cout << '\r';
		cout << flush;

		// Remet le curseur dans l'overlay
		printf("\033[2A");			// Haut de deux lignes
		printf("\033[%dC", TermWidth/2);	// Droite de TermWidth-2 cases
	}

	void updateMessage(std::string nouveauMessage, int pos)
	{
		if (pos <= 0 || pos > 4)
			pos = 3;
		// Variables utilisées ici
		int messagePositionY = TermHeight-5+pos;
		char delimiteur = '%';
		std::string couleurDelimiteur = BLUE;

		if (nouveauMessage.size() > TermWidth-2)
			nouveauMessage = nouveauMessage.substr(0,TermWidth - 5)+"...";

		int deplacementNecessaire = TermWidth - 2 - nouveauMessage.size();

		// On remet le curseur au debut du terminal
		// printf("\033[1;1H");
		// On descend jusqu'à la ligne demandée
		printf("\033[%i;1H", messagePositionY);

		// On affiche
		cout << couleurDelimiteur;
		cout << delimiteur;
		cout << BLANK;
		cout << std::string(deplacementNecessaire/2, ' ');
		cout << nouveauMessage;
		cout << std::string(deplacementNecessaire/2 + deplacementNecessaire%2, ' ');
		cout << couleurDelimiteur;
		cout << delimiteur;
		cout << BLANK;
		cout << '\r';

		// On remet le curseur au milieu du message
		printf("\033[%d;1H", TermHeight);
		printf("\033[2A");
		printf("\033[%dC", TermWidth/2);
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
			try
			{
				de();
			}
			catch (int deError)
			{
				throw deError;
			}
		}
	}

	int taille_str(std::string s)
	{
		int j = 0;				// Initialise la taille à 0
		for (int i = 0; i < s.size(); i++)	// Boucle dans la chaîne
		{
			if (int(s[i] < 0))		// Si le caractère n'est pas en ASCII
			{
				j++;			// On le compte un caractère
				i++;			// On saute le prochain caractère
			}
			else
				j++;			// On compte un caractère
		}
		return j;
	}

	void setPlayerPosition(int i, int j)
 	{
 		currentPlayerPosition = std::make_pair(i,j);
 	}

	void bienvenue()
	{
		getTerminalWidth();
		getTerminalHeight();
		clearScreen();
		printf("\033[1;1H");
		std::puts("\n");
		printf("\033[%dC", ((TermWidth-92)/2)-1); std::puts("                                         Welcome to");
		printf("\033[%dC", ((TermWidth-92)/2)-1); std::puts(" __________   ___    ___   __________     __________   __________   __     ___   __________");
		printf("\033[%dC", ((TermWidth-92)/2)-1); std::puts("/___   ___/  /  /   /  /  /  _______/    /  _______/  /  ____   /  /  \\__ /  /  /  _______/");
		printf("\033[%dC", ((TermWidth-92)/2)-1); std::puts("   /  /     /  /__ /  /  /  /__         /  /  __     /  /___/  /  /         /  /  /__");
		printf("\033[%dC", ((TermWidth-92)/2)-1); std::puts("  /  /     /   __    /  /   __/        /  /  /  \\   /  ____   /  /  / - /  /  /   __/");
		printf("\033[%dC", ((TermWidth-92)/2)-1); std::puts(" /  /     /  /   /  /  /  /______     /  /___/  /  /  /   /  /  /  /   /  /  /  /______");
		printf("\033[%dC", ((TermWidth-92)/2)-1); std::puts("/_ /     /_ /   /_ /  /_________/    /_________/  /_ /   /_ /  /_ /   /_ /  /_________/");
		std::puts("\n");

		printf("\033[%dC", ((TermWidth-96)/2)-1); std::puts("Dans The Game,vous devez débusquer et tuer tous les monstres présents sur la carte.Bonne chance!");
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

	void aff_combat(vector<entite> vect_entite)
	{
		for (int i = 0; i < vect_entite.size(); i++)
		{
			if (vect_entite[i].is_personnage())
			{
				std::pair<std::string,std::string> res = vect_entite[i].afficher_combat();
				updateMessage(res.first,1);
				updateMessage(res.second,2);
			}
		}

		for (int i = 0; i < vect_entite.size(); i++)
		{
			if (!vect_entite[i].is_personnage())
			{
				std::pair<std::string,std::string> res = vect_entite[i].afficher_combat();
				updateMessage(res.first,3);
				updateMessage("Choisissez une action avec [1-4]",4);
			}
		}
	}

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

	bool checkSeparatorSkill(std::string nomFichier, int numLigne) //Retourne false si le nb de séparateurs dans un champ de compétence n'est pas le nombre définit
	{
		int nbSeparateur = 0;

		string laLigne="";

		char parcoursSkill;
		int cptLigne=0;
		int nbParentheseO=0;
		int nbParentheseF=0;
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

							if (parcoursSkill == '(')
							{
								nbParentheseO++;
							}

							if (parcoursSkill == ')')
							{
								nbParentheseF++;
							}

							if (parcoursSkill == '_')
							{
								nbUnderscore++;
							}

							if (parcoursSkill == ':') //Fin de l'analyse d'une compétence
							{
								if((nbParentheseO == 1) && (nbParentheseF == 1) && (nbUnderscore == 1)) //Verification bon nb de séparateurs
								{
									nbParentheseO=0; //Reset des compteurs
									nbParentheseF=0;
									nbUnderscore=0;
									continue;
								}
								else
								{
									return false;
								}

							}
							if (parcoursSkill== '|') //Fin du champ compétence
							{
								return true;
							}
						}
					}
				}
			}
			fichierMonstre.close();
		}
	}

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
		// Carte par défaut
		Carte defaut(5, "defaut", "carte par défaut", 1);
		defaut.setCase(4,4,"joueur");
		defaut.setCase(2,0,"m0");
		defaut.setCase(1,3,"arbre");
 		selectionnable.push_back(defaut);

		Carte::nbElemProt = 1;

		ifstream fichier(nomFichier, ios :: in) ;

		if (fichier)
		{
			string current_line;
			while (getline(fichier, current_line))
			{
				string id, nom, description, taille, nbr_monstre, coordonnee1, coordonnee2, type = "" ;
				int i = 0 ;
				std::stringstream entree;
				// Prise ID
				while (current_line[i] != '|')
					entree << current_line[i++];
				i++;
				id = entree.str();
				entree.str("");
				// Prise NOM
				while (current_line[i] != '|')
					entree << current_line[i++];
				i++;
				nom = entree.str();
				entree.str("");
				// Prise DESCRIPTION
				while (current_line[i] != '|')
					entree << current_line[i++];
				i++;
				description = entree.str();
				entree.str("");
				// Prise TAILLE
				while (current_line[i] != '|')
					entree << current_line[i++];
				i++;
				taille = entree.str();
				entree.str("");
				// Prise NOMBRE DE MONSTRE
				while (current_line[i] != '|')
					entree << current_line[i++];
				i++;
				nbr_monstre = entree.str();
				entree.str("");
				int t = atoi(taille.c_str());
				int nb_m = atoi(nbr_monstre.c_str());

				Carte carte_temporaire(t, nom, description, nb_m);

				// Prise obstacles
				while (i < current_line.size() && current_line[i+1] != '\0')
				{
					i++;	// Saute la première parenthèse
					// Coordonnée 1 : depuis la position actuelle jusqu'à la première virgule
					int coor1 = atoi( ( current_line.substr( i, current_line.find(",", i)-1 ).c_str() ) );
					// Coordonnée 2 : depuis la première virgule jusqu'à la deuxième virgule
					int coor2 = atoi( ( current_line.substr( current_line.find(",", i)+1, current_line.find(",", current_line.find(",", i)+1)-1 ).c_str() ) );
					i = current_line.find(",", current_line.find(",", i)+1);i++;	// On met le 'i' après les deux coordonnées trouvées
					// Prise nom obstacle
					while (current_line[i] != ')')
						entree << current_line[i++];
					i++;	// Passe après la deuxième parenthèse
					type = entree.str();
					entree.str("");
					carte_temporaire.setCase(coor1,coor2,type);
				}
				selectionnable.push_back(carte_temporaire) ;
			}
		}
		return selectionnable ;
	}

	int To_int(string input)
	{
		stringstream ss (input);
		int output = 0;

		while (ss >> output || !ss.eof())
		{
			if (ss.fail())
			{
				ss.clear();
				string nether;
				ss >> nether;
				continue;
			}
		}

		return output;
	}

	bool isNumber(string s_input)
	{
		for (int i = 0; i < s_input.size(); i++)
		{
			if (s_input[0] == '-')
			{
				continue;
			}

			if (!isdigit(s_input[i]))
			{
				return false;
			}
		}

		return true;
	}

}

bool checkSeparatorCarte(string uneLigne) //Retourne false si le nb de séparateurs dans une ligne n'est pas le nombre définit
{
	int cptBarre=0;
	char parcours;

	for (int i=0; i<uneLigne.length(); i++)
	{
		parcours = uneLigne[i];

		if(parcours=='|')
		{
			cptBarre++;
		}
	}

	if(cptBarre == 5)
	{
		return true;
	}

	return false;
}

bool checkSeparatorCoordonnee(std::string nomFichier, int numLigne) //Retourne false si le nb de séparateurs dans un champ de compétence n'est pas le nombre définit
{
	int nbSeparateur = 0;

	string laLigne="";

	char parcoursCoordonnee;
	int cptLigne=0;
	int nbParentheseO=0;
	int nbParentheseF=0;
	int nbVirgules=0;

	ifstream fichierCarte(nomFichier.c_str(), ios::in); //Ouverture en mode lecture

	if(fichierCarte)
	{
		while (getline(fichierCarte, laLigne)) //Parcours des lignes
		{
			cptLigne++;
			if (cptLigne==numLigne) //Si on est sur la ligne recherchée
			{
				for(int i=0; i<laLigne.length() ; i++) //Boucle de parcours de toute la ligne
				{
					parcoursCoordonnee = laLigne[i]; //Variable de parcours de la ligne

					if(nbSeparateur < 5) //Recherche du champ compétence sur la ligne
					{
						if (parcoursCoordonnee == '|')
						{
							nbSeparateur++;
						}
					}

					if (nbSeparateur==5) //Si le curseur est sur le champ compétence.
					{

						if (parcoursCoordonnee == '(')
						{
							nbParentheseO++;
						}
						if (parcoursCoordonnee == ',')
						{
							nbVirgules++;
						}
						if (parcoursCoordonnee == ')')
						{
							nbParentheseF++;
							if((nbParentheseO == 1) && (nbParentheseF == 1) && (nbVirgules == 2)) //Verification bon nb de séparateurs
							{
								nbParentheseO=0; //Reset des compteurs
								nbParentheseF=0;
								nbVirgules=0;
								continue;
							}
							else
							{
								return false;
							}

						}
						if (parcoursCoordonnee== '\0') //Fin du champ compétence
						{
							return true;
						}
					}
				}
			}
		}
	}
}
