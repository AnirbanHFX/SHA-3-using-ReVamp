#include <stdio.h>

void Rotate(int c, FILE *fp) {  // Used for bit shifting
                                // Rotate(0, fp) signifies no bit shifting
   int t = 63-c;

   for(int i=0; i<64; i++) {

      if (t < 0)
         t+=64;

      fprintf(fp, "1 %d ", t--);

   }

   fprintf(fp, "\n\n");

}

int Load(FILE *fp, int cyc) {  //Verified

   int i, j;

   fprintf(fp, "// Loads the initial SHA-3 states into the SHA-3 State logical compartment of the DCM\n\n\n");

   for(j=0; j<25; j++) {

      fprintf(fp, "Apply 25 0 01 000000 ");  cyc++;
      Rotate(0, fp);

      fprintf(fp, "\nRead 25\n\n");  cyc++;

      fprintf(fp, "Apply %d 1 01 000000 ", j);  cyc++;
      Rotate(0, fp);

      fprintf(fp, "// Stores state %d in non inverted form", j);

      fprintf(fp, "\n\n");

      fprintf(fp, "Apply 25 0 00 000000 ");  cyc++;
      Rotate(0, fp);

      fprintf(fp, "// Resetting wl 25");

      fprintf(fp, "\n\n");

   }

   return cyc;

}

