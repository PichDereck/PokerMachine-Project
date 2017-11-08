#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <typeinfo>
#include <iterator>

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
	fstream fichierecriture("fichierpokerhasard.txt",ios::out);
	for(int i=0;i<54;i++)
	{
		fichierecriture<<paquet3[i].nom<<" ";
		fichierecriture<<paquet3[i].valeur<<" ";
		fichierecriture<<paquet3[i].sorte<<endl;
	}
	fichierecriture.close();
}

void BubbleSort(int j, carte paquetsort[][5])
{
	bool change=true;	
	
	while(change==true)
	{
		change=false;
		for(int i=0; i<4; i++)
		{
			if(paquetsort[j][i].valeur>paquetsort[j][i+1].valeur)
			{
				swap(paquetsort[j][i], paquetsort[j][i+1]);
				change=true;
			}
		}
	}
}

int LignesFichier()
{
	fstream fichierlecture("fichierpoker.txt",ios::in);
	
	fichierlecture.unsetf(ios_base::skipws);

    int lignes = count(
        istream_iterator<char>(fichierlecture),
        istream_iterator<char>(), 
        '\n');
        
    fichierlecture.close();
    
    return lignes;
}


void SelonFichier(bool fin2, carte paquetsf[])
{
	int formatlength,lignes,j=0;

	fstream fichierlecture("fichierpoker.txt",ios::in);
		
    if (!fichierlecture)
    {
		cout<<"Impossible d'ouvrir le fichier"<<endl;
		fin2=true;
    }
    
	lignes=LignesFichier();
	
	float mises[lignes/6];
	carte paquettxt[lignes/6][5];
	
	for(int i=0;i<lignes/6;i++)
	{
		fichierlecture>>mises[i];
		for(int k=0;k<5;k++)
		{
			fichierlecture>>paquettxt[i][k].nom;
			fichierlecture>>paquettxt[i][k].valeur;
			fichierlecture>>paquettxt[i][k].sorte;
			paquettxt[i][k].donne=true;
		}
	}
	
	while(j!=lignes/6)
	{
		BubbleSort(j,paquettxt);
		cout<<fixed<<setprecision(2)<<"Voici votre mise : "<<mises[j]<<"$"<<endl;
		
		formatlength=0;
		for(int i=0;i<5;i++)
		{
			formatlength = paquettxt[j][i].nom.length() + paquettxt[j][i].sorte.length() + formatlength + 5;
		}
		
		cout<<setw(formatlength)<<setfill('-')<<"-"<<endl;
		for(int i=0;i<5;i++)
		{
			cout<<"| "<<paquettxt[j][i].nom<<"-"<<paquettxt[j][i].sorte<<" |";
		}
		cout<<endl<<setw(formatlength)<<setfill('-')<<"-"<<endl;
		j++;
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
				RandomDeck(paquet);
				SelonFichier(fin,paquet);
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
