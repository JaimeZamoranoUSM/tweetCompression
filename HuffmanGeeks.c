// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>


// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100
static float startSize;
static float finalSize;

void outputBits(char* bits,int len,FILE* file) {
  unsigned char buffer = 0;
  unsigned count = 0;
  while(count<len){
    buffer <<= 1;         // Make room for next bit.
    if ((int)(bits[count]-'0')) buffer |= 1; // Set if necessary.
    count++;              // Remember we have added a bit.
    if (count%8 == 0) {
      fwrite(&buffer, sizeof(buffer), 1, file); // Error handling elided.
      buffer = 0;
      //count = 0;
    }
  }
  if (count%8>0){
    buffer<<=(8-(count%8));
    fwrite(&buffer, sizeof(buffer), 1, file);
  }
}


//Function that fills a ascii table with relative Frequency
int fillAsTable(unsigned char *text,double* Ascii){
    for(int i=0;i<256;i++){
      Ascii[i] = 0.0;
    }
    int k;
    double total = 0;
    unsigned char temp = '0';
    unsigned char end = '\n';
    k = 0;
    while(!(temp==end)){
      Ascii[(int)text[k]] += 1.0;
      startSize+=sizeof(char);
      k++;
      total++;
      temp = text[k];
    }
    for(int j=0;j<256;j++){
      Ascii[j] = Ascii[j] / total;
    }
    return total;
}

//distance functions
static double dKL(double *p1,double *p2){
    double result=0.0;
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

static double dJS(double *p1,double *p2){
    double M[256];
    for(int i=0;i<256;i++){
      M[i] = (p1[i]+p2[i])/2.0;
    }
    double d1M = dKL(p1,M);
    double d2M = dKL(p2,M);
    double result = (d1M +d2M)/2;
    return result;
}



// A Huffman tree node
struct MinHeapNode {

	// One of the input characters
	char data;

	// Frequency of the character
	unsigned freq;

	// Left and right child of this node
	struct MinHeapNode *left, *right;
};

// A Min Heap: Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap {

	// Current size of min heap
	unsigned size;

	// capacity of min heap
	unsigned capacity;

	// Array of minheap node pointers
	struct MinHeapNode** array;
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq)
{
	struct MinHeapNode* temp
		= (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode));

	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;

	return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)

{

	struct MinHeap* minHeap
		= (struct MinHeap*)malloc(sizeof(struct MinHeap));

	// current size is 0
	minHeap->size = 0;

	minHeap->capacity = capacity;

	minHeap->array
		= (struct MinHeapNode**)malloc(minHeap->
capacity * sizeof(struct MinHeapNode*));
	return minHeap;
}

// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a,
					struct MinHeapNode** b)

{

	struct MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)

{

	int smallest = idx;
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->
freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->
freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx) {
		swapMinHeapNode(&minHeap->array[smallest],
						&minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{

	return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0]
		= minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap,
				struct MinHeapNode* minHeapNode)

{

	++minHeap->size;
	int i = minHeap->size - 1;

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}

	minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap)

{

	int n = minHeap->size - 1;
	int i;

	for (i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%d", arr[i]);

	printf("\n");
}

// Utility to convert code to String
void convertArr(int arr[], int n, char* buffer)
{
	int a = 0;
	for (int i = 0; i < n; i++) {
        a += sprintf (&buffer[a], "%d", arr[i]);
    }

}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)

{

	return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)

{

	struct MinHeap* minHeap = createMinHeap(size);

	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)

{
	struct MinHeapNode *left, *right, *top;

	// Step 1: Create a min heap of capacity
	// equal to size. Initially, there are
	// modes equal to size.
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

	// Iterate while size of heap doesn't become 1
	while (!isSizeOne(minHeap)) {

		// Step 2: Extract the two minimum
		// freq items from min heap
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		// Step 3: Create a new internal
		// node with frequency equal to the
		// sum of the two nodes frequencies.
		// Make the two extracted node as
		// left and right children of this new node.
		// Add this node to the min heap
		// '$' is a special value for internal nodes, not used
		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}

	// Step 4: The remaining node is the
	// root node and the tree is complete.
	return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct MinHeapNode* root, int arr[], int top)

{

	// Assign 0 to left edge and recur
	if (root->left) {

		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}

	// Assign 1 to right edge and recur
	if (root->right) {

		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}

	// If this is a leaf node, then
	// it contains one of the input
	// characters, print the character
	// and its code from arr[]
	if (isLeaf(root)) {

		printf("%c: ", root->data);
		printArr(arr, top);
	}
}

//SearchFunction
void searchCodes(struct MinHeapNode* root, int arr[], int top, char searchCaracter,char* buffer)

{
	// Assign 0 to left edge and recur
	if (root->left) {

		arr[top] = 0;
		searchCodes(root->left, arr, top + 1, searchCaracter,buffer);
	}

	// Assign 1 to right edge and recur
	if (root->right) {

		arr[top] = 1;
		searchCodes(root->right, arr, top + 1, searchCaracter,buffer);
	}

	// If this is a leaf node, then
	// it contains one of the input
	// characters, print the character
	// and its code from arr[]
	if (isLeaf(root)) {
		if(searchCaracter==root->data){
			convertArr(arr, top,buffer);
		}
	}
}


// The main function that builds a
// Huffman Tree and print codes by traversing
// the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size, unsigned char* text, FILE* resultBin)

