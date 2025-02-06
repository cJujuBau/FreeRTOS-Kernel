# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/cjuju/School/PDI/pico-sdk/tools/pioasm"
  "/home/cjuju/School/PDI/FreeRTOS-Kernel/examples/tests_scheduling/test_noPriorities/build/pioasm"
  "/home/cjuju/School/PDI/FreeRTOS-Kernel/examples/tests_scheduling/test_noPriorities/build/pioasm-install"
  "/home/cjuju/School/PDI/FreeRTOS-Kernel/examples/tests_scheduling/test_noPriorities/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/tmp"
  "/home/cjuju/School/PDI/FreeRTOS-Kernel/examples/tests_scheduling/test_noPriorities/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
  "/home/cjuju/School/PDI/FreeRTOS-Kernel/examples/tests_scheduling/test_noPriorities/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src"
  "/home/cjuju/School/PDI/FreeRTOS-Kernel/examples/tests_scheduling/test_noPriorities/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/cjuju/School/PDI/FreeRTOS-Kernel/examples/tests_scheduling/test_noPriorities/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/cjuju/School/PDI/FreeRTOS-Kernel/examples/tests_scheduling/test_noPriorities/build/pico-sdk/src/rp2_common/pico_cyw43_driver/pioasm/src/pioasmBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
