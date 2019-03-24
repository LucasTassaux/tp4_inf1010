/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#include "PlatVege.h"


//TODO
PlatVege::PlatVege(string nom, double prix, double cout, double vitamines, double proteines, double mineraux): Plat(nom, prix, cout), Vege(nom, vitamines, proteines, mineraux)
{
	setTaxe();
}
PlatVege::~ PlatVege(){}

Plat* PlatVege::clone()const
{ 
	Plat* plat = new PlatVege(*this);
	return plat;
}


void PlatVege::afficherPlat(ostream & os) const
{
	Plat::afficherPlat(os);
	Vege::afficherVege(os);
}

double PlatVege::calculerApportNutritif() const
{
	double apport = (vitamines_*proteines_ / mineraux_)*RAPPORT_NUTRITIF;
	return apport;
}
double PlatVege::getTaxe() const
{
	return taxe_;
}
void PlatVege::setTaxe()
{
	taxe_ = 0.07;
}