
#ifndef LIBJOURNAL_H
#define LIBJOURNAL_H
#include <iostream>

#define errorUnknowImportanceLevel "Unknown"
#define JournalLoadException 1000

class Journal
{
	public:
		enum Notification { lUsual, lWarning, lCritical }; 
		/* Конструирование и инициализация журнала
			Принимает: Название файла, Уровень важности сообщения
		*/
		Journal(std::string jourName, Notification jourLvl);
		//Устанавливает уровень важности сообщения для журнала
		void setImportanceLevel(Notification level);
		/* Отправляет сообщение в журнал
			Принимает: Уровень важности сообщения, Текст сообщения
		*/
		int sendMessage(const std::string& text, Notification level);
		//Проверка, является ли существующим уровнем важности
		static bool isRealImportanceLevel(Notification level);
	private:
		std::string journalName;
		Notification importanceLevel;
		std::string levelToStr(Notification level) const;
};
#endif