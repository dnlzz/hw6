/* HW6 read cafefully and follow all the instructions/comments
   this program compiles and runs as is although it's not doing much.
   DO NOT CHANGE THE SEED. Changing seed gives a different sequence of
   numbers but we want the same numbers for comparison purposes.

   FLOATING point radix sort requires some substantial changes to this code
   float n, lst[N],tmp[N];	
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
#define NELM 100		/* default 100 elements */
#define N 15		/* 2^30 or 1 meg elements  */
//#define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
//#define N 33554432

void selection_sort();
void swap();

void merge_sort();
void msort_recursive();

void int_radix_sort();
void float_radix_sort();
void swap();
void self_check();

int rand(void);
void srand();
int rand_r();
void init_lst();
void print_lst();

int n, lst[N],tmp[N];

int main(int argc,char **argv) {

  long int del_sec,del_msec;
  // struct timeval tv_s,tv_e;
  int iii=0, group = 4;

  if (argc>1) n = atoi(argv[1]);
  else n = N;
  printf("n=%d\n",n);
  init_lst(lst,n);
  print_lst(lst,n);

  // gettimeofday(&tv_s, NULL); 
  // selection_sort(lst,n);
  //  merge_sort(lst,tmp,n);

  int *src, * dest;

  src = lst;
  dest = tmp;

  for (iii = 0; iii < 32; iii + group) {
    printf("%d", iii);
    int_radix_sort(lst, tmp, n, iii);
    swap(lst, tmp);
    printf("\n");
  }

  //  float_radix_sort(lst,tmp,n);
  // gettimeofday(&tv_e, NULL); 

  /****
    PRINT elapsed time in sec and milli secs
  ****/

  print_lst(lst,n);
  self_check();
  return 0;
}

void swap(int *src, int *dest) {

  //have src point to dest and have destpoint to ...?
  
  int *tmp;
  tmp = src;
  src = dest;
  dest = tmp;
  
  
}

void selection_sort(int list[],int n){
  // fill here
}

void merge_sort(int list[], int temp[], int n){
  msort_recursive(list, temp, 0, n-1);
}

//use recursion
void msort_recursive(int list[], int temp[], int left, int right){
  // fill here
}

void int_radix_sort(int *lst, int *tmp, int n, int iii) {
    int group = 4;
    // int buckets = 1 << group;
    int buckets = 1 << group;
    int mask = buckets - 1;
    int cnt[buckets], map[buckets];

    //INITIALIZE CNT ARRAY TO ALL ZEROS
    for (int i=0; i < buckets; i++) {
        cnt[i] = 0;
    }

    /* printf("\n%d\n%d\n%d\n", buckets, lst[0] >> 0, ( (lst[0] >> 0 ) & (buckets-1) ) ); */
    /* printf("\n%d\n%d\n%d\n", buckets, lst[0] >> 4, ( (lst[0] >> 4 ) & (buckets-1) ) ); */
    /* printf("\n%d\n%d\n%d\n", buckets, lst[0] >> 2, ( (lst[0] >> 2 ) & (buckets-1) ) ); */
    /* printf("\n%d\n%d\n%d\n", buckets, lst[0] >> 3, ( (lst[0] >> 3  ) & (buckets-1) ) ); */

    //COUNT
    for (int i=0; i < N; i++) {
      cnt[(lst[i] >> iii) & mask]++;
    }


    //MAP
    int j = 0;
    for (int i=0; i < buckets; i++) {
      map[i]=j;
      j=map[i]+cnt[i];
    }


    //MOVE
    for (int i=0; i < N; i++) {
      tmp[map[(lst[i] >> iii) & mask]] = lst[i];
    }

}

//fix the bucket size to 256. run 4 passes where each pass processes 8 bits
//use lst and tmp only. do not use any more memory of size n.
void radix_sort(int ii) {
  int group=8;			/* 8 bits per pass (or round) */
  int bucket = 1 << group;	/* number of buckets = 256 */
  // fill here
}

void print_lst(int *l,int n){
  int i;
  for (i=0; i<n; i++) {
    printf("%d   ",l[i]);
  }
  printf("\n");
}

void init_lst(int *l,int n){
  int i;
  //  int seed = time(0) % 100;	/* seconds since 1/1/1970 */
  //  printf ("seed=%d\n", seed);
  srand(1234);			/* SEED */
  for (i=0; i<n; i++) {
    l[i] = rand();
  }
}

void self_check(int *list,int n) {
  int i,j,flag=OK,*listp;

  listp = list;
  for (i=0;i<n-1;i++)
     if (listp[i] > listp[i+1]) { flag = NOK; break; }

  if (flag == OK) printf("sorted\n");
  else printf("NOT sorted at %d\n",i);
}
