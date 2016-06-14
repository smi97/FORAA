#pragma once
class Flight
{
	Plane * plane;
	int distance, duration;
	std::string destination;
public:
	Flight() : plane(nullptr), destination("nowhere"), distance(0) {}
	Flight(Plane * some_plane, std::string _destination, int distance) : plane(some_plane), destination(_destination), distance(distance)
	{
		try
		{
			duration = plane->duration(distance);
		}
		catch (const char * a)
		{
			throw;
		}
	}
	
	std::string MakeFlight()
	{
		try
		{
			std::string log = plane->fly();
			plane->landing();
			return log;
		}
		catch (const char * a)
		{
			throw;
		}
		catch (...)
		{
			throw;
		}
	}




};
