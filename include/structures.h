// 
// @file structures.h
// @brief Definitions of data structures de datos y metadatos IQ según doumentación
// @author Agustín Martina (amartina(at)unc.edu.ar)
//

#ifndef IQ_STRUCTURES_H
#define IQ_STRUCTURES_H

#include <stdlib.h>
#include <stdint.h>
#include <complex.h>    /* Standard Library of Complex Numbers */

/** @brief Structure of reserved data of a headers pulse
 */
struct Reservado{
        char const *unifierMethod;

        float unifierThreshold;         // Espacio Reservado : umbral del metodo de unificacion

        float saturedSampledRatio_H;    // Espacio Reservado : relacion de muetras saturadas respecto del total en el canal H
        float saturedSampledRatio_V;    // Espacio Reservado : relacion de muetras saturadas respecto del total en el canal V
        float attenuatedSampledRatio_H; // Espacio Reservado : relacion de muetras atenuadas respecto del total en el canal H
        float attenuatedSampledRatio_V; // Espacio Reservado : relacion de muetras atenuadas respecto del total en el canal V

        float pulseSaturedSampledRatio_H_reg;   // Espacio Reservado : relacion de muetras de pulso saturadas en el canal H regular
        float pulseSaturedSampledRatio_H_att;   // Espacio Reservado : relacion de muetras de pulso saturadas en el canal H atenuado
        float pulseSaturedSampledRatio_V_reg;   // Espacio Reservado : relacion de muetras de pulso atenuadas en el canal V regular
        float pulseSaturedSampledRatio_V_att;   // Espacio Reservado : relacion de muetras de pulso atenuadas en el canal V atenuado

        int32_t pulsePeakPower_H_reg;   // Espacio Reservado : potencia pico de muestra de pulso canal H regular
        int32_t pulsePeakPower_H_att;   // Espacio Reservado : potencia pico de muestra de pulso canal H atenuado
        int32_t pulsePeakPower_V_reg;   // Espacio Reservado : potencia pico de muestra de pulso canal V regular
        int32_t pulsePeakPower_V_att;   // Espacio Reservado : potencia pico de muestra de pulso canal V atenuado
};

/** @brief Declaration of Header structure of a pulse
 */
struct Header{
        uint16_t    version;            // Version de DataN1
        uint16_t    drxVersion;         // Version del procesador DRX que generó el dato n1
        char        estrategia[4];         // número de estrategia
        
        double      initCW;             // Inicio de ventana de recepcion en segundos
        float       azimuth;            // Posicion en Azimuth en grados
        float       elevation;          // Posicion de Elevacion en grados

        uint16_t    idVolumen;          // Id Volumen
        uint16_t    idBarrido;          // Id Barrido
        uint16_t    idConjunto;         // Numero de Conjunto
        uint16_t    idGrupo;            // Id Grupo
        uint16_t    idPulso;            // Numero de Pulso

        uint8_t     iniBarrido;         // Inicio barrido
        uint8_t     finBarrido;         // Fin barrido
        uint8_t     finGrupo;           // Fin grupo
        uint8_t     inhibido;           // Pulso inhibido

        uint16_t    validSamples;       // Cantidad de Muestas validas

        uint16_t    nroAdquisicion;     // Contador de adquisiciones. Cada pulso es una adquisicion distinta

        uint32_t    nroSecuencia;       // Nro. de secuencia que se incrementa en el envio y se controla en el receptor

        uint64_t    timeval_h;          // Estampa de tiempo de lectura del dato parte alta NOTA: modifique .h por _h
        uint64_t    timeval_l;          // Estampa de tiempo de lectura del dato parte baja NOTA: modifique .l por _l

        //uint8_t     reserved;          // Espacio Reservado (Size of Header fijo en 128 bytes)

        struct Reservado reservado;

        int32_t basura;                 // Basura

};

/** @brief Declaration of IQ Data structure of a pulse #VER XXX
 */
struct data{
        float _Complex V;
        float _Complex H;
};

/** Esttructura del nombre de archivo IQ
 *  RMA01_0202_20180907T143110_599Z_01_006_16.IQ
 */
struct fileName{
    char radar[5];
    char estrategia[5];
    char iniTime[50];
    char zeta[4];
    char volumen[2];
    char indice[3];
    char num[2];
    char *filepath;
};

#endif //IQ_STRUCTURES_H
