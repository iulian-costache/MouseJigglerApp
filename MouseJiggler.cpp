#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <Windows.h>
#include<ctime>
#include <chrono>
#include <thread>
using namespace std;
using namespace this_thread; // sleep_for, sleep_until
using namespace chrono; // nanoseconds, syPositionstem_clock, seconds

void moveCursor(int xPosition, int yPosition, int nrOfSecondsToSleep, time_t timeFrom, time_t timeTo) {
	SetCursorPos(xPosition, yPosition);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	sleep_until(system_clock::now() + seconds(nrOfSecondsToSleep));
	timeFrom = chrono::system_clock::to_time_t(system_clock::now());
	if (timeTo < timeFrom)
	{
		return;
	}
	moveCursor(xPosition, yPosition, nrOfSecondsToSleep, timeFrom, timeTo);
}
int main()
{
	int xPosition, yPosition, nrOfSecondsToSleep, m;
	cout << "This app will trigger mouse click on specified position" << endl;
	cout << "Input X coordinates position : "; cin >> xPosition;
	cout << "Input Y coordinates position : "; cin >> yPosition;
	cout << "Input seconds between clicks : "; cin >> nrOfSecondsToSleep;
	cout << "Input number of minutes to run this app( only 1 minute allowed for free version ): "; cin >> m;
	if (m <= 0 || nrOfSecondsToSleep < 0)
	{
		return 0;
	}
	/*if (m > 1)
	{
		cout << "Please buy full version to use that feature" << endl;
		system("pause");
		return 0;
	}*/
	char shutDown = 'n';
	cout << "Do you want to shutdown the system at the and (Y/N) ?";
	cin >> shutDown;

	if (shutDown != 'y' && shutDown != 'Y' && shutDown != 'n' && shutDown != 'N')
	{
		cout << "Incorect input!" << endl;
	}
	time_t currentTime = system_clock::to_time_t(system_clock::now());
	time_t untilTime = system_clock::to_time_t(system_clock::now() + minutes(m));
	cout << "This program will close on: " << ctime(&untilTime) << endl;
	moveCursor(xPosition, yPosition, nrOfSecondsToSleep, currentTime, untilTime);
	if (shutDown == 'y' || shutDown == 'Y')
	{
		system("shutdown -s");
	}
	system("pause");
	return 0;
}
