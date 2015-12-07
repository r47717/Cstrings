/**
* Implementation of some string.h functions and some other custom functions
* (c) r47717
*/

/************************* some string.h functions ***************************/

typedef unsigned int size_t;

int strlen(const char *str);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *str1, const char *str2, size_t n);
void strcpy(char *s1, const char *s2);
void strncpy(char *s1, const char *s2, size_t n);
char* strcat(char *dest, const char *src); 
char* strncat(char *dest, const char *src, size_t n); 
char* strchr(const char *str, int c); /* Searches for the first occurrence of the character c */
char* strstr(const char *haystack, const char *needle); /* Finds the first occurrence of the entire string needle */
char* strtoupper(char *str);
char* strtolower(char *str);

/************************* custom string functions ***************************/

char* strcut(char *from, char *str); /* cuts str substring out from 'from' */ 
char* strcutch(char *from, char c); /* cuts all occurrences of character 'c'from string 'from' */
char* strreplace(char *str, const char *from, const char *to); /* replaces all occurrences of 'from' with 'to' in 'str' */
char* strrev(char *str); /* reverses the string */
char* strtrim(char *str); /* removes whitespaces */
char* strrtrim(char *str); /* removes whitespaces on the right */
char* strltrim(char *str); /* removes whitespaces on the left */
char* strcompact(char *str); /* reduces whilespace sequences inside string */

/************************* string.h implementation ***************************/

int strlen(const char *str) {
	char *tmp = str;
	while(*tmp++) {}
	return tmp - str;
}

int strcmp(const char *s1, const char *s2) {
	while(*s1 && *s2) {
		if(*s1 > *s2) return 1;
		if(*s1 < *s2) return -1;
		s1++;
		s2++;
	}
	return 0;
}

int strncmp(const char *str1, const char *str2, size_t n) {
	while(*s1 && *s2 && n--) {
		if(*s1 > *s2) return 1;
		if(*s1 < *s2) return -1;
		s1++;
		s2++;
	}
	return 0;
}

void strcpy(char *s1, char *s2) {
	while(*s2)
		*s1++ = *s2++;
}

void strncpy(char *s1, char *s2, size_t n) {
	while(n) {
		*s1++ = *s2++;
		n--;
	}
	*s1 = 0;
}

char *strcat(char *dest, const char *src) {
	char *res = dest;
	while(*dest++) {}
	while(*src) *dest++ = *src++;
	*dest = 0;
	return res;
}

char *strncat(char *dest, const char *src, size_t n) {
	char *res = dest;
	while(*dest++) {}
	while(*src && n--) *dest++ = *src++;
	*dest = 0;
	return res;
}

char *strchr(const char *str, int c) { /* Searches for the first occurrence of the character c */
	while(*str) {
		if(*str == c) return str;
		str++;
	}
}

char *strstr(const char *haystack, const char *needle) { /* Finds the first occurrence of the entire string needle */
	while(*haystack) {
		char *hay = haystack;
		char *need == needle;
		while(*need++ == *hay++) 
		{}
		if(*need == 0)
			break;
	}
	return haystack;
}

char* strtoupper(char *str) {
	char *tmp = str;
	while(*tmp) {
		if(*tmp >= 'a' && *tmp <= 'z')
			*tmp += 'A' - 'a';
		tmp++;
	}
	return str;
}

char* strtolower(char *str) {
	char *tmp = str;
	while(*tmp) {
		if(*tmp >= 'A' && *tmp <= 'Z')
			*tmp -= 'A' - 'a';
		tmp++;
	}
	return str;
}

/************************* custom functions implementation ***************************/

static int iswhitespace(char c) {
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

char* strcut(char *from, char *str) { /* cuts str substring out from 'from' */ 
	return strreplace(from, "");
}

char* strcutch(char *from, char c) { /* cuts all occurrences of character 'c'from string 'from' */
	char *save = str;
	char *from = str;
	char *to = str;
	while(*from) {
		if(*from == c)
			from++;
		else
			*to++ = *from++;
	}
	*to = 0;
	return save;
}

char* strreplace(char *str, const char *from, const char *to) { /* replaces all occurrences of 'from' with 'to' in 'str' */
	char *p1 = str;
	char *p2 = str;
	while(*p2) {
		
	}
}

char* strrev(char *str) { /* reverses the string */
	char *start = str;
	char *end = str;
	
	if(*str == 0)
		return str;
	while(*end) end++;
	end--;
	while(start < end) {
		char c;
		c = *start;
		*start = *end;
		*end = c;
		start++; end--;
	}
	return str;
}

char* strtrim(char *str) { /* removes whitespaces */
	strltrim(str);
	strrtrim(str);
}

char* strrtrim(char *str) { /* removes whitespaces on the right */
	char *tmp = str;
	if(*str == 0)
		return str;
	while(*tmp) 
		tmp++;
	while(1) {
		if(iswhitespace(*--tmp)) {
			if(tmp == str) {
				*tmp = 0;
				break;
			}
		} else {
			tmp[1] = 0;
			break;
		}
	}
	return str;
}

char* strltrim(char *str) { /* removes whitespaces on the left */
	char *save = str;
	char *from = str;
	char *to = str;
	while(*from) {
		if(iswhitespace(*from))
			from++;
		else
			*to++ = *from++;
	}
	*to = 0;
	return save;
}

char* strcompact(char *str) { /* reduces whilespace sequences inside string */
	char *from = str;
	char *to = str;
	int ws = 0;
	
	while(*from) {
		if(iswhitespace(*tmp) {
			if(ws)
				from++;
			else {
				*to++ = *from++;
				ws = 1;
			}
		} else
			*to++ = *from++;
	}
	*to = 0;
	return str;
}



