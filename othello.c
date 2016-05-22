/**
  * @date 22/05/2016
  */

#include <stdio.h>
#include <stdlib.h>
#define N 8

char joueur1[50];
char joueur2[50];
short turn=1;
char jeu[2];


// X == Noir
// O == Blanc
short	plateau [N][N];


/**
  * @brief Fonction pour afficher le plateau
  */
void afficher_plateau()
{
	int	x, y;
	printf("   A B C D E F G H \n");
	for (y = 0; y < N; y++) {
		printf("%d |",y+1);
		for (x = 0; x < N; x++) {
			if (plateau[x][y] == 0)	printf(" |");
			else if (plateau[x][y] == 1) printf("X|");
			else if (plateau[x][y] == 2) printf("O|");
		}
		printf("%d\n",y+1);
	}
	printf("   A B C D E F G H \n");

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
		fprintf(stderr, "[SYS] Erreur selection joueur\n");
		return -1;
	}

	return 1;
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

	int finished=0;
	while(!finished)
	{
		short val = recuperer_valeur();

		if (val < 0)
			finished=1;


		// Dans la table ASCII: • les minuscules sont entre 97 et 122
		// 						• Les majuscules entre 65 et 90;
		int x,y;
		y = jeu[1] - '0';
		

		if (jeu[0] >= 65 && jeu[0] <= 90)
			x = jeu[0] - 65;
		else if (jeu[0] >= 97 && jeu[0] <= 122)
			x = jeu[0] - 97;

		printf("x=%d, y=%d\n",x,y);


		if (x < 0 || x > 8 || y < 0 || y > 8)
		{
			fprintf(stderr, "Vous avez entré une valeur erronnée.\n");
			continue;
		}
		turn = (turn == 1) ? 2 : 1;


		afficher_plateau();


	}


	return 0;
}





