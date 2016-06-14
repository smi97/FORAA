#pragma once

#include "resource.h"

std::vector<Plane> get_planes()
{
	std::vector<Plane> plane;
	int passengers_max_count = 111, average_speed = 111, fuel_consumption = 111, tank_volume = 111;
	int a = 0, i = 0;
	std::string buff;
	std::string model_name;

	std::ifstream file("ADB.txt");
	while (file >> model_name)
	{
		file >> buff;
		model_name += " " + buff;
		while (a < 4)
		{
			file >> buff;
			switch (a)
			{
			case 0:
				passengers_max_count = atoi(buff.c_str());
				break;
			case 1:
				average_speed = atoi(buff.c_str());
				break;
			case 2:
				fuel_consumption = atoi(buff.c_str());
				break;
			case 3:
				tank_volume = atoi(buff.c_str());
				break;
			}
			a++;
		}
		a = 0;
		
		plane.push_back(Plane(model_name, passengers_max_count, average_speed, fuel_consumption, tank_volume));
		i++;
	}
	file.close();

	return plane;
}

std::vector<AirportInsideWorker> get_inside_workers()
{
	int a = 0, i = 0;
	int age, salary, experience, level;
	std::string buff;
	std::string name;
	std::vector<AirportInsideWorker> InWorker;

	std::ifstream file("IWDB.txt");
	while (file >> name)
	{
		file >> buff;
		name += " " + buff;
		while (a < 4)
		{
			file >> buff;
			switch (a)
			{
			case 0:
				age = atoi(buff.c_str());
				break;
			case 1:
				salary = atoi(buff.c_str());
				break;
			case 2:
				experience = atoi(buff.c_str());
				break;
			case 3:
				level = atoi(buff.c_str());
				break;
			}
			a++;
		}
		a = 0;
		InWorker.push_back( AirportInsideWorker(age, salary, experience, level, name));
		i++;
	}
	file.close();

	return InWorker;
}


std::vector<AirportOutsideWorker> get_outside_workers()
{
	int a = 0, i = 0;
	int age, salary, experience, level;
	std::string buff;
	std::string name;
	std::vector<AirportOutsideWorker> OutWorker;


	std::ifstream file("OWDB.txt");
	while (file >> name)
	{
		file >> buff;
		name +=  " " + buff;
		while (a < 4)
		{
			file >> buff;
			switch (a)
			{
			case 0:
				age = atoi(buff.c_str());
				break;
			case 1:
				salary = atoi(buff.c_str());
				break;
			case 2:
				experience = atoi(buff.c_str());
				break;
			case 3:
				level = atoi(buff.c_str());
				break;
			}
			a++;
		}
		a = 0;
		OutWorker.push_back( AirportOutsideWorker(age, salary, experience, level, name));
		i++;
	}


	file.close();

	return OutWorker;
}