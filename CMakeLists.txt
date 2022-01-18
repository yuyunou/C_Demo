
cmake_minimum_required(VERSION 3.10.0)


project(TEST)

#add_executable需要放在添加动态库前

add_subdirectory(src)
#target_link_libraries(ROBOT libsqlite3.so)


