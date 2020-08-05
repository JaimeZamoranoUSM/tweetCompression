#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include <errno.h>
#include <limits.h>

double uniform(double min,double max){
  double number;
  double randomize = ((double)rand()/(double)RAND_MAX);
  number = min + randomize * (max - min);
  return number;
}

double gaussian(double mean, double s){
  double u = ((double)rand()/(double)RAND_MAX);
  double v = ((double)rand()/(double)RAND_MAX);
  if (u==0.0) return mean;
  double x = ( sqrt(-2*log(u)) * cos(2*M_PI*v) );
  double number = s*x + (double)mean;
  return number;
}

double exponential(double min,double max,double lambda){
  double dl = (1.0/(max-min));
  dl = ( (-log(dl)));
  double candidate = uniform(0,1);
  double number;
  if(candidate==0.0){
    number = min + candidate * (max - min);
    return number;
  }
  double a = (-log(candidate)/lambda);
  double v = uniform(0,dl);
  while(v>a){
    candidate = uniform(0,1);
    if(candidate==0.0){
      number = min + candidate * (max - min);
      return number;
    }
    a = (-log(candidate)/lambda);
    v = uniform(0,dl);
  }
  number = min + candidate * (max - min);
  return number;
}

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
  int tipoRand = getNumber(argv[4]);
  double pl;
  if (argc>5){ pl = atof(argv[5]); }
  else{ pl=1; }
  //seleccion de tablas
  switch (tipoRand) {
    case 1:
    for(i=0;i<nTables;i++){
      selection[i] = (int)(uniform(0,total) + 0.5);
    }
    break;
    case 2:
    for(i=0;i<nTables;i++){
      selection[i] = (int)gaussian(500000,100000);
    }
    break;
    case 3:
    for(i=0;i<nTables;i++){
      selection[i] = (int)(exponential(0,total,pl)+0.5);
    }
    break;
    default:
    for(i=0;i<nTables;i++){
      selection[i] = (rand()%total);
    }
    break;
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
  char temp2[100];
  FILE *data = fopen("finalTables.txt", "w");
  sprintf(temp,"%d",finalTally);
  fputs(temp,data); fputs("\n",data);
  int k;
  //opcional, para graficar data en excel
  FILE *graf;
  graf = fopen("points.txt","w");

  for(i=0;i<total;i++){
    for(k=0;k<finalTally;k++){
      if(i==selection[k]){
        if(!(selection[k]==currentNumber)){
          sprintf(temp2,"%d",selection[k]);
          fputs(temp2,graf);
          fputs("\n",graf);
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
  fclose(graf);
  return 0;
}
