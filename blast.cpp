// blast.cpp - MEMORY STRESS TEST SCRIPT
//
// Note: This allocates huge blocks of memory and fills with 1
//
// MAINTENANCE HISTORY
// DATE         AUTHOR AND DETAILS
// 15-12-09     BAS     TR - ORIGINAL (modified)
//
//----------------------------------------------------------------------------79

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #define MEGABYTE 1024*1024

int *myblock[10000] ;

 int main(int argc, char *argv[])
 {
         
         int count = 0;
         char ch,*mem;

         if ( argv[1] == NULL ) {
                 printf("usage: blast <memmory space>\n");
                 exit(0);
         }

         int memReq = 0;
         memReq = strtol (argv[1],&mem,10);

         //while (1)
         while (count < memReq)
         {
                 myblock[count] = (int *) malloc(MEGABYTE);
                 if (!myblock[count]) break;
                
                for (int i =0 ; i < MEGABYTE/4 ; i++){
                        myblock[count][i] = i + count;
                }
                 
                 printf("Currently allocating %d MB\n", ++count);
         }
         do {
                 printf("Hit 'y' to exit...\n");
                 scanf("%c",&ch);
         } while ( ch == 'y' );
         
         for (int i =0 ; i <count ; i++){
                 free(myblock[i]);
         }
         
         exit(0);
 }
