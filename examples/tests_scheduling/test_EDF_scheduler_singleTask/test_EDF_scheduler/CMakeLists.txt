# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/cjuju/School/PDI/pico-sdk")

set(PICO_BOARD pico CACHE STRING "Board type")

set(FREERTOS_KERNEL_PATH "/home/cjuju/School/PDI/FreeRTOS-Kernel")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

# Pull FreeRTOS specific definitions
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(test_EDF_scheduler C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(test_EDF_scheduler test_EDF_scheduler.c )

pico_set_program_name(test_EDF_scheduler "test_EDF_scheduler")
pico_set_program_version(test_EDF_scheduler "0.1")

pico_enable_stdio_uart(test_EDF_scheduler 1)
pico_enable_stdio_usb(test_EDF_scheduler 1)

# Add the standard library to the build
target_link_libraries(test_EDF_scheduler
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(test_EDF_scheduler PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(test_EDF_scheduler 
        hardware_timer
        FreeRTOS-Kernel-Heap4
        )

pico_add_extra_outputs(test_EDF_scheduler)

