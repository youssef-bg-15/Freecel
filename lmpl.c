#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "head.h"
void empiler(Pile **P,Card *c){
	Pile *nouveau;
	nouveau=(Pile *)malloc(sizeof(Pile));
	nouveau->C=c;
	nouveau->previous=NULL;
	if(*P==NULL){
		nouveau->next=NULL;
		*P=nouveau;
		return;
	}
	nouveau->next=*P;
	(*P)->previous=nouveau;
	*P=nouveau;
}
//countpile
int CountPile(Pile *P){
	int count=0;
	Pile *pt;
	for(pt=P;pt!=NULL;pt=pt->next){
		count++;
	}
	return count;
}
//pop
void pop (Pile **P){
	if(*P==NULL) return;
	if (CountPile(*P) == 1){
		*P=NULL;
		return;
	}
	Pile *temp;
	temp = *P;
	*P=(*P)->next;
	(*P)->previous=NULL;
	free(temp);
}
//peek
Card *peek(Pile *P){
	if(P==NULL) return;
	Card *c;
	c=P->C;
	return c;
}
//initialiser les piles
void PileNULL(Pile **P,int index){
	int i;
	for(i=0;i<index;i++){
		P[i]=NULL;
	}
}
//fonction pour modifier les couleurs
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}
// des fonctions pour l'affichage et la distibution : afficher - arriverfin - afficherpilezone1- afficherpilezone23 :
	//afficher
void afficher(Pile *pt){
	if(pt==NULL){
		printf("\t");
		return;
	}
	char type; //pour transformer le type qui est un caractere en symbole 
        switch (pt->C->type) {
            case ('H'): type=3; break;  // Heart
            case ('S'): type=6; break;  // Spade
            case ('C'): type=5; break;  // Club
            case ('D'): type=4; break;  //diamonds
        }
        //pour les couleurs
        if(pt->C->couleur == 'R'){
        	Color(4,15);
	        if (pt->C->chiffre == 1) printf("A %c \t", type);
	        else if (pt->C->chiffre == 11) printf("J %c \t",type);
	        else if (pt->C->chiffre == 12) printf("Q %c \t",type);
	        else if (pt->C->chiffre == 13) printf("K %c \t",type);
	        else printf("%d %c \t", pt->C->chiffre, type);
	        Color(15,0);
    	}
    	if(pt->C->couleur == 'N'){
    		Color(0,15);
	        if (pt->C->chiffre == 1) printf("A %c \t", type);
	        else if (pt->C->chiffre == 11) printf("J %c \t",type);
	        else if (pt->C->chiffre == 12) printf("Q %c \t",type);
	        else if (pt->C->chiffre == 13) printf("K %c \t",type);
	        else printf("%d %c \t", pt->C->chiffre, type);
	        Color(15,0);
    }
}
	//arriverfin : pour afficher du dernier element au premier
Pile *arriverFin(Pile *pt){
	Pile *temp;
	if(pt==NULL) return NULL;
	while(pt!=NULL){
		temp=pt;
		pt=pt->next;
	}
	return temp;
}
	//pour afficher les piles de zone 1 verticalement
void afficherPileZone1(Pile **P1){
	int i,j;
	Pile *pt[8];
	for(i=0;i<8;i++){
		pt[i]=P1[i];
	}
	Pile *temp[8];
	for(i=0;i<8;i++){
		temp[i]=arriverFin(pt[i]);
	}
	for(i=0;i<8;i++){
		pt[i]=temp[i];
	}
	while(pt[0]!=NULL || pt[1]!=NULL || pt[2]!=NULL || pt[3]!=NULL || pt[4]!=NULL || pt[5]!=NULL || pt[6]!=NULL || pt[7]!=NULL){
		for(i=0;i<8;i++){
			afficher(pt[i]);
			if(pt[i]!=NULL) 
				pt[i]=pt[i]->previous;
		}
		printf("\n");
		printf("\n");
	}
}
   //pour afficher les piles de zone2
