/** \file dataN1_header.c
 *  \brief DataN1 file pulse header reader
 *  \author Agustín Martina (amartina@unc.edu.ar)
 *
 *  This function receive a file descriptor to a data N1 file, read its pulse headers
 *  and return the data loaded intro a Header structure.
 *
 *  \param[in] fid - File descriptor of a N1 file
 *  \param[out] header - Header structure with header data
**/

#include "dataN1_header.h"
#include <inttypes.h>
#include <errno.h>
#include <string.h>

void write_JSON(cJSON *jheader){
    FILE *jfile;
    char *out;

    out = cJSON_Print(jheader);
    jfile = fopen("test/head.json", "w+"); 
    fprintf(jfile, "%s", out);

    free(out);
    fclose(jfile);
}

void save_as_JSON(struct Header header){
    

    cJSON *jheader = cJSON_CreateObject();
    if (jheader == NULL){
        printf("No se pudo crear el objeto JSON");
        return;
    }

    cJSON *version = NULL;
    cJSON *estrategia = NULL;
    cJSON *drxVersion = NULL;

    cJSON *initCW = NULL;
    cJSON *azimuth = NULL;
    cJSON *elevation = NULL;

    cJSON *idVolumen = NULL;
    cJSON *idBarrido = NULL;
    cJSON *idConjunto = NULL;
    cJSON *idGrupo = NULL;
    cJSON *idPulso = NULL;
    
    cJSON *finBarrido = NULL;
    cJSON *iniBarrido = NULL;
    cJSON *finGrupo = NULL;
    cJSON *inhibido = NULL;

    cJSON *validSamples = NULL;
    cJSON *nroAdquisicion = NULL;
    cJSON *nroSecuencia = NULL;

    cJSON *timeval_h = NULL;
    cJSON *timeval_l = NULL;

    cJSON *reservado = NULL;
    cJSON *reservados = NULL;
    cJSON *unifierMethod = NULL;

    version = cJSON_CreateNumber(header.version);
    if (version == NULL) return;
    cJSON_AddItemToObject(jheader, "version", version);
    estrategia = cJSON_CreateString(header.estrategia);
    if (estrategia == NULL) return;
    cJSON_AddItemToObject(jheader, "estrategia", estrategia);
    drxVersion = cJSON_CreateNumber(header.drxVersion);
    if (drxVersion == NULL) return;
    cJSON_AddItemToObject(jheader, "drxVersion", drxVersion);
    
    initCW = cJSON_CreateNumber(header.initCW);
    if (initCW == NULL) return;
    cJSON_AddItemToObject(jheader, "initCW", initCW);
    azimuth = cJSON_CreateNumber(header.azimuth);
    if (azimuth == NULL) return;
    cJSON_AddItemToObject(jheader, "azimuth", azimuth);
    elevation = cJSON_CreateNumber(header.elevation);
    if (elevation == NULL) return;
    cJSON_AddItemToObject(jheader, "elevation", elevation);

    idVolumen = cJSON_CreateNumber(header.idVolumen);
    if (idVolumen == NULL) return;
    cJSON_AddItemToObject(jheader, "idVolumen", idVolumen);
    idBarrido = cJSON_CreateNumber(header.idBarrido);
    if (idBarrido == NULL) return;
    cJSON_AddItemToObject(jheader, "idBarrido", idBarrido);
    idConjunto = cJSON_CreateNumber(header.idConjunto);
    if (idConjunto == NULL) return;
    cJSON_AddItemToObject(jheader, "idConjunto", idConjunto);
    idGrupo = cJSON_CreateNumber(header.idGrupo);
    if (idGrupo == NULL) return;
    cJSON_AddItemToObject(jheader, "idPulso", idGrupo);
    idPulso = cJSON_CreateNumber(header.idPulso);
    if (idPulso == NULL) return;
    cJSON_AddItemToObject(jheader, "idPulso", idPulso);

    iniBarrido = cJSON_CreateNumber(header.iniBarrido);
    if (iniBarrido == NULL) return;
    cJSON_AddItemToObject(jheader, "iniBarrido", iniBarrido);
    finBarrido = cJSON_CreateNumber(header.finBarrido);
    if (finBarrido == NULL) return;
    cJSON_AddItemToObject(jheader, "finBarrido", finBarrido);
    finGrupo = cJSON_CreateNumber(header.finGrupo);
    if (finGrupo == NULL) return;
    cJSON_AddItemToObject(jheader, "finGrupo", finGrupo);
    inhibido = cJSON_CreateNumber(header.inhibido);
    if (inhibido == NULL) return;
    cJSON_AddItemToObject(jheader, "inhibido", inhibido);

    validSamples = cJSON_CreateNumber(header.validSamples);
    if (validSamples == NULL) return;
    cJSON_AddItemToObject(jheader, "validSamples", validSamples);
    nroAdquisicion = cJSON_CreateNumber(header.nroAdquisicion);
    if (nroAdquisicion == NULL) return;
    cJSON_AddItemToObject(jheader, "nroAdquisicion", nroAdquisicion);
    nroSecuencia = cJSON_CreateNumber(header.nroSecuencia);
    if (nroSecuencia == NULL) return;
    cJSON_AddItemToObject(jheader, "nroSecuencia", nroSecuencia);

    
    char ctimeval_h[20];
    sprintf(ctimeval_h, "0x%016" PRIx64, header.timeval_h);
    timeval_h = cJSON_CreateString(ctimeval_h);
    if (timeval_h == NULL) return;
    cJSON_AddItemToObject(jheader, "timeval_h", timeval_h);

    char ctimeval_l[20];
    sprintf(ctimeval_l, "0x%016" PRIx64, header.timeval_l);
    timeval_l = cJSON_CreateString(ctimeval_l);
    if (timeval_l == NULL) return;
    cJSON_AddItemToObject(jheader, "timeval_l", timeval_l);

    reservado = cJSON_CreateArray();
    if (reservado == NULL) return;
    cJSON_AddItemToObject(jheader, "reservado", reservado);

    reservados = cJSON_CreateObject();
    if (reservados == NULL) return;
    cJSON_AddItemToArray(reservado, reservados);

    unifierMethod = cJSON_CreateString(header.reservado.unifierMethod);
    if (unifierMethod == NULL) return;
    cJSON_AddItemToObject(reservados, "unifierMethod", unifierMethod);

    write_JSON(jheader);

    cJSON_Delete(jheader);
}

