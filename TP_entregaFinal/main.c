#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "peliculas.h"
#include "directores.h"
#include "input.h"
void readMockDirector(ArrayList* pList);
void readPelicula(ArrayList* pList2);
int main()
{
    ArrayList* listPeliculas, *listDirectores,*auxPeliculas, *auxDirectores;
    ArrayList *backupDirectores = NULL;
    ArrayList *backupPeliculas = NULL;
    int auxInt;
    char opcion;
    listPeliculas = al_newArrayList();
    listDirectores = al_newArrayList();
    //backupDirectores = al_newArrayList();
    //backupPeliculas = al_newArrayList();

    readMockDirector(listDirectores);
    readPelicula(listPeliculas);
    if(listPeliculas != NULL && listDirectores != NULL)
    {
        do
        {
            opcion = mostrarMenu("1.ALTAS PELICULAS\n2.MODIFICAR PELICULA\n3.BAJA PELICULA\n4.NUEVO DIRECTOR\n5.ELIMINAR DIRECTOR\n6.RECUPERAR\n7.INFORMAR\n8.LISTAR\n9.SALIR\n", '1', '9');
            switch(opcion)
            {
                case '1':

                    auxInt = agregarPelicula(listPeliculas, listDirectores);
                    if(auxInt == 0)
                    {
                        printf("Pelicula agregada");
                    }
                    /*
                    printf("%d", listDirectores->size);
                    printf("\n");
                    printArrayDirectores(listDirectores);
                    printf("\n");
                    */
                    break;
                case '2':
                    auxInt = modificarPelicula(listPeliculas, listDirectores);
                    if(auxInt == 0)
                    {
                        printf("Pelicula modificada");
                    }
                    break;
                case '3':
                    backupPeliculas = borrarPelicula(listPeliculas);
                    break;
                case '4':
                    auxInt = agregarDirector(listDirectores);
                    if(auxInt == 0)
                    {
                        printf("Director cargado!");
                        printArrayDirectores(listDirectores);
                    }
                    break;
                case '5':
                    backupDirectores = borrarDirector(listDirectores);
                    if(backupDirectores != NULL)
                    {
                        printf("Director borrado");
                    }
                    break;
                case '6':
                    opcion = mostrarMenu("1.RECUPERAR PELICULAS\n2.RECUPERAR DIRECTORES\n", '1', '2');
                    switch(opcion)
                    {
                    case '1':
                        auxPeliculas = recuperarDatos(listPeliculas, backupPeliculas);
                        if(auxPeliculas == NULL)
                        {
                            printf("No se ha podido recuperar peliculas!\n");
                        }
                        else
                        {
                            printf("Peliculas recuperadas\n");
                            listPeliculas = al_clone(auxPeliculas);
                            auxPeliculas->deleteArrayList(auxPeliculas);
                        }
                        break;
                    case '2':

                        auxDirectores = recuperarDatos(listDirectores, backupDirectores);
                        if(auxDirectores == NULL)
                        {
                            printf("No se ha podido recuperar los directores\n");
                        }
                        else
                        {
                            printf("Directores recuperados\n");
                            listDirectores = al_clone(auxDirectores);
                            auxDirectores->deleteArrayList(auxDirectores);
                        }

                        break;
                    }
                    break;
                case '7':

                    break;
                case '8':

                    printf("DIRECTORES: \n");
                    printArrayDirectores(listDirectores);
                    listPeliculas->sort(listPeliculas, compararPeliculas, 1);
                    printArrayPeliculas(listPeliculas, listDirectores);


                    break;
                case '9':
                    listDirectores->deleteArrayList(listDirectores);
                    listPeliculas->deleteArrayList(listPeliculas);
                    break;
                default:
                    break;
            }
        }while(opcion!='9');
    }
    return 0;
}
void readMockDirector(ArrayList* pList)
{
    FILE* pArch;
    eDirector* pDirector;
    char nombre[50];
    char fecha[30];
    char paisOrigen[50];
    char auxIdDirector;

    pArch = fopen("MOCK_DATA.txt", "r");

    while(!(feof(pArch)))
    {
        pDirector = malloc(sizeof(eDirector));
        fscanf(pArch,"%[^,],%[^,],%[^,],%s\n", nombre, fecha, paisOrigen, &auxIdDirector);
        strcpy(pDirector->nombre, nombre);
        strcpy(pDirector->fechaNacimiento, fecha);
        strcpy(pDirector->paisOrigen, paisOrigen);
        pDirector->idDirector =atoi(&auxIdDirector);
        pList->add(pList, pDirector);
    }
    fclose(pArch);
}

void readPelicula(ArrayList* pList)
{
    FILE* pArch;
    ePelicula* pPelicula;
    char auxTitulo[50];
    char auxNacionalidad[50];


    char auxAnio[10];
    char auxId[10];
    char auxDirector[3];
    int auxInt;
    int i;
    pArch = fopen("MOCK_PELI.txt", "r");

    while(!(feof(pArch)))
    {
        pPelicula = malloc(sizeof(ePelicula));
        fscanf(pArch, "%[^,],%[^,],%[^,],%[^,],%s\n", auxTitulo, auxAnio, auxNacionalidad, auxDirector, auxId);
        for(i=0;i<10;i++)
        {
            pPelicula->director[i] = -1;
        }
        strcpy(pPelicula->titulo, auxTitulo);
        strcpy(pPelicula->nacionalidad, auxNacionalidad);
        pPelicula->anio = atoi(auxAnio);
        pPelicula->id = atoi(auxId);
        pPelicula->director[0] = atoi(auxDirector);

        auxInt = al_add(pList, pPelicula);
    }
    fclose(pArch);
}
