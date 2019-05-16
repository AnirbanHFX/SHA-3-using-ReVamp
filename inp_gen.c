#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {

   srand(time(NULL));

   FILE *fp;
   fp = fopen("temp3.txt", "w");

   for(int i=1; i<=100; i++) {

      if (i%4 == 1) {

         fprintf(fp, "%d ", i);

         for (int j=0; j<64; j++) {

            int t = rand()%1000;

            if (t > 500)
               fprintf(fp, "1");
            else
               fprintf(fp, "0");

         }

      fprintf(fp, "\n\n");

      }

      if (i%4 == 0) {

         fprintf(fp, "%d ", i);

         for (int j=0; j<64; j++) {

            fprintf(fp, "1");

         }

      fprintf(fp, "\n\n");

      }

   }

   fclose(fp);

   return 0;

}
