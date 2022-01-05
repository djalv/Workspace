#include <stdio.h>
#include <gmp.h>

int main() {
    mpz_t m, n;
    mpz_inits(m, n, NULL);

    gmp_scanf("%Zd %Zd", m, n);

    mpz_t resp;
    mpz_init(resp);
    mpz_mul(resp, m, n);

    gmp_printf("%Zd\n", resp);

    mpz_clears(m, n, resp, NULL);
}