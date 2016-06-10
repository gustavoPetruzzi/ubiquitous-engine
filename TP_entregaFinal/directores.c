#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directores.h"
#include "input.h"
#include "ArrayList.h"

int datosDirectores(ArrayList* pListDirectores,char* nombre, char* fechaNacimiento,char* paisOrigen,int* idDirector)
{
    int auxInt, i;
    char auxNombre[50];
    char auxFechaNacimiento[11];
    char auxPaisOrigen[50];
    int auxIdDirector;
    int returnAux = -1;
    eDirector* pDirector;

    if(pListDirectores != NULL && nombre != NULL && fechaNacimiento != NULL && paisOrigen != NULL && idDirector != NULL)
    {
        returnAux = 0;
        do
        {
            auxInt = getInt(&auxIdDirector, "Ingrese el id del director: ", "error: id invalido", 0, 501);
            for(i = 0; i<pListDirectores->size; i++)
            {
                pDirector = al_get(pListDirectores, i);
                if(pDirector->idDirector == auxIdDirector)
                {
                    printf("Ya existe alguien con ese id!");
                    auxInt = -1;
                    break;
                }
            }
        }while(auxInt!= 0);
        *idDirector = auxIdDirector;
        do
        {
            auxInt = getName(auxNombre, "Ingrese el nombre del director: ", "error: maximo 50 caracteres", 0, 51);
            for(i=0;i<pListDirectores->size;i++)
            {
                pDirector = al_get(pListDirectores, i);
                if(strcmp(pDirector->nombre, auxNombre)== 0)
                {
                    printf("Ya existe alguien con ese nombre!");
                    auxInt = -1;
                    break;
                }
            }
        }while(auxInt!=0);
        strcpy(nombre, auxNombre);

        do
        {
            auxInt =getString(auxFechaNacimiento, "Ingrese la fecha de nacimiento: ", "error: ingrese fecha en formato dd/mm/aaaa", 0, 12);
        }while(auxInt!=0);
        strcpy(fechaNacimiento, auxFechaNacimiento);
        do
        {
            auxInt = getString(auxPaisOrigen, "Ingrese el pais de origen del director: ", "error: maximo 50 caracteres", 0, 51);
        }while(auxInt!=0);
        strcpy(paisOrigen, auxPaisOrigen);
    }
    return returnAux;
}
eDirector* nuevoDirector(char* nombre, char* fechaNacimiento, char* paisOrigen, int* idDirector)
{
    eDirector* pDirector = malloc(sizeof(eDirector));

    if(pDirector != NULL)
    {
        strcpy(pDirector->nombre, nombre);
        strcpy(pDirector->fechaNacimiento, fechaNacimiento);
        strcpy(pDirector->paisOrigen, paisOrigen);
        (pDirector->idDirector) = *idDirector;
    }
    return pDirector;
}

int agregarDirector(ArrayList* pListDirectores)
{
    int returnAux = -1;
    char auxNombre[50];
    char auxFechaNacimiento[12];
    char auxPaisOrigen[50];
    int auxIdDirector;
    int auxInt;
    eDirector* pDirector;
    if(pListDirectores != NULL)
    {
        returnAux = 0;
        auxInt = datosDirectores(pListDirectores, auxNombre, auxFechaNacimiento, auxPaisOrigen, &auxIdDirector);
        if(auxInt == 0)
        {
            pDirector = nuevoDirector(auxNombre, auxFechaNacimiento, auxPaisOrigen, &auxIdDirector);
            if(pDirector != NULL)
            {
                pListDirectores->add(pListDirectores, pDirector);
            }
        }
    }
    return returnAux;
}

void printArrayDirectores(ArrayList* pListDirectores)
{
    eDirector* pDirector;
    int i;
    if(pListDirectores != NULL && (!pListDirectores->isEmpty(pListDirectores)))
    printf("-----Cantidad total de directores: %d-----", pListDirectores->len(pListDirectores));
    for(i=0;i<pListDirectores->size;i++)
    {
        pDirector = al_get(pListDirectores, i);

        printf("\n");
        printf("%s %s %s %d\n", pDirector->nombre, pDirector->paisOrigen, pDirector->fechaNacimiento, pDirector->idDirector);


    }
}
eDirector* getDirector(ArrayList* pListDirector, int idDirector)
{
    eDirector* auxDirector = NULL;
    int i;
    int flagIsEmpty = 1;
    if(pListDirector != NULL && idDirector > 0)
    {
        for(i=0;i<pListDirector->size;i++)
        {
            auxDirector = al_get(pListDirector, i);
            if(auxDirector->idDirector == idDirector)
            {
                flagIsEmpty = 0;
                break;
            }
        }
        if(flagIsEmpty == 1)
        {
            auxDirector = NULL;
        }
    }
    return auxDirector;
}
ArrayList* borrarDirector(ArrayList* pListDirectores)
{
    int returnAux = -1;
    int auxInt, i;
    char auxNombre[50];
    eDirector* pDirector;
    ArrayList* backup;
    char respuesta;
    if(pListDirectores != NULL && (!pListDirectores->isEmpty(pListDirectores)))
    {
        do
        {
            auxInt = getName(auxNombre, "Ingrese el nombre del director a eliminar:", "ERROR: maximo 51 caracteres", 0, 51);
        }while(auxInt!=0);
        for(i=0;i<pListDirectores->size;i++)
        {
            pDirector = al_get(pListDirectores, i);
            if(strcmp(pDirector->nombre, auxNombre) == 0)
            {
                returnAux = 0;
                printf("nombre: %s\nid: %d\nFecha de nacimiento %s\nPais de origen: %s", pDirector->nombre, pDirector->idDirector, pDirector->fechaNacimiento, pDirector->paisOrigen);
                do
                {
                    auxInt = siOno(&respuesta, "Desea eliminarlo? s/n", "ERROR: ingrese 's' o 'n'", 's', 'n');
                }while(auxInt!=0);
                if(respuesta == 's')
                {
                    backup = al_clone(pListDirectores);
                    pListDirectores->remove(pListDirectores, i);
                }
                break;
            }

        }
        if(returnAux != 0)
        {
            printf("No existe ningun director con ese nombre!");
        }
    }
    return backup;
}


