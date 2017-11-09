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
	int k=0,j=0;
	
	const string ncarte[14]={"2","3","4","5","6","7","8","9","10","J","Q","K","AS","JK"};
	const string scarte[4]={"pique","coeur","trefle","carreau"};
	const string sjoker[2]={"jk1","jk2"};
	
	for(int i=0;i<52;i++)
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
	}
	
	for(int i=0;i<2;i++)
	{
		paquet[i+52].nom = ncarte[13];
		paquet[i+52].valeur = 15;
		paquet[i+52].sorte = sjoker[i];
	}
}
//Cette fonction mélange un paquet de carte qui a le même format que celui dans la fonction DefineDeck
void ShuffleDeck(carte paquet[])
{
	srand(time(NULL));
	random_shuffle(paquet, paquet+54);
}

//Cette fonction écrit le paquet de carte randomisé dans un fichier texte
void WriteTXT(carte paquet[])
{
	fstream fichierecriture("fichierpokerhasard.txt", ios::out | ios::trunc);
	for(int i=0;i<54;i++)
	{
		fichierecriture<<paquet[i].nom<<" ";
		fichierecriture<<paquet[i].valeur<<" ";
		fichierecriture << paquet[i].sorte<<endl;
	}
	fichierecriture.close();
}

//Cette fonction trie en ordre croissant de la valeur de chaque carte de la main
void BubbleSort(carte paquetsort[])
{
	bool change=true;	
	
	while(change==true)
	{
		change=false;
		for(int i=0; i<4; i++)
		{
			if(paquetsort[i].valeur>paquetsort[i+1].valeur)
			{
				swap(paquetsort[i], paquetsort[i+1]);
				change=true;
			}
		}
	}
}

//Cette fonction fait en sorte que les cartes de la main soit donné dans le tableau "paquet de 54 carte en ordre" afin de ne pas pouvoir les piger lors d'un changement de carte
void DonneTrue(carte paquettxt[], carte paquetsf[])
{
	for(int i=0;i<5;i++)
	{
		for(int k=0;k<54;k++)
		{
			if((paquettxt[i].valeur==paquetsf[k].valeur)
				&&(paquettxt[i].sorte==paquetsf[k].sorte))
			{
				paquetsf[k].donne=true;
			}
		}
	}
}

