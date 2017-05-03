#include "../headers/monstre.h"
#include <iostream>
#include <fstream>

using namespace std;

int monstre::nbElemProt = 3;

monstre::monstre()
{
	entite();
	this -> entiteId = "m";
}
