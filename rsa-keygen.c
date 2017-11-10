#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gmp.h"

int main(int argc, char **argv)
{
    char inputStr[2048];
    FILE *pub ,*sec;
    mpz_t n, d, c, m;
    int i, bits;
    
    assert(argc == 7);
    for(i = 1; i < argc; i++){
	if(strcmp(argv[i], "-p") == 0)	pub	= fopen(argv[i+1], "w");
	if(strcmp(argv[i], "-s") == 0)	sec	= fopen(argv[i+1], "w");
	if(strcmp(argv[i], "-n") == 0)	bits	= atoi(argv[i+1]);
    }
    
    mpz_inits(n,d,c,m,NULL);   
    /*fscanf(key, "%2047s", inputStr);
    fscanf(key, "%2047s", inputStr);
    mpz_set_str(n,inputStr, 10);
    
    fscanf(key, "%2047s", inputStr);
    mpz_set_str(d,inputStr, 10);
    
    fscanf(in, "%2047s", inputStr);
    mpz_set_str(c,inputStr, 10);
    
    mpz_powm_sec(m, c, d, n); 
    printf ("m = ");
    mpz_out_str(stdout,10,m);
    printf ("\n");
    mpz_out_str(out,10,m);
    fprintf (out,"\n");*/
    mpz_clears(n,d,c,m,NULL);
    return 0;
}
