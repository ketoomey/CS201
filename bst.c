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

  void *left;
  void *right;
  void *parent;
};

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
  //  int debug;
    swapper swap_funct;
    comparator comp;
  //  display_f display_funct;
  //  free_f free_funct;
};

extern BST *newBST()//int (*c)(void *,void *))
{
    BST *tree = malloc(sizeof(BST));
    assert(tree != 0);
    tree->size = 0;
  //  tree->comp = c;
    tree->root = NULL;
  //  t->debug = 0;

    //t->swap_funct = NULL;
    //setBSTswapper(tree, initSwapper);
  //  tree->free_funct = NULL;
  //  tree->display_funct = NULL;

    return tree;
}

/*
//[OK]
extern void setBSTswapper(BST *t,void (*s)(SNODE *,SNODE *))
{
    tree->swap_funct = s;
}
*/
extern SNODE *getBSTroot(BST *tree)
{
    return tree->root;
}


extern void setBSTroot(BST *tree,SNODE *replacement) {
  fprintf(stdout, "setting root\n");
    tree->root = replacement;
    if (replacement != NULL)
    {
        replacement->parent = replacement->parent;
    }
}

extern void setBSTsize(BST *tree,int s)
{
    tree->size = s;
}

extern SNODE *insertBST(BST *tree,SNODE *value)
{
  fprintf(stdout, "intro\n");
  /*
    SNODE *n = locateBST(tree, value);

    if (n != NULL)
    {
      fprintf(stdout, "break return\n");
      return n;
    }
    */
    SNODE *n; //n = newSNODE(value, NULL, NULL, NULL);
    n = value;
    fprintf(stdout, "help\n");
    assert(n != 0);

    // Set all nodes = the display and free functions?
    //setSNODEdisplay(n, t->display_funct);
    //setSNODEfree(n, t->free_funct);

    if (tree->size == 0)
    {
        //fprintf(stdout, "hi please work\n");
        setBSTroot(tree, n);
        //setBSTsize(tree, tree->size + 1);

    }
    else
    {
      fprintf(stdout, "oh hey there please work\n");
        SNODE *head, *tmp;
        int cmp, lvl = 0;
        head = getBSTroot(tree);

        //fprintf(stdout, "head:: %p\n", head);
        //fprintf(stdout, "val:: %p\n", n);

        //fprintf(stdout, "headp:: %p\n", head->primaryTitle);
        //fprintf(stdout, "valp:: %p\n", n->primaryTitle);
        while (head != NULL)
        {
            lvl++;
            cmp = strcmp(head->primaryTitle, n->primaryTitle);
            //fprintf(stdout, "inserte_cmp:: %d\n", cmp);
            if (cmp > 0)
            {
                tmp = head->left;
                if (tmp == NULL)
                {
                  fprintf(stdout, "set left \n");
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
                  fprintf(stdout, "set right \n");
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
    fprintf(stdout, "successful INSERT\n");
    setBSTsize(tree, tree->size + 1);
    return n;
}

extern void  *findBST(BST *tree,SNODE *key)
{
    SNODE *head, *tmp;
    int cmp;
    head = getBSTroot(tree);
    while (head != NULL)
    {
        cmp = strcmp(head->primaryTitle, key->primaryTitle);
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

extern SNODE *locateBST(BST *tree,SNODE *key) {

    SNODE *head, *tmp;
    int cmp;
    head = getBSTroot(tree);
    //fprintf(stdout, "KEY:: %p\n", key->primaryTitle);
    //fprintf(stdout, "key:: %p\n", key);

    while (head != NULL)
    {
      //fprintf(stdout, "HEADD:: %p\n", head->primaryTitle);
      //fprintf(stdout, "head:: %p\n", head);
        cmp = strcmp(head->primaryTitle, key->primaryTitle);//make lower for comparisons
        //fprintf(stdout, "Locate cmp:: %d\n", cmp);
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

extern int deleteBST(BST *tree,void *key)
{
    SNODE *tmp = locateBST(tree, key);
    if (tmp == NULL) {
        printf("cannot find\n"); return -1;}

    tmp = swapToLeafBST(tree, tmp);
    pruneLeafBST(tree, tmp);

    setBSTsize(tree, tree->size - 1);

    return 0;
}

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

extern int sizeBST(BST *tree)
{
    return tree->size;
}

char *lowercase(char *word)
{
  char *str = malloc(4000);
  for(int i = 0; word[i]; i++)
  {
    str[i] = tolower(word[i]);
  }
  return str;
}

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
          duplicate->primaryTitle = head->primaryTitle;
          duplicate->genres = head->genres;
          duplicate->startYr = head->startYr;
          duplicate->runtimeMin = head->runtimeMin;
          duplicate->type = head->type;
          duplicate->dateAdded= head->dateAdded;
          duplicate->mediaType= head->mediaType;
          insertBST(tiny, duplicate);
          fprintf(stdout, "word we found a substring\n");
        }
        cmp = strcmp(head->primaryTitle, key->primaryTitle);
        if (cmp > 0)
        {
            tmp = head->left;
            if (tmp == NULL)
            {
              return NULL;
            }
            head = tmp;
        }
        else
        {
            tmp = head->right;
            if (tmp == NULL)
            {
              return NULL;
            }
            head = tmp;
        }
    }
    return NULL;
}