int Theta(FILE *fp, int cyc) {   ///// VERIFIED //////

   // ---- 5 times 5XOR --------

   fprintf(fp, "// The following code implements 5 input XOR 5 times\n\n");

   for (int i=0; i<5; i++) {

      fprintf(fp, "// Implementation of 5 inp XOR\n\n");

      fprintf(fp, "Read %d\n\n", i);  cyc++;  // Read A[i, 0]

      fprintf(fp, "Apply 26 1 01 000000 ");  cyc++;  
      Rotate(0, fp);

      fprintf(fp, "Read 26\n\n");  cyc++;

      fprintf(fp, "Apply 29 1 01 000000 ");  cyc++;
      Rotate(0, fp);     

      fprintf(fp, "Apply 30 1 01 000000 ");  cyc++;
      Rotate(0, fp);     

      fprintf(fp, "Apply 31 1 01 000000 ");  cyc++;
      Rotate(0, fp);     

      fprintf(fp, "Read %d\n\n", i+5);  cyc++;  // Read A[i, 1]

      fprintf(fp, "Apply 29 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// a + ~b");
      fprintf(fp, "\n\n");     

      fprintf(fp, "Apply 30 1 00 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// a.~b");
      fprintf(fp, "\n\n");    

      fprintf(fp, "Apply 31 1 00 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// a.~b");
      fprintf(fp, "\n\n");   

      fprintf(fp, "Read 29\n\n");  cyc++;

      fprintf(fp, "Apply 30 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// a.~b + ~(a+~b) = a XOR b");
      fprintf(fp, "\n\n");

      fprintf(fp, "Apply 31 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// a.~b + ~(a+~b) = a XOR b");
      fprintf(fp, "\n\n"); 

      fprintf(fp, "Read %d\n\n", i+10);  cyc++;  // Read A[i, 2]

      fprintf(fp, "Apply 25 1 01 000000 ");  cyc++;
      Rotate(0, fp); 

      fprintf(fp, "Read 25\n\n");  cyc++;

      fprintf(fp, "Apply 27 1 01 000000 ");  cyc++;
      Rotate(0, fp); 

      fprintf(fp, "Apply 28 1 01 000000 ");  cyc++;/////////
      Rotate(0, fp);

      fprintf(fp, "Read %d\n\n", i+15);  cyc++;  // Read A[i, 3]

      fprintf(fp, "Apply 27 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// c + ~d");
      fprintf(fp, "\n\n"); 

      fprintf(fp, "Apply 28 1 00 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// c.~d");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 27\n\n");  cyc++;

      fprintf(fp, "Apply 28 1 01 000000 ");  cyc++; 
      Rotate(0, fp);
      fprintf(fp, "// c.~d + ~(c+~d) = c XOR d");
      fprintf(fp, "\n\n"); 

      fprintf(fp, "Read 28\n\n");  cyc++;

      fprintf(fp, "Apply 31 1 00 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// (aXORb).~(cXORd)");
      fprintf(fp, "\n\n");

      fprintf(fp, "Apply 30 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// (aXORb) + ~(cXORd)");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 30\n\n");  cyc++;

      fprintf(fp, "Apply 31 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// (aXORb)XOR(cXORd)");   // Result in wl 31
      fprintf(fp, "\n\n");

      for (int l=25; l<=30; l++) {   // Resetting wl 25 to 30

         fprintf(fp, "Apply %d 0 00 000000 ", l);  cyc++;
         Rotate(0, fp);

      }

      fprintf(fp, "Read 31\n\n");  cyc++;

      fprintf(fp, "Apply 27 1 01 000000 ");  cyc++;
      Rotate(0, fp);

      fprintf(fp, "Read 27\n\n");  cyc++;

      fprintf(fp, "Apply 30 1 01 000000 ");  cyc++;
      Rotate(0, fp);

      fprintf(fp, "Read %d\n\n", i+20);  cyc++; // Read A[i,4]

      fprintf(fp, "Apply 31 1 00 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// (aXORbXORcXORd).~e");
      fprintf(fp, "\n\n"); 

      fprintf(fp, "Apply 30 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// (aXORbXORcXORd) + ~e");
      fprintf(fp, "\n\n"); 

      fprintf(fp, "Read 30\n\n");  cyc++;

      fprintf(fp, "Apply 31 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// (aXORbXORcXORd)XORe");
      fprintf(fp, "\n\n");

      // One 5 input XOR calculated and stored in wl 31
      fprintf(fp, "// One 5 input XOR calculated and stored in wl 31. This is copied to UX and Computation memory is reset\n\n");

      fprintf(fp, "Apply %d 0 00 000000 ", 32+2*i);  cyc++; // Reset UX
      Rotate(0, fp);      

      fprintf(fp, "Read 31\n\n");  cyc++;

      fprintf(fp, "Apply %d 1 01 000000 ", 32+2*i);  cyc++;
      Rotate(0, fp);

      // Resets Computation memory

      fprintf(fp, "Apply 27 0 00 000000 ");  cyc++;
      Rotate(0, fp);

      fprintf(fp, "Apply 30 0 00 000000 ");  cyc++;
      Rotate(0, fp); 

      fprintf(fp, "Apply 31 0 00 000000 ");  cyc++;
      Rotate(0, fp);

   }  

   // --------------------------

   // Shifting of ri to generate si and calculation of mi

   fprintf(fp, "// Shifting of ri to generate si and calculation of mi\n\n");

   for (int i=0; i<5; i++) {

      fprintf(fp, "Read %d\n\n", 32+2*((i+1)%5));  cyc++;

      fprintf(fp, "Apply 25 1 01 000000 ");  cyc++;
      Rotate(1, fp);
      fprintf(fp, "// Shifted copy from UX to Computation memory");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read %d\n\n", 32+2*((i+4)%5));  cyc++;

      fprintf(fp, "Apply 28 1 01 000000 ");  cyc++;
      Rotate(0, fp);

      fprintf(fp, "Apply 29 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// Direct copy from UX to Computation memory");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 25\n\n");  cyc++;

      fprintf(fp, "Apply 28 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// ri+1 + ~si");
      fprintf(fp, "\n\n");

      fprintf(fp, "Apply 29 1 00 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// ri+1.~si");
      fprintf(fp, "\n\n");

      fprintf(fp, "Read 28\n\n");  cyc++;

      fprintf(fp, "Apply 29 1 01 000000 ");  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// ri+1XORsi");
      fprintf(fp, "\n\n");

      fprintf(fp, "Apply %d 0 00 000000 ", 33+2*i);  cyc++;   // Reset UX
      Rotate(0, fp);

      fprintf(fp, "Read 29\n\n");  cyc++;

      fprintf(fp, "Apply %d 1 01 000000 ", 33+2*i);  cyc++;
      Rotate(0, fp);
      fprintf(fp, "// Copy result to UX in inverted form");
      fprintf(fp, "\n\n");

      fprintf(fp, "Apply 25 0 00 000000 ");  cyc++;
      Rotate(0, fp);

      fprintf(fp, "Apply 28 0 00 000000 ");  cyc++;
      Rotate(0, fp);

      fprintf(fp, "Apply 29 0 00 000000 ");  cyc++;
      Rotate(0, fp);

   } 

   // ---------------------------

   // -----Updation of Words-----

   int a;

   fprintf(fp, "// The following code updates each word in the SHA-3 state\n\n");

   for (int i=0; i<5; i++) {

      for (int j=0; j<25; j+=5) {

         a = j+i;

         // ----XNOR-----

         fprintf(fp, "Read %d\n\n", 33+2*i);  cyc++;

         fprintf(fp, "Apply 25 1 01 000000 ");  cyc++;
         Rotate(0, fp);
         fprintf(fp, "// Copy mj");
         fprintf(fp, "\n\n");

         fprintf(fp, "Read 25\n\n");  cyc++;

         fprintf(fp, "Apply 28 1 01 000000 ");  cyc++;
         Rotate(0, fp);
         fprintf(fp, "// Copy ~mj");
         fprintf(fp, "\n\n");

         fprintf(fp, "Apply 29 1 01 000000 ");  cyc++;
         Rotate(0, fp);
         fprintf(fp, "// Copy ~mj");
         fprintf(fp, "\n\n");

         fprintf(fp, "Read %d\n\n", a);  cyc++;

         fprintf(fp, "Apply 29 1 00 000000 ");  cyc++;
         Rotate(0, fp);
         fprintf(fp, "// ~mj.~wi");
         fprintf(fp, "\n\n");

         fprintf(fp, "Apply 28 1 01 000000 ");  cyc++;
         Rotate(0, fp);
         fprintf(fp, "// ~mj+~wi");
         fprintf(fp, "\n\n");

         fprintf(fp, "Read 28\n\n");  cyc++;

         fprintf(fp, "Apply 29 1 01 000000 ");  cyc++;
         Rotate(0, fp);
         fprintf(fp, "// mj XNOR wi");
         fprintf(fp, "\n\n"); 

         // -------------

         // Reset current SHA-3 state word

         fprintf(fp, "Apply %d 0 00 000000 ", a);  cyc++;
         Rotate(0, fp);
         // -------------

         // Copy new state to SHA-3 memory partition
 
         fprintf(fp, "Read 29\n\n");  cyc++;

         fprintf(fp, "Apply %d 1 01 000000 ", a);  cyc++;
         Rotate(0, fp);
         fprintf(fp, "// ~(mj XNOR wi) = mj XOR wi");
         fprintf(fp, "\n\n");

         // --------------

         // Reset computation memory

         fprintf(fp, "Apply 25 0 00 000000 ");  cyc++;
         Rotate(0, fp);

         fprintf(fp, "Apply 28 0 00 000000 ");  cyc++;
         Rotate(0, fp); 

         fprintf(fp, "Apply 29 0 00 000000 ");  cyc++;
         Rotate(0, fp);
  
      }

   } 

   return cyc;

}

