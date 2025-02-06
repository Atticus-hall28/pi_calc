#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <math.h>
#define EXIT_SUCCESS 0 

int main(int argc, char *argv[])
{
    FILE *file;
    int bits = 32768;
    int iterations = 4096;
    if (argc == 3) {
        bits = atoi(argv[1]);
        iterations = atoi(argv[2]);
    }

    // Use strings for initialization to avoid precision loss
    const char *init_a = "1.0";
    const char *init_b = "0.707106781186547524400844362104849039284835937688474036588339868995366239231";
    const char *init_t = "0.25";
    const char *init_p = "1.0";

    mpf_set_default_prec(bits);
    mpf_t a, b, t, p, a_next, result, temp, pi;
    mpf_init(a);
    mpf_init(b);
    mpf_init(t);
    mpf_init(p);
    mpf_init(a_next);
    mpf_init(result);
    mpf_init(temp);
    mpf_init(pi);

    mpf_set_str(temp,"2.0",10);
    mpf_set_str(a, init_a, 10);
    mpf_set_str(t, init_t, 10);
    mpf_set_str(p, init_p, 10);
    mpf_sqrt(result,temp);
    mpf_set_str(temp,"1.0",10);

    mpf_div(b,temp,result);
    for (int i = 0; i < iterations; i++) {
        // a_next = (a + b) / 2
        mpf_add(result, a, b);
        mpf_div_ui(a_next, result, 2);

        // b = sqrt(a * b)
        mpf_mul(result, a, b);
        mpf_sqrt(b, result);

        // t -= p * (a - a_next)^2
        mpf_sub(result, a, a_next);
        mpf_mul(temp, result, result);
        mpf_mul(temp, p, temp);
        mpf_sub(t, t, temp);

        // a = a_next
        mpf_set(a, a_next);

        // p *= 2
        mpf_mul_ui(p, p, 2);
    }

    // pi = (a + b)^2 / (4 * t)
    mpf_add(result, a, b);
    mpf_mul(result, result, result);
    mpf_mul_ui(temp, t, 4);
    mpf_div(pi, result, temp);

        file = fopen("output.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file!\n");
        return 1;
    }
    
    gmp_fprintf(file,"%Ff",pi);
    
    fclose(file);

    // Clear memory
    mpf_clear(a);
    mpf_clear(b);
    mpf_clear(t);
    mpf_clear(p);
    mpf_clear(a_next);
    mpf_clear(result);
    mpf_clear(temp);
    mpf_clear(pi);

    return EXIT_SUCCESS;
}
