#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char **argv){
  FILE *resultBin;
  resultBin = fopen (argv[1],"rb");
  if(resultBin==NULL){
    printf("resultBin file not found\n");
    exit(1);
  }
  int number;
  int16_t indexNumber;
  uint8_t number2;
  uint8_t number3;
  unsigned char number4;
  fread(&number,sizeof(int),1,resultBin);
  printf("%d\n",number);
  for(int i=0;i<number;i++){
    fread(&indexNumber,sizeof(int16_t),1,resultBin);
    fread(&number2,sizeof(uint8_t),1,resultBin);
    fread(&number3,sizeof(uint8_t),1,resultBin);
    printf("text %d index %d : %d,%d\n",i,indexNumber,number2,number3);
    for(int j=0;j<number2;j++){
      fread(&number4,1,1,resultBin);
      printf("%d\n",(int)number4);
    }
    if(number3>0){
      fread(&number4,1,1,resultBin);
      printf("%d\n",(int)number4);
    }
  }
  fclose(resultBin);
  return 0;
}
