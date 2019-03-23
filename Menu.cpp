/*
* Date : 25 février 2019
* Auteur : AbdeB
*/

#include "Menu.h"
#include "LectureFichierEnSections.h"
#include <cassert>  //? Contient "assert" qui permet de s'assurer qu'une expression est vraie, et terminer le programme avec un message d'erreur en cas contraire.
using namespace std;

// Constructeurs.

Menu::Menu() :
	type_{TypeMenu::Matin}
{
}

Menu::Menu(string fichier, TypeMenu type) :
	type_{type}
{
	lireMenu(fichier); 
}

Menu::~Menu()
{
	for (unsigned int i = 0; i < listePlats_.size(); i++) {
		delete listePlats_[i];
	}
	
}

Plat* Menu::allouerPlat(Plat* plat) {
    return plat->clone();
}


Menu::Menu(const Menu & menu) : type_(menu.type_)
{
	
	for (unsigned int i = 0; i < menu.listePlats_.size(); i++) {
		*this += allouerPlat(menu.listePlats_[i]);
	}
	
}

Menu & Menu::operator=(const Menu & menu)
{
	if (this != &menu) {
		type_ = menu.type_;
		
		for (unsigned int j = 0; j < listePlats_.size(); j++) {
			delete listePlats_[j];
		}
		listePlats_.clear();

		for (unsigned int k = 0; k < listePlatsVege_.size(); k++) {
			delete listePlatsVege_[k];
		}
		listePlatsVege_.clear();

		for (unsigned int i = 0; i < menu.listePlats_.size(); i++) {
			*this += allouerPlat(menu.listePlats_[i]);
		}
	}
	return *this;
}

// Getters.

vector<Plat*> Menu::getListePlats() const
{
	return listePlats_;
}

// Autres methodes.

Menu& Menu::operator+=(owner<Plat*> plat) {
	listePlats_.push_back(plat);
	if (dynamic_cast<Vege*>(plat) != nullptr) {
		listePlatsVege_.push_back(dynamic_cast<Vege*>(plat));
	}
	return *this;
}

void Menu::lireMenu(const string& nomFichier) {
	LectureFichierEnSections fichier{nomFichier};
	fichier.allerASection(entetesDesTypesDeMenu[static_cast<int>(type_)]);
	while (!fichier.estFinSection())
		*this += lirePlatDe(fichier);
}

Plat* Menu::trouverPlatMoinsCher() const
{
	assert(!listePlats_.empty() && "La liste de plats de doit pas etre vide pour trouver le plat le moins cher.");
	Plat* minimum = listePlats_[0];
	for (Plat* plat : listePlats_)
		if (*plat < *minimum)
			minimum = plat;

	return minimum;
}

Plat* Menu::trouverPlat(string_view nom) const
{
	for (Plat* plat : listePlats_)
		if (plat->getNom() == nom)
			return plat; 

	return nullptr; 
}
Plat* Menu::lirePlatDe(LectureFichierEnSections& fichier)
{
    auto lectureLigne = fichier.lecteurDeLigne();
    
    string nom, typeStr;
    TypePlat type;
    double prix, coutDeRevient;
    lectureLigne >> nom >> typeStr >> prix >> coutDeRevient;
    type = TypePlat(stoi(typeStr));
    double ecotaxe, vitamines, proteines, mineraux;
    switch (type) {
        case TypePlat::Bio :
            lectureLigne >> ecotaxe;
            return new PlatBio{ nom, prix, coutDeRevient, ecotaxe };
        case TypePlat::BioVege:
            lectureLigne >> ecotaxe >> vitamines >> proteines >> mineraux;
            return new PlatBioVege(nom, prix, coutDeRevient, ecotaxe, vitamines, proteines, mineraux);
        case TypePlat::Vege:
            lectureLigne >> vitamines >> proteines >> mineraux;
            return new PlatVege(nom, prix, coutDeRevient, vitamines, proteines, mineraux);
        default:
            return new Plat{nom, prix, coutDeRevient};
    }
    
}

// Fonctions globales.

ostream& operator<<(ostream& os, const Menu& menu)
{
	os << "-------------Exemple de menu-------------" << endl;
	for (unsigned int i = 0; i < menu.listePlats_.size(); i++) {
		menu.listePlats_[i]->afficherPlat(os);
	}
	os << "-------------Menu entierement vegetarien-------------" << endl;
	for (unsigned int i = 0; i < menu.listePlatsVege_.size(); i++) {
		menu.listePlatsVege_[i]->afficherVege(os);
	}
	return os;
}
