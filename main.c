#include "structures.h"
#include "dataN1_read.h"
#include "libs/list.h"
#include <stdio.h>

int main() {
        char *filename;
        struct Node *header;

        filename="/home/sagus/CLionProjects/IQ/RMA01_9005_01_20160224T195114_245Z_02.IQ";
        
        /* leemos todas las cabeceras */
        header=dataN1_read(filename, 1);
        /*imprimimos las cabeceras */
        //PrintList(header);
        //PrintDataList(header);

        
        return 0;
}