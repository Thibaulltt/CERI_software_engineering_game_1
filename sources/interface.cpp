#include "interface.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


bool interface::checkInput(int x) //Verifie que l'utilisateur entre bien un entier
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


competence interface::createCompetence() //Permet à l'utilisateur de créer une compétence pour personnage
{
    string skillName;
    int damage;
    int manaCost;

    cout << "Entrez le nom de la compétence : ";
    cin >> skillName;

    cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
    cin >> damage;
    while(!checkInput(damage))
    {
        cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
        cin >> damage;
    }

    cout << "Entrez le cout en mana de la competence : ";
    cin >> manaCost;
    while(!checkInput(manaCost))
    {
        cout << "Entrez le cout en mana de la competence : ";
        cin >> manaCost;
    }

    competence creation(skillName, damage, manaCost);

    return creation;
}

competence interface::createCompetenceMonstre() //Permet à l'utilisateur de créer une compétence pour monstre
{
    string skillName;
    int damage;
    int manaCost;

    cout << "Entrez le nom de la compétence : ";
    cin >> skillName;

    cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
    cin >> damage;
    while(!checkInput(damage))
    {
        cout << "Entrez le nombre de dommage de la compétence (chiffre négatif pour du soin) : ";
        cin >> damage;
    }

    competence creation(skillName, damage);

    return creation;
}


monstre interface::createMonstre() //Permet à l'utilisateur de créer un monstre avec des caractéristiques choisies
{
    string name;
    int hpMax;
    int speed;

    cout << "Entrez le nom du monstre : ";
    cin >> name;
    cout << endl;

    cout << "Entrez son nombre de points de vie : ";
    cin >> hpMax;
    while(!checkInput(hpMax))
    {
        cout << "Entrez son nombre de points de vie : ";
        cin >> hpMax;
    }

    cout << "Entrez sa vitesse : ";
    cin >> speed;
    while(!checkInput(speed))
    {
        cout << "Entrez sa vitesse : ";
        cin >> speed;
    }

    monstre creation(name, hpMax, speed); //Créé le monstre

    for (int i=0 ; i<3 ; i++) //Rempli le tableau de compétences avec de nouvelles compétences
    {
        // PREVOIR UN SWITCH POUR SAVOIR SI L'USER VEUT CONTINUER A RENTRER DES COMPETENCES
        // PENSER A CHANGER LE 3 DANS LA BOUCLE EN 11
       creation.skillVect.push_back(this->createCompetenceMonstre());
    }

    creation.printMonstre();

    creation.saveInFile(); //Le sauvegarde dans le fichier texte

    return creation;
}


vector<competence> interface::loadCompetenceFromFile()
{
    int nbSeparateur = 0;
    string sSkillName;
    string sDamage;

    vector<competence> allSkills;

    char parcoursSkill;

    ifstream fichierMonstre("fichierMonstre.txt", ios::in); //Ouverture en mode lecture

    if(fichierMonstre)
    {
        while (fichierMonstre.get(parcoursSkill)) //Parcours des caractéristiques
        {
            if(nbSeparateur <4)
            {
                if (parcoursSkill == '/')
                {
                    nbSeparateur++;
                }
            }

            if (nbSeparateur==4) //On déplace le curseur jusqu'au champ compétence.
            {

                if ((parcoursSkill !='(') && (parcoursSkill != ':') )//Champ nom de compétence
                {
                    if (parcoursSkill == '/')  fichierMonstre.get(parcoursSkill);
                    sSkillName += parcoursSkill;
                }

                if (parcoursSkill =='(') //Champ degats d'une compétence
                {
                    fichierMonstre.get(parcoursSkill); //Pour ne pas recupérer le "("
                    sDamage += parcoursSkill;
                    while (parcoursSkill != ')') //On récupére le champ des dommages
                    {
                        fichierMonstre.get(parcoursSkill);
                        sDamage += parcoursSkill;
                    }

                }

                if (parcoursSkill == ':')
                {
                    int damage;
                    istringstream (sDamage) >> damage; //Conversion string to int

                    competence skill(sSkillName, damage); //On crée la compétence
                    allSkills.push_back(skill); //On la met dans le vecteur

                    sSkillName=""; // On reset tout
                    sDamage="";
                    fichierMonstre.get(parcoursSkill);
               }

               if (parcoursSkill == '\n')
               {
                   break;
               }
            }
        }
    }

    else
    {
        cerr << "Impossible d'ouvrir le fichier." << endl;
    }
    return allSkills;
}


monstre interface::loadMonstreFromFile()
{
    int nbSeparateur = 0;
    string sID;
    string sName;
    string sHpMax;
    string sSpeed;

    char parcoursCarac;

    ifstream fichierMonstre("fichierMonstre.txt", ios::in); //Ouverture en mode lecture

    if(fichierMonstre)
    {
        while (fichierMonstre.get(parcoursCarac)) //Parcours des caractéristiques
        {
            if(nbSeparateur <4) // Récupération des carac. d'un monstre
            {
                if (parcoursCarac == '/')
                {
                    nbSeparateur++;
                }

                if (nbSeparateur == 0) // Champ ID
                {
                    sID+=parcoursCarac;
                }

                if (nbSeparateur == 1) //Champ Nom
                {
                    if (parcoursCarac == '/')  fichierMonstre.get(parcoursCarac);
                    sName+=parcoursCarac;
                }

                if (nbSeparateur == 2) //Champ hpMax
                {
                    if (parcoursCarac == '/')  fichierMonstre.get(parcoursCarac);
                    sHpMax+=parcoursCarac;
                }

                if (nbSeparateur == 3) //Champ vitesse
                {
                    if (parcoursCarac == '/')  fichierMonstre.get(parcoursCarac);
                    sSpeed+=parcoursCarac;
                }
            }
        }

        int hpMax;
        istringstream (sHpMax) >> hpMax; //Conversion string to int

        int speed;
        istringstream (sSpeed) >> speed; //Conversion string to int

        vector<competence> allSkills = this->loadCompetenceFromFile(); //Récupération des compétences

        monstre creation(sName, hpMax, speed, allSkills); //Création du monstre

        return creation;

        fichierMonstre.close();
    }

    else
    {
        cerr << "Impossible d'ouvrir le fichier." << endl;
    }


}
