#include "s21_string.h"

// 1
void *s21_memchr(const void *str, int c, s21_size_t n) {
    char *s = (char*)str;
    for (; n > 0 && *s != c; n--, s++) {}
    return !n ? S21_NULL: s;
}

// 2
int s21_memcmp(const void * str1, const void * str2, s21_size_t n) {
    int result = 0;
    for (s21_size_t i = 0; i < n && !result; i++)
        if (*((char*)str1+i) != *((char*)str2+i))
            result = *((char*)str1+i) - *((char*)str2+i);
    return result;
}

// 3
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++)
        *((char*)dest+i) = *((char*)src+i);
    return dest;
}

// 4
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
    if (dest < src) {
        s21_memcpy(dest, src, n);
    } else {
        char *d = (char*)dest + n;
        char *s = (char*)src + n;
        while (n--)
            *--d = *--s;
    }
    return dest;
}

// 5
void *s21_memset(void *str, int c, s21_size_t n) {
    for (s21_size_t i = 0; i < n; i++)
        *((char*)str+i) = c;
    return str;
}

// 6
char *s21_strcat(char *dest, const char *src) {
    s21_size_t len = s21_strlen(dest);
    s21_strcpy(dest + len, src);
    return dest;
}

// 7
char *s21_strchr(const char *str, int c) {
    char *result = NULL;
    for (s21_size_t i = 0; i < s21_strlen(str) + 1 && !result; i++)
        if (str[i] == c)
            result = (char*)str+i;
    return result;
}

// 8
int s21_strcmp(const char *str1, const char *str2) {
    int res = *str1 - *str2;
    for (int i = 0; (str1[i] || str2[i]) && !res; i++)
        if (str1[i] != str2[i])
            res = str1[i] - str2[i];
    return res;
}

// 9
char *s21_strcpy(char *dest, const char *src) {
    s21_size_t len = s21_strlen(src);
    for (s21_size_t i = 0; i < len + 1; i++) {
        dest[i] = src[i];
    }
    return dest;
}

// 10
s21_size_t s21_strcspn(const char *str1, const char *str2) {
    s21_size_t count = 0, check = 0;
    s21_size_t len1 = s21_strlen(str1);
    s21_size_t len2 = s21_strlen(str2);
    for (s21_size_t i = 0; i < len1 && !check; i++) {
        for (s21_size_t j = 0; j < len2 && !check; j++)
            if (str1[i] == str2[j])
                check = 1;
        if (!check)
            count++;
    }
    return count;
}

// 11
void s21_reverse(char *str) {
    int k, j;
    for (k = 0, j = s21_strlen(str) - 1; k < j; k++, j--) {
        char buf = str[k];
        str[k] = str[j];
        str[j] = buf;
    }
}

void s21_itoa(int n, char* str) {
    int i = 0;
    long int x = n;
    if (n < 0)
        x *= -1;
    if (!x)
        str[i++] = '0';
    while (x > 0) {
        str[i] = x % 10 + '0';
        i++;
        x /= 10;
    }
    if (n < 0) {
        str[i] = '-';
        i++;
    }
    str[i] = '\0';
    s21_reverse(str);
}

char *s21_strerror(int errnum) {
    char *text = S21_NULL;
    if (errnum < 0 || errnum > ERRLIST_LEN - 1) {
        static char unk[33] = "Unknown error";
        if (ERRLIST_LEN == APPL) {
            char tmp[33] = ": ";
            s21_strcat(unk, tmp);
        } else {
            char tmp[33] = " ";
            s21_strcat(unk, tmp);
        }
        char err[33] = "";
        s21_itoa(errnum, err);
        s21_strcat(unk, err);
        text = unk;
    } else {
        static char *spisok[] = ERRLIST;
        text = (char*)spisok[errnum];
    }
    return text;
}

// 12
s21_size_t s21_strlen(const char *str) {
    s21_size_t len = 0;
    for (; str[len]; len++) {}
    return len;
}

// 13
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
    char *end = dest + s21_strlen(dest);
    while (n-- && *src)
        *end++ = *src++;
    *end = '\0';
    return dest;
}

// 14
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
    int res = 0;
    for (int i = 0; !res && n--; i++)
        if (str1[i] != str2[i])
            res = str1[i] - str2[i];
    return res;
}

// 15
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
    char *result = dest;
    while (n-- && *src)
        *dest++ = *src++;
    if (n > 0)
        *dest = '\0';
    return result;
}

// 16
char *s21_strpbrk(const char *str1, const char *str2) {
    s21_size_t len1 = s21_strlen(str1);
    s21_size_t len2 = s21_strlen(str2);
    char *res = S21_NULL;
    for (s21_size_t i = 0; i < len1 && !res; i++)
        for (s21_size_t j = 0; j < len2 && !res; j++)
            if (str1[i] == str2[j])
                res = (char*)str1 + i;
    return res;
}

// 17
char *s21_strrchr(const char *str, int c) {
    if (!*str)
        return S21_NULL;
    char *res = S21_NULL;
    for (int i = (int)s21_strlen(str); i >= 0 && !res; i--)
        if (str[i] == c)
            res = (char*)(str+i);
    return res;
}

