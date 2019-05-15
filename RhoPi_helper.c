#include <stdio.h>
#include <stdlib.h>

#define PREVk 210

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

   int k = PREVk + 1;

   FILE *fp;
   FILE *fp2;
   fp = fopen("temp.txt", "w");
   fp2 = fopen("temp2.txt", "w");

   int rot_c[25] = {0, 1, 62, 28, 27, 36, 44, 6, 55, 20, 3, 10, 43,
	25, 39, 41, 45, 15, 21, 8, 18, 2, 61, 56, 14};

   int a, b;
   int i=0, j=1;
   int loc = 0;

   int c=0;

   fprintf(fp, "// The following code implements Rho and Pi stages\n\n");

   a = 5*i+j;

   fprintf(fp, "\nRead %d\n\n", a);

   fprintf(fp, "Apply %d 0 01 000000 ", 25+loc);
   Rotate(0, fp);

   loc = (loc+1)%2;

   while(c < 24) {

      a = 5*i+j;
      b = 5*j + (2*i+3*j)%5;

      printf("%d\n", a);

      i = b/5;
      j = b%5;

      fprintf(fp, "\nRead %d\n\n", b);

      fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++, j);
      fprintf(fp2, "%d ", k-1);
      for(int c=0; c<64; c++) {
         fprintf(fp2, "%d", 1);
      }
      fprintf(fp2, "\n\n");

      fprintf(fp, "Apply %d 0 00 000000 ", 25+loc);  // Resets Computation memory
      Rotate(0, fp);

      fprintf(fp, "Apply %d 0 01 000000 ", 25+loc);
      Rotate(0, fp);

      loc = (loc+1)%2;

      fprintf(fp, "\nRead %d\n\n", 25+loc);

      fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++, j);
      fprintf(fp2, "%d ", k-1);
      for(int c=0; c<64; c++) {
         fprintf(fp2, "%d", 1);
      }
      fprintf(fp2, "\n\n");

      fprintf(fp, "Apply %d 0 00 000000 ", b);  // Resets SHA-3 state location where shifted word is to be copied
      Rotate(0, fp);   

      fprintf(fp, "Apply %d 0 01 000000 ", b);  // Copied shifted word
      Rotate(rot_c[c+1], fp);

      c++;

   }

   return 0;

}
