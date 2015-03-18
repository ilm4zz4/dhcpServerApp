PROJECT (dhcpServerApp)

CMAKE_MINIMUM_REQUIRED(VERSION 1.0.0)
SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)
#set(INSTALL_BIN_DIR bin CACHE PATH )

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
INCLUDE_DIRECTORIES (inc)
 
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package(Threads REQUIRED)
if(CMAKE_USE_PTHREADS_INIT)
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-pthread")
endif()

ADD_EXECUTABLE (dhcpServerApp src/dhcp_server.c src/dhcp_log.c src/ip_allocator.c src/dhcp_server.c src/ip_allocator.c src/main.c src/dhcp_packet.c)
target_link_libraries( dhcpServerApp ${CMAKE_THREAD_LIBS_INIT} )

#install(TARGETS dhcpServerApp
#RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
#)



#INSTALL(RUNTIME DESTINATION bin)
