#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

unsigned long int flog2(unsigned long int x) {
    unsigned long int r = 0 ;
  
    while( x>>=1 ) { 
        r++;
    }

    return r ;
}
 

int talvez_primo(const mpz_t a, const mpz_t n, const mpz_t n1, unsigned int t, const mpz_t q) {
    mpz_t r, aux;
    mpz_inits(r, aux, NULL);

    mpz_powm(r, a, q,n);
    mpz_mod(aux, a, n);

    if(mpz_cmp_ui(aux, 0) == 0) {
        return 1;
    }
    
    mpz_mod(aux, r, n);
    
    if(mpz_cmp_ui(aux, 1) == 0) {
        return 1;
    }

    for(int i = 0; i < t; i++) {
        mpz_mod(aux, r, n);

        
        if(mpz_cmp(aux, n1) == 0) {
            
            return 1;
        }
        mpz_pow_ui(r, r, 2);
        mpz_mod(r, r, n);
    }
    return 0;
}

int provavelmente_primo(const mpz_t n, unsigned int k, gmp_randstate_t rnd) {
    mpz_t a, n1, q, paridade, aux;
    unsigned long int t;
    mpz_inits(a, n1, q, paridade, NULL);

    mpz_sub_ui(n1, n, 1);
    mpz_set(q, n1);
    mpz_mod_ui(paridade, q, 2);
    
    while(mpz_cmp_ui(paridade, 0) == 0) {
        mpz_fdiv_q_ui(q, q, 2);
        mpz_mod_ui(paridade, q, 2);
    }
    mpz_fdiv_q(aux, n1, q);
    t = flog2(mpz_get_ui(aux));
    mp_bitcnt_t num_bits = mpz_sizeinbase(n1, 2);
    
    for(int i = 0; i < k; i++) {
        do{
            mpz_urandomb(a, rnd, num_bits);
        } while(mpz_cmp_ui(a, 1) < 0 || mpz_cmp(a, n1) > 0);
        
        if(talvez_primo(a, n, n1, t, q) == 0) {
            return 0;
        }
    }
    return 1;
}

void primo_aleatorio(mpz_t r, unsigned int b, gmp_randstate_t rnd) {
    mpz_t min;
    mpz_inits(min, NULL);

    mpz_ui_pow_ui(min, 2, b-1);
    
    do{
        mpz_urandomb(r, rnd, b);
    } while(mpz_cmp(r, min) < 0 || provavelmente_primo(r, 20, rnd) == 0);
    
}

int main() {
    mpz_t a, n, n1, q, r, paridade, k, aux;
    gmp_randstate_t rnd;
    
    unsigned long long int t, j, num;
    FILE *file;
    
    if((file = fopen("/home/djalv009/Workspace/UFMG-2021-2/Algebra A/TP2/primes.txt", "r")) == NULL) {
        printf("Error! opening file");
        exit(1);
    }
    

    mpz_inits(a, n, n1, q, r, paridade, k, aux, NULL);
    gmp_randinit_default(rnd);
    gmp_randseed_ui(rnd, time(NULL));

    //for(int i = 0; i < 78499; i++) {
        //fscanf(file,"%d", &num);
        gmp_fscanf(file, "%Zd", n);
        mpz_set_si(a, 2);
        //mpz_set_si(n, num);
        mpz_sub_ui(n1, n, 1);
    
        mpz_set(q, n1);
        mpz_mod_ui(paridade, q, 2);
        while(mpz_cmp_ui(paridade, 0) == 0) {
            mpz_fdiv_q_ui(q, q, 2);
            mpz_mod_ui(paridade, q, 2);
        }
        mpz_fdiv_q(aux, n1, q);
        t = flog2(mpz_get_ui(aux));

        if(provavelmente_primo(n, 40, rnd) == 0) {
            gmp_printf("%Zd, %d\n", n, t);
        }
    //}

    fclose(file);
    return 0;
}