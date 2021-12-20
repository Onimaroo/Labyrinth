#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <MLV/MLV_all.h>
#define LONGUEUR 700
#define LARGUEUR 700


typedef struct {
	int x;	
	int y;
} Cellule;


typedef struct {
	int mur_hori;
	int mur_vert;
} Labyrinthe;


/* Fonction qui initialise les tableaux 
peres rang et labyrinthe,où chaque case appartient 
à sa propre case et donc leurs rangs vaut 1 */

Cellule ** InitialisationPeres(Cellule **peres, int n, int m) {
	int i, j;
	Cellule cell;
	peres = (Cellule **) malloc(sizeof(Cellule *) * n);

	for (i = 0; i != n; i++) {
		peres[i] = (Cellule *) malloc(sizeof(Cellule ) * m);
		for (j = 0; j != m; j++) {
			cell.x = i;
			cell.y = j;
			peres[i][j] = cell;
		}
	}

	return peres;
}


int ** InitialisationRang(int **rang, int n, int m) {
	int i, j;
	rang = (int **) malloc(sizeof(int *) * n);

	for (i = 0; i != n; i++) {
		rang[i] = (int *) malloc(sizeof(int) * m);
		for (j = 0; j != m; j++)
			rang[i][j] = 1;
	}

	return rang;
}


Labyrinthe ** InitialisationLabyrinthe(Labyrinthe **mur, int n, int m) {
	int i, j;

	mur = (Labyrinthe **) malloc(sizeof(Labyrinthe *) * n);

	for (i = 0; i != n; i++) {
		mur[i] = (Labyrinthe *) malloc(sizeof(Labyrinthe) * m);

		for (j = 0; j != m; j++) {
			mur[i][j].mur_hori = 1;
			mur[i][j].mur_vert = 1;
		}
	}

	return mur;
}


void Initialisation(Cellule ***peres, int ***rang, Labyrinthe ***mur, int n, int m) {
	*peres = InitialisationPeres(*peres, n, m);
	*rang = InitialisationRang(*rang, n, m);
	*mur = InitialisationLabyrinthe(*mur, n, m);
}

/* Permet de trouver le représentant 
de classe d'une case */

Cellule TrouveNaif(Cellule **peres, Cellule cell) {
	Cellule repr;
	repr = peres[cell.x][cell.y];

	while ((repr.x != peres[repr.x][repr.y].x) && (repr.y != peres[repr.x][repr.y].y))
		repr = peres[repr.x][repr.y];

	return repr;
}


Cellule TrouveCompresse(Cellule **peres,Cellule cell){
	if((peres[cell.x][cell.y].x != cell.x) || (peres[cell.x][cell.y].y != cell.y))
		peres[cell.x][cell.y] = TrouveCompresse(peres, peres[cell.x][cell.y]);
	return peres[cell.x][cell.y];
}


/* Fonction qui retourne 1 si 
deux cases sont dans la même
classe et 0 sinon */

int MemeClasse(Cellule **peres, Cellule cel1, Cellule cel2) {
	Cellule repr1, repr2;
	repr1 = TrouveNaif(peres, cel1);
	repr2 = TrouveNaif(peres, cel2);

	if (repr1.x == repr2.x && repr1.y == repr2.y)
		return 1;
	return 0;
}


/* Réalise la fusion des deux 
ensembles de deux cases */


void FusionRang(Cellule **peres, int **rang, Cellule cell, Cellule cell2) {
	Cellule repr1, repr2;

	repr1 = TrouveNaif(peres, cell);
    repr2 = TrouveNaif(peres, cell2);

    if(repr1.x != repr2.x || repr1.y != repr2.y) {
	    if (rang[repr1.x][repr1.y] >= rang[repr2.x][repr2.y]) {
	    	peres[repr2.x][repr2.y] = repr1;
	    	if (rang[repr1.x][repr1.y] == rang[repr2.x][repr2.y])
	    		rang[repr1.x][repr1.y] += 1;
	    }

	    else
	    	peres[repr1.x][repr1.y] = repr2;
	}
}


void AffichageGraphique(Labyrinthe **mur, int n, int m) {
	int i, j;
	int pas_x, pas_y;

	pas_x = LONGUEUR / m;
	pas_y = LARGUEUR / n;

	MLV_draw_line(0, 0, (m * pas_x), 0, MLV_COLOR_WHITE);
	MLV_draw_line(0, pas_y, 0, (n * pas_y), MLV_COLOR_WHITE);
	MLV_draw_line(0, (n * pas_y) - 1, (m * pas_x), (n* pas_y) - 1, MLV_COLOR_WHITE);
	MLV_draw_line((m * pas_x) - 1, ((n -1 ) * pas_y), (m * pas_x) - 1, 0, MLV_COLOR_WHITE);

	for (i = 0; i != n * pas_y ; i += pas_y){
		for (j = 0; j != m * pas_x; j += pas_x) {
			if ((j != (m - 1) * pas_x || i != (n - 1) * pas_y) && mur[i / pas_y][j / pas_x].mur_vert == 1){
				MLV_draw_line(j + pas_x, i, j + pas_x, i + pas_y, MLV_COLOR_WHITE);
			}
			if (mur[i / pas_y][j / pas_x].mur_hori == 1)
				MLV_draw_line(j, i + pas_y, j +pas_x, i + pas_y, MLV_COLOR_WHITE);	
		}		
	}
}


