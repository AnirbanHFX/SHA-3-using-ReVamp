#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* stringToBinary(char* s) {  // Converts an ascii string to binary
    if(s == NULL) return 0; 
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

char *sponge(char *bin, unsigned int b) {   // Converts a binary string to a SHA-3 state string of length b

   if (bin == NULL)
      return 0;

   unsigned int len = strlen(bin);
   unsigned int bytes = len/8;
   char t;

   char *s = malloc((b+1)*sizeof(char));

   // LSB bit numbering

   for(int i=0; i<bytes; i++) {
      for(int j=0; j<4; j++) {
         t = bin[8*i+j];
         bin[8*i+j] = bin[8*(i+1) - j - 1];
         bin[8*(i+1) - j - 1] = t;
      }
   }

   for(unsigned int i = 0; i<b; i++) {
      
      if (i < len) {
         s[i] = bin[i];
      }

      else if (i == len) 
         s[i] = '0';
      else if (i == len+1)
         s[i] = '1';
      else if (i == len+2)
         s[i] = '1';
      else if (i == b-1)
         s[i] = '1';
      else
         s[i] = '0';

   }

   s[b] = '\0';

   return s;

}


int main() {

   // Keccak Round Constants
   char RC[24][64] =  { "0000000000000000000000000000000000000000000000000000000000000001",
                        "0000000000000000000000000000000000000000000000001000000010000010",
                        "1000000000000000000000000000000000000000000000001000000010001010",
                        "1000000000000000000000000000000010000000000000001000000000000000",
                        "0000000000000000000000000000000000000000000000001000000010001011",
                        "0000000000000000000000000000000010000000000000000000000000000001",
                        "1000000000000000000000000000000010000000000000001000000010000001",
                        "1000000000000000000000000000000000000000000000001000000000001001",
                        "0000000000000000000000000000000000000000000000000000000010001010",
                        "0000000000000000000000000000000000000000000000000000000010001000",
                        "0000000000000000000000000000000010000000000000001000000000001001",
                        "0000000000000000000000000000000010000000000000000000000000001010",
                        "0000000000000000000000000000000010000000000000001000000010001011",
                        "1000000000000000000000000000000000000000000000000000000010001011",
                        "1000000000000000000000000000000000000000000000001000000010001001",
                        "1000000000000000000000000000000000000000000000001000000000000011",
                        "1000000000000000000000000000000000000000000000001000000000000010",
                        "1000000000000000000000000000000000000000000000000000000010000000",
                        "0000000000000000000000000000000000000000000000001000000000001010",
                        "1000000000000000000000000000000010000000000000000000000000001010",
                        "1000000000000000000000000000000010000000000000001000000010000001",
                        "1000000000000000000000000000000000000000000000001000000010000000",
                        "0000000000000000000000000000000010000000000000000000000000000001",
                        "1000000000000000000000000000000010000000000000001000000000001000"
                      };

   FILE *fp, *fp2;
   fp = fopen("Keccak-f1600.inp", "w");

   char *x, *out;
   x = (char *) malloc(199*sizeof(char));
   printf("Input string: ");
   scanf("%s", x);

   out = (char *) malloc((8*strlen(x)+1)*sizeof(char));

   out = stringToBinary(x);

   printf("Bin: %s\n\n", out);

   char *sp = sponge(out, 1600);

   for(int i=0; i<25; i++) {

      for(int j=0; j<64; j++) 
         printf("%c", sp[64*i + j]);
      printf("\n");

   }

   for(int i=1; i<=100; i++) {

      if (i%4 == 1) {

         fprintf(fp, "%d ", i);

         for (int j=63; j>=0; j--) {
            fprintf(fp, "%c", sp[64*(i/4) + j]);
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

   fp2 = fopen ("RCt.csv", "r");  // Reads cycle numbers where PIR is called for Round Constants from file RCt.csv
   int c;

   for (int i=0; i<24; i++) {

      fscanf(fp2, " %d,", &c);

      fprintf(fp, "%d ", c);
      printf("Putting RC at: %d\n", c);

      for (int j=0; j<64; j++)
         fprintf(fp, "%c", RC[i][j]);

      fprintf(fp, "\n\n");

      fscanf(fp2, " %d,", &c);

      fprintf(fp, "%d ", c);
      for (int j=0; j<64; j++)
         fprintf(fp, "%d", 1);

      fprintf(fp, "\n\n");

   }

   fclose(fp);

   return 0;

}
