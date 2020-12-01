/** \file dataN1_read.c
 *  \brief Read N1 data files and store in a double double linked list of N1 structures
 *  \author Agustín Martina (amartina@unc.edu.ar)
 *
 *  This function gets a file descriptor to a N1 file, and loads into a double double
 *  link of data N1 file. One linked list of Headers structures and the second
 *  of IQ data elements. It also can receive N dynamic parameters. Functions
 *  to use this dynamic parameters are not implemented yet.
 *
 *  \param[in] filename - File descriptor to a N1 data file
 *  \param[in] n_args - Number of dynamic parameters function is waiting
 *  \param[out] nodeHeader - Double double linked list of N1 data structures
 *
 *  \version 0.8
 *
 *  \todo Open N1 file dialog box if n_args=0
 *  \todo Read all IQ data into a malloc and then took the IQ form memory
 *  \todo check if zero as first data is in all rays or just the first ray
 *
 *  \see dataN1_read_header.c
**/

#include "dataN1_header.h"
#include "libs/list.h"
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <stdarg.h>         /* ISO C variable aruments */
#include <zconf.h>
#include <complex.h>    /* Standard Library of Complex Numbers */
#include <netcdf.h> 

/* RMA N1 DEFINITIONS */
#define MAX_CHANNEL 2;
#define SAMPLE_SIZE 4;      /* bytes */
#define IQ 2;
#define MAX_DATAN1_FILE 10000;

struct Node *dataN1_read(char *filename,int n_args, ...){
        int idx;
        extern int errno;
        size_t error;

        struct Node *nodeHeader;
        struct Node *temp;
        struct Data *IQheader, *IQfirst;
        struct Header h;
        struct data d = {0+0*I,0+0*I};

        float Vi, Vq, Hi, Hq;           // to temporary read I/Q data 

        va_list ap;
        va_start(ap, n_args);

        FILE *fid;

        /* Inicializamos la lista*/
        nodeHeader=GetHeadNull();
        IQheader=GetDataNull();

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

        /** We open the binary file to be parsed  */
        fid = fopen(filename, "rb");
        if (fid == NULL){
                perror("Error in open N1 file");
                return 0;
        }

        /* SAMPLES */
        int m = 1;
        //int n = 1;
        int max_channel = MAX_CHANNEL;
        int iq = IQ;
        int sample_size = SAMPLE_SIZE;
        int max_datan1_file = MAX_DATAN1_FILE;

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
                                        if (fseek(fid, h.validSamples*max_channel*iq*sample_size, SEEK_CUR)!= 0) {    // in matlab fseek(fid, h.validSamples*MAX_CHANNEL*IQ*SAMPLE_SIZE, 'cof');
                                                perror("ERROR: Fseek, Value of errno");
                                                exit(EXIT_FAILURE);
                                        }
                                        m++;
                                        printf("INGRESA AL idx!=m\n");
                                        //continue;   /* next loop pof while */
                                }

                                /* Implementation of a doubly linked list to store the N headers */
                                nodeHeader=InsertAtHead(h, nodeHeader);
                                //PrintList(nodeHeader);
                                /** The IQ data has the next structure
                                 *  V_I[1]
                                 *  V_Q[1]
                                 *  V_I[..]
                                 *  V_Q[..]
                                 *  V_I[validSamples]
                                 *  V_Q[validSamples]
                                 *  H_I[1]
                                 *  H_Q[1]
                                 *  H_I[..]
                                 *  H_Q[..]
                                 *  H_I[validSamples]
                                 *  H_Q[validSamples]
                                 *  So first we fill all V data, and then all H
                                 **/



                                /*if(fseek(fidH, fseek(fid, 4, SEEK_CUR)+2*h.validSamples, SEEK_SET)!=0){
                                        perror("ERROR: Fseek, Value of errno: %d\n");
                                        exit(EXIT_FAILURE);
                                }*/

                                /** we read all V (I and Q) into IQ structure **/
                                /**
                                if (fseek(fid, h.validSamples*max_channel*iq*sample_size, SEEK_CUR)!= 0) {    // to the next head
                                        perror("ERROR: Fseek, Value of errno");
                                        exit(EXIT_FAILURE);
                                }
                                */
                                /* we prepare two *FILE  */

                                //fidH = fdopen (dup (fileno (fid)), "r"); // to dulpicate the filepinters
                                //fidH=fid;
                                /*if (fseek(fidH, h.validSamples*iq, SEEK_CUR)!= 0) {    // to the next head
                                        perror("ERROR: Fseek, Value of errno");
                                        exit(EXIT_FAILURE);
                                }
                                */
                                /* iteration over a IQ ray samples*/
                                printf("We will iterate Nº %u samples\n", h.validSamples); //ERASE
                                for(int i=0; i<h.validSamples;i++) {
                                        error=fread(&Vi, sizeof(float),1,fid);
                                        if (error==0){
                                                perror("Error reading Ray");
                                        }
                                        error=fread(&Vq, sizeof(float),1,fid);
                                        if (error==0){
                                                perror("Error reading Ray");
                                        }
                                        d.V=Vi+Vq*I; // we save it as a complex number
                                        //printf("Insert V tail\n");
                                        IQheader = InsertDataAtHead(d, IQheader);
                                }
                                IQfirst=DataGoToTail(IQheader);
                                for(int i=0; i<h.validSamples;i++) {
                                        error=fread(&Hi, sizeof(float),1,fid);
                                        if (error==0){
                                                perror("Error reading Ray");
                                        }
                                        error=fread(&Hq, sizeof(float),1,fid);
                                        if (error==0){
                                                perror("Error reading Ray");
                                        }
                                        
                                        d.H=Hi+Hq*I; // we save it as a complex number
                                        //printf("%.16f, %.16fi, %.16f, %.16fi\n",creal(d.V), cimag(d.V), creal(d.H), cimag(d.H));
                                        IQfirst = InsertDataH(d, IQfirst);
                                }

                                
                                /** we need to go back to the head of the IQ list **/

                                //nodeHeader = rewindIQ(nodeHeader);

                                //we print it on a file so we test it
                                //PrintDataListFile(nodeHeader);
                                //nodeHeader = rewindIQ(nodeHeader);

                                //PrintDataListFile(IQheader);
                                break;
                                }
                        default:
                                perror("ERROR: Exit by default, no compatible version\n");
                                break;
                        }
                        m++;
                        //printf("\nIteration Nº %d\n",m); // ERASE
                }
                //char c = getchar();
        }
        fclose(fid);
        //fclose(fidH);
        return nodeHeader;
}