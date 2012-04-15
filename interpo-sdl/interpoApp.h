//Classe qui se charge de d'effectuer les opérations des boutons

#ifndef INTERPOAPP_H
#define INTERPOAPP_H
//#include "libsdl.h"
#include <string>
namespace interpo{

typedef struct {
	double y;
	double x;
}Val;



using namespace std;

class interpoApp{
    protected:
        int nbVal;


	public:
        interpoApp();
        ~interpoApp();
		Val*        openFile();
		void        getVals();

		Val*        setInterval(const Val *Pt,const double pas);
        int         getNbVals();
    private:
//        double  ptInf; // point Y inférieur;
//        double  ptSupp; //point Y supp;


        //Val     ptI[10]; //valeurs interpolés entre 2 points
       // Val     pt[100]; //Valeur charger du fichier
        Val    pt[60];  ///javais un bug avec le pointeur
        Val*    ptI;



};
//char *interpoApp::file = "./HGN200mg.txt";
}
#endif //INTERPOAPP_H
