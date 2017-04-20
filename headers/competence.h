 #include <string>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class competence
{
    string skillName;
    int damage;
    int manaCost;
public:
    competence();
    competence(string skillName, int damage, int manaCost);
    competence(string skillName, int damage);

    void printCompetence();
    template<typename T>string toString(const T & valeur);
    string competenceString();

};
