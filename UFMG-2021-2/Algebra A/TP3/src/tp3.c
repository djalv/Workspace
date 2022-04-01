#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <gmp.h>

void codifica(mpz_t r, const char *str) {
    mpz_t b, p, mul;
    int s;
    mpz_inits(b, p, mul, NULL);

    mpz_set_ui(b, 256);
    int n = strlen(str);
    
    s = str[0];
    mpz_set_ui(r, s);

    for(int i = 1; i < n; i++) {
        s = str[i];
        mpz_pow_ui(p, b, i);
        mpz_mul_ui(mul, p, s);
        mpz_add(r, r, mul);
    }
}

char *decodifica(const mpz_t n) {
    mpz_t r, q, n0;
    char c;
    char *str;

    str = (char *) malloc(500 * sizeof(char*));
    mpz_inits(r, q, n0, NULL);

    mpz_set(n0, n);
    int b = 256;

    while(mpz_cmp_ui(n0, 0) > 0) {
        mpz_mod_ui(r, n0, b);
        mpz_fdiv_q_ui(q, n0, b);
        mpz_set(n0, q);
        c = (char) mpz_get_ui(r);
        strncat(str, &c, 1);
    }
    return str;
}

void criptografia(mpz_t C, const mpz_t M, const mpz_t n, const mpz_t e) {
    mpz_powm(C, M, e, n);
}

void descriptografia(mpz_t M, const mpz_t C, const mpz_t n, const mpz_t d) {
    mpz_powm(M, C, d, n);
}

int main() {
    mpz_t r, n, C, e, M, d;
    char *s;
    mpz_inits(r, n, C, e, M, d, NULL);
    
    mpz_set_ui(n, 221);
    mpz_set_ui(e, 5);
    mpz_set_ui(d, 77);
    
    codifica(r, "a");
    criptografia(C, r, n, e);
    descriptografia(M, C, n, d);
    
    gmp_printf("%Zd, %Zd", C, M);
    return 0;
}