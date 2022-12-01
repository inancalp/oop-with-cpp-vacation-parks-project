#include "Bungalow.h"


Bungalow::Bungalow(
    const int id,
    const int nbr_people,
    const int size,
    const bool bathroom_with_bath,
    const string luxury_level,
    const int bedrooms
) : Accomodations(id, nbr_people, size, bathroom_with_bath, luxury_level), m_bedrooms(bedrooms) {
	cout << "(!) Bungalow::Constructor" << endl;
}
Bungalow::~Bungalow() {
	cout << "(!) Bungalow::Destructor" << endl;
};

const int& Bungalow::getBedrooms() const {
    return this->m_bedrooms;
}
void Bungalow::setBedrooms(const int bedrooms) {
    this->m_bedrooms = bedrooms;
}


const string Bungalow::toString() const {
    ostringstream output;
    output << " Bungalow::ID -> " << this->getId() << endl;
    output << " Bungalow::NbrPeople -> " << this->getNbrPeople() << endl;
    output << " Bungalow::Size -> " << this->getSize() << endl;
    output << " Bungalow::BathroomWithBath -> " << this->getBathroomWithBath() << endl;
    output << " Bungalow::LuxuryLevel -> " << this->getLuxuryLevel() << endl;
    output << " Bungalow::Bedrooms -> " << this->getBedrooms() << endl;

    return output.str();
}