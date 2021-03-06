#include <stdio.h>


/**
* Implementation of some string.h functions and some other custom functions
* (c) r47717
*/


/************************* some string.h functions ***************************/

typedef unsigned int size_t;

int strlen(const char *str);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *str1, const char *str2, size_t n);
char* strcpy(char *s1, const char *s2);
char* strncpy(char *s1, const char *s2, size_t n);
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
	const char *tmp = str;
	while (*tmp) {
		tmp++;
	}
	return tmp - str;
}

int strcmp(const char *s1, const char *s2) {
	while (*s1 && *s2) {
		if (*s1 > *s2) return 1;
		if (*s1 < *s2) return -1;
		s1++;
		s2++;
	}

	if (*s1 && !*s2)
		return 1;
	if (!*s1 && *s2)
		return -1;

	return 0;
}

int strncmp(const char *s1, const char *s2, size_t n) {
	if (n <= 0)
		return 0;

	while (*s1 && *s2 && n) {
		if (*s1 > *s2) return 1;
		if (*s1 < *s2) return -1;
		s1++;
		s2++;
		n--;
	}

	if (n && *s1 && !*s2)
		return 1;
	if (n && !*s1 && *s2)
		return -1;

	return 0;
}

char* strcpy(char *s1, const char *s2) {
	char *save = s1;
	while (*s2)
		*s1++ = *s2++;
	*s1 = 0;
	return save;
}

char* strncpy(char *s1, const char *s2, size_t n) {
	char *save = s1;
	if (n <= 0) {
		*s1 = 0;
		return s1;
	}

	while (n && *s2) {
		*s1++ = *s2++;
		n--;
	}
	*s1 = 0;
	return save;
}

char* strcat(char *dest, const char *src) {
	char *res = dest;
	while (*dest) dest++;
	while (*src) *dest++ = *src++;
	*dest = 0;
	return res;
}

char* strncat(char *dest, const char *src, size_t n) {
	char *res = dest;
	if (n <= 0)
		return dest;
	while (*dest) dest++;
	while (*src && n--) *dest++ = *src++;
	*dest = 0;
	return res;
}

char* strchr(const char *str, char c) { /* Searches for the first occurrence of the character c */
	while (*str) {
		if (*str == c) 
			return (char*)str;
		str++;
	}

	return NULL;
}

char* strstr(const char *haystack, const char *needle) { /* Finds the first occurrence of the entire string needle */
	if (*needle == 0)
		return NULL;

	while (*haystack) {
		const char *hay = haystack;
		const char *need = needle;
		while (*need && *hay == *need) {
			hay++;
			need++;
		}
		if (*need == 0)
			return (char*)haystack;
		haystack++;
	}
	return NULL;
}

char* strtoupper(char *str) {
	char *tmp = str;
	while (*tmp) {
		if (*tmp >= 'a' && *tmp <= 'z')
			*tmp += 'A' - 'a';
		tmp++;
	}
	return str;
}

