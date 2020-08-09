#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

struct node
{
  int data;
  struct node *next;
};

static struct node *insertFirstNode();
static struct node *updateNode(struct node *arg, int data);
static int printList(struct node *arg);
static int freeNode(struct node *arg);
static int getListSize(struct node *arg, bool forceCount);

struct node *current = NULL;
struct node *head = NULL;
struct node *tail = NULL;

static int listSize = 0;

int sizeOfNode = sizeof(struct node);

int main()

{
  int memArray[] = {1,2,3,4,5,6,7,8,9};
  int sizeOfMemArray = sizeof(memArray);
  int i;

  current = insertFirstNode();
  head = current;
  
  for (i = 0; i < sizeOfMemArray/sizeof(int); ++i)
  {
    current = updateNode(current, memArray[i]);
  }

  getListSize(head, false);

  printList(head);
  getListSize(head, true);
  freeNode(head);
  printList(head);
  
  /* free the list */
  int size = getListSize(head, true);
  for (i = 0; i <= size; i++)
  {
    freeNode(head);
  }
  printList(head);

  return 0;

}


static struct node *insertFirstNode()
{
  struct node *first;

  /* Allocate the first node */
  first = malloc(sizeOfNode);
  printf("first sizeof node: %d - first: %d \n", sizeOfNode, (int)first);
  if (first == NULL) 
    {
      printf("%s\n", "Malloc failed");
      return NULL;
    }

  return first;
}

/**
 * @brief      
 * Adding a node should:
 * Malloc the next structure
 * update the pointer of the current structure.
 * return the pointer to the next structure/.
 * 
 * 
 */
static struct node *updateNode(struct node *arg, int data)
{
  struct node *temp;

  temp = (struct node *)malloc(sizeOfNode);
  printf("temp: %d \n", (int)temp);
  if (temp == NULL) printf("%s\n", "Malloc failed");

  /* update data of the current node */
  arg->data = data;
  arg->next = temp;

  listSize++;

  // update tail with latest node
  tail = temp;

  return temp;
}

static int printList(struct node * arg)
{

  printf("printList data: %d, next %d\n", arg->data, (int)arg->next);
  if (arg == NULL)
  {
    printf(" printList: arg is NULL\n");
    return -1;
  }

  struct node * temp = arg;

  while(temp->next != NULL)
  {
    printf("%d,", temp->data);
    temp = temp->next;
  }
  printf("\n");
  return 0;
}

static int freeNode(struct node *arg)
{
  struct node *previous;

  printf("freeNode arg %d data %d next %d\n", (int)arg, arg->data, (int)arg->next);
  /* Check input */
  if(arg == NULL) return -1;
  
  if(arg->next == NULL)
  {
    printf("Whiskey Tango foxtrot\n");
    // free the firs and last node of the list
    free(arg);
    return 0;
  } 

  /* Walk the list */
  while(arg->next != NULL)
  {
    previous = arg; 
    arg = arg->next;
  }
  /* update pointer of the previous node */
  previous->next = NULL;
  /* We reach the end of the list --> free the last node */
  free(arg);
  /* update list's size */
  listSize--;

  return 0;
}

static int getListSize(struct node *arg, bool forceCount)
{
  int calculatedSize = 0;

  if(arg == NULL) return -1;

  if(forceCount)
  {
    while(arg->next != NULL)
    {
      arg = arg->next;
      printf("getListSize: Counting arg: %d\n", (int)arg);
      calculatedSize++;
    }
  }
  else
  {
    printf("getListSize: list counter %d\n", listSize);
    return   listSize;
  }

  printf("getListSize: list count %d \n", calculatedSize);

  return calculatedSize;

}


