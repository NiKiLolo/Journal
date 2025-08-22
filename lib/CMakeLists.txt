cmake_minimum_required(VERSION 3.1)

project(LibJournal)


#Создание динамической библиотеки
add_library(journal_shared SHARED libjournal.cpp) 
set_target_properties(journal_shared PROPERTIES OUTPUT_NAME "journal")
set_property(TARGET journal_shared PROPERTY CXX_STANDARD 17)

#Создание статической библиотеки
add_library(journal_static STATIC libjournal.cpp) 
set_target_properties(journal_static PROPERTIES OUTPUT_NAME "journal")
set_property(TARGET journal_static PROPERTY CXX_STANDARD 17)

install(TARGETS journal_static journal_shared 
	RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin/
	LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin/
	ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin/
)

install(FILES libjournal.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../include)
