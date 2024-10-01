cmake_minimum_required(VERSION 3.16.0)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ESPIDF_BASICE_Rtos)

target_add_binary_data(ESPIDF_BASICE_Rtos.elf "src/mqtt_eclipseprojects_io.pem" TEXT)