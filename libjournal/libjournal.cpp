#include "libjournal.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
using namespace std;

static string timeToString()
{
	auto timeNow = chrono::system_clock::to_time_t(chrono::system_clock::now());
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", localtime(&timeNow));
	return buffer;
}
Journal::Journal(string jourName, Notification jourLvl)
{
	importanceLevel = jourLvl;
	journalName = jourName + ".txt";
}
void Journal::setImportanceLevel(Notification level)
{
	importanceLevel = level;
}
int Journal::sendMessage(const string& text, Notification level = lUsual)
{
	if (level >= importanceLevel)
	{
		ofstream ist(journalName.c_str(), ios::app);
		if (ist)
		{
			ist << '[' << timeToString() << ']' << '[' << levelToStr(level) << ']' << text << endl;
			return 1;
		}
		else
			return JournalLoadException;
	}
	return 0;
}
bool Journal::isRealImportanceLevel(Notification level) 
{
	switch (level)
	{
		case lUsual: return true;
		case lWarning: return true;
		case lCritical: return true;
		default: return false;
	}
}

string Journal::levelToStr(Notification level) const
{
	switch (level)
	{
		case lUsual: return "Usual";
		case lWarning: return "Warning";
		case lCritical: return "Critical";
		default: return errorUnknowImportanceLevel;
	}
}







