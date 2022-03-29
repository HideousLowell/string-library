#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include "s21_string.h"
#include <limits.h>
#include <float.h>


void convert(unsigned int num, int x, struct format* S, char *str) {
    const char arr[]= "0123456789abcdef";
    const char arr1[]= "0123456789ABCDEF";
    int i = 0;
    char buf[SIZE] = {};
    if (S->spec == 'x' || S->spec == 'o') {
        while (num != 0 && x != 0) {
            buf[i++] = arr[num % x];
            num /= x;
        }
    }
    if (S->spec == 'X') {
        while (num != 0 && x != 0) {
            buf[i++] = arr1[num % x];
            num /= x;
        }
    }
    buf[i] = '\0';
    s21_reverse(buf);
    s21_strcat(str, buf);
}

void convert_for_long(unsigned long int num, int x, struct format* S, char *str) {
    const char arr[]= "0123456789abcdef";
    const char arr1[]= "0123456789ABCDEF";
    int i = 0;
    char buf[SIZE] = {};
    if (S->spec == 'x' || S->spec == 'o') {
        while (num != 0 && x != 0) {
            buf[i++] = arr[num % x];
            num /= x;
        }
    }
    if (S->spec == 'X') {
        while (num != 0 && x != 0) {
            buf[i++] = arr1[num % x];
            num /= x;
        }
    }
    buf[i] = '\0';
    s21_reverse(buf);
    s21_strcat(str, buf);
}

void s21_utoa(s21_size_t n, char* str) {
    int i = 0;
    if (n == 0) {
        str[i] = n + '0';
        i++;
    } else {
        while (n > 0) {
            str[i] = n % 10 + '0';
            i++;
            n /= 10;
        }
    }
    str[i] = '\0';
    s21_reverse(str);
}

void s21_lutoa(s21_size_t_long n, char* str) {
    int i = 0;
    while (n > 0) {
        str[i] = n % 10 + '0';
        i++;
        n /= 10;
    }
    str[i] = '\0';
    s21_reverse(str);
}

void s21_ltoa(long int n, char* str, struct format* S) {
    int i = 0;
    if (n < 0) {
        n = n * -1;
    }
    while (n > 0) {
        str[i++] = n % 10 + '0';
        n /= 10;
    }
    if (S->negative == 1) {
        str[i++] = '-';
    }
    str[i] = '\0';
    s21_reverse(str);
}

void s21_flagHash(char *c, struct format* S, int i) {
    c[i++] = '0';
    if (S->spec == 'x')
        c[i++] = 'x';
    else if (S->spec == 'X')
        c[i++] = 'X';
}

void s21_flagMinus(char *c, struct format* S) {
    char temp[SIZE] = {};
    int i = 0;
    if (S->accur > -1) {
        if (S->flag_plus && c[0] != '-' && !S->minus)
            temp[i++] = '+';
        S->flag_plus = 0;
    }
    if (S->flag_hash && !S->flag_zero && (S->spec == 'o' || S->spec == 'x' || S->spec == 'X')) {
        int x = i;
        s21_flagHash(temp, S, x);
    }
    if (S->minus) {
        temp[i++] = '-';
        s21_strcat(temp, c);
    } else if (S->flag_plus) {
        S->flag_space = 0;
        temp[i++] = '+';
        s21_strcat(temp, c);
    } else if (S->flag_space) {
        temp[i++] = ' ';
        s21_strcat(temp, c);
    } else {
        s21_strcat(temp, c);
    }
    int len = s21_strlen(temp);
    if (S->wight < len)
        S->wight = len;
    while (len < S->wight)
        temp[len++] = ' ';
    temp[len] = '\0';
    s21_strcpy(c, temp);
}

void s21_flagPlusSpase(char *c, struct format* S) {
        char buf[SIZE] = {};
        int i = 0;
        if (S->flag_hash && (S->spec == 'o' || S->spec == 'x' || S->spec == 'X'))
            s21_flagHash(buf, S, i);
        i = 0;
        if (S->flag_plus) {
            S->flag_space = 0;
            buf[i++] = '+';
        }
        if (S->flag_space)
            buf[i++] = ' ';
        s21_strcat(buf, c);
        i = 0;
        while (buf[i])
            *c++ = buf[i++];
        *c = '\0';
}

