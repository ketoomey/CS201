#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <string.h>
#include <time.h>

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
}SNODE;

int datasetIntoArray()//int *array, struct satelliteData *satDat)
{
  FILE *fp = fopen("input.txt", "r");
  if(feof(fp))
  {
    return 0;
  }
  int ch, rindex, widex, wsize;
  char* word;
  wsize = 400;
  word = malloc(wsize);
  rindex = 0;
  windex = 0;
  ch = fgetc(fp);
  if(ch == EOF) return 0;
  while(ch != EOF)
  {
    ch = fgetc(fp);
    if(ch == '\n')
    {
      //determine newlines
      fprintf(stdout, "\n");
      //define newline array
      rindex = 0;
      SNODE* satDat = malloc(sizeof(SNODE));

    }
    else if(ch == '\t')
    {
      fprintf(stdout, " ");
      //new index of array
      rindex++;
      word[windex++] = '\0';
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
        satDat->genres = word;
      }
      else
      {
        free(word);
      }
      word = malloc(wsize);
      windex = 0;
    }
    else
    {
      fprintf(stdout, "%c", ch);
      //add characters to buffer
      if (windex > wsize)
      {
        wsize = 2 * wsize;
        word = realloc(word, wsize);
      }
      word[windex++] = ch;
    }
  }
  return 0;
}



int main(void)
{
  datasetIntoArray();
  return 0;
}
