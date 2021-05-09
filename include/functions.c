#include "structures.h" 
#include <stdio.h>
#include <string.h>

struct fileName* getMetadataFilename(char *filename) {
   //char string[53] = "/b/a/iq/RMA01_0202_20180907T143110_599Z_01_006_16.IQ";
   //char strin = /lala/lelle/jaja/RMA01_9005_01_20160224T194902_623Z_02.IQ
   struct fileName *data = malloc(sizeof(struct fileName));

   char *tmpath = (char*) malloc(strlen(filename) + 1);
   data->filepath = (char*) malloc(strlen(filename) + 1);
   strcpy(data->filepath, filename);
   strcpy(tmpath, filename);
   printf("Created structure with file: %s \n", data->filepath);

   // Extract the directory path
   char *path = strtok(tmpath, "/");
   char *temp = NULL;

   while(path != NULL) {
      //free(temp);
      temp = (char*) malloc(strlen(path) + 1);
      strcpy(temp, path);
      path = strtok(NULL, "/");
   }
   printf("Temp: %s \n", temp);
   // Get info from file
   path = strtok(temp, "_");
   strcpy(data->radar, path);
   printf("radar: %s \n", data->radar);   
   
   path = strtok(NULL, "_");
   strcpy(data->estrategia, path);
   printf("estrategia: %s \n", data->estrategia);  
   path = strtok(NULL, "_");
   strcpy(data->iniTime, path);
   printf("iniTime: %s \n", data->iniTime);  
   path = strtok(NULL, "_");
   strcpy(data->zeta, path);
   printf("zeta: %s \n", data->zeta);  
   path = strtok(NULL, "_");
   if(path == NULL){
      printf("Path is null");
   }
   strcpy(data->volumen, path);
   printf("Volumen: %s \n", data->volumen);  
   path = strtok(NULL, "_");
   strcpy(data->indice, path);
   printf("Indice: %s \n", data->indice);  
   path = strtok(NULL, ".");
   strcpy(data->num, path);
   printf("Nume: %s \n", data->num);

   if(path == NULL){
      printf("Path is null");
   }
   printf("Created structure with file: %s \n", data->filepath);
   return data;
}