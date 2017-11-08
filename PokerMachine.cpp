#include <iostream>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <iterator>

using namespace std;

struct carte
{
	string nom;
	int valeur;
	string sorte;
	bool donne=false;	
};

/*Cette fonction défini un paquet de carte contenant 54 cartes. À la fin de la fonction, ce paquet est défini comme un tableau du type variable ci-haut. Il est défini en ordre : 
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
//Cette fonction mélange un paquet de carte qui a le même format que celui dans la fonction DefineDeck
void ShuffleDeck(carte paquet[])
{
	random_shuffle(paquet, paquet+54);
}

void Hasard()
{
	
}

//Cette fonction trie en ordre croissant de la valeur de chaque carte de la main, cette main qui est associé au 5 éléments de la ligne à laquelle on veut trier (Utilisé seulement pour le fichier prédéfini)
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

/*Cette fonction renvoie un INT qui indique le nombre de lignes qu'un fichier texte possède en tout jusqu'à la fin du fichier
	EX : 
	J'aime les petits    - Ligne 1
	bonbons au           - Ligne 2
	chocolat             - Ligne 3
	Ce sont mes          - Ligne 4
	bonbons              - Ligne 5
	préférés             - Ligne 6
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

//Cette fonction fait en sorte que les cartes dans le fichier prédéfini comme donné dans le tableau "paquet de 54 carte en ordre" afin de ne pas pouvoir les piger lors d'un changement de carte
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

//Cette fonction vérifie qu'elle est la main gagnante et renvoie le gain en float
float CheckHand(int main, carte paquettxt[][5])
{
	float tmp=0;
	int vcarte[5];
	string scarte[5];
	
	for(int j=0;j<5;j++)
	{
		vcarte[j]=paquettxt[main][j].valeur;
		scarte[j]=paquettxt[main][j].sorte;
	}
	
	//Ces if imbriqués regarde si la main est une Straight, Straight FLush ou Straight Flush Royale
	if(vcarte[0]==vcarte[1]-1)
	{
		if(vcarte[0]==vcarte[2]-2)
		{
			if(vcarte[0]==vcarte[3]-3)
			{
				if(vcarte[0]==vcarte[4]-4)
				{
					cout<<"STRAIGHT ";
					tmp=20;
					if(scarte[0]==scarte[1]&&scarte[0]==scarte[2]&&scarte[0]==scarte[3])
					{
						cout<<"FLUSH ";
						tmp=tmp+10;
						if(vcarte[0]==10&&vcarte[1]==11&&vcarte[2]==12&&vcarte[3]==13&&vcarte[4]==14)
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
	if(vcarte[0]==vcarte[1]&&vcarte[0]==vcarte[2]&&vcarte[0]==vcarte[3])
	{
		cout<<"FOUR OF A KIND";
		tmp=25;
	}
	
	//Regarde si Flush
	if(tmp==0)
	{
		if(scarte[0]==scarte[1]&&scarte[0]==scarte[2]&&scarte[0]==scarte[3])
		{
			cout<<"FLUSH";
			tmp=15;
		}		
	}
	
	 //Regarde si Full House
	if((vcarte[0]==vcarte[1]&&vcarte[2]==vcarte[3]&&vcarte[2]==vcarte[4])||(vcarte[0]==vcarte[1]&&vcarte[0]==vcarte[2]&&vcarte[3]==vcarte[4]))
	{
		cout<<"FULL HOUSE";
		tmp=10;
	}
	
	//Regarde si Three of a kind	
	if(tmp==0)
	{
		for(int i=0;i<=2;i++)
		{
			if(vcarte[i]==vcarte[i+1]&&vcarte[i]==vcarte[i+2])
			{
				cout<<"THREE OF A KIND";
				tmp=5;
			}
		}
	}
	
	//Regarde si Two pairs
	if(tmp==0)
	{
    	for(int q=0;q<=1;q++)
	 	{
	 		if(vcarte[q]==vcarte[q+1])
	 		{
	 			if(vcarte[q+2]==vcarte[q+3])
	 			{
	 				cout<<"TWO PAIRS";
	 				tmp=3;
			 	}
		 	}
		}
		
		if(vcarte[0]==vcarte[1]&&vcarte[3]==vcarte[4])
		{
			cout<<"TWO PAIRS";
			tmp=3;
		}
		     
	}
	
	if(tmp==0)
	{
		cout<<"LA MAIN N'EST PAS GAGNANTE";
	}
	cout<<endl;
	return tmp;
}

//Cette fonction est la fonction principale lors du choix de jouer selon le fichier de mains prédéfinies
void SelonFichier(bool fin, carte paquetsf[])
{
	int formatlength,lignes,main=0;
	float gains=0;

	fstream fichierlecture("fichierpoker.txt",ios::in);
		
    if (!fichierlecture)
    {
		cout<<"Impossible d'ouvrir le fichier"<<endl;
		fin=true;
		fichierlecture.close();
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
		
		//Va me chercher le gain à multiplier avec la mise selon la main
		gains = CheckHand(main,paquettxt);
		
		cout<<"Vos gains : "<<gains*mises[main]<<endl;
		
		main++;
	}
	fichierlecture.close();
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
