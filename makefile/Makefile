#Makefile to compile 'dhcpServerApp' 

#FOLDER
ROOT_PRJ=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))/..
BIN_DIR=$(ROOT_PRJ)/bin
OBJ_DIR=$(ROOT_PRJ)/obj
CFG_DIR=$(ROOT_PRJ)/cfg
SRC_DIR=$(ROOT_PRJ)/src
INC_DIR=$(ROOT_PRJ)/inc
LOG_DIR=$(ROOT_PRJ)/log
LIB_DIR=$(ROOT_PRJ)/lib

GTEST_FOLDER=$(ROOT_PRJ)/test/googletest
FOLDER=$(BIN_DIR) $(OBJ_DIR) $(LOG_DIR) $(LOG_DIR) $(LIB_DIR)

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
	$(CC) $(FLAGs) $(OBJs) -o $(BIN_FILE) $(LIB_SYS) 
	@echo "Building is done..."


clean:.folderDel .generateFileDel
	@echo "Clean is complete..."

test: .folderAdd $(LIB_TEST)


.folderAdd:
	@mkdir -p $(FOLDER)

.folderDel:
	@rm -rf $(FOLDER)
.generateFileDel:
	@rm -rf $(GTEST_FOLDER)/CMakeCache.txt
	@rm -rf $(GTEST_FOLDER)/CMakeFiles/
	@rm -rf $(GTEST_FOLDER)/Makefile
	@rm -rf $(GTEST_FOLDER)/cmake_install.cmake
	@rm -rf $(GTEST_FOLDER)/libgtest.a
	@rm -rf $(GTEST_FOLDER)/libgtest_main.a

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) -MD -MF $(patsubst %.o,%.d,$@) -c $(FLAGs) -I$(INC_DIR) -o  $@  $<

$(LIB_TEST):
	bash -c 'cd $(GTEST_FOLDER) &&  cmake . && make' 
	@echo "lib libgtest.a and libgtest_main.a are copied into lib folder"
	@cp $(GTEST_FOLDER)/libgtest.a $(LIB_DIR) 
	@cp $(GTEST_FOLDER)/libgtest_main.a $(LIB_DIR) 

