#ifndef IQ_DATAN1_HEADER_H
#define IQ_DATAN1_HEADER_H

#include "include/structures.h"
#include "include/cJSON.h"
#include <stdio.h>
#include <stdbool.h>
struct Header dataN1_header(FILE *, uint16_t, bool);
void save_as_JSON(struct Header);
void write_JSON(cJSON *);

#endif