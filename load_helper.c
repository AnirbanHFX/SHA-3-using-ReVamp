#include <stdio.h>

int main() {

   FILE *fp;
   int i, j, k=1;

   fp = fopen("temp.txt", "w");

   fprintf(fp, "// Loads the initial SHA-3 states into the SHA-3 State logical compartment of the DCM\n\n\n");

   for(j=0; j<25; j++) {

      fprintf(fp, "// %d PIR call :: PIR = [ Initial State %d ]\n", k++, j);
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
