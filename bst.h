#ifndef __BST_INCLUDED__
#define __BST_INCLUDED__

#include <stdio.h>
//#include "SNODE.h"

typedef struct bst BST;
typedef struct satelliteData SNODE;

extern BST   *newBST();
extern void   setBSTswapper(BST *t,void (*s)(SNODE *,SNODE *));
extern SNODE *getBSTroot(BST *t);
extern void   setBSTroot(BST *t,SNODE *replacement);
extern void   setBSTsize(BST *t,int s);
extern SNODE *insertBST(BST *t,SNODE *value);
extern void  *findBST(BST *t,SNODE *key);
extern SNODE *locateBST(BST *t,SNODE *key);
extern int    deleteBST(BST *t,SNODE *key);
extern SNODE *swapToLeafBST(BST *t,SNODE *node);
extern void   pruneLeafBST(BST *t,SNODE *leaf);
extern int    sizeBST(BST *t);

extern void  *buildTinyBST(BST *tree,SNODE *key, BST *tiny);

#endif