char* strtolower(char *str) {
	char *tmp = str;
	while (*tmp) {
		if (*tmp >= 'A' && *tmp <= 'Z')
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
	return strreplace(from, str, "");
}

char* strcutch(char *str, char c) { /* cuts all occurrences of character 'c'from string 'str' */
	char *save = str;
	char *from = str;
	char *to = str;
	while (*from) {
		if (*from == c)
			from++;
		else
			*to++ = *from++;
	}
	*to = 0;
	return save;
}

#define STR_MAX_LEN 2048

char* strreplace(char *str, const char *from, const char *to) { /* replaces all occurrences of 'from' with 'to' in 'str' */
	char buf[STR_MAX_LEN + 1];
	char *newstr = buf;
	char *oldstr = str;

	if (*str == 0 || *from == 0)
		return str;

	while (*oldstr) {
		const char *fromtmp = from;
		char *oldtmp = oldstr;
		while (*oldtmp == *fromtmp && *fromtmp != 0) {
			oldtmp++;
			fromtmp++;
		}
		if (*fromtmp == 0) { /* 'from' string found */
			char *totmp = (char *)to;
			while (*totmp) {
				*newstr++ = *totmp++;
			}
			oldstr = oldtmp;
		}
		else { /* not found */
			do {
				*newstr++ = *oldstr++;
			} while (oldstr <= oldtmp);
		}
	}
	*newstr = 0;
	strcpy(str, buf);

	return str;
}

char* strrev(char *str) { /* reverses the string */
	char *start = str;
	char *end = str;

	if (*str == 0)
		return str;
	while (*end) end++;
	end--;
	while (start < end) {
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
	return strrtrim(str);
}

char* strrtrim(char *str) { /* removes whitespaces on the right */
	char *tmp = str;

	if (*str == 0)
		return str;

	while (*tmp)
		tmp++;

	while (iswhitespace(*--tmp)) {
		if (tmp == str) {
			*tmp = 0;
			break;
		}
	}
	tmp[1] = 0;

	return str;
}

char* strltrim(char *str) { /* removes whitespaces on the left */
	char *save = str;
	char *from = str;
	char *to = str;

	if (str == NULL || *str == 0)
		return str;

	while (iswhitespace(*from))
		from++;

	while (*from)
		*to++ = *from++;
	*to = 0;

	return save;
}

char* strcompact(char *str) { /* trims and reduces whilespace sequences inside string */
	char *from = str;
	char *to = str;
	int ws = 0;

	if (str == NULL || *str == 0)
		return str;

	str = strtrim(str);

	while (*from) {
		if (iswhitespace(*from)) {
			if (ws)
				from++;
			else {
				*to++ = *from++;
				ws = 1;
			}
		}
		else {
			*to++ = *from++;
			ws = 0;
		}
	}
	*to = 0;

	return str;
}


/************************** TESTS ******************************/

int tests_run = 0;
int tests_passed = 0;
int tests_failed = 0;

int test(char * descr, int value) {
	tests_run++;
	if (!value) {
		printf("Test '%s' failed\n", descr);
		tests_failed++;
	}
	else {
		printf("Test '%s' successful\n", descr);
		tests_passed++;
	}

	return value;
}


int main()
{
	char buf1[255] = "";
	char buf2[255] = "";
	char buf3[255] = "";

	/*int strlen(const char *str);*/

	test("strlen 1", strlen("Hello") == 5);
	test("strlen 2", strlen("") == 0);
	test("strlen 3", strlen("werjk345348u9rtjk  owerwer89 897 we%^%@^#%^ dasd") == 48);

	/*int strcmp(const char *s1, const char *s2);*/

	test("strcmp 1", strcmp("hello", "hello 2") == -1);
	test("strcmp 2", strcmp("", "hello") == -1);
	test("strcmp 3", strcmp("hello 2", "hello 2") == 0);
	test("strcmp 4", strcmp("hello 2", "hello") == 1);
	test("strcmp 5", strcmp("absde", "abrerer") == 1);
	test("strcmp 6", strcmp("absde", "") == 1);
	test("strcmp 7", strcmp("", "") == 0);


	/*int strncmp(const char *str1, const char *str2, size_t n);*/

	test("strNcmp 1", strncmp("hello", "hello 2", 5) == 0);
	test("strNcmp 2", strncmp("", "hello", 0) == 0);
	test("strNcmp 3", strncmp("hello 2", "hello 2", -1) == 0);
	test("strNcmp 4", strncmp("hello 2", "hello", 6) == 1);
	test("strNcmp 5", strncmp("absde", "abrerer", 2) == 0);
	test("strNcmp 6", strncmp("absde", "", 0) == 0);
	test("strNcmp 7", strncmp("", "", 1) == 0);

	/*void strcpy(char *s1, const char *s2);*/
	
	
	/*void strncpy(char *s1, const char *s2, size_t n);*/
	
	
	/*char* strcat(char *dest, const char *src);*/
	
	
	/*char* strncat(char *dest, const char *src, size_t n);*/
	
	
	/*char* strchr(const char *str, int c);*/ /* Searches for the first occurrence of the character c */
	
											  
	/*char* strstr(const char *haystack, const char *needle);*/ /* Finds the first occurrence of the entire string needle */
	
	test("strstr 1", strcmp(strstr("absde *&#12 fin me 1456 find me", "find me"), "find me") == 0);
	test("strstr 2", strstr("this is my sample string", "find me") == NULL);
	test("strstr 3", strstr("this is my sample string", "") == NULL);
	test("strstr 4", strstr("this is my sample string", "t")[0] == 't');
	test("strstr 5", strlen(strstr("this is my sample string", "st")) == 6);
	test("strstr 6", strstr("this is my sample string", " ")[1] == 'i');

	strcpy(buf1, "hello");
	strcpy(buf2, " world");
	strcat(buf1, buf2);
	strncpy(buf3, " test record", 5);
	strcat(buf1, buf3);
	test("strstr 7", strcmp(strstr(buf1, "wor"), "world test") == 0);


	/*char* strtoupper(char *str);*/

	strcpy(buf1, "abcde");
	test("strtoupper 1", strcmp(strtoupper(buf1), "ABCDE") == 0);
	strcpy(buf1, "ABCDE");
	test("strtoupper 2", strcmp(strtoupper(buf1), "ABCDE") == 0);
	strcpy(buf1, "ab2DE");
	test("strtoupper 3", strcmp(strtoupper(buf1), "AB2DE") == 0);
	test("strtoupper 4", strcmp(strtoupper(""), "") == 0);

	/*char* strtolower(char *str);*/

	strcpy(buf1, "ABCDE");
	test("strtolower 1", strcmp(strtolower(buf1), "abcde") == 0);
	strcpy(buf1, "abcde");
	test("strtolower 2", strcmp(strtolower(buf1), "abcde") == 0);
	strcpy(buf1, "ab2DE");
	test("strtolower 3", strcmp(strtolower(buf1), "ab2de") == 0);
	test("strtolower 4", strcmp(strtolower(""), "") == 0);

	/*char* strcutch(char *from, char c);*/ /* cuts all occurrences of character 'c'from string 'from' */
											
	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd");
	strcutch(buf1, 's');
	test("strcutch 1", strcmp(buf1, "ample 123 tring &#^EBJKHSDUHK8 878 kjlad 989 d dad") == 0);
	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd");
	strcutch(buf1, ' ');
	test("strcutch 2", strcmp(buf1, "sample123string&#^EBJKHSDUHK8878kjlasd989sdsdasd") == 0);
											 
	/*char* strcut(char *from, char *str);*/ /* cuts str substring out from 'from' */
    /*char* strreplace(char *str, const char *from, const char *to);*/ /* replaces all occurrences of 'from' with 'to' in 'str' */

	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd");
	strreplace(buf1, "string", "pepper");
	test("strreplace 1", strcmp(buf1, "sample 123 pepper &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd") == 0);

	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd");
	strreplace(buf1, "string", "");
	test("strreplace 2", strcmp(buf1, "sample 123  &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd") == 0);

	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd");
	strreplace(buf1, "&#^EBJKHSDUHK8 878 kjlasd", "hi");
	test("strreplace 3", strcmp(buf1, "sample 123 string hi 989 sd sdasd") == 0);

	strcpy(buf1, "");
	test("strreplace 4", strreplace(buf1, "&#^EBJKHSDUHK8 878 kjlasd", "hi")[0] == 0);

	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd");
	strreplace(buf1, "&#^EBJKHSDUHK8", "sample");
	test("strreplace 5", strcmp(buf1, "sample 123 string sample 878 kjlasd 989 sd sdasd") == 0);

	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd");
	strreplace(buf1, "sample 123 string &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd", "kuku");
	test("strreplace 6", strcmp(buf1, "kuku") == 0);

	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd");
	strreplace(buf1, "sample 123 string &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd", "");
	test("strreplace 7", strcmp(buf1, "") == 0);

	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 string878 kjlasd string989 sd sdasdstring");
	strreplace(buf1, "string", "ttt");
	test("strreplace 8", strcmp(buf1, "sample 123 ttt &#^EBJKHSDUHK8 ttt878 kjlasd ttt989 sd sdasdttt") == 0);

	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 string878 kjlasd string989 sd sdasdstring");
	strreplace(buf1, "string", "");
	test("strreplace 9", strcmp(buf1, "sample 123  &#^EBJKHSDUHK8 878 kjlasd 989 sd sdasd") == 0);

	strcpy(buf1, "sample 123 string &#^EBJKHSDUHK8 string878 kjlasd string989 sd sdasdstring");
	strreplace(buf1, "hello", "");
	test("strreplace 10", strcmp(buf1, "sample 123 string &#^EBJKHSDUHK8 string878 kjlasd string989 sd sdasdstring") == 0);

	strcpy(buf1, "sssssample 123 sstring &#^EBJKHSDUHK8 string878 kjlasd string989 sd sdasdstringss");
	strreplace(buf1, "s", "mm");
	test("strreplace 11", strcmp(buf1, "mmmmmmmmmmample 123 mmmmtring &#^EBJKHSDUHK8 mmtring878 kjlammd mmtring989 mmd mmdammdmmtringmmmm") == 0);

	strcpy(buf1, "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
	strreplace(buf1, "h", "");
	test("strreplace 12", strcmp(buf1, "") == 0);

	strcpy(buf1, "h");
	strreplace(buf1, "h", "t");
	test("strreplace 13", strcmp(buf1, "t") == 0);

	strcpy(buf1, "h");
	strreplace(buf1, "h", "");
	test("strreplace 14", strcmp(buf1, "") == 0);

	strcpy(buf1,                       "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh");
	strreplace(buf1, "h", "tt");
	test("strreplace 15", strcmp(buf1, "tttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt") == 0);

	/*char* strrev(char *str);*/ /* reverses the string */

	strcpy(buf1, "123456789");
	test("strrev 1", strcmp(strrev(buf1), "987654321") == 0);

	strcpy(buf1, "1 2 3 4 5 6 7 8 9 ");
	test("strrev 2", strcmp(strrev(buf1), " 9 8 7 6 5 4 3 2 1") == 0);

	strcpy(buf1, "1");
	test("strrev 3", strcmp(strrev(buf1), "1") == 0);

	strcpy(buf1, "");
	test("strrev 4", strcmp(strrev(buf1), "") == 0);

	/*char* strtrim(char *str);*/ /* removes whitespaces */
    /*char* strrtrim(char *str);*/ /* removes whitespaces on the right */
	/*char* strltrim(char *str);*/ /* removes whitespaces on the left */

	strcpy(buf1, "  dsdsd sdsds   dsds    ");
	test("strtrim 1", strcmp(strtrim(buf1), "dsdsd sdsds   dsds") == 0);

	strcpy(buf1, "  dsdsd sdsds   dsds    ");
	test("strtrim 2", strcmp(strrtrim(buf1), "  dsdsd sdsds   dsds") == 0);

	strcpy(buf1, "  dsdsd sdsds   dsds    ");
	test("strtrim 3", strcmp(strltrim(buf1), "dsdsd sdsds   dsds    ") == 0);

	strcpy(buf1, "   ");
	test("strtrim 4", strcmp(strtrim(buf1), "") == 0);

	strcpy(buf1, "");
	test("strtrim 5", strcmp(strtrim(buf1), "") == 0);

	/*char* strcompact(char *str);*/ /* reduces whilespace sequences inside string */

	strcpy(buf1, "  dsdsd  sdsds   dsds    ");
	test("strcompact 1", strcmp(strcompact(buf1), "dsdsd sdsds dsds") == 0);

	strcpy(buf1, "     ");
	test("strcompact 2", strcmp(strcompact(buf1), "") == 0);

	strcpy(buf1, "");
	test("strcompact 3", strcmp(strcompact(buf1), "") == 0);

	strcpy(buf1, "\t\t\t\t\t\n\n\n\t\t");
	test("strcompact 4", strcmp(strcompact(buf1), "") == 0);


	printf("\nTesting summary:\n");
	printf("\tTests run: %d\n", tests_run);
	printf("\tTests failed: %d\n", tests_failed);
	printf("\tTests passed: %d\n", tests_passed);
	if (tests_failed == 0)
		printf("ALL TESTS PASSED\n");

	return tests_failed == 0;
}
