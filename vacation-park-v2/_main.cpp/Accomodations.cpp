#include "Accomodations.h"

// LUXURY_LEVEL (!) change to class later
Accomodations::Accomodations
(
	const string parc_name,
	const int id,
	const int nbr_people,
	const int size,
	const bool bathroom_with_bath,
	const bool is_booked,
	LuxuryLevel* luxury_level //
)
	: m_parcName(parc_name), m_id(id), m_nbrPeople(nbr_people), m_size(size), m_bathroomWithBath(bathroom_with_bath), m_isBooked(is_booked), m_luxuryLevel(luxury_level)
{
	cout << "(?) Accomodations::Constructor ->> Accomodation with id[" << this->getId() << "] created." << endl;
}

Accomodations::~Accomodations() {

	// luxuryLevel can stay as an object when Acc. been deleted

	cout << "(!) Accomodations::Destructor ->> Accomodation with id[" << this->getId() << "] deleted." << endl;
};


const string& Accomodations::getParcName() const
{
	return this->m_parcName;
}

const int& Accomodations::getId() const
{
	return this->m_id;
}


const int& Accomodations::getNbrPeople() const
{
	return this->m_nbrPeople;
}


const int& Accomodations::getSize() const
{
	return this->m_size;
}


const bool& Accomodations::getBathroomWithBath() const
{
	return this->m_bathroomWithBath;
}

const bool& Accomodations::getIsBooked() const
{
	return this->m_isBooked;
}

//(?) no const, else can't pass it to saveLuxuryLevel() function as argument.
LuxuryLevel* Accomodations::getLuxuryLevel()
{
	return this->m_luxuryLevel;
}

void Accomodations::setParcName(const string& parc_name)
{
	this->m_parcName = parc_name;
}

void Accomodations::setId(const int& id)
{
	this->m_id = id;
}


void Accomodations::setNbrPeople(const int& nbr_people)
{
	this->m_nbrPeople = nbr_people;
}


void Accomodations::setSize(const int& size)
{
	this->m_size = size;
}


void Accomodations::setBathroomWithBath(const bool& bathroom_with_bath)
{
	this->m_bathroomWithBath = bathroom_with_bath;
}

void Accomodations::setIsBooked(const bool is_booked)
{
	this->m_isBooked = is_booked;
}

void Accomodations::setLuxuryLevel(LuxuryLevel* luxury_level)
{
	this->m_luxuryLevel = luxury_level;
}
