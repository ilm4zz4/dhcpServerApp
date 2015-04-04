dhcpClientApp
=========================

[![Build Status](https://travis-ci.org/ilm4zz4/dhcpServerApp.png)](https://travis-ci.org/ilm4zz4/dhcpServerApp)
[![Codeship Build Status](https://www.codeship.io/projects/876c9b00-9f67-0132-ef75-520a26f6f18f/status)](https://www.codeship.io/projects/65162) 
[![Coverage Status](https://coveralls.io/repos/ilm4zz4/dhcpServerApp/badge.svg?branch=develop)](https://coveralls.io/r/ilm4zz4/dhcpServerApp?branch=develop)

The project is based on the application at https://code.google.com/p/simple-dhcp-server.

To run this dhcp server application type the following command:

 - Download the project: git clone --recursive https://github.com/ilm4zz4/dhcpServerApp.git
 - Create a build folder: mkdir build && cd build 
 - Building: cmake .. && make 
 - With super user privilege run from *bin* folder: ./dhcpServerApp.bin ../../cfg/dhcp_log.conf  ../../cfg/dhcp_server.conf 
 - Into log folder is going to create the log file.

Other building options:
 - To run the test: cmake -Dtest=1 .. && make test && ./bin/runUnitTests






