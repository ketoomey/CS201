#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
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


BST* datasetIntoBST(BST *bist, char *fileName)//int *array, struct satelliteData *satDat)
{
  FILE *fp = fopen(fileName, "r");
  //if file does not exist
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
  if(access(name, F_OK) != -1)
  {
    int i = 0;
  }
  else
  {
    return bist;
  }
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

  FILE *output = fopen(name, "w");
  printRowWise(newishLog, output);

  return;
}
/*
SNODE *parseThroughInput(char *input)
{
  fprintf(stdout, "Made it into new function");
  SNODE *tempish = malloc(sizeof(SNODE));
  int windex = 0;
  int rindex = 0;
  int wsize = 1000;
  int tracker = 0;
  char *tempWord = malloc(wsize);
  while(input[tracker]!= '\0') //are you the issue?
  {
    if(input[tracker] == '\t')
    {
      tempWord[windex++] = '\0';
      windex = 0;
     if(rindex == 0)
     {
        tempish->primaryTitle = tempWord;
     }
     else if(rindex == 1)
     {
       tempish->startYr = tempWord;
     }
     else if(rindex == 2)
     {
       tempish->runtimeMin = tempWord;
     }
     else if(rindex == 3)
     {
       tempish->genres = tempWord;
     }
     else if(rindex == 4)
     {
       tempish->mediaType = tempWord;
     }
     else if(rindex == 5)
     {
       tempish->dateAdded = tempWord;
     }
     rindex++;
   }
    else
    {
      if (windex > wsize)
      {
        wsize = 2 * wsize;
        tempWord = realloc(tempWord, wsize);
      }
      tempWord[windex++] = input[tracker];
    }
    tracker++;
  }
  return tempish;
}
*/
int main(void)
{
  BST *database = newBST();
  BST *tinybst = newBST();

  SNODE *found = malloc(sizeof(SNODE));
  SNODE *item = malloc(sizeof(SNODE));
  SNODE *duplicate = malloc(sizeof(SNODE));

  char *fileName = malloc(30*sizeof(char));
  fileName = "input.txt";
  char *logname;

  //char *doInput = malloc(12*sizeof(char));
  char doInput[12];
  //char *itemsearch = malloc(250*sizeof(char));
  char itemsearch[250];
  //char *input = malloc(1000*sizeof(char));
  char input[1000];
  char temp[1000];

  char keepGoing[15];
  char dateAddedAnswer[15];
  strcpy(keepGoing, "y");
  strcpy(dateAddedAnswer, "n");
  //keepGoing = {"y"};
  //dateAddedAnswer = {"n"};
  /*fprintf(stdout, "Hello! Please enter the name of the IMDB datafile you would like to use.\n");
  scanf("%s", fileName);*/




  fprintf(stdout, "Dont forget to un comment out user input :)");
  logname = "testlog";
  database = datasetIntoBST(database, fileName);


  /*SNODE *root = getBSTroot(database);
  fprintf(stdout, "--------------------------\n");
  fprintf(stdout, "root:: %s\n", root->primaryTitle);
  */
  /*
  SNODE *gen;
  char *gensearch = "girl";
  gen = searchNode(gensearch);
  */

/*  found = findBST(userlog, item);
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
*/
//  printOneItem(found, stdout);

  /*
  fprintf(stdout, "What log would you like to write to?\n");
  scanf("%s", logname);
  */


  fprintf(stdout, "user innitialization\n");


  BST *userlog = loadUserLog(logname);
  fprintf(stdout, "Here is your current log\n");
  printRowWise(getBSTroot(userlog), stdout);
  fprintf(stdout, "made it here!\n");


  while(strcmp(keepGoing, "y") == 0)
  {
    fprintf(stdout, "What would you like to do? (add, delete, update, changeUser)\n");
    //scanf("%s", doInput);
    fgets(doInput, 11, stdin);
    doInput[strcspn(doInput, "\n")] = 0;

    while(strcmp(doInput, "add")!= 0 && strcmp(doInput, "delete")!= 0 && strcmp(doInput, "update")!= 0 && strcmp(doInput, "changeUser")!= 0)
    {
      printf("I'm sorry, that was not an option, please choose again\n");
      printf("What would you like to do? (add, delete, update, changeUser)\n");
      fgets(doInput, 11, stdin);
      doInput[strcspn(doInput, "\n")] = 0;
    }

    if(strcmp(doInput, "add")==0)
    {
      fprintf(stdout, "What title would you like to search for?\n");
      //scanf("%s", itemsearch);

      fgets(itemsearch, 250, stdin);
      itemsearch[strcspn(itemsearch, "\n")] = 0;
      item = searchNode(itemsearch);

      buildTinyBST(database, item, tinybst);
      printRowWise(getBSTroot(tinybst), stdout);

      fprintf(stdout, "Which movie would you like to add? Please copy and paste the title of the selection\n");
      fgets(input, 250, stdin);
      input[strcspn(input, "\n")] = 0;
      fprintf(stdout, ">|%s|<\n", input);


      SNODE *specific = malloc(sizeof(SNODE));
      specific = searchNode(input);
      printOneItem(specific, stdout);
      fprintf(stdout, "did die here?\n");
      fprintf(stdout, "|%s|\n", specific->primaryTitle);
      // ------------- Works up to here --------------

      fprintf(stdout, "FINDING NEW\n");
      found = findBST(tinybst, specific);
      if (found == NULL)
      {
        fprintf(stdout, "why is this null\n");
      }
      fprintf(stdout, "post find\n");

      //SNODE *duplicate = malloc(sizeof(SNODE));
      duplicate->primaryTitle = found->primaryTitle;
      //fprintf(stdout, "1\n");
      duplicate->genres = found->genres;
      //fprintf(stdout, "2\n");
      duplicate->startYr = found->startYr;
      //fprintf(stdout, "3\n");
      duplicate->runtimeMin = found->runtimeMin;
      //fprintf(stdout, "4\n");
      duplicate->dateAdded = found->dateAdded;
      //fprintf(stdout, "5\n");
      duplicate->mediaType = found->mediaType;
      //fprintf(stdout, "MADE IT\n");

      insertBST(userlog, duplicate);
      found = findBST(userlog, duplicate);

      fprintf(stdout, "What media type is this? (examples: blueray, dvd, digital)\n");
      //scanf("%s", found->mediaType);
      fgets(temp, 15, stdin);
      temp[strcspn(temp, "\n")] = 0;
      fprintf(stdout, "about to assign to mediaType\n");
      //found->mediaType = temp;
      /*
      char *newtemp = malloc(256);
      int i = 0;
      //int len = sizeof(temp) / sizeof(temp[0]);
      //fprintf(stdout, "len: %d\n", len);
      while (i < 10)
      {
        fprintf(stdout, "%c ", temp[i]);
        newtemp[i] = temp[i];
        i++;
      }
      fprintf(stdout, "out of while loop, assigning\n");
      fprintf(stdout, "populated: %s\n", newtemp);
      if (found == NULL) {
        fprintf(stdout, "found is null lmao\n");
      }
      found->mediaType = newtemp;
      */

      strcpy(found->mediaType, temp);
      fprintf(stdout, "Successfully assigned\n");


      fprintf(stdout, "Would you like to add the date added? (y or n)\n");
      //scanf("%c", &dateAddedAnswer);
      fgets(dateAddedAnswer, 3, stdin);
      dateAddedAnswer[strcspn(dateAddedAnswer, "\n")] = 0;
      if(strcmp(dateAddedAnswer, "y") == 0)
      {
        fprintf(stdout, "Please enter date added in MM/DD/YYYY format.\n");
        //scanf("%s", found->dateAdded);
        fgets(temp, 15, stdin);
        temp[strcspn(temp, "\n")] = 0;
        strcpy(found->dateAdded, temp);
      }

    }

    else if(strcmp(doInput, "delete")==0)
    {
      printRowWise(getBSTroot(userlog), stdout);
      fprintf(stdout, "Which selection would you like to delete? Please copy and paste the title from above.\n");
      //scanf("%s ", input);
      fgets(input, 255, stdin);
      input[strcspn(input, "\n")] = 0;

      SNODE *byebyebye = malloc(sizeof(SNODE));
      byebyebye = searchNode(input);
      deleteBST(userlog, byebyebye);
    }

    else if(strcmp(doInput, "update")==0)
    {
      printRowWise(getBSTroot(userlog), stdout);
      fprintf(stdout, "Which selection would you like to update? Please copy and paste from above.\n");
      //scanf("%s ", input); //will this work?
      fgets(input, 255, stdin);
      input[strcspn(input, "\n")] = 0;

      SNODE *specific = malloc(sizeof(SNODE));
      char reading[256];
      char updating[256];
      specific = searchNode(input);
      fprintf(stdout, "FINDING NEW\n");
      found = findBST(userlog, specific);
      fprintf(stdout, "MADE IT\n");
      fprintf(stdout, "What would you like to update? (title, year, runtime, genres, mediatype, date)\n");
      //scanf("%s", reading);
      fgets(reading, 255, stdin);
      reading[strcspn(reading, "\n")] = 0;

      fprintf(stdout, "What would you like to update it to? \n");
      //scanf("%s", updating);
      fgets(updating, 255, stdin);
      updating[strcspn(updating, "\n")] = 0;

      if(strcmp(reading, "title") == 0)
      {
        strcpy(found->primaryTitle, updating);
      }
      else if(strcmp(reading, "year") == 0)
      {
        strcpy(found->startYr, updating);
      }
      else if(strcmp(reading, "runtime") == 0)
      {
        strcpy(found->runtimeMin, updating);
      }
      else if(strcmp(reading, "genres") == 0)
      {
        strcpy(found->genres, updating);
      }
      else if(strcmp(reading, "mediatype") == 0)
      {
        strcpy(found->mediaType, updating);
      }
      else if(strcmp(reading, "date") == 0)
      {
        strcpy(found->dateAdded, updating);
      }
    }

    /*
    //writeToFile(logname,  getBSTroot(userlog));
    else if(strcmp(doInput, "changeUser") == 0)
    {
        writeToFile(logname, getBSTroot(userlog));
        fprintf(stdout, "Which user log would you like to change to?\n");
        scanf("%s", logname);
        userlog = loadUserLog(logname);
    }
    */

    fprintf(stdout, "Change made, would you like to make other changes? (y or n)\n");
    //scanf("%c", &keepGoing);
    fgets(keepGoing, 15, stdin);
    keepGoing[strcspn(keepGoing, "\n")] = 0;

  }

  writeToFile(logname, getBSTroot(userlog));
  fprintf(stdout, "The log has been updated, bye!\n");

  return 0;
}
