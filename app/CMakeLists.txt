cmake_minimum_required(VERSION 3.10.0)
project(JournalApp VERSION 0.1.0 LANGUAGES C CXX)

add_executable(JournalApp main.cpp)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../lib/)
target_link_libraries(JournalApp ${CMAKE_CURRENT_SOURCE_DIR}/../build/lib/libjournal.a)

set_property(TARGET JournalApp PROPERTY CXX_STANDARD 17)
install(TARGETS JournalApp RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin)  
