#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gmp.h"
#define print_num(num) {mpz_out_str(stdout,10,num); printf("\n");}
#define fprint_num(file, num) {mpz_out_str(file,10,num); fprintf(file, "\n");}

int main(int argc, char **argv)
{
    char inputStr[8];
    FILE *pub ,*sec, *seed;
    mpz_t p, q, t, n, e, d;
    gmp_randstate_t state;
    mp_bitcnt_t bits;
    int i;
    
    assert(argc == 7);
    for(i = 1; i < argc; i++){
	if(strcmp(argv[i], "-p") == 0)	pub	= fopen(argv[i+1], "w");
	if(strcmp(argv[i], "-s") == 0)	sec	= fopen(argv[i+1], "w");
	if(strcmp(argv[i], "-n") == 0)	bits	= (mp_bitcnt_t)atoi(argv[i+1]);
    }
    
    //initialize necessary variables
    mpz_inits(p,q,t,n,e,d,NULL);
    gmp_randinit_default(state);
    seed = fopen("/dev/urandom", "r");
    fread(inputStr, 8, 1, seed);
    gmp_randseed_ui(state, *((unsigned int*)inputStr));

    //get p, q, and n
    do{
	mpz_urandomb(q, state, bits/2);
	mpz_nextprime(p,q);
	mpz_ui_pow_ui(e, 2, bits-1);
	mpz_ui_pow_ui(d, 2, bits);
	mpz_cdiv_q(t, e, p);	//keep t
	mpz_fdiv_q(n, d, p);
	mpz_sub(e, n, t);
	mpz_urandomm(d, state, e);
	mpz_add(e, d, t);
	mpz_nextprime(q, e);
	mpz_mul(n, p, q);
	printf("p = ");	print_num(p);
	printf("q = ");	print_num(q); 
	printf("n = ");	print_num(n); 
	printf("n is %zu bits.\n\n", mpz_sizeinbase(n,2));
    }while(mpz_sizeinbase(n,2) != bits || mpz_probab_prime_p(p, 15) < 1 || mpz_probab_prime_p(q,15) < 1);
   
    //get totient of p and q
    mpz_sub_ui(e, p, 1);
    mpz_sub_ui(d, q, 1);
    mpz_lcm(t, e, d); 
    printf("t = "); print_num(t);

    //pick e
    mpz_set_str(e, "65537", 10);
    printf("e = "); print_num(e);

    //solve for d
    mpz_invert(d, e, t);
    printf("d = "); print_num(d);

    //output to files
    fprintf(pub, "%lu\n", bits);
    fprint_num(pub, n);
    fprint_num(pub, e);
    fprintf(sec, "%lu\n", bits);
    fprint_num(sec, n);
    fprint_num(sec, d);

    //clean up
    fclose(seed); fclose(pub); fclose(sec);
    gmp_randclear(state);
    mpz_clears(p,q,t,n,e,d,NULL);
    return 0;
}
