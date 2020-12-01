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

#include "structures.h"
#include "dataN1_header.h"
#include <errno.h>

struct Header dataN1_header(FILE *fid, uint16_t strategy){

    size_t control;
    struct Header header;
    uint16_t version;
    uint32_t unifierMethod;
    //extern int errno;

    /* control struct empty */
    header.version = 9999;
    header.estrategia = strategy;
    //DATAN1_HEADER Devuelve el header del archivo de datan1 'filename'
    control = fread(&version,sizeof(uint16_t),1,fid);   // fread(buffer,sizeof(buffer),1,ptr); // read 10 bytes to our buffer
    if(control==1 && version==2){                       // si control no esta vacio y version es 2

        header.version=version;
        fread(&header.drxVersion,sizeof(uint16_t),1,fid);// Version de DRXProcessor
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
                    header.reservado.unifierMethod = 'Regular';
                    break;
                case 1:
                    header.reservado.unifierMethod = 'Atenuado';
                    break;
                case 2:
                    header.reservado.unifierMethod = 'Saturador';
                    break;
                case 3:
                    header.reservado.unifierMethod = 'Concatenador';
                    break;
                case 4:
                    header.reservado.unifierMethod = 'Asimilador';
                    break;
                case 5:
                    header.reservado.unifierMethod = 'Ganancia';
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
    }
    return header;
}