int RhoPi(FILE *fp, int cyc) {  //// VERIFIED ////////

   const int rot_c[24] = {1,  3,  6,  10, 15, 21, 28, 36, 45, 55, 2,  14,
        27, 41, 56, 8,  25, 43, 62, 18, 39, 61, 20, 44};

   const int keccak_piln[24] = { 10, 7,  11, 17, 18, 3, 5,  16, 8,  21, 24, 4,
        15, 23, 19, 13, 12, 2, 20, 14, 22, 9,  6,  1};
    
   int a, b;
   int i=0, j=0;
   int loc = 0;

   int c=0;

   fprintf(fp, "// The following code implements Rho and Pi stages\n\n");

   a = 1;

   fprintf(fp, "\nRead %d\n\n", a);  cyc++;

   fprintf(fp, "Apply %d 1 01 000000 ", 25+loc);  cyc++;
   Rotate(0, fp);

   loc = (loc+1)%2;

   while(i < 24) {

      j = keccak_piln[i];

      fprintf(fp, "\nRead %d\n\n", j);  cyc++;

      fprintf(fp, "Apply %d 0 00 000000 ", 25+loc);  cyc++;// Resets Computation memory
      Rotate(0, fp);

      fprintf(fp, "Apply %d 1 01 000000 ", 25+loc);  cyc++;
      Rotate(0, fp);

      loc = (loc+1)%2;

      fprintf(fp, "\nRead %d\n\n", 25+loc);  cyc++;

      fprintf(fp, "Apply %d 0 00 000000 ", j);  cyc++;  // Resets SHA-3 state location where shifted word is to be copied
      Rotate(0, fp);   

      fprintf(fp, "Apply %d 1 01 000000 ", j);  cyc++;  // Copied shifted word
      Rotate(rot_c[i], fp);

      i++;

   }

   fprintf(fp, "Apply %d 0 00 000000 ", 25);  cyc++;  // Resets Computation memory
   Rotate(0, fp);

   fprintf(fp, "Apply %d 0 00 000000 ", 26);  cyc++;  // Resets Computation memory
   Rotate(0, fp);

   return cyc;

}

