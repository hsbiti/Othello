/**
  * @date 22/05/2016
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define N 8
#define MAX_LEN 128


char joueur1[50];
char joueur2[50];
int turn=1;
char jeu[2];
int score_j1, score_j2;
int contre_ia; /* 0 si joueur contre joueur, 1 si joueur contre PC*/


/* X == Noir
   O == Blanc */
int	plateau [N][N];



void afficher_plateau()
{
	int	x, y;
	score_j1 = 0; score_j2 = 0;
	printf("    A   B   C   D   E   F   G   H \n");
	printf("  +-------------------------------+\n");
	for (y = 0; y < N; y++) {
		printf("%d |",y+1);
		for (x = 0; x < N; x++) {
			if (plateau[x][y] == 0)	printf("   |");
			else if (plateau[x][y] == 1) { printf(" X |"); score_j1++;}
			else if (plateau[x][y] == 2) { printf(" O |"); score_j2++; }
		}
		printf("%d\n",y+1);
		printf("  +-------------------------------+\n");
	}
		printf("    A   B   C   D   E   F   G   H \n\n");

	printf("====== SCORE : \"%s\": %d, \"%s\": %d ======\n\n",joueur1, score_j1, joueur2, score_j2);

}


void initialiser()
{
	plateau[4][3] = 1;
	plateau[3][4] = 1;

	plateau[3][3] = 2;
	plateau[4][4] = 2;

}


bool test_adjacence (int x, int y)
{

	/* Dernière case en bas à droite */
	if (
		(x == 7 && y == 7)
		&& (!plateau[x-1][y] && !plateau[x-1][y-1] && !plateau[x][y-1])
		)
		return false;

	/* Dernière case en haut à droite */
	if (
		(x == 7 && y == 0)
		&& (!plateau[x-1][y] && !plateau[x][y+1] && !plateau[x-1][y-1])
		)
		return false;

	/* Première case en haut à gauche */
	if (
		(x == 0 && y == 0)
		&& (!plateau[x+1][y] && !plateau[x+1][y-1] && !plateau[x][y+1])
		)
		return false;

	/* Première case en bas à gauche */
	if (
		(x == 0 && y == 7)
		&& (!plateau[x][y-1] && !plateau[x+1][y-1] && !plateau[x+1][y])
		)
		return false;

	/* Cas normal */
	if (!plateau[x+1][y] && !plateau[x+1][y+1] && !plateau[x][y+1] && !plateau[x-1][y+1] 
        && !plateau[x-1][y] && !plateau[x-1][y-1] && !plateau[x][y-1] && !plateau[x+1][y-1])
		return false;


	return true;
}


bool case_valide(int x, int y)
{
	if ((x >= 0) && (x < N) && (y >= 0) && (y < N))
		return true;
	else return false;
}


bool test_coup (int x, int y)
{

	int autre = (turn == 1) ? 2 : 1;

    if (!case_valide(y, x) || plateau[x][y] != 0)
    	return false;

    int i, j, ok;

    /* Tester la droite */
    i = x + 1;
    ok = 0;
    while (case_valide(i, y) && plateau[i][y] == autre) {
        i++;
        ok = 1;
    }
    if (ok && case_valide(i, y) && plateau[i][y] == turn)
    	return true;

	/* Tester la gauche */
    i = x - 1;
    ok = 0;
    while (case_valide(i, y) && plateau[i][y] == autre) {
        i--;
        ok = 1;
    }
    if (ok && case_valide(i, y) && plateau[i][y] == turn)
    	return true;

    /* Tester le haut */
	j = y - 1;
    ok = 0;
    while (case_valide(i, x) && plateau[x][j] == autre) {
        j--;
        ok = 1;
    }
    if (ok && case_valide(x, j) && plateau[x][j] == turn) 
    	return true;


    /* Tester le bas */
    j = y + 1;
    ok = 0;
    while (case_valide(x, j) && plateau[x][j] == autre) {
        j++;
        ok = 1;
    }
    if (ok && case_valide(x, j) && plateau[x][j] == turn)
    	return true;

    /* Tester diagonale gauche vers le haut */
    i = y - 1;
    j = x - 1;
    ok = 0;
    while (case_valide(i, j) && plateau[j][i] == autre) {
        i--;
        j--;
        ok = 1;
    }
    if (ok && case_valide(i, j) && plateau[j][i] == turn)
    	return true;


    /* Tester diagonale droite vers le haut */
    i = y - 1;
    j = x + 1;
    ok = 0;
    while (case_valide(i, j) && plateau[j][i] == autre) {
        i--;
        j++;
        ok = 1;
    }
    if (ok && case_valide(i, j) && plateau[j][i] == turn)
    	return true;


    /* Tester diagonale gauche vers le bas */
    i = y + 1;
    j = x + 1;
    ok = 0;
    while (case_valide(i, j) && plateau[j][i] == autre) {
        i++;
        j++;
        ok = 1;
    }
    if (ok && case_valide(i, j) && plateau[j][i] == turn)
    	return true; 

    /* Diagonale droite vers le bas */
    i = y + 1;
    j = x - 1;
    ok = 0;
    while (case_valide(i, j) && plateau[j][i] == autre) {
        i++;
        j--;
        ok = 1;
    }
    if (ok && case_valide(i, j) && plateau[j][i] == turn)
    	return true;

	return false;
}



