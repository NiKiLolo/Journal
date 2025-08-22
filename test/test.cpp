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
        cout << "TestCheckFileCreate: File is Open, Test: OK" << endl;
        
    }
    else
    {
        cout << "TestCheckFileCreate: File isnt Open, Test: FAIL" << endl;
    }
    
    
}

void TestCheckMessageInput()
{
    string line;
    int count = 1;
    Journal test("TestCheckMessageInput", Journal::lUsual);
    test.sendMessage("test message", Journal::lUsual);
    ifstream check("TestCheckMessageInput.txt");
    if(check.is_open())
    {
        getline(check, line);
        if(line.find("test message") != string::npos)
        {
            cout << "TestCheckMessageInput: OK" << endl;
            return;
        }
    }
    cout << "TestCheckMessageInput: FALSE" << endl;
}

void TestCheckLessLevelImportance()
{
    string line;
    int coutL1 = 0;
    int coutL2 = 0;
    int coutL3 = 0;
    Journal test("TestCheckLessLevelImportance", Journal::lUsual);
    test.sendMessage("L1", Journal::lUsual);
    test.sendMessage("L1", Journal::lCritical);
    test.sendMessage("L1", Journal::lWarning);
    test.setImportanceLevel(Journal::lWarning);
    test.sendMessage("L2", Journal::lUsual);
    test.sendMessage("L2", Journal::lCritical);
    test.sendMessage("L2", Journal::lWarning);
    test.setImportanceLevel(Journal::lCritical);
    test.sendMessage("L3", Journal::lUsual);
    test.sendMessage("L3", Journal::lCritical);
    test.sendMessage("L3", Journal::lWarning);
    ifstream check("TestCheckLessLevelImportance.txt");
    if(check.is_open())
    {
        while (getline(check, line))
        {
            if(line.find("L1") != string::npos)
                coutL1++;
            if(line.find("L2") != string::npos)
                coutL2++;
            if(line.find("L3") != string::npos)
                coutL3++;
        }
    }
    if(coutL1 == 3 && coutL2 == 2 && coutL3 == 1)
    {
        cout << "TestCheckLessLevelImportance: OK" << endl;
        return;
    }
    cout << "TestCheckLessLevelImportance: FALSE" << endl;

}

void TestCheckAllLevelImportance()
{
    string line;
    int count = 0;
    Journal test("TestCheckAllLevelImportance", Journal::lUsual);
    test.sendMessage("L1", Journal::lUsual);
    test.sendMessage("L2", Journal::lCritical);
    test.sendMessage("L3", Journal::lWarning);
    ifstream check("TestCheckAllLevelImportance.txt");
    if(check.is_open())
    {
        while (getline(check, line))
        {
            if(line.find("Usual") || line.find("Critical") || line.find("Warning"))
                count++;
        }
    }
    if(count == 3)
    {
        cout << "TestCheckAllLevelImportance: OK" << endl;
        return;
    }
    cout << "TestCheckAllLevelImportance: FALSE" << endl;
}

void TestCheckNonValidParamters(){
    Journal testOne("", Journal::lUsual);
    if (testOne.sendMessage("test message", Journal::lUsual) != -1)
    {
        cout << "TestCheckNonValidParamters: FALSE" << endl;
        return;
    }
    cout << "TestCheckNonValidParamters: OK" << endl;

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
    remove("TestCheckFileCreate.txt");
    remove("TestCheckMessageInput.txt");
    remove("TestCheckLessLevelImportance.txt");
    remove("TestCheckAllLevelImportance.txt");
    remove("TestCheckNonValidParamters.txt");
    return 0;
}