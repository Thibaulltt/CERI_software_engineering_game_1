#include "../headers/io.h"
#include <vector>
#include <termios.h>	// Needed for terminal input manipulation
#include <stdio.h>	// Needed for terminal input manipulation

// Notes :
// Get the terminal column number :
// 	> stty -a | grep "col" | tail -c 22 | tail -c 13 | head -c 3
// Get the terminal rows number :
// 	> stty -a | grep "col" | tail -c 22 | head -c 2

using namespace std;

namespace io
{
	char de()
	{
		// Create new structures for storing new and old configs of the current terminal.
		static struct termios old, mew;
		char ch;				// Return character
		// Initialize new terminal I/O settings
		tcgetattr(0, &old);			/* Grab old terminal i/o settings */
		mew = old;				/* Make new settings same as old settings */
		mew.c_lflag &= ~ICANON;			/* Disable buffered i/o */
		mew.c_lflag &= ~ECHO;			/* Set echo mode */
		tcsetattr(0, TCSANOW, &mew);		/* Use these new terminal i/o settings now */
		ch = getchar();				// getchar() now takes only one char
		// Restore old terminal I/O settings
		tcsetattr(0, TCSANOW, &old);
		return ch;
	}

	void bienvenue()
	{
        std::puts("\n");
        std::puts("                                         Welcome to");
        std::puts(" __________   ___    ___   __________     __________   __________   ___    ___   __________");
        std::puts("/___   ___/  /  /   /  /  /  _______/    /  _______/  /  ____   /  /  /__ /  /  /  _______/");
        std::puts("   /  /     /  /__ /  /  /  /__         /  /  __     /  /___/  /  /         /  /  /__");
        std::puts("  /  /     /   __    /  /   __/        /  /  /  \\   /  ____   /  /  / - /  /  /   __/");
        std::puts(" /  /     /  /   /  /  /  /______     /  /___/  /  /  /   /  /  /  /   /  /  /  /______");
        std::puts("/_ /     /_ /   /_ /  /_________/    /_________/  /_ /   /_ /  /_ /   /_ /  /_________/");
        std::puts("\n");

        std::puts("Dans The Game, vous devez débusquer et tuer tous les monstres présents sur la carte. Bonne chance!");
        std::puts("\n");
	}
}

////! Implémentation classe test
//personnage::personnage()
//{
//    name = "";
//    description = "";
//}
//
//personnage::personnage(string nom, string desc)
//{
//    name = nom;
//    description = desc;
//}
//
//string personnage::get_name()
//{
//    return name;
//}
//
//string personnage::get_desc()
//{
//    return description;
//}
