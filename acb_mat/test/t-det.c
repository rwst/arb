/*
    Copyright (C) 2012 Fredrik Johansson

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb_mat.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("det....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 10000 * arb_test_multiplier(); iter++)
    {
        fmpq_mat_t Q;
        fmpq_t Qdet;
        acb_mat_t A;
        acb_t Adet, imagunit;
        slong n, qbits, prec;
        int imaginary;

        n = n_randint(state, 8);
        qbits = 1 + n_randint(state, 100);
        prec = 2 + n_randint(state, 200);
        imaginary = n_randint(state, 2);

        fmpq_mat_init(Q, n, n);
        fmpq_init(Qdet);

        acb_mat_init(A, n, n);
        acb_init(Adet);
        acb_init(imagunit);

        fmpq_mat_randtest(Q, state, qbits);
        fmpq_mat_det(Qdet, Q);

        acb_mat_set_fmpq_mat(A, Q, prec);

        if (imaginary)
        {
            acb_onei(imagunit);
            acb_mat_scalar_mul_acb(A, A, imagunit, prec);
        }

        acb_mat_det(Adet, A, prec);

        if (imaginary)
        {
            acb_onei(imagunit);
            acb_inv(imagunit, imagunit, prec);
            acb_pow_ui(imagunit, imagunit, n, prec);
            acb_mul(Adet, Adet, imagunit, prec);
        }

        if (!acb_contains_fmpq(Adet, Qdet))
        {
            flint_printf("FAIL (containment, iter = %wd)\n", iter);
            flint_printf("n = %wd, prec = %wd\n", n, prec);
            flint_printf("\n");

            flint_printf("Q = \n"); fmpq_mat_print(Q); flint_printf("\n\n");
            flint_printf("Qdet = \n"); fmpq_print(Qdet); flint_printf("\n\n");

            flint_printf("A = \n"); acb_mat_printd(A, 15); flint_printf("\n\n");
            flint_printf("Adet = \n"); acb_printd(Adet, 15); flint_printf("\n\n");
            flint_printf("Adet = \n"); acb_print(Adet); flint_printf("\n\n");

            flint_abort();
        }

        fmpq_mat_clear(Q);
        fmpq_clear(Qdet);
        acb_mat_clear(A);
        acb_clear(Adet);
        acb_clear(imagunit);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}
