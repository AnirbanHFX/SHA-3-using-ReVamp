#include <stdio.h>
#define PREVk 50


int main() {

   FILE *fp;
   FILE *fp2;
   int k = PREVk + 1;

   fp = fopen("temp.txt", "w");
   fp2 = fopen("temp2.txt", "w");

   // ---- 5 times 5XOR --------

   fprintf(fp, "// The following code implements 5 input XOR 5 times\n\n");

   for (int i=0; i<5; i++) {

      fprintf(fp, "// Implementation of 5 inp XOR\n\n");

      fprintf(fp, "Read %d\n\n", 5*i);

      // fprintf(fp, "// %d PIR call :: PIR = [ A[%d, 0] ]\n", k++, i);
      fprintf(fp, "Apply 26 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 26\n\n");

      fprintf(fp, "Apply 29 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n\n");      

      fprintf(fp, "Apply 30 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n\n");      

      fprintf(fp, "Apply 31 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n\n");      

      fprintf(fp, "Read %d\n\n", 5*i+1);

      //fprintf(fp, "// %d PIR call :: PIR = [ A[%d, 1] ]\n", k++, i);
      fprintf(fp, "Apply 29 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// a + ~b");
      fprintf(fp, "\n\n");     

      //fprintf(fp, "// %d PIR call :: PIR = [ A[%d, 1] ]\n", k++, i);
      fprintf(fp, "Apply 30 1 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// a.~b");
      fprintf(fp, "\n\n");    

      //fprintf(fp, "// %d PIR call :: PIR = [ A[%d, 1] ]\n", k++, i);
      fprintf(fp, "Apply 31 1 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// a.~b");
      fprintf(fp, "\n\n");   

      fprintf(fp, "Read 29\n\n");

      fprintf(fp, "Apply 30 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// a.~b + ~(a+~b) = a XOR b");
      fprintf(fp, "\n\n");

      fprintf(fp, "Apply 31 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// a.~b + ~(a+~b) = a XOR b");
      fprintf(fp, "\n\n"); 

      fprintf(fp, "Read %d\n\n", 5*i+2);

      //fprintf(fp, "// %d PIR call :: PIR = [ A[%d, 2] ]\n", k++, i);
      fprintf(fp, "Apply 25 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n\n");  

      fprintf(fp, "Read 25\n\n");

      fprintf(fp, "Apply 27 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n\n");  

      fprintf(fp, "Apply 28 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n\n");  

      fprintf(fp, "Read %d\n\n", 5*i+3);

      //fprintf(fp, "// %d PIR call :: PIR = [ A[%d, 3] ]\n", k++, i);
      fprintf(fp, "Apply 27 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// c + ~d");
      fprintf(fp, "\n\n"); 

      //fprintf(fp, "// %d PIR call :: PIR = [ A[%d, 3] ]\n", k++, i);
      fprintf(fp, "Apply 28 1 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// c.~d");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 27\n\n");

      fprintf(fp, "Apply 28 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// c.~d + ~(c+~d) = c XOR d");
      fprintf(fp, "\n\n"); 

      fprintf(fp, "Read 28\n\n");

      fprintf(fp, "Apply 31 1 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// (aXORb).~(cXORd)");
      fprintf(fp, "\n\n");

      fprintf(fp, "Apply 30 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// (aXORb) + ~(cXORd)");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 30\n\n");

      fprintf(fp, "Apply 31 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// (aXORb)XOR(cXORd)");   // Result in wl 31
      fprintf(fp, "\n\n");

      for (int l=25; l<=30; l++) {   // Resetting wl 25 to 30

         fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
         fprintf(fp, "Apply %d 0 00 000000 ", l);
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// Resetting wl %d", l);
         fprintf(fp, "\n\n"); 

         fprintf(fp2, "%d ", k-1);
         for(int c=0; c<64; c++) {
            fprintf(fp2, "%d", 1);
         }
         fprintf(fp2, "\n\n");

      }

      fprintf(fp, "Read 31\n\n");

      fprintf(fp, "Apply 27 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 27\n\n");

      fprintf(fp, "Apply 30 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n\n");

      fprintf(fp, "Read %d\n\n", 5*i+4);

      //fprintf(fp, "// %d PIR call :: PIR = [ A[%d, 4] ]\n", k++, i);
      fprintf(fp, "Apply 31 1 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// (aXORbXORcXORd).~e");
      fprintf(fp, "\n\n"); 

      //fprintf(fp, "// %d PIR call :: PIR = [ A[%d, 4] ]\n", k++, i);
      fprintf(fp, "Apply 30 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// (aXORbXORcXORd) + ~e");
      fprintf(fp, "\n\n"); 

      fprintf(fp, "Read 30\n\n");

      fprintf(fp, "Apply 31 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// (aXORbXORcXORd)XORe");
      fprintf(fp, "\n\n");

      // One 5 input XOR calculated and stored in wl 31
      fprintf(fp, "// One 5 input XOR calculated and stored in wl 31. This is copied to UX and Computation memory is reset\n\n");

      fprintf(fp, "Read 31\n\n");

      fprintf(fp, "Apply %d 1 01 000000 ", 32+2*i);
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// Stores inverted 5XOR in UX wl %d", 32 + 2*i);
      fprintf(fp, "\n\n");

      // Resets Computation memory

      fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
      fprintf(fp, "Apply 27 0 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// Reset wl 27");
      fprintf(fp, "\n\n");

      fprintf(fp2, "%d ", k-1);
      for(int c=0; c<64; c++) {
         fprintf(fp2, "%d", 1);
      }
      fprintf(fp2, "\n\n");

      fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
      fprintf(fp, "Apply 30 0 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// Reset wl 30");
      fprintf(fp, "\n\n");  

      fprintf(fp2, "%d ", k-1);
      for(int c=0; c<64; c++) {
         fprintf(fp2, "%d", 1);
      }
      fprintf(fp2, "\n\n");

      fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
      fprintf(fp, "Apply 31 0 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// Reset wl 31");
      fprintf(fp, "\n\n");

      fprintf(fp2, "%d ", k-1);
      for(int c=0; c<64; c++) {
         fprintf(fp2, "%d", 1);
      }
      fprintf(fp2, "\n\n");

   }

   // --------------------------

   // Shifting of ri to generate si and calculation of mi

   fprintf(fp, "// Shifting of ri to generate si and calculation of mi\n\n");

   for (int i=0; i<5; i++) {

      fprintf(fp, "Read %d\n\n", 32+2*i);

      fprintf(fp, "Apply 25 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         if (j-1>0)
            fprintf(fp, "1 %d ", j-1);
         else
            fprintf(fp, "1 %d ", 63);             
      }
      fprintf(fp, "\n// Shifted copy from UX to Computation memory");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read %d\n\n", 32+2*((i+1)%5));

      fprintf(fp, "Apply 28 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// Direct copy from UX to Computation memory");
      fprintf(fp, "\n\n");

      fprintf(fp, "Apply 29 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// Direct copy from UX to Computation memory");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 25\n\n");

      fprintf(fp, "Apply 28 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// ri+1 + ~si");
      fprintf(fp, "\n\n");

      fprintf(fp, "Apply 29 1 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// ri+1.~si");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 28\n\n");

      fprintf(fp, "Apply 29 1 01 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// ri+1XORsi");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 29\n\n");

      fprintf(fp, "Apply %d 1 01 000000 ", 33+2*i);
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// Copy result to UX in inverted form");
      fprintf(fp, "\n\n");

      fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
      fprintf(fp, "Apply 25 0 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// Reset wl 25");
      fprintf(fp, "\n\n");

      fprintf(fp2, "%d ", k-1);
      for(int c=0; c<64; c++) {
         fprintf(fp2, "%d", 1);
      }
      fprintf(fp2, "\n\n");

      fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
      fprintf(fp, "Apply 28 0 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// Reset wl 28");
      fprintf(fp, "\n\n");

      fprintf(fp2, "%d ", k-1);
      for(int c=0; c<64; c++) {
         fprintf(fp2, "%d", 1);
      }
      fprintf(fp2, "\n\n");

      fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
      fprintf(fp, "Apply 29 0 00 000000 ");
      for(int j=63; j>=0; j--) {
         fprintf(fp, "1 %d ", j); 
      }
      fprintf(fp, "\n// Reset wl 29");
      fprintf(fp, "\n\n");

      fprintf(fp2, "%d ", k-1);
      for(int c=0; c<64; c++) {
         fprintf(fp2, "%d", 1);
      }
      fprintf(fp2, "\n\n");

   }

   // ---------------------------

   // -----Updation of Words-----

   int a;

   fprintf(fp, "// The following code updates each word in the SHA-3 state\n\n");

   for (int i=0; i<5; i++) {

      for (int j=0; j<5; j++) {

         a = 5*i+j;

         // ----XNOR-----

         fprintf(fp, "Read %d\n\n", 33+2*i);

         fprintf(fp, "Apply 25 1 01 000000 ");
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// Copy mj");
         fprintf(fp, "\n\n");

         fprintf(fp, "Read 25\n\n");

         fprintf(fp, "Apply 28 1 01 000000 ");
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// Copy ~mj");
         fprintf(fp, "\n\n");

         fprintf(fp, "Apply 29 1 01 000000 ");
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// Copy ~mj");
         fprintf(fp, "\n\n");

         fprintf(fp, "Read %d\n\n", a);

         fprintf(fp, "Apply 29 1 00 000000 ");
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// ~mj.~wi");
         fprintf(fp, "\n\n");

         fprintf(fp, "Apply 28 1 01 000000 ");
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// ~mj+~wi");
         fprintf(fp, "\n\n");

         fprintf(fp, "Read 28\n\n");

         fprintf(fp, "Apply 29 1 01 000000 ");
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// mj XNOR wi");
         fprintf(fp, "\n\n");

         // -------------

         // Reset current SHA-3 state word

         fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
         fprintf(fp, "Apply %d 0 00 000000 ", a);
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// Resetting wl %d", a);
         fprintf(fp, "\n\n"); 

         fprintf(fp2, "%d ", k-1);
         for(int c=0; c<64; c++) {
            fprintf(fp2, "%d", 1);
         }
         fprintf(fp2, "\n\n");
  
         // -------------

         // Copy new state to SHA-3 memory partition
 
         fprintf(fp, "Read 29\n\n");

         fprintf(fp, "Apply %d 1 01 000000 ", a);
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// ~(mj XNOR wi) = mj XOR wi");
         fprintf(fp, "\n\n");

         // --------------

         // Reset computation memory

         fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
         fprintf(fp, "Apply 25 0 00 000000 ");
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// Resetting wl 25");
         fprintf(fp, "\n\n"); 

         fprintf(fp2, "%d ", k-1);
         for(int c=0; c<64; c++) {
            fprintf(fp2, "%d", 1);
         }
         fprintf(fp2, "\n\n");

         fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
         fprintf(fp, "Apply 28 0 00 000000 ");
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// Resetting wl 28");
         fprintf(fp, "\n\n"); 

         fprintf(fp2, "%d ", k-1);
         for(int c=0; c<64; c++) {
            fprintf(fp2, "%d", 1);
         }
         fprintf(fp2, "\n\n");

         fprintf(fp, "// %d PIR call :: PIR = [ String of 1's ]\n", k++);
         fprintf(fp, "Apply 29 0 00 000000 ");
         for(int j=63; j>=0; j--) {
            fprintf(fp, "1 %d ", j); 
         }
         fprintf(fp, "\n// Resetting wl 29");
         fprintf(fp, "\n\n"); 

         fprintf(fp2, "%d ", k-1);
         for(int c=0; c<64; c++) {
            fprintf(fp2, "%d", 1);
         }
         fprintf(fp2, "\n\n");
  
      }

   } 

   fclose (fp);
   return 0;

}
