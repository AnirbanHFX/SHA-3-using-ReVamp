#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha3.h"

char* stringToBinary(char* s) {
    if(s == NULL) return 0; /* no input string */
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

char *sponge(char *bin, unsigned int b) { 

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

void sha3_keccakf(uint64_t st[25])
{
    // constants
    const uint64_t keccakf_rndc[24] = {
        0x0000000000000001, 0x0000000000008082, 0x800000000000808a,
        0x8000000080008000, 0x000000000000808b, 0x0000000080000001,
        0x8000000080008081, 0x8000000000008009, 0x000000000000008a,
        0x0000000000000088, 0x0000000080008009, 0x000000008000000a,
        0x000000008000808b, 0x800000000000008b, 0x8000000000008089,
        0x8000000000008003, 0x8000000000008002, 0x8000000000000080,
        0x000000000000800a, 0x800000008000000a, 0x8000000080008081,
        0x8000000000008080, 0x0000000080000001, 0x8000000080008008
    };
    const int keccakf_rotc[24] = {
        1,  3,  6,  10, 15, 21, 28, 36, 45, 55, 2,  14,
        27, 41, 56, 8,  25, 43, 62, 18, 39, 61, 20, 44
    };
    const int keccakf_piln[24] = {
        10, 7,  11, 17, 18, 3, 5,  16, 8,  21, 24, 4,
        15, 23, 19, 13, 12, 2, 20, 14, 22, 9,  6,  1
    };

    // variables
    int i, j, r;
    uint64_t t, bc[5];
    uint64_t lt = 0xffffffffffffffff;

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
    uint8_t *v;

    // endianess conversion. this is redundant on little-endian targets
    for (i = 0; i < 25; i++) {
        v = (uint8_t *) &st[i];
        st[i] = ((uint64_t) v[0])     | (((uint64_t) v[1]) << 8) |
            (((uint64_t) v[2]) << 16) | (((uint64_t) v[3]) << 24) |
            (((uint64_t) v[4]) << 32) | (((uint64_t) v[5]) << 40) |
            (((uint64_t) v[6]) << 48) | (((uint64_t) v[7]) << 56);
    }
#endif

    // actual iteration
    for (r = 0; r < 24; r++) {

        // Theta
        for (i = 0; i < 5; i++)
            bc[i] = st[i] ^ st[i + 5] ^ st[i + 10] ^ st[i + 15] ^ st[i + 20];

        for (i = 0; i < 5; i++) {
            t = bc[(i + 4) % 5] ^ ROTL64(bc[(i + 1) % 5], 1);

            for (j = 0; j < 25; j += 5)
                st[j + i] ^= t;
        }

        // Rho Pi
        t = st[1];
        for (i = 0; i < 24; i++) {
            j = keccakf_piln[i];
            bc[0] = st[j];
            st[j] = ROTL64(t, keccakf_rotc[i]);
            t = bc[0];
        }

        //  Chi
        for (j = 0; j < 25; j += 5) {
            for (i = 0; i < 5; i++)
                bc[i] = st[j + i];
            for (i = 0; i < 5; i++)
                st[j + i] ^= (~bc[(i + 1) % 5]) & bc[(i + 2) % 5];
        }

        //  Iota
        st[0] ^= keccakf_rndc[r];

    }

#if __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__
    // endianess conversion. this is redundant on little-endian targets
    for (i = 0; i < 25; i++) {
        v = (uint8_t *) &st[i];
        t = st[i];
        v[0] = t & 0xFF;
        v[1] = (t >> 8) & 0xFF;
        v[2] = (t >> 16) & 0xFF;
        v[3] = (t >> 24) & 0xFF;
        v[4] = (t >> 32) & 0xFF;
        v[5] = (t >> 40) & 0xFF;
        v[6] = (t >> 48) & 0xFF;
        v[7] = (t >> 56) & 0xFF;
    }
#endif
}

int main() {

   char *inp = (char *) malloc(100*sizeof(char));

   printf("Enter message: ");
   scanf("%s", inp);

   unsigned int len = strlen(inp);

   char *out = (char *) malloc((8*strlen(inp)+1)*sizeof(char));

   out = stringToBinary(inp);

   printf("Bin: %s\n\n", out);

   char *sp = sponge(out, 1600);
   uint64_t st[25];
   uint64_t place = (uint64_t) 1;

   for(int i=0; i<25; i++) {

      st[i] = 0;

      for(int j=0; j<64; j++) {

         if(sp[64*i+j] == '1')
            st[i] += (place << j);

      }

   }

   sha3_keccakf(st);

   for (int i=24; i>=0; i--)
      printf("wl %2d: %016lx\n", i, st[i]);

   return 0;

}
