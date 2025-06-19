# Lab9

# Завдання 1

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

# Завдання 2

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

# Завдання 3

## Опис

Ця програма на мові C виконує дві системні команди:
- `whoami` — для виведення імені поточного користувача
- `id` — для виведення UID, GID та списку груп, до яких належить користувач

Програма демонструє:
- хто зараз виконує програму
- до яких груп належить цей користувач (включаючи вторинні групи)

``` C
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
```

# Завдання за варіантом `17`
## Опис

У Unix-подібних системах `sudo` дозволяє звичайним користувачам виконувати команди від імені адміністратора (root). Зазвичай це вимагає введення пароля. Проте іноді адміністратори спрощують доступ, додаючи `NOPASSWD`, що дозволяє виконувати `sudo` без жодної перевірки особи.

> Приклад небезпечного запису у файлі `/etc/sudoers`:
> ```
> user ALL=(ALL) NOPASSWD:ALL
> ```

---

## ⚠Загрози та ризики

### 1. Компрометація одного облікового запису = root-доступ

Будь-який злом або перехоплення акаунту користувача (через фішинг, вразливість або брутфорс) дозволяє зловмиснику миттєво отримати повний контроль над системою.

---

### 2. Можливість постійного бекдору

Користувач без пароля може:
- Встановити rootkit або троян
- Додати себе до `cron` для запуску бекдорів
- Відключити антивірусні або моніторингові системи

---

### 3. Шпигування та витік даних

Root-доступ дозволяє:
- Читати вміст будь-якого користувацького каталогу
- Прослуховувати мережеві інтерфейси (`tcpdump`)
- Збирати SSH-ключі, файли cookie, паролі

---

### 4. Відсутність контролю за діями

- Всі `sudo`-операції відбуваються без підтвердження, тому не можна відслідкувати, чи вони авторизовані.
- Будь-які критичні дії (видалення файлів, перезавантаження, вимкнення сервісів) можуть бути виконані непомітно.

---

### 5. Недотримання політик безпеки

- Не відповідає стандартам: ISO 27001, CIS Benchmarks, NIST 800-53
- Порушує базові принципи контрольованого доступу та мінімізації повноважень
