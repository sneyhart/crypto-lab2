#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "gmp.h"

int main(int argc, char **argv)
{
    char inputStr[2048];
    FILE *key ,*in, *out;
    mpz_t n, e, c, m;
    int i;

    assert(argc == 7);
    for(i = 1; i < argc; i++){
	if(strcmp(argv[i], "-k") == 0) key  = fopen(argv[i+1], "r");
	if(strcmp(argv[i], "-i") == 0) in   = fopen(argv[i+1], "r");
	if(strcmp(argv[i], "-o") == 0) out  = fopen(argv[i+1], "w");
    }

    mpz_init(n); mpz_init(e); mpz_init(c); mpz_init(m); 
    mpz_set_ui(n,0); mpz_set_ui(e,0); mpz_set_ui(c,0); mpz_set_ui(m,0);    

    fscanf(key, "%2047s", inputStr);
    fscanf(key, "%2047s", inputStr);
    mpz_set_str(n,inputStr, 10);

    fscanf(key, "%2047s", inputStr);
    mpz_set_str(e,inputStr, 10);

    fscanf(in, "%2047s", inputStr);
    mpz_set_str(m,inputStr, 10);

    mpz_powm_sec(c, m, e, n); 
    printf ("c = ");
    mpz_out_str(stdout,10,c);
    printf ("\n");
    mpz_out_str(out,10,c);
    fprintf (out,"\n");
    mpz_clears(n,e,c,m,NULL);
    return 0;
}