struct Header dataN1_header(FILE *fid, struct fileName *file, bool json){

    size_t control;
    struct Header header;
    uint16_t version;
    uint32_t unifierMethod;
    //extern int errno;

    /* control struct empty */
    header.version = 9999;
    strcpy(header.estrategia, file->estrategia);
    //DATAN1_HEADER Devuelve el header del archivo de datan1 'filename'
    control = fread(&version,sizeof(uint16_t),1,fid);   // fread(buffer,sizeof(buffer),1,ptr); // read 10 bytes to our buffer
    if(control==1){                       
        header.version=version;
        fread(&header.drxVersion, sizeof(uint16_t),1,fid);// Version de DRXProcessor
            /* RESERVADO */
        if(fseek(fid, 4, SEEK_CUR)!=0){    // in matlab status = fseek(fileID, offset, origin) origin='cof' current position
            fprintf(stderr, "ERROR: Fseek, Value of errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }

        fread(&header.initCW, sizeof(double),1,fid);            // Inicio de ventana de recepcion en segundos
        fread(&header.azimuth, sizeof(float),1,fid);            // Posicion en Azimuth en grados
        fread(&header.elevation, sizeof(float),1,fid);          // Posicion de Elevacion en grados

        fread(&header.idVolumen, sizeof(uint16_t),1, fid);      // Id Volumen
        fread(&header.idBarrido, sizeof(uint16_t),1, fid);      // Id Barrido
        fread(&header.idConjunto, sizeof(uint16_t),1,fid);      // Numero de Conjunto
        fread(&header.idGrupo, sizeof(uint16_t),1, fid);        // Id Grupo
        fread(&header.idPulso, sizeof(uint16_t),1, fid);        // Numero de Pulso

        fread(&header.iniBarrido, sizeof(uint8_t),1,fid);       // Inicio barrido bool
        fread(&header.finBarrido, sizeof(uint8_t),1,fid);       // Fin barrido bool
        fread(&header.finGrupo, sizeof(uint8_t),1,fid);         // Fin grupo bool
        fread(&header.inhibido, sizeof(uint8_t),1,fid);         // Pulso inhibido bool

        fread(&header.validSamples, sizeof(uint16_t),1, fid);   // Cantidad de Muestas complejas validas por canal polarimétrico
        fread(&header.nroAdquisicion,sizeof(uint16_t),1, fid);  // Contador de adquisiciones del DRX. Cada pulso es una adquisicion distinta

        /* RESERVADO */
        if(fseek(fid, 2, SEEK_CUR)!=0){
            fprintf(stderr, "ERROR: Fseek, Value of errno: %d\n", errno);
            exit(EXIT_FAILURE);
        }
        fread(&header.nroSecuencia,sizeof(uint32_t),1, fid);    // Nro. de secuencia que se incrementa en el envio y se controla en el receptor

        fread(&header.timeval_h, sizeof(uint64_t),1,fid);       // Estampa de tiempo de lectura del dato parte alta
        fread(&header.timeval_l, sizeof(uint64_t),1,fid);       // Estampa de tiempo de lectura del dato parte baja

        //fread(&header.reserved, sizeof(uint8_t),64,fid);        // Espacio Reservado (Size of Header fijo en 128 bytes)
            /* DE ACA PARA ABAJO NO ESTA EN LA DOCUMENTACIÓN */
        control=fread(&unifierMethod, sizeof(uint32_t),1,fid);  // Espacio Reservado : metodo de unificacion
        if(control==1){
            switch (unifierMethod){
                case 0:
                    //char *metodo = "Regular";
                    //header.reservado.unifierMethod = malloc(strlen(metodo) + 1);
                    //strcpy(header.reservado.unifierMethod, metodo);
                    header.reservado.unifierMethod = "Regular";
                    break;
                case 1:
                    header.reservado.unifierMethod = "Atenuado";
                    break;
                case 2:
                    header.reservado.unifierMethod = "Saturador";
                    break;
                case 3:
                    header.reservado.unifierMethod = "Concatenador";
                    break;
                case 4:
                    header.reservado.unifierMethod = "Asimilador";
                    break;
                case 5:
                    header.reservado.unifierMethod = "Ganancia";
                    break;
                default:
                    perror("No switch case unifierMethod");
            }
        }else{
            header.version=0;
        }

        fread(&header.reservado.unifierThreshold, sizeof(float),1,fid);                 // Espacio Reservado : umbral del metodo de unificacion

        fread(&header.reservado.saturedSampledRatio_H, sizeof(float),1,fid);            // Espacio Reservado : relacion de muetras saturadas respecto del total en el canal H
        fread(&header.reservado.saturedSampledRatio_V, sizeof(float),1,fid);            // Espacio Reservado : relacion de muetras saturadas respecto del total en el canal V
        fread(&header.reservado.attenuatedSampledRatio_H, sizeof(float),1,fid);         // Espacio Reservado : relacion de muetras atenuadas respecto del total en el canal H
        fread(&header.reservado.attenuatedSampledRatio_V, sizeof(float),1,fid);         // Espacio Reservado : relacion de muetras atenuadas respecto del total en el canal V

        fread(&header.reservado.pulseSaturedSampledRatio_H_reg, sizeof(float),1,fid);   // Espacio Reservado : relacion de muetras de pulso saturadas en el canal H regular
        fread(&header.reservado.pulseSaturedSampledRatio_H_att, sizeof(float),1,fid);   // Espacio Reservado : relacion de muetras de pulso saturadas en el canal H atenuado
        fread(&header.reservado.pulseSaturedSampledRatio_V_reg, sizeof(float),1,fid);   // Espacio Reservado : relacion de muetras de pulso atenuadas en el canal V regular
        fread(&header.reservado.pulseSaturedSampledRatio_V_att, sizeof(float),1,fid);   // Espacio Reservado : relacion de muetras de pulso atenuadas en el canal V atenuado

        fread(&header.reservado.pulsePeakPower_H_reg, sizeof(int32_t),1,fid);           // Espacio Reservado : potencia pico de muestra de pulso canal H regular
        fread(&header.reservado.pulsePeakPower_H_att, sizeof(int32_t),1,fid);           // Espacio Reservado : potencia pico de muestra de pulso canal H atenuado
        fread(&header.reservado.pulsePeakPower_V_reg, sizeof(int32_t),1,fid);           // Espacio Reservado : potencia pico de muestra de pulso canal V regular
        fread(&header.reservado.pulsePeakPower_V_att, sizeof(int32_t),1,fid);           // Espacio Reservado : potencia pico de muestra de pulso canal V atenuado
        fread(&header.basura, sizeof(int32_t),2,fid);                                   // Basura

        if(json == true){
            save_as_JSON(header);
        }
    }
    return header;
}