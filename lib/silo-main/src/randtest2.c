#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int seed, core;
	long long max, i, j, k;
    char * p, * q;
	
	printf("Input Seed : ");
    scanf("%d", &seed);
    printf("Input Core : ");
	scanf("%lld", &core);
	printf("Input Max  : ");
	scanf("%lld", &max);
	srand(seed);
    
    p = malloc(max);
    q = malloc(max);
    if (p == NULL || q == NULL)
        return -1;
    
	for (i = 0; i < max; i++) {
		if (rand()%2)
			p[i] = 1;
		else
			p[i] = 0;
	}
	
    for (i = 0; i < max; i++)
        printf("%d", p[i]);
    putchar('\n');
	
	for (i = 0; i < max; i++)
        q[i] = 0;
	
	for (k = 0; k < core; k++) {
        for (i = j = k; i < max; i += core) {
            if (p[i]) {
                p[i] = 0;
                q[j] = 1;
                j += core;
            }
        }
    }
    
    for (i = 0; i < max; i++)
        printf("%d", q[i]);
    putchar('\n');
    
	return 0;
}
