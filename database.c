#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <string.h>
#include <time.h>
#include "bst.h"

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


BST* datasetIntoBST(BST *bist)//int *array, struct satelliteData *satDat)
{
  FILE *fp = fopen("input.txt", "r");
  if(feof(fp))
  {
    return 0;
  }
  int ch, rindex, windex, wsize;
  char* word;
  char *dateAdded;
  wsize = 400;
  word = malloc(wsize);
  rindex = 0;
  windex = 0;
  ch = fgetc(fp);
  if(ch == EOF) return 0;
  SNODE* satDat = malloc(sizeof(SNODE));

  while(ch != EOF)
  {

    if(ch == '\n')
    {
      //determine newlines
      fprintf(stdout, "%s", word);
      fprintf(stdout, "\n");
      //define newline array
      rindex = 0;

      satDat->genres = word;

      char *empty = malloc(20);
      empty[0] = '\\';
      empty[1] = 'N';
      satDat->mediaType = empty;
      fprintf(stdout, "meditype%s\n", empty);

      char text[100];
      time_t now = time(NULL);
      struct tm *t = localtime(&now);

      strftime(text, sizeof(text)-1, "%m/%d/%Y", t);
      printf("Current Date: %s\n", text);

      dateAdded = malloc(100);
      for (int i=0; i<11; i++) {
        dateAdded[i] = text[i];
        fprintf(stdout, "%c", text[i]);
      }
      fprintf(stdout, "\n");

      satDat->dateAdded = dateAdded;

      fprintf(stdout, "wanna insert: %s\n", satDat->type);
      if(strcmp(satDat->type, "movie") == 0)
      {
        //fprintf(stdout, "did insert\n");
        fprintf(stdout, "inserting:: %p\n", satDat);
        insertBST(bist, satDat);
      }
    //  insertBST(bist, satDat);
      fprintf(stdout, "SatDat_1:: %p\n", satDat);
      satDat = malloc(sizeof(SNODE));
      fprintf(stdout, "SatDat_2:: %p\n", satDat);

      word = malloc(wsize);

    }
    else if(ch == '\t')
    {
      fprintf(stdout, " ");
      //new index of array
      word[windex++] = '\0';
      fprintf(stdout, "%s", word);
      //fprintf(stdout, " %p\n", word);
      if(rindex == 1)
      {
        satDat->type = word;
      }
      else if(rindex == 2)
      {
        satDat->primaryTitle = word;
      }
      else if(rindex == 5)
      {
        satDat->startYr = word;
      }
      else if(rindex == 7)
      {
        satDat->runtimeMin = word;
      }
      else if(rindex == 8)
      {
        fprintf(stdout, "setting genre");
        satDat->genres = word;
      }
      else
      {
        free(word);
      }
      //char* word = malloc(wsize);
      //fprintf(stdout, "word:: %p\n", word);
      word = malloc(wsize);
      windex = 0;
      rindex++;
    }
    else
    {
      //fprintf(stdout, "%c", ch);
      //add characters to buffer
      if (windex > wsize)
      {
        wsize = 2 * wsize;
        word = realloc(word, wsize);
      }
      word[windex++] = ch;
    }
    ch = fgetc(fp);
  }
  return bist;
}


BST* loadUserLog(char* log)//int *array, struct satelliteData *satDat)
{

  BST *bist = newBST();
  char name[100];
  strcpy(name, log);
  strcat(name, ".log");
  FILE *fp = fopen(name, "r");
  if(feof(fp))
  {
    //fprintf(stdout, "pastfind\n");
    return bist;
  }
  int ch, rindex, windex, wsize;
  char* word;
  char *dateAdded;
  wsize = 400;
  word = malloc(wsize);
  rindex = 0;
  windex = 0;
  ch = fgetc(fp);
  if(ch == EOF) return bist;
  SNODE* satDat = malloc(sizeof(SNODE));

  while(ch != EOF)
  {

    if(ch == '\n')
    {
      //determine newlines
      fprintf(stdout, "%s", word);
      fprintf(stdout, "\n");
      //define newline array
      rindex = 0;

      satDat->dateAdded = word;

      insertBST(bist, satDat);
      satDat = malloc(sizeof(SNODE));

      word = malloc(wsize);

    }
    else if(ch == '\t')
    {
      fprintf(stdout, " ");
      //new index of array
      word[windex++] = '\0';
      //fprintf(stdout, "%s", word);
      //fprintf(stdout, " %p\n", word);
      if(rindex == 0)
      {
        fprintf(stdout, "ptitle: %s\n", word);
        satDat->primaryTitle = word;
      }
      else if(rindex == 1)
      {
        fprintf(stdout, "yr: %s\n", word);
        satDat->startYr = word;
      }
      else if(rindex == 2)
      {
        fprintf(stdout, "runtime: %s\n", word);
        satDat->runtimeMin = word;
      }
      else if(rindex == 3)
      {
        fprintf(stdout, "genres: %s\n", word);
        satDat->genres = word;
      }
      else if(rindex == 4)
      {
        satDat->mediaType = word;
      }
      else if(rindex == 5)
      {
        satDat->dateAdded = word;
      }
      else
      {
        free(word);
      }
      //char* word = malloc(wsize);
      //fprintf(stdout, "word:: %p\n", word);
      word = malloc(wsize);
      windex = 0;
      rindex++;
    }
    else
    {
      //fprintf(stdout, "%c", ch);
      //add characters to buffer
      if (windex > wsize)
      {
        wsize = 2 * wsize;
        word = realloc(word, wsize);
      }
      word[windex++] = ch;
    }
    ch = fgetc(fp);
  }
  return bist;
}

