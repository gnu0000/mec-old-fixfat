

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
//#include <os2.h>

#undef _REGS_DEFINED
#include <dos.h>

char  BUFFER [1024];

typedef unsigned short USHORT;


USHORT ReadBootRec (void)
   {
   union REGS inregs, outregs;

   /*--- Read Boot Rec ---*/
   inregs.h.al = 0;
   inregs.x.cx = 1;
   inregs.x.dx = 0;
   inregs.x.bx = (USHORT) BUFFER;
   int86 (0x25, &inregs, &outregs);
   return (outregs.x.cflag);
   }



USHORT WriteBootRec (void)
   {
   union REGS inregs, outregs;

   /*--- Write Boot Rec ---*/
   inregs.h.al = 0;
   inregs.x.cx = 1;
   inregs.x.dx = 0;
   inregs.x.bx = (USHORT) BUFFER;
   int86 (0x26, &inregs, &outregs);
   return (outregs.x.cflag);
   }


USHORT ReadFromFile ()
   {
   char  szFile[80];
   FILE  *fp;

   printf ("Enter file name to read :");
   gets (szFile);
   printf ("\n");
   if (! (fp = fopen (szFile, "rb")))
      {
      printf ("Unable to open input file: %s\n", szFile);
      return 1;
      }
   fread (BUFFER, 512, 1, fp);
   fclose (fp);
   }


USHORT WriteToFile ()
   {
   char  szFile[80];
   FILE  *fp;

   printf ("Enter file name to write :");
   gets (szFile);
   printf ("\n");
   if (! (fp = fopen (szFile, "wb")))
      {
      printf ("Unable to open input file: %s\n", szFile);
      return 1;
      }
   fwrite (BUFFER, 512, 1, fp);
   fclose (fp);
   }


int main (int argc, char *argv[])
   {
   int c;

   while (1)
      {
      printf ("[R] Read boot rec from disk\n");
      printf ("[W] Write boot rec to disk \n");
      printf ("[1] Read boot rec from file\n");
      printf ("[2] Write boot rec to file \n");
      printf ("[Q]uit");                  
      c = getch ();
      printf ("\n");
      switch (toupper (c))
         {
         case 'R':
            if (ReadBootRec ())
               printf ("Error reading Boot Rec.\n");
            break;   
         case 'W':
            if (WriteBootRec ())
               printf ("Error writing Boot Rec.\n");
            break;
         case '1':
            ReadFromFile ();
            break;
         case '2':
            WriteToFile ();
            break;

         case 'Q':
            exit (0);
            break;
         }
      }
   return 0;
   }
