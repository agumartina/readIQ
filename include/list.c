/** \file list.c
 *  \brief Double linked list implementations
 *  \author Agustín Martina (amartina@unc.edu.ar)
 *
 * \todo CountNodes functions: counts the length of a linked list
**/
#include "list.h"
#include<stdio.h>

/** \brief node of Header data structure
**/
struct Node{
        struct Header head;
        struct Node *next;
        struct Node *prev;
};

/** \brief Creates a new node to be inserted into a list of Headers
 * \param[in] x - Header data of a pulse
 * \param[out] newNode - node with the header data
**/
//Creates a new Node and returns pointer to it.
struct Node *GetNewNode(struct Header x)
{
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->head = x;
        newNode->prev = NULL;
        newNode->next = NULL;
        return newNode;
}

/** \brief Initialize a linked list with NULL head.
 *
 * The user must call this function to get a head of a new linked list.
 * This functions declare an empty node (pointing null)
 *
 * \param[out] head - head of a new linked list
**/
struct Node *GetHeadNull(){
        struct Node *head; // global variable - pointer to head node.
        return head = NULL;
}


/** \brief Insert a node at the head of a linked list.
 *
 * \param[in]x - A Header structure to be inserted
 * \param[in,out] head - Head of the target linked list
**/
struct Node *InsertAtHead(struct Header x, struct Node *head) {
        struct Node* newNode = GetNewNode(x);

        if(head == NULL) {
                head = newNode;
                //head->datos=NULL;
                return head;
        }
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
        //head->datos=NULL;

        return head;
}

/** \brief TODO Length linked list counter
 *
 * \param[in] head - Head of the linked list to be measured
**/
int CountNodes(struct Node *head){
        /*
         * TO BE IMPLEMENTED
         */
        free(head);

        return 0;
}

/** \brief Insert a Node at the tail of doubly linked list
 *
 * @param x[in] - Header structure to be inserted
 * @param head[in,out] - Head of the double linked list target
 */
struct Node *InsertAtTail(const struct Header x, struct Node *head) {
        struct Node* temp = head;
        struct Node* newNode = GetNewNode(x);
        if(head == NULL) {
                head = newNode;
        //        printf("ITS NULL, new node with azimuth=%.19lf\n", head->head.azimuth);
                return head;
        }
        while(temp->next != NULL) temp = temp->next; // Go To last Node
        temp->next = newNode;
        newNode->prev = temp;
        //printf("\n INSERTED NODE: %u,%u, %.19lf \n", temp->head.version, temp->head.drxVersion, temp->head.initCW); //BORRAR
        return head;
}


/** \brief Prints all elements of a doubly linked list in a LIFO way
 *
 * @param head[in] - Head of the double linked list target
 */
void PrintList(struct Node *head) {
        struct Node* temp = head;

        printf("Version, drxVersion, initCW, azimuth, elevation, idVolumen, idBarrido, idConjunto, idGrupo, idPulso. iniBarrido, finBarrido, finGrupo, inhibido, validSamples, nroAdquisicion, nroSecuencia, timeval_h, timeval_l\n");
        while(temp != NULL) {
                printf("%u, %u, %.19lf, %.19lf, %.19lf, %u, %u, %.u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %lu, %lu \n",
                        temp->head.version, temp->head.drxVersion, temp->head.initCW, temp->head.azimuth, temp->head.elevation,
                        temp->head.idVolumen, temp->head.idBarrido, temp->head.idConjunto, temp->head.idGrupo, temp->head.idPulso,
                        temp->head.iniBarrido, temp->head.finBarrido, temp->head.finGrupo, temp->head.inhibido, temp->head.validSamples,
                        temp->head.nroAdquisicion, temp->head.nroSecuencia, temp->head.timeval_h, temp->head.timeval_l);
                printf("\n\n %.19lf, %.19lf, %.19lf, %.19lf, %.19lf, %.19lf, %.19lf,%.19lf,%.19lf, %u,%u,%u,%u, %u\n",
                        temp->head.reservado.unifierThreshold, temp->head.reservado.saturedSampledRatio_H,
                        temp->head.reservado.saturedSampledRatio_V, temp->head.reservado.attenuatedSampledRatio_H, temp->head.reservado.attenuatedSampledRatio_V,
                        temp->head.reservado.pulseSaturedSampledRatio_H_reg, temp->head.reservado.pulseSaturedSampledRatio_H_att, temp->head.reservado.pulseSaturedSampledRatio_V_reg,
                        temp->head.reservado.pulseSaturedSampledRatio_V_att, temp->head.reservado.pulsePeakPower_H_reg, temp->head.reservado.pulsePeakPower_H_att,
                        temp->head.reservado.pulsePeakPower_V_reg, temp->head.reservado.pulsePeakPower_V_att, temp->head.basura);
                temp = temp->next;
        }
}

