cmake_minimum_required(VERSION 3.5)
project(TelegramLib)

set(CMAKE_CXX_STANDARD 14)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
endif(DOXYGEN_FOUND)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

enable_testing(true)
add_test(NAME "TestOfTelegramLib" COMMAND tltest)
add_executable(tltest src/telegram_lib_test.cpp include/TelegramBase.hpp include/TelegramHFI.hpp)