void s21_accur_s(char *c, struct format* S) {
    char buf[SIZE] = {};
    int len = s21_strlen(c);
    int i = 0;
    if (S->accur < len) {
        len = S->accur;
    }
    while (len > 0) {
        buf[i++] = *c++;
        len--;
    }
    s21_strcpy(c, buf);
    *c = '\0';
}

void s21_accur_d(char *str, struct format* S) {
    S->accur_spec_d = 1;
    S->flag_zero = 0;
    char temp_in[SIZE] = {};
    char *c = temp_in;
    s21_strcpy(c, str);
    int len = s21_strlen(temp_in);
    int min = 0;
    char temp[SIZE] = {};
    char *b = temp;
    if (c[0] == '-') {
        min = 1;
        c[0] = '0';
    }
    if (S->accur > len) {
        int i = 0;
        if (S->flag_hash && S->spec == 'o')
            len++;
        if (min && S->accur >= len + 1) {
            b[i++] = '-';
        }
        while (len != S->accur) {
            b[i++] = '0';
            len++;
        }
        b[i] = '\0';
        s21_strcat(b, c);
        s21_strcpy(str, b);
    }
}

void s21_wight(char *c, struct format* S) {
    char buf[SIZE] = {};
    int len = s21_strlen(c);
    int i = 0;
    int W = S->wight;
    if ((S->minus || S->flag_plus) && S->wight <= len) {
        if (S->minus)
            buf[i++] = '-';
        else if (S->flag_plus)
            buf[i++] = '+';
    }
    if (S->flag_space && !S->minus && !S->flag_plus) {
        buf[i++] = ' ';
        W--;
    }
    if (S->minus && S->flag_zero) {
        buf[i++] = '-';
        W--;
    }
    if (S->flag_plus && !S->minus && S->flag_zero) {
        buf[i++] = '+';
        W--;
    }
    while (W-- > len) {
        if (S->flag_zero && S->spec != 'c' && S->spec != 's' && S->spec != 'n'&& S->spec != 'p')
            buf[i++] = '0';
        else
            buf[i++] = ' ';
    }
    if (S->minus && !S->flag_zero)
        buf[i-1] = '-';
    if (S->flag_plus && !S->minus && !S->flag_zero) {
        if (S->accur > -1 && c[0] != '-')
            buf[i-1] = '+';
        else
            buf[i-1] = '+';
    }
    s21_strcat(buf, c);
    i = 0;
    while (buf[i])
        *c++ = buf[i++];
    *c = '\0';
}

void s21_wight_oxX(char *c, struct format* S) {
    char buf[SIZE] = {};
    int len = s21_strlen(c);
    int i = 0;
    int W = S->wight;
    if (S->flag_hash) {
        if (S->spec == 'o')
            W--;
        if (S->spec == 'x' || (S->spec == 'X'))
            W -= 2;
    }
    if (!S->flag_zero) {
        while (W-- > len)
            buf[i++] = ' ';
    }
    if (S->flag_hash) {
        s21_flagHash(buf, S, i);
        if (S->spec == 'o')
            i += 1;
        else if (S->spec == 'x' || S->spec == 'X')
            i += 2;
    }
    if (S->flag_zero) {
            while (W-- > len)
                buf[i++] = '0';
        }
    s21_strcat(buf, c);
    i = 0;
    while (buf[i])
        *c++ = buf[i++];
}

void s21_lenght(int x, char* str, struct format* S) {
    if (S->lenght == 'h')
        x = (short)x;
    s21_itoa((int)x, str);
}

