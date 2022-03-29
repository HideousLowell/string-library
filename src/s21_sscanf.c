#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include "s21_string.h"

void init_scanf(struct fsc* S) {
    S->wight = 0;
    S->lenght = '0';
    S->minus = 1;
    S->ast = 0;
    S->wight = 0;
}

void *temp_adress(void) {
    static int temp[1000] = {0};
    void *adress = temp;
    return adress;
}

int is_error(struct fsc *S) {
    if (!*S->str)
        S->error = 1;
    return S->error;
}

void spaces_sign(struct fsc *S) {
    while (!s_valid(S->str))
        S->str++;
    if (*S->str == '-') {
        S->minus = -1;
        S->str++;
        S->wight--;
    } else if (*S->str == '+') {
        S->str++;
        S->wight--;
    }
}

void c_sscanf(struct fsc *S, va_list ap) {
    char *path = temp_adress();;
    if (!S->ast)
        path = va_arg(ap, char*);
    if (*S->str) {
        *path = *S->str++;
        if (!S->ast)
            S->result++;
    }
}

void lc_sscanf(struct fsc *S, va_list ap) {
    wchar_t *path = temp_adress();;
    if (!S->ast)
        path = va_arg(ap, wchar_t*);
    if (*S->str) {
        *path = (wchar_t)*S->str++;
        S->result++;
    }
}

int s_valid(char *c) {
    int res = 1;
    switch (*c) {
        case '\n':
        case '\t':
        case '\v':
        case '\f':
        case '\r':
        case ' ':
            res = 0;
            break;
    }
    return res;
    }

void s_sscanf(struct fsc *S, va_list ap) {
    char* path = temp_adress();
    if (!S->ast)
        path = va_arg(ap, char*);
    while (!s_valid(S->str))
        S->str++;
    int res = 0;
    while (!is_error(S) && s_valid(S->str) && S->wight--) {
        *path++ = *S->str++;
        res = 1;
    }
    if (res && !S->ast)
        S->result += res;
    *path = '\0';
}

void ls_sscanf(struct fsc *S, va_list ap) {
    wchar_t* path = (wchar_t*)temp_adress();
    if (!S->ast)
        path = va_arg(ap, wchar_t*);
    while (!s_valid(S->str))
        S->str++;
    int res = 0;
    while (!is_error(S) && s_valid(S->str) && S->wight--) {
        *path++ = *S->str++;
        res = 1;
    }
    if (res && !S->ast)
        S->result += res;
    *path = '\0';
}

void d_isresult(int res, struct fsc *S, int *path) {
    if (res && !S->ast) {
        S->result++;
        *path *= S->minus;
    }
}

void ld_isresult(int res, struct fsc *S, long *path) {
    if (res && !S->ast) {
        S->result++;
        *path *= S->minus;
    }
}

int d_valid(char c) {
    int res = 0;
    if (c >= '0' && c <= '9')
        res = 1;
    return res;
}

int o_convert(int value) {
    if (value >= '0' && value <= '7')
        value -= '0';
    if (value >= '8' && value <= '9')
        value = 0;
    return value;
}

int x_convert(int value) {
    if (value >= '0' && value <= '9')
        value -= '0';
    else if (value == 'x')
        value = 0;
    else if (value == 'a' || value == 'A')
        value = 10;
    else if (value == 'b' || value == 'B')
        value = 11;
    else if (value == 'c' || value == 'C')
        value = 12;
    else if (value == 'd' || value == 'D')
        value = 13;
    else if (value == 'e' || value == 'E')
        value = 14;
    else if (value == 'f' || value == 'F')
        value = 15;
    return value;
}

int o_valid(int value) {
    int res = 0;
    if (value >= '0' && value <= '7')
        res = 1;
    return res;
}

void s21_strtoi(int *res, struct fsc *S, int n, int *path) {
    if (*res == 0) {
        *path = 0;
        *res = 1;
    }
    if (*S->str == 'x')
        if (!S->wight || !d_valid(*(S->str + 1)))
            S->error = 1;
    if (n == 10)
        *path = *path * n + (*S->str - '0');
    else if (n == 8)
        *path = *path * n + o_convert(*S->str);
    else if (n == 16)
        *path = *path * n + x_convert(*S->str);
    S->str++;
}

void s21_strtoli(int *res, struct fsc *S, int n, long *path) {
    if (*res == 0) {
        *path = 0;
        *res = 1;
    }
    if (*S->str == 'x')
        if (S->wight == 0 || !d_valid(*(S->str + 1)))
            S->error = 1;
    if (n == 10)
        *path = *path * n + (*S->str - '0');
    else if (n == 8)
        *path = *path * n + o_convert(*S->str);
    else if (n == 16)
        *path = *path * n + x_convert(*S->str);
    S->str++;
}

