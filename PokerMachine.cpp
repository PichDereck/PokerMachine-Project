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

void RandomDeck(carte paquet2[])
{
	int k=0,j=0,i;
	
	srand(time(NULL));
	
	const string ncarte[14]={"2","3","4","5","6","7","8","9","10","J","Q","K","AS","JK"};
	const string scarte[4]={"pique","coeur","trefle","carreau"};
	const string sjoker[2]={"jk1","jk2"};
	
	for(i=0;i<52;i++)
	{
		paquet2[i].nom = ncarte[k];
		paquet2[i].valeur = k+2;
		paquet2[i].sorte = scarte[j];

		k++;
		if(k==13)
		{
			k=0;
			j++;
		}
		if(j==4)
		{
			j=0;
		}
	}
	
	for(i=52;i<54;i++)
	{
		paquet2[i].nom = ncarte[13];
		paquet2[i].valeur = 15;
		paquet2[i].sorte = sjoker[j];
		j++;
	}
	
	random_shuffle(paquet2, paquet2+54);
}

void Hasard(carte paquet3[])
{	
	int i;
	
	fstream fichierecriture("fichierpokerhasard.txt",ios::out);
	for(i=0;i<5;i++)
	{
		fichierecriture<<paquet3[i].nom<<" ";
		fichierecriture<<paquet3[i].valeur<<" ";
		fichierecriture<<paquet3[i].sorte<<endl;
	}
	fichierecriture.close();
}

void BubbleSort(carte paquetsort[])
{
	bool change=true;	
	
	while(change==true)
	{
		change=false;
		for(int i=0; i<4; i++)
		{
			if(paquetsort[i].valeur<paquetsort[i+1].valeur)
			{
				swap(paquetsort[i], paquetsort[i+1]);
				change=true;
			}
		}
	}
}

void SelonFichier(bool fin2)
{
	float mise;
	carte paquettxt[54];
	int formatlength;

	fstream fichierlecture("fichierpoker.txt",ios::in);
		
    if (!fichierlecture)
    {
		cout<<"Impossible d'ouvrir le fichier"<<endl;
		fin2=true;
    }
    else
    {
    	fichierlecture>>mise;
		cout<<fixed<<setprecision(2)<<"Voici votre mise : "<<mise<<"$"<<endl;
		
		for(int i=0;i<5;i++)
		{
			fichierlecture>>paquettxt[i].nom;
			fichierlecture>>paquettxt[i].valeur;
			fichierlecture>>paquettxt[i].sorte;	
		}
		
		BubbleSort(paquettxt);
		
		for(int i=0;i<5;i++)
		{
			paquettxt[i].nom.length() + formatlength = formatlength;
		}
		
		for(int i=0;i<5;i++)
		{
			cout<<setw(formatlength)<<paquettxt[i].nom<<" "<<paquettxt[i].valeur<<" "<<paquettxt[i].sorte<<endl;
		}
	}
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
		        RandomDeck(paquet);
		        Hasard(paquet);
			    break;
			case 2:
				SelonFichier(fin);
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
