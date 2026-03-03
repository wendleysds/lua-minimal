#include <stddef.h>

void* memset(void* ptr, int c, unsigned long size){
	char* temp = (char*) ptr;

	for(unsigned long i = 0; i < size; i++){
		temp[i] = (char) c;
	}

	return ptr;
}

void* memcpy(void* dest, const void* src, unsigned long length){
	char *d = (char*)dest;
	const char *s = (const char*)src;

	if(d < s){
		while(length--){
			*d++ = *s++;
		}
	}
	else{
		while(length--){
			*(d + length) = *(s + length);
		}
	}

	return dest;
}

int memcmp(const void* s1, const void* s2, int count){
	const unsigned char *c1 = s1;
	const unsigned char *c2 = s2;

	while(count-- > 0){
		if(*c1++ != *c2++){
			return c1[-1] < c2[-1] ? -1 : 1;
		}
	}

	return 0;
}

void* memmove(void *dest, const void *src, unsigned long n){
	char *d = (char *)dest;
	const char *s = (const char *)src;

	if(d < s || d >= s + n) {
		// Non-overlapping regions, copy forwards
		while(n--) {
			*d++ = *s++;
		}
	} else {
		// Overlapping regions, copy backwards
		d += n;
		s += n;
		while(n--) {
			*(--d) = *(--s);
		}
	}

	return dest;
}

size_t strlen(const char *s){
	const char *p;
	for (p = s; *p; ++p);
	return (p - s);
}

size_t strnlen(const char *s, size_t maxlen){
	size_t i = 0;
	for(; i < maxlen; i++){
		if(!s[i]) break;
	}

	return i;
}

int strcmp(const char *s1, const char *s2){
	while (*s1 && *s1 == *s2) ++s1, ++s2;
	return (*s1 > *s2) - (*s2  > *s1);
}

char *strchr(const char *s, int c){
    while (*s) {
        if (*s == (char)c)
            return (char*)s;
        s++;
    }

    return c == 0 ? (char*)s : NULL;
}

char* strtok(char *restrict s, const char *restrict delim){
	static char* p = NULL;
	if(s)
		p = s;

	if(!p)
		return NULL;

	while(*p && strchr(delim, *p)){
		p++;
	}

	if(*p == '\0')
		return NULL;

	char* t = p;

	while(*p && !strchr(delim, *p)){
		p++;
	}

	if(*p){
		*p = '\0';
		p++;
	}

	return t;
}

char *strpbrk(const char *str1, const char *str2){
	if (str1 == NULL || str2 == NULL)
		return NULL;

	const char *temp;
	while (*str1 != '\0'){
		temp = str2;
		while (*temp != '\0'){
			if (*str1 == *temp)
				return (char *) str1;
			temp++;
		}

		str1++;
	}

	return NULL;
}

char* strcpy(char *restrict dst, const char *restrict src){
	while ((*dst++ = *src++));
	return dst;
}

long strspn(const char *s1, const char *s2) {
    long len = 0;
    while (s1[len] && strchr(s2, s1[len])) len++;
    return len;
}

// No one is gonna know
int strcoll(const char *s1, const char *s2){
	return strcmp(s1, s2);
}