int Chi(FILE *fp, int cyc) {  //// VERIFIED /////

   fprintf(fp, "// The following code implements Chi stage\n\n");

   for (int i=0; i<5; i++) {

      // ----- RESET UX partition -----

      fprintf(fp, "// Resetting UX partition\n\n");   

      for (int k=32; k<=41; k++) {

         fprintf(fp, "Apply %d 0 00 000000 ", k);  cyc++;
         Rotate(0,fp); 

      }

      // ----- Copy SHA-3 states to CM and UX -----

      fprintf(fp, "// Copy SHA-3 states to CM and UX\n\n");

      for (int j=0; j<5; j++) {

         fprintf(fp, "Read %d\n\n", 5*i+j);  cyc++;

         fprintf(fp, "Apply %d 1 01 000000 ", 32 + 2*j);  cyc++;
         Rotate(0,fp);

         fprintf(fp, "Apply %d 1 01 000000 ", 33 + 2*j);  cyc++;
         Rotate(0,fp);

         fprintf(fp, "Apply %d 1 01 000000 ", 25 + j);  cyc++;
         Rotate(0,fp);

      }

      // ----- Compute ~wj.wk -----

      fprintf(fp, "// Compute (~wj).wk for all words\n\n");

      for (int j=0; j<5; j++) {

         fprintf(fp, "Read %d\n\n", 32 + 2*((j+2)%5));  cyc++;

         fprintf(fp, "Apply %d 1 00 000000 ", 25 + (j+1)%5);  cyc++;
         Rotate(0,fp);        

      }

      // ----- Compute XNOR in UX -----

      fprintf(fp, "// Compute XNOR in UX\n\n");

      for (int j=0; j<5; j++) {

         fprintf(fp, "Read %d\n\n", 25 + (j+1)%5);  cyc++;

         fprintf(fp, "Apply %d 1 01 000000 ", 32 + 2*j);  cyc++;
         Rotate(0,fp);
         // ~wi + ~(~wj.wk)

         fprintf(fp, "Apply %d 1 00 000000 ", 33 + 2*j);  cyc++;
         Rotate(0,fp);
         // ~wi.~(~wj.wk)

         fprintf(fp, "Read %d\n\n", 32 + 2*j);  cyc++;

         fprintf(fp, "Apply %d 1 01 000000 ", 33 + 2*j);  cyc++;
         Rotate(0,fp);
         // XNOR computation

      }

      // ----- Reset SHA-3 and copy ui -----

      fprintf(fp, "// Reset SHA-3 and copy ui to appropriate location\n\n");

      for (int j=0; j<5; j++) {

         fprintf(fp, "Apply %d 0 00 00000 ", 5*i + j);  cyc++;
         // Reset SHA-3
         Rotate(0,fp);

         fprintf(fp, "Read %d\n\n", 33 + 2*j);  cyc++;

         fprintf(fp, "Apply %d 1 01 000000 ", 5*i+j);  cyc++;
         Rotate(0,fp);
         // Copy ui to appropriate wordline

      }

      // ----- Reset Computation memory -----

      fprintf(fp, "// Reset CM\n\n");

      for (int j=0; j<5; j++) {

         fprintf(fp, "Apply %d 0 00 00000 ", 25+j);  cyc++;
         Rotate(0,fp);
         // Reset CM

      }

   }

   return cyc;

}

int Iota(FILE *fp, FILE *fp2, int cyc) {  ///// VERIFIED /////

   fprintf(fp, "// The following code implements Iota stage\n\n");

   fprintf(fp, "Read 0\n\n");  cyc++;
   // Read A[0, 0]

   fprintf(fp, "Apply 28 1 01 000000 ");  cyc++;
   Rotate(0,fp);
   // Store ~w0 at wl 28

   fprintf(fp, "Apply 29 1 01 000000 ");  cyc++;
   Rotate(0,fp);
   // Store ~w0 at wl 29

   // ----------- PIR Loads RC
   fprintf(fp, "Apply 28 0 01 000000 ");  cyc++;
   Rotate(0,fp);
   // ~w0 + ~RC

   printf("CYCLE for RC: %d\n", cyc);

   fprintf(fp2, "%d, ", cyc);

   fprintf(fp, "Apply 29 0 00 000000 ");  cyc++;
   Rotate(0,fp);
   // ~w0.~RC 

   fprintf(fp, "Read 28\n\n");  cyc++;

   fprintf(fp, "Apply 29 1 01 000000 ");  cyc++;
   Rotate(0,fp);
   // w0 XNOR RC

   fprintf(fp, "Read 29\n\n");  cyc++;

   // Reset Wordline 0
   // ------------- PIR Loads string of 1s
   fprintf(fp, "Apply 0 0 00 000000 ");  cyc++;
   Rotate(0,fp); 

   fprintf(fp2, "%d, ", cyc);

   // Store w0 XOR RC at wordline 0  

   fprintf(fp, "Apply 0 1 01 000000 ");  cyc++;
   Rotate(0,fp); 

   // Reset Computation memory

   fprintf(fp, "Apply 28 0 00 000000 ");  cyc++;
   Rotate(0,fp);

   fprintf(fp, "Apply 29 0 00 000000 ");  cyc++;
   Rotate(0,fp);

   return cyc;

}

int main() {

   int cyc = 0;

   FILE *fp;
   fp = fopen("Keccak-f1600.ins", "w");

   FILE *fp2;
   fp2 = fopen("RCt.csv", "w");

   cyc = Load(fp, cyc);

   for (int i=0; i<24; i++) {

      cyc = Theta(fp, cyc);

      cyc = RhoPi(fp, cyc);

      cyc = Chi(fp, cyc);

      cyc = Iota(fp, fp2, cyc);

   }

   return 0;  

}
