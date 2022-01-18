
link_directories(/mnt/hgfs/git/C_Demo/lib)
include_directories(/mnt/hgfs/git/C_Demo/include/mosquitto)

set(CMAKE_C_FLAGS "-g")
add_executable(MQTT_SUB mqtt_sub.c)
add_executable(MQTT_PUB mqtt_pub.c)

target_link_libraries(MQTT_SUB libmosquitto.so)
target_link_libraries(MQTT_PUB libmosquitto.so)
