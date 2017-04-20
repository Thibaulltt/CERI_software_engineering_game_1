#include "../headers/fonctionsjeu.h"
#include <iostream>	// à remplacer avec notre librairie I/O plus tard

jeu::jeu()
{
	// jeu_perso = new perso();			// À COMPLÉTER UNE FOIS QUE CLASSE PERSO FINIE
	// jeu_carte = new carte();			// À COMPLÉTER UNE FOIS QUE CLASSE CARTE FINIE
	// jeu_nombre_monstre = carte.getMonsters();	// À COMPLÉTER UNE FOIS QUE CLASSE CARTE FINIE
}

jeu::~jeu()
{}

void jeu::demarrer_jeu()
{
	bienvenue();



	// custom_buffer.affichercarte(jeu_carte);
}

/*
void jeu::combat(perso &p, monstre &m)
{
	while (monstre_mort == 0)
	{
		v_retour a = choisir_coup(player);			// CLASSE COMPETENCE EN RETOUR
		v_retour b = choisir_coup(monster);			// CLASSE COMPETENCE EN RETOUR
		application_coup(p,a,m,b);
		if (joueur_mort == 1)
			fin_de_partie();
	}
}

void jeu::application_coup(perso &p, compet &a, monstre &m, compet &b)
{
	int jeu_degats_joueur = a.getDegats();
	int jeu_degats_monstre = b.getDegats();
	if ( p.enleverVie(a) )						// LA FONCTION enleverVie() REVOIE VRAI SI LE JOUEUR N'EST PAS MORT, FAX SINON
		finishGame(0);
	else
}
*/
