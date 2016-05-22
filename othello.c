/**
  * @date 22/05/2016
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 8

char joueur1[50];
char joueur2[50];
short turn=1;
char jeu[2];
short score_j1, score_j2;


// X == Noir
// O == Blanc
short	plateau [N][N];


/**
  * @brief Fonction pour afficher le plateau
  */
void afficher_plateau()
{
	int	x, y;
	score_j1 = 0; score_j2 = 0;
	printf("   A B C D E F G H \n");
	for (y = 0; y < N; y++) {
		printf("%d |",y+1);
		for (x = 0; x < N; x++) {
			if (plateau[x][y] == 0)	printf(" |");
			else if (plateau[x][y] == 1) { printf("X|"); score_j1++;}
			else if (plateau[x][y] == 2) { printf("O|"); score_j2++; }
		}
		printf("%d\n",y+1);
	}
	printf("   A B C D E F G H \n\n");

	printf("======== SCORE : \"%s\": %d, \"%s\": %d ========\n\n",joueur1, score_j1, joueur2, score_j2);

}

/**
  * @brief Fonction qui initialise le plateau selon les règles d'othello
  */
void initialiser()
{
	plateau[4][3] = 1;
	plateau[3][4] = 1;

	plateau[3][3] = 2;
	plateau[4][4] = 2;

}

/**
  * @brief Fonction qui récupère uniquement le jeu du joueur courant.
  */
short recuperer_valeur()
{
	if (turn == 1) {
		printf("[SYS] Au tour du joueur1 \"%s\". Que voulez-vous jouer ? ",joueur1);
		scanf("%s",jeu);
		printf("[SYS] Vous avez joué %s\n\n",jeu);
	} else if (turn == 2) {
		printf("[SYS] Au tour du joueur2 \"%s\". Que voulez-vous jouer ? ",joueur2);
		scanf("%s",jeu);
		printf("[SYS] Vous avez joué %s\n\n",jeu);
	} else {
		fprintf(stderr, "[ERR] Erreur selection joueur\n");
		return -1;
	}

	return 1;
}


/**
  * @brief Fonction qui teste si la case à jouer est correcte
  * @return true  si le coup est possible
  *			false sinon
  */
bool test_adjacence (short x, short y)
{

	// Dernière case en bas à droite
	if (
		(x == 7 && y == 7)
		&& (!plateau[x-1][y] && !plateau[x-1][y-1] && !plateau[x][y-1])
		)
		return false;

	// Dernière case en haut à droite
	if (
		(x == 7 && y == 0)
		&& (!plateau[x-1][y] && !plateau[x][y+1] && !plateau[x-1][y-1])
		)
		return false;

	// Première case en haut à gauche
	if (
		(x == 0 && y == 0)
		&& (!plateau[x+1][y] && !plateau[x+1][y-1] && !plateau[x][y+1])
		)
		return false;

	// Première case en bas à gauche
	if (
		(x == 0 && y == 7)
		&& (!plateau[x][y-1] && !plateau[x+1][y-1] && !plateau[x+1][y])
		)
		return false;

	// Cas normal
	if (!plateau[x+1][y] && !plateau[x+1][y+1] && !plateau[x][y+1] && !plateau[x-1][y+1] && !plateau[x-1][y] && !plateau[x-1][y-1] && !plateau[x][y-1] && !plateau[x+1][y-1])
		return false;


	return true;
}




int main ()
{

	printf("[SYS] Entrez le nom du joueur1 (X) : ");
	scanf("%s",joueur1);

	printf("[SYS] Entrez le nom du joueur2 (O) : ");
	scanf("%s",joueur2);


	printf("[SYS] Joueur1: \"%s\", Joueur2: \"%s\"\n",joueur1, joueur2);

	initialiser();
	afficher_plateau();

	short finished=0;
	while(!finished)
	{
		short val = recuperer_valeur();

		if (val < 0)
			finished=1;


		// Dans la table ASCII: • les minuscules sont entre 97 et 122
		// 						• Les majuscules entre 65 et 90;
		short x,y;
		y = (jeu[1] - '0') -1;
		

		if (jeu[0] >= 65 && jeu[0] < 73) // 73 pour s'arrêter à H
			x = jeu[0] - 65;
		else if (jeu[0] >= 97 && jeu[0] < 105) // 105 pour s'arrêter à h
			x = jeu[0] - 97;
		else {
			fprintf(stderr, "[ERR] Vous avez entré une valeur erronnée.\n");
			continue;
		}

		if (x < 0 || x > 8 || y < 0 || y > 8)
		{
			fprintf(stderr, "[ERR] Vous avez entré une valeur erronnée.\n");
			continue;
		} else if (plateau[x][y] != 0) {
			fprintf(stderr, "[ERR] La case est déjà remplie :( Réessayez\n");
			continue;
		}
		if (!test_adjacence(x,y)) {
			fprintf(stderr, "[ERR] Ce coup est impossible. Réessayez\n");
			continue;
		}


		turn = (turn == 1) ? 2 : 1;

		afficher_plateau();

	}


	return 0;
}





