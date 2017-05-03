#include "../headers/personnage.h"
#include <fstream>

using namespace std;

int personnage::nbElemProt = 0;

personnage::personnage()
{
	entite();
	this -> entiteId = "p";
}

void personnage::printPersonnage()
{
	cout << "Nom: " << this->entiteName<< endl;
	cout << "HP: " << this->entiteHpCurrent << "/" << this->entiteHpMax;
	cout << "Vitesse: " << this->entiteSpeed<< endl;
	cout << "MP: " << this->entiteManaCurrent << "/" << this->entiteManaMax;
	cout << "Description: " <<this->entiteDescription<<endl;

	cout << endl << "Compétences: " << endl;

	for (int i=0 ; i<3 ; i++)
	{
		this->entiteSkillVect[i].afficher_detail();
	}

	cout << endl;
}
