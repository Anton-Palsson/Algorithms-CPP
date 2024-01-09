#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>


using namespace std;

enum class SensorType
{
	Altitude,
	SpeedInKmh,
	FuelConsumption
};

class SensorData
{
	float value;
	SensorType sensorType;
	time_t time;
public:
	SensorType GetSensorType() const { return sensorType; }
	float GetValue() const { return value; }
	void SetValue(float v) { value = v; }
	time_t GetTime() const { return time; }
	SensorData(SensorType sensorType, float value, time_t time)
	{
		this->value = value;
		this->sensorType = sensorType;
		this->time = time;
	}
};


void FillData(vector<SensorData> &v);
time_t CreateTime(int year, int month, int day, int hour, int minute, int second);
int main()
{   // DEL 1 ANVÄND ALGORITHM
	vector<SensorData> sensorData;
	FillData(sensorData);

    time_t startTime = CreateTime(2012, 1, 2, 0, 0, 0);
    time_t endTime = CreateTime(2012, 1, 2, 23, 59, 59);

    int countAltitudebetween2Timestamps = count_if(sensorData.begin(), sensorData.end(), [&](const SensorData &data) {
        return data.GetSensorType() == SensorType::Altitude && data.GetTime() >= startTime && data.GetTime() <= endTime;
    });

    cout << "The number of Altitude readings with timestamps in the set range is: " << countAltitudebetween2Timestamps << endl;

	
	
	//DEL 2 ANVÄND ALGORITHM
	float limit = 99.9;

    bool overLimit = any_of(sensorData.begin(), sensorData.end(), [&](const SensorData &data) {
        return data.GetSensorType() == SensorType::SpeedInKmh && data.GetValue() > limit;
    });


	if (overLimit) {
		cout << "Maximum speed reached" << endl;

	} else {
		cout << "No maximum speed reached" << endl;
	}


	 
	 //DEL 3 ANVÄND ALGORITHM
	   auto updateFuelConsumption = [](SensorData &entry) {
        if (entry.GetSensorType() == SensorType::FuelConsumption)
        {
            entry.SetValue(entry.GetValue() * 1.75);
            //Rör ej!! Endast för att se om det funkar cout << "SensorType: " << static_cast<int>(entry.GetSensorType()) << ", Value: " << entry.GetValue() << endl;
        }
    };

    for_each(sensorData.begin(), sensorData.end(), updateFuelConsumption);

    return 0;
}


void FillData(vector<SensorData>& v)
{
	srand(time(NULL));

	time_t tid = CreateTime(2012, 1, 1, 1, 1, 1 );
	for (int i = 0; i < 100000; i++)
	{
		SensorType type = static_cast<SensorType>(rand() % 3);
		float value = 0.0f;
		if (type == SensorType::Altitude)
			value = rand() % 1000;
		else if (type == SensorType::FuelConsumption)
			value = rand() * 3.0f;
		else if (type == SensorType::SpeedInKmh)
			value = rand() % 110;
		else
		{
			value = 99;
		}
		v.push_back(SensorData(type,value,tid));
		tid = tid + rand() % 10 + 1;
	}
}

time_t CreateTime(int year, int month, int day, int hour, int minute, int second)
{
	struct tm tid = { 0 };
	tid.tm_year = year-1900;
	tid.tm_mon = month - 1;
	tid.tm_mday = day;
	tid.tm_hour = hour;
	tid.tm_min = minute;
	tid.tm_sec = second;
	return mktime(&tid);
}
