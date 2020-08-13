
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/times.h>

// #include "obj.h"
typedef int Obj;
#define NewObj 0

#define faleat (((unsigned)random())/((double)(unsigned)(1<<31)))
#define aleat(n) ((unsigned)((faleat)*(n)))

typedef struct sTweetDB
   { float *nums;  /* coords all together */
     int nnums;	  /* number of vectors (with space for one more) */
   } TweetDB;

static int never = 1;
static TweetDB DB;

#define db(p) (DB.nums + 256*(int)p)

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
    unsigned long dn;

    f = fopen (name,"r");
    stat (name,&sdata);
    DB.nnums = (sdata.st_size)/sizeof(float)/256;
    //char buff[50];
    //fgets(buff, 50,f);
    //DB.nnums = atoi((char*)buff);
    DB.nums = malloc ((DB.nnums+1) * sizeof(float) * 256);
    fread (DB.nums + 256,DB.nnums * sizeof(float) * 256,1,f);
    fclose (f);
    return DB.nnums;
  }

void perturb (int from, float r)

   { int i;
     Obj orig = from+1+aleat(DB.nnums-from);
     memcpy (db(NewObj),db(orig),256 * sizeof(float));
     i = aleat(256);
     if (aleat(2)) db(NewObj)[i] += r; else db(NewObj)[i] -= r;
   }

int main (int argc, char **argv)

  { int n,from,nq;
    float pert;
    char *kk;
    struct timeval t;

    if (argc < 6)
	{ fprintf (stderr,"Usage: genqueries <db file> <from> <nqueries> "
			    "<k> <perturb>\n  See the manual for details.\n");
	  exit(1);
	}
    n = openDB(argv[1]);
    from = atoi(argv[2]);
    nq = atoi(argv[3]);
    kk = argv[4];
    sscanf (argv[5],"%f",&pert);

    gettimeofday (&t,NULL);
    srandom (t.tv_sec*t.tv_usec);

    while (nq--)
      { printf ("%s,",kk);
        perturb(from,pert);
        printobj(NewObj);
      }
    printf("-0\n");
  }
