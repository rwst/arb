/*
    Copyright (C) 2016 Pascal Molin

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "acb_dirichlet.h"

void
acb_dirichlet_pairing_conrey(acb_t res, const dirichlet_group_t G, const dirichlet_conrey_t a, const dirichlet_conrey_t b, slong prec)
{
    ulong expo;
    expo = dirichlet_ui_pairing_conrey(G, a, b);
    if (expo == DIRICHLET_CHI_NULL)
        acb_zero(res);
    else
    {
        fmpq_t t;
        fmpq_init(t);
        fmpq_set_si(t, 2 * expo, G->expo);
        arb_sin_cos_pi_fmpq(acb_imagref(res), acb_realref(res), t, prec);
        fmpq_clear(t);
    }
}