//Cette fonction vérifie qu'elle est la main gagnante et renvoie le gain en float
int CheckHand(carte paquettxt[], carte paquetsf[])
{
	int tmp=0,multiple=0;
	carte cartes[5];
	bool onejoker=false;
	bool twojokers=false;

	for(int jk=0;jk<52;jk++)
	{
		for(int jk2=0;jk2<52;jk2++)
		{	
			for(int j=0;j<5;j++)
			{
				cartes[j].valeur=paquettxt[j].valeur;
				cartes[j].sorte=paquettxt[j].sorte;
			}
			
			if(cartes[4].valeur==15)
			{
				onejoker=true;
				if(cartes[3].valeur==15)
				{
					twojokers=true;
				}
			}
			
			if(onejoker==true)
			{
				cartes[4].valeur=paquetsf[jk2].valeur;
				cartes[4].sorte=paquetsf[jk2].sorte;
			}
			
			if(twojokers==true)
			{
				cartes[3].valeur=paquetsf[jk+1].valeur;
				cartes[3].sorte=paquetsf[jk+1].sorte;				
			}
			
			//Va mettre les cartes en ordre de croissance de valeur
			BubbleSort(cartes);
			
			//Regarde si Two pairs
	    	for(int i=0;i<=1;i++)
		 	{
		 		if(cartes[i].valeur==cartes[i+1].valeur)
		 		{
		 			if(cartes[i+2].valeur==cartes[i+3].valeur)
		 			{
		 				tmp=3;
				 	}
			 	}
			}
			
			if(cartes[0].valeur==cartes[1].valeur&&cartes[3].valeur==cartes[4].valeur)
			{
				tmp=3;
			}
			
			//Regarde si Three of a kind	
			for(int i=0;i<=2;i++)
			{
				if(cartes[i].valeur==cartes[i+1].valeur&&cartes[i].valeur==cartes[i+2].valeur)
				{
					tmp=5;
				}
			}
			
			//Regarde si Full House
			if((cartes[0].valeur==cartes[1].valeur&&cartes[2].valeur==cartes[3].valeur&&cartes[2].valeur==cartes[4].valeur)
				or(cartes[0].valeur==cartes[1].valeur&&cartes[0].valeur==cartes[2].valeur&&cartes[3].valeur==cartes[4].valeur))
			{
				tmp=10;
			}
			
			//Regarde si Flush
			if(tmp<30)
			{
				if(cartes[0].sorte==cartes[1].sorte&&cartes[0].sorte==cartes[2].sorte&&cartes[0].sorte==cartes[3].sorte)
				{
					tmp=15;
				}		
			}
			
			//Regarde si Four of a kind
			if((cartes[0].valeur==cartes[1].valeur&&cartes[0].valeur==cartes[2].valeur&&cartes[0].valeur==cartes[3].valeur)
				or(cartes[1].valeur==cartes[2].valeur&&cartes[1].valeur==cartes[3].valeur&&cartes[1].valeur==cartes[4].valeur))
			{
				tmp=25;
			}
			
			//Ces if imbriqués regarde si la main est une Straight, Straight FLush ou Straight Flush Royale
			if(cartes[0].valeur==cartes[1].valeur-1&&cartes[0].valeur==cartes[2].valeur-2
				&&cartes[0].valeur==cartes[3].valeur-3&&cartes[0].valeur==cartes[4].valeur-4)
			{
				tmp=20; //Straight
				if(cartes[0].sorte==cartes[1].sorte&&cartes[0].sorte==cartes[2].sorte&&cartes[0].sorte==cartes[3].sorte)
				{
					tmp=30; //Straight Flush
					if(cartes[0].valeur==10&&cartes[1].valeur==11&&cartes[2].valeur==12&&cartes[3].valeur==13&&cartes[4].valeur==14)
					{
						tmp=40; //Straight FLush Royale
					}
				}
			}
			
			//À chaque boucle, il garde seulement la valeur la plus haute, pour identifier la meilleure main possible
			if(tmp>multiple)
			{
				multiple=tmp;
				tmp=0;
			}
		}	
	}
	return multiple;
}

//Détermination de la combinaison selon le multiple
void DetermMain(int multiple)
{
	if(multiple==40)
	{
		cout<<"STRAIGHT FLUSH ROYALE - 40x";
	}
	if(multiple==30)
	{
		cout<<"STRAIGHT FLUSH - 30x";
	}
	if(multiple==25)
	{
		cout<<"FOUR OF A KIND - 25x";
	}
	if(multiple==20)
	{
		cout<<"STRAIGHT - 20x";
	}
	if(multiple==15)
	{
		cout<<"FLUSH - 15x";
	}
	if(multiple==10)
	{
		cout<<"FULL HOUSE - 10x";
	}
	if(multiple==5)
	{
		cout<<"THREE OF A KIND - 5x";
	}
	if(multiple==3)
	{
		cout<<"TWO PAIRS - 3x";
	}
	if(multiple==0)
	{
		cout<<"HIGH CARD - 0x";
	}
	
	cout<<endl;
}

//Affichage relatif selon longueur de string total des noms de cartes de la main en cours
void FormatAffMain(carte paquettxt[])
{
	int formatlength=0;
	for(int i=0;i<5;i++)
	{
		formatlength = paquettxt[i].nom.length() + paquettxt[i].sorte.length() + formatlength + 5;
	}
	
	cout<<setw(formatlength)<<setfill('-')<<"-"<<endl;
	for(int i=0;i<5;i++)
	{
		cout<<"| "<<paquettxt[i].nom<<"-"<<paquettxt[i].sorte<<" |";
	}
	cout<<endl<<setw(formatlength)<<setfill('-')<<"-"<<endl;
}

