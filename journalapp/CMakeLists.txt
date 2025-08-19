cmake_minimum_required(VERSION 3.10.0)
project(JournalApp VERSION 0.1.0 LANGUAGES C CXX)

add_executable(JournalApp main.cpp)

target_link_libraries(JournalApp /home/superuser/projects/lbj_type/lbj_static/libjournal.a)

set_property(TARGET JournalApp PROPERTY CXX_STANDARD 17)