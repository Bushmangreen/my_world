
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *joinstr (const char **s, const char *sep)
{
    char *joined = NULL;                /* pointer to joined string w/sep */
    size_t lensep = strlen (sep),       /* length of separator */
        sz = 0;                         /* current stored size */
    int first = 1;                      /* flag whether first term */

    while (*s) {                        /* for each string in s */
        size_t len = strlen (*s);
        /* allocate/reallocate joined */
        void *tmp = realloc (joined, sz + len + (first ? 0 : lensep) + 1);
        if (!tmp) {                     /* validate allocation */
            perror ("realloc-tmp");     /* handle error (adjust as req'd) */
            exit (EXIT_FAILURE);
        }
        joined = tmp;                   /* assign allocated block to joined */
        if (!first) {                   /* if not first string */
            strcpy (joined + sz, sep);  /* copy separator */
            sz += lensep;               /* update stored size */
        }
        strcpy (joined + sz, *s++);     /* copy string to joined */
        first = 0;                      /* unset first flag */
        sz += len;                      /* update stored size */
    }

    return joined;      /* return joined string */
}

   
int main (void) {

    const char *strings[] = {"Abc", "Bba","bebe",NULL},
        *sep = "XXX";
    char *joined = joinstr (strings, sep);  /* join strings */

    printf ("%s\n", joined);    /* output joined string */
    free (joined);              /* free memory */
}