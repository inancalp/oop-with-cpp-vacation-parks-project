#include "_ParcController.h"
#include "_AccomodationController.h"


void saveParcFile(Parcs* parc)
{
	ofstream parcsFile(PARCSFILE, ios::out | ios::app);
	if (!parcsFile)
	{
		cout << "Error opening the file \"parcs.txt\"." << endl;
		return;
	}
	
	parcsFile << parc->getName() << " " << parc->getAddress() << endl;

	parcsFile.close();

	saveParcServicesFile(parc->getParcServices()); 

}

void saveParcServicesFile(ParcServices* parc_services)
{
	ofstream parcServicesFile(PARCSERVICESFILE, ios::out | ios::app);

	if (!parcServicesFile)
	{
		cout << "Error occured while opening parcs.txt file" << endl;
		return;
	}

	parcServicesFile <<
		parc_services->getParcName() << " " <<
		parc_services->getSubtropicSwimmingPool() << " " <<
		parc_services->getSportsInfrastructure() << " " <<
		parc_services->getBowlingAlley() << " " <<
		parc_services->getBicycleRent() << " " <<
		parc_services->getChildrensParadise() << " " <<
		parc_services->getWaterBikes() << endl;

	parcServicesFile.close();
}

void reWriteParcsFile(VacationParcs* vp)
{
	ofstream parcsFile(PARCSFILE, ios::out);

	if (!parcsFile)
	{
		cout << "Error occured while opening parcs.txt file" << endl;
		return;
	}

	emptyParcServicesFile();

	for (Parcs* parc : vp->getParcs())
	{
	/*	cout << "reWriteParcsFile() ->> Parcs::getName() ->> " << parc->getName() << " is being manipulated." << endl;*/
		parcsFile << parc->getName() << " " << parc->getAddress() << endl;
		saveParcServicesFile(parc->getParcServices());
	}

	parcsFile.close();

}

void emptyParcServicesFile()
{
	ofstream parcServicesFile(PARCSERVICESFILE, ios::out);

	if (!parcServicesFile)
	{
		cout << "Error occured while opening parcs.txt file" << endl;
		return;
	}

	parcServicesFile.close();
}

void retrieveParcsFile(VacationParcs* vp)
{
	string parc_name;
	string parc_address;

	ifstream parcsFile(PARCSFILE, ios::in);
	ifstream parcServicesFile(PARCSERVICESFILE, ios::in);

	if (!parcsFile)
	{
		cout << "Error occured while opening parcs.txt file" << endl;
		return;
	}

	while (parcsFile >> parc_name >> parc_address)
	{
		vp->setParc(new Parcs(parc_name, parc_address, retrieveParcServicesFile(parcServicesFile)));
	}
	parcServicesFile.close();
	parcsFile.close();
}

ParcServices* retrieveParcServicesFile(ifstream& parcServicesFile)
{
	array<bool, PARCSERVICESSIZE> parc_services;
	bool parc_service_value;
	string parc_name;

	parcServicesFile >> parc_name;

	for (size_t i{ 0 }; i < PARCSERVICESSIZE; i++)
	{
		parcServicesFile >> parc_service_value;
		parc_services[i] = parc_service_value;
	}

	return new ParcServices(
		parc_name,
		parc_services[0],
		parc_services[1],
		parc_services[2],
		parc_services[3],
		parc_services[4],
		parc_services[5]
	);
}

//Parcs CRUD
void createParc(VacationParcs* vp)
{
	string parc_name;
	string parc_address;
	ParcServices* parc_services;
	Parcs* parc;
	bool parc_created;
	bool parc_name_taken;
	bool parc_address_taken;

	parc_name.clear();
	parc_address.clear();
	parc_services = NULL; //(?)
	parc = NULL;
	parc_created = false;
	parc_name_taken = false;
	parc_address_taken = false;

	while (parc_created == false)
	{
		do
		{
			cout << "Parc Name: ";
			cin >> parc_name;
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			for (size_t i{ 0 }; i < vp->getParcs().size(); i++)
			{
				if (vp->getParcs()[i]->getName() == parc_name)
				{
					cout << "Parc Name is already in use, please try another one." << endl;
					parc_name_taken = true;
					break;
				}
				else
				{
					parc_name_taken = false;
				}
			}

		} while (parc_name_taken);

		do
		{
			cout << "Parc Address: ";
			cin >> parc_address;
			if (cin.eof())
			{
				cin.clear();
				return;
			}
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			for (size_t i{ 0 }; i < vp->getParcs().size(); i++)
			{
				if (vp->getParcs()[i]->getAddress() == parc_address)
				{
					cout << "Parc Address is already in use, please try another one." << endl;
					parc_address_taken = true;
					break;
				}
				else
				{
					parc_address_taken = false;
				}
			}
		} while (parc_address_taken);

		if (parc_name_taken == false && parc_address_taken == false) {
			parc_created = true;
		}
	}
	parc_services = createParcServices(parc_name);
	if (cin.eof())
	{
		cin.clear();
		return;
	}

	parc = new Parcs(parc_name, parc_address, parc_services);
	saveParcFile(parc);
	vp->setParc(parc);

	cout << parc->toString() << endl;
	cout << "-------------------" << endl;
	cout << "End of createParc()" << endl;
	cout << "-------------------" << endl;
}