/** \brief Prints all elements of a doubly linked list in a FIFO (reverse) way
 *
 * @param head[in] - Head of the double linked list target
 */
void ReversePrintList(struct Node *head) {
        struct Node* temp = head;
        if(temp == NULL) return; // empty list, exit
        // Going to last Node
        while(temp->next != NULL) {
                temp = temp->next;
        }
        // Traversing backward using prev pointer
        printf("Version, drxVersion, initCW, azimuth, elevation, idVolumen, idBarrido, idConjunto, idGrupo, idPulso. iniBarrido, finBarrido, finGrupo, inhibido, validSamples, nroAdquisicion, nroSecuencia, timeval_h, timeval_l\n");
        while(temp != NULL) {
                printf("inside the wile \n");
                printf("%u, %u, %.19lf, %.11f, %.11f, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %u, %lu, %lu\n", temp->head.version,
                        temp->head.drxVersion, temp->head.initCW, temp->head.azimuth, temp->head.elevation, temp->head.idVolumen,
                        temp->head.idBarrido, temp->head.idConjunto, temp->head.idGrupo, temp->head.idPulso, temp->head.iniBarrido,
                        temp->head.finBarrido, temp->head.finGrupo, temp->head.inhibido, temp->head.validSamples, temp->head.nroAdquisicion,
                        temp->head.nroSecuencia, temp->head.timeval_h, temp->head.timeval_l);
                temp = temp->prev;
        }
        printf("\n");
}

/*************************************************************************************************************************************************************
 *
 * 
 * Funciones de la lista de datos
 * 
 * 
 *************************************************************************************************************************************************************/

/** \brief node of IQ data structure
**/
struct Data {
        struct data muestra;
        struct Data* next;
        struct Data* prev;
};

/** \brief Initialize a linked list with NULL head.
 *
 * The user must call this function to get a head of a new linked list.
 * This functions declare an empty node (pointing null)
 *
 * \param[out] head - head of a new linked list
**/
struct Data *GetDataNull(){
        struct Data *head; // global variable - pointer to head node.
        return head = NULL;
}

/** \brief Creates a new Data node (IQ) and returns pointer to it.
 *
 * @param x[in] - Data IQ structure
 */
struct Data *GetNewDataNode(struct data x) {
        struct Data* newDataNode = (struct Data*)malloc(sizeof(struct Data));
        newDataNode->muestra = x;
        newDataNode->prev = NULL;
        newDataNode->next = NULL;
        return newDataNode;
}

/** \brief Insert a node of IQ data at the head of a Data linked list.
 *
 * \param[in]x - A V structure to be inserted
 * \param[in,out] head - Head of the target linked list
**/
struct Data *InsertDataAtHead(struct data sample, struct Data *head) {
        struct Data* newData = GetNewDataNode(sample);

        /* si es el primer dato */
        if(head == NULL) {
                head = newData;
                return head;
        }

        head->prev = newData;
        newData->next = head;
        head = newData;

        return head;
}

/** \brief This function goes to the tail so H data is inserted
 * This must be called before we inser H channel data
 * \param[in] - IQheader 
 * \param[out] - IQtail
 **/
struct Data *DataGoToTail(struct Data *head){
        struct Data *temp=head;
        while(temp->next != NULL) temp = temp->next; // Go To last Data

        return temp;
}

/** \brief Insert a node of H IQ data at the head of a Data linked list, and returns the position were the data is inserted
 *
 * The difference with InsertDataAtHead is that this function returns a pinter to the
 * las data stored.
 *
 * \param[in]x - A H structure to be inserted
 * \param[in,out] head - Head of the target linked list
**/
struct Data *InsertDataH(struct data sample, struct Data *head) {

