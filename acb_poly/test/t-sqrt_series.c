/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2012, 2013 Fredrik Johansson

******************************************************************************/

#include "acb_poly.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("sqrt_series....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 5000; iter++)
    {
        slong m, n, qbits, rbits1, rbits2;
        fmpq_poly_t A;
        acb_poly_t a, b, c;

        qbits = 2 + n_randint(state, 200);
        rbits1 = 2 + n_randint(state, 200);
        rbits2 = 2 + n_randint(state, 200);

        m = 1 + n_randint(state, 30);
        n = 1 + n_randint(state, 30);

        fmpq_poly_init(A);
        acb_poly_init(a);
        acb_poly_init(b);
        acb_poly_init(c);

        fmpq_poly_randtest_not_zero(A, state, m, qbits);
        acb_poly_set_fmpq_poly(a, A, rbits1);

        acb_poly_sqrt_series(b, a, n, rbits2);

        /* Check sqrt(a)^2 = a */
        acb_poly_mullow(c, b, b, n, rbits2);

        fmpq_poly_truncate(A, n);
        if (!acb_poly_contains_fmpq_poly(c, A))
        {
            flint_printf("FAIL\n\n");
            flint_printf("bits2 = %wd\n", rbits2);

            flint_printf("A = "); fmpq_poly_print(A); flint_printf("\n\n");
            flint_printf("a = "); acb_poly_printd(a, 15); flint_printf("\n\n");
            flint_printf("b = "); acb_poly_printd(b, 15); flint_printf("\n\n");
            flint_printf("c = "); acb_poly_printd(c, 15); flint_printf("\n\n");

            abort();
        }

        acb_poly_sqrt_series(a, a, n, rbits2);
        if (!acb_poly_equal(a, b))
        {
            flint_printf("FAIL (aliasing)\n\n");
            abort();
        }

        fmpq_poly_clear(A);
        acb_poly_clear(a);
        acb_poly_clear(b);
        acb_poly_clear(c);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}