/*
void affiche_labyrinthe(Labyrinthe **mur, int n, int m) {
	int i, j;
	for(i = 0; i < n; i++) {
		for(j = 0; j < m; j++) {
			printf("%d:%d	", mur[i][j].mur_hori, mur[i][j].mur_vert);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
}

*/

void AffichageTexte(Labyrinthe **mur, int n, int m) {
	int i, j;

	printf("+");
	for (i = 0; i < m; i++) {
		printf("---");
		printf("+");
	}

	printf("\n");

	for (i = 0; i != 2 * n; i += 1) {
		if((i % 2) != 0) {

			printf("+");

			for (j = 0; j != m; j += 1) {
				if (mur[i / 2][j].mur_hori == 1){
					printf("---");
					printf("+");
				}

				else
					printf("   +");
			}
		}

		else {

			if (i != 0)
				printf("|");
			else
				printf(" ");

			for (j = 0; j != m; j += 1) {
				if((i == 2 * n - 2) && (j == m - 1)) {
					printf("    ");
					break;
				}
				if (mur[i / 2][j].mur_vert == 1)
					printf("   |");
				
				else
					printf("    ");
			}
		}

		printf("\n");
	}
	printf("\n\n");
}


int main(int argc, char * argv[]) {
	char mot[10];
	char x[4], y[4];
	int i = 0, j = 0, k = 0;
	int n, m;
	int graine;
	int attente;
	int verif, mur_check;
	int unique = 0;
    Cellule origine, fin;
    Cellule test1, test2;
    int **rang =NULL;
    Cellule **peres = NULL;
    Labyrinthe **mur = NULL;
    attente = -1;
    verif = 1;
    n = 6;
    m = 8;

	srand(time(NULL));

    if (argc > 1){
		for (k = 1; k < argc; k++) {
			for (i = 0; argv[k][i - 1] != '='; i++) {
				mot[i] = argv[k][i];
			}
			if (strcmp(mot, "--taille=") == 0) {
				j = 0;
				while (argv[k][i] != 'x') {
					x[j] = argv[k][i];
					i += 1;
					j += 1;
				}
				
				j = 0;
				while (argv[k][i] != '\0') {
					y[j] = argv[k][i + 1];
					i += 1;
					j += 1;
				}

				if (atoi(x) != 0 && atoi(y) != 0){
					n = atoi(x);
					m = atoi(y);

				}

			}

			else if (strcmp(mot, "--graine=") == 0) {
				j = 0;

				while (argv[k][i] != '\0') {
					x[j] = argv[k][i];
					i += 1;
					j += 1;
				}

				if (atoi(x) != 0){
					graine = atoi(x);
					srand(graine);
				}

			}

			else if (strcmp(mot, "--attente=") == 0) {
				j = 0;

				while (argv[k][i] != '\0') {
					x[j] = argv[k][i];
					i += 1;
					j += 1;
				}
				attente = atoi(x);
			}

			else if (strcmp(argv[k], "--mode=texte") == 0){
				verif = 0;
			}

			else if (strcmp(argv[k], "--unique") == 0){
				unique = 1;
			}
		}

    }

    origine.x = 0;
    origine. y = 0;
    fin.x = (n - 1);
    fin.y = (m - 1);

   	Initialisation(&peres, &rang, &mur, n, m);

    if (verif == 1){
    	MLV_create_window("Labyrinthe"," ", LONGUEUR, LARGUEUR);

    	AffichageGraphique(mur, n, m);
    	MLV_actualise_window();
    }

   	while (MemeClasse(peres, origine, fin) == 0) {

    	test1.x = rand() % n;
    	test1.y = rand() % m;

		mur_check = rand() % 2;

		if (test1.x == (n - 1) && test1.y == (m - 1) && mur_check == 0)
			test1.x -= 1;

		else if (test1.x == (n - 1) && test1.y == (m - 1) && mur_check == 1)
			test1.y -= 1;

		if (mur_check == 0 && test1.x == (n - 1))
			mur_check = 1;

		if (mur_check == 1 && test1.y == (m - 1))
			mur_check = 0;
		

		if (mur_check == 0){
			mur[test1.x][test1.y].mur_hori = 0;
			test2.x = test1.x + 1;
			test2.y = test1.y;
			if(unique == 1) {
				if(MemeClasse(peres, test1, test2) == 1)
					mur[test1.x][test1.y].mur_hori = 1;
			}
			mur[test1.x][test1.y].mur_hori = 0;
		}

		else{
			test2.x = test1.x;
			test2.y = test1.y + 1;
			if(unique == 1) {
				if(MemeClasse(peres, test1, test2) == 1)
					mur[test1.x][test1.y].mur_vert = 1;
			}
			mur[test1.x][test1.y].mur_vert = 0;
		}
	
    	TrouveCompresse(peres, test1);
    	FusionRang(peres, rang, test1, test2);


    	if (verif == 0) {
			if (attente >= 0)
				sleep(attente);
			AffichageTexte(mur, n, m);
    	}

		else {
			if (attente >= 0)
				MLV_wait_seconds(attente);
    		MLV_clear_window(MLV_COLOR_BLACK);
			AffichageGraphique(mur, n, m);
    		MLV_actualise_window();
		}
    }
 
    if (verif == 1){
    	MLV_wait_seconds(60);
    	MLV_free_window();
    }

    return 0;
}
