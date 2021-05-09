#include "structures.h"
#include "cJSON.h"
#include <stdio.h>
#include <stdbool.h>

#ifndef IQ_DATAN1_HEADER_H
#define IQ_DATAN1_HEADER_H

struct Header dataN1_header(FILE *, struct fileName *, bool);

void save_as_JSON(struct Header);

void write_JSON(cJSON *);

#endif