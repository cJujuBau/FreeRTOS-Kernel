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

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Pull FreeRTOS specific definitions
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)


project(test_noPriorities C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(test_noPriorities test_noPriorities.c )

pico_set_program_name(test_noPriorities "test_noPriorities")
pico_set_program_version(test_noPriorities "0.1")

pico_enable_stdio_uart(test_noPriorities 1)
pico_enable_stdio_usb(test_noPriorities 1)

# Add the standard library to the build
target_link_libraries(test_noPriorities
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(test_noPriorities PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(test_noPriorities 
	hardware_timer
        FreeRTOS-Kernel-Heap4
        )

pico_add_extra_outputs(test_noPriorities)

