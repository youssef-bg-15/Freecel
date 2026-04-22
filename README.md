# FreeCell — Projet Langage C

Implémentation en C du jeu de cartes **FreeCell** en mode console (Windows), développée dans le cadre du module Langage C à l'ENSA d'Oujda (IIDSCC, 3ᵉ année).

**Auteur :** Boulghalegh Youssef
**Encadrant :** Abdelwahab Naji
**Année universitaire :** 2023/2024

---

## Table des matières

- [Description du jeu](#description-du-jeu)
- [Règles](#règles)
- [Structure du projet](#structure-du-projet)
- [Modélisation](#modélisation)
- [Les trois zones](#les-trois-zones)
- [Fonctions principales](#fonctions-principales)
- [Compilation](#compilation)
- [Utilisation](#utilisation)
- [Scénario d'exécution](#scénario-dexécution)
- [Démonstration et rapport](#démonstration-et-rapport)

---

## Description du jeu

FreeCell (ou « cellule libre ») est un jeu de solitaire jouable avec un jeu de 52 cartes :
- 13 carreaux (♦)
- 13 piques (♠)
- 13 cœurs (♥)
- 13 trèfles (♣)

Le plateau est composé de **16 cases** réparties en 3 zones :
- **Zone 1** — 8 colonnes contenant initialement toutes les cartes distribuées.
- **Zone 2** — 4 cellules libres pouvant contenir une carte chacune.
- **Zone 3** — 4 cases de gain (fondations), une par type.

**Objectif :** transférer toutes les cartes de la zone 1 vers la zone 3, triées par type et dans l'ordre As → Roi.

---

## Règles

- On déplace les cartes **une par une**.
- En zone 1, une carte peut être posée sur une carte de rang immédiatement supérieur et de **couleur opposée** (exemple : un 4 ♣ ou 4 ♠ peut être posé sur un 5 ♥ ou 5 ♦).
- En zone 2, chaque cellule libre accepte **au maximum une carte**.
- En zone 3, on empile du plus petit (As) au plus grand (Roi), **même type** obligatoirement.
- Une **colonne vide** de la zone 1 peut recevoir n'importe quelle carte.
- La partie se termine lorsqu'aucun mouvement n'est plus possible (**blocage**, partie perdue) ou lorsque toutes les cartes sont dans la zone 3 (**victoire**).

Référence : [Wikipedia — FreeCell](https://fr.wikipedia.org/wiki/FreeCell)

---

## Structure du projet

```
Boulghalegh_Youssef/
├── head.h                        # Déclarations : structures + prototypes
├── lmpl.c                        # Implémentations des fonctions
├── main.c                        # Point d'entrée / boucle de jeu
├── Makefile.win                  # Script de compilation (MinGW64)
├── Freecell-game-project.dev     # Projet Dev-C++
├── Freecell-game-project.exe     # Binaire compilé
├── Freecell-game-project.layout  # Layout Dev-C++
├── lmpl.o / main.o               # Objets de compilation
├── DEMO.mp4                      # Vidéo de démonstration
├── RAPPORT_freecel.pdf           # Rapport du projet
└── README.md                     # Ce fichier
```

---

## Modélisation

Deux structures sont définies dans [head.h](head.h) :

### `Card`
Représente une carte.
```c
typedef struct {
    char type;     // 'H' = Heart, 'D' = Diamond, 'C' = Club, 'S' = Spade
    char couleur;  // 'R' = Rouge, 'N' = Noir
    int  chiffre;  // 1 (As) .. 13 (Roi)
} Card;
```

### `Pile`
Liste doublement chaînée utilisée comme pile (LIFO).
```c
typedef struct element {
    Card *C;
    struct element *next;
    struct element *previous;
} Pile;
```

---

## Les trois zones

Les zones sont déclarées dans [main.c:8-10](main.c#L8-L10) sous forme de tableaux de piles :

| Zone | Déclaration | Cases | Lettres |
|------|-------------|-------|---------|
| Zone 1 — colonnes de jeu | `Pile *Zone1[8]` | 8 | A, B, C, D, E, F, G, H |
| Zone 2 — cellules libres | `Pile *Zone2[4]` | 4 | I, J, K, L |
| Zone 3 — fondations      | `Pile *Zone3[4]` | 4 | M (♣), N (♥), O (♠), P (♦) |

**Distribution initiale :**
- Colonnes A à D : 7 cartes chacune
- Colonnes E à H : 6 cartes chacune
- Ordre aléatoire grâce à `melangerCartes` (algorithme de Fisher–Yates)

---

## Fonctions principales

| Catégorie | Fonctions | Emplacement |
|-----------|-----------|-------------|
| **Primitives de pile** | `empiler`, `pop`, `peek`, `CountPile`, `PileNULL` | [lmpl.c:6-55](lmpl.c#L6-L55) |
| **Affichage** | `afficher`, `afficherPileZone1/2/3`, `Distribuer`, `Color`, `arriverFin` | [lmpl.c:57-169](lmpl.c#L57-L169) |
| **Initialisation des cartes** | `initialiserCard`, `melangerCartes` | [lmpl.c:172-189](lmpl.c#L172-L189) |
| **Saisie utilisateur** | `Jeu`, `FromCharToPile` | [lmpl.c:192-229](lmpl.c#L192-L229) |
| **Déplacements (avec validation des règles)** | `DeplacementToZone1`, `DeplacementToZone2`, `DeplacementToZone3` | [lmpl.c:232-319](lmpl.c#L232-L319) |
| **Détection fin de partie** | `GagnerJeu`, `Blocage`, `BlocageZone1`, `BlocageZone1_Zone2`, `BlocageZone3` | [lmpl.c:322-422](lmpl.c#L322-L422) |
| **Maintenance** | `UpdatePile`, `Rejouer`, `effacerEcranWindows`, `effacerEcranUnix` | [lmpl.c:423-468](lmpl.c#L423-L468) |

### Rôle de quelques fonctions clés

- **`initialiserCard(chiffre, type, couleur)`** — Alloue et renvoie une nouvelle carte.
- **`melangerCartes(cartes[], size)`** — Mélange aléatoire de Fisher–Yates.
- **`Distribuer(Zone1, Zone2, Zone3)`** — Affiche le plateau complet.
- **`DeplacementToZoneX`** — Lit les cases de départ et d'arrivée, vérifie la conformité aux règles de la zone `X`, effectue le déplacement si valide.
- **`GagnerJeu(Zone3)`** — Renvoie 1 si les 4 fondations contiennent chacune 13 cartes.
- **`Blocage(Zone1, Zone2, Zone3)`** — Renvoie 1 si aucun déplacement n'est plus possible.
- **`UpdatePile`** — Synchronise les tableaux Zone1/Zone2/Zone3 avec les têtes de pile après un déplacement.

---

## Compilation

### Avec Dev-C++
Ouvrir `Freecell-game-project.dev` puis lancer la compilation (F9).

### Avec MinGW / GCC (ligne de commande)
```bash
gcc -c lmpl.c -o lmpl.o
gcc -c main.c -o main.o
gcc lmpl.o main.o -o Freecell-game-project.exe
```

### Avec le Makefile fourni
```bash
mingw32-make -f Makefile.win
```

> **Note :** Le projet dépend de `windows.h` (pour les couleurs de console via `SetConsoleTextAttribute`). Il est donc destiné à **Windows**.

---

## Utilisation

Lancer l'exécutable :
```bash
./Freecell-game-project.exe
```

### Menu principal
À chaque tour, le joueur choisit une action :

| Touche | Action |
|--------|--------|
| 1 | Déplacer une carte vers la zone 1 |
| 2 | Déplacer une carte vers la zone 2 (cellule libre) |
| 3 | Déplacer une carte vers la zone 3 (fondation) |
| 4 | Rejouer la partie en cours |
| 5 | Nouvelle partie (nouveau mélange) |
| 6 | Quitter |

### Exemple de déplacement
```
Choix : 1
Dans quelle pile se trouve cette carte : A
Où vous voulez la transférer : C
```
Déplace la carte du haut de la colonne `A` vers la colonne `C` (si les règles le permettent).

---

## Scénario d'exécution

1. **Initialisation** — Les 52 cartes sont créées, mélangées, puis distribuées en zone 1.
2. **Boucle de jeu** — Tant que le joueur n'a pas gagné ou que la partie n'est pas bloquée :
   - Affichage du plateau complet.
   - Saisie de l'action (1–6).
   - Si déplacement : vérification des règles, puis mise à jour.
   - Si erreur : message coloré en rouge indiquant la nature (piles invalides, règle non respectée, type incorrect pour une fondation).
3. **Fin de partie** — Message de victoire (vert) ou de défaite (rouge), puis proposition de rejouer, de commencer une nouvelle partie ou de quitter.

---

## Démonstration et rapport

- 📽️ **Vidéo de démonstration :** [DEMO.mp4](DEMO.mp4) — structure, fonctions principales et exemple de partie.
- 📄 **Rapport complet :** [RAPPORT_freecel.pdf](RAPPORT_freecel.pdf) — modélisation, explication des fonctions, captures d'écran.

---

## Références

- [FreeCell — Wikipédia](https://fr.wikipedia.org/wiki/FreeCell)
- [Règles du jeu — freecell.fr](https://www.freecell.fr/reglesdujeudefreecell.php)
- [Jouer en ligne — freecell.fr](https://www.freecell.fr/jouerafreecell/freecell-solitaire-classique.php)
