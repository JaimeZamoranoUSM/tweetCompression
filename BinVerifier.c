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
  int tweetCount;
  uint16_t indexNumber;
  uint16_t codeSize;
  uint8_t remaining;
  unsigned char buffer;
  fread(&tweetCount,sizeof(int),1,resultBin);
  printf("%d\n",tweetCount);
  for(int i=0;i<tweetCount;i++){
    fread(&indexNumber,sizeof(int16_t),1,resultBin);
    fread(&codeSize,sizeof(uint16_t),1,resultBin);
    //fread(&number3,sizeof(uint8_t),1,resultBin);
    remaining=codeSize%8;
    printf("text %d index %d : %d,%d\n",i,indexNumber,codeSize,remaining);
    for(int j=0;j<(codeSize/8);j++){
      fread(&buffer,1,1,resultBin);
      printf("%d\n",(int)buffer);
    }
    if(remaining>0){
      fread(&buffer,1,1,resultBin);
      printf("%d\n",(int)buffer);
    }
  }
  fclose(resultBin);
  return 0;
}
