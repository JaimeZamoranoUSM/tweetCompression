#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include <errno.h>
#include <limits.h>

int compare_function(const void *a,const void *b) {
int *x = (int *) a;
int *y = (int *) b;
return *x - *y;
}

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
  int nTables = getNumber(argv[2]);
  srand(getNumber(argv[3]));
  int selection[nTables];
  int i = 0;
  //seleccion de tablas
  for(i=0;i<nTables;i++){
    selection[i] = (rand()%total);
  }
  qsort (selection, sizeof(selection)/sizeof(*selection), sizeof(*selection), compare_function);
  int repeats=0;
  int currentNumber=-1;
  for (i=0;i<nTables;i++){
    if (selection[i]==currentNumber){
      repeats++;
    }
    currentNumber=selection[i];
  }
  int finalTally=(nTables-repeats);
  currentNumber=-1;
  int tag=0;
  float value;
  char temp[100];
  FILE *data = fopen("finalTables.txt", "w");
  sprintf(temp,"%d",finalTally);
  fputs(temp,data); fputs("\n",data);
  int k;

  for(i=0;i<total;i++){
    for(k=0;k<finalTally;k++){
      if(i==selection[k]){
        if(!(selection[k]==currentNumber)){
          currentNumber=selection[k];
          tag=1;
          break;
        }
      }
    }
    for(int j=0;j<256;j++){
      fscanf(file,"%f",&value);
      if(tag==1){
        gcvt(value,6,temp);
        fputs(temp,data);
        if((j+1)<256){
          fputs(" ",data);
        }
        else{
          if((k+1)<finalTally){
            fputs("\n",data);
          }
        }
      }
    }
    tag=0;
  }

  fclose(file);
  fclose(data);
  return 0;
}
