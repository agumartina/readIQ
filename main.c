#include "structures.h"
#include "dataN1_read.h"
#include "include/list.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
        char *filename;
        struct Node *header;

        if(argc != 2){
                printf("Se debe incluir el path de un archivo N1 compatible");
                return 0;
        }else{
                filename = argv[1];
        }
        
        /* leemos todas las cabeceras */
        header = dataN1_read(filename, 1);
        /*imprimimos las cabeceras */
        //PrintList(header);
        //PrintDataList(header);

        // TODO: make a free function
        free(header);

        return 0;
}
