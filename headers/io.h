#include <iostream>
#include <vector>
#include <typeinfo>

#ifndef IO_H
#define IO_H


//! Cet espace sera un espace permettant de définir un buffer custom pour les input, ainsi que de pouvoir afficher tout ce que l'on souhaite.
namespace io
{
	std::istream io_input();

	//! Input
	/*!
        Gestion des entrées utilisateur.
	*/
	extern char de();


	//! Message d'accueil
	/*!
        Affiche un message de bienvenue.
	*/
	void bienvenue();


	//! Affichage d'objet.
    /*!
        Affiche le nom (et éventuellement la description) d'un objet.
        \param object Objet à afficher.
        \param need_desc Description ou non.
    */
    template<typename T> void afficher(T object, bool need_desc)
    {
        std::cout << (object).getName();                          //Affiche le nom

        //std::cout << (object).getDescription();                   //Affiche la description
    }


    //! Affichage d'un ensemble d'objets
    /*!
        Parcourt le vecteur de stockage des objets chargés, et les affiche.
        \param vect_element Vecteur d'éléments.
        \param need_desc Description ou non.
        \sa afficher()
    */
    template<typename T> void liste_elements(std::vector<T> vect_element, bool need_desc)
    {
        typename std::vector<T>::iterator itv;                              //Variable de parcours de vecteur
        int cpt = 0;                                                        //Compteur d'éléments

        for (itv = vect_element.begin(); itv != vect_element.end(); itv++)  //Parcours vecteur
        {
            cpt++;                                                          //Incrémentation compteur
            std::cout << cpt%10 << "- ";                                    //Numéro de l'élément (0 - 9)
            afficher((* itv), need_desc);                                   //Affichage de l'élément
            std::cout << "   ";
        }
    }


    //! Choix d'un élément unique
    /*!
        Fonction qui prend un vecteur d'éléments en entrée ainsi qu'un booléen (affichage ou non de la description), et affiche puis renvoie l'élément choisi.
        \param vect_element Vecteur de l'élément à choisir.
        \param need_desc Nécessité de description ou non.
        \return L'élement choisi.
        \sa liste_elements(), afficher()
    */
    template<typename T> T choix_unique_element(std::vector<T> vect_element, bool need_desc)
    {
        std::string type_name = typeid(T).name();                            //String à partir du type appelant

        while (isdigit(type_name[0]))
        {
            type_name = type_name.substr(1, type_name.size());            //Conservation des caractères pertinents
        }

        std::cout << "Veuillez choisir votre " << type_name << " (0-9): ";

        liste_elements(vect_element, need_desc);                        //Affichage des éléments parmi lesquels choisir

	    char c_input = de();                                            //Input utilisateur
	    int input = c_input - '0';                                      //Transcription en chiffres

	    while (input < 0 || input > vect_element.size())                //Input incorrect
        {
            std::puts("Input incorrect. Réessayez!");
            c_input = de();                                             //Input utilisateur
            input = c_input - '0';                                      //Trancription en chiffres
        }

	    T choix = vect_element[input - 1];                              //Sélection de l'objet dans son vecteur

	    std::cout << std::endl << "Vous avez choisi: ";
	    afficher(choix, need_desc);                                     //Affichage de l'objet choisi
	    std::puts("\n");

	    return choix;                                                   //Renvoi de l'objet choisi
    }
}

#endif