void jouer_coup(int x, int y)
{
    printf("Vous jouez : %c%d\n",65+x,y+1);

	plateau[x][y] = turn;

	int i=0,j=0;
	int autre = (turn == 1) ? 2 : 1;

	/* Jouer la droite */
    for (i=x+1; case_valide(i, y) && plateau[i][y] == autre; i++)
    	{} /* Mettre en place les compteurs */

    if (case_valide(i, y) && plateau[i][y] == turn) {
        for (i=x+1; plateau[i][y] == autre; i++)
            plateau[i][y] = turn;
    }

    /* Jouer la gauche */
    for (i=x-1;case_valide(i, y) && plateau[i][y] == autre; i--)
        {} /* Mettre en place les compteurs */
    
    if (case_valide(i, y) && plateau[i][y] == turn) {
        for (i=x-1; plateau[i][y] == autre; i--)
            plateau[i][y] = turn;
    }


    /* Jouer le haut */
    /* Tant que c'est la case adversaire en haut. */
    for (i=y-1;case_valide(i, x) && plateau[x][i] == autre;i--)
    	{} /* Mettre en place les compteurs */

    if (case_valide(i, x) && plateau[x][i] == turn) {
        i = y - 1;
        for (i=y-1;plateau[x][i] == autre; i--)
            plateau[x][i] = turn; /* Manger les cases */
    }

    /* Jouer le bas */
    for (i=y+1; case_valide(i, x) && plateau[x][i] == autre; i++)
	    {} /* Mettre en place les compteurs */

    if (case_valide(i, x) && plateau[x][i] == turn) {
        for (i=y+1;plateau[x][i] == autre;i++)
            plateau[x][i] = turn; /* Manger les cases */
    }


    /* Jouer diagonale gauche vers le haut */
    for (i=y-1, j=x-1; case_valide(i, j) && plateau[j][i] == autre; i--, j--)
        {} /* Mettre en place les compteurs */

    if (case_valide(i, j) && plateau[j][i] == turn) {
        for (i=y-1, j=x-1; plateau[j][i] == autre; i--, j--)
            plateau[j][i] = turn;
    }

    /* Jouer diagonale droite vers le haut */
    for (i=y-1, j=x+1; case_valide(i, j) && plateau[j][i] == autre; i--, j++)
	    {}
    
    if (case_valide(i, j) && plateau[j][i] == turn) {
        i = y - 1;
        j = x + 1;
        for (i=y-1, j=x+1; plateau[j][i] == autre; i--, j++)
            plateau[j][i] = turn;
    }


    /* Jouer diagonale gauche vers le bas */
    for (i=y+1, j=x+1; case_valide(i, j) && plateau[j][i] == autre; i++, j++)
    	{}
    if (case_valide(i, j) && plateau[i][j] == turn) {
        for (i=y+1, j=x+1;plateau[i][j] == autre; i++, j++)
            plateau[i][j] = turn;
    }


    /* Jouer diagonale droite vers le bas */
    for (i=x-1, j=y+1; case_valide(i, j) && plateau[i][j] == autre; i--, j++)
    	{}
    if (case_valide(i, j) && plateau[i][j] == turn) {
        for (i=x-1, j=y+1; plateau[i][j] == autre; i--, j++)
            plateau[i][j] = turn;
    }
}




