#include "ArrayList.h"
//#include "directores.h"
typedef struct{
    char titulo[50];
    int anio;
    char nacionalidad[30];
    int director[10];
    int id;
}ePelicula;

int datosPeliculas(ArrayList* pListPeliculas, ArrayList* pListDirectores ,char* titulo, int* anio, char* nacionalidad, int* director, int* id, int pedirId);
ePelicula* nuevaPelicula(char* titulo, int* anio, char* nacionalidad, int* director, int* id);
int agregarPelicula(ArrayList* pListPeliculas, ArrayList* pListDirectores);
void printArrayPeliculas(ArrayList* pListPelicula, ArrayList* pListDirector);
int modificarPelicula(ArrayList* pListPeliculas, ArrayList* pListDirectores);
ArrayList* borrarPelicula(ArrayList* pListPeliculas);
int compararPeliculas(void* pPeliculaA,void* pPeliculaB);
ArrayList* recuperarDatos(ArrayList* pList ,ArrayList* pListRecupero );
