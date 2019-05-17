#include <stdio.h>

void Rotate(int c, FILE *fp) {

   int t = 63-c;

   for(int i=0; i<64; i++) {

      if (t < 0)
         t+=64;

      fprintf(fp, "1 %d ", t--);

   }

   fprintf(fp, "\n\n");

}

int main() {

   FILE *fp;
   fp = fopen("temp.txt", "w");

   fprintf(fp, "// The following code implements Chi stage\n\n");

   for (int i=0; i<5; i++) {

      // ----- RESET UX partition -----

      fprintf(fp, "// Resetting UX partition\n\n");   

      for (int k=32; k<=41; k++) {

         fprintf(fp, "Apply %d 0 00 000000 ", k);
         Rotate(0,fp); 

      }

      // ----- Copy SHA-3 states to CM and UX -----

      fprintf(fp, "// Copy SHA-3 states to CM and UX\n\n");

      for (int j=0; j<5; j++) {

         fprintf(fp, "Read %d\n\n", 5*i+j);

         fprintf(fp, "Apply %d 1 01 000000 ", 32 + 2*j);
         Rotate(0,fp);

         fprintf(fp, "Apply %d 1 01 000000 ", 33 + 2*j);
         Rotate(0,fp);

         fprintf(fp, "Apply %d 1 01 000000 ", 25 + j);  
         Rotate(0,fp);

      }

      // ----- Compute ~wj.wk -----

      fprintf(fp, "// Compute (~wj).wk for all words\n\n");

      for (int j=0; j<5; j++) {

         fprintf(fp, "Read %d\n\n", 32 + 2*((j+2)%5));

         fprintf(fp, "Apply %d 1 00 000000 ", 25 + (j+1)%5);
         Rotate(0,fp);        

      }

      // ----- Compute XNOR in UX -----

      fprintf(fp, "// Compute XNOR in UX\n\n");

      for (int j=0; j<5; j++) {

         fprintf(fp, "Read %d\n\n", 25 + (j+1)%5);

         fprintf(fp, "Apply %d 1 01 000000 ", 32 + 2*j);
         Rotate(0,fp);
         // ~wi + ~(~wj.wk)

         fprintf(fp, "Apply %d 1 00 000000 ", 33 + 2*j);
         Rotate(0,fp);
         // ~wi.~(~wj.wk)

         fprintf(fp, "Read %d\n\n", 32 + 2*j);

         fprintf(fp, "Apply %d 1 01 000000 ", 33 + 2*j);
         Rotate(0,fp);
         // XNOR computation

      }

      // ----- Reset SHA-3 and copy ui -----

      fprintf(fp, "// Reset SHA-3 and copy ui to appropriate location\n\n");

      for (int j=0; j<5; j++) {

         fprintf(fp, "Apply %d 0 00 00000 ", 5*i + j);
         // Reset SHA-3
         Rotate(0,fp);

         fprintf(fp, "Read %d\n\n", 33 + 2*j);

         fprintf(fp, "Apply %d 1 01 000000 ", 5*i+j);
         Rotate(0,fp);
         // Copy ui to appropriate wordline

      }

      // ----- Reset Computation memory -----

      fprintf(fp, "// Reset CM\n\n");

      for (int j=0; j<5; j++) {

         fprintf(fp, "Apply %d 0 00 00000 ", 25+j);
         Rotate(0,fp);
         // Reset CM

      }

   }

   return 0;

}
