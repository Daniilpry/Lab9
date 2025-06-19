#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	FILE *file1 = popen("whoami", "r");
	if (!file1){
		printf("error running command\n");
		return 1;
	}
	char line1[256];
	fgets(line1, sizeof(line1), file1);
	printf("result of whoami command -> %s", line1);
	pclose(file1);

	FILE *file2 = popen("id", "r");
	if (!file2){
		printf("error running command\n");
                return 1;
        }
        char line2[256];
        fgets(line2, sizeof(line2), file2);
        printf("result of id command -> %s", line2);
        pclose(file2);
}
