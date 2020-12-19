/**
 * @file alumnos.c
 * @brief Módulo que implementa las funciones...
 * @author --------
 * @date 19/12/2020
*/
 
/*=====[Inclusion of own header]=============================================*/

#include "alumnos.h"
#include <stdio.h>
#include <string.h>

/*=====[Inclusions of private function dependencies]=========================*/

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

static const struct alumno_s ESTEBAN_VOLENTINI = {
    .apellidos = "VOLENTINI",
    .nombres = "Esteban Daniel",
    .documento = "23.517.968",
};


static const struct alumno_s FERNANDO_TAJES = {
    .apellidos = "TAJES",
    .nombres = "Fernando",
    .documento = "3.864.221-4",
};

const alumno_t ALUMNOS[] = {
    &ESTEBAN_VOLENTINI,
    &FERNANDO_TAJES,
};

const int CANTIDAD_ALUMNOS = (sizeof(ALUMNOS) / sizeof(alumno_t));

/*=====[Definitions of private global variables]=============================*/

/*=====[Prototypes (declarations) of private functions]======================*/

/*=====[Implementations of public functions]=================================*/

/*=====[Implementations of interrupt functions]==============================*/

/**
 * @brief Función que serializa al alumno
*/
bool SerializarAlumno(char * cadena, size_t espacio, const alumno_t alumno) {
    int resultado;
    const char FORMATO[] = "{"
        "\"documento\":\"%s\","
        "\"apellidos\":\"%s\","
        "\"nombres\":\"%s\""
    "}";

    resultado = snprintf(cadena, espacio, FORMATO, 
             alumno->documento, alumno->apellidos, alumno->nombres);

    return (resultado >= 0);
}

/**
 * @brief Función que serializa a los alumnos
*/
bool SerializarAlumnos(char * cadena, size_t espacio) {
    static const int  cantidad = sizeof(ALUMNOS) / sizeof(alumno_t);
    int posicion = snprintf(cadena, espacio, "[\r\n  ");
    bool resultado = (posicion > 0);

    if (resultado){
        for(int indice = 0; indice < cantidad; indice++ ) {
            resultado = SerializarAlumno(&cadena[posicion], espacio - posicion, ALUMNOS[indice]);
            if (resultado) {
                posicion += strlen(&cadena[posicion]);
                posicion += snprintf(&cadena[posicion], espacio - posicion, ",\r\n  ");
            } else {
                break;
            }
        }
    }

    snprintf(&cadena[posicion] - 5, espacio - posicion + 5, "\r\n]");
    return resultado;
}

/*=====[Implementations of private functions]================================*/
