ALL: MSC16.DLL MSC16.LIB

MSC16.OBJ : MSC16.c 
     cl /Fs -c -G2s -W4 -Alfu MSC16.C

MSC16.DLL : MSC16.OBJ MSC16.DEF
     link @<< 
MSC16.obj /align:16, 
MSC16.dll, 
MSC16.map /NOD,
llibcdll.lib os2.lib, 
MSC16.def
<<

MSC16.LIB : MSC16.OBJ MSC16.DLL MSC16.DEF
     implib MSC16.lib MSC16.def
