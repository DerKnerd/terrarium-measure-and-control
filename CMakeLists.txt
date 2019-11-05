cmake_minimum_required(VERSION 3.2)
project(terrarium-measure-and-control)

include(CMakeListsPrivate.txt)
include_directories(.pio/libdeps/nanoatmega328/ArduinoJson_ID64)
include_directories(".pio/libdeps/nanoatmega328/DHT sensor library_ID19")
include_directories(.pio/libdeps/nanoatmega328/RTClib_ID83)
include_directories(".pio/libdeps/nanoatmega328/Adafruit Unified Sensor_ID31")
include_directories(.pio/libdeps/nanoatmega328/DallasTemperature_ID54)
include_directories(.pio/libdeps/nanoatmega328/OneWire_ID1)

include_directories(.pio/libdeps/nano_33_iot/ArduinoJson_ID64)
include_directories(".pio/libdeps/nano_33_iot/DHT sensor library_ID19")
include_directories(.pio/libdeps/nano_33_iot/RTClib_ID83)
include_directories(".pio/libdeps/nano_33_iot/Adafruit Unified Sensor_ID31")
include_directories(.pio/libdeps/nano_33_iot/DallasTemperature_ID54)
include_directories(.pio/libdeps/nano_33_iot/OneWire_ID1)
include_directories(.pio/libdeps/nano_33_iot/WiFiNINA_ID5538/src)
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

add_executable(${PROJECT_NAME} ${SRC_LIST} src/main.cpp src/display/Display.cpp src/display/Display.h src/humidity/HumiditySensor.cpp src/humidity/HumiditySensor.h src/temperature/Thermometer.cpp src/temperature/Thermometer.h src/dimming/DimmerControl.cpp src/dimming/DimmerControl.h src/relay/Relay.cpp src/relay/Relay.h src/timing/Clock.cpp src/timing/Clock.h src/work/Runner.cpp src/work/Runner.h src/Symbols.h)
