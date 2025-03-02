#ifndef VACATIONPARCS_H
#define VACATIONPARCS_H
#include "Customer.h"
#include "Parcs.h" 
#include "Booking.h"

class VacationParcs
{
private:
	string m_name;
	string m_address;
	string m_vat;
	vector<Parcs*> m_parcs;
	vector<Customer*> m_customers;
	vector<Booking*> m_bookings;
	vector<LuxuryLevel*> m_luxuryLevels;
public:
	VacationParcs(string name, string address, string vat);
	~VacationParcs();
	const string& getName() const;
	const string& getAddress() const;
	const string& getVat() const;
	vector<Parcs*>& getParcs();
	vector<Customer*>& getCustomers();
	vector<Booking*>& getBookings();
	vector<LuxuryLevel*>& getLuxuryLevels();
	void setName(const string& name);
	void setAddress(const string& address);
	void setVat(const string& vat);
	void setParc(Parcs* parc);
	void setCustomer(Customer* customer);
	void setBooking(Booking* booking);
	void setLuxuryLevel(LuxuryLevel* luxury_level);
	string toString();
};

#endif

