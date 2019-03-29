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

char *lowercase(char *word)
{
  char *str = malloc(4000);
  for(int i = 0; word[i]; i++)
  {
    str[i] = tolower(word[i]);
  }
  return str;
}

/***************************************************************************************
*    Title: bst.c
*    Author: Matthew Rinne
*    Date Accessed: <03/05/2019>
*    Link: <https://github.com/mdrinne/cs201-assign3/blob/master/bst.c>
*
***************************************************************************************/
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
extern SNODE *getBSTroot(BST *tree)
{
    return tree->root;
}


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
extern void setBSTsize(BST *tree,int s)
{
    tree->size = s;
}


extern SNODE *insertBST(BST *tree,SNODE *value)
{
//  fprintf(stdout, "intro\n");

    SNODE *n;
    n = value;
  //  fprintf(stdout, "help\n");
    assert(n != 0);

    if (tree->size == 0)
    {
        setBSTroot(tree, n);
    }
    else
    {
    //  fprintf(stdout, "oh hey there please work\n");
        SNODE *head, *tmp;
        int cmp, lvl = 0;
        head = getBSTroot(tree);

        while (head != NULL)
        {
            /*
            fprintf(stdout, "pre head print -->\n");
            fprintf(stdout, "%s\t", head->primaryTitle);
            fprintf(stdout, "%s\t", head->startYr);
            fprintf(stdout, "%s\t", head->runtimeMin);
            fprintf(stdout, "%s\t", head->genres);
            fprintf(stdout, "%s\t", head->mediaType);
            fprintf(stdout, "%s\t", head->dateAdded);
            fprintf(stdout, "\npost head print -->\n");
            */
            lvl++;
            if (head->primaryTitle == NULL)
            {
              cmp = 0;
            }
            else
            {
              //fprintf(stdout, "~~~~~~~~~~~~~~~~~~~~~~~~\n");
              //fprintf(stdout, "~~~~~~ %s\n", n->primaryTitle);
              //fprintf(stdout, "~~~~~~~~~~~~~~~~~~~~~~~~\n");
              //fprintf(stdout, "************************\n");
              //fprintf(stdout, "******* %s\n", head->primaryTitle); //so something is wrong with the head
              //fprintf(stdout, "************************\n");
              cmp = strcmp(lowercase(head->primaryTitle), lowercase(n->primaryTitle)); //SEG FAULTING HERE!!!!
            }
            //fprintf(stdout, "past cmp:: %d\n", cmp);
            if (cmp > 0)
            {
                tmp = head->left;
                if (tmp == NULL)
                {
                //  fprintf(stdout, "set left \n");
                    head->left = n;
                    n->parent = head;
                    //fprintf(stdout, "if if\n");
                    break;
                }
                else
                {
                    head = tmp;
                    //fprintf(stdout, "if else\n");
                    /*
                    fprintf(stdout, " -->\n");
                    fprintf(stdout, "%s\t", head->primaryTitle);
                    fprintf(stdout, "%s\t", head->startYr);
                    fprintf(stdout, "%s\t", head->runtimeMin);
                    fprintf(stdout, "%s\t", head->genres);
                    fprintf(stdout, "%s\t", head->mediaType);
                    fprintf(stdout, "%s\t", head->dateAdded);
                    fprintf(stdout, "\npost if else print -->\n");
                    */
                    //so i believe the issue is in here... porque???
                    //perhaps when its called twice in a row
                }
            }
            else if (cmp < 0)
            {
                tmp = head->right;
                if (tmp == NULL)
                {
                //  fprintf(stdout, "set right \n");
                    head->right = n;
                    n->parent = head;
                    //fprintf(stdout, "else if\n");
                    break;
                }
                else
                {
                    head = tmp;
                    //fprintf(stdout, "else else\n");
                }
            }
            else
            {
                return head;
                //fprintf(stdout, "else\n");
                break;
            }
        }
    }
  //  fprintf(stdout, "successful INSERT\n");

    //fprintf(stdout, "%s\t", n->primaryTitle);
    //fprintf(stdout, "%s\t", n->startYr);
    //fprintf(stdout, "%s\t", n->runtimeMin);
    //fprintf(stdout, "%s\t", n->genres);
    //fprintf(stdout, "%s\t", n->mediaType);
    //fprintf(stdout, "%s\t", n->dateAdded);
    //fprintf(stdout, "\nhmmm\n");

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
        fprintf(stdout, "~~~ %s\n", head->realTitle);
        fprintf(stdout, "*** %s\n", key->primaryTitle);
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
        cmp = strcmp(lowercase(head->primaryTitle), lowercase(key->primaryTitle));//make lower for comparisons
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

/***************************************************************************************
*    Title: bst.c
*    Author: Matthew Rinne
*    Date Accessed: <03/05/2019>
*    Link: <https://github.com/mdrinne/cs201-assign3/blob/master/bst.c>
*
***************************************************************************************/
extern int deleteBST(BST *tree,void *key)
{
    SNODE *tmp = locateBST(tree, key);
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
*
***************************************************************************************/
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
extern int sizeBST(BST *tree)
{
    return tree->size;
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
          fprintf(stdout, "word we found a substring\n");
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
