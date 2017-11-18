//Dereck Pichette et Jeremy Breton

#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

struct carte
{
	string nom;
	int valeur;
	string sorte;
	bool donne=false;	
};

void DefinirPaquet(carte paquet[])
{
	//Cette fonction définie un paquet de carte contenant 54 cartes.
}

void Hasard(carte paquet[])
{
	/*
	Cette fonction joue selon la détermination au hasard d'un paquet
	Dans cette fonction, on utilise une fonction qui mélange un paquet de carte qui a le même format que celui dans la fonction DefinirPaquet
	
	Dans cette fonction, on utilise une fonction qui fait en sorte que les cartes de la main
	définies comme "données", donc il ne sera pas possible de les repiger si il y a un changement de cartes dans la main
	
	Dans cette fonction, on utilise une fonction qui trie en ordre croissant de la valeur de chaque carte de la main
	
	Dans cette fonction, on utilise une fonction qui affiche la main en cours
	Dans cette fonction, on utilise une fonction qui vérifie le multiple de gain et le renvoie pour calculer le gain total
	*/
}

void SelonFichier(carte paquetsf[])
{
	/*
	Cette fonction est la fonction principale lors du choix de jouer selon le fichier de mains prédéfinies	
	Dans cette fonction, on utilise une fonction qui mélange un paquet de carte qui a le même format que celui dans la fonction DefinirPaquet
	
	Dans cette fonction, on utilise une fonction qui fait en sorte que les cartes de la main
	définies comme "données", donc il ne sera pas possible de les repiger si il y a un changement de cartes dans la main
	
	Dans cette fonction, on utilise une fonction qui trie en ordre croissant de la valeur de chaque carte de la main
	Dans cette fonction, on utilise une fonction qui affiche la main en cours
	Dans cette fonction, on utilise une fonction qui vérifie le multiple de gain et le renvoie pour calculer le gain total
	*/
}

int main()
{
	int choix;
	carte paquet[54];
	bool fin=false;
	
	while(!fin)
	{
		cout<<"1 - Jouer avec le hasard"<<endl;
		cout<<"2 - Jouer selon le fichier texte"<<endl;
		cout<<"3 - Quitter le jeu de poker"<<endl;
		cout<<"Entrez votre choix : ";
		cin>>choix;
		
		switch (choix)
		{
			case 1:
		        DefinirPaquet(paquet);
		        Hasard(paquet);
			    break;
			case 2:
				DefinirPaquet(paquet);
				SelonFichier(paquet);
			    break;
			case 3:
			    cout<<"Fin du jeu de poker"<<endl;
			    fin=true;
			    break;
			default:
			    cout << "Choix invalide" << endl << endl;
			    break;
		}
		cout<<endl;		
	}
}
