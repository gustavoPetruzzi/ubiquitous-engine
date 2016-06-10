#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peliculas.h"
#include "directores.h"
#include "ArrayList.h"
#include "input.h"
#define MAX_DIRECTOR 10

int datosPeliculas(ArrayList* pListPeliculas, ArrayList* pListDirectores ,char* titulo, int* anio, char* nacionalidad, int* director, int* id, int pedirId)
{
    int returnAux = -1;
    int auxInt;
    char auxTitulo[50];
    int auxAnio;
    char auxNacionalidad[30];
    int auxDirector[10];
    int auxId;
    int i, j;
    int cantidadDirectores;
    ePelicula* auxPelicula = NULL;
    eDirector* pDirector;
    if(pListPeliculas != NULL && pListDirectores !=NULL && (!pListDirectores->isEmpty(pListDirectores) && titulo !=NULL && anio != NULL && nacionalidad != NULL && director != NULL && id != NULL))
    {
        for(i=0;i<10;i++)
        {
            auxDirector[i] = -1;
        }
        do
        {
            auxInt = getStringSpace(auxTitulo, "Ingrese el titulo de la pelicula: ", "ERROR: maximo 50 caracteres", 0, 51);
        }while(auxInt!=0);
        strcpy(titulo, auxTitulo);

        do
        {
            auxInt = getInt(&auxAnio, "Ingrese el anio de la pelicula: ", "ERROR: minino 1890 maximo 2016", 1889, 2017);
        }while(auxInt!=0);
        *anio = auxAnio;
        do
        {
            auxInt = getString(auxNacionalidad, "Ingrese la nacionalidad de la pelicula: ", "ERROR: maximo 30 caracteres", 0, 31);
        }while(auxInt!=0);
        strcpy(nacionalidad, auxNacionalidad);
        if(pedirId)
        {
            do
            {
                auxInt = getInt(&auxId, "Ingrese el id: ", "ERROR: solamente numeros", 0, 1000);
                if(auxInt== 0)
                {
                    if(pListPeliculas->size > 0)
                    {
                        for(i= 0; i<pListPeliculas->size-1; i++)
                        {
                            auxPelicula = al_get(pListPeliculas, i);
                            if(auxPelicula->id == auxId)
                            {
                                auxInt = -1;
                                printf("Ya existe una pelicula  con ese ID!");
                                break;
                            }
                        }
                    }
                }

            }while(auxInt!=0);
            *id = auxId;
        }

        do
        {
            auxInt = getInt(&cantidadDirectores, "Ingrese la cantidad de directores que quiere tiene la pelicula: ", "ERROR: maximo 10",0, 11);
            if(auxInt == 0 && cantidadDirectores<= pListDirectores->size)
            {
                for(i = 0; i<cantidadDirectores; i++)
                {
                    do
                    {
                        auxInt = getInt(&auxDirector[i], "Ingrese el id del director: ", "solamente numeros", 0, 1000);
                        pDirector = getDirector(pListDirectores, auxDirector[i]);
                        if(pDirector == NULL )
                        {
                            printf("Ese director no esta cargado!\n");
                            auxInt = -1;
                        }
                        for(j=0;j<MAX_DIRECTOR;j++)
                        {
                            if(i != j)
                                if(auxDirector[i] == auxDirector[j])
                                {
                                    printf("Ya se ha cargado ese director en esta pelicula!");
                                    auxInt = -1;
                                    break;
                                }
                        }
                    }while(auxInt !=0);

                }

                    for(i= 0; i<10;i++)
                    {
                        *(director+i) = auxDirector[i];
                    }

            }
            else
            {
                printf("No hay tantos directores cargados!");
                auxInt = -1;
            }

        }while(auxInt!=0);



        returnAux = 0;

    }
    return returnAux;

}

ePelicula* nuevaPelicula(char* titulo, int* anio, char* nacionalidad, int* director, int* id)
{
    ePelicula* pelicula = malloc(sizeof(ePelicula));
    int i;
    if(pelicula !=NULL)
    {
        strcpy(pelicula->titulo, titulo);
        pelicula->anio = *anio;
        strcpy(pelicula->nacionalidad, nacionalidad);

        for( i = 0; i< MAX_DIRECTOR; i++)
        {
            pelicula->director[i] = director[i];
        }

        pelicula->id = *id;
    }
    return pelicula;
}

int agregarPelicula(ArrayList* pListPeliculas, ArrayList* pListDirectores)
{
    int returnAux = -1;
    char titulo[50];
    int anio;
    char nacionalidad[30];
    int director[10];
    int id;
    ePelicula* pelicula;
    int auxInt;
    if(pListPeliculas != NULL && pListDirectores != NULL && (!pListDirectores->isEmpty(pListDirectores))  )
    {
        returnAux = 0;
        auxInt = datosPeliculas(pListPeliculas, pListDirectores, titulo, &anio, nacionalidad,director, &id, 1);
        if(auxInt== 0)
        {
            pelicula = nuevaPelicula(titulo, &anio, nacionalidad, director, &id);
            if(pelicula != NULL)
            {
                pListPeliculas->add(pListPeliculas, pelicula);
            }
        }
    }
    else if(pListDirectores->size <=0)
    {
        printf("No hay directores cargados");
    }
    return returnAux;

}


