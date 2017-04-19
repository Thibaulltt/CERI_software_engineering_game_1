#include <string>
#include <vector>
#include "competence.h"

class monstre
{
    string name;
    int hpMax;
    int hpCurrent;
    int speed;
    bool alive;

public:
    vector<competence> skillVect; //Pour test, à modifier

    monstre(); //Constructeut vide
    monstre(string name, int hpMax, int speed); //Constructeur avec carac d'un monstre
    monstre (string name, int hpMax, int speed, vector<competence> allSkills); //Constructeur avec les compétences
    void saveInFile(); //Permet d'écrire le monstre dans un fichier de sauvegarde
    void printMonstre(); // Pour tester
    template<typename T>string toString(const T & valeur); // Conversion de n'importe quoi en string
    int nbLigneFichier(); //Compte le nb de ligne du fichier pour créer l'identifiant unique d'un monstre
    string monstreString(); //

    bool enleverVie(int degats);




};
