# Lab9

# Завдання 9.1

## Опис

Ця програма на C виконує команду `getent passwd`, щоб зчитати список усіх облікових записів у системі. Далі вона перевіряє, які з них є звичайними користувачами (UID ≥ 1000 або ≥ 500 — залежно від дистрибутива), та виключає поточного користувача з результатів.

## Реалізація 

``` C
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
```

# Завдання 9.2

## Опис

Ця програма демонструє, як звичайний користувач може виконати адміністративну команду (`cat /etc/shadow`) за допомогою `sudo`, якщо конфігурація системи це дозволяє.
> ⚠Файл `/etc/shadow` зберігає хеші паролів усіх користувачів системи і зазвичай захищений від читання. Тому команда потребує прав суперкористувача.

---

## Реалізація 

``` C
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
```
