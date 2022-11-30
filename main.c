#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char digits[]="0123456789abcdefghijklmnopqrstuvwxyz";

void parse_input(char *input, int *integral, float *fractional) {
   char *c;
   char frac[128] = "0.";

   *integral = atoi(strtok(input,"."));
   if ((c = strtok(NULL, ".")) != NULL) {
      int i = 2;
      for (; *c; c++,i++)
         frac[i] = *c;
      frac[i] = '\0';
      *fractional = atof(frac);
   }
}

int main(int argc, char *argv[]) {

   int integral = 0;
   int base;
   float fractional = 0.0;
   char *c;

   char answer[128];

   if (argc != 3) {
      fprintf(stderr, "Need one decimal value and desired radix (base) are needed\n");
      fprintf(stderr, "convert 123.425 4");
      exit(0);
   }
   parse_input(argv[1], &integral, &fractional);
   base = atoi(argv[2]);

   /* convert integral part with requested base (radix) */
   int whole = integral;
   unsigned d[128];
   int i = 0;
   int j = 0;
   int k = 0;
   do {
      d[i] = whole % base;
      whole = whole / base; // integer division
      i++;
   } while (whole != 0);

   for (j = i-1, i=0; j >= 0; j--,i++)
      answer[i] = digits[d[j]];
   answer[i] = '.';
   k = ++i;

   /* convert fractional part with requested base (radix) */
   float frac;
   frac = fractional;
   while (frac != 0 && i < 128) {
      frac = frac * base;
      whole = (int) frac;
      frac = frac - whole;
      d[i] = whole;
      i++;
   }

   for (j = k; j < i; j++,k++)
      answer[k] = digits[d[j]];
   answer[k] = '\0';
   printf("answer = %s\n", answer);
   return 0;
}
