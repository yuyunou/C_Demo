
include_directories(/mnt/hgfs/git/C_Demo/include)
include_directories(/mnt/hgfs/git/C_Demo/include/sqlite3)
include_directories(/mnt/hgfs/git/C_Demo/include/hp_socket)
include_directories(/mnt/hgfs/git/C_Demo/include/curl)
link_directories(/mnt/hgfs/git/C_Demo//lib)
link_directories(/mnt/hgfs/git/C_Demo/lib/hp_socket)

#add_executable需要放在添加动态库前
set(CMAKE_C_FLAGS "-lcurl")
set(CMAKE_C_FLAGS "-lssl")
set(CMAKE_C_FLAGS "-g")
add_executable(ROBOT main.c)
add_executable(UDP_SERVER udp_server.cpp)
add_executable(UDP_CLIENT udp_client.cpp)
add_executable(CURL curl.c)
target_link_libraries(UDP_SERVER libhpsocket.so.5)
target_link_libraries(UDP_CLIENT libhpsocket.so.5)
target_link_libraries(ROBOT libsqlite3.so)
target_link_libraries(CURL libcurl.so libssl.so.3)


add_subdirectory(mqtt)