//Cette fonction joue selon le hasard d'un paquet
void Hasard(carte paquet[])
{	
	int multiple,pos,numbtochange,indeck=0;
	carte paquet5[5];
	float mise=0;
	char choix;
	bool validchoice=false, fin=false, changed=false, finjeu=false;
	bool postochange[5] = {false,false,false,false,false};
	
	while(!finjeu)
	{
		ShuffleDeck(paquet);
		
		for(int i=0;i<5;i++)
		{
			paquet5[i].nom=paquet[i].nom;
			paquet5[i].valeur=paquet[i].valeur;
			paquet5[i].sorte=paquet[i].sorte;		
		}
		
		DonneTrue(paquet5, paquet);
		BubbleSort(paquet5);
		
		while(mise<=0)
		{
			cout<<endl<<"Veuillez entrer votre mise : ";
			cin>>mise;
		}
		
		FormatAffMain(paquet5);
		
		//Va me chercher le gain à multiplier avec la mise selon la main
		multiple = CheckHand(paquet5,paquet);
		
		if(!changed)
		{
			while(!validchoice)
			{
				cout<<"Voulez vous changer des cartes ? (O/N) ";
				cin>>choix;
				choix=toupper(choix);
				
				switch (choix)
				{
					case 'O':
						validchoice=true;
						changed=true;
						cout<<"Combien de cartes voulez-vous changer ? ";
						cin>>numbtochange;
						while(numbtochange<1 or numbtochange>5)
						{
							cout<<"Choix Invalide"<<endl;
							cout<<"Combien de cartes voulez-vous changer ? ";
							cin>>numbtochange;							
						}
						
						if(numbtochange==5)
						{
							for(int i=0;i<5;i++)
							{
								postochange[i]=true;
							}
						}
						else
						{
							cout<<"Quelles positions de carte voulez-vous changer ? "<<endl;
							for(int i=0;i<numbtochange;i++)
							{
								cin>>pos;
								if(pos<1 or pos>5 or postochange[pos+1]==true)
								{
									cout<<"Choix Invalide"<<endl;
									i--;
								}
								postochange[pos-1]=true;
							}	
												
							ShuffleDeck(paquet); //Pour ne pas qu'il me montre 2-pique, 3-pique... à chaque fois que je refais une main							
							for(int pos=0;pos<5;pos++)
							{
								for(int i=0;i<54;i++)
								{
									if(postochange[pos]==true)
									{
										if(paquet[i].donne==false)
										{
											paquet5[pos]=paquet[i];
											paquet[i].donne=true;
											postochange[pos]=false;
										}
									}			
								}
							}	
						}
						
						BubbleSort(paquet5);
						FormatAffMain(paquet5);
						multiple = CheckHand(paquet5,paquet);
						DetermMain(multiple);
					    break;
					case 'N':
						validchoice=true;
						DetermMain(multiple);
					    break;
					default:
					    cout << "Choix invalide" << endl << endl;
					    validchoice=false;
					    break;
				}		
			}			
		}
		
		//Calcule gains ou pertes
		if(multiple==0)
		{
			cout<<"Vos pertes : "<<-(mise)<<endl;
		}
		else
		{
			cout<<"Vos gains : "<<multiple*mise<<endl;			
		}
		
		changed=false;
		validchoice=false;
		
		while(!validchoice)
		{
			cout<<"Voulez vous continuer ? (O/N) ";
			cin>>choix;
			choix=toupper(choix);
			
			switch (choix)
			{
				case 'O':
					validchoice=true;
					mise=0;
				    break;
				case 'N':
					validchoice=true;
					finjeu=true;
				    break;
				default:
				    cout << "Choix invalide" << endl << endl;
				    validchoice=false;
				    break;
			}		
		}
		validchoice=false;
	}
}

