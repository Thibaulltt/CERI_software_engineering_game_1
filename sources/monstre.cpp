#include "../headers/monstre.h"
#include <iostream>
#include <fstream>

using namespace std;


// --------------------CONSTRUCTEURS



//-------------------------------------------FONCTIONS



// TESTS


void monstre::printMonstre()
{
	cout << "nom : " << this->entiteName<< endl;
	cout << "hp max : " << this->entiteHpMax<< endl;
	cout << "entiteSpeed : " << this->entiteSpeed<< endl;

	for (int i=0 ; i<this->entiteSkillVect.size() ; i++)
	{
		this->entiteSkillVect[i].printCompetence();
	}

	cout << endl;
}
