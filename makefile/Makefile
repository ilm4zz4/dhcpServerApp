#Makefile to compile 'dhcpServerApp' 

#FOLDER
ROOT_PRJ=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/..
BIN_DIR=$(ROOT_PRJ)/bin
OBJ_DIR=$(ROOT_PRJ)/obj
SRC_DIR=$(ROOT_PRJ)/src
INC_DIR=$(ROOT_PRJ)/inc
LOG_DIR=$(ROOT_PRJ)/log

#GTEST_FOLDER=$(ROOT_PRJ)/test/googletest
FOLDER=$(BIN_DIR) $(OBJ_DIR) $(LOG_DIR)

#FILE
BIN_FILE=$(BIN_DIR)/dhcpServerApp.bin

OBJs+=$(OBJ_DIR)/dhcp_server.o 
OBJs+=$(OBJ_DIR)/dhcp_packet.o 
OBJs+=$(OBJ_DIR)/dhcp_log.o
OBJs+=$(OBJ_DIR)/ip_allocator.o

#LIBRARY
LIB_SYS= -lpthread -lsqlite3 
LIB_TEST+=$(LIB_DIR)/libgtest.a
LIB_TEST+=$(LIB_DIR)/libgtest_main.a

#FLAGs
FLAGs=-g 

#TARGET
all: .folderAdd $(OBJs)
	$(CC) $(FLAGs) -I$(INC_DIR) $(OBJs) ../src/main.c  -o $(BIN_FILE) $(LIB_SYS) 
	@echo "Building is done..."


clean: .folderDel
	@$(MAKE) -C ../test/makefile $@ 
	@echo "Clean is complete..."

test:   all 
	git submodule update --init
	rm -rf $(BIN_DIR)/unittest ../test/bin/unittest
	$(MAKE) -C  ../test/makefile all 
	

.folderAdd:
	@mkdir -p $(FOLDER)

.folderDel:
	@rm -rf $(FOLDER)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) -MD -MF $(patsubst %.o,%.d,$@) -c $(FLAGs) -I$(INC_DIR) -o  $@  $<

