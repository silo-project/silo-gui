#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int seed, max, i;
	
	printf("Input Seed : ");
	scanf("%d", &seed);
	printf("Input Max  : ");
	scanf("%d", &max);
	srand(seed);

	for (i = 0; i < max; i++) {
		if (rand()%2)
			printf("1");
		else
			printf("0");
	}
	putchar('\n');
	return 0;
}
