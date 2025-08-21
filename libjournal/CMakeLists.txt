cmake_minimum_required(VERSION 3.1)

project(LibJournal)

add_library(journal SHARED libjournal.cpp) # Создание динамической библиотеки с именем libjournal
add_library(journalStatic STATIC libjournal.cpp)# Создание статической библиотеки с именем libjournal

add_executable(test test.cpp)# Создает исполняемый файл с именем test для проведения тестов
target_link_libraries(test journal) # Линковка теста с библиотекой

set_property(TARGET journal PROPERTY CXX_STANDARD 17)