// 18
s21_size_t s21_strspn(const char *str1, const char *str2) {
    s21_size_t count = 0, check = 0;
    s21_size_t len1 = s21_strlen(str1);
    s21_size_t len2 = s21_strlen(str2);
    for (s21_size_t k = 0; k < len2; k++)
        if (str1[0] == str2[k])
            check++;
    s21_size_t flag = 1;
    for (s21_size_t i = 0; i < len1 && flag; i++) {
        flag = 0;
        for (s21_size_t j = 0; j < len2 && !flag; j++) {
            if (str1[i] == str2[j]) {
                count++;
                flag = 1;
            }
        }
    }
    return !check? 0: count;
}

// 19
char *s21_strstr(const char *str1, const char *str2) {
    if (!*str2)
        return (char*)str1;
    char *str = S21_NULL;
    s21_size_t len1 = s21_strlen(str1);
    s21_size_t len2 = s21_strlen(str2);
    int res = 0;
    for (s21_size_t i = 0; i < len1 && !res; i++) {
        s21_size_t count = 0;
        for (s21_size_t j = 0; j < len2; j++) {
            str = (char*)(str1+i);
            while (i < len1 && j < len2 && str1[i] == str2[j]) {
                i++;
                j++;
                count++;
            }
            if (count == len2)
                res = 1;
        }
    }
return res? str: S21_NULL;
}

// 20
char *s21_strtok(char *str, const char *delim) {
    static char *new;
    if (str) {
        new = str;
        while (s21_strchr(delim, *new))
            *new++ = '\0';
    }
    int endofnew = 0;
    if (!*new) {
        endofnew = 1;
    } else {
    str = new;
    while (*new && !s21_strchr(delim, *new))
        new++;
    while (*new && s21_strchr(delim, *new))
        *new++ = '\0';
    }
    return endofnew? S21_NULL: str;
}

// 21
void *s21_to_lower(const char *str) {
    char *lower_str = S21_NULL;
    if (str) {
        s21_size_t len_lower = s21_strlen(str);
        lower_str = (char *)malloc((len_lower + 1) * sizeof(char));
        if (lower_str) {
            s21_strcpy(lower_str, str);
            for (char *temp_lower_str = lower_str; *temp_lower_str; temp_lower_str++) {
                if (*temp_lower_str >= 'A' && *temp_lower_str <= 'Z')
                    *temp_lower_str += 32;
            }
        }
    }
    return (void *)lower_str;
}

// 22
void *s21_to_upper(const char *str) {
    char *upper_str = S21_NULL;
    if (str) {
        s21_size_t len_upper = s21_strlen(str);
        upper_str = (char *)malloc((len_upper + 1) * sizeof(char));
        if (upper_str) {
            s21_strcpy(upper_str, str);
            for (char *temp_upper_str = upper_str; *temp_upper_str; temp_upper_str++) {
                if (*temp_upper_str >= 'a' && *temp_upper_str <= 'z')
                    *temp_upper_str -= 32;
            }
        }
    }
    return (void *)upper_str;
}

// 23
s21_size_t s21_right_strspn(const char *str1, const char *str2) {
    s21_size_t count = 0, check = 0;
    s21_size_t len1 = s21_strlen(str1);
    s21_size_t len2 = s21_strlen(str2);
    for (s21_size_t k = 0; k < len2; k++) {
        if (str1[len1 - 1] == str2[k])
            check++;
    }
    s21_size_t flag = 1;
    for (s21_size_t i = len1 - 1; i > 0 && flag; i--) {
        flag = 0;
        for (s21_size_t j = 0; j < len2 && !flag; j++) {
            if (str1[i] == str2[j]) {
                count++;
                flag = 1;
            }
        }
    }
    return !check? 0: count;
}

void *s21_trim(const char *src, const char *trim_chars) {
    char *trim_str = S21_NULL;
    char *temp_trim_chars = (char *)trim_chars;
    char *temp_src = (char *)src;
    if (!src) {
    } else {
        char trim_empty[7] = " \t\n\v\f\r\0";
        if (!temp_trim_chars || s21_strlen(temp_trim_chars) == 0) {
            temp_trim_chars = trim_empty;
        }
        s21_size_t len = s21_strlen(temp_src);
        s21_size_t count_start = s21_strspn(temp_src, temp_trim_chars);
        if (len == 0 || len == count_start) {
            trim_str = (char *)malloc(sizeof(char));
            trim_str[0] = '\0';
        } else {
            s21_size_t count_end = s21_right_strspn(temp_src, temp_trim_chars);
            s21_size_t newstr = len - count_start - count_end;
            trim_str = (char *)malloc((newstr + 1) * sizeof(char));
            for (s21_size_t i = 0; i < newstr; i++)
                trim_str[i] = src[i+count_start];
            trim_str[newstr] = '\0';
        }
    }
    return (void *)trim_str;
}

// 24
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
    char *newstr = S21_NULL;
    if (!src) {
    } else {
        int index = start_index;
        s21_size_t len_src = s21_strlen(src);
        if (!str || index < 0 || start_index > len_src) {
        } else {
            s21_size_t len_str = s21_strlen(str);
            s21_size_t n = len_str + len_src;
            newstr = (char *)calloc((n + 1), sizeof(char));
            for (s21_size_t i = 0; i < start_index; i++)
                newstr[i] = src[i];
            s21_size_t k = 0;
            for (s21_size_t i = start_index; i < start_index + len_str && k != len_str; i++, k++)
                newstr[i] = str[k];
            k = start_index;
            for (s21_size_t i = len_str + start_index; i < n; i++, k++)
                newstr[i] = src[k];
            newstr[n] = '\0';
        }
    }
    return (void *)newstr;
}