{
	// Construct Huffman Tree
	struct MinHeapNode* root
		= buildHuffmanTree(data, freq, size);

	// Print Huffman codes using
	// the Huffman tree built above
	int arr[MAX_TREE_HT], top = 0;
	char buff[500];

	unsigned char temp = '0';
	unsigned char end = '\n';
	int k = 0;
  int i;
  int tamano = 0;
  int buffSize;
  char finalBits[2047];
	while(!(temp==end)){
		searchCodes(root, arr, top, text[k], buff);
		//printf("%c: %s\n",text[k],buff);
    buffSize=strlen(buff);
    for(i=0;i<buffSize;i++){
      finalBits[i+tamano]=buff[i];
    }
    tamano+=buffSize;
    finalSize+=1;
		k++;
		temp = text[k];
	}
  finalBits[tamano]=0;
  //printf("cadena:%s\n",finalBits);

  uint16_t byteSize=tamano;
  //uint8_t byteOffset=tamano%8;
  fwrite(&byteSize,sizeof(uint16_t),1,resultBin);
  //fwrite(&byteOffset,sizeof(int8_t),1,resultBin);
  outputBits(finalBits,tamano,resultBin);
	printCodes(root, arr, top);
}

// Driver program to test above functions
int main(int argc, char **argv)
{
	//Initialization files
	FILE *tweets;
  FILE *resultBin;
  resultBin = fopen (argv[3],"wb");
	FILE *centroids;
  tweets = fopen (argv[1],"r");
  if(tweets==NULL){
    printf("tweets file not found\n");
    exit(1);
  }

	char buffer[300];
	fgets((char*)buffer, 300, (FILE*)tweets);
  int tweetCount = atoi((char*)buffer);

	//inizialization variables
	int i,j,k,total;
	char buff[500];
	char temp[100];
	unsigned char buff2[500];
	double bestTable[256];
  double currentTable[256];
	double currentDist;
  double bestDist;
	int centroidsCount;
	double asc[256];
  int limiter = atoi(argv[4]);
  if(limiter==0) limiter=tweetCount;
	char *arr;
	int *freq;
	int numActives;
	int integerInitTable[256];
	int integerBestTable[256];
	uint16_t bestIndex=0;
	int tempActive;
	int size;

  centroids = fopen (argv[2],"r");
  if(centroids==NULL){
    printf("centroids file not found\n");
    return 1;
  }

  fgets((char*)buff, 500, (FILE*)centroids);
  centroidsCount = atoi((char*)buff);

  double* tables = (double*) malloc(sizeof(double)*centroidsCount*256);

  for(i=0;i<centroidsCount;i++){
    for(j=0;j<256;j++){
      fscanf(centroids,"%lf",&tables[i*256+j]);
    }
  }
  fclose(centroids);

	//writing header
  fwrite(&limiter,sizeof(limiter),1,resultBin);

	//loop for all texts in file
	for(i=0;i<limiter;i++){

		fgets((char*)buff2, 500, (FILE*)tweets);
    total = fillAsTable(buff2,asc);

		bestDist=2.0;
		printf("Starting distance: %lf\n",bestDist);
    for (j=0;j<centroidsCount;j++){
      for (k=0;k<256;k++){
          currentTable[k]=tables[j*256+k];
        }
      currentDist = dJS(asc,currentTable);
      if(currentDist<bestDist){
        printf("New best dist %lf at index %d\n",currentDist,j+1);
				bestIndex=j;
        bestDist=currentDist;
        for(k=0;k<256;k++){
          bestTable[k]=currentTable[k];
        }
      }
    }
    printf("distance to original: %lf\n",bestDist);


    finalSize+=sizeof(int16_t);
    fwrite(&bestIndex,sizeof(bestIndex),1,resultBin);


		for(j=0;j<256;j++){
			integerInitTable[j] = (int)(round(asc[j]*total));
			integerBestTable[j] = (int)(round(bestTable[j]*total));
		}

		numActives=0;
		/*for(j=0;j<256;j++){
			if(integerBestTable[j]>0) numActives++;
			else if(integerInitTable[j]>0) numActives++;
		}
    */

    for(j=0;j<256;j++){
			numActives++;
		}



		arr = (char *) malloc(numActives*sizeof(char));
		freq = (int *) malloc(numActives*sizeof(int));

		tempActive=0;
		/*for(j=0;j<256;j++){
			if(integerBestTable[j]>0){
				*(arr+tempActive) = (char)j;
				*(freq+tempActive) = integerBestTable[j];
				tempActive++;
			}
			else if(integerInitTable[j]>0){
				*(arr+tempActive) = (char)j;
				*(freq+tempActive) = integerBestTable[j];
				tempActive++;
			}
		}
    */
    for(j=0;j<256;j++){
			*(arr+tempActive) = (char)j;
			*(freq+tempActive) = integerBestTable[j]+1;
			tempActive++;
		}


		for(j=0;j<numActives;j++){
			printf("%d: %c ",j,arr[j]);
			printf("%d\n",freq[j]);
		}


		//size = sizeof(arr) / sizeof(arr[0]);
		size = numActives;
		//printf("size:%d\n",size);
		HuffmanCodes(arr, freq, size, buff2, resultBin);

		free(arr);
		free(freq);

	}

  free(tables);
	fclose(tweets);
  fclose(resultBin);
	return 0;
}
