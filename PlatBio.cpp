/*
* Date : 25 février 2019
* Auteur : AbdeB
*/
#include "PlatBio.h"

PlatBio::PlatBio(string nom, double prix, double cout, double ecotaxe): Plat(nom, prix, cout), ecoTaxe_(ecotaxe){}


PlatBio::~ PlatBio(){}

double PlatBio::getEcoTaxe() const
{
	return ecoTaxe_;
}

void PlatBio::setEcoTaxe(double ecoTaxe)
{
	ecoTaxe_ = ecoTaxe;
}


Plat * PlatBio:: clone () const
{
	Plat* plat =  new PlatBio(*this);
	return plat;
}
double PlatBio::getPrixDeRevient()
{
	double prixDeRevient = prix_ - cout_ + ecoTaxe_;
	return prixDeRevient;
}

void PlatBio::afficherPlat(ostream& os) const
{
	 Plat::afficherPlat(os);
	 os << "Plat Bio  comprend une taxe écologique de :" << ecoTaxe_ << endl;
}