void showParcs(VacationParcs* vp)
{
	cout << endl;
	cout << "------------------------------------------------------------ " << endl;
	cout << "Parcs included in the system of VacationParcs::getName() ->> " << vp->getName() << endl;
	cout << "------------------------------------------------------------ " << endl << endl;
	if (vp->getParcs().size() == 0)
	{
		cout << "-------------------------------" << endl;
		cout << "(!) There are no parcs to show." << endl;
		cout << "-------------------------------" << endl;
		return;
	}

	for (size_t i{ 0 }; i < vp->getParcs().size(); i++)
	{
		cout << " ->>";
		cout << vp->getParcs()[i]->toString();
	}
}

void modifyParc(VacationParcs* vp)
{
	char service_num;
	Parcs* selected_parc;
	ParcServices* selected_services;
	bool subtropic_swimming_pool_val;
	bool sports_infrastructure_val;
	bool bowling_alley_val;
	bool bicycle_rent_val;
	bool childrens_paradise_val;
	bool water_bikes_val;
	
	selected_parc = selectParc(vp);
	if (cin.eof())
	{
		cin.clear();
		return;
	}
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}


	//(!)update: if any any accomodation included in the park has the isBooked as "true";
	//park can't be modified since it's kind of a construction which is not proper while there are guests in park (reputation--);
	for (size_t i{ 0 }; i < selected_parc->getAccomodations().size(); i++)
	{
		if (selected_parc->getAccomodations()[i]->getIsBooked() == true)
		{
			cout << "-----------------------------------------------------------------" << endl;
			cout << "(!) Parc can't be modified while there are bookings by customers." << endl;
			cout << "-----------------------------------------------------------------" << endl;
			return;
		}
	}


	selected_services = selected_parc->getParcServices(); //selected_services
	subtropic_swimming_pool_val = selected_services->getSubtropicSwimmingPool();
	sports_infrastructure_val = selected_services->getSportsInfrastructure();
	bowling_alley_val = selected_services->getBowlingAlley();
	bicycle_rent_val = selected_services->getBicycleRent();
	childrens_paradise_val = selected_services->getChildrensParadise();
	water_bikes_val = selected_services->getWaterBikes();

	cout << "ParcServices::toString() ->> " << endl;
	cout << selected_parc->toString() << endl;

	do
	{
		cout << "Enter the number for the service you would like to add or remove: ";
		cin >> service_num;

		if (cin.eof())
		{
			cout << "Updated Parc Object: " << endl;
			cout << selected_services->toString() << endl;
			cin.clear();
			reWriteParcsFile(vp); //user can exit only with using ^Z so save-point is here.
			return;
		}

		switch (service_num)
		{
		case '1':
			changeSelectedParcServiceMiddleware("SubtropicSwimmingPool", subtropic_swimming_pool_val);
			selected_services->setSubtropicSwimmingPool(subtropic_swimming_pool_val);
			break;
		case '2':
			changeSelectedParcServiceMiddleware("SportsInfrastructure", sports_infrastructure_val);
			selected_services->setSportsInfrastructure(sports_infrastructure_val);
			break;
		case '3':
			changeSelectedParcServiceMiddleware("BowlingAlley", bowling_alley_val);
			selected_services->setBowlingAlley(bowling_alley_val);
			break;
		case '4':
			changeSelectedParcServiceMiddleware("BicycleRent", bicycle_rent_val);
			selected_services->setBicycleRent(bicycle_rent_val);
			break;
		case '5':
			changeSelectedParcServiceMiddleware("ChildrensParadise", childrens_paradise_val);
			selected_services->setChildrensParadise(childrens_paradise_val);
			break;
		case '6':
			changeSelectedParcServiceMiddleware("WaterBikes", water_bikes_val);
			selected_services->setWaterBikes(water_bikes_val);
			break;
		default:
			cout << "Invalid input." << endl;
			break;
		}
	} while (true);
	reWriteParcsFile(vp); //but still..just in case
}

