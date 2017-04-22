#include "../headers/personnage.h"
#include <fstream>

using namespace std;


//FONCTIONS DE TEST



void personnage::printPersonnage()
{
	cout << "nom : " << this->entiteName<< endl;
	cout << "hp max : " << this->entiteHpMax<< endl;
	cout << "entiteSpeed : " << this->entiteSpeed<< endl;
	cout << "mana max : " << this->entiteManaMax<<endl;
	cout << "entiteDescription : " <<this->entiteDescription<<endl;

	for (int i=0 ; i<3 ; i++)
	{
		this->entiteSkillVect[i].printCompetence();
	}

	cout << endl;
}
