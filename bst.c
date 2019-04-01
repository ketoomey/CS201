#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "bst.h"

typedef int (*comparator)(void *,void *);
typedef void (*swapper)(SNODE *,SNODE *);
typedef void (*display_f)(void *, FILE *);
typedef void (*free_f)(void *);

struct satelliteData
{
  char* type; //index 1
  char* primaryTitle; //index 2
  char* startYr; //index 5
  char* runtimeMin; //index 7
  char* genres; //index 8
  char* mediaType; //read in later
  char* dateAdded; //read in later
  char* realTitle;

  void *left;
  void *right;
  void *parent;
};

//changes the string to lowercase
char *lowercase(char *word)
{
  char *str = malloc(4000);
  for(int i = 0; word[i]; i++)
  {
    str[i] = tolower(word[i]);
  }
  return str;
}
//swaps the two nodes
void initSwapper(SNODE *n1,SNODE *n2)
{
    void *x = n1->primaryTitle;
    void *y = n2->primaryTitle;
    n1->primaryTitle = y;
    n2->primaryTitle = x;
}

struct bst
{
    SNODE *root;
    int size;
    swapper swap_funct;
    comparator comp;
};

//creates a new binary search tree
extern BST *newBST()
{
    BST *tree = malloc(sizeof(BST));
    assert(tree != 0);
    tree->size = 0;
    tree->root = NULL;
    return tree;
}

/***************************************************************************************
*    Title: bst.c
*    Author: Matthew Rinne
*    Date Accessed: <03/05/2019>
*    Link: <https://github.com/mdrinne/cs201-assign3/blob/master/bst.c>
*
***************************************************************************************/
//returns the root of the binary search tree
extern SNODE *getBSTroot(BST *tree)
{
    return tree->root;
}

//sets the root of the binary search tree
extern void setBSTroot(BST *tree,SNODE *replacement)
{
//  fprintf(stdout, "setting root\n");
    tree->root = replacement;
    if (replacement != NULL)
    {
        replacement->parent = replacement->parent;
    }
}

/***************************************************************************************
*    Title: bst.c
*    Author: Matthew Rinne
*    Date Accessed: <03/05/2019>
*    Link: <https://github.com/mdrinne/cs201-assign3/blob/master/bst.c>
*
***************************************************************************************/
//sets the size of the binary search tree
extern void setBSTsize(BST *tree,int s)
{
    tree->size = s;
}

//inserts the node into the binary search tree
extern SNODE *insertBST(BST *tree,SNODE *value)
{
    SNODE *n;
    n = value;
    assert(n != 0);

    if (tree->size == 0)
    {
        setBSTroot(tree, n);
    }
    else
    {
        SNODE *head, *tmp;
        int cmp, lvl = 0;
        head = getBSTroot(tree);

        while (head != NULL)
        {
            lvl++;
            if (head->primaryTitle == NULL)
            {
              cmp = 0;
            }
            else
            {
              cmp = strcmp(lowercase(head->primaryTitle), lowercase(n->primaryTitle)); //SEG FAULTING HERE!!!!
            }
            if (cmp > 0)
            {
                tmp = head->left;
                if (tmp == NULL)
                {
                    head->left = n;
                    n->parent = head;
                    break;
                }
                else
                {
                    head = tmp;
                }
            }
            else if (cmp < 0)
            {
                tmp = head->right;
                if (tmp == NULL)
                {
                    head->right = n;
                    n->parent = head;
                    break;
                }
                else
                {
                    head = tmp;
                }
            }
            else
            {
                return head;
                break;
            }
        }
    }
    setBSTsize(tree, tree->size + 1);
    return n;
}

//finds the node in the binary search tree
extern void  *findBST(BST *tree,SNODE *key)
{
    SNODE *head, *tmp;
    int cmp;
    head = getBSTroot(tree);
    while (head != NULL)
    {
        cmp = strcmp(lowercase(head->realTitle), lowercase(key->primaryTitle));
        if (cmp > 0)
        {
            tmp = head->left;
            if (tmp == NULL)
            {
              return NULL;
            }
            head = tmp;
        }
        else if (cmp < 0)
        {
            tmp = head->right;
            if (tmp == NULL)
            {
              return NULL;
            }
            head = tmp;
          }
        else
        {
            return head;
        }
    }
    return NULL;
}

//finds and returns the node if found in the binary search tree
extern SNODE *locateBST(BST *tree,SNODE *key)
{
    SNODE *head, *tmp;
    int cmp;
    head = getBSTroot(tree);

    while (head != NULL)
    {
        cmp = strcmp(lowercase(head->realTitle), lowercase(key->primaryTitle));//make lower for comparisons
        if (cmp > 0)
        {
            tmp = head->left;
            if (tmp == NULL)
            {
              return NULL;
            }
            head = tmp;
        }
        else if (cmp < 0)
        {
            tmp = head->right;
            if (tmp == NULL)
            {
              return NULL;
            }
            head = tmp;
        }
        else
        {
            return head;
        }
    }
    return NULL;
}

