#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
#include <string.h>
#include <time.h>

struct satelliteData
{
  char* ttNum;
  char* type;
  char* primaryTitle;
  char* originalTitle;
  char* isAdult;
  char* startYr;
  char* endYr;
  char* runtimeMin;
  char* genres;
  char* mediaType;
  char* dateAdded;
//  struct satelliteData* next;
};

struct binSearchTree
{
  int tconst;
  struct binSearchTree* left;
  struct binSearchTree* right;
};

int datasetIntoArray(int *array, struct satelliteData *satDat)
{
  printf("sos\n");
  //struct satelliteData* satDat = (struct satelliteData*)malloc(sizeof(10000000));
  //struct satelliteData satDat[10000000];
//  satDat->next = NULL;
  char c;
  //array = malloc(sizeof(200));
  int i = 0;
  char* arr;
  int start = 0;
  int end = 0;
  char** temp;
  int count = 0;
  int x = 0;
  char* temp2;
  int a = 0;
  int index = 0;
  int* everything;
  int ind = 0;
  int f = 0;
  //array = malloc(sizeof(30));
  FILE *dataSet = fopen("data-2.tsv", "r");
  FILE *test = fopen("input.txt", "r");
  FILE *output = fopen("output.txt", "w");
  if(test == NULL)
  {
    return -1;
  }
  else
  {
    printf("help\n");
  //  for(f = 0; f<3; f++)
     while ( (fgets(arr, 400, test) != NULL)) // goes through every line
     {
      // fgets(arr, 400, test);
       printf("do we make it to the while?");
       for(i = 0; i<400; i++) //goes through each character in the line
       {
          if(arr[i] == '\t') //if its a tab
          {
            count = 0;
            a = 0;
            end = i;  //set the end of the word equal to the tab space
            for(int s = start; s<end; s++) //for the num of characters between start and tab
            {
              //do i need to add it a differerent way? YAY ALLY!!
              temp[count][a] += arr[s]; //add each character to the temp array
            }
            count++;
            a++; //increment count to determine which switch case
            if(strcmp(*temp, "\\N") == 0) //if its empty set it to NULL
            {
              temp = NULL;
            }
            start = end +1;
            // set the begining of the next word after the tab
          }
          printf("please work\n");
        }
        for(int b = 1; b <= 9; b++)
        {
          switch(b)
            {
              case 1:
                satDat[ind].ttNum = temp[0]; //satDat  the temp into satDat
                break;
              case 2:
                satDat[ind].type = temp[1];
                break;
              case 3:
                satDat[ind].primaryTitle = temp[2];
                break;
              case 4:
                satDat[ind].originalTitle = temp[3];
                break;
              case 5:
                satDat[ind].isAdult = temp[4];
                break;
              case 6:
                satDat[ind].startYr = temp[5];
                break;
              case 7:
                satDat[ind].endYr = temp[6];
                break;
              case 8:
                satDat[ind].runtimeMin = temp[7];
                break;
              case 9:
                satDat[ind].genres = temp[8];
                break;
              default: satDat[ind] = NULL;
            }
            //satDat = satDat->next; //move to next node element
          }
          if(strcmp(satDat[ind].type, "movie")) //only add to array if movie
          {
            for(x = 2; x<8; x++) //for the length of the number
            {
              temp2[x-2] = satDat[ind].ttNum[x]; // add the string number to the string
            }
            array[index] = atoi(temp2); // add the number to the future bst array
            index++;
          }
          ind++;
        }
     }
//  printf("%d\n", array[1]);
  return *array;
}

struct binSearchTree* allocateNewNode(int num)
{
  struct binSearchTree* add = (struct binSearchTree*)malloc(sizeof(struct binSearchTree));
  add->tconst = num;
  add->left = NULL;
  add->right = NULL;

  return add;
}

