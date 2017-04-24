#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <typeinfo>
#include "../headers/carte.h"
#include "../headers/fonctionsjeu.h"
#include "../headers/io.h"

using namespace io;
using namespace std;

int main()
{
	jeu a;

	a.preparation_partie();

//	a.deplacement();

	string monster = "m1";

	a.combat(monster);


	return 0;
}
