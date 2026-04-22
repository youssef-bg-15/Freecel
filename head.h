#ifndef HEAD_HEADER
#define HEAD_HEADER
//les structures necessaires
typedef struct {
	char type; // HEART: H  diamonds : D   clubs : C    spades : S
	char couleur; // Rouge : R    Noir: N
	int chiffre;
}Card;
typedef struct element{
	Card *C;
	struct element *next;
	struct element *previous;
}Pile;
void empiler(Pile **P,Card *c);
int CountPile(Pile *P);
void pop (Pile **P);
Card *peek(Pile *P);
void PileNULL(Pile **P,int index);
void Color(int couleurDuTexte,int couleurDeFond);
void afficher(Pile *pt);
Pile *arriverFin(Pile *pt);
void afficherPileZone1(Pile **P1);
void afficherPileZone2(Pile *P);
void afficherPileZone3(Pile *P);
void Distribuer(Pile **P1, Pile **P2, Pile **P3);
Card *initialiserCard(int chiff,char ty , char coul);
void melangerCartes(Card *cartes[], int size);
int Jeu(int *jeu);
Pile *FromCharToPile(char C,Pile **P1, Pile **P2, Pile **P3);
int DeplacementToZone1(char *deb, char*fi, Pile **debut, Pile **fin, Pile **P1, Pile **P2, Pile **P3);
int DeplacementToZone2(char *deb, char*fi, Pile **debut, Pile **fin, Pile **P1, Pile **P2, Pile **P3);
int DeplacementToZone3(char *deb, char*fi, Pile **debut, Pile **fin, Pile **P1, Pile **P2, Pile **P3);
int GagnerJeu(Pile **P);
int BlocageZone1_Zone2(Card *c1,Card *c2);
int BlocageZone1(Card *c1,Card *c2);
int BlocageZone3(Card *c1 , Card *c2);
int Blocage(Pile **P1, Pile **P2, Pile **P3);
void UpdatePile(char deb, char fi, Pile *debut, Pile *fin, Pile **P1, Pile **P2, Pile **P3);
void Rejouer(int *rejouer);
void effacerEcranUnix(void);
void effacerEcranWindows(void); 
#endif