struct binSearchTree* arrayIntoBST(int *array, int s, int e)
{
  if (s > e) return NULL;
  int middle = (s + e) / 2;
  struct binSearchTree *root = allocateNewNode(array[middle]);
  root->left = arrayIntoBST(array, s, middle-1);
  root->right = arrayIntoBST(array, middle+1, e);
  return root;
}

struct binSearchTree* traverseBST()
{
  //searches through BST to find the node to retrieve
  //update if necessary
  //wait this might not be necessary
  //how am i going to be able to find the keyword bc its not attached to the array
  return NULL;
}

struct satelliteData* retrieve(struct satelliteData *satDat,  struct satelliteData* retrievalList, struct satelliteData* newishLog)
{
  //finds all the entry and writes them to file
  char criteria[17];
  char search[300];
  int i = 0;
  int j = 0;
  printf("What search criteria are you using? \n Options: tconst, titleType, primaryTitle, originalTitle, isAdult, startYr, endYr, runtimeMin, genres\n");
  scanf("%s", criteria);
  while (strcmp(criteria, "tconst")!= 0 && strcmp(criteria, "titleType")!=0 && strcmp(criteria, "primaryTitle") != 0 && strcmp(criteria, "originalTitle")!= 0
  && strcmp(criteria, "isAdult")!= 0&& strcmp(criteria, "startYr")!= 0&& strcmp(criteria, "endYr")!= 0&& strcmp(criteria, "runtimeMin")!= 0&& strcmp(criteria, "genres")!= 0)
  {
    printf("I'm sorry, that was not an option, please choose again\n");
    printf("What search criteria are you using? \n Options: tconst, titleType, primaryTitle, originalTitle, isAdult, startYr, endYr, runtimeMin, genres\n");
    scanf("%s", criteria);
  }
  printf("What would you like to search for?");
  scanf("%s", search);
  strcpy(strlwr(search), search);

  for(i = 0; i < sizeof(satDat); i++)
  {
    if(strcmp(criteria, "tconst") == 0)
    {
      if(strcmp(strlwr(satDat[i].ttNum), search) == 0)
      {
        retrievalList[j] = satDat[i];
        j++;
      }
    }
    else if(strcmp(criteria, "titleType") == 0)
    {
      if(strcmp(strlwr(satDat[i].type), search) == 0)
      {
        retrievalList[j] = satDat[i];
        j++;
      }
    }
    else if(strcmp(criteria, "primaryTitle") == 0)
    {
      if(strstr(strlwr(satDat[i].primaryTitle), search) == 0)
      {
        retrievalList[j] = satDat[i];
        j++;
      }
    }
    else if(strcmp(criteria, "originalTitle") == 0)
    {
      if(strstr(strlwr(satDat[i].originalTitle), search) == 0)
      {
        retrievalList[j] = satDat[i];
        j++;
      }
    }
    else if(strcmp(criteria, "isAdult") == 0)
    {
      if(strstr(strlwr(satDat[i].isAdult), search) == 0)
      {
        retrievalList[j] = satDat[i];
        j++;
      }
    }
    else if(strcmp(criteria, "startYr") == 0)
    {
      if(strstr(strlwr(satDat[i].startYr), search) == 0)
      {
        retrievalList[j] = satDat[i];
        j++;
      }
    }
    else if(strcmp(criteria, "endYr") == 0)
    {
      if(strstr(strlwr(satDat[i].endYr), search) == 0)
      {
        retrievalList[j] = satDat[i];
        j++;
      }
    }
    else if(strcmp(criteria, "runtimeMin") == 0)
    {
      if(strstr(strlwr(satDat[i].runtimeMin), search) == 0)
      {
        retrievalList[j] = satDat[i];
        j++;
      }
    }
    else if(strcmp(criteria, "genres") == 0)
    {
      if(strstr(strlwr(satDat[i].genres), search) == 0)
      {
        retrievalList[j] = satDat[i];
        j++;
      }
    }
  }
  printf("keep going\n");
  return NULL;
}