        head->muestra.H=creal(sample.H)+cimag(sample.H)*I;
        //head->muestra.H_Q=sample.H_Q;

        head=head->prev;
        
        return head;
}

/** \brief Insert a node of IQ data at the tail of a Data linked list.
 *
 * \param[in]x - A IQ structure to be inserted
 * \param[in,out] head - Head of the target linked list
**/
void InsertDataAtTail(struct data sample, struct Data *head) {
        struct Data* temp = head;
        struct Data* newData = GetNewDataNode(sample);
        if(head == NULL) {
                head = newData;
                return;
        }
        while(temp->next != NULL) temp = temp->next; // Go To last Data
        temp->next = newData;
        newData->prev = temp;
}


/** \brief Insert a node of IQ data at the tail of a Data linked list and returns that header
 *
 * The difference of this function with InsertDataAtTail is that we want to return the tail
 * pointer, instead of the head.
 * 
 * \param[in]x - A IQ structure to be inserted
 * \param[in,out] head - Head of the target linked list
**/
void InsertDataV(struct data sample, struct Data *head) {
        struct Data* temp = head;
        struct Data* newData = GetNewDataNode(sample);
        if(head == NULL) {
                head = newData;
                return;
        }
        while(temp->next != NULL) temp = temp->next; // Go To last Data
        temp->next = newData;
        newData->prev = temp;
}

/*struct Node *InsertDataV(struct data x, struct Node *head) {

        struct Data* newData = GetNewDataNode(x);
        if(head->datos == NULL) {
                head->datos = newData;
                return head;
        }
        while(head->datos->next != NULL)
                head->datos = head->datos->next; // Go To last Data
        head->datos->prev = head->datos;
        head->datos=newData;

        return head;
}*/

/** @brief Counts the length of a list
 *
 * @param head - Linked list
 */
void lengthList(struct Data *head){

        while(head->prev != NULL){
                head=head->prev;
                //TO BE IMPEMENTED
        }
}

/** @brief This function go back to the first IQ data
 *
 * We need to return to the first IQ data to fill the data structure with H_I and H_Q
 *
 * @param[in,out] head - Data N1 structure
 */
struct Data *rewindIQ(struct Data *head){
        int contador;
        contador = 0; //borrar
        while(head->prev != NULL) {
                head = head->prev;
                contador++;
        }
        printf("rewind %u\n", contador);
        return head;
}

/** @brief Prints all the IQ elements in linked list in forward traversal order
 *
 * @param head - Head of the linked list to be printed
 */
void PrintDataList(struct Data *head) {
        struct Data* temp = head;

       //FILE *fheader;
        //header=fopen("data.csv","w");

        while(temp->next != NULL) {
                printf("DATA LIST V_I, V_Q | H_I, H_Q\n");
                printf("%.16f, %.16fi| %.16f, %.16fi\n", creal(temp->muestra.V), cimag(temp->muestra.V), creal(temp->muestra.H), cimag(temp->muestra.H));

                temp = temp->next;
        }
        //close(fheader);
}

void PrintDataListFile(struct Data *head) {
        struct Data* temp = head;

        FILE *fheader = fopen("data.csv","w");
        if (fheader == NULL){
                perror("Error in open N1 file");
        }
        fprintf(fheader,"V_I, V_Q | H_I, H_Q\n");
        while(temp->next != NULL) {
                fprintf(fheader,"%.16f, %.16fi, %.16f, %.16fi\n",creal(temp->muestra.V), cimag(temp->muestra.V), creal(temp->muestra.H), cimag(temp->muestra.H));
                temp = temp->next;
        }
        fprintf(fheader,"%.16f, %.16fi, %.16f, %.16fi\n", creal(temp->muestra.V), cimag(temp->muestra.V), creal(temp->muestra.H), cimag(temp->muestra.H));
        fclose(fheader);
}

void printPrueba(struct Data *head){
        printf("\nIQ CONTROL: hi %.16f, hq %.16f, vi %.16f, vq %.16f\n", creal(head->muestra.H), cimag(head->muestra.H), creal(head->muestra.V), cimag(head->muestra.V));
}