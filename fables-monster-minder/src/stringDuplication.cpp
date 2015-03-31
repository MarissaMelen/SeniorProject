#include "stringDuplication.hpp"
#include <cstdlib>
#include <cstring>

char *cust_strdup(const char *str) {
	int length = strlen(str)+1;
	char *temp = (char *)malloc(sizeof(char) * length);
	if (temp == nullptr) {
		return nullptr;
	}
	memcpy(temp, str, length);

	return temp;
}