void printArrayPeliculas(ArrayList* pListPelicula, ArrayList* pListDirector)
{
    ePelicula* pelicula;
    eDirector* director;
    int i,j, auxInt;
    //int indexDirector;
    if(pListDirector != NULL && pListPelicula != NULL && (!pListPelicula->isEmpty(pListPelicula)))
    {
        printf("-----Listado de peliculas ordenado-----\n");
        for(i=0;i<pListPelicula->size;i++)
        {
            pelicula = al_get(pListPelicula, i);
            printf("\nPelicula : %s \nNacionalidad: %s\nanio: %d\nid: %d\n", pelicula->titulo, pelicula->nacionalidad, pelicula->anio, pelicula->id);
            printf("Dirigida por:\n");

            for(j=0;j<MAX_DIRECTOR;j++)
            {
                if(pelicula->director[j] != -1)
                {
                    director = getDirector(pListDirector, pelicula->director[j]);
                    if(director != NULL)
                    {
                        printf("%s\n", director->nombre);
                    }
                    else
                    {
                        printf("Director borrado/Inexistente");
                    }
                }

            }
        }
        printf("-----Cantidad total de peliculas %d-----\n", auxInt = al_len(pListPelicula));
    }
}
int buscarIndexPelicula(ArrayList* pListPeliculas, int id)
{
    int i;
    int returnAux = -1;
    ePelicula* pPelicula;
    if(pListPeliculas!=NULL && id > 0)
    {
        for(i = 0; i<pListPeliculas->size; i++)
        {
            pPelicula = al_get(pListPeliculas, i);
            if(pPelicula->id == id)
            {
                returnAux = i;
            }
        }
    }
    return returnAux;
}
int modificarPelicula(ArrayList* pListPeliculas, ArrayList* pListDirectores)
{
    int returnAux = -1;
    char titulo[50];
    int anio;
    char nacionalidad[30];
    int director[10];
    int index,id;
    ePelicula* pelicula;
    int auxInt;
    if(pListPeliculas != NULL && pListDirectores != NULL && (!pListPeliculas->isEmpty(pListPeliculas)))
    {
        returnAux = 0;

        do
        {
            auxInt = getInt(&id, "Ingrese id pelicula: ", "error: valido entre 1 y 1000",0, 1001);
        }while(auxInt!=0);

        index = buscarIndexPelicula(pListPeliculas, id);
        if(index != -1)
        {
            auxInt = datosPeliculas(pListPeliculas, pListDirectores, titulo, &anio, nacionalidad,director, &id, 0);
            if(auxInt== 0)
            {
                pelicula = nuevaPelicula(titulo, &anio, nacionalidad, director, &id);
                pListPeliculas->set(pListPeliculas,index, pelicula);
            }
        }
        else
        {
            printf("no existe ninguna pelicula con ese id");
            returnAux = -1;
        }

    }
    else if(pListPeliculas->size <= 0)
    {
        printf("No se ha ingresado ninguna pelicula");
        returnAux = -1;

    }
    return returnAux;
}
ArrayList* borrarPelicula(ArrayList* pListPeliculas)
{
    int index;
    int auxInt;
    int id;
    char opcion;
    ePelicula *pPelicula;
    ArrayList* backup;
    if(pListPeliculas != NULL && (!pListPeliculas->isEmpty(pListPeliculas)))
    {
        opcion = mostrarMenu("1.BORRAR PELICULA\n2.BORRAR PELICULAS\n", '1', '2');
        switch(opcion)
        {
            case '1':
                do
                {
                    auxInt = getInt(&id, "Ingrese id pelicula: ", "error: valido entre 1 y 1000",0, 1001);
                }while(auxInt!=0);

                index = buscarIndexPelicula(pListPeliculas, id);
                if(index != -1)
                {
                    backup = al_clone(pListPeliculas);
                    pPelicula = al_pop(pListPeliculas, index);
                    printf("Pelicula borrada:\n");
                    printf("Nombre: %s\nAnio: %d\nId: %d", pPelicula->titulo,pPelicula->anio,pPelicula->id);
                }
                else if( pListPeliculas->isEmpty(pListPeliculas))
                {
                    printf("No se ha ingresado ninguna pelicula");
                }
                break;
            case '2':
                auxInt = siOno(&opcion, "Desea borrar todas las peliculas? s/n\n", "ingrese 's' o 'n'", 's', 'n');
                if(opcion == 's')
                {
                    backup = al_clone(pListPeliculas);
                    pListPeliculas->clear(pListPeliculas);
                }
                break;
        }
    }
    else if( pListPeliculas->isEmpty(pListPeliculas))
    {
        printf("No hay peliculas cargadas para borrar!");
    }

    return backup;
}


int compararPeliculas(void* pPeliculaA,void* pPeliculaB)
{
    int auxInt;
    ePelicula *aux, *aux1;
    aux = (ePelicula*)pPeliculaA;
    aux1 = (ePelicula*) pPeliculaB;

    auxInt = strcmp(aux1->titulo, aux->titulo);

    if(auxInt == 0)
    {
        if(aux->anio > aux1->anio)
        {
            auxInt = 1;
        }
        else if(aux->anio < aux1->anio)
        {
            auxInt = -1;
        }
        else
        {
            auxInt = 0;
        }
    }
    return auxInt;
}

ArrayList* recuperarDatos(ArrayList* pList ,ArrayList* pListRecupero )
{
    int auxInt;
    ArrayList* returnAux;
    if(pList != NULL && pListRecupero != NULL)
    {
        auxInt = al_containsAll(pList, pListRecupero);
        if(auxInt != -1)
        {
            returnAux = al_clone(pListRecupero);
            if(pList != NULL)
            {
                pList->deleteArrayList(pList);
            }
        }
    }
    return returnAux;
}
/*
int listar(ArrayList* pListPeliculas, ArrayList* pListDirectores)
{

}
*/

