#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  FILE *fp;
  unsigned char buff[500];
  //unsigned char *ptr;
  fp = fopen(argv[1], "r");
  fgets((char*)buff, 500, (FILE*)fp);
  printf("%s\n", buff );
  int nTweets = atoi((char*)buff);
  printf("Total de Tweets: %d\n",nTweets);
  FILE *f = fopen("tables.txt", "w");

  int i;
  float asc[256];
  int total;
  char temp[100];
  int cant;

  for(i=0;i<256;i++){
    asc[i]=0;
  }

  sprintf(temp,"%d ",nTweets);
  fputs(temp,f);
  fputs("\n",f);

  for(i=0;i<nTweets;i++){
    fgets((char*)buff, 500, (FILE*)fp);
    total = fillAsTable(buff,asc);
    printf("Texto:%s - Largo %d\n",buff,total);
    for(int j=0;j<256;j++){
      gcvt(asc[j],6,temp);
      fputs(temp,f);
      if((j+1)<256){
        fputs(" ",f);
      }
      else{
        if((i+1)<nTweets){
          fputs("\n",f);
        }
      }
    }
    //printf(" That's it!\n");
  }

  fclose(fp);
  fclose(f);
  return 0;
}
