#include "structures.h" 
#include <stdio.h>
#include <string.h>

struct fileName getMetadataFilename(char *filename) {
   //char string[53] = "/b/a/iq/RMA01_0202_20180907T143110_599Z_01_006_16.IQ";

   char *tmpath = (char*) malloc(strlen(filename) + 1);
   strcpy(tmpath, filename);

   struct fileName data;

   // Extract the directory path
   char *path = strtok(tmpath, "/");
   char *temp;
   
   while(path != NULL) {
      //free(temp);
      temp = (char*) malloc(strlen(path) + 1);
      strcpy(temp, path);
      path = strtok(NULL, "/");
   }

   // Get info from file
   path = strtok(temp, "_");
   strcpy(data.radar, path);
   
   path = strtok(NULL, "_");
   strcpy(data.estrategia, path);
   
   path = strtok(NULL, "_");
   strcpy(data.iniTime, path);

   path = strtok(NULL, "_");
   strcpy(data.zeta, path);

   path = strtok(NULL, "_");
   strcpy(data.volumen, path);

   path = strtok(NULL, "_");
   strcpy(data.indice, path);

   path = strtok(NULL, "_");
   strcpy(data.num, path);

   return data;
}