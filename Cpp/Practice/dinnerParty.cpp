#include <stdio.h>

int cnt = 0;
int combs = 0;

void comb_rec(char A[], int len, int limit, int i, int takes) {
 cnt++;

 if ((takes + (len - i)) < limit) {
  return;
 }

 if (i == len) {
  if (takes == limit) {
   combs++;
   printf("%s\n", A);
  }

  return;
 }

 char taken = A[i];

 // leave it
 A[i] = '-';

 comb_rec(A, len, limit, i + 1, takes);

 // take it
 A[i] = taken;

 comb_rec(A, len, limit, i + 1, takes + 1);
}

void comb(char A[], int len, int limit) {
 comb_rec(A, len, limit, 0, 0);
}

int main() {
 char A[6] = { '1', '2', '3', '4', '5',0 };
 int limit = 3;

 comb(A, 4, limit);

 printf("Found %d combinations\n", combs);
 printf("Visited %d nodes\n", cnt);

 return 0;
}