void afficherPileZone2(Pile *P){
	Pile *pt=P;
	afficher(pt);
}
	//pour afficher les piles de zone3
void afficherPileZone3(Pile *P){
	if(P==NULL){
		printf("\n");
		printf("\n");
		return;
	}
	Pile *pt;
	pt=P;
	Pile *temp=arriverFin(pt);
    for (pt = temp; pt != NULL; pt = pt->previous) {
        afficher(pt);
    }
    printf("\n");
    printf("\n");
}
	//fonction principale distribuer
void Distribuer(Pile **P1, Pile **P2, Pile **P3){
	printf("---------------------------------------------ZONE 1 : Zone des cartes----------------------------------------------------------------- \n");
	Color(1,15);
	printf("\n A \t B \t C \t D \t E \t F \t G \t H \n");
	printf("\n");
	afficherPileZone1(P1);
	printf("\n---------------ZONE 2 : LES CELLULES LIBRES-------------------------\n");
	printf("\nI : ");afficherPileZone2(P2[0]);
	printf("\tJ : ");afficherPileZone2(P2[1]);
	printf("\tK : ");afficherPileZone2(P2[2]);
	printf("\tL : ");afficherPileZone2(P2[3]);  
	printf("\n\n------------------------ZONE 3 : LES CELLULES DE GAIN-------------------------------------\n");
	char H=3 , C=5 , D=4 , S=6 ;
	printf("CELLULE DE  CLUBS    %c   M : ",C);afficherPileZone3(P3[0]);
	printf("CELLULE DE HEART     %c   N : ",H);afficherPileZone3(P3[1]);
	printf("CELLULE DE SPADES    %C   O : ",S);afficherPileZone3(P3[2]);
	printf("CELLULE DE DIAMONDS  %C   P : ",D);afficherPileZone3(P3[3]);   
}

// des fonctions pour les cartes de jeu : initialiser et melanger les cartes
Card *initialiserCard(int chiff,char ty , char coul){
	Card *C;
	C=(Card *)malloc(sizeof(Card));
	C->chiffre=chiff;
	C->type=ty;
	C->couleur=coul;
	return C;
}
void melangerCartes(Card *cartes[], int size) {
	int i;
    for (i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Échange les pointeurs de cartes[i] et cartes[j]
        Card *temp = cartes[i];
        cartes[i] = cartes[j];
        cartes[j] = temp;
    }
}
//fonctions pour jouer FREECELL
	//pour demader à l'utilisateur qu'est-ce-qu'il veut faire
int Jeu(int *jeu){
	char buffer[256];
	do{
		printf("\t\t veuillez tapez un nombre entre 1 et 6 : ");
		if(scanf("%d",jeu)!=1){
			Color(4,0);
			printf("\t\t Errreur de saisie . Entrez un entier \n");
			Color(15,0);
			fgets(buffer, sizeof(buffer), stdin);
			*jeu=0;
		}
    }while(*jeu==0);
    if(*jeu > 6 || *jeu < 1){
    	Color(4,0);
    	printf("\t\t Erreur . veuillez tapez un nombre convenable s'il vous plait \n");
    	Color(15,0);
    	return 0;
	}
	return 1;
}
	//pour transformer le caractere que l'utilisateur va entrer en pile qu'on peut manipuler
Pile *FromCharToPile(char C,Pile **P1, Pile **P2, Pile **P3){
	Pile *pi;
	int i,j=C;
	for(i=0;i<8;i++){
		if(j==i+65)
			pi=P1[i];
	}
	for(i=0;i<4;i++){
		if(j==i+73)
			pi=P2[i];
	}
	for(i=0;i<4;i++){
		if(j==i+77)
			pi=P3[i];
	}
	return pi;
}

	//fonction pour tout deplacement entre une zone1-2 et zone 1
