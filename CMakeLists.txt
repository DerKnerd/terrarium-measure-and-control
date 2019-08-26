cmake_minimum_required(VERSION 3.2)
project(terrarium-measure-and-control)

include(CMakeListsPrivate.txt)
include_directories(.pio/libdeps/uno/ArduinoJson_ID64)
include_directories(.pio/libdeps/uno/RFTransmitter_ID1501)
include_directories(.pio/libdeps/uno/U8g2_ID942/src)
include_directories(".pio/libdeps/uno/DHT sensor library_ID19")
include_directories(.pio/libdeps/uno/RTClib_ID83)
include_directories(".pio/libdeps/uno/Adafruit Unified Sensor_ID31")
include_directories(.pio/libdeps/uno/DallasTemperature_ID54)
include_directories(.pio/libdeps/uno/OneWire_ID1)
include_directories(.pio/libdeps/uno/Dimmer_ID5704/src)
include_directories(lib/epd2in9)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_BUILD_VERBOSE ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --verbose
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_MONITOR ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion device monitor
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_TEST ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_PROGRAM ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOADFS ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPDATE_ALL ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion update
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_REBUILD_PROJECT_INDEX ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion init --ide clion
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${SRC_LIST} src/main.cpp src/display/Display.cpp src/display/Display.h src/humidity/HumiditySensor.cpp src/humidity/HumiditySensor.h src/sender/Sender.cpp src/sender/Sender.h src/temperature/Thermometer.cpp src/temperature/Thermometer.h src/dimming/DimmerControl.cpp src/dimming/DimmerControl.h src/relay/Relay.cpp src/relay/Relay.h src/timing/Clock.cpp src/timing/Clock.h)
