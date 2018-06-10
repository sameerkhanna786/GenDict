
#include "hashtable.h"
#include "philphix.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

HashTable *dictionary;

int main(int argc, char **argv){
  if(argc != 2){
    /* Note, you can print everything you want to standard error, it will be
       ignored by the autograder */
    fprintf(stderr, "Specify a dictionary\n");
    return 0;
  }
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(2255, &stringHash, &stringEquals);
  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");
  fprintf(stderr, "Processing stdin\n");
  processInput();
  return 0;
}


/* Define a hash function. This hash function was found on StackOverflow, question ID 7666509*/
unsigned int stringHash(void *s){
  char *string = (void *) s;
  unsigned int hash = 5381;
  int c;
  while ((c = *string++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}


int stringEquals(void *s1, void *s2){
  if (strcmp((char *) s1, (char *) s2) == 0) {
     return 1;
  }
  return 0;
}

int findword(FILE * file, char **b, int size) {
     int i = 0;
     int type = 0;
     char c;
     while((c = getc(file)) && c != EOF) {
        if (!(isspace(c))) {
           if (type == 0) {
              type = 1;
           }
           if (type == 1) {
              (*b)[i] = c;
              if (i >= (size - 1)) {
                 size*=2;
                 *b = realloc(*b, (size+1)*sizeof(char));
                 if (*b == NULL) {
                    return 0;
                 }
              }
              i++;
           }
        } else {
           if (type == 1) {
              (*b)[i] = 0;
              break;
           }
        }
     }
     if (c == EOF) {
        return 0;
     }
     return size;
}

void readDictionary(char *name){
  int buffer_size = 999;
  int item_size = 999;
  FILE * file = fopen(name, "r");
  char * buffer = malloc(buffer_size*sizeof(char));
  char * item = malloc(item_size*sizeof(char));
  char **b = &buffer;
  char **i = &item;
  int end = 1;
  if (!(file == NULL)) {
      while (end != 0) {
         end = findword(file, b, buffer_size);
         buffer_size = end;
         char *key = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
         end = findword(file, i, item_size);
         item_size = end;
         char *data = (char *)malloc((strlen(item) + 1) * sizeof(char));
         strcpy(key, buffer);
         key[strlen(key)] = 0;
         strcpy(data, item);
         data[strlen(data)] = 0;
         insertData(dictionary, key, data);
      }
  }
}

void processInput(){
     int i = 0;
     int type = 0;
     unsigned char c;
     unsigned int a;
     int size = 1;
     char * buffer = malloc(size*sizeof(char));
     char **b = &buffer;
     while((a = (getchar()))) {
        c = (char)a;
        if ((isalpha(c) || isdigit(c))) {
           if (type == 0) {
              i = 0;
              type = 1;
           }
           if (type == 1) {
              if (i >= size - 1) {
                size *= 2;
                *b = realloc(*b, ((size-1)*sizeof(char)));
              }
              (*b)[i] = c;
              i += 1;
           }
        } else {
           if (type == 1) {
              type = 0;
              (*b)[i] = '\0';
              char *tmp = (char *)malloc(2*(size + 1) * sizeof(char));
              strcpy(tmp, buffer);
              int t1 = 0;
              int t2 = 0;
              int t3 = 0;

              if (findData(dictionary, tmp) != NULL) {
                 t1 = 1;
                 char *temp = findData(dictionary, tmp);
                 int index = 0;
                 for(index = 0; index < strlen(temp); index++) {
                    fprintf(stdout, "%c", temp[index]);
                 }
              }

              int j = 0;
              for (j = 1; j < strlen(tmp); j++) {
                 tmp[j] = tolower(tmp[j]);
              }
              if (findData(dictionary, tmp) != NULL) {
                 t2 = 1;
                 if(t1 == 0) {
                    char *temp = findData(dictionary, tmp);
                    int index = 0;
                    for(index = 0; index < strlen(temp); index++) {
                       fprintf(stdout, "%c", temp[index]);
                    }
                 }
              }

              tmp[0] = tolower(tmp[0]);
              if (findData(dictionary, tmp) != NULL) {
                 t3 = 1;
                 if (t1 == 0 && t2 == 0) {
                    char *temp = findData(dictionary, tmp);
                    int index = 0;
                    for(index = 0; index < strlen(temp); index++) {
                       fprintf(stdout, "%c", temp[index]);
                    }
                 }
              }

              if (t1 == 0 && t2 == 0 && t3 == 0) {
                    char *temp = buffer;
                    int index = 0;
                    for(index = 0; index < i; index++) {
                       fprintf(stdout, "%c", temp[index]);
                    }
              }
           }
           if (a == EOF) {
              break;
           }
           fprintf(stdout, "%c", c);
        }
     }
}