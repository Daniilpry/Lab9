#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void shadow();

int main(){
        shadow();
        return 0;
}

void shadow(){
        FILE *file = popen("sudo cat /etc/shadow", "r");
        if (!file){
                printf("error running the command");
                return;
        }
        char line[256];
        while(fgets(line, sizeof(line), file)){
        	printf("%s", line);
        }
        pclose(file);
}
