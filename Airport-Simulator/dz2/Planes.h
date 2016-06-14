#pragma once


class Plane
{
	std::string model_name;
	int passengers_max_count, passengers_count, average_speed, fuel_consumption, tank_volume, baggage_count, fuel_quantity;
public:
	Plane() : model_name("default_plane"), passengers_max_count(100), passengers_count(0), average_speed(500), fuel_consumption(100), tank_volume(10000), baggage_count(0), fuel_quantity(0) { }
	Plane(std::string _model_name, int _passengers_max_count, int _average_speed, int _fuel_consumption, int _tank_volume) : model_name(_model_name), passengers_max_count(_passengers_max_count), passengers_count(0), average_speed(_average_speed), fuel_consumption(_fuel_consumption), tank_volume(_tank_volume), baggage_count(0), fuel_quantity(0) { }
	Plane(const Plane & other) : model_name(other.model_name), passengers_max_count(other.passengers_max_count), passengers_count(other.passengers_count), average_speed(other.average_speed), fuel_consumption(other.fuel_consumption), tank_volume(other.fuel_consumption), baggage_count(other.baggage_count), fuel_quantity(other.fuel_quantity) { }

	void refuel(int _fuel_quantity)
	{
		if (_fuel_quantity < tank_volume)
			fuel_quantity = _fuel_quantity;
		else
		{
			fuel_quantity = tank_volume;
			throw "Tank is full\n";
		}
	}

	std::string get_model_name()
	{
		return model_name;
	}

	void boarding(int _passengers_count, int _baggage_count)
	{
		if ((_passengers_count < passengers_max_count) && (_baggage_count / 3 < passengers_max_count))
		{
			passengers_count = _passengers_count;
			baggage_count = _baggage_count;
		}
		else
		{
			passengers_count = passengers_max_count;
			baggage_count = _baggage_count / 3;
			throw "Plane is out of place\n";
		}
	}

	int duration(int km)
	{
		int duration = (km / average_speed);
		if (fuel_consumption * duration > tank_volume)
		{
			std::cout << "Too long duration\n";
			return 0;
		}
		else return duration;
	}

	std::string fly()
	{if (fuel_quantity == 0)
			throw "Refuel tank!!\n";
		if ((passengers_count == 0) || (baggage_count == 0))
			throw "You have forgotten something!\n";
		std::string all("Flight began\n Log: \n"), Passenger = "Passenger went bad!\n",
			Electronics = "Electronics problem solved!\n",
			Turbulence = "High turbulence!\n",
			OK = "All systems are ok!\n",
			Critical = "Critical problem!\n";
		srand(time(0));
		for (int i = 0; i < 10; i++)
			switch (rand() % 10)
			{
			case 1:
				all += Passenger;
				if (rand() % 10 == 2)
				{
					landing();
					all += "Plane landed in the nearest airport\n";
					return all;
				}
				all += "Doctors helped\n";
				break;
			case 2:
				all += Electronics;
				break;
			case 3:
				all += Turbulence;
				break;
			case 4:
				all += Turbulence;
				break;
			case 5:
				all += Electronics;
				break;
			case 6:
				all += Electronics;
				break;
			case 7:
				all += Turbulence;
				break;
			case 8:
				all += Turbulence;
				break;
			case 9:
				if (rand() % 10 == 2)
				{
					all += Critical;
					landing();
					return all;
				}
			default:
				all += OK;
				break;
			}
		return all + "End of flight\n";
	}

	void landing()
	{
		passengers_count = 0;
		baggage_count = 0;
		fuel_quantity = 0;
	}

	std::string info()
	{
		char * passengers_max_count_ = new char [1000], * passengers_count_ = new char[1000], * average_speed_ = new char[1000], * fuel_consumption_ = new char[1000], * tank_volume_ = new char[1000], * baggage_count_ = new char[1000], * fuel_quantity_ = new char[1000];
		_itoa(passengers_max_count, passengers_max_count_, 10);
		_itoa(passengers_count, passengers_count_, 10);
		_itoa(average_speed, average_speed_, 10);
		_itoa(fuel_consumption, fuel_consumption_, 10);
		_itoa(tank_volume, tank_volume_, 10);
		_itoa(baggage_count, baggage_count_, 10);
		_itoa(fuel_quantity, fuel_quantity_, 10);

		std::string a = "Model name: " + model_name + "\nMaximum number of passengers: " + passengers_max_count_ + "\nNumber of passengers: " + passengers_count_ + "\nMaximum number of luggage: " + baggage_count_ + "\nAverage speed: " + average_speed_ + "\nFuel consumption: " + fuel_consumption_ + "\nTank volume: " + tank_volume_ + "\nFuel quantity: " + fuel_quantity_;
		return a;
	}

	~Plane()
	{ }


};