void s21_format(struct format* S, char* str) {
    if (S->spec == 's') {
        if (S->accur > 0)
        s21_accur_s(str, S);
        if (S->accur == 0)
        *str = '\0';
    } else if (S->accur > 0) {
        s21_accur_d(str, S);
    }
    if (S->wight > 0 && !S->flag_minus && (S->spec == 'o' || S->spec == 'x' || S->spec == 'X'))
        s21_wight_oxX(str, S);
    else if (S->wight > 0 && !S->flag_minus)
        s21_wight(str, S);
    else if (S->flag_minus && S->wight > 0)
        s21_flagMinus(str, S);
    if (!S->wight && S->negative == 0 && (S->flag_plus || S->flag_space))
        s21_flagPlusSpase(str, S);
    if (!S->wight && S->flag_hash && (S->spec == 'o' || S->spec == 'x' || S->spec == 'X'))
        s21_flagPlusSpase(str, S);
}

void s21_formatF(struct format* S, char* str, int num) {
    if (S->wight > 0 && !S->flag_minus)
        s21_wight(str, S);
    else if (S->flag_minus && S->wight > 0)
        s21_flagMinus(str, S);
    if (!S->wight && num >= 0 && (S->flag_plus || S->flag_space))
        s21_flagPlusSpase(str, S);
}

char* d_sprintf(struct format* S, char* str, int num) {
    char arr[SIZE];
    char *c = arr;
    if (num < 0 && S->wight && S->accur == -1) {
        S->minus = 1;
        num *= -1;
    }
    if (S->lenght == 'h')
        s21_lenght(num, arr, S);
    else
        s21_itoa(num, arr);
    if (S->accur == 0 && num == 0)
        *c = '\0';
    s21_format(S, arr);
    while (*c)
        *str++ = *c++;
    *str = '\0';
    return str;
}

char* ld_sprintf(struct format* S, char* str, long int num) {
    char arr[SIZE];
    char *c = arr;
    if (num == LLONG_MIN) {
        c = "-9223372036854775808";
    } else {
    if (num < 0)
        S->negative = 1;
    s21_ltoa(num, arr, S);
    }
    s21_format(S, arr);
    while (*c)
        *str++ = *c++;
    *str = '\0';
    return str;
}


char* oxX_sprintf(struct format* S, char* str, int num) {
    char arr[SIZE] = {};
    char *c = arr;
    if (num == 0) {
        int i = 0;
        arr[i++] = num + '0';
        S->flag_hash = 0;
    } else if (S->spec == 'o') {
        convert(num, 8, S, c);
        if (num < 0 && S->lenght == 'h') {
            c += 5;
            *c = '1';
        }
    } else if (S->spec == 'x' || S->spec == 'X') {
         convert(num, 16, S, c);
        if (num < 0 && S->lenght == 'h')
            c += 4;
    }
    if (S->accur == 0 && num == 0)
        *c = '\0';
    s21_format(S, arr);
    while (*c)
        *str++ = *c++;
    *str = '\0';
    return str;
}

char* loxX_sprintf(struct format* S, char* str, long int num) {
    char arr[SIZE] = {};
    char *c = arr;
    if (S->spec == 'o' && num != 0) {
        convert_for_long(num, 8, S, c);
    } else if ((S->spec == 'x' || S->spec == 'X') && num != 0) {
        convert_for_long(num, 16, S, c);
    }
    s21_format(S, arr);
    while (*c)
        *str++ = *c++;
    *str = '\0';
    return str;
}

char* c_sprintf(struct format* S, char* str, int C) {
    char arr[SIZE] = {};
    char *c = arr;
    *c = (char)C;
    if (S->wight > 0 && !S->flag_minus)
        s21_wight(c, S);
    else if (S->flag_minus && S->wight > 0)
        s21_flagMinus(c, S);
    while (*c)
        *str++ = *c++;
    *str = '\0';
    return str;
}

char* s_sprintf(struct format* S, char* str, char* C) {
    char arr[SIZE] = {};
    int i = 0;
    while (*C)
        arr[i++] = *C++;
    char *c = arr;
    s21_format(S, c);
    while (*c)
        *str++ = *c++;
    *str = '\0';
    return str;
}

char* ls_sprintf(struct format* S, char* str, wchar_t* C) {
    char arr[SIZE] = {};
    char temp[SIZE] = {};
    char *c = temp;
    int i = 0;
    while (C[i] != '\0') {
        arr[i] = (char)C[i];
        i++;
    }
    int len = s21_strlen(arr);
    i = 0;
    while (len) {
        c[i] = arr[i];
        i++;
        len--;
    }
    s21_format(S, c);
    while (*c)
        *str++ = *c++;
    *str = '\0';
    return str;
    }

