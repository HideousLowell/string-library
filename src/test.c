#include <check.h>
#include "s21_string.h"
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <float.h>

char test0[] = "Hello world\0";
char test1[] = "Hello world\0";
char test2[] = "Hello world\n\0";
char test3[] = "a\n\0";
char test4[] = " \n\0";
char test5[] = " \0";
char test6[] = "\n\0";
char test7[] = "\0";
char test8[] = "Hello\0";
char test9[] = "aloha\0";
char test10[50] = "aloha\0";
int test11 = 49;  // 1 по таблице ASCII
int test12 = 0;  // \0 по таблице ASCII
int test13 = 32;  // пробел по таблице ASCII
char x = 'l';
char x1 = 't';
s21_size_t s = 5;
int err0 = -1;
char *test14 = S21_NULL;
char *test15 = "";
char test16[] = "HELLO, VERTER!\0";
char test17[] = "***ver***ter***\0";

// 1
START_TEST(test_s21_memchr) {
    ck_assert_msg(s21_memchr(test1, x, 12) == memchr(test1, x, 12), "memchr 1");
    ck_assert_msg(s21_memchr(test1, x1, 12) == memchr(test1, x1, 12), "memchr 2");
    ck_assert_msg(s21_memchr(test1, '\0', 12) == memchr(test1, '\0', 12), "memchr 3");
    ck_assert_msg(s21_memchr(test4, ' ', 3) == memchr(test4, ' ', 3), "memchr 4");
    ck_assert_msg(s21_memchr(test6, '\n', 2) == memchr(test6, '\n', 2), "memchr 5");
}
END_TEST
// 2
START_TEST(test_s21_memcmp) {
    ck_assert_msg(s21_memcmp(test1, test8, 4) == memcmp(test1, test8, 4), "memcmp 2");
    ck_assert_msg(s21_memcmp(test8, test7, 2) == memcmp(test8, test7, 2), "memcmp 3");
    ck_assert_msg(s21_memcmp(test8, test7, 3) != memcmp(test1, test8, 2), "memcmp 4");
    ck_assert_msg(s21_memcmp(test3, test4, 3) == memcmp(test3, test4, 3), "memcmp 5");
    ck_assert_msg(s21_memcmp(test8, test3, 4) == memcmp(test8, test3, 4), "memcmp 6");
}
END_TEST
// 3
START_TEST(s21_memcpyPassTest) {
    char cpy1[] = "Hello world\0";
    char cpy2[] = "Hello world\n\0";
    char cpy3[] = "a\n\0";
    char cpy4[] = " \n\0";
    char cpy6[] = "\n\0";
    char cpy7[] = "\0";
    ck_assert_msg(s21_memcpy(cpy1, cpy2, strlen(cpy2)) == memcpy(cpy1, cpy2, strlen(cpy2)), "memcpy 1");
    ck_assert_msg(s21_memcpy(cpy2, cpy3, strlen(cpy3)) == memcpy(cpy2, cpy3, strlen(cpy3)), "memcpy 2");
    ck_assert_msg(s21_memcpy(cpy3, cpy4, 0) == memcpy(cpy3, cpy4, 0), "memcpy 3");
    ck_assert_msg(s21_memcpy(cpy6, cpy7, strlen(cpy6)) == memcpy(cpy6, cpy7, strlen(cpy6)), "memcpy 4");
}
END_TEST
// 4
START_TEST(test_s21_memmove) {
    char move1[] = "Hello world\0";
    char move2[] = "Hello world\n\0";
    char move9[] = "aloha\0";
    char move5[] = " \0";
    char move7[] = "\0";
    char move10[50] = "aloha\0";
    ck_assert_msg(s21_memmove(&move1[3], &move9[2], 3) == memmove(&move1[3], &move9[2], 3), "memmove 1");
    ck_assert_msg(s21_memmove(&move1[0], &move1[6], 5) == memmove(&move1[0], &move1[6], 5), "memmove 2");
    ck_assert_msg(s21_memmove(&move1[5], &move5[1], 1) == memmove(&move1[5], &move5[1], 1), "memmove 3");
    ck_assert_msg(s21_memmove(&move7[0], &move7[1], 1) == memmove(&move7[0], &move7[0], 1), "memmove 4");
    ck_assert_msg(s21_memmove(&move10[6], &move2[0], 5) == memmove(&move10[6], &move2[0], 5), "memmove 5");
}
END_TEST
// 5
START_TEST(test_s21_memset) {
    char set1[] = "Hello world\0";
    char set2[] = "Hello world\n\0";
    char set9[] = "aloha\0";
    char set10[50] = "aloha\0";
    int set11 = 49;
    int set12 = 0;
    int set13 = 32;
    ck_assert_msg(s21_memset(set1, set11, 5) == memset(set1, set11, 5), "memset 1");
    ck_assert_msg(s21_memset(set2, set12, 10) == memset(set2, set12, 10), "memset 2");
    ck_assert_msg(s21_memset(set9, set11, 6) == memset(set9, set11, 6), "memset 3");
    ck_assert_msg(s21_memset(set10, set13, 20) == memset(set10, set13, 20), "memset 4");
}
END_TEST
// 6
START_TEST(test_s21_strcat) {
    char cat1[] = "Hello world\0";
    char cat4[] = " \n\0";
    char cat7[] = "\0";
    char cat9[] = "aloha\0";
    char cat10[50] = "aloha\0";
    ck_assert_msg(s21_strcat(cat10, cat1) == strcat(cat10, cat1), "strcat 1");
    ck_assert_msg(s21_strcat(cat10, cat9) == strcat(cat10, cat9), "strcat 2");
    ck_assert_msg(s21_strcat(cat4, cat7) == strcat(cat4, cat7), "strcat 3");
    ck_assert_msg(s21_strcat(cat9, cat7) == strcat(cat9, cat7), "strcat 4");
}
END_TEST
// 7
START_TEST(test_s21_strncat) {
    char ncat1[] = "Hello world\0";
    char ncat4[] = " \n\0";
    char ncat7[] = "\0";
    char ncat9[] = "aloha\0";
    char ncat10[50] = "aloha\0";
    ck_assert_msg(s21_strncat(ncat10, ncat1, 5) == strncat(ncat10, ncat1, 5), "strncat 1");
    ck_assert_msg(s21_strncat(ncat10, ncat9, 6) == strncat(ncat10, ncat9, 6), "strncat 2");
    ck_assert_msg(s21_strncat(ncat4, ncat7, 1) == strncat(ncat4, ncat7, 1), "strncat 3");
    ck_assert_msg(s21_strncat(ncat9, ncat7, 0) == strncat(ncat9, ncat7, 0), "strncat 4");
}
END_TEST
// 8
START_TEST(test_s21_strchr) {
    ck_assert_msg(s21_strchr(test1, x) == strchr(test1, x), "strchr 1");
    ck_assert_msg(s21_strchr(test2, x) == strchr(test2, x), "strchr 2");
    ck_assert_msg(s21_strchr(test1, x1) == strchr(test1, x1), "strchr 3");
    ck_assert_msg(s21_strchr(test4, x) == strchr(test4, x), "strchr 4");
    ck_assert_msg(s21_strchr(test5, x) == strchr(test5, x), "strchr 5");
    ck_assert_msg(s21_strchr(test6, x) == strchr(test6, x), "strchr 6");
    ck_assert_msg(s21_strchr(test7, x) == strchr(test7, x), "strchr 7");
}
END_TEST
// 9
START_TEST(test_s21_strcmp) {
    ck_assert_int_eq(s21_strcmp(test1, test0), strcmp(test1, test0));
    ck_assert_int_le(s21_strcmp(test1, test2), strcmp(test1, test2));
    ck_assert_int_le(s21_strcmp(test1, test3), strcmp(test1, test3));
    ck_assert_int_ge(s21_strcmp(test1, test4), strcmp(test1, test4));
    ck_assert_int_ge(s21_strcmp(test1, test5), strcmp(test1, test5));
    ck_assert_int_ge(s21_strcmp(test1, test6), strcmp(test1, test6));
    ck_assert_int_ge(s21_strcmp(test1, test7), strcmp(test1, test7));
    ck_assert_int_le(s21_strcmp(test7, test1), strcmp(test7, test1));
}
END_TEST
// 10
START_TEST(test_s21_strncmp) {
    ck_assert_int_eq(s21_strncmp(test1, test2, s), strncmp(test1, test2, s));
    ck_assert_int_le(s21_strncmp(test1, test3, s), strncmp(test1, test3, s));
    ck_assert_int_ge(s21_strncmp(test1, test4, s), strncmp(test1, test4, s));
    ck_assert_int_ge(s21_strncmp(test1, test5, s), strncmp(test1, test5, s));
    ck_assert_int_ge(s21_strncmp(test1, test6, s), strncmp(test1, test6, s));
    ck_assert_int_ge(s21_strncmp(test1, test7, s), strncmp(test1, test7, s));
    ck_assert_int_le(s21_strncmp(test7, test1, s), strncmp(test7, test1, s));
}
END_TEST
// 11
START_TEST(s21_strcpyPassTest) {
    char cpy1[] = "Hello world\0";
    char cpy2[] = "Hello world\n\0";
    char cpy3[] = "a\n\0";
    char cpy4[] = " \n\0";
    char cpy6[] = "\n\0";
    char cpy7[] = "\0";
    ck_assert_msg(s21_strcpy(cpy1, cpy2) == strcpy(cpy1, cpy2), "strcpy 1");
    ck_assert_msg(s21_strcpy(cpy2, cpy3) == strcpy(cpy2, cpy3), "strcpy 2");
    ck_assert_msg(s21_strcpy(cpy3, cpy4) == strcpy(cpy3, cpy4), "strcpy 3");
    ck_assert_msg(s21_strcpy(cpy6, cpy7) == strcpy(cpy6, cpy7), "strcpy 4");
}
END_TEST
// 12
START_TEST(s21_strncpyPassTest) {
    char cpy1[] = "Hello world\0";
    char cpy2[] = "Hello world\n\0";
    char cpy3[] = "a\n\0";
    char cpy4[] = " \n\0";
    char cpy6[] = "\n\0";
    char cpy7[] = "\0";
    ck_assert_msg(s21_strncpy(cpy1, cpy2, strlen(cpy2)) == strncpy(cpy1, cpy2, strlen(cpy2)), "ncpy 1");
    ck_assert_msg(s21_strncpy(cpy2, cpy3, strlen(cpy3)) == strncpy(cpy2, cpy3, strlen(cpy3)), "ncpy 2");
    ck_assert_msg(s21_strncpy(cpy3, cpy4, strlen(cpy3)) == strncpy(cpy3, cpy4, strlen(cpy3)), "ncpy 3");
    ck_assert_msg(s21_strncpy(cpy6, cpy7, strlen(cpy6)) == strncpy(cpy6, cpy7, strlen(cpy6)), "ncpy 4");
}
END_TEST
// 13
START_TEST(s21_strcspnPassTest) {
    ck_assert_msg(s21_strcspn(test1, test2) == strcspn(test1, test2), "cspn 1");
    ck_assert_msg(s21_strcspn(test2, test3) == strcspn(test2, test3), "cspn 2");
    ck_assert_msg(s21_strcspn(test3, test4) == strcspn(test3, test4), "cspn 3");
    ck_assert_msg(s21_strcspn(test6, test7) == strcspn(test6, test7), "cspn 4");
}
END_TEST
// 14
START_TEST(s21_strerrorPassTest) {
    for (int j = 0; j < 3; j++) {
    char* errtest1 = s21_strerror(err0);
    char* errtest2 = strerror(err0);
    s21_size_t i = 0, len1 = s21_strlen(errtest1), len2 = s21_strlen(errtest2);
        while (i < len1 || i < len2) {
            ck_assert_msg(*(errtest1 + i) == *(errtest2 + i), "strerror 1");
            i++;
        }
        err0 += 1;
    }
}
END_TEST
// 15
START_TEST(test_s21_strlen) {
    ck_assert_msg(s21_strlen(test1) == strlen(test1), "strlen 1");
    ck_assert_msg(s21_strlen(test2) == strlen(test2), "strlen 2");
    ck_assert_msg(s21_strlen(test3) == strlen(test3), "strlen 3");
    ck_assert_msg(s21_strlen(test4) == strlen(test4), "strlen 4");
    ck_assert_msg(s21_strlen(test5) == strlen(test5), "strlen 5");
    ck_assert_msg(s21_strlen(test6) == strlen(test6), "strlen 6");
    ck_assert_msg(s21_strlen(test7) == strlen(test7), "strlen 7");
    ck_assert_uint_eq(s21_strlen(test1), strlen(test1));  // проверка с помощью другого флага
}
END_TEST
// 16
START_TEST(s21_strpbrkPassTest) {
    ck_assert_msg(s21_strpbrk(test1, test2) == strpbrk(test1, test2), "pbrk 1");
    ck_assert_msg(s21_strpbrk(test2, test3) == strpbrk(test2, test3), "pbrk 2");
    ck_assert_msg(s21_strpbrk(test1, test3) == strpbrk(test1, test3), "pbrk 3");
    ck_assert_msg(s21_strpbrk(test6, test7) == strpbrk(test6, test7), "pbrk 4");
}
END_TEST
// 17
START_TEST(test_s21_strrchr) {
    ck_assert_str_eq(s21_strrchr("Hello world\0", 'w') , strrchr("Hello world\0", 'w'));
    ck_assert_str_eq(s21_strrchr("a\n\0", '\n') , strrchr("a\n\0", '\n'));
    ck_assert_str_eq(s21_strrchr("Hello world\n\0", '\0') , strrchr("Hello world\n\0", '\0'));
    ck_assert_msg(s21_strrchr("", 'e') == strrchr("", 'e'), "strchr 2");
    ck_assert_str_eq(s21_strrchr(" \0", ' ') , strrchr(" \0", ' '));
}
END_TEST
// 18
START_TEST(s21_strspnPassTest) {
    ck_assert_msg(s21_strspn(test1, test2) == strspn(test1, test2), "strspn 1");
    ck_assert_msg(s21_strspn(test1, test3) == strspn(test1, test3), "strspn 2");
    ck_assert_msg(s21_strspn(test4, test7) == strspn(test4, test7), "strspn 3");
    ck_assert_msg(s21_strspn(test6, test3) == strspn(test6, test3), "strspn 4");
}
END_TEST
// 19
START_TEST(test_s21_strstr) {
    ck_assert_msg(s21_strstr(test1, test2) == strstr(test1, test2), "strstr 1");
    ck_assert_msg(s21_strstr(test1, test3) == strstr(test1, test3), "strstr 2");
    ck_assert_msg(s21_strstr(test2, test4) == strstr(test2, test4), "strstr 3");
}
END_TEST
// 20
START_TEST(s21_strtokPassTest) {
    char arr1[100] = "London is the.capital of GB";
    char *parr1 = arr1;
    char arr2[100] = "London is the.capital of GB";
    char *parr2 = arr2;
    s21_strtok(parr1, " .");
    strtok(parr2, " .");
    ck_assert_str_eq(parr1, parr2);
    parr1 = s21_strtok(NULL, " .");
    parr2 = strtok(NULL, " .");
    ck_assert_str_eq(parr1, parr2);
    parr1 = s21_strtok(NULL, " .");
    parr2 = strtok(NULL, " .");
    ck_assert_str_eq(parr1, parr2);
}
END_TEST
// 21
START_TEST(s21_sprintfPassTest) {
    char c[255] = {};
    char d[255] = {};
    int n = 2100;
    int n1 = 0;
    int n2 = -21;
    short sh = 123;
    short sh1 = -123;
    float f = 21.21;
    float f1 = -21.21;
    long int lg = 12345678912345;
    long int lg1 = -12345678912345;

    // p %
    // 1
    s21_sprintf(c, "%% %p", &n);
    sprintf(d, "%% %p", &n);
    ck_assert_str_eq(c, d);

    // %d
    // 2
    s21_sprintf(c, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg, lg1, lg1);
    sprintf(d, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg, lg1, lg1);
    ck_assert_str_eq(c, d);
    // 3
    s21_sprintf(c, "%10d %+3d %+010d %+-10d %+-10d % -10d %-10d %-10d", n, 212121, 2121, n2, n, 21, 55, -55);
    sprintf(d, "%10d %+3d %+010d %+-10d %+-10d % -10d %-10d %-10d", n, 212121, 2121, n2, n, 21, 55, -55);
    ck_assert_str_eq(c, d);
    // 4
    s21_sprintf(c, "%-10d %010d %010d %*d %2d", 21, n2, n, 10, n, n2);
    sprintf(d, "%-10d %010d %010d %*d %2d", 21, n2, n, 10, n, n2);
    ck_assert_str_eq(c, d);
    // 5
    s21_sprintf(c, "%.*d %3.10d %.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d",
    10, n, n2, 42, 21, 10, n, n2, -21, x1, 21, -42);
    sprintf(d, "%.*d %3.10d %.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d",
    10, n, n2, 42, 21, 10, n, n2, -21, x1, 21, -42);
    ck_assert_str_eq(c, d);
    // 6
    s21_sprintf(c, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX,
    SHRT_MAX, SHRT_MIN, USHRT_MAX, LONG_MAX, LONG_MIN);
    sprintf(d, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX,
    SHRT_MAX, SHRT_MIN, USHRT_MAX, LONG_MAX, LONG_MIN);
    ck_assert_str_eq(c, d);

    // %c
    // 7
    s21_sprintf(c, "%c %10c %-10c", '!', 'a', 'b');
    sprintf(d, "%c %10c %-10c", '!', 'a', 'b');
    ck_assert_str_eq(c, d);
    // 8
    s21_sprintf(c, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
    sprintf(d, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
    ck_assert_str_eq(c, d);

    // %s
    // 9
    s21_sprintf(c, "%s %10s %-10s %-3s %.s %.3s %.10s",
    "hello", "hello", "hello", "hello", "hello", "hello", "hello");
    sprintf(d, "%s %10s %-10s %-3s %.s %.3s %.10s",
    "hello", "hello", "hello", "hello", "hello", "hello", "hello");
    ck_assert_str_eq(c, d);
    // 10
    s21_sprintf(c, "%ls %10ls %-10ls %-3ls %.ls %.3ls %.10ls",
    L"hello", L"hello", L"hello", L"hello", L"hello", L"hello", L"hello");
    sprintf(d, "%ls %10ls %-10ls %-3ls %.ls %.3ls %.10ls",
    L"hello", L"hello", L"hello", L"hello", L"hello", L"hello", L"hello");
    ck_assert_str_eq(c, d);

    // %u
    // 11
    s21_sprintf(c, "%u %lu", UINT_MAX, ULONG_MAX);
    sprintf(d, "%u %lu", UINT_MAX, ULONG_MAX);
    ck_assert_str_eq(c, d);

    // n
    // 12
    s21_sprintf(c, "hello %n", &n);
    sprintf(d, "hello %n", &n1);
    ck_assert_msg(c, d, "error");

    // o
    // 13
    s21_sprintf(c, "%-10o %lo %lo %o %o %o %10o %#10o %0#10o", 21, lg, lg1, n, 0, n2, 0, 21, 42);
    sprintf(d, "%-10o %lo %lo %o %o %o %10o %#10o %0#10o", 21, lg, lg1, n, 0, n2, 0, 21, 42);
    ck_assert_str_eq(c, d);
    // 14
    s21_sprintf(c, "%#o %#o %#10o %0#10o %.10o %.0o %#5.10o", n, n2, 0, 0, n, 0, 123);
    sprintf(d, "%#o %#o %#10o %0#10o %.10o %.0o %#5.10o", n, n2, 0, 0, n, 0, 123);
    ck_assert_str_eq(c, d);

    // x
    // 15
    s21_sprintf(c, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21, n, 0, 123);
    sprintf(d, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21, n, 0, 123);
    ck_assert_str_eq(c, d);
    // 16
    s21_sprintf(c, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
    n, n2, 21, 0, 42, 21, 0, -65, lg, lg1);
    sprintf(d, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
    n, n2, 21, 0, 42, 21, 0, -65, lg, lg1);
    ck_assert_str_eq(c, d);

    // X
    // 17
    s21_sprintf(c, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
    sprintf(d, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
    ck_assert_str_eq(c, d);
    // 18
    s21_sprintf(c, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0, 4221, n1);
    sprintf(d, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0, 4221, n1);
    ck_assert_str_eq(c, d);

    // f
    // 19
    s21_sprintf(c, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f",
    f, f1, 21.21, -21.21, 42.42, -42.42, f, f1);
    sprintf(d, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f",
    f, f1, 21.21, -21.21, 42.42, -42.42, f, f1);
    ck_assert_str_eq(c, d);
    // 20
    s21_sprintf(c, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f",
    f, f1, 21., 21.21, 0.0, 21.21, 21., 0.0, 21.21);
    sprintf(d, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f",
    f, f1, 21., 21.21, 0.0, 21.21, 21., 0.0, 21.21);
    ck_assert_str_eq(c, d);
}
END_TEST
// 22
START_TEST(s21_sscanfPassTest) {
    int a1 = 1, b1 = 0;
    unsigned int a2 = 1, a3 = 1, b2 = 0, b3 = 0;
    char q1 = '0';
    char w1 = '1';
    char arr1[100] = "";
    char arr2[100] = "";
    ck_assert_msg(s21_sscanf(" -12345678asd", " %2d%2o%2x%1c%2s", &a1, &a2, &a3, &q1, arr1) ==
    sscanf(" -12345678asd", " %2d%2o%2x%1c%2s", &b1, &b2, &b3, &w1, arr2), "sscanf 1.0");
    ck_assert_msg(a1 == b1, "sscanf 1.1");
    ck_assert_msg(a2 == b2, "sscanf 1.2");
    ck_assert_msg(a3 == b3, "sscanf 1.3");
    ck_assert_msg(q1 == w1, "sscanf 1.4");
    ck_assert_str_eq(arr1, arr2);
    float f1 = 0, f2 = 1;
    long double ld1 = 0, ld2 = 1;
    wchar_t wc1, wc2;
    ck_assert_msg(s21_sscanf("z1.25e5 1.23e+10", "%lc%G%Le", &wc1, &f1, &ld1) ==
    sscanf("z1.25e5 1.23e+10", "%lc%G%Le", &wc2, &f2, &ld2), "sscanf 2.0");
    ck_assert_msg(f1 == f2, "sscanf 2.1");
    ck_assert_msg(ld1 == ld2, "sscanf 2.2");
    long e1 = 1, r1 = 1;
    unsigned long e2 = 0, r2 = 0;
    ck_assert_msg(s21_sscanf(" -123abcdeasd", "%2li%2lo", &e1, &e2) ==
    sscanf(" -123abcdeasd", "%2li%2lo", &r1, &r2), "sscanf 3.0");
    ck_assert_msg(e1 == r1, "sscanf 3.1");
    ck_assert_msg(e2 == r2, "sscanf 3.2");
    int i1 = 0, n1 = 0, i2 = 0, n2 = 0;
    void *adres1 = S21_NULL;
    void *adres2 = S21_NULL;
    ck_assert_msg(s21_sscanf("5 0x213def", "%1i%p%n", &i1, &adres1, &n1) ==
    sscanf("5 0x213def", "%1i%p%n", &i2, &adres2, &n2), "sscanf 4.0");
    ck_assert_msg(i1 == i2, "sscanf 4.1");
    ck_assert_msg(n1 == n2, "sscanf 4.2");
    ck_assert_ptr_eq(adres1, adres2);
    long double e3 = 0, e4 = 0, g3 = 0, g4 = 0;
        ck_assert_msg(s21_sscanf("1.23451e+15 34567837433.456", "%Le%Lg", &e3, &g3) ==
        sscanf("1.23451e+15 34567837433.456", "%Le%Lg", &e4, &g4), "sscanf 4.4");
        ck_assert_msg(e3 == e4, "sscanf 4.4");
        ck_assert_msg(g3 == g4, "sscanf 4.4");
}
END_TEST
// 23
START_TEST(test_s21_to_upper) {
    char *upper_test16 = s21_to_upper(test16);
    ck_assert_str_eq(upper_test16, "HELLO, VERTER!\0");
    free(upper_test16);

    char *upper_test15 = s21_to_upper(test15);
    ck_assert_str_eq(upper_test15, "\0");
    free(upper_test15);

    char *upper_test1 = s21_to_upper(test1);
    ck_assert_str_eq(upper_test1, "HELLO WORLD\0");
    free(upper_test1);

    char *upper_test14 = s21_to_upper(test14);
    ck_assert_ptr_eq(upper_test14, S21_NULL);
    free(upper_test14);
}
END_TEST
// 24
START_TEST(test_s21_to_lower) {
    char *lower_test16 = s21_to_lower(test16);
    ck_assert_str_eq(lower_test16, "hello, verter!\0");
    free(lower_test16);

    char *lower_test15 = s21_to_lower(test15);
    ck_assert_str_eq(lower_test15, "\0");
    free(lower_test15);

    char *lower_test1 = s21_to_lower(test1);
    ck_assert_str_eq(lower_test1, "hello world\0");
    free(lower_test1);

    char *lower_test14 = s21_to_lower(test14);
    ck_assert_ptr_eq(lower_test14, S21_NULL);
    free(lower_test14);
}
END_TEST
// 25
START_TEST(test_s21_insert) {
    int it1 = 6, it2 = 11, it3 = 10, it4 = 12, it5 = -1;
    char *insert_test1 = s21_insert(test16, test9, it1);
    ck_assert_str_eq(insert_test1, "HELLO,aloha VERTER!\0");
    free(insert_test1);

    char *insert_test2 = s21_insert(test1, test9, it2);
    ck_assert_str_eq(insert_test2, "Hello worldaloha\0");
    free(insert_test2);

    char *insert_test3 = s21_insert(test1, test9, it3);
    ck_assert_str_eq(insert_test3, "Hello worlalohad\0");
    free(insert_test3);

    char *insert_test4 = s21_insert(test1, test9, it4);
    ck_assert_ptr_eq(insert_test4, S21_NULL);
    free(insert_test4);

    char *insert_test5 = s21_insert(test1, test9, it5);
    ck_assert_ptr_eq(insert_test5, S21_NULL);
    free(insert_test5);

    char *insert_test6 = s21_insert(test14, test9, it2);
    ck_assert_ptr_eq(insert_test6, S21_NULL);
    free(insert_test6);

    char *insert_test7 = s21_insert(test1, test14, it2);
    ck_assert_ptr_eq(insert_test7, S21_NULL);
    free(insert_test7);
}
END_TEST
// 26
START_TEST(test_s21_trim) {
    char test18[] = "ver***ter \0";
    char test19[] = "***verter\0";
    char test20[] = "*******\0";
    char test21[] = " \t\n\v\f\rverter\t\n\v\f\r \0";
    char test22[] = "*\0";
    char test23[] = "* \0";
    char *trim_test1 = s21_trim(test17, test22);
    ck_assert_str_eq(trim_test1, "ver***ter\0");
    free(trim_test1);

    char *trim_test2 = s21_trim(test18, test23);
    ck_assert_str_eq(trim_test2, "ver***ter\0");
    free(trim_test2);

    char *trim_test3 = s21_trim(test19, test22);
    ck_assert_str_eq(trim_test3, "verter\0");
    free(trim_test3);

    char *trim_test4 = s21_trim(test20, test22);
    ck_assert_str_eq(trim_test4 , "");
    free(trim_test4);

    char *trim_test5 = s21_trim(test15, test22);
    ck_assert_str_eq(trim_test5, "");
    free(trim_test5);

    char *trim_test6 = s21_trim(test21, test15);
    ck_assert_str_eq(trim_test6, "verter\0");
    free(trim_test6);

    char *trim_test7 = s21_trim(test21, test14);
    ck_assert_str_eq(trim_test7, "verter\0");
    free(trim_test7);

    char *trim_test8 = s21_trim(test14, test22);
    ck_assert_ptr_eq(trim_test8, S21_NULL);
    free(trim_test8);
}
END_TEST

int main() {
    Suite *s1 = suite_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    // 1
    TCase *s21_memchrCase = tcase_create("memchrTest");
    suite_add_tcase(s1, s21_memchrCase);
    tcase_add_test(s21_memchrCase, test_s21_memchr);
    // 2
    TCase *s21_memcmpCase = tcase_create("memcmpTest");
    suite_add_tcase(s1, s21_memcmpCase);
    tcase_add_test(s21_memcmpCase, test_s21_memcmp);
    // 3
    TCase *s21_memcpyCase = tcase_create("s21_memcpyBaseTest");
    suite_add_tcase(s1, s21_memcpyCase);
    tcase_add_test(s21_memcpyCase, s21_memcpyPassTest);
    // 4
    TCase *s21_memmoveCase = tcase_create("memmoveTest");
    suite_add_tcase(s1, s21_memmoveCase);
    tcase_add_test(s21_memmoveCase, test_s21_memmove);
    // 5
    TCase *s21_memsetCase = tcase_create("memsetTest");
    suite_add_tcase(s1, s21_memsetCase);
    tcase_add_test(s21_memsetCase, test_s21_memset);
    // 6
    TCase *s21_strcatCase = tcase_create("strcatTest");
    suite_add_tcase(s1, s21_strcatCase);
    tcase_add_test(s21_strcatCase, test_s21_strcat);
    // 7
    TCase *s21_strncatCase = tcase_create("strncatTest");
    suite_add_tcase(s1, s21_strncatCase);
    tcase_add_test(s21_strncatCase, test_s21_strncat);
    // 8
    TCase *s21_strchrCase = tcase_create("sumBaseTest");
    suite_add_tcase(s1, s21_strchrCase);
    tcase_add_test(s21_strchrCase, test_s21_strchr);
    // 9
    TCase *s21_strcmpCase = tcase_create("sumBaseTest");
    suite_add_tcase(s1, s21_strcmpCase);
    tcase_add_test(s21_strcmpCase, test_s21_strcmp);
    // 10
    TCase *s21_strncmpCase = tcase_create("sumBaseTest");
    suite_add_tcase(s1, s21_strncmpCase);
    tcase_add_test(s21_strncmpCase, test_s21_strncmp);
    // 11
    TCase *s21_strcpyCase = tcase_create("s21_strcpyBaseTest");
    suite_add_tcase(s1, s21_strcpyCase);
    tcase_add_test(s21_strcpyCase, s21_strcpyPassTest);
    // 12
    TCase *s21_strncpyCase = tcase_create("s21_strncpyBaseTest");
    suite_add_tcase(s1, s21_strncpyCase);
    tcase_add_test(s21_strncpyCase, s21_strncpyPassTest);
    // 13
    TCase *s21_strcspnCase = tcase_create("s21_strcspnBaseTest");
    suite_add_tcase(s1, s21_strcspnCase);
    tcase_add_test(s21_strcspnCase, s21_strcspnPassTest);
    // 14
    TCase *s21_strerrorCase = tcase_create("s21_strerrorBaseTest");
    suite_add_tcase(s1, s21_strerrorCase);
    tcase_add_test(s21_strerrorCase, s21_strerrorPassTest);
    // 15
    TCase *s21_strlenCase = tcase_create("strlenTest");
    suite_add_tcase(s1, s21_strlenCase);
    tcase_add_test(s21_strlenCase, test_s21_strlen);
    // 16
    TCase *s21_strpbrkCase = tcase_create("s21_strpbrkBaseTest");
    suite_add_tcase(s1, s21_strpbrkCase);
    tcase_add_test(s21_strpbrkCase, s21_strpbrkPassTest);
    // 17
    TCase *s21_strrchrCase = tcase_create("sumBaseTest");
    suite_add_tcase(s1, s21_strrchrCase);
    tcase_add_test(s21_strrchrCase, test_s21_strrchr);
    // 18
    TCase *s21_strspnCase = tcase_create("s21_strspnBaseTest");
    suite_add_tcase(s1, s21_strspnCase);
    tcase_add_test(s21_strspnCase, s21_strspnPassTest);
    // 19
    TCase *s21_strstrCase = tcase_create("sumBaseTest");
    suite_add_tcase(s1, s21_strstrCase);
    tcase_add_test(s21_strstrCase, test_s21_strstr);
    // 20
    TCase *s21_strtokCase = tcase_create("s21_strtokBaseTest");
    suite_add_tcase(s1, s21_strtokCase);
    tcase_add_test(s21_strtokCase, s21_strtokPassTest);
    // 21
    TCase *s21_sscanfCase = tcase_create("s21_sscanfBaseTest");
    suite_add_tcase(s1, s21_sscanfCase);
    tcase_add_test(s21_sscanfCase, s21_sscanfPassTest);
    // 22
    TCase *s21_sprintfCase = tcase_create("s21_sprintfBaseTest");
    suite_add_tcase(s1, s21_sprintfCase);
    tcase_add_test(s21_sprintfCase, s21_sprintfPassTest);
    // 23
    TCase *s21_to_upperCase = tcase_create("s21_to_upperBaseTest");
    suite_add_tcase(s1, s21_to_upperCase);
    tcase_add_test(s21_to_upperCase, test_s21_to_upper);
    // 24
    TCase *s21_to_lowerCase = tcase_create("s21_to_lowerBaseTest");
    suite_add_tcase(s1, s21_to_lowerCase);
    tcase_add_test(s21_to_lowerCase, test_s21_to_lower);
    // 25
    TCase *s21_insertCase = tcase_create("s21_insertBaseTest");
    suite_add_tcase(s1, s21_insertCase);
    tcase_add_test(s21_insertCase, test_s21_insert);
    // 26
    TCase *s21_trimCase = tcase_create("s21_trimBaseTest");
    suite_add_tcase(s1, s21_trimCase);
    tcase_add_test(s21_trimCase, test_s21_trim);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf != 0;
}
