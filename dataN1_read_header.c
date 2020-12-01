/** \file dataN1_read_header.c
 *  \brief Read N1 pulse headers and store in a double linked list of N1 Headers structs
 *  \author Agustín Martina (amartina@unc.edu.ar)
 *
 *  This function gets a file descriptor to a N1 file, reads its pulse headers, and loads
 *  into a double link of data N1 header file. It also can receive N dynamic parameters.
 *  Functions to use this dynamic parameters are not implemented yet.
 *
 *  \param[in] filename - File descriptor to a N1 data file
 *  \param[in] n_args - Number of dynamic parameters function is waiting
 *  \param[out] nodeHeader - Double linked list of N1 data structures
 *
 *  \version 0.8
 *
 *  \todo Open N1 file dialog box if n_args=0
 *
 *  \see dataN1_read.c
**/

#include "dataN1_header.h"
#include "libs/list.h"
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>         /* ISO C variable aruments */


/* DEFINICIONES */
#define MAX_CHANNEL 2;
#define SAMPLE_SIZE 4;      /* bytes */
#define IQ 2;
#define MAX_DATAN1_FILE 10000;

struct Node *dataN1_read_header(char *filename, int n_args, ...){
        int idx;

        struct Node *nodeHeader;
        struct Header h;

        va_list ap;
        va_start(ap, n_args);

        FILE *fid;

        /* Inicializamos la lista*/
        nodeHeader=GetHeadNull();

        if (n_args==0){
                /* TO BE IMPLEMENTED: abre un cuadro de diálogo para seleccionar que archivo abrir*/
                printf("TBI: FALTA IMPLEMENTAR APERTURA DE UN ARCHIVO SI NO SE SELECCIONÓ NINGUNO");
        }

        /*lectura de muestras*/
        idx=MAX_DATAN1_FILE;
        if(n_args==2){
                idx = va_arg(ap, int);
        }

        va_end(ap);

        fid = fopen(filename, O_RDONLY);
        if(fid==NULL){
                printf("err %d \n", errno);
                return 0;
        }

        /* SAMPLES */
        int m = 1;
        int n = 1;
        int max_channel=MAX_CHANNEL;
        int iq=IQ;
        int sample_size=SAMPLE_SIZE;
        int max_datan1_file=MAX_DATAN1_FILE;

        while (!feof(fid)){
                /* Lectura de encabezado */
                h = dataN1_header(fid);

                if(h.version!=9999){    /* if h is not empty CHECK IF THIS WORK */
                        switch(h.version){
                        case 0:
                                printf("Version 0, I have no idea what does this do\n");
                                break;
                        case 2: {
                                if (idx < m) {
                                        if(fseek(fid,2,SEEK_CUR)!=0){
                                                fprintf(stderr, "ERROR: Fseek, Value of errno: %d\n", errno);
                                                exit(EXIT_FAILURE);
                                        }
                                        if(fseek(fid, h.validSamples * max_channel * iq * sample_size, SEEK_CUR)
                                                != 0) {
                                                fprintf(stderr, "ERROR: Fseek, Value of errno: %d\n", errno);
                                                exit(EXIT_FAILURE);
                                        }
                                        m++;
                                        printf("INGRESA AL idx!=m\n");
                                        continue;   /* next loop pof while */
                                }

                                /* APUNTAMIENTO VER */
                                if(fseek(fid, 2, SEEK_CUR)!= 0) {
                                        fprintf(stderr, "ERROR: Fseek, Value of errno: %d\n", errno);
                                        exit(EXIT_FAILURE);
                                }

                                /* Implementation of a doubly linked list to store the N headers */
                                nodeHeader = InsertAtHead(h, nodeHeader);

                                /* APUNTAMIENTO VER */
                                if(fseek(fid, h.validSamples*max_channel*iq*4, SEEK_CUR)!= 0) {
                                        fprintf(stderr, "ERROR: Fseek, Value of errno: %d\n", errno);
                                        exit(EXIT_FAILURE);
                                }
                                break;
                        }
                        default:
                                perror("ERROR: Exit by default, no compatible version\n");
                                break;
                        }
                        m++;
                        n++;
                }
        }
        fclose(fid);
        return nodeHeader;

}