#include "../headers/monstre.h"
#include <iostream>
#include <fstream>

using namespace std;

int monstre::nbElemProt = 0;

monstre::monstre()
{
	entite();
	this -> entiteId = "m";
}

void monstre::printMonstre()
{
	cout << "Nom: " << this->entiteName<< endl;
	cout << "HP: " << this->entiteHpCurrent << "/" << this->entiteHpMax;
	cout << "Vitesse: " << this->entiteSpeed<< endl;

	cout << endl << "Compétences: " << endl;

	for (int i=0 ; i<this->entiteSkillVect.size() ; i++)
	{
		this->entiteSkillVect[i].afficher_detail();
	}

	cout << endl;
}
