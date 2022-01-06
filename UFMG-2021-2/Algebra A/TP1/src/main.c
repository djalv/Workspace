#include <stdio.h>
#include <gmp.h>

void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b) {
    mpz_t r, q, s, temp, temp2, temp3, x1, y1;
    mpz_inits(r, q, s, temp, temp2, x1, y1, NULL);
    
    if(mpz_cmp_ui(b, 0) == 0) {
        mpz_set(g, a);
        mpz_set_si(x, 1);
        mpz_set_si(y, 0);
    }
    else{  
        mpz_mod(r, a, b); // a % b
        mpz_sub(s, a, r); // a - r
        mpz_fdiv_q(q, s, b); // (a - r)/b
        
        mdc_estendido(g, x, y, b, r);

        mpz_set(y1, y); // y' = y
        mpz_set(x1, x); // x' = x

        mpz_mul(temp, q, y); // q * y
        mpz_sub(temp2, x, temp); // x - (q * y)
        mpz_set(y, temp2); // y = x - (q * y)

        mpz_set(x, y1); // x = y'

    }
}


int main() {
    mpz_t g, x, y, a, b, x1, y1, g1;
    mpz_inits(g, x, y, a, b, x1, y1, g1, NULL);
    
    mpz_set_si(a, 53);
    mpz_set_si(b, 31);
    
    mdc_estendido(g, x, y, a, b);
    
    gmp_printf("(%Zd, %Zd, %Zd)\n", g, x, y);
    mpz_gcdext(g1, x1, y1, a, b);
    gmp_printf("(%Zd, %Zd, %Zd)\n", g1, x1, y1);
}