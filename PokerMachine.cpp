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

/*Cette fonction d�fini un paquet de carte contenant 54 cartes. � la fin de la fonction, ce paquet est d�fini comme un tableau du type variable ci-haut. Il est d�fini en ordre : 
	{2,3,4...Q,K,AS|2,3,4...Q,K,AS|2,3,4...Q,K,AS|2,3,4...Q,K,AS|JK,JK}*/
void DefineDeck(carte paquet[])
{
	int k=0,j=0,i;
	
	srand(time(NULL));
	
	const string ncarte[14]={"2","3","4","5","6","7","8","9","10","J","Q","K","AS","JK"};
	const string scarte[4]={"pique","coeur","trefle","carreau"};
	const string sjoker[2]={"jk1","jk2"};
	
	for(i=0;i<52;i++)
	{
		paquet[i].nom = ncarte[k];
		paquet[i].valeur = k+2;
		paquet[i].sorte = scarte[j];

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
		paquet[i].nom = ncarte[13];
		paquet[i].valeur = 15;
		paquet[i].sorte = sjoker[j];
		j++;
	}
}
//Cette fonction m�lange un paquet de carte qui a le m�me format que celui dans la fonction DefineDeck
void ShuffleDeck(carte paquet[])
{
	random_shuffle(paquet, paquet+54);
}

void Hasard()
{
	
}

//Cette fonction trie en ordre croissant de la valeur de chaque carte de la main, cette main qui est associ� au 5 �l�ments de la ligne � laquelle on veut trier (Utilis� seulement pour le fichier pr�d�fini)
void BubbleSort(int main, carte paquetsort[][5])
{
	bool change=true;	
	
	while(change==true)
	{
		change=false;
		for(int i=0; i<4; i++)
		{
			if(paquetsort[main][i].valeur>paquetsort[main][i+1].valeur)
			{
				swap(paquetsort[main][i], paquetsort[main][i+1]);
				change=true;
			}
		}
	}
}

/*Cette fonction renvoie un INT qui indique le nombre de lignes qu'un fichier texte poss�de en tout jusqu'� la fin du fichier
	EX : 
	J'aime les petits    - Ligne 1
	bonbons au           - Ligne 2
	chocolat             - Ligne 3
	Ce sont mes          - Ligne 4
	bonbons              - Ligne 5
	pr�f�r�s             - Ligne 6
*/
int LignesFichier()
{
	fstream fichierlecture("fichierpoker.txt",ios::in);
	
	fichierlecture.unsetf(ios_base::skipws);

    int lignes = count(
        istream_iterator<char>(fichierlecture),
        istream_iterator<char>(), '\n');
    fichierlecture.close();
    
    return lignes;
}

//Cette fonction fait en sorte que les cartes dans le fichier pr�d�fini comme donn� dans le tableau "paquet de 54 carte en ordre" afin de ne pas pouvoir les piger lors d'un changement de carte
void VerifieDonne(carte paquettxt[][5], carte paquetsf[], int lignes)
{
	for(int j=0;j<lignes/6;j++)
	{
		for(int i=0;i<5;i++)
		{
			for(int k=0;k<54;k++)
			{
				if((paquettxt[j][i].valeur==paquetsf[k].valeur)&&(paquettxt[j][i].sorte==paquetsf[k].sorte))
				{
					paquetsf[k].donne=true;
				}
			}
		}
	}
}

