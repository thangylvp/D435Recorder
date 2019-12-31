#include "global.h"

int main(int argc, char** argv)
{	
	RGBDSensor* sensor = new D435Sensor();
	sensor->run();
	delete sensor;
	return 0;
}