SNODE *searchNode(char *str)//, BST *main, BST *tiny)
{
  SNODE *temp = malloc(sizeof(SNODE));
  temp->primaryTitle = str;

  return temp;
}

void printOneItem(SNODE *s, FILE *fp)
{
  fprintf(fp, "%s\t", s->primaryTitle);
  fprintf(fp, "%s\t", s->startYr);
  fprintf(fp, "%s\t", s->runtimeMin);
  fprintf(fp, "%s\t", s->genres);
  //if (s->mediaType != NULL)

  fprintf(fp, "%s\t", s->mediaType);
  fprintf(fp, "%s\t", s->dateAdded);
  fprintf(fp, "\n");
}

void printInOrder(SNODE *s)
{
  if(s == NULL)
  {
    //fprintf(stdout, "NULL\n");
    return;
  }
  fprintf(stdout, "[");
  printInOrder(s->left);
  if(s->left != NULL)
  {
    fprintf(stdout, " ");
  }
  fprintf(stdout, "%s", s->primaryTitle);
  if(s->right != NULL)
  {
    fprintf(stdout, " ");
  }

  printInOrder(s->right);
  fprintf(stdout, "]");
}

void printRowWise(SNODE *s, FILE *fp)
{
  if(s == NULL)
  {
    return;
  }

  printRowWise(s->left, fp);

  printOneItem(s, fp);

  printRowWise(s->right, fp);

}

void writeToFile(char *log, SNODE *newishLog)
{
  int i = 0;
  char name[100];
  strcpy(name, log);
  strcat(name, ".log");
  //FILE *output = fopen(name, "a");
  FILE *output = fopen(name, "w");
  printRowWise(newishLog, output);
  /*
    fprintf(output,"%s\t", newishLog->primaryTitle);
    fprintf(output,"%s\t", newishLog->startYr);
    fprintf(output,"%s\t", newishLog->runtimeMin);
    fprintf(output,"%s\t", newishLog->genres);
    fprintf(output,"%s\t", newishLog->mediaType);
    fprintf(output,"%s\n", newishLog->dateAdded);
    */

  return;
}

int main(void)
{
  /* ~~~~~ Initialization ~~~~~ */
  //create new BST
  BST *database = newBST();
  //read in data(bst)
  database = datasetIntoBST(database);
  SNODE *root = getBSTroot(database);
  fprintf(stdout, "--------------------------\n");
  fprintf(stdout, "root:: %s\n", root->primaryTitle);
  //printInOrder(root);
  //fprintf(stdout, "\n");
  //----------------------------------------------------------

  /* ~~~~~~ UI ~~~~~~ */
  SNODE *gen;
  char *gensearch = "girl";
  gen = searchNode(gensearch);

  BST *tinybst = newBST();

  // 0) select user log
  // need user input
  //write log with changes
  char *logname = "testlog";


  BST *userlog = loadUserLog(logname);
  fprintf(stdout, "------------------- User Log ---------------------\n");
  printRowWise(getBSTroot(userlog), stdout);
  printf("--------------------------------------------------------");


  // 1) Build tiny set from search key
  buildTinyBST(database, gen, tinybst);

  // 2) Display
  fprintf(stdout, "--------------------------- Search Log --------------------------\n");
  printRowWise(getBSTroot(tinybst), stdout);
  fprintf(stdout, "---------------------------------------------------------------\n");

  // 3) collect name of item from user

  //find item
  SNODE *item;
  char *itemsearch = "The Girl Who Took the Wrong Turning"; //"The Girl Who Loves a Soldier";
  item = searchNode(itemsearch);

  SNODE *found;
  fprintf(stdout, "prefind\n");
  found = findBST(userlog, item);
  fprintf(stdout, "pastfind\n");
  if (found == NULL) {
    fprintf(stdout, "FINDING NEW\n");
    found = findBST(tinybst, item);
    SNODE *duplicate = malloc(sizeof(SNODE));
    duplicate->primaryTitle = found->primaryTitle;
    duplicate->genres = found->genres;
    duplicate->startYr = found->startYr;
    duplicate->runtimeMin = found->runtimeMin;
    duplicate->type = found->type;
    duplicate->dateAdded= found->dateAdded;
    duplicate->mediaType= found->mediaType;
    insertBST(userlog, duplicate);
    found = findBST(userlog, item);
  }

  printOneItem(found, stdout);

  //4) determine change type
  //    delete
  //    update

  //5) implement changes



  //newdate = input 1;
  /*
  char *newdate = "2/11/2222";
  found->dateAdded = newdate; //newdate;
  */

  //fprintf(stdout, "um\n");
  //write log with changes
  //char *logname = "testlog";
  deleteBST(userlog, found);
  writeToFile(logname, getBSTroot(userlog));

  //alert user changes have been made and ask for more input




  return 0;
  //*nodes are satDat
  //data at top level
  //full bst that we can process
  //querying loops will come in
}
