#include <iostream>
#include <istream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <atomic>

#include "libjournal.h"
using namespace std;
bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

condition_variable cv;
mutex mtx;
atomic<bool> stop_flag{false};
struct JournalEntry {
    string text;
    int level;
};
queue<JournalEntry> journalQueue;

int levelNotificationCheck(string& lvlNotifStr)
{
    if (is_number(lvlNotifStr))
    {
        auto lvlNotif = stoi(lvlNotifStr);
        if (Journal::isImportanceLevelValid(Journal::Notification(lvlNotif)))
            return lvlNotif;
    }
    return -1;
    
}
void initializationApp(string& fileName, int& levelNotification)
{
    string newLvlNotificantion;
    cout << "Введите название файла логгирования" << endl;
    getline(cin, fileName);
    cout << "Введите уровень важности сообщения для файла логгирования (от 0 до 2)" << endl;
    getline(cin,newLvlNotificantion);

    levelNotification = levelNotificationCheck(newLvlNotificantion);

    if (levelNotification == -1)
    {
        cout << "Неверный уровень важности сообщения, попробуйте еще раз" << endl;
        initializationApp(fileName, levelNotification);
    }
    if(fileName.empty())
    {
        cout << "Название файла не может быть пустым, попробуйте снова" << endl;
        initializationApp(fileName, levelNotification);
    }

}

bool requestLogMessage(JournalEntry& entry)
{
    string message;
    string messageLvlNotif;
    int code = 0;

    cout << "Введите сообщение и его уровеень важности(от 0 до 2, любое другое значение считается за 0 - ый уровень)" << endl;
    getline(cin, message);
    if (message == "exit")
    {
        stop_flag = true;
        cv.notify_one();
        return false;
    }
    getline(cin, messageLvlNotif);
    if (is_number(messageLvlNotif))
    {
        auto levelMsg = stoi(messageLvlNotif);
        if(Journal::isImportanceLevelValid(Journal::Notification(levelMsg)))
            code = levelMsg;
    }
    entry = JournalEntry{message, code};
    return true;
}
void putLogToProcessing(JournalEntry& entry)
{
    lock_guard<mutex> lock(mtx);
    journalQueue.push(entry);
    cv.notify_one();
}
void loggerProc(string fileName, int levelNotification)
{
    Journal JournalObj(fileName, Journal::Notification(levelNotification));
    while (!stop_flag)
    {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock);
        if(stop_flag) break;;
        JournalEntry userMessage = journalQueue.front();
        journalQueue.pop();
        lock.unlock();
        JournalObj.sendMessage(userMessage.text, Journal::Notification(userMessage.level));
    }
}

int main()
{
    string fileName;
    int levelNotification;
    auto isWork = true;
    
    initializationApp(fileName, levelNotification);
    cout << "Чтобы остановить работу программы, впишите exit" << endl;
    thread logger(loggerProc, fileName, levelNotification);
    while (isWork)
    {
        JournalEntry entry;
        isWork = requestLogMessage(entry);
        putLogToProcessing(entry);
    }
    logger.join();
    return 0;
}