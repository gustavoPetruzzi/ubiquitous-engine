#include "ArrayList.h"
typedef struct{
    char nombre[50];
    char fechaNacimiento[11];
    char paisOrigen[50];
    int idDirector;
}eDirector;



void printArrayDirectores(ArrayList* pList);
eDirector* getDirector(ArrayList* pListDirector, int idDirector);
int datosDirectores(ArrayList* pListDirectores,char* nombre, char* fechaNacimiento,char* paisOrigen,int* idDirector);
eDirector* nuevoDirector(char* nombre, char* fechaNacimiento, char* paisOrigen, int* idDirector);
int agregarDirector(ArrayList* pListDirectores);
ArrayList* borrarDirector(ArrayList* pListDirectores);
