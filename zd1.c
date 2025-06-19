#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void print_usernames();

int main(){
	print_usernames();
	return 0;
}

void print_usernames(){
	FILE *file = popen("getent passwd", "r");
	if (!file){
		printf("error running the command");
		return;
	}
	char line[256];
	uid_t my_userID = getuid();

	while(fgets(line, sizeof(line), file)){
		char *username = strtok(line, ":");
		strtok(NULL, ":"); //password
		char *uid = strtok(NULL, ":");
		if(atoi(uid) >= 1000 && atoi(uid) != my_userID){
			printf("%s \n", username);
		}
	}
	pclose(file);
}