char* u_sprintf(struct format* S, char* str, s21_size_t num) {
    if (S->accur > S->wight) {
        S->wight = S->accur;
        S->flag_zero = 1;
    }
    char arr[SIZE];
    char *c = arr;
    s21_utoa(num, arr);
    s21_format(S, arr);
    while (*c)
        *str++ = *c++;
    *str = '\0';
    return str;
}

char* lu_sprintf(struct format* S, char* str, s21_size_t_long num) {
    if (S->accur > S->wight) {
        S->wight = S->accur;
        S->flag_zero = 1;
    }
    char arr[SIZE];
    char *c = arr;
    s21_lutoa(num, arr);
    s21_format(S, arr);
    while (*c)
        *str++ = *c++;
    *str = '\0';
    return str;
}

char *p_convert(long x, int hex) {
    long num = x;
    const char arr[]= "0123456789abcdef";
    static char buffer[SIZE];
    char *ptr = buffer;
    while (num != 0 && hex != 0) {
        *--ptr = arr[num % hex];
        num /= hex;
    }
    return(ptr);
}

void* p_sprintf(char* str, void* ptr) {
    static char string_pointer[SIZE] = "0x";
    char *p = string_pointer;
    long x = (long)ptr;
    char *buf = p_convert(x, 16);
    s21_strcat(string_pointer, buf);
    while (*p)
        *str++ = *p++;
    *str = '\0';
    return str;
}

void n_sprintf(const char* str, const char* start, int* path) {
    *path = str - start;
}

void init(struct format* S) {
    S->flag_plus = 0;
    S->flag_minus = 0;
    S->flag_space = 0;
    S->flag_hash = 0;
    S->flag_zero = 0;
    S->wight = 0;
    S->accur = -1;
    S->accur_spec_d = 0;
    S->minus = 0;
    S->lenght = '0';
    S->spec = '0';
    S->negative = 0;
}

void badflags(struct format *S) {
    if (S->spec == 'c') {
        S->flag_plus = S->flag_space = S->flag_hash = S->flag_zero = 0;
        S->accur = -1;
        if (S->lenght == 'h' || S->lenght == 'L')
            S->lenght = '0';
    } else if (S->spec == 'd' || S->spec == 'i') {
        S->flag_hash = 0;
        if (S->lenght == 'L')
            S->lenght = '0';
        if (S->flag_minus && S->flag_zero)
            S->flag_minus = S->flag_zero = 0;
        if (S->flag_space && S->flag_plus)
            S->flag_space = 0;
    } else if (S->spec == 's') {
        S->flag_plus = S->flag_space = S->flag_hash = S->flag_zero = 0;
        if (S->lenght == 'h' || S->lenght == 'L')
            S->lenght = '0';
    } else if (S->spec == 'o' || S->spec == 'x' || S->spec == 'X') {
        S->flag_plus = S->flag_space = 0;
        if (S->flag_minus && S->flag_zero)
            S->flag_minus = S->flag_zero = 0;
        if (S->lenght == 'L')
            S->lenght = '0';
    } else if (S->spec == 'u') {
        S->flag_plus = S->flag_hash = S->flag_space = 0;
        if (S->lenght == 'L')
            S->lenght = '0';
    } else if (S->spec == 'p') {
        S->flag_plus = S->flag_hash = S->flag_space = S->flag_zero = 0;
    }
}

