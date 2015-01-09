#Makefile to compile 'dhcpServerApp'  -MM -MF $(patsubst %.o,%.d,$@) 

#FOLDER
ROOT_PRJ=..
BIN_DIR=$(ROOT_PRJ)/bin
OBJ_DIR=$(ROOT_PRJ)/obj
CFG_DIR=$(ROOT_PRJ)/cfg
SRC_DIR=$(ROOT_PRJ)/src
INC_DIR=$(ROOT_PRJ)/inc
LOG_DIR=$(ROOT_PRJ)/log
LIB_DIR=$(ROOT_PRJ)/lib
GTEST_FOLDER=$(ROOT_PRJ)/test/googletest/
FOLDER=$(BIN_DIR) $(OBJ_DIR) $(LOG_DIR) $(LOG_DIR) $(LIB_DIR)

#FILE
BIN_FILE=$(BIN_DIR)/dhcpServerApp.bin

OBJs+=$(OBJ_DIR)/dhcp_server.o 
OBJs+=$(OBJ_DIR)/dhcp_packet.o 
OBJs+=$(OBJ_DIR)/dhcp_log.o
OBJs+=$(OBJ_DIR)/ip_allocator.o

#LIBRARY
LIB_SYS= -lpthread -lsqlite3 
LIB_TEST=$(LIB_DIR)/libgtest.a

#FLAGs
FLAGs=-g

#TARGET
all: .folderAdd $(OBJs)
	$(CC) $(FLAGs) $(OBJs) -o $(BIN_FILE) $(LIB_SYS) 
	@echo "Building is done..."


clean:.folderDel
	@echo "Clean is complete..."

test: .folderAdd $(LIB_TEST)




.folderAdd:
	@mkdir -p $(FOLDER)

.folderDel:
	@rm -rf $(FOLDER)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) -MD -MF $(patsubst %.o,%.d,$@) -c $(FLAGs) -I$(INC_DIR) -o  $@  $<

$(LIB_TEST):
	$(shell cd $(GTEST_FOLDER) && cmake . && cd $(ROOT_FOLDER)/makefile)
	@make -C ../test/googletest/
	@mkdir -p ../lib
	@cp -f  ../test/googletest/libgtest.a ../lib
