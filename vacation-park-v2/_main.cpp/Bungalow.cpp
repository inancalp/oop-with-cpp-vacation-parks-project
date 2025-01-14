#include "Bungalow.h"


Bungalow::Bungalow(
    const string parc_name,
    const int id,
    const int nbr_people,
    const int size,
    const bool bathroom_with_bath,
    const bool is_booked,
    LuxuryLevel* luxury_level,
    const int bedrooms
) : Accomodations(parc_name, id, nbr_people, size, bathroom_with_bath, is_booked, luxury_level), m_bedrooms(bedrooms) {
	cout << "(?) Bungalow::Constructor ->> " << this->getId() << " created." << endl;
}
Bungalow::~Bungalow() {
	cout << "(!) Bungalow::Destructor ->> " << this->getId() << " deleted." << endl;
};

const int& Bungalow::getBedrooms() const {
    return this->m_bedrooms;
}
void Bungalow::setBedrooms(const int bedrooms) {
    this->m_bedrooms = bedrooms;
}


string Bungalow::toString(){
    ostringstream output;
    output << "\t Bungalow::ParcName ->> " << this->getParcName() << endl;
    output << "\t\t Bungalow::ID ->> " << this->getId() << endl;
    output << "\t\t Bungalow::NbrPeople ->> " << this->getNbrPeople() << endl;
    output << "\t\t Bungalow::Size ->> " << this->getSize() << endl;
    output << "\t\t Bungalow::BathroomWithBath ->> " << boolalpha << this->getBathroomWithBath() << endl;
    output << "\t\t Bungalow::IsBooked ->> " << ((this->getIsBooked() == true) ? "State: Booked" : "State: Available") << endl;
    output << "\t\t Bungalow::LuxuryLevel ->> " << endl << this->getLuxuryLevel()->toString() << endl;
    output << "\t\t Bungalow::Bedrooms ->> " << this->getBedrooms() << endl << endl;

    return output.str();
}