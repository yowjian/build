#include <amqm/AMQManager.h>
#include "Ground_Movers.h"




//Constructors
Ground_Vehicle::Ground_Vehicle()
{

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> bearing_Random(0.0, 360.0); // 0 -360 heading in degrees
	std::uniform_real_distribution<double> speed_Random(25.0, 125.0); // 0-25 KpH
	std::uniform_int_distribution<int> id_random(1, 500000);
	starting_Location.x = current_Location.x = 32.715736; // San Diego, CA USA
	starting_Location.y = current_Location.y = -117.161087; // San Diego, CA USA
	starting_time = std::chrono::system_clock::now();
	last_time = starting_time;
	speed = speed_Random(mt);
	MpMS = speed / 3600;
	bearing = bearing_Random(mt);
	vehcile_ID = id_random(mt);
	std::thread t1(&Ground_Vehicle::Update_Ground_Vehicle_Position, this);
	t1.detach();
}
Ground_Vehicle::Ground_Vehicle(double starting_Lat, double starting_Long)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> bearing_Random(0.0, 360.0); // 0 -360 heading in degrees
	std::uniform_real_distribution<double> speed_Random(25.0, 125.0); // 0-25 KpH
	std::uniform_int_distribution<int> id_random(1, 500000);
	starting_Location.x = current_Location.x = starting_Lat;
	starting_Location.y = current_Location.y = starting_Long;
	starting_time = std::chrono::system_clock::now();
	last_time = starting_time;
	speed = speed_Random(mt);
	MpMS = speed / 3600;
	bearing = bearing_Random(mt);
	vehcile_ID = id_random(mt);
	std::thread t1(&Ground_Vehicle::Update_Ground_Vehicle_Position, this);
	t1.detach();
}
Ground_Vehicle::Ground_Vehicle(double starting_Lat, double starting_Long, double starting_Speed, double starting_Bearing)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	starting_Location.x = current_Location.x = starting_Lat;
	starting_Location.y = current_Location.y = starting_Long;
	std::uniform_int_distribution<int> id_random(1, 500000);
	starting_time = std::chrono::system_clock::now();
	last_time = starting_time;
	speed = starting_Speed;
	bearing = starting_Bearing;
	vehcile_ID = id_random(mt);
	std::thread t1(&Ground_Vehicle::Update_Ground_Vehicle_Position, this);
	t1.detach();
}


void Ground_Vehicle::Update_Ground_Vehicle_Position(void)
{


	int sleep_msec = 1000 + int(speed);

	while (true) {


		std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
		// # of milliseconds between creation time and current  time
		auto delta_Time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - starting_time).count();
		// # of milliseconds between last time and current  time
		auto delta_Last_Time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_time).count();

		// distance = Time * Speed
		double meters_Traveled = (delta_Time * MpMS);
		// distance = Time * Speed
		double leg_distance = (delta_Last_Time * MpMS);

		// continues on same bearing until a distance is traveled and turns 90 deg
		distance_traveled += leg_distance;
		if (distance_traveled >= MAX_TOTAL_DISTANCE)
		{

			if (bearing + 90 >= 360)
			{
				bearing -= 270;
			}
			else
			{
				bearing += 90;
			}
			leg_distance = (distance_traveled + leg_distance) - MAX_TOTAL_DISTANCE;

			distance_traveled = 0;
		}

		current_Location = CoordinateToCoordinate(current_Location.x, current_Location.y, bearing, leg_distance);
		last_time = current_time;

		json j;
		j["vehicleID"] = std::to_string(vehcile_ID);
		j["lat"] = current_Location.x;
		j["lon"] = current_Location.y;
		j["bearing"] = bearing;
		j["speed"] = speed;
		amq.publish("groundMovers", j, true);
		Utils::sleep_for(1000);
	}
}

// Getters
uas::Location Ground_Vehicle::get_Curruent_Location(void)
{
	return current_Location;
}
double Ground_Vehicle::get_Speed(void)
{
	return speed;
}
double Ground_Vehicle::get_Bearing(void)
{
	return bearing;
}



uas::Location Ground_Vehicle::CoordinateToCoordinate(double x, double y, double angle, double meters)
{
	x = Utils::deg2rad(x);
	y = Utils::deg2rad(y);
	angle = Utils::deg2rad(angle);
	meters *= 2 / earthDiameterMeters;
	uas::Location new_Location;
	using namespace std;
	pair<double, double> coordinate;

	coordinate.first = asin((sin(x) * cos(meters))
		+ (cos(x) * sin(meters) * cos(angle)));
	coordinate.second = y + atan2((sin(angle) * sin(meters) * cos(x)),
		cos(meters) - (sin(x) * sin(coordinate.first)));

	new_Location.x = Utils::rad2deg(coordinate.first);
	new_Location.y = Utils::rad2deg(coordinate.second);
	return new_Location;
}
void Ground_Vehicle::print_Current_Location(void)
{
	std::cout << "Current Latitue: " << current_Location.x << std::endl;
	std::cout << "Current y: " << current_Location.y << std::endl;
}

void Ground_Vehicle::print_Debug(void)
{
	std::cout << current_Location.y << "," << current_Location.x << "\n";;
}