void d_sscanf(struct fsc *S, va_list ap) {
    int temp[1000];
    int *path = temp;
    if (!S->ast)
        path = va_arg(ap, int*);
    spaces_sign(S);
    int res = 0;
    while (d_valid(*S->str) && S->wight--)
        s21_strtoi(&res, S, 10, path);
    d_isresult(res, S, path);
    if (S->lenght == 'h')
        *path = (unsigned short)*path;
}

void ld_sscanf(struct fsc *S, va_list ap) {
    long *path  = temp_adress();;
    if (!S->ast)
        path = va_arg(ap, long*);
    spaces_sign(S);
    int res = 0;
    while (d_valid(*S->str) && S->wight--)
        s21_strtoli(&res, S, 10, path);
    ld_isresult(res, S, path);
}

void o_sscanf(struct fsc* S, va_list ap) {
    int *path  = temp_adress();;
    if (!S->ast)
        path = va_arg(ap, int*);
    spaces_sign(S);
    int res = 0;
    while (o_valid(*S->str) && S->wight--)
        s21_strtoi(&res, S, 8, path);
    d_isresult(res, S, path);
    if (S->lenght == 'h')
        *path = (unsigned short)*path;
}

void lo_sscanf(struct fsc* S, va_list ap) {
    long *path  = temp_adress();
    if (!S->ast)
        path = va_arg(ap, long*);
    spaces_sign(S);
    int res = 0;
    while (o_valid(*S->str) && S->wight--)
        s21_strtoli(&res, S, 8, path);
    ld_isresult(res, S, path);
}

int x_valid(int value) {
    int result = 0;
    if ((value >= '0' && value <= '9') ||
        (value == 'x' || value == 'X') ||
        (value >= 'a' && value <= 'f') ||
        (value >= 'A' && value <= 'F'))
        result = 1;
    return result;
}

void x_sscanf(struct fsc* S, va_list ap) {
    int *path  = temp_adress();
    if (!S->ast)
        path = va_arg(ap, int*);
    spaces_sign(S);
    int res = 0;
    while (x_valid(*S->str) && S->wight--) {
        if (*S->str == 'x' && !d_valid(*(S->str + 1)))
            S->error = 1;
        s21_strtoi(&res, S, 16, path);
    }
    d_isresult(res, S, path);
    if (S->lenght == 'h')
        *path = (unsigned short)*path;
}

void lx_sscanf(struct fsc* S, va_list ap) {
    long *path  = temp_adress();
    if (!S->ast)
        path = va_arg(ap, long*);
    spaces_sign(S);
    int res = 0;
    while (x_valid(*S->str) && S->wight--)
        s21_strtoli(&res, S, 16, path);
    ld_isresult(res, S, path);
}

void i_sscanf(struct fsc* S, va_list ap) {
    spaces_sign(S);
    if (*S->str == '0' && *(S->str + 1) == 'x')
        x_sscanf(S, ap);
    else if (*S->str == '0')
        o_sscanf(S, ap);
    else
        if (d_valid(*S->str))
            d_sscanf(S, ap);
}

void li_sscanf(struct fsc* S, va_list ap) {
    spaces_sign(S);
    if (*S->str == '0' && *(S->str + 1) == 'x')
        lx_sscanf(S, ap);
    else if (*S->str == '0')
        lo_sscanf(S, ap);
    else
        if (d_valid(*S->str))
            ld_sscanf(S, ap);
}

void n_sscanf(struct fsc* S, va_list ap) {
    int *path = temp_adress();
    if (!S->ast)
        path = va_arg(ap, int*);
    *path = S->str - S->start;
}

long double s21_strtold(struct fsc *S, int *res) {
    spaces_sign(S);
    long double path = 0;
    while (d_valid(*S->str) && S->wight--) {
        path = path * 10 + (*S->str - '0');
        S->str++;
        *res = 1;
    }
    if (*S->str >= '.' && S->wight) {
        S->str++;
        S->wight--;
        long double x = 10;
        while (d_valid(*S->str) && S->wight--) {
            path = path + (*S->str - '0')/x;
            x *= 10;
            S->str++;
        }
    }
    if ((*S->str == 'e' || *S->str == 'E') && S->wight) {
        S->str++;
        S->wight--;
        int minus = 0;
        long double exp = 10;
        if (*S->str == '+' && S->wight) {
            S->str++;
            S->wight--;
        } else if (*S->str == '-' && S->wight) {
            S->str++;
            S->wight--;
            minus = 1;
        }
        int num = 0;
        while (d_valid(*S->str) && S->wight--)
            num = num * 10 + *S->str++ - '0';
        exp = powl(10, num);
        path = minus? path / exp: path * exp;
    }
    if (*res && !S->ast)
        S->result++;
    path *= S->minus;
    return path;
}