/***************************************************************************************
*    Title: bst.c
*    Author: Matthew Rinne
*    Date Accessed: <03/05/2019>
*    Link: <https://github.com/mdrinne/cs201-assign3/blob/master/bst.c>
*
***************************************************************************************/
//delete a node from the binary search tree
extern int deleteBST(BST *tree, SNODE *key)
{
  //  fprintf(stdout, "key:: %s\n", key->realTitle);
    SNODE *tmp = locateBST(tree, key);
  //  fprintf(stdout, "temp:: %s\n", tmp->realTitle);
    while (tmp == NULL)
    {
        printf("I'm sorry, this title does not exist in the log.\n");
        return -1;
    }

    tmp = swapToLeafBST(tree, tmp);
    pruneLeafBST(tree, tmp);

    setBSTsize(tree, tree->size - 1);

    return 0;
}

/***************************************************************************************
*    Title: bst.c
*    Author: Matthew Rinne
*    Date Accessed: <03/05/2019>
*    Link: <https://github.com/mdrinne/cs201-assign3/blob/master/bst.c>
*
***************************************************************************************/
//find the previous node
SNODE *findPredecessor(SNODE *node)
{
    node = node->left;

    if (node == NULL)
    {
      return NULL;
    }
    while (node->right != NULL)
    {
        node = node->right;
    }
    return node;
}

/***************************************************************************************
*    Title: bst.c
*    Author: Matthew Rinne
*    Date Accessed: <03/05/2019>
*    Link: <https://github.com/mdrinne/cs201-assign3/blob/master/bst.c>
*
***************************************************************************************/
//find the next node
SNODE *findSuccessor(SNODE *node)
{
    node = node->right;
    if (node == NULL)
    {
      return NULL;
    }
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

/***************************************************************************************
*    Title: bst.c
*    Author: Matthew Rinne
*    Date Accessed: <03/05/2019>
*    Link: <https://github.com/mdrinne/cs201-assign3/blob/master/bst.c>
*
***************************************************************************************/
//swap the correct leaf to take over its parent in the binary search tree
extern SNODE *swapToLeafBST(BST *tree,SNODE *node)
{
    if ((node->left == NULL) && (node->right == NULL))
    {
      return node;
    }

    SNODE *tmp = findPredecessor(node);
    if (tmp != NULL)
    {
        //t->swap_funct(node, tmp);
        initSwapper(node, tmp);
        //return tmp;
        return swapToLeafBST(tree, tmp);
    }
    tmp = findSuccessor(node);
    if (tmp != NULL)
    {
        //t->swap_funct(node, tmp);
        initSwapper(node, tmp);
        //return tmp;
        return swapToLeafBST(tree, tmp);
    }
    return swapToLeafBST(tree, tmp);
}

/***************************************************************************************
*    Title: bst.c
*    Author: Matthew Rinne
*    Date Accessed: <03/05/2019>
*    Link: <https://github.com/mdrinne/cs201-assign3/blob/master/bst.c>
***************************************************************************************/
//removes the node from the tree
extern void pruneLeafBST(BST *tree,SNODE *leaf)
{
    SNODE *parent = leaf->parent;
    if (leaf == getBSTroot(tree))
    {
        setBSTroot(tree, NULL);
    }
    else {
        if (parent->left == leaf)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }
    }
}

/***************************************************************************************
*    Title: bst.c
*    Author: Matthew Rinne
*    Date Accessed: <03/05/2019>
*    Link: <https://github.com/mdrinne/cs201-assign3/blob/master/bst.c>
*
***************************************************************************************/
//returns the size of the binary search tree
extern int sizeBST(BST *tree)
{
    return tree->size;
}


//build a smaller binary search tree to hold the search values
extern void  *buildTinyBST(BST *tree,SNODE *key, BST *tiny)
{
    SNODE *head, *tmp;
    int cmp;
    head = getBSTroot(tree);
    while (head != NULL)
    {
        if(strstr(lowercase(head->primaryTitle), lowercase(key->primaryTitle)))
        {
          SNODE *duplicate = malloc(sizeof(SNODE));
          duplicate->realTitle = head->realTitle;
          duplicate->primaryTitle = head->primaryTitle;
          duplicate->genres = head->genres;
          duplicate->startYr = head->startYr;
          duplicate->runtimeMin = head->runtimeMin;
          duplicate->type = head->type;
          duplicate->dateAdded= head->dateAdded;
          duplicate->mediaType= head->mediaType;
          duplicate->parent = NULL;
          duplicate->left = NULL;
          duplicate->right = NULL;
          insertBST(tiny, duplicate);
          //fprintf(stdout, "word we found a substring\n");
        }
        cmp = strcmp(lowercase(head->primaryTitle), lowercase(key->primaryTitle));
        if (cmp > 0)
        {
            tmp = head->left;
            if (tmp == NULL)
            {
              return NULL;
            }
            head = tmp;
        }
        else if (cmp < 0)
        {
            tmp = head->right;
            if (tmp == NULL)
            {
              return NULL;
            }
            head = tmp;
        }
        else
        {
            return head;
        }
    }
    return NULL;
}
