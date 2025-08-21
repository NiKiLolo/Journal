#include <iostream>
#include <fstream>
#include "libjournal.h"

using namespace std;
void TestCheckFileCreate()
{
    Journal test("TestCheckFileCreate", Journal::lUsual);
    test.sendMessage("test message", Journal::lUsual);
    ifstream check("TestCheckFileCreate.txt");
    if(check.is_open())
    {
        cout << "TestCheckFileCreate: File is Open, Test: passed" << endl;
    }
    else
    {
        cout << "TestCheckFileCreate: File isnt Open, Test: failure" << endl;
    }
    
}
void TestCheckMessageInput()
{
    string line;
    Journal test("TestCheckMessageInput", Journal::lUsual);
    test.sendMessage("test message", Journal::lUsual);
    ifstream check("TestCheckMessageInput.txt");
    if(check.is_open())
    {
        while (getline(check, line))
        {
            cout << "TestCheckMessageInput:" << line << endl;
        }
        
        
    }
}
void TestCheckLessLevelImportance()
{
    string line;
    Journal test("TestCheckLessLevelImportance", Journal::lUsual);
    test.sendMessage("Level is lUsual test message 1 lUsual", Journal::lUsual);
    test.sendMessage("Level is lUsual test message 1 lCritical", Journal::lCritical);
    test.sendMessage("Level is lUsual test message 1 lWarning", Journal::lWarning);
    test.setImportanceLevel(Journal::lWarning);
    test.sendMessage("Level is lWarning test message 2 lUsual", Journal::lUsual);
    test.sendMessage("Level is lWarning test message 2 lCritical", Journal::lCritical);
    test.sendMessage("Level is lWarning test message 2 lWarning", Journal::lWarning);
    test.setImportanceLevel(Journal::lCritical);
    test.sendMessage("Level is lCritical test message 3 lUsual", Journal::lUsual);
    test.sendMessage("Level is lCritical test message 3 lCritical", Journal::lCritical);
    test.sendMessage("Level is lCritical  test message 3 lWarning", Journal::lWarning);
    ifstream check("TestCheckLessLevelImportance.txt");
    if(check.is_open())
    {
        while (getline(check, line))
        {
            cout << "TestCheckLessLevelImportance:" << line << endl;
        }
    }
}
void TestCheckAllLevelImportance()
{
    string line;
    Journal test("TestCheckAllLevelImportance", Journal::lUsual);
    test.sendMessage("test message lUsual", Journal::lUsual);
    test.sendMessage("test message lCritical", Journal::lCritical);
    test.sendMessage("test message lWarning", Journal::lWarning);
    ifstream check("TestCheckAllLevelImportance.txt");
    if(check.is_open())
    {
        while (getline(check, line))
        {
            cout << "TestCheckAllLevelImportance:" << line << endl;
        }
    }
}
void TestCheckNonValidParamters(){
    Journal testOne("", Journal::Notification(-1));
    cout << "TestCheckNonValidParamters(TestOne, without file name): " << testOne.sendMessage("test message", Journal::lUsual) << endl;
    Journal testTwo("TestCheckNonValidParamters", Journal::lUsual);
    cout << "TestCheckNonValidParamters (sendMessage(Hi, Journal::Notification(-1)): " << testTwo.sendMessage("Hi", Journal::Notification(-1)) << endl;

}
int main()
{
    /*Тест кторый проверяет, создается ли файл при инициализации и отправки сообщения*/
    TestCheckFileCreate(); 
    /*Тест кторый проверяет, вводятся ли сообщения в файл журнала при использовании sendMessage*/
    TestCheckMessageInput();
    /*Тест который проверяет, правильность отправки сообщений в журнал при определенных уровнях важности сообщений в журнале*/
    TestCheckLessLevelImportance();
    /*Тест который проверяет, вводятся ли все уровни важности журнала*/
    TestCheckAllLevelImportance();
    /*Тест который проверяет, в случае ввода невалидных данных, как действует программа, возвращает ли ошибку*/
    TestCheckNonValidParamters();
    return 0;
}