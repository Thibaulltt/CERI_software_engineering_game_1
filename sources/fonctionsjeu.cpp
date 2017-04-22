#include "../headers/fonctionsjeu.h"
#include <iostream>	// à remplacer avec notre librairie I/O plus tard

jeu::jeu()
{
	jeu_perso = new personnage();			// À COMPLÉTER UNE FOIS QUE CLASSE PERSO FINIE
	jeu_carte = new Carte();			// À COMPLÉTER UNE FOIS QUE CLASSE CARTE FINIE
	jeu_nombre_monstre = 8;				// À COMPLÉTER UNE FOIS QUE CLASSE CARTE FINIE
	// Normalement, à ca point là, la carte doit être chargée, le personnage est choisi et chargé, les monstres sont chargés et il ne reste qu'à lancer le jeu.
}

jeu::~jeu()
{}

void jeu::demarrer_jeu()
{
	bienvenue();



	// custom_buffer.affichercarte(jeu_carte);
}

//
//ent_combat::ent_combat(monstre monst)
//{
//	entite = monst;
//}
//
//monstre ent_combat::Get_entite()
//{
//	return entite;
//}
//
//void ent_combat::util_comp(monstre entite, competence comp)
//{
//
//}

//bool sort_speed(ent_combat a, ent_combat b)
//{
//	return a.Get_entite().getSpeed() < b.Get_entite().getSpeed();
//}

bool sort_speed(monstre a, monstre b)
{
	return a.getSpeed() < b.getSpeed();
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
