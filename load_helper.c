#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void randombin(int *arr) {

   int k;

   for(int c=0; c<64; c++) {

      k = rand()%1000;

      if (k > 500)
         arr[c] = 1;
      else
         arr[c] = 0;
   }

}

int main() {

   srand(time(NULL));

   FILE *fp;
   FILE *fp2;
   int i, j, k=1;

   int **state = (int **) malloc(25*sizeof(int *));

   fp = fopen("temp.txt", "w");
   fp2 = fopen("temp2.txt", "w");

   fprintf(fp, "// Loads the initial SHA-3 states into the SHA-3 State logical compartment of the DCM\n\n\n");

   for(j=0; j<25; j++) {

      state[j] = (int *) malloc(64*sizeof(int));

      randombin(state[j]);

      fprintf(fp, "// %d PIR call :: PIR = [ Initial State %d ]\n", k++, j);
      fprintf(fp2, "%d ", k-1);
      for(int c=0; c<64; c++) {
         fprintf(fp2, "%d", state[j][c]);
      }
      fprintf(fp2, "\n\n");

      fprintf(fp, "Apply 25 0 01 000000 ");

      for(i=63; i>=0; i--) {
         fprintf(fp, "1 %d ", i); 
      }

      fprintf(fp, "\nRead 25\n\n");

      fprintf(fp, "Apply %d 1 01 000000 ", j);

      for(i=63; i>=0; i--) {
         fprintf(fp, "1 %d ", i); 
      }

      fprintf(fp, "// Stores state %d in non inverted form", j);

      fprintf(fp, "\n\n");

      fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++, j);
      fprintf(fp2, "%d ", k-1);
      for(int c=0; c<64; c++) {
         fprintf(fp2, "%d", 1);
      }
      fprintf(fp2, "\n\n");

      fprintf(fp, "Apply 25 0 00 000000 ");

      for(i=63; i>=0; i--) {
         fprintf(fp, "1 %d ", i); 
      }

      fprintf(fp, "// Resetting wl 25");

      fprintf(fp, "\n\n");

   }

   fclose (fp);
   return 0;

}
