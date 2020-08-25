//Credits to tutorialspoint for queue code
//For more information:https://www.tutorialspoint.com/data_structures_algorithms/queue_program_in_c.htm
//Visit tutorialspoint.com
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "queue.h"
#define MAX 1000000

int intArray[MAX];
int front = 0;
int rear = -1;
int itemCount = 0;

int peek() {
   return intArray[front];
}

int isEmpty() {
  if(itemCount == 0){return 1;}
  else{return 0;}
}

int isFull() {
   if(itemCount == MAX){return 1;}
   else{return 0;}
}

int size() {
   return itemCount;
}

void insert(int data) {

   if(isFull()==0) {

      if(rear == MAX-1) {
         rear = -1;
      }

      intArray[++rear] = data;
      itemCount++;
   }
}

int removeData() {
   int data = intArray[front++];

   if(front == MAX) {
      front = 0;
   }

   itemCount--;
   return data;
}
