#Makefile to compile 'dhcpServerApp'  -MM -MF $(patsubst %.o,%.d,$@) 

#FOLDER
ROOT_PRJ=..
BIN_DIR=$(ROOT_PRJ)/bin
OBJ_DIR=$(ROOT_PRJ)/obj
CFG_DIR=$(ROOT_PRJ)/cfg
SRC_DIR=$(ROOT_PRJ)/src
INC_DIR=$(ROOT_PRJ)/inc

#FILE
BIN_FILE=$(BIN_DIR)/dhcpServerApp.bin

OBJs+=$(OBJ_DIR)/dhcp_server.o 
OBJs+=$(OBJ_DIR)/dhcp_packet.o 
OBJs+=$(OBJ_DIR)/dhcp_log.o
OBJs+=$(OBJ_DIR)/ip_allocator.o

#LIBRARY
LIB= -lpthread -lsqlite3 

#FLAGs
FLAGs=-g

#TARGET
all: folder $(OBJs)
	$(CC) $(FLAGs) $(OBJs) -o $(BIN_FILE) $(LIB) 
	@echo "Build is done..."


clean:
	@rm -rf $(BIN_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "Clean is complete..."


folder:
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)


$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	$(CC) -MD -MF $(patsubst %.o,%.d,$@) -c $(FLAGs) -I$(INC_DIR) -o  $@  $<
#dhcp_server: server.o packet.o log.o ip_allocator.o
#	$(CC) -lpthread -lsqlite3 -g -o dhcp_server server.o packet.o log.o ip_allocator.o
#
#server.o: dhcp_server.c ip_allocator.c dhcp_log.h dhcp_server.h dhcp_packet.h
#	$(CC) -g -c dhcp_server.c -o server.o
#
#packet.o: dhcp_packet.c dhcp_log.h dhcp_packet.h
#	$(CC) -g -c dhcp_packet.c -o packet.o
#	
#log.o: dhcp_log.c dhcp_log.h
#	$(CC) -g -c dhcp_log.c -o log.o
#ip_allocator.o: ip_allocator.c dhcp_server.h
#	$(CC) -lsqlite3 -g -c ip_allocator.c -o ip_allocator.o
#
#clean:
#	rm dhcp_server server.o packet.o log.o ip_allocator.o
