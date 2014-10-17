/* This header file belongs to WAT2MSC.C which demonstrates the */
/* 32->16 bit thunking process bug.                             */

/* func prototypes */
SHORT main(void);

/* This typedef was created for this demo and you'll have to modify the */
/* parameters portion to suit your own needs. Remember to change the    */
/* typedef name from PFNHLL16 to something that makes sense to you      */
typedef void __export __loadds __pascal (__far16 *PFNHLL16)(USHORT *_Seg16, 
                              CHAR *_Seg16, USHORT *_Seg16, USHORT *_Seg16);

