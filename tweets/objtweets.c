
#include "../../obj.h"

#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct sTweetDB
   { float *nums;  /* coords all together */
     int nnums;	  /* number of vectors (with space for one more) */
   } TweetDB;

static int never = 1;
static TweetDB DB;

#define db(p) (DB.nums + 256*(int)p)

static float dKL(float *p1,float *p2){
    float result=0.0;
    for(int i=0;i<256;i++){
      if((p1[i]==0.0)|(p2[i]==0.0)){
        result+=0.0;
      }
      else{
        result += p1[i] * log2((p1[i]/p2[i]));
      }
    }
    return result;
}

static float dJS(float *p1,float *p2){
    float M[256];
    for(int i=0;i<256;i++){
      M[i] = (p1[i]+p2[i])/2.0;
    }
    float d1M = dKL(p1,M);
    float d2M = dKL(p2,M);
    float result = (d1M +d2M)/2;
    printf("%f\n",result);
    return result;
}

float distanceInter (Obj o1, Obj o2)

   { return dJS (db(o1),db(o2));
   }

Obj parseobj (char *p)

   { float *d = db(NewObj);
     int i,step;
     for (i=0;i<256-1;i++)
	{ sscanf (p,"%f,%n",d+i,&step);
	  p += step;
	}
     sscanf (p,"%f",d+i);
     return NewObj;
   }

void printobj (Obj obj)

   { int i;
     float *p = db(obj);
     for (i=0;i<256-1;i++) printf ("%f,",p[i]);
     printf ("%f\n",p[i]);
   }

int openDB (char *name)

   { FILE *f;
     struct stat sdata;
     int func;

     closeDB ();
     f = fopen (name,"r");
     stat (name,&sdata);
     DB.nnums = (sdata.st_size)/sizeof(float)/256;
     //fscanf (f,"%i\n",&DB.nnums);
     //char buff[50];
     //fgets(buff, 50,f);
     //DB.nnums = atoi((char*)buff);
     printf("%d\n",DB.nnums);
     DB.nums = malloc ((DB.nnums+1) * sizeof(float) * 256);
     //fread (DB.nums + 256, DB.nnums * sizeof(float) * 256,1,f);
     for (int i=0;i<DB.nnums;i++){
 	      for (int j=0;j<256;j++)
 	        { fscanf(f,"%f",&DB.nums[j+i*256]);
 	        }
        }
      for (int i=0;i<DB.nnums;i++){
    	        printobj(i);
              printf("\n");
           }
     fclose (f);
     return DB.nnums;
   }

void closeDB (void)

   { if (never) { DB.nums = NULL; never=0;}
     if (DB.nums == NULL) return;
     free (DB.nums);
     DB.nums = NULL;
   }
