static char const cvsid[] = "$Id: main.c,v 2.1 2005/06/14 22:16:51 jls Exp $";

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
#include <stdlib.h>


void subr (double d_arr[], double *res, int m, int64_t *tm, int mapnum);


int main (int argc, char *argv[]) {
    FILE *res_map, *res_cpu;
    int i, num;
    double *D_src, res, acc;
    int64_t tm;
    int mapnum = 0;

    if ((res_map = fopen ("res_map", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_map'\n");
        exit (1);
        }

    if ((res_cpu = fopen ("res_cpu", "w")) == NULL) {
        fprintf (stderr, "failed to open file 'res_cpu'\n");
        exit (1);
        }

    if (argc < 2) {
	fprintf (stderr, "need number of elements as arg\n");
	exit (1);
	}

    if (sscanf (argv[1], "%d", &num) < 1) {
	fprintf (stderr, "need number of elements as arg\n");
	exit (1);
	}

    if ((num < 1) || (num > MAX_OBM_SIZE)) {
        fprintf (stderr, "number of elements must be in the range 1 through %d\n", MAX_OBM_SIZE);
	exit (1);
	}

    D_src = (double*) malloc (num * sizeof (double));

    srandom (99);

    acc = 0.0;

    for (i=0; i<num; i++) {
        D_src[i] = (double)random() / random();
	acc += D_src[i];
	}

    fprintf (res_cpu, "%lf\n", acc);

    map_allocate (1);

    subr (D_src, &res, num, &tm, mapnum);

    printf ("%lld clocks\n", tm);

    fprintf (res_map, "%lf\n", res);

    map_free (1);

    exit(0);
    }