void f_sscanf(struct fsc* S, va_list ap) {
    float *path = temp_adress();
    if (!S->ast)
        path = va_arg(ap, float*);
    int res = 0;
    float result = (float)s21_strtold(S, &res);
    if (res)
        *path = result;
}

void lf_sscanf(struct fsc* S, va_list ap) {
    double *path = temp_adress();
    if (!S->ast)
        path = va_arg(ap, double*);
    int res = 0;
    double result = (double)s21_strtold(S, &res);
    if (res)
        *path = result;
}

int f_valid(char c) {
    int res = 0;
    if (c >= '0' && c <= '9')
        res = 1;
    else if (c == '.' || c == '-' || c == 'e' || c == '+')
        res = 1;
    return res;
}
void llf_sscanf(struct fsc* S, va_list ap) {
    while (*S->str == ' ')
        S->str++;
    long double *path = temp_adress();
    if (!S->ast)
        path = va_arg(ap, long double*);
    char *a = temp_adress();
    int i = 0;
    while (S->wight-- && f_valid(*S->str))
        *(a + i++) = *S->str++;
    *(a + i) = '\0';
    long double result = strtold(a, &a);
    if (i && !S->ast) {
        *path = result;
        S->result++;
    }
}

void p_sscanf(struct fsc* S, va_list ap) {
    void **path  = (void*)temp_adress();
    spaces_sign(S);
    if (!S->ast)
        path = va_arg(ap, void**);
    long adres = 0;
    int res = 0;
    while (x_valid(*S->str) && S->wight--) {
        adres = adres * 16 + x_convert(*S->str);
        S->str++;
        res = 1;
    }
    if (res && !S->ast)
        S->result++;
    *path = (void*)adres;
}

void l_spec_scanf(struct fsc* S, va_list ap) {
    if (S->spec == 'c')
        lc_sscanf(S, ap);
    else if (S->spec == 'i')
        li_sscanf(S, ap);
    else if (S->spec == 'o')
            lo_sscanf(S, ap);
    else if (S->spec == 's')
        ls_sscanf(S, ap);
    else if (S->spec == 'x' || S->spec == 'X')
        lx_sscanf(S, ap);
    else if (S->spec == 'd' || S->spec == 'u')
        ld_sscanf(S, ap);
    else if (S->spec == 'f' || S->spec == 'G' || S->spec == 'g' ||
             S->spec == 'E' || S->spec == 'e')
        lf_sscanf(S, ap);
}

int spec_scanf(char spec, struct fsc* S, va_list ap) {
    int result = 1;
    S->spec = spec;
    if (S->wight == 0)
        S->wight = 999999;
    if (S->lenght == 'l')
        l_spec_scanf(S, ap);
    else if (spec == 'c')
        c_sscanf(S, ap);
    else if (spec == 'i')
        i_sscanf(S, ap);
    else if (spec == 'o')
        o_sscanf(S, ap);
    else if (spec == 's')
        s_sscanf(S, ap);
    else if (spec == 'p')
        p_sscanf(S, ap);
    else if (spec == 'n')
        n_sscanf(S, ap);
    else if (spec == 'x' || spec == 'X')
        x_sscanf(S, ap);
    else if (spec == 'd' || spec == 'u')
        d_sscanf(S, ap);
    else if ((spec == 'f' || spec == 'G' ||
             spec == 'g' || spec == 'E' ||
             spec == 'e') && S->lenght == 'L')
        llf_sscanf(S, ap);
    else if (spec == 'f' || spec == 'G' ||
             spec == 'g' || spec == 'E' ||
             spec == 'e')
        f_sscanf(S, ap);
    else
        result = 0;
    return result;
}

int s21_sscanf(const char *str, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    struct fsc S;
    char *f = (char*)format;
    S.str = S.start = (char*)str;
    S.result = *S.str == '\0' ? - 1: 0;
    S.error = 0;
    while (*f != '\0') {
        init_scanf(&S);
        if (*f == '%' && *(f + 1) != '\0') {
            f++;
            if (*f == '*') {
                S.ast = 1;
                f++;
            }
            while (*f >= '0' && *f <= '9')
                S.wight = S.wight * 10 + (*f++ - '0');
            if (*f == 'h' || *f == 'l' || *f == 'L')
                S.lenght = *f++;
            if ((S.error && *f != 'n') || !spec_scanf(*f, &S, ap))
                break;
            is_error(&S);
        }
        f++;
    }
    va_end(ap);
    return S.result;
}