struct satelliteData* create(struct satelliteData *satDat, struct satelliteData* retrievalList, struct satelliteData* newishLog)
{
  //creates a new entry
  int endNode = __________ + 1;//how do i find the endNode?
  char entry[400];
  char temp[9][75];
  char num[8];
  char mediaType[10];
  char dateAdded[12];
  /*https://www.techiedelight.com/print-current-date-and-time-in-c/
    used to get the current date
  */
  time_t now;
  struct tm *local = localtime(&now);
  int month = local->tm_mon +1;
  int day = local->tm_mday;
  int year = local->tm_year + 1900;
  char tempdate[12];
  sprintf(tempdate, "%d/%d/%d ", month, day, year);
  strcpy(dateAdded, tempdate);
  int i = 0, a = 0, count = 0, start = 0, end = 0, number = 0;
  retrieve(satDat, retrievalList, newishLog);
  printf("Please enter the information for the new entry. Cut and paste the line from the list above.\n");
  scanf("%s", entry);
  printf("Please enter media type and date added(MM/DD/YYYY)");
  scanf("%s %s", mediaType, dateAdded);
  for(i = 0; i<400; i++) //goes through each character in the line
  {
     if(entry[i] == '\t') //if its a tab
     {
       count = 0;
       a = 0;
       end = i;  //set the end of the word equal to the tab space
       for(int s = start; s<end; s++) //for the num of characters between start and tab
       {
         //do i need to add it a differerent way?
         temp[count][a] += entry[s]; //add each character to the temp array
       }
       count++;
       a++; //increment count to determine which switch case
       start = end + 1;
       // set the begining of the next word after the tab
     }
     printf("please work\n");
   }
   for(int b = 1; b <= 9; b++ )
   {
     switch(b)
       {
         case 1:
        //   satDat[endNode].ttNum = temp[0];
           break;
         case 2:
        //   satDat[endNode].type = temp[1];
           break;
         case 3:
           newishLog[endNode].primaryTitle = temp[2];
           break;
         case 4:
        //   satDat[endNode].originalTitle = temp[3];
           break;
         case 5:
        //   satDat[endNode].isAdult = temp[4];
           break;
         case 6:
           newishLog[endNode].startYr = temp[5];
           break;
         case 7:
        //   satDat[endNode].endYr = temp[6];
           break;
         case 8:
           newishLog[endNode].runtimeMin = temp[7];
           break;
         case 9:
           newishLog[endNode].genres = temp[8];
           break;
         default: newishLog[endNode] = NULL;
       }
       newishLog[endNode].mediaType = mediaType;
       newishLog[endNode].dateAdded = dateAdded;

    }


    printf("wahoo\n");
    return NULL;
}


struct satelliteData* update(struct satelliteData *satDat, struct satelliteData *retrievalList, struct satelliteData *newishLog)
{
  //updates the entry
  //if ttNum changes, need to delete node, then insert new one with correct stuff


  //retrieve(satDat, retrievalList); // hmm so you dont want to retrieve the whole thing, just the log
  //which one would you like to update?
  //delete it
  //what would to like to update it to?
  //add new with new info
  char mediaType[10];
  char dateAdded[12];
  for(int i = 0; i < sizeof(newishLog); i++)
  {
    printf("%s %s %s %s %s %s\n", newishLog[i].originalTitle, newishLog[i].genres, newishLog[i].runtimeMin, newishLog[i].startYr, newishLog[i].mediaType, newishLog[i].dateAdded);
  }
  int j = sizeof(newishLog) + 1;
  //delete
  printf("Please enter the information for the updated entry. Cut and paste the line from the list above.\n");
  scanf("%s %s %s %s %s %s\n", newishLog[j].originalTitle, newishLog[j].genres, newishLog[j].runtimeMin, newishLog[j].startYr, newishLog[j].mediaType, newishLog[j].dateAdded);
  printf("Please enter media type and date added(MM/DD/YYYY)");
  scanf("%s %s", mediaType, dateAdded);


