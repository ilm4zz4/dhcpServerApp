#include "dhcp_server.h"
#include "dhcp_log.h"
#include "stdio.h"
#include <unistd.h>
#include <sys/types.h>
int main(int argc, char* argv[])
{
	if (setuid(0) == -1){
		printf("\nERROR: you need the root privileges\n\n");
		return -1;
	}
	
	printf("\n==> The application is started, check log...\n\n");
	
	//check args
	if(argc > 2){
	   log_init(argv[1]);
	   start_server(argv[2]);
	}else{
	   fprintf(stderr,"Invoce the %s with log configuration file and configuration server\n\n\t %s ../cfg/dhcp_log.conf  ../cfg/dhcp_server.conf \n\n", argv[0], argv[0]);	
	}

	   fprintf(stderr,"exit application\n\n");	
}
