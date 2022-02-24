#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

int talvez_primo(const mpz_t a, const mpz_t n, const mpz_t n1, unsigned int t, const mpz_t q) {
    mpz_t r, aux;
    mpz_inits(r, aux, NULL);

    mpz_powm(r, a, q,n);
    mpz_mod(aux, a, n);

    if(mpz_cmp_ui(aux, 0) == 0) {
        return 1;
    }
    
    mpz_mod(aux, r, n);
    
    if(mpz_cmp_ui(aux, 0) == 0) {
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

int main() {
    mpz_t a, n, n1, q;
    unsigned int t;

    mpz_inits(a, n, n1, q, NULL);
    
    mpz_set_si(a, 2);
    mpz_set_si(n, 561);
    mpz_sub_ui(n1, n, 1);
    mpz_set_si(q, 35);
    t = 4;

    int k = talvez_primo(a, n, n1, t, q);
    
    printf("%d\n", k);
    
    return 0;
}