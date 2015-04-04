CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#About project
#---------------------
SET(PROJECT_NAME dhcpServerApp)
PROJECT (${PROJECT_NAME})
SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")


# Options. Turn on with 'cmake -Dmyvarname=ON'.
OPTION(test "Build all tests." OFF) # Makes boolean 'test' available.

SET(CMAKE_CXX_FLAGS "-fPIC -g -Wall")
SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

INCLUDE_DIRECTORIES (inc)
 
SET(CMAKE_THREAD_PREFER_PTHREAD TRUE)
FIND_PACKAGE(Threads REQUIRED)
IF(CMAKE_USE_PTHREADS_INIT)
    SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")
ENDIF()

################################
# Libraries & Executables
################################
ADD_LIBRARY(dhcpServerApp  
		src/dhcp_server.c 
		src/dhcp_log.c 
		src/ip_allocator.c 
		src/dhcp_server.c 
		src/ip_allocator.c 
		src/dhcp_packet.c)

ADD_EXECUTABLE (dhcpServerApp.bin src/main.c)
target_link_libraries(dhcpServerApp.bin dhcpServerApp ${CMAKE_THREAD_LIBS_INIT} )


################################
# Testing
################################
if (test)
  
  # This adds another subdirectory, which has 'project(gtest)'.
  add_subdirectory(test/gTest-1.7.0)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  ##############
  # Unit Tests
  ##############
  add_executable(runUnitTests 
			test/src/dhcp_serverTest.cc)

  # Standard linking to gtest stuff.
  target_link_libraries(runUnitTests gtest gtest_main)

  # Extra linking for the project.
  target_link_libraries(runUnitTests dhcpServerApp)

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  add_test(NAME ip_asc2byte COMMAND runUnitTests)

endif()
