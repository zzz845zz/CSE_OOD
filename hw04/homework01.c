#include <stdio.h>

int main() {
	char str[100] = "";

	printf("문자를 입력하세요(100자 이내).\n");
	scanf("%s", str);
	printf("입력된 문자는 %s 입니다.\n", str);
	return 0;
}
