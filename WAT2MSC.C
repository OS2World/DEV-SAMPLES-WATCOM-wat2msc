#define INCL_BASE
#define INCL_DOSMODULEMGR
#include <os2.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "wat2msc.h"     /* func prototypes etc. */

SHORT main(void)
{                
    HMODULE hinstTESTPROC = 0;          /* hInst to 16 bit dll */
    PFNHLL16 pfnHll16=0;              /* 16 bit proc addr */
    PFN pfnHll32=0;                   /* 32 bit proc addr */
    USHORT usFunc, retc=0, length=0;  /* holds func #, rc & cmd length */
    CHAR szFailMod[129], szCmd[10];   /* .dll fail module & str cmd */

    /* dynamically load the 16 bit dll */
    retc = DosLoadModule(szFailMod, sizeof(szFailMod),
                                    "C:\\WATTEST\\MSC16.DLL", 
                                    &hinstTESTPROC);
    if(retc)   /* > 0 == error loading .dll */
    {
        printf("Error '%x' occured while loading the 16 bit dll!\n", retc);
        return(retc);
    }

    /* get 16bit proc address */
    retc = DosQueryProcAddr(hinstTESTPROC, 0, "TESTPROC", &pfnHll32);
    if(retc != 0)
    {
        printf("Error '%x' occured while querying the proc address!\n", retc);
        return(retc);
    }

    /* convert to 16 bit pfn if necessary */
    if(pfnHll32)
    {
        ULONG ulProcType = 0;
        DosQueryProcType(hinstTESTPROC, 0, "TESTPROC", &ulProcType);
        if(ulProcType == 0)
           pfnHll16 = (PFNHLL16)pfnHll32;
    }

    /* we have a dll and a proc addr now load up some  */
    /* params and call the proc.  thunking should work */
    strcpy(szCmd, "howdy!");
    length = strlen(szCmd);
    usFunc = 9;

    /* check for 16 bit address first as we'll always  */
    /* have a 32 bit address (or we would have failed  */
    /* and exited by now)                              */
    if(pfnHll16)
        pfnHll16(&usFunc, &szCmd, &length, &retc);
    else
        pfnHll32(&usFunc, &szCmd, &length, &retc);

    /* display the results, clean up and exit! */
    printf("Return code from MSC16 was %d\n", retc);
    DosFreeModule(hinstTESTPROC);
    return(retc);
}