//Cette fonction v�rifie qu'elle est la main gagnante et renvoie le gains en float
float CheckHand(int main, carte paquettxt[][5])
{
	int i=0;
	float tmp=0;
	
	//Ces if imbriqu�s regarde si la main est une Straight, Straight FLush ou Straight Royale
	if(paquettxt[main][i].valeur==paquettxt[main][i+1].valeur-1)
	{
		if(paquettxt[main][i].valeur==paquettxt[main][i+2].valeur-2)
		{
			if(paquettxt[main][i].valeur==paquettxt[main][i+3].valeur-3)
			{
				if(paquettxt[main][i].valeur==paquettxt[main][i+4].valeur-4)
				{
					cout<<"STRAIGHT ";
					tmp=20;
					if(paquettxt[main][i].sorte==paquettxt[main][i+1].sorte&&paquettxt[main][i].sorte==paquettxt[main][i+2].sorte&&paquettxt[main][i].sorte==paquettxt[main][i+3].sorte)
					{
						cout<<"FLUSH ";
						tmp=tmp+10;
						if(paquettxt[main][i].valeur==10&&paquettxt[main][i+1].valeur==11&&paquettxt[main][i+2].valeur==12&&paquettxt[main][i+3].valeur==13&&paquettxt[main][i+4].valeur==14)
						{
							cout<<"ROYALE";
							tmp=tmp+10;
						}
					}
				}
			}
		}
	}
	
	//Regarde si Four of a kind
	if(paquettxt[main][i].valeur==paquettxt[main][i+1].valeur&&paquettxt[main][i].valeur==paquettxt[main][i+2].valeur&&paquettxt[main][i].valeur==paquettxt[main][i+3].valeur)
	{
		cout<<"FOUR OF A KIND";
		tmp=25;
	}
	
	//Regarde si Flush
	if(tmp<30)
	{
		if(paquettxt[main][i].sorte==paquettxt[main][i+1].sorte&&paquettxt[main][i].sorte==paquettxt[main][i+2].sorte&&paquettxt[main][i].sorte==paquettxt[main][i+3].sorte)
		{
			cout<<"FLUSH";
			tmp=15;
		}		
	}
	
	if((paquettxt[main][i].valeur==paquettxt[main][i+1].valeur&&paquettxt[main][i+2].valeur==paquettxt[main][i+3].valeur&&paquettxt[main][i+2].valeur==paquettxt[main][i+4].valeur)||(paquettxt[main][i].valeur==paquettxt[main][i+1].valeur&&paquettxt[main][i].valeur==paquettxt[main][i+2].valeur&&paquettxt[main][i+3].valeur==paquettxt[main][i+4].valeur))
	{
		cout<<"FULL HOUSE";
		tmp=10;
	}
	
	//MANQUE ENCORE 3 POSSIBILIT�S � AJOUTER
	if(tmp==0)
	{
		cout<<"LA MAIN N'EST PAS GAGNANTE";
	}
	cout<<endl;
	return tmp;
}

//Cette fonction est la fonction principale lors du choix de jouer selon le fichier de mains pr�d�finies
void SelonFichier(bool fin, carte paquetsf[])
{
	int formatlength,lignes,main=0;
	float gains=0;

	fstream fichierlecture("fichierpoker.txt",ios::in);
		
    if (!fichierlecture)
    {
		cout<<"Impossible d'ouvrir le fichier"<<endl;
		fin=true;
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
	
	VerifieDonne(paquettxt,paquetsf,lignes);
	
	while(main!=lignes/6)
	{
		BubbleSort(main,paquettxt);
		cout<<fixed<<setprecision(2)<<endl<<"Voici votre mise : "<<mises[main]<<"$"<<endl;
		
		formatlength=0;
		for(int i=0;i<5;i++)
		{
			formatlength = paquettxt[main][i].nom.length() + paquettxt[main][i].sorte.length() + formatlength + 5;
		}
		
		cout<<setw(formatlength)<<setfill('-')<<"-"<<endl;
		for(int i=0;i<5;i++)
		{
			cout<<"| "<<paquettxt[main][i].nom<<"-"<<paquettxt[main][i].sorte<<" |";
		}
		cout<<endl<<setw(formatlength)<<setfill('-')<<"-"<<endl;
		
		//Va me chercher le gain � multiplier la mise avec selon la main
		gains = CheckHand(main,paquettxt);
		
		cout<<"Vos gains : "<<gains*mises[main]<<endl;
		
		main++;
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
		        DefineDeck(paquet);
		        ShuffleDeck(paquet);
			    break;
			case 2:
				DefineDeck(paquet);
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
