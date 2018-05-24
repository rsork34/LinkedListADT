#include "LinkedListAPI.h"

void printNode(void * data);
int compareNodes(const void * first, const void * second);
void deleteNode(void* data);

int main()
{
  void (*printFunction)(void * data) = &printNode;
  void (*deleteFunction)(void *toBeDeleted) = &deleteNode;
  int (*compareFunction)(const void *first,const void *second) = &compareNodes;

  int num1 = 1;
  int num2 = 2;
  int num3 = 3;
  int num4 = 4;
  void * testNum1 = &num1;
  void * testNum2 = &num2;
  void * testNum3 = &num3;
  void * testNum4 = &num4;

  // Initialize the list and some Nodes
  List * testList = initializeList(printFunction, deleteFunction, compareFunction);
  Node * testNode1 = initializeNode(testNum1);
  Node * testNode2 = initializeNode(testNum2);
  Node * testNode3 = initializeNode(testNum3);
  Node * testNode4 = initializeNode(testNum4);

  insertSorted(testList, (void*)testNode3);
  insertSorted(testList, (void*)testNode1);
  insertSorted(testList, (void*)testNode2);
  insertSorted(testList, (void*)testNode4);

  printForward(testList);
  deleteList(testList);

  return 0;
}

void printNode(void * data)
{
  Node * toBePrinted = (Node*)data;
  printf("Data is: %d\n", *( (int*) toBePrinted->data) );
}

int compareNodes(const void * first, const void * second)
{
  Node * node1 = (Node*)first;
  Node * node2 = (Node*)second;

  int num1 = *((int*)node1->data);
  int num2 = *((int*)node2->data);

  if (num1 == num2)
  {
    return 0;
  }
  else if (num1 < num2)
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

void deleteNode(void* data)
{
  if (!data)
  {
    return;
  }

  // Delete and free node
  Node * temp = (Node*)data;
  temp->next = NULL;
  temp->previous = NULL;
  temp->data = NULL;
  free(temp);
}
