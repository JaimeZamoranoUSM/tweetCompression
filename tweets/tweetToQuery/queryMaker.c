#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

int getNumber(char *arg){
  char *p;
  int num;

  errno = 0;
  long conv = strtol(arg, &p, 10);

  // Check for errors: e.g., the string does not represent an integer
  // or the integer is larger than int
  if (errno != 0 || *p != '\0' || conv > INT_MAX) {
    return(1);
  }
  else {
    num = conv;
    return(num);
  }
}

int main(int argc, char **argv){

  FILE *file;
  file = fopen(argv[1],"r");
  int total;
  fscanf(file,"%i\n",&total);
  int nQueries = getNumber(argv[2]);
  if(nQueries<1){ nQueries = total; }
  FILE *queries;
  queries = fopen("queries.txt","w");

  float value;
  char temp[100];

  for(int i=0;i<nQueries;i++){
    fputs("-1,",queries);
    for(int j=0;j<256;j++){
      fscanf(file,"%f",&value);
      gcvt(value,6,temp);
      fputs(temp,queries);
      if(j+1<256){ fputs(",",queries); }
    }
    fputs("\n",queries);
  }
  fputs("-0",queries);
  fclose(file);
  fclose(queries);
  return 0;
}