int s21_sprintf(char *str, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    struct format S;
    const char *start = str;
    init(&S);
    char* f = (char*)format;
    while (*f != '\0') {
        if (*f == '%') {
            f++;
            while (*f == '-' || *f == '+' || *f == ' ' || *f == '#' || *f == '0') {
                if (*f == '-')
                    S.flag_minus = 1;
                else if (*f == '+')
                    S.flag_plus = 1;
                else if (*f == ' ')
                    S.flag_space = 1;
                else if (*f == '#')
                    S.flag_hash = 1;
                else if (*f == '0')
                    S.flag_zero = 1;
                f++;
            }
            while ((*f >= '0' && *f <= '9') || *f == '*') {
                if (*f >= '0' && *f <= '9')
                    S.wight = S.wight * 10 + (*f - '0');
                else if (*f == '*')
                    S.wight = va_arg(ap, int);
                f++;
            }
            if (*f == '.') {
                S.accur = 0;
                f++;
                while ((*f >= '0' && *f <= '9') || *f == '*') {
                    if (*f >= '0' && *f <= '9')
                        S.accur = S.accur * 10 + (*f - '0');
                    else if (*f == '*')
                        S.accur = va_arg(ap, int);
                    f++;
                }
            }
            if (*f == 'h' || *f == 'l' || *f == 'L' )
                S.lenght = *f++;
            if (*f == 'c' || *f == 'd' || *f == 'i' || *f == 'e' || *f == 'E' || *f == 'f' ||
            *f == 'g' || *f == 'G' || *f == 'o' || *f == 's' || *f == 'u' || *f == 'x' ||
            *f == 'X' || *f == 'p' || *f == 'n')
                S.spec = *f++;
            else if (*f == '%')
                *str++ = *f++;
            if (S.spec == 'c') {
                badflags(&S);
                if (S.lenght == 'l')
                    str = c_sprintf(&S, str, (int)va_arg(ap, wchar_t));
                else
                    str = c_sprintf(&S, str, va_arg(ap, int));
            } else if (S.spec == 'd' || S.spec == 'i') {
                badflags(&S);
                if (S.lenght == 'l')
                    str = ld_sprintf(&S, str, va_arg(ap, long int));
                else
                    str = d_sprintf(&S, str, va_arg(ap, int));
            } else if (S.spec == 's') {
                badflags(&S);
                if (S.lenght == 'l') {
                    wchar_t* y = va_arg(ap, wchar_t*);
                    str = ls_sprintf(&S, str, y);
                } else {
                    char* x = va_arg(ap, char*);
                    str = s_sprintf(&S, str, x);
                }
            } else if (S.spec == 'n') {
                n_sprintf(str, start, va_arg(ap, int*));
            } else if (S.spec == 'o' || S.spec == 'x' || S.spec == 'X') {
                badflags(&S);
                if (S.lenght == 'l')
                    str = loxX_sprintf(&S, str, va_arg(ap, long int));
                else
                    str = oxX_sprintf(&S, str, va_arg(ap, int));
            } else if (S.spec == 'u') {
                badflags(&S);
                if (S.lenght == 'l')
                    str = lu_sprintf(&S, str, va_arg(ap, s21_size_t_long));
                else
                    str = u_sprintf(&S, str, va_arg(ap, s21_size_t));
            } else if (S.spec == 'f') {
                    str = f_sprintf(&S, str, va_arg(ap, double));
            } else if (S.spec == 'p') {
                badflags(&S);
                str = p_sprintf(str, va_arg(ap, void*));
            }
            init(&S);
        } else {
            *str++ = *f++;
        }
    }
    int result = str - start;
    va_end(ap);
    return result;
}

char* f_sprintf(struct format* S, char* str, long double num) {
    if (S->accur == -1)
        S->accur = 6;
    if (num < 0 && S->wight) {
        S->minus = 1;
        num *= -1;
    }
    char arr[SIZE] = {};
    char *c = arr;
    int celoe = 0;
    celoe = !S->accur? (int)round(num): (int)num;
    s21_itoa(celoe, c);
    if (S->flag_hash || S->accur)
        s21_strcat(c, ".");
    if (S->accur) {
        long double ostatok = num - (int)num;
        int acc = S->accur;
        while (acc--)
            ostatok *= 10;
        char fl[SIZE] = {};
        char *f = fl;
        s21_itoa(abs((int)round(ostatok)), f);
        int len = s21_strlen(f);
        while (len++ < S->accur)
            strcat(c, "0");
        strcat(c, f);
    }
    s21_formatF(S, c, num);
    while (*c)
        *str++ = *c++;
    *str = '\0';
    s21_strcat(str, c);

    return str;
}
