#define INCL_BASE
#define INCL_DOS
#include <os2.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned pascal far testproc(int far*, char far*, int far*, int far*);

unsigned pascal far testproc(int far *func, char far *datastr, 
                             int far *dlen, int far *retc)
{
    int  cchString=0;
    char szParams[81];

    /* generate a string based on the variables passed */
    sprintf(szParams, "p1 = %d, p2 = %.40s, p3 = %d, p4 = %d", 
                      *func, datastr, *dlen, *retc);

    /* get the string length */
    cchString = strlen(szParams);

    /* display the generated string */
    printf("MSC16 sez:\n%s\n\n", szParams);

    /* store string count back into the 32 bit variable */
    *retc = cchString;

    /* return the string count the normal way */
    return(cchString);
}
