cmake_minimum_required(VERSION 3.10.0)
project(UnitTests VERSION 0.1.0 LANGUAGES C CXX)

#Создание исполняемого файла для юнит тестов
add_executable(test test.cpp)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
target_link_libraries(test ${CMAKE_CURRENT_SOURCE_DIR}/../build/lib/libjournal.a)

set_property(TARGET test PROPERTY CXX_STANDARD 17)
install(TARGETS test RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin)  
