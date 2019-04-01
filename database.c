#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
  char* realTitle;

  void *left;
  void *right;
  void *parent;
};

//prints one element of the satelliteData struct
void printOneItem(SNODE *s, FILE *fp)
{
  fprintf(fp, "%s\t", s->realTitle);
  fprintf(fp, "%s\t", s->startYr);
  fprintf(fp, "%s\t", s->runtimeMin);
  fprintf(fp, "%s\t", s->genres);
  fprintf(fp, "%s\t", s->mediaType);
  fprintf(fp, "%s\t", s->dateAdded);
  fprintf(fp, "\n");
}

//prints the titles of the binary search tree in order
void printInOrder(SNODE *s)
{
  if(s == NULL)
  {
    return;
  }
  fprintf(stdout, "[");
  printInOrder(s->left);
  if(s->left != NULL)
  {
    fprintf(stdout, " ");
  }
  fprintf(stdout, "%s", s->realTitle);
  if(s->right != NULL)
  {
    fprintf(stdout, " ");
  }

  printInOrder(s->right);
  fprintf(stdout, "]");
}

//prints all elements of the in order by title name
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

//reads the all the data from the file into the binary search tree
BST* datasetIntoBST(BST *bist, char fileName[])
{

  int i = 0;
  //checks to see if the file exists
  while(i == 0)
  {
    if( access( fileName, F_OK ) != -1 )
    {
       i = 1;
    }
    else
    {
       fprintf(stdout, "This file does not exist, please enter a different file.\n");
       fgets(fileName, 250, stdin);
       fileName[strcspn(fileName, "\n")] = 0;
    }
  }

  FILE *fp = fopen(fileName, "r");
  if(feof(fp))
  {
    return 0;
  }

  int ch, rindex, windex, wsize;
  char* word;
  char* tword;
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
    // If found newline, end of single record
    if(ch == '\n')
    {

      // Populating the current time
      char text[100];
      time_t now = time(NULL);
      struct tm *t = localtime(&now);
      strftime(text, sizeof(text)-1, "%m/%d/%Y", t);
      dateAdded = malloc(100);
      for (int i=0; i<11; i++) {
        dateAdded[i] = text[i];
      }
      satDat->dateAdded = dateAdded;

      satDat->genres = word;

      // Determines if it is a movie and if so it adds to database
      if(strcmp(satDat->type, "movie") == 0)
      {
        satDat->parent = NULL;
        satDat->left = NULL;
        satDat->right = NULL;
        satDat->mediaType = NULL;
        insertBST(bist, satDat);
      }

      // reset everything for next input
      rindex = 0;
      satDat = malloc(sizeof(SNODE));
      word = malloc(wsize);

    }
    //when there is a tab, add the completed word to the correct struct item
    else if(ch == '\t')
    {
      // Sets end string character for current word buffer
      word[windex++] = '\0';

      if(rindex == 1)
      {
        satDat->type = word;
      }
      else if(rindex == 2)
      {
        satDat->realTitle = word;
        //if A, The, An is at the begining of the string
        if (word[0] == 'T' && word[1] == 'h' && word[2] == 'e' && word[3] == ' ') {
          tword = malloc(wsize);
          for (int i=4; i<windex; i++){
            tword[i-4] = word[i];
          }
          satDat->primaryTitle = tword;
        }
        else if (word[0] == 'A' && word[1] == ' ') {
          tword = malloc(wsize);
          for (int i=2; i<windex; i++){
            tword[i-2] = word[i];
          }
          satDat->primaryTitle = tword;
        }
        else if (word[0] == 'A' && word[1] == 'n' && word[2] == ' ') {
          tword = malloc(wsize);
          for (int i=3; i<windex; i++){
            tword[i-3] = word[i];
          }
          satDat->primaryTitle = tword;
        }
        else {
          satDat->primaryTitle = word;
        }
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
        satDat->genres = word;
      }
      else
      {
        free(word);
      }

      // Reset word buffer, increment the row index
      word = malloc(wsize);
      windex = 0;
      rindex++;
    }
    else
    {
      //add characters to buffer, first check if out of space
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

//reads in the user log and adds it to a seperate binary search tree
BST* loadUserLog(char log[])
{
  BST *bist = newBST();
  char name[100];
  strcpy(name, log);
  strcat(name, ".log");

  if(access(name, F_OK) != -1)
  {
    fprintf(stdout, "Successfully found: %s\n", name);
  }
  else
  {
    fprintf(stdout, "------------------------------- User Log -------------------------------\n");
    fprintf(stdout, "------------------------------------------------------------------------\n");
    return bist;
  }

  FILE *fp = fopen(name, "r+");

  if(feof(fp))
  {
    return bist;
  }

  int ch, rindex, windex, wsize;
  char* word;
  char* tword;

  wsize = 400;
  word = malloc(wsize);
  rindex = 0;
  windex = 0;
  ch = fgetc(fp);
  if(ch == EOF) return bist;
  SNODE* satDat = malloc(sizeof(SNODE));

  while(ch != EOF)
  {
    // If newline, clear row buffer and insert new node
    if(ch == '\n')
    {
    //  fprintf(stdout, "%s\n", word);
      //define newline array

      if(rindex == 4)
      {
        //fprintf(stdout, "Date added not here, manually setting\n");
        satDat->mediaType = word;

        word = malloc(400);
        word[0] = '\\';
        word[1] = 'N';
        word[2] = '\0';
        satDat->dateAdded = word;
      }
      else if(rindex == 5)
      {
        satDat->dateAdded = word;
      }

      insertBST(bist, satDat);

      // reset buffers and row index for next entry
      rindex = 0;
      satDat = malloc(sizeof(SNODE));
      word = malloc(wsize);

    }
    //if tab, write word to correct place
    else if(ch == '\t')
    {
      //fprintf(stdout, " ");
      // end word buffer with escape char
      word[windex++] = '\0';

      if(rindex == 0)
      {
        satDat->realTitle = word;
        // if A, The, An is at the begining of the string
        if (word[0] == 'T' && word[1] == 'h' && word[2] == 'e' && word[3] == ' ') {
          tword = malloc(wsize);
          for (int i=4; i<windex; i++){
            tword[i-4] = word[i];
          }
          satDat->primaryTitle = tword;
        }
        else if (word[0] == 'A' && word[1] == ' ') {
          tword = malloc(wsize);
          for (int i=2; i<windex; i++){
            tword[i-2] = word[i];
          }
          satDat->primaryTitle = tword;
        }
        else if (word[0] == 'A' && word[1] == 'n' && word[2] == ' ') {
          tword = malloc(wsize);
          for (int i=3; i<windex; i++){
            tword[i-3] = word[i];
          }
          satDat->primaryTitle = tword;
        }
        else {
          satDat->primaryTitle = word;
        }
      }
      else if(rindex == 1)
      {
        satDat->startYr = word;
      }
      else if(rindex == 2)
      {
        satDat->runtimeMin = word;
      }
      else if(rindex == 3)
      {
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
    //    fprintf(stdout, "FREEING WORD\n");
        free(word);
      }

      // reset for next word
      word = malloc(wsize);
      windex = 0;
      rindex++;
    }
    else
    {
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
  fclose(fp);

  fprintf(stdout, "------------------------------- User Log -------------------------------\n");
  printRowWise(getBSTroot(bist), stdout);
  fprintf(stdout, "------------------------------------------------------------------------\n");

  return bist;
}

//returns a struct element to be searched for
SNODE *searchNode(char *str)
{
  SNODE *temp = malloc(sizeof(SNODE));
  temp->primaryTitle = str;

  return temp;
}

//write the userlog to the file
void writeToFile(char log[], SNODE *newishLog)
{
  char name[100];
  strcpy(name, log);
  strcat(name, ".log");

  fprintf(stdout, "Writing userlog: %s\n", name);

  FILE *output = fopen(name, "w");
  printRowWise(newishLog, output);
  fclose(output);
//  fprintf(stdout, "Successful write!\n");
  return;
}

int main(void)
{
  BST *database = newBST();
  BST *tinybst = newBST();

  SNODE *found = malloc(sizeof(SNODE));
  SNODE *item = malloc(sizeof(SNODE));
  SNODE *duplicate;

  char fileName[256];
  char logname[256];
  char doInput[50];
  char itemsearch[250];
  char input[1000];
  char temp[1000];

  char keepGoing[15];
  char dateAddedAnswer[15];
  strcpy(keepGoing, "y");
  strcpy(dateAddedAnswer, "n");

  fprintf(stdout, "Hello! Please enter the name of the IMDB datafile you would like to use.\n");
  fgets(fileName, 250, stdin);
  fileName[strcspn(fileName, "\n")] = 0;

  database = datasetIntoBST(database, fileName);
/*
  fprintf(stdout, "----------------------DATABASE----------------------------\n");
  printRowWise(getBSTroot(database), stdout);
  fprintf(stdout, "----------------------------------------------------------\n");
*/

  fprintf(stdout, "What log would you like to write to?\n");
  fgets(logname, 250, stdin);
  logname[strcspn(logname, "\n")] = 0;

  BST *userlog = loadUserLog(logname);



  while(strcmp(keepGoing, "y") == 0)
  {
    fprintf(stdout, "What would you like to do? (add, delete, update, retrieve, changeUser)\n");
    fgets(doInput, 25, stdin);
    doInput[strcspn(doInput, "\n")] = 0;

    while(strcmp(doInput, "add")!= 0 && strcmp(doInput, "delete")!= 0 && strcmp(doInput, "update")!= 0 && strcmp(doInput, "retrieve") != 0 && strcmp(doInput, "changeUser")!= 0)
    {
      printf("I'm sorry, that was not an option, please choose again\n");
      printf("What would you like to do? (add, delete, update, changeUser)\n");
      fgets(doInput, 25, stdin);
      doInput[strcspn(doInput, "\n")] = 0;
    }

    if(strcmp(doInput, "add")==0)
    {
      fprintf(stdout, "What title would you like to search for?\n");
      fgets(itemsearch, 250, stdin);
      itemsearch[strcspn(itemsearch, "\n")] = 0;

      item = searchNode(itemsearch);


      buildTinyBST(database, item, tinybst);

      while(getBSTroot(tinybst) == NULL)
      {
        fprintf(stdout, "I'm sorry, that title does not exist in the database, please enter different search word\n");
        fgets(itemsearch, 250, stdin);
        itemsearch[strcspn(itemsearch, "\n")] = 0;
        item = searchNode(itemsearch);
        buildTinyBST(database, item, tinybst);
      }
      fprintf(stdout, "----------------------------- Search Results -----------------------------\n");
      printRowWise(getBSTroot(tinybst), stdout);
      fprintf(stdout, "---------------------------------------------------------------------------\n");


      fprintf(stdout, "Which movie would you like to add? Please copy and paste the title of the selection\n");
      fgets(input, 250, stdin);
      input[strcspn(input, "\n")] = 0;

      SNODE *specific = malloc(sizeof(SNODE));
      specific = searchNode(input);

      found = findBST(tinybst, specific);
      while(found == NULL)
      {
        fprintf(stdout, "I'm sorry, that title does not exist in the search results, please enter the title of the selection\n");
        fgets(input, 250, stdin);
        input[strcspn(input, "\n")] = 0;
        specific = searchNode(input);
        found = findBST(tinybst, specific);
      }

      duplicate = malloc(sizeof(SNODE));
      duplicate->primaryTitle = found->primaryTitle;
      duplicate->realTitle = found->realTitle;
      duplicate->genres = found->genres;
      duplicate->startYr = found->startYr;
      duplicate->runtimeMin = found->runtimeMin;
      duplicate->dateAdded = found->dateAdded;
      duplicate->mediaType = found->mediaType;

      insertBST(userlog, duplicate);

      if (found == NULL)
      {
          fprintf(stdout, "why is this null\n");
      }

      fprintf(stdout, "What media type is this? (examples: blueray, dvd, digital)\n");
      fgets(temp, 15, stdin);
      temp[strcspn(temp, "\n")] = 0;

      char *newmedia;
      newmedia = malloc(100);
      for (int i=0; i<11; i++)
      {
        newmedia[i] = temp[i];
      }
      duplicate->mediaType = newmedia;

      fprintf(stdout, "Would you like to add the date added? (y or n)\n");
      fgets(dateAddedAnswer, 3, stdin);
      dateAddedAnswer[strcspn(dateAddedAnswer, "\n")] = 0;
      if(strcmp(dateAddedAnswer, "y") == 0)
      {
        fprintf(stdout, "Please enter date added in MM/DD/YYYY format.\n");
        fgets(temp, 15, stdin);
        temp[strcspn(temp, "\n")] = 0;

        char *newdate;
        newdate = malloc(100);
        for (int i=0; i<11; i++)
        {
          newdate[i] = temp[i];
        }
        duplicate->dateAdded = newdate;

      }
      else
      {
        char text[100];
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char *dateAdded;

        strftime(text, sizeof(text)-1, "%m/%d/%Y", t);
        dateAdded = malloc(100);
        for (int i=0; i<11; i++)
        {
          dateAdded[i] = text[i];
        }

        strcpy(found->dateAdded, dateAdded);
      }

    }

    else if(strcmp(doInput, "delete")==0)
    {
      fprintf(stdout, "------------------------------- User Log -------------------------------\n");
      printRowWise(getBSTroot(userlog), stdout);
      fprintf(stdout, "------------------------------------------------------------------------\n");

      fprintf(stdout, "Which selection would you like to delete? Please copy and paste the title from above.\n");
      fgets(input, 255, stdin);
      input[strcspn(input, "\n")] = 0;
    //  fprintf(stdout, "input:: %s\n", input);

      SNODE *byebyebye = malloc(sizeof(SNODE));
      byebyebye = searchNode(input);
      //printOneItem(byebyebye, stdout);
      deleteBST(userlog, byebyebye);
    }

    else if(strcmp(doInput, "update")==0)
    {
      fprintf(stdout, "------------------------------- User Log -------------------------------\n");
      printRowWise(getBSTroot(userlog), stdout);
      fprintf(stdout, "------------------------------------------------------------------------\n");

      fprintf(stdout, "Which selection would you like to update? Please copy and paste the title from above.\n");
      fgets(input, 255, stdin);
      input[strcspn(input, "\n")] = 0;

      SNODE *specific = malloc(sizeof(SNODE));
      char reading[256];
      char updating[256];
      specific = searchNode(input);
      //  fprintf(stdout, "FINDING NEW\n");
      found = findBST(userlog, specific);

      while(found == NULL)
      {
        fprintf(stdout, "I'm sorry, that title does not exist in the log, please enter different search word\n");
        fgets(input, 255, stdin);
        input[strcspn(input, "\n")] = 0;

        specific = searchNode(input);
        //fprintf(stdout, "FINDING NEW\n");
        found = findBST(userlog, specific);
      }
      //ok this is great but why do some of them not exist?

      fprintf(stdout, "What would you like to update? (title, year, runtime, genres, mediatype, date)\n");
      fgets(reading, 255, stdin);
      reading[strcspn(reading, "\n")] = 0;

      fprintf(stdout, "What would you like to update it to? \n");
      fgets(updating, 255, stdin);
      updating[strcspn(updating, "\n")] = 0;
      char *newnew;
      if(strcmp(reading, "title") == 0)
      {
        newnew = malloc(400);
        for (int i=0; i<399; i++)
        {
          newnew[i] = updating[i];
        }
        found->realTitle = newnew;
        //strcpy(found->realTitle, updating);
      }
      else if(strcmp(reading, "year") == 0)
      {
        newnew = malloc(400);
        for (int i=0; i<399; i++)
        {
          newnew[i] = updating[i];
        }
        found->startYr = newnew;
        //strcpy(found->startYr, updating);
      }
      else if(strcmp(reading, "runtime") == 0)
      {
        newnew = malloc(400);
        for (int i=0; i<399; i++)
        {
          newnew[i] = updating[i];
        }
        found->runtimeMin = newnew;
        //strcpy(found->runtimeMin, updating);
      }
      else if(strcmp(reading, "genres") == 0)
      {
        newnew = malloc(400);
        for (int i=0; i<399; i++)
        {
          newnew[i] = updating[i];
        }
        found->genres = newnew;
        //strcpy(found->genres, updating);
      }
      else if(strcmp(reading, "mediatype") == 0)
      {
        newnew = malloc(400);
        for (int i=0; i<399; i++)
        {
          newnew[i] = updating[i];
        }
        found->mediaType = newnew;
        //strcpy(found->mediaType, updating);
      }
      else if(strcmp(reading, "date") == 0)
      {
        newnew = malloc(400);
        for (int i=0; i<399; i++)
        {
          newnew[i] = updating[i];
        }
        found->dateAdded = newnew;
        //strcpy(found->dateAdded, updating);
      }
      else
      {
        fprintf(stdout, "Sorry, that was not an option, please choose to update again and input a valid choice.\n");
      }
    }
    else if(strcmp(doInput, "retrieve") == 0)
    {
      fprintf(stdout, "------------------------------- User Log -------------------------------\n");
      printRowWise(getBSTroot(userlog), stdout);
      fprintf(stdout, "------------------------------------------------------------------------\n");
    }
    else if(strcmp(doInput, "changeUser") == 0)
    {
        writeToFile(logname, getBSTroot(userlog));

        fprintf(stdout, "What log would you like to write to?\n");
        fgets(logname, 250, stdin);
        logname[strcspn(logname, "\n")] = 0;

        userlog = loadUserLog(logname);
    }


    tinybst = newBST();
    fprintf(stdout, "Change made, would you like to make other changes? (y or n)\n");
    fgets(keepGoing, 15, stdin);
    keepGoing[strcspn(keepGoing, "\n")] = 0;
    while(strcmp(keepGoing, "n") != 0 && strcmp(keepGoing, "y") != 0)
    {
      fprintf(stdout, "Sorry, that was not an option, would you like to make other changes? (y or n)\n");
      fgets(keepGoing, 15, stdin);
      keepGoing[strcspn(keepGoing, "\n")] = 0;
    }
  }

  writeToFile(logname, getBSTroot(userlog));
  fprintf(stdout, "The log has been updated, bye!\n");

  return 0;
}
