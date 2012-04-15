//Classe qui se charge de d'effectuer les opérations des boutons

//#include "libsdl.h"
#include <iostream>
#include <fstream>
#include "interpoApp.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
namespace interpo
{

interpoApp::interpoApp()
{
    ptI =NULL;
//pt =NULL;
}

interpoApp::~interpoApp() {}

Val* interpoApp::openFile() //charge les valeur dans struct Val pt[]
{
    char buff[40];
    FILE* pFile = fopen("./HGN200mg.txt", "r");
    if (!pFile) {
        cerr << "Impossible d'ouvrir le fichier !" << endl;
        return NULL;
    }
    int c;
    fgets(buff,sizeof(buff),pFile);
    sscanf(buff,"%d",&nbVal);
    //pt = new Val[nbVal];
    int i,j;
    i=j=0;

    c =fgetc(pFile);
    do  // peut être un peu compliqué pour rien, mais cétait déjà pondu;
        // change le point pour une virgule puis stock double dans val[].y;
    {
        if(c == EOF) break;
        if (c == '\r' || c ==  '\n' || c == '\t') {
            buff[i]='\0';
            i=0;
            pt[j].x = (double)j;
            pt[j++].y = atof(buff);  /// hahaha :(...ben oui, pas sscanf :(
            c =fgetc(pFile);
            continue;
        }
        if(c == ',') {
            c = '.';
        }
        buff[i++]=c;
        c =fgetc(pFile);
    } while( c!=EOF);
    fclose(pFile);
    printf("\n");
    for(int i=0; i<nbVal; i++)
        //  printf("%d\t %f\n",i,pt[i].y);
        return pt;

}
void interpoApp::getVals()
{
    int i=0;
    while(i<50) {
        cout << pt[i].y << endl;
        i++;
    }
}
Val* interpoApp::setInterval(const Val* start,const double pas)
//retourne un vecteur contenant toutes les valeur interpolé
{
    int nb= 1/pas;
    ptI = new Val[nb];
    int i=0;
    Val ptInf,ptSupp;
    ptInf.y= start->y;
    ptInf.x=start->x;

    start++;
    ptSupp.y= start->y;
    ptSupp.x= start->x;

    double d=start->x;

    for(d=start->x,i=0; i<nb; i++,d=d+pas) { // prépare les valeur de X interpolé
        ptI[i].x=d;
    }


    for(i=0; i<pas; i++) { //trouve les 10 valeurs de Y
        ptI[i].y= ptInf.y + ((ptSupp.y-ptInf.y)/(ptSupp.x-ptInf.x))*(ptI[i].x-ptInf.x);

    }
    return ptI;
}

int     interpoApp::getNbVals()
{
    return nbVal;
}
}