//Cette fonction est la fonction principale lors du choix de jouer selon le fichier de mains prédéfinies
void SelonFichier(carte paquetsf[])
{
	int multiple,pos,numbtochange;
	float mise;
	carte paquettxt[5];
	char choix;
	bool validchoice=false, fin=false, changed=false;
	bool postochange[5] = {false,false,false,false,false};
	
	fstream fichierlecture("fichierpoker.txt",ios::in);		
    if (!fichierlecture)
    {
		cout<<"Impossible d'ouvrir le fichier"<<endl;
		fin=true;
		fichierlecture.close();
    }
	
	while(!fin)
	{ 
		fichierlecture>>mise;
		while(!fichierlecture.eof())
		{
			DefineDeck(paquetsf);
			
			for(int i=0;i<5;i++)
			{
				fichierlecture>>paquettxt[i].nom;
				fichierlecture>>paquettxt[i].valeur;
				fichierlecture>>paquettxt[i].sorte;		
			}
			
			DonneTrue(paquettxt,paquetsf);
	
			BubbleSort(paquettxt);
			cout<<fixed<<setprecision(2)<<endl<<"Voici votre mise : "<<mise<<"$"<<endl;
			
			FormatAffMain(paquettxt);
			
			//Va me chercher le gain à multiplier avec la mise selon la main
			multiple = CheckHand(paquettxt,paquetsf);
			
			if(!changed)
			{
				while(!validchoice)
				{
					cout<<"Voulez vous changer des cartes ? (O/N) ";
					cin>>choix;
					choix=toupper(choix);
					
					switch (choix)
					{
						case 'O':
							validchoice=true;
							changed=true;
							cout<<"Combien de cartes voulez-vous changer ? ";
							cin>>numbtochange;
							while(numbtochange<1 or numbtochange>5)
							{
								cout<<"Choix Invalide"<<endl;
								cout<<"Combien de cartes voulez-vous changer ? ";
								cin>>numbtochange;							
							}
							
							if(numbtochange==5)
							{
								for(int i=0;i<5;i++)
								{
									postochange[i]=true;
								}
							}
							else
							{
								cout<<"Quelles positions de carte voulez-vous changer ? "<<endl;
								for(int i=0;i<numbtochange;i++)
								{
									cin>>pos;
									if(pos<1 or pos>5 or postochange[pos+1]==true)
									{
										cout<<"Choix Invalide"<<endl;
										i--;
									}
									postochange[pos-1]=true;
								}	
													
								ShuffleDeck(paquetsf); //Pour ne pas qu'il me montre 2-pique, 3-pique... à chaque fois que je refais une main							
								for(int pos=0;pos<5;pos++)
								{
									for(int i=0;i<54;i++)
									{
										if(postochange[pos]==true)
										{
											if(paquetsf[i].donne==false)
											{
												paquettxt[pos]=paquetsf[i];
												paquetsf[i].donne=true;
												postochange[pos]=false;
											}
										}			
									}
								}	
							}
							
							BubbleSort(paquettxt);
							FormatAffMain(paquettxt);
							multiple = CheckHand(paquettxt,paquetsf);
							DetermMain(multiple);
						    break;
						case 'N':
							validchoice=true;
							DetermMain(multiple);
						    break;
						default:
						    cout << "Choix invalide" << endl << endl;
						    validchoice=false;
						    break;
					}		
				}			
			}
			
			//Calcule gains ou pertes
			if(multiple==0)
			{
				cout<<"Vos pertes : "<<-(mise)<<endl;
			}
			else
			{
				cout<<"Vos gains : "<<multiple*mise<<endl;			
			}
			
			changed=false;
			validchoice=false;
			fichierlecture>>mise;
		}
		fin=true;
		cout<<endl<<"---------------"<<endl;
		cout<<"FIN DU FICHIER";
		cout<<endl<<"---------------"<<endl;
		fichierlecture.close();	
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
		        Hasard(paquet);
			    break;
			case 2:
				DefineDeck(paquet);
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
