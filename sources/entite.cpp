#include <fstream>
#include <iostream>
#include "../headers/entite.h"
#include "../headers/io.h"

using namespace io;
using namespace std;


// --------------------CONSTRUCTEURS

entite::entite()      //Constructeur vide
{
	this->entiteId="";
	this->entiteName = "Inconnu";
	this->entiteDescription = "";
	this->entiteHpMax = 0;
	this->entiteHpCurrent = 0;
	this->entiteManaMax = 0;
	this->entiteManaCurrent = 0;
	this->entiteSpeed = 0;
	this->entiteAlive = true;
	vector<competence> entiteSkillVect;
}


entite::entite(string entiteId, string entiteName, int entiteHpMax, int entiteSpeed, int entiteManaMax, string entiteDescription, std::vector<competence> allSkills) //Constructeur avec arguments de caractéristiques du entite
{
	this->entiteId=entiteId;
	this->entiteName = entiteName;
	this->entiteDescription = entiteDescription;
	this->entiteHpMax = entiteHpMax;
	this->entiteHpCurrent = entiteHpMax;
	this->entiteManaMax = entiteManaMax;
	this->entiteManaCurrent = entiteManaMax;
	this->entiteSpeed = entiteSpeed;
	this->entiteAlive = true;
	this->entiteSkillVect = allSkills;
}


//-------------------------------------------FONCTIONS


//-----GET ATTRIBUTS

string entite::getID() //Rretourne l'id d'une entite
{
	return this->entiteId;
}


string entite::getName() //Retourne le nom d'une entite
{
	return this->entiteName;
}


string entite::getDescription() //Retourne la description d'une entite
{
	return this->entiteDescription;
}


int entite::getHpMax() //Retourne le nombre de points de vie max d'une entite
{
	return this->entiteHpMax;
}


int entite::getHpCurrent() //Retourne le nombre de points de vie actuel d'une entite
{
	return this->entiteHpCurrent;
}


int entite::getManaMax() //Retourne les points de mana MAX d'une entite
{
	return this->entiteManaMax;
}

int entite::getManaCurrent() //Retourne les points de mana actuels d'une entite
{
	return this->entiteManaCurrent;
}


int entite::getSpeed() //Retourne la vitesse d'une entite
{
	return this->entiteSpeed;
}


bool entite::getAlive() //Retourne l'état de vie ou de mort d'une entite
{
	return this->entiteAlive;
}


vector<competence> entite::getSkillVect() //Retourne le vecteur de compétences d'un entite
{
	return this->entiteSkillVect;
}

void entite::setHpCurrent(int current)
{
	entiteHpCurrent = current;
}

void entite::setManaCurrent(int current)
{
	entiteManaCurrent = current;
}


// POUR SAUVEGARDE DANS FICHIER


int entite::nbLigneFichier(string nomFichier) //Compte le nb de lignes du fichier pour créer l'identifiant unique d'un entite
{
	ifstream fichier(nomFichier.c_str()); //Ouverture en mode lecture
	int nbLigne = 0;
	if(fichier)
	{
		string ligne="";

		while(getline(fichier, ligne)) //Stockage de chaque ligne du fichier
		{
			nbLigne++;
		}
		fichier.close(); //On ferme le fichier
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}

	return nbLigne;
}


string entite::entiteString(string lettreEntite, string nomFichier) //Convertit toutes les caracs. d'un entite en string
{
	string ligneFichier;

	int nbEntite = this->nbLigneFichier(nomFichier.c_str());
	string sNbEntite;
	sNbEntite = toString(nbEntite);

	string entiteId;
	entiteId = lettreEntite + sNbEntite;

	string sentiteHpMax;
	sentiteHpMax = toString(this->entiteHpMax);

	string sentiteSpeed;
	sentiteSpeed = toString(this->entiteSpeed);

	string sentiteManaMax;
	sentiteManaMax = toString(this->entiteManaMax);

	string allSkill="";
	for (int i=0 ; i< entiteSkillVect.size() ; i++) //Conversion de toutes les compétences en une ligne de string
	{
		allSkill += entiteSkillVect[i].competenceString() + ":";
	}

	ligneFichier = entiteId + "/" + this->entiteName + "/" + sentiteHpMax + "/" + sentiteSpeed + "/" + allSkill + "|" + sentiteManaMax + "|" + this->entiteDescription + "|" + "\r\n"; //Création de la ligne compléte

	return ligneFichier;
}

void entite::saveInFile(string lettreEntite,string nomFichier) //Ecrit les carac d'un entite dans un fichier
{
	ofstream fichierentite(nomFichier.c_str(), ios::out | ios::app); // Ouverture du fichier en écriture, avec curseur en fin de fichier.

	string entiteLigne = this->entiteString(lettreEntite, nomFichier);

	if(fichierentite) //Vérification ouverture du fichier
	{
		fichierentite << entiteLigne; //Ecriture de la ligne
		fichierentite.close();
	}

	else
	{
		cerr << "Impossible d'ouvrir le fichier." << endl;
	}
}


// FONCTIONS

bool entite::is_personnage()
{
	if (getID().substr(0, 1) == "p")
	{
		return true;
	}
	return false;
}

bool entite::is_monstre()
{
	if (getID().substr(0, 1) == "m")
	{
		return true;
	}
	return false;
}

entite entite::enleverVie(int degats)
{


	this->entiteHpCurrent-=degats;

	if(this->entiteHpCurrent <= 0)
	{
		this->entiteAlive = false;
	}

	return * this;
}


bool entite::enleverMana(int skillManaCost)
{
	if (this->entiteManaCurrent >= skillManaCost)
	{
		this->entiteManaCurrent -= skillManaCost;
		return true;
	}
	return false;
}


int entite::randomizeDegat(int damage, int fumbleChance, int critChance)
{
	int dice = (rand() % 100) + 1;	//Valeur entre 1 et la range choisie

	if (dice <= fumbleChance)	//On fait un fumble!
	{
		damage /= 2;
	}
	else if (dice >= 100 - critChance)	//On fait un critique!
	{
		damage *= 2;
	}

	return damage;
}

// TESTS

void entite::afficher_detail()
{
	cout << endl << endl << "Détails de l'entité " << this->entiteName << endl << endl;

	cout << "HP: " << this->entiteHpMax << endl;
	cout << "MP: " << this->entiteManaMax << endl;

	if (this->entiteDescription != "")
	{
		cout << endl << "Description: " << this->entiteDescription << endl;
	}

	cout << endl << "Compétences: " << endl << endl;

	for (int i = 0; i < entiteSkillVect.size(); i++)
	{
		this->entiteSkillVect[i].afficher_detail();
		cout << endl;
	}

	cout << endl << endl;
}

void entite::afficher_combat()
{
	string vie;
	vie.append("HP: ");
	vie.append(toString(entiteHpCurrent));
	vie.append("/");
	vie.append(toString(entiteHpMax));

	cout << endl << " " << entiteName << endl;
	cout << "" << vie << endl;

	if (this -> getID().substr(0, 1) != "m")
	{
		cout << "MP: " << entiteManaCurrent << "/" << entiteManaMax << endl;

		for (int i = 0; i < getSkillVect().size(); i++)
		{
			getSkillVect()[i].afficher_detail();
		}
	}
	cout << endl;
}


void entite::afficher_brut()
{
	cout << entiteName << ", " << entiteHpMax << "HP, " << entiteManaMax << "MP, vitesse " << entiteSpeed << endl;
}
