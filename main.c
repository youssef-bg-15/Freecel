#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "head.h"
int main() {
	//Déclaration les piles
	Pile *Zone1[8]; //piles de zone1 
	Pile*Zone2[4]; //piles de zone 2
	Pile*Zone3[4]; //piles de zone 3
	//initialiser les piles
	PileNULL(Zone1,8); PileNULL(Zone2,4); PileNULL(Zone3,4);
	//initialiser les cartes
	Card *ASH=initialiserCard(1,'H','R'); Card *ASD=initialiserCard(1,'D','R'); Card *ASC=initialiserCard(1,'C','N'); Card *ASS=initialiserCard(1,'S','N');
	Card *_2H=initialiserCard(2,'H','R'); Card *_2D=initialiserCard(2,'D','R'); Card *_2C=initialiserCard(2,'C','N'); Card *_2S=initialiserCard(2,'S','N');
	Card *_3H=initialiserCard(3,'H','R'); Card *_3D=initialiserCard(3,'D','R'); Card *_3C=initialiserCard(3,'C','N'); Card *_3S=initialiserCard(3,'S','N');
	Card *_4H=initialiserCard(4,'H','R'); Card *_4D=initialiserCard(4,'D','R'); Card *_4C=initialiserCard(4,'C','N'); Card *_4S=initialiserCard(4,'S','N');
	Card *_5H=initialiserCard(5,'H','R');	Card *_5D=initialiserCard(5,'D','R');	Card *_5C=initialiserCard(5,'C','N'); Card *_5S=initialiserCard(5,'S','N');
	Card *_6H=initialiserCard(6,'H','R');	Card *_6D=initialiserCard(6,'D','R');	Card *_6C=initialiserCard(6,'C','N');	Card *_6S=initialiserCard(6,'S','N');
	Card *_7H=initialiserCard(7,'H','R');	Card *_7D=initialiserCard(7,'D','R');	Card *_7C=initialiserCard(7,'C','N');	Card *_7S=initialiserCard(7,'S','N');
	Card *_8H=initialiserCard(8,'H','R');	Card *_8D=initialiserCard(8,'D','R');	Card *_8C=initialiserCard(8,'C','N');	Card *_8S=initialiserCard(8,'S','N');
	Card *_9H=initialiserCard(9,'H','R');	Card *_9D=initialiserCard(9,'D','R');	Card *_9C=initialiserCard(9,'C','N');	Card *_9S=initialiserCard(9,'S','N');
	Card *_10H=initialiserCard(10,'H','R'); Card *_10D=initialiserCard(10,'D','R'); Card *_10C=initialiserCard(10,'C','N');Card *_10S=initialiserCard(10,'S','N');
	Card *JH=initialiserCard(11,'H','R'); Card *JD=initialiserCard(11,'D','R'); Card *JC=initialiserCard(11,'C','N'); Card *JS=initialiserCard(11,'S','N');
	Card *QH=initialiserCard(12,'H','R'); Card *QD=initialiserCard(12,'D','R'); Card *QC=initialiserCard(12,'C','N'); Card *QS=initialiserCard(12,'S','N');
	Card *KH=initialiserCard(13,'H','R'); Card *KD=initialiserCard(13,'D','R'); Card *KC=initialiserCard(13,'C','N'); Card *KS=initialiserCard(13,'S','N');
	//EMPILER ALEATOIREMENT LES PILES
	srand(time(NULL));
    Card *cartes[] = {ASH, ASD, ASC, ASS, _2H, _2D, _2C, _2S, _3H, _3D, _3C, _3S ,_4H, _4D, _4C, _4S ,_5H, _5D, _5C, _5S, _6H, _6D, _6C, _6S ,_7H, _7D, _7C, _7S,
	_8H, _8D, _8C, _8S ,_9H, _9D, _9C, _9S ,_10H, _10D, _10C, _10S, JH, JD,JC, JS ,QH, QD, QC, QS ,KH, KD, KC, KS};

    // Mélangez les cartes
    int tailleCartes = sizeof(cartes) / sizeof(cartes[0]);
    melangerCartes(cartes, tailleCartes);

    int i;
    while(1){ //boucle while infini pour la nouvelle partie
    	//empiler les piles de la zone 1 aléatoirement
	    for (i = 0; i < 7; i++) {//empiler 7 cartes dans les 4 premières piles
	        empiler(&Zone1[0], cartes[i]);
	        empiler(&Zone1[1], cartes[i + 7]);
	        empiler(&Zone1[2], cartes[i + 14]);
	        empiler(&Zone1[3], cartes[i + 21]);
	    }
	    // Empilez 6 cartes dans les 4 dernières piles
	    for (i = 28; i < 34; i++) {
	        empiler(&Zone1[4], cartes[i]);
	        empiler(&Zone1[5], cartes[i + 6]);
	        empiler(&Zone1[6], cartes[i + 12]);
	        empiler(&Zone1[7], cartes[i + 18]);
	    }
	    int temp = 2;//la var qui va prendre les retours des fonctions DeplacementToZonex
	    int jeu; //var pour differentier entre rejouer ou nouvelle partie ou quitter
	    while(GagnerJeu(Zone3) == 0 && Blocage(Zone1,Zone2,Zone3)==0){//boucle while termine quand l'utilisateur perd ou gagne la partie
	    	//afficher à l'écran
	    	printf("--------------------------------------LES REGLES--------------------------------------------\n");
	    	printf("|les piles de la zone 1 sont : A, B, C, D, E, F, G, H                                      | \n");
	    	printf("|les piles de la zone 2 sont : I, J, K, L                                                  | \n");
	    	printf("|les piles de la zone 3 sont : M(Clubs), N(Heart), O(Spades), P(Diamonds)                  | \n");
			printf("|Pour deplacer une carte de la zone 1 ou 2 dans une pile de la zone 1 veuillez tapez sur 1 | \n");
			printf("|Pour deplacer une carte de la zone 1 ou 2 dans une pile de la zone 2 veuillez tapez sur 2 | \n");
		    printf("|Pour deplacer une carte de la zone 1 ou 2 dans une pile de la zone 3 veuillez tapez sur 3 | \n");
		    printf("|Pour rejouez cette partie veuillez tapez sur 4                                            | \n");
			printf("|Pour une nouvelle partie veuillez tapez sur 5                                             | \n");
			printf("|Pour quitter veuillez tapez sur 6                                                         | \n");
			printf("--------------------------------------------------------------------------------------------\n");
			Distribuer(Zone1,Zone2,Zone3);
		    // debut du jeu
		    //les variables nécessaires pour le jeu
		    Pile *DEB=NULL;
			Pile *FIN=NULL;
		    char deb;
		    char fi;
		    printf("--------------------------------------------Debut du jeu------------------------------------\n");
		    Color(4,0);
			if(temp==0){
		    	printf("\t\t EREEUR veuillez choisir des piles convenables s'il vous plait \n");
			}
			else if(temp == -1){
				printf("\t\t ERREUR DE DEPLACEMENT \n");
			}
			else if (temp == -2){
				printf("\t\t Erreur : veuillez respectez le type de la pile \n");
			}
			Color(15,0);
		    do{
		    	temp=Jeu(&jeu);
		    }while(temp==0);
		    if(jeu==1)
				temp=DeplacementToZone1(&deb,&fi,&DEB,&FIN,Zone1,Zone2,Zone3);
			else if(jeu==2)
				temp=DeplacementToZone2(&deb,&fi,&DEB,&FIN,Zone1,Zone2,Zone3);
			else if(jeu==3)
				temp=DeplacementToZone3(&deb,&fi,&DEB,&FIN,Zone1,Zone2,Zone3);
			else if(jeu==4 || jeu==5 || jeu==6)
				break;
			if(temp == 1)
				UpdatePile(deb,fi,DEB,FIN,Zone1,Zone2,Zone3);
			//pour effacer l'ecran
			#ifdef _WIN32
		        effacerEcranWindows();
		    #else
		        effacerEcranUnix();
		    #endif
		}
		int rejouer;
		if(GagnerJeu(Zone3) == 1) {
			Distribuer(Zone1,Zone2,Zone3);
			Color(2,0);
			printf("Felicitation . Vous avez gagne :) \n");
			Color(15,0);
			Rejouer(&rejouer);
		}
		if(Blocage(Zone1,Zone2,Zone3)==1){
			Distribuer(Zone1,Zone2,Zone3);
			Color(4,0);
			printf("Desole mais Vous avez perdu :( \n");
			Color(15,0);
			Rejouer(&rejouer);
		}
		PileNULL(Zone1,8); PileNULL(Zone2,4); PileNULL(Zone3,4);
		if(jeu==5 || rejouer == 1){
			melangerCartes(cartes, tailleCartes);
		}
		else if(jeu==6 || rejouer==0){
			break;
		}
		#ifdef _WIN32
		    effacerEcranWindows();
		#else
		    effacerEcranUnix();
		#endif
	}
	return 0;
}
