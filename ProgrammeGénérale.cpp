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
	//Cette fonction défini un paquet de carte contenant 54 cartes.
}

void MelangerPaquet(carte paquet[])
{
	//Cette fonction mélange un paquet de carte qui a le même format que celui dans la fonction DefinirPaquet
}

void Hasard(carte paquet[])
{
	//Cette fonction joue selon la détermination au hasard d'un paquet
	//Dans cette fonction, on utilise une fonction qui mélange un paquet de carte qui a le même format que celui dans la fonction DefinirPaquet
	//Dans cette fonction, on utilise une fonction qui fait en sorte que les cartes de la main soit donné dans le tableau "paquet de 54 carte en ordre" afin de ne pas pouvoir les piger lors d'un changement de carte
	//Dans cette fonction, on utilise une fonction qui trie en ordre croissant de la valeur de chaque carte de la main
	//Dans cette fonction, on utilise une fonction qui affiche relativement selon longueur de string total des noms de cartes de la main en cours
	//Dans cette fonction, on utilise une fonction qui vérifie le multiple de gain et le renvoie en int dans la détermination de la main selon le multiple de gain
}

void SelonFichier(carte paquetsf[])
{
	//Cette fonction est la fonction principale lors du choix de jouer selon le fichier de mains prédéfinies
	//Dans cette fonction, on utilise une fonction défini un paquet de carte contenant 54 cartes.
	//Dans cette fonction, on utilise une fonction qui fait en sorte que les cartes de la main soit donné dans le tableau "paquet de 54 carte en ordre" afin de ne pas pouvoir les piger lors d'un changement de carte
	//Dans cette fonction, on utilise une fonction qui trie en ordre croissant de la valeur de chaque carte de la main
	//Dans cette fonction, on utilise une fonction qui affiche relativement selon longueur de string total des noms de cartes de la main en cours
	//Dans cette fonction, on utilise une fonction qui vérifie le multiple de gain et le renvoie en int dans la détermination de la main selon le multiple de gain
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
		        MelangerPaquet(paquet);
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
