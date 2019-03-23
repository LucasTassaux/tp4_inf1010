/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#include "PlatBioVege.h"

PlatBioVege::PlatBioVege(string nom, double prix, double cout, double ecotaxe, double vitamines, double proteines, double mineraux) : PlatBio(nom, prix, cout, ecotaxe), Vege(nom, vitamines, proteines, mineraux) 
{ 
}
PlatBioVege:: ~PlatBioVege(){}

//TODO
void PlatBioVege::afficherPlat(ostream & os) const
{   
	PlatBio::afficherPlat(os);
	os << "ET ";
	Vege::afficherVege(os);

}

Plat * PlatBioVege::clone() const
{ 
	Plat* plat = new PlatBioVege(*this);
	return plat;
}

double PlatBioVege::calculerApportNutritif() const
{
	double apport = (vitamines_*proteines_ / mineraux_)*RAPPORT_NUTRITIF_BIO*AVANTAGE_SANS_PESTICIDE;
	return apport;
}