  printf("youve got this\n");
  return NULL;
}

struct satelliteData* delete(struct satelliteData *satDat, struct satelliteData *retrievalList, struct satelliteData *newishLog)
{
  //deletes the entry

  //char deletion[];
  retrieve(satDat, retrievalList, newishLog); //dont need to retrieve everything, just the log

  //scanf("%s", deletion);




  printf("you did it\n");
  return NULL;
}

void writeToFile(char *log, SNODE *newishLog)
{
  int i = 0;
  char name[100];
  strcpy(name, log);
  strcat(name, ".log");
  FILE *output = fopen(name, "a");
    fprintf(output,"%s\t", newishLog->primaryTitle);
    fprintf(output,"%s\t", newishLog->startYr);
    fprintf(output,"%s\t", newishLog->runtimeMin);
    fprintf(output,"%s\t", newishLog->genres);
    fprintf(output,"%s\t", newishLog->mediaType);
    fprintf(output,"%s\n", newishLog->dateAdded);

  return;
}

void printSearchOptions(char *log, struct satelliteData *retrievalList)
{
  int i = 0;
  if(retrievalList[0].ttNum == NULL)
  {
    printf("I'm sorry, nothing with that search criteria exists.");
  }
  else
  {
    printf("This is what your search criteria returns:: \n");
    for(i = 0; i < sizeof(retrievalList); i++)
    {
      printf("%s\t", retrievalList[i].ttNum);
      printf("%s\t", retrievalList[i].type);
      printf("%s\t", retrievalList[i].primaryTitle);
      printf("%s\t", retrievalList[i].originalTitle);
      printf("%s\t", retrievalList[i].isAdult);
      printf("%s\t", retrievalList[i].startYr);
      printf("%s\t", retrievalList[i].endYr);
      printf("%s\t", retrievalList[i].runtimeMin);
      printf("%s\n", retrievalList[i].genres);
    }
  }
}

//book has good pseudocode for insertion and deletion of binSearchTree
//when thats deleted or inserted then we need to call a method to change the struct
int main()
{
  int *array;
  char option[9];
  char *log;
  int end = sizeof(array);
  char keepGoing[3] = "yes";
  struct satelliteData* satDat = (struct satelliteData*)malloc(sizeof(10000000));
  struct satelliteData* retrievalList = (struct satelliteData*)malloc(sizeof(10000));
  struct satelliteData* newishLog = (struct satelliteData*)malloc(sizeof(100000));
  datasetIntoArray(array, satDat);
  //arrayIntoBST(array, 0, end-1);
  while(strcmp(keepGoing, "yes"))
  {
    printf("What would you like to do? Options: create, retrieve, update, delete\n");
    scanf("%s", option);
    while (strcmp(option, "create")!= 0 && strcmp(option, "retrieve")!=0 && strcmp(option, "update") != 0 &&strcmp(option, "delete")!= 0)
    {
      printf("I'm sorry, that was not an option, please choose again\n");
      printf("What would you like to do? Options: create, retrieve, update, delete\n");
      scanf("%s", option);
    }
    printf("What log would you like to write to?\n");
    scanf("%s", log);

    if(strcmp(option, "create") == 0)
    {
        create(satDat, retrievalList, newishLog);
        writeToFile(log, newishLog);
    }
    else if(strcmp(option, "retrieve") == 0)
    {
        retrieve(satDat, retrievalList, newishLog);
        printSearchOptions(log, retrievalList);
    }
    else if(strcmp(option, "update") == 0)
    {
        update(satDat, retrievalList, newishLog);
        writeToFile(log, newishLog);
    }
    else if(strcmp(option, "delete") == 0)
    {
        delete(satDat, retrievalList, newishLog);
        writeToFile(log, newishLog);
    }
    //so i can either write to log after each addition or after the user is done
    printf("Would you like to keep going? (yes or no)");
    scanf("%s\n", keepGoing);
  }
  return 0;
}