int DeplacementToZone1(char *deb, char*fi, Pile **debut, Pile **fin, Pile **P1, Pile **P2, Pile **P3){
	printf("\t\t dans quelle pile se trouve cette carte (pile de debut soit de zone 1 ou de zone 2) : ");
	scanf(" %c", deb);
	printf("\t\t ou vous voulez la transferer (pile fin): ");
	scanf(" %c", fi);
	if (*deb > 'L' || *deb < 'A' || *fi > 'H' || *fi < 'A')
		return 0;
	*debut=FromCharToPile(*deb,P1,P2,P3);
	*fin=FromCharToPile(*fi,P1,P2,P3);
	if(*debut == NULL)
		return -1;
	Card *c1=peek(*debut);
	if(*fin == NULL){
		empiler(fin,c1);
		pop(debut);
		return 1;
	}
	Card *c2=peek(*fin);
	if (c2->chiffre-c1->chiffre!=1 || c2->couleur==c1->couleur)
		return -1;
	empiler(fin,c1);
	pop(debut);
	return 1;
}
	//fonction pour tout deplacement entre une zone1-2 et zone 2
int DeplacementToZone2(char *deb, char*fi, Pile **debut, Pile **fin, Pile **P1, Pile **P2, Pile **P3){
	printf("\t\t dans quelle pile se trouve cette carte (pile de debut soit de zone 1 ou de zone 2) : ");
	scanf(" %c", deb);
	printf("\t\t ou vous voulez la transferer (pile de fin) : ");
	scanf(" %c", fi);
	if (*deb >'L' || *deb < 'A' || *fi > 'L' || *fi < 'I')
		return 0;
	*debut=FromCharToPile(*deb,P1,P2,P3);
	*fin=FromCharToPile(*fi,P1,P2,P3);
	if (*fin != NULL || *debut == NULL)
		return -1;
	Card *c1=peek(*debut);
	empiler(fin,c1);
	pop(debut);
	return 1;
}
	//fonction pour tout deplacement entre une zone1-2 et zone 3
int DeplacementToZone3(char *deb, char*fi, Pile **debut, Pile **fin, Pile **P1, Pile **P2, Pile **P3){
	printf("\t\t dans quelle pile se trouve cette carte (pile de debut soit de zone 1 ou de zone 2) : ");
	scanf(" %c", deb);
	printf("\t\t ou vous voulez la transferer (pile de fin) : ");
	scanf(" %c", fi);
	if (*deb > 'L' || *deb < 'A' || *fi > 'P' || *fi < 'M')
		return 0;
	*debut=FromCharToPile(*deb,P1,P2,P3);
	*fin=FromCharToPile(*fi,P1,P2,P3);
	if(*debut == NULL)
		return -1;
	Card *c1=peek(*debut);
	if(*fin == NULL && c1->chiffre != 1 )
		return -1;
	if(*fin == NULL && c1->chiffre == 1){
		switch(*fi){ //pour respecter le type des piles quand les piles sont encores nulles
			case 'M':
				if(c1->type != 'C')
					return -2;
				break;
			case 'N':
				if(c1->type != 'H')
					return -2;
				break;
			case 'O':
				if(c1->type != 'S')
					return -2;
				break;
			case 'P':
				if(c1->type != 'D')
					return -2;
				break;
		}
		empiler(fin,c1);
		pop(debut);
		return 1;
	}
	if(*fin != NULL){
		Card *c2=peek(*fin);
			if (c1->chiffre-c2->chiffre!=1 || c2->type!=c1->type)
				return -1;
		empiler(fin,c1);
		pop(debut);
		return 1;
	}
}
//fonctions game over:
	//fonction gagner
int GagnerJeu(Pile **P){
	int i;
	int count=0;
	for(i=0;i<4;i++){
		if(CountPile(P[i])==13)
			count++;
	}
	if(count==4)
		return 1;
	return 0;
}
	//fonctions perdre (blockage) :
		//blockage entre zone1 et zone2
int BlocageZone1_Zone2(Card *c1,Card *c2){
	if (c1->chiffre-c2->chiffre == 1 && c2->couleur!=c1->couleur){
		return 0;
	}
	return 1;
}
		//blockage entre les piles de la zone 1
