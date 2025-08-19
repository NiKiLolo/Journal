cmake_minimum_required(VERSION 3.1)

project(LibJournal)

add_library(journal SHARED libjournal.cpp)	# Создание динамической библиотеки с именем libjournal
add_library(journal STATIC libjournal.cpp)	# Создание статической библиотеки с именем libjournal

set_property(TARGET journal PROPERTY CXX_STANDARD 17)
