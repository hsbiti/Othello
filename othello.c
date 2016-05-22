#include <stdio.h>
#define N 8

int		plateau    [N][N];

void afficher_plateau()
{
	int	x, y;
	printf("  A B C D E F G H \n");
	for (y = 0; y < N; y++) {
		printf("%d ",y+1);
		for (x = 0; x < N; x++) {
			if (plateau[x][y] == 0)	printf("  ");
			else if (plateau[x][y] == 1) printf("X ");
			else if (plateau[x][y] == 2) printf("O ");
		}
		printf("%d\n",y+1);
	}
	printf("  A B C D E F G H \n");

}


int main ()
{
	afficher_plateau();
	return 0;
}