int recuperer_valeur()
{
	if (turn == 1) {
		printf("[SYS] Au tour de \"%s\"(X). Que voulez-vous jouer ? ",joueur1);
		scanf("%s",jeu);
		if (strcmp(jeu,"tab") == 0)
			afficher_plateau();
		else
			printf("[SYS] Vous avez joué %s\n\n",jeu);
	} else if (turn == 2) {

		if (contre_ia)
		{
			int i, j;
			for (i = 0; i < N; i++) {
				for (j = 0; j < N; j++) {
					if (test_adjacence(i,j) && test_coup(i,j)) {
						jeu[0] = i+65;
						jeu[1] = j+49;
					}
				}
			}
			/*
			if (i == 8 && j == 8)
				return -1;
			*/
			printf("[SYS] PC a joué : %s\n", jeu);
		} else {
			printf("[SYS] Au tour de \"%s\"(O). Que voulez-vous jouer ? ",joueur2);
			scanf("%s",jeu);

			if (strcmp(jeu,"tab") == 0)
				afficher_plateau();
			else
				printf("[SYS] Vous avez joué %s\n\n",jeu);
		}
	} else {
		fprintf(stderr, "[ERR] Erreur selection joueur\n");
		return -1;
	}

	return 1;
}





int main ()
{


    char choix;

    printf("Voulez-vous jouer contre l'ordinateur ? (O/n)\n");

    scanf("%c",&choix);

    if (choix == 'O' || choix == 'o')
    	contre_ia = 1;


	printf("[SYS] Entrez le nom du joueur1 (X) : ");
	scanf("%s",joueur1);

	if (contre_ia) {
		strcpy(joueur2,"PC");

	} else { 
		printf("[SYS] Entrez le nom du joueur2 (O) : ");
		scanf("%s",joueur2);
	}
	printf("[SYS] Joueur1(X): \"%s\", Joueur2(O): \"%s\"\n",joueur1, joueur2);

	initialiser();
	afficher_plateau();

	int finished=0;
	while(!finished)
	{
		int val = recuperer_valeur();


		if (val < 0)
			finished=1;


		/* Dans la table ASCII: • les minuscules sont entre 97 et 122
		 						• Les majuscules entre 65 et 90;
		*/
		int x,y;
		y = (jeu[1] - '0') -1;
		

		if (jeu[0] >= 65 && jeu[0] < 73) /* 73 pour s'arrêter à H */
			x = jeu[0] - 65;
		else if (jeu[0] >= 97 && jeu[0] < 105) /* 105 pour s'arrêter à h */
			x = jeu[0] - 97;
		else {
			fprintf(stderr, "[ERR] Vous avez entré une valeur erronnée.\n");
			continue;
		}


		if (strcmp(jeu,"tab") == 0)
			continue;

		if ((x < 0 || x > 8 || y < 0 || y > 8))
		{
			fprintf(stderr, "[ERR] Vous avez entré une valeur erronnée.\n");
			continue;
		}
		if (plateau[x][y] != 0) {
			fprintf(stderr, "[ERR] La case est déjà remplie :( Réessayez\n");
			continue;
		}
		
		if (!test_adjacence(x,y) || !test_coup(x,y)) {
			fprintf(stderr, "[ERR] Ce coup est impossible. Réessayez\n");
			continue;
		}


		jouer_coup(x,y);

		turn = (turn == 1) ? 2 : 1;

		afficher_plateau();

	}

	printf("Terminé ! %s a eu %d, %s a eu %d\n",joueur1, score_j1, joueur2, score_j2);


	return 0;
}





