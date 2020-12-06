//
// Created by sagus on 02/02/17.
//

#ifndef IQ_LIST_H
#define IQ_LIST_H

#include "structures.h"

struct Node *GetNewNode(struct Header);
struct Node *GetHeadNull();
struct Node *InsertAtHead(struct Header, struct Node*);

struct Node *InsertAtTail(struct Header, struct Node*);
void PrintList(struct Node*);
void ReversePrintList(struct Node*);

struct Data *GetDataNull();
struct Data *GetNewDataNode(struct data);
struct Data *InsertDataAtHead(struct data, struct Data*);
struct Data *InsertDataH(struct data, struct Data*);
struct Data *DataGoToTail(struct Data*);
void InsertDataAtTail(struct data, struct Data*);
void InsertDataV(struct data, struct Data *);
void PrintDataList(struct Data*);
struct Data *rewindIQ(struct Data *);

void printPrueba(struct Data *);
void PrintDataListFile(struct Data *);
#endif //IQ_LIST_H