int BlocageZone1(Card *c1 , Card *c2){
	if((c2->chiffre-c1->chiffre == 1 && c2->couleur!=c1->couleur) || (c1->chiffre-c2->chiffre == 1 && c2->couleur!=c1->couleur)){
		return 0;
	}
	return 1; 
}
		//blockage entre zone1-2 et zone3	
int BlocageZone3(Card *c1 , Card *c2){
	if (c1->type == c2->type && c1->chiffre-c2->chiffre == 1){
		return 0;
	}
	return 1;
}
		//fonction blockage principale
int Blocage(Pile **P1, Pile **P2, Pile **P3){
	int i,j,k,l,m=0,count=0;
	for(i=0;i<8;i++){
		if(P1[i]==NULL)
			return 0;
	}
	for(i=0;i<4;i++){
		if(P2[i]==NULL)
			return 0;
	}
	Card *C1[8];
	Card *C2[4];
	Card *C3[4];
	j=0;
	for(i=0;i<8;i++){
		C1[i]=peek(P1[j]);
		j++;
	}
	j=0;
	for(i=0;i<4;i++){
		C2[i]=peek(P2[j]);
		j++;
	}
	if(P3[0]==NULL){
		C3[0]=initialiserCard(0,'C','N');
	}
	else
		C3[0]=peek(P3[0]);
	if(P3[1]==NULL){
		C3[1]=initialiserCard(0,'H','R');
	}
	else
		C3[1]=peek(P3[1]);
	if(P3[2]==NULL){
		C3[2]=initialiserCard(0,'S','N');
	}
	else
		C3[2]=peek(P3[2]);
	if(P3[3]==NULL){
		C3[3]=initialiserCard(0,'D','R');
	}
	else
		C3[3]=peek(P3[3]);
	for(i=0;i<8;i++){
		for(j=i+1;j<8;j++){
			if(BlocageZone1(C1[i],C1[j])==1)
				count++;
		}
		for(k=0;k<4;k++){
			if(BlocageZone1_Zone2(C1[i],C2[k])==1)
				count++;
		}
		for(l=0;l<4;l++){
			if(BlocageZone3(C1[i],C3[l])==1)
				count++;
		}
	}
	for(i=0;i<4;i++){
		for(l=0;l<4;l++){
			if(BlocageZone3(C2[i],C3[l])==1)
				count++;
		}
	}
	if(count==108)
		return 1;
	return 0;
}
void UpdatePile(char deb, char fi, Pile *debut, Pile *fin, Pile **P1, Pile **P2, Pile **P3){
	int i;
	int j=deb;
	int k=fi;
	for(i=0;i<8;i++){
		if(j==i+65)
			P1[i]=debut;
		if(k==i+65)
			P1[i]=fin;	
	}
	for(i=0;i<4;i++){
		if(j==i+73)
			P2[i]=debut;
		if(k==i+73)
			P2[i]=fin;	
	}
	for(i=0;i<4;i++){
		if(j==i+77)
			P3[i]=debut;
		if(k==i+77)
			P3[i]=fin;	
	}
}
void Rejouer(int *rejouer){
	printf("voulez vous continuer a jouer ? \n");
	printf("Pour rejouez cette partie veuillez tapez sur 2\n");
	printf("Pour une nouvelle partie veuillez tapez sur 1\n");
	printf("Pour quitter veuillez tapez sur 0\n");
	do{
	printf("tapez un nombre entre 0 et 2 : ");
	scanf("%d",rejouer);
	Color(4,0);
	if(*rejouer < 0 || *rejouer > 2)
		printf("Erreur . veuillez tapez un nombre convenable s'il vous plait \n");
	Color(15,0);
	}while(*rejouer < 0 || *rejouer > 2);
}
// Fonction pour effacer l'écran (Unix/Linux)
void effacerEcranUnix() {
    system("clear");
}

// Fonction pour effacer l'écran (Windows)
void effacerEcranWindows() {
    system("cls");
}
