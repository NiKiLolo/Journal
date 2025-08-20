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
	if (jourName.size() > 0)
		journalName = jourName + ".txt";
}

void Journal::setImportanceLevel(Notification level)
{
	importanceLevel = level;
}
int Journal::sendMessage(const string& text, Notification level)
{
	if (level < importanceLevel)
		return 0;
	
	if (!isImportanceLevelValid(level) || !journalName.size())
		return -1;
	
	ofstream logger(journalName.c_str(), ios::app);
	if (!logger)
		return -1;
	
	logger << '[' << timeToString() << ']' << '[' << levelToStr(level) << ']' << text << endl;
	return 0;
}


bool Journal::isImportanceLevelValid(Notification level) 
{
	return (level >= lUsual && level <= lCritical);
}

string Journal::levelToStr(Notification level) const
{
	switch (level)
	{
		case lUsual: return "Usual";
		case lWarning: return "Warning";
		case lCritical: return "Critical";
		default: return "Unknown";
	}
}