void deleteParc(VacationParcs* vp)
{
	string parc_name;
	int parc_index;
	bool parc_found{ false };
	char delete_parc;

	Parcs* selected_parc = selectParc(vp);
	if (cin.eof())
	{
		cin.clear();
		return;
	}
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	
	for (size_t i{ 0 }; i < selected_parc->getAccomodations().size(); i++)
	{
		if (selected_parc->getAccomodations()[i]->getIsBooked() == true)
		{
			cout << "----------------------------------------------------------------" << endl;
			cout << "(!) Parc can't be deleted while there are bookings by customers." << endl;
			cout << "----------------------------------------------------------------" << endl;
			return;
		}
	}

	cout << "Here is the information for the parc to be deleted: " << endl;
	cout << " ->>";
	cout << selected_parc->toString() << endl;

	do
	{
		cout << "If you are sure to delete it enter \"y\": ";
		cin >> delete_parc;
		if (cin.eof())
		{
			cin.clear();
			return;
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (!(delete_parc == 'y'))
		{
			cout << "Invalid input, please try again." << endl;
		}
	} while (!(delete_parc == 'y'));


	if (delete_parc == 'y')
	{
		for (int i{ 0 }; i < vp->getParcs().size(); i++)
		{
			if (vp->getParcs()[i]->getName() == selected_parc->getName())
			{
				parc_index = i;
				break;
			}
		}
		cout << selected_parc->getName() << " is deleted." << endl << endl;
		delete selected_parc;
		vp->getParcs().erase(vp->getParcs().begin() + parc_index);

		reWriteParcsFile(vp);
		reWriteAccomodationsFile(vp);
	}
}

Parcs* selectParc(VacationParcs* vp)
{
	string parc_name;
	int parc_index;
	bool parc_name_found;
	int i;

	do
	{
		parc_name.clear();
		parc_index = -1;
		parc_name_found = false;

		cout << "Please enter the \"name\" of the Parc: ";
		cin >> parc_name; 
		if (cin.eof())
		{
			return NULL;
		}
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		for (size_t i{0}; i < vp->getParcs().size(); i++)
		{
			if (vp->getParcs()[i]->getName() == parc_name)
			{
				parc_name_found = true;
				break;
			}
		}
		if (!parc_name_found)
		{
			cout << endl << "Invalid ParcName, please try again!" << endl;
		}

	} while (!parc_name_found);

	for (size_t i{ 0 }; i < vp->getParcs().size(); i++)
	{
		if (parc_name == vp->getParcs()[i]->getName())
		{
			parc_index = static_cast<int>(i);
			break;
		}
	}

	return vp->getParcs()[parc_index];
}

//createParcServices() included in createParc();
ParcServices* createParcServices(string& parc_name)
{
	char selected_option;
	cout << "Select Services included with the Parc. (y/n)" << endl;
	array<bool, PARCSERVICESSIZE> parc_services{};
	array<string, PARCSERVICESSIZE> parc_service_names = {
		"SubtropicSwimmingPool",
		"SportsInfrastructure",
		"BowlingAlley",
		"BicycleRent",
		"ChildrensParadise",
		"WaterBikes"
	};
	

	for (size_t i{ 0 }; i < parc_services.size(); i++)
	{
		selected_option = '\0';
		while (!selected_option)
		{
			cout << "-> " << parc_service_names[i] << ": " << right;
			cin >> selected_option;
			if (cin.eof())
			{
				return NULL;
			}
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				selected_option = '\0'; //
				continue;
			}

			switch (selected_option)
			{
			case 'y':
				parc_services[i] = true;
				break;
			case 'n':
				parc_services[i] = false;
				break;
			default:
				cout << "Invalid input." << endl;
				selected_option = '\0';
				break;
			}
		}
	}
	//do update in case PARCSERVICESSIZE changes.
	return new ParcServices(parc_name, parc_services[0], parc_services[1], parc_services[2], parc_services[3], parc_services[4], parc_services[5]);

}

void changeSelectedParcServiceMiddleware(string data_name, bool& data)
{
	cout << "--------------" << endl;
	cout
		<< data_name
		<< " has change from \""
		<< boolalpha << data
		<< "\" to \"" << !data
		<< "\"."
		<< endl;
	cout << "--------------" << endl;
	data = !data;
}