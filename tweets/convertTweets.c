#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "queue.h"

double uniform(double min,double max){
  double number;
  double randomize = ((double)rand()/(double)RAND_MAX);
  number = min + randomize * (max - min);
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

int fillAsTable(unsigned char *text,float* Ascii){
    for(int i=0;i<256;i++){
      Ascii[i] = 0.0;
    }
    int k;
    float total = 0;
    unsigned char temp = '0';
    unsigned char end = '\n';
    k = 0;
    while(!(temp==end)){
      Ascii[(int)text[k]] += 1.0;
      k++;
      total++;
      temp = text[k];
    }
    for(int j=0;j<256;j++){
      Ascii[j] = Ascii[j] / total;
    }
    return total;
}

int main(int argc, char **argv){

  /*
  insert(0.2);
  printf("%f\n",peek());
  insert(0.34);
  removeData();
  insert(0.0001);
  printf("%f\n",peek());
  insert(0.0000002);
  insert(0.0000001);
  */

  FILE *fp;
  FILE *used;
  unsigned char buff[500];
  //unsigned char *ptr;
  fp = fopen(argv[1], "r");//finalTweets.txt
  fgets((char*)buff, 500, (FILE*)fp);
  printf("%s\n", buff );
  int nTweets = atoi((char*)buff);
  srand(getNumber(argv[3]));
  printf("Total Tweets: %d\n",nTweets);
  FILE *f = fopen(argv[4], "w"); //Data used for training
  FILE *g = fopen(argv[5], "w"); //Data used for testing
  int i;
  float asc[256];
  int total;
  char temp[100];
  int cant;
  for(i=0;i<256;i++){
    asc[i]=0.0;
  }
  cant=getNumber(argv[2]); //If cant is 0, all tables will be in testing file.

  //Selection of numbers
  int selection[cant];
  for(i=0;i<cant;i++){
    selection[i] = (int)(uniform(0,nTweets) + 0.5);
  }
  qsort(selection, sizeof(selection)/sizeof(*selection), sizeof(*selection), compare_function);
  int repeats=0;
  int currentNumber=-1;
  for (i=0;i<cant;i++){
    if (selection[i]==currentNumber){
      repeats++;
      currentNumber=selection[i];
    }
    else{
       currentNumber=selection[i];
       insert(currentNumber);}

  }

  //Writing files headers
  sprintf(temp,"%d ",size());
  fputs(temp,f);
  sprintf(temp,"%d ",nTweets-size());
  fputs(temp,g);
  fputs("\n",f);
  fputs("\n",g);

  //Writing tables to files
  int position;
  int fileUsed = 0;
  for(i=0;i<nTweets;i++){
    fgets((char*)buff, 500, (FILE*)fp);
    total = fillAsTable(buff,asc);
    if(size()>0){position=peek();}
    else{ position = -1;}
    //printf("Texto:%s - Largo %d\n",buff,total);
    used=g;
    fileUsed=1;

    if(i==position){
      used=f;
      fileUsed=0;
      removeData();
    }
    for(int j=0;j<256;j++){
      gcvt(asc[j],6,temp);
      fputs(temp,used);
      if((j+1)<256){
        fputs(" ",used);
      }
      else{
        if (fileUsed==0){if(size()>0) {fputs("\n",f);}}
        else{if((i+1)<nTweets-size()){fputs("\n",g);}}
      }
    }
    //printf(" That's it!\n");
  }
  fclose(fp);
  fclose(f);
  fclose(g);
  return 0;
}
