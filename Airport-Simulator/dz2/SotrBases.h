#pragma once
class Human
{
protected:
	int age, salary, experience;
	std::string name;
public:
	Human() : age(18), salary(0), experience(0), name(" No Name") { }
	Human(int _age, int _salary, int _experience, std::string _name) : age(_age), salary(_salary), experience(_experience), name(_name) { }
	std::string get_name() { return name; }

};

class AirportInsideWorker : public Human
{
	unsigned int level;
	std::string post;
public:
	AirportInsideWorker() : Human(19, 10000, 0, "No Name"), level(0), post(" ") { }
	AirportInsideWorker(int _age, int _salary, int _experience, int level, std::string _name) : Human(_age, _salary, _experience, _name)
	{
		switch (level)
		{
		case 1:
			post = "Trainee";
			break;
		case 2:
			post = "Low worker";
			break;
		case 3:
			post = "Economist";
			break;
		case 4:
			post = "Accountant";
			break;
		case 5:
			post = "Manager";
			break;

		}
	}

	std::string info()
	{
		char * age_ = new char[1000], *salary_ = new char[1000], *experience_ = new char[1000], *level_ = new char[1000];
		_itoa(age, age_, 10);
		_itoa(salary, salary_, 10);
		_itoa(experience, experience_, 10);
		_itoa(level, level_, 10);

		std::string a = "Name: " + name + "\nAge: " + age_ + "\nSalary: " + salary_ + "\nExperience: " + experience_ + "\nLevel: " + level_ + "\nPost: " + post;
		return a;
	}

	int getlevel()
	{
		std::cout << post << std::endl;
		return level;
	}

	void MakeBoarding(int _passengers_count, int _baggage_count, Plane * plane)
	{
		try
		{
			plane->boarding(_passengers_count, _baggage_count);
		}

		catch (const char * a)
		{
			std::cout << a;
		}
	}

	void fire() { salary = 0; }


};

class AirportOutsideWorker : public Human
{
	unsigned int level;
	std::string post;
public:
	AirportOutsideWorker() : Human(19, 10000, 0, "No Name") { }
	AirportOutsideWorker(int _age, int _salary, int _experience, int level, std::string _name) : Human(_age, _salary, _experience, _name)
	{
		switch (level)
		{
		case 1:
			post = "Trainee";
			break;
		case 2:
			post = "Car Driver";
			break;
		case 3:
			post = "Refueller";
			break;
		case 4:
			post = "Manager";
			break;
		}
	}

	std::string info()
	{
		char * age_ = new char[1000], *salary_ = new char[1000], *experience_ = new char[1000], *level_ = new char[1000];
		_itoa(age, age_, 10);
		_itoa(salary, salary_, 10);
		_itoa(experience, experience_, 10);
		_itoa(level, level_, 10);

		std::string a = "Name: " + name + "\nAge: " + age_ + "\nSalary: " + salary_ + "\nExperience: " + experience_ + "\nLevel: " + level_ + "\nPost: " + post;
		return a;
	}

	void PreparePlane(int _fuel_quantity, Plane * plane)
	{

		try
		{
			plane->refuel(_fuel_quantity);
		}

		catch (const char * a)
		{
			std::cout << a;
		}
	}



	void fire() { salary = 0; }


};

