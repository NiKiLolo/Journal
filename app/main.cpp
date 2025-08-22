#include <iostream>
#include <istream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <atomic>

#include <libjournal.h>
using namespace std;
struct JournalEntry 
{
    string text;
    int level;
};

mutex mtx;
condition_variable cv;
atomic<bool> stopFlag{false};

queue<JournalEntry> journalQueue;

bool isNumber(const string & s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) 
		++it;
    
	return !s.empty() && it == s.end();
}

int checkNotificationLevel(const string & lvlNotifStr)
{
    if (isNumber(lvlNotifStr))
    {
        auto lvlNotif = stoi(lvlNotifStr);
        if (Journal::isImportanceLevelValid(Journal::Notification(lvlNotif)))
            return lvlNotif;
    }
    return -1;
}

void initializationApp(std::string & fileName, int & levelNotification)
{
    cout << "Введите название файла логгирования" << endl;
    getline(cin, fileName);
	if (fileName.empty())
    {
        cout << "Ошибка: Название файла не может быть пустым." << endl;
        return;
    }
	
	cout << "Введите уровень важности сообщения для файла логгирования (от 0 до 2)" << endl;
	std::string userEnteredLevel;
    getline(cin,userEnteredLevel);
    levelNotification = checkNotificationLevel(userEnteredLevel);
    if (levelNotification == -1)
    {
        cout << "Ошибка: Неверный уровень важности сообщения." << endl;
		return;
    }
}


/*

*/
bool requestLogMessage(JournalEntry & entry)
{
    cout << "Введите сообщение для записи в журнал и [Enter], затем уровень важности (0-2) и [Enter]" << endl;
	string message;
    getline(cin, message);
    if (message == "exit")
    {
        stopFlag = true;
        cv.notify_one();
        return false;
    }
	
	int code = 0;
	std::string messageLvlNotif;
    getline(cin, messageLvlNotif);
    if (isNumber(messageLvlNotif))
    {
        auto levelMsg = stoi(messageLvlNotif);
        if(Journal::isImportanceLevelValid(Journal::Notification(levelMsg)))
            code = levelMsg;
    }
	
    entry = JournalEntry{message, code};
    return true;
}

/* 
   Размещает данные для логирования в очереди и оповещает считывающий поток через cond_var
   доступ в очередь синхронизирован мьюетксом
*/
void putLogToProcessing(JournalEntry& entry)
{
    lock_guard<mutex> lock(mtx);
    journalQueue.push(entry);
    cv.notify_one();
}

/* 
   Инициализирует логгер 
   При появлении события на cv gолучает данные для логирования из очереди 
   Отправляет данные для логирования в логгер. 
*/
void loggerProc(string fileName, int levelNotification)
{
    Journal JournalObj(fileName, Journal::Notification(levelNotification));
    while (!stopFlag)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock);
        if (stopFlag) 
			break;
		
        JournalEntry userMessage = journalQueue.front();
        journalQueue.pop();
        lock.unlock();
        JournalObj.sendMessage(userMessage.text, Journal::Notification(userMessage.level));
    }
}

int main()
{
    std::string fileName;
    int levelNotification;
    
	/* 
	   Запрашивает имя файла и уровень оповещения для начальной инциализации библиотеки
	   Параметрые запрашиваются в цикле пока пользователь не введет их все валидными.
	*/
    bool isInitialized = false;
	while(!isInitialized) {
		initializationApp(fileName, levelNotification);
		if (fileName.size() != 0 && levelNotification != -1)
			isInitialized = true;
	}
	
	
	/* 
	   Рабочий цикл программы
	   1. requestLogMessage(entry) - запрашивает у пользователя данные для логирования в структуру JournalEntry.
	   2. putLogToProcessing(entry) - помещает полученные данные для логгирования в очередь.
	   3. loggerProc в отдельном потоке забирает данные из очереди и выводит их в логгер.
	*/
    cout << "Чтобы остановить работу программы, введите: exit" << endl;
    thread logger(loggerProc, fileName, levelNotification);
	bool isWork = true;
    while (isWork)
    {
        JournalEntry entry;
        isWork = requestLogMessage(entry);
        putLogToProcessing(entry);
    }
    logger.join();
    return 0;
}
