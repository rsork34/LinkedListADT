#include "LinkedListAPI.h"

List *initializeList(
    void (*printFunction)(void *toBePrinted),
    void (*deleteFunction)(void *toBeDeleted),
    int (*compareFunction)(const void *first,const void *second))
{
  // Make and allocate memory for list pointer
  List * listPtr;
  listPtr = malloc(sizeof(List));

  // Set head and tail to NULL
  listPtr->head = NULL;
  listPtr->tail = NULL;

  // Set delete, print, compare to function pointers passed in
  listPtr->printData = printFunction;
  listPtr->deleteData = deleteFunction;
  listPtr->compare = compareFunction;

  return listPtr;
}

Node *initializeNode(void *data)
{
  // Create and allocate memory for a Node pointer
  Node * nodePtr = malloc(sizeof(Node));

  // Set data to parameter, next and previous to NULL
  nodePtr->data = data;
  nodePtr->next = NULL;
  nodePtr->previous = NULL;

  return nodePtr;
}

void insertFront(List *list, void *toBeAdded)
{
  // List is NULL, return
  if (list == NULL)
  {
    printf("Error: List is null\n");
    return;
  }

  // List is empty, set toBeAdded to head
  if (list->head == NULL)
  {
    list->head = (Node*)toBeAdded;
    list->tail = (Node*)toBeAdded;
    return;
  }

  // Add new Node to front of list
  Node * newHead = (Node*)toBeAdded;
  newHead->next = list->head;
  list->head->previous = newHead;
  list->head = newHead;
}

void insertBack(List *list, void *toBeAdded)
{
  // The list is NULL, return
  if (list == NULL)
  {
    return;
  }

  // The list is empty, set toBeAdded to the head
  if (list->head == NULL)
  {
    insertFront(list, toBeAdded);
    return;
  }

  // Insert Node at end of List
  // Create temp Node and traverse list to last Node
  Node * curNode = list->head;
  while (curNode->next != NULL)
  {
    curNode = curNode->next;
  }

  // Create new node and insert at end
  Node * newTail = (Node*)toBeAdded;
  curNode->next = newTail;
  newTail->previous = curNode;
  list->tail = newTail;
}

void deleteList(List *list)
{
  // List is null, return
  if (!list)
  {
    printf("List is empty\n");
    return;
  }

  // Free and delete every node then free the list
  Node * temp;
  while (list->head)
  {
    temp = list->head;
    list->head = list->head->next;

    temp->next = NULL;
    temp->previous = NULL;
    free(temp);
  }
  free(list);
}

void insertSorted(List *list, void *toBeAdded)
{
  // List or data are NULL, return
  if (list == NULL || toBeAdded == NULL)
  {
    return;
  }

  // List is empty, insert node at head
  // toBeAdded is greater than head, insert as new head
  if (list->head == NULL || list->compare((void*)list->head, toBeAdded) < 0)
  {
    insertFront(list, toBeAdded);
    return;
  }
  // Only one node in list, insert at end of list
  else if (list->head->next == NULL)
  {
    insertBack(list, toBeAdded);
    return;
  }

  Node * curNode = list->head;
  // Loop while curNode > toBeAdded to find correct spot
  while (list->compare((void*)curNode->next, toBeAdded) > 0)
  {
    curNode = curNode->next;
    if (curNode->next == NULL)
    {
      insertBack(list, toBeAdded);
      return;
    }
  }

  // Cast toBeAdded to a Node* and add to list
  Node * newNode = (Node*)toBeAdded;
  newNode->next = curNode->next;
  newNode->previous = curNode;
  newNode->next->previous = newNode;
  curNode->next = newNode;
  return;
}

int deleteDataFromList(List *list, void *toBeDeleted)
{
  if (list == NULL || list->head == NULL)
  {
    return EXIT_FAILURE;
  }

  Node * temp = list->head;
  while (temp)
  {
    // Node to be deleted is found
    if (list->compare((void*)temp, toBeDeleted) == 0)
    {
      // If the Node to be deleted is the head of the list
      if (temp == list->head)
      {
        list->head = temp->next;

        // If the head is not NULL set previous to NULL
        if (list->head)
        {
          list->head->previous = NULL;
        }
      }
      // Node to be deleted is the tail of the list
      else if (temp == list->tail)
      {
        if (temp->previous)
        {
          temp->previous->next = NULL;
        }
      }
      // Node to be deleted is in the middle
      else
      {
        temp->previous->next = temp->next;
        temp->next->previous = temp->previous;
      }
      // Delete and free the Node
      temp->next = NULL;
      temp->previous = NULL;
      free(temp);

      return EXIT_SUCCESS;
    }

    temp = temp->next;
  }

  // Node was not found, return -1
  return -1;
}

void *getFromFront(List *list)
{
  if (list == NULL || list->head == NULL)
  {
    return NULL;
  }

  return list->head;
}

void *getFromBack(List *list)
{
  if (list == NULL || list->head == NULL)
  {
    return NULL;
  }

  return list->tail;
}

void printForward(List *list)
{
  if (list == NULL)
  {
    printf("Error: list is null\n");
    return;
  }

  Node * curNode = list->head;
  while (curNode)
  {
    list->printData(curNode);
    curNode = curNode->next;
  }
}

void printBackwards(List *list)
{
  if (list == NULL)
  {
    printf("Error: list is null\n");
    return;
  }

  Node * curNode = list->tail;
  while (curNode)
  {
    list->printData(curNode);
    curNode = curNode->previous;
  }
}
