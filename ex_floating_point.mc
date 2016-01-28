/* $Id: ex16.mc,v 2.1 2005/06/14 22:16:51 jls Exp $ */

/*
 * Copyright 2005 SRC Computers, Inc.  All Rights Reserved.
 *
 *	Manufactured in the United States of America.
 *
 * SRC Computers, Inc.
 * 4240 N Nevada Avenue
 * Colorado Springs, CO 80907
 * (v) (719) 262-0213
 * (f) (719) 262-0223
 *
 * No permission has been granted to distribute this software
 * without the express permission of SRC Computers, Inc.
 *
 * This program is distributed WITHOUT ANY WARRANTY OF ANY KIND.
 */

#include <libmap.h>

void subr (double d_arr[], double *res, int m, int64_t *tm, int mapnum) {
    OBM_BANK_A (AL, double, MAX_OBM_SIZE)
    int64_t t0, t1;
    int i;

    Stream_64 SA;

    read_timer (&t0);

    *res = 0.0;

#pragma src parallel sections
{
#pragma src section
{
    streamed_dma_cpu_64 (&SA, PORT_TO_STREAM, d_arr, m*sizeof(int64_t));
}
#pragma src section
{
    int i,err;
    double v64;


    for (i=0;i<m;i++)  {
       get_stream_dbl_64 (&SA, &v64);
       fp_accum_64 (v64, i==(m-1), 1, i==0, res, &err);
    }
}
}

    read_timer (&t1);
    *tm = t1 - t0;
    }
