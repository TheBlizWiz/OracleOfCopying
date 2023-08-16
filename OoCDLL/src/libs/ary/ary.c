#include "ary.h"
#include <ctype.h>

/* taken from OpenBSD */
#define MUL_NO_OVERFLOW	((size_t)1 << (sizeof(size_t) * 4))

static void *array_xrealloc_builtin(void *ptr, size_t nmemb, size_t size) {
    if ((nmemb >= MUL_NO_OVERFLOW || size >= MUL_NO_OVERFLOW) &&
        nmemb > 0 && SIZE_MAX / nmemb < size)
        return NULL;
    return realloc(ptr, nmemb * size);
}

array_xalloc_t array_xrealloc = array_xrealloc_builtin;
static array_xdealloc_t array_xfree = free;

void array_cb_freevoidptr(void *buf, void *userp) {
    (void) userp;
    array_xfree(*(void **) buf);
}

void array_cb_freecharptr(void *buf, void *userp) {
    (void) userp;
    array_xfree(*(char **) buf);
}

int array_cb_cmpint(const void *a, const void *b) {
    int x = *(const int *) a, y = *(const int *) b;

    return x > y ? 1 : x < y ? -1 : 0;
}

int array_cb_cmplong(const void *a, const void *b) {
    long x = *(const long *) a, y = *(const long *) b;

    return x > y ? 1 : x < y ? -1 : 0;
}

int array_cb_cmpvlong(const void *a, const void *b) {
    long long x = *(const long long *) a, y = *(const long long *) b;

    return x > y ? 1 : x < y ? -1 : 0;
}

int array_cb_cmpsize_t(const void *a, const void *b) {
    size_t x = *(const size_t *) a, y = *(const size_t *) b;

    return x > y ? 1 : x < y ? -1 : 0;
}

int array_cb_cmpdouble(const void *a, const void *b) {
    double x = *(const double *) a, y = *(const double *) b;

    return x > y ? 1 : x < y ? -1 : 0;
}

int array_cb_cmpchar(const void *a, const void *b) {
    char x = *(const char *) a, y = *(const char *) b;

    return x > y ? 1 : x < y ? -1 : 0;
}

int array_cb_strcmp(const void *a, const void *b) {
    return strcmp(*(char **) a, *(char **) b);
}

int strcasecmp(const char *a, const char *b) {
    int ca, cb;
    do {
        ca = *(unsigned char *) a;
        cb = *(unsigned char *) b;
        ca = tolower(toupper(ca));
        cb = tolower(toupper(cb));
        a++;
        b++;
    } while (ca == cb && ca != '\0');
    return ca - cb;
}

int array_cb_strcasecmp(const void *a, const void *b) {
    return strcasecmp(*(char **) a, *(char **) b);
}

static const size_t snprintf_bufsize = 32;

int array_cb_voidptrtostr(char **ret, const void *elem) {
    if (!(*ret = array_xrealloc(NULL, snprintf_bufsize, 1)))
        return -1;
    return snprintf(*ret, snprintf_bufsize, "%p", *(void **) elem);
}

int array_cb_inttostr(char **ret, const void *elem) {
    if (!(*ret = array_xrealloc(NULL, snprintf_bufsize, 1)))
        return -1;
    return snprintf(*ret, snprintf_bufsize, "%d", *(int *) elem);
}

int array_cb_longtostr(char **ret, const void *elem) {
    if (!(*ret = array_xrealloc(NULL, snprintf_bufsize, 1)))
        return -1;
    return snprintf(*ret, snprintf_bufsize, "%ld", *(long *) elem);
}

int array_cb_vlongtostr(char **ret, const void *elem) {
    if (!(*ret = array_xrealloc(NULL, snprintf_bufsize, 1)))
        return -1;
    return snprintf(*ret, snprintf_bufsize, "%lld", *(long long *) elem);
}

int array_cb_size_ttostr(char **ret, const void *elem) {
    if (!(*ret = array_xrealloc(NULL, snprintf_bufsize, 1)))
        return -1;
    return snprintf(*ret, snprintf_bufsize, "%zu", *(size_t *) elem);
}

int array_cb_doubletostr(char **ret, const void *elem) {
    if (!(*ret = array_xrealloc(NULL, snprintf_bufsize, 1)))
        return -1;
    return snprintf(*ret, snprintf_bufsize, "%g", *(double *) elem);
}

int array_cb_chartostr(char **ret, const void *elem) {
    if (!(*ret = array_xrealloc(NULL, snprintf_bufsize, 1)))
        return -1;
    return snprintf(*ret, snprintf_bufsize, "%d", *(char *) elem);
}

void array_use_as_realloc(array_xalloc_t routine) {
    array_xrealloc = routine;
}

void array_use_as_free(array_xdealloc_t routine) {
    array_xfree = routine;
}

void array_freebuf(struct arrayb *array) {
    if (array->len && array->dtor) {
        array_elemcb_t dtor = array->dtor;
        char *elem = array->buf;
        void *userp = array->userp;
        size_t i;

        for (i = array->len; i--; elem += array->sz)
            dtor(elem, userp);
    }
    array_xfree(array->buf);
}

void *(array_detach) (struct arrayb *array, size_t *ret) {
    void *buf;

    (array_shrinktofit) (array);
    buf = array->buf;
    if (ret)
        *ret = array->len;
    array->alloc = array->len = 0;
    array->buf = NULL;
    return buf;
}

int (array_shrinktofit)(struct arrayb *array) {
    void *buf;

    if (array->alloc == array->len)
        return 1;
    if (array->len) {
        buf = array_xrealloc(array->buf, array->len, array->sz);
        if (!buf)
            return 0;
    }
    else {
        array_xfree(array->buf);
        buf = NULL;
    }
    array->alloc = array->len;
    array->buf = buf;
    return 1;
}

void *(array_splicep) (struct arrayb *array, size_t pos, size_t rlen, size_t alen) {
    char *buf;

    if (pos > array->len)
        pos = array->len;
    if (rlen > array->len - pos)
        rlen = array->len - pos;
    if (alen > rlen && !(array_grow) (array, alen - rlen))
        return NULL;
    buf = (char *) array->buf + (pos * array->sz);
    if (rlen && array->dtor) {
        array_elemcb_t dtor = array->dtor;
        char *elem = buf;
        void *userp = array->userp;
        size_t i;

        for (i = rlen; i--; elem += array->sz)
            dtor(elem, userp);
    }
    if (rlen != alen && pos < array->len)
        memmove(buf + (alen * array->sz), buf + (rlen * array->sz),
            (array->len - pos - rlen) * array->sz);
    array->len = array->len - rlen + alen;
    return buf;
}

int (array_index)(struct arrayb *array, size_t *ret, size_t start, const void *data,
    array_cmpcb_t comp) {
    size_t i;
    char *elem = (char *) array->buf + (start * array->sz);

    for (i = start; i < array->len; i++, elem += array->sz) {
        if (comp ? !comp(elem, data) : !memcmp(elem, data, array->sz)) {
            if (ret)
                *ret = i;
            return 1;
        }
    }
    return 0;
}

int (array_rindex)(struct arrayb *array, size_t *ret, size_t start, const void *data,
    array_cmpcb_t comp) {
    size_t i;
    char *elem;

    if (start >= array->len)
        start = array->len - 1;
    elem = (char *) array->buf + (start * array->sz);
    for (i = start; i--; elem -= array->sz) {
        if (comp ? !comp(elem, data) : !memcmp(elem, data, array->sz)) {
            if (ret)
                *ret = i + 1;
            return 1;
        }
    }
    return 0;
}

int (array_reverse)(struct arrayb *array) {
    size_t i, j;
    char *p, *q, *tmp;

    tmp = array_xrealloc(NULL, 1, array->sz);
    if (!tmp)
        return 0;
    j = array->len - 1;
    p = (char *) array->buf;
    q = p + (j * array->sz);
    for (i = 0; i < array->len / 2; i++, j--) {
        memcpy(tmp, p, array->sz);
        memcpy(p, q, array->sz);
        memcpy(q, tmp, array->sz);
        p += array->sz;
        q -= array->sz;
    }
    array_xfree(tmp);
    return 1;
}

int (array_join)(struct arrayb *array, char **ret, const char *sep,
    array_joincb_t stringify) {
    struct array_char strbuf;
    char *elem = (char *) array->buf, *tmp;
    size_t seplen = sep ? strlen(sep) : 0, i, len;
    int tmplen, tmpret;

    if (!array_init(&strbuf, 1024))
        goto error;
    for (i = 0; i < array->len; i++, elem += array->sz) {
        if (stringify) {
            tmplen = stringify(&tmp, elem);
            if (tmplen > 0) {
                tmpret = array_splice(&strbuf, strbuf.len, 0,
                    tmp, tmplen);
                array_xfree(tmp);
                if (!tmpret)
                    goto error;
            }
            else if (!tmplen) {
                array_xfree(tmp);
            }
        }
        else {
            tmp = *(char **) elem;
            if (!tmp)
                continue;
            if (!array_splice(&strbuf, strbuf.len, 0, tmp,
                strlen(tmp)))
                goto error;
        }
        if (seplen) {
            if (!array_splice(&strbuf, strbuf.len, 0, sep, seplen))
                goto error;
        }
    }
    if (!strbuf.len) {
        if (!(*ret = _strdup("")))
            goto error;
        return 0;
    }
    array_setlen(&strbuf, strbuf.len - seplen + 1);
    strbuf.buf[strbuf.len - 1] = '\0';
    array_shrinktofit(&strbuf);
    *ret = array_detach(&strbuf, &len);
    return (int) len;

error:
    array_release(&strbuf);
    *ret = NULL;
    return -1;
}

int (array_swap)(struct arrayb *array, size_t a, size_t b) {
    char *p, *q, *tmp;

    if (a >= array->len)
        a = array->len - 1;
    if (b >= array->len)
        b = array->len - 1;
    if (a == b)
        return 1;
    tmp = array_xrealloc(NULL, 1, array->sz);
    if (!tmp)
        return 0;
    p = (char *) array->buf + (a * array->sz);
    q = (char *) array->buf + (b * array->sz);
    memcpy(tmp, p, array->sz);
    memcpy(p, q, array->sz);
    memcpy(q, tmp, array->sz);
    array_xfree(tmp);
    return 1;
}

int (array_search)(struct arrayb *array, size_t *ret, size_t start, const void *data,
    array_cmpcb_t comp) {
    size_t count = (start < array->len) ? array->len - start : 0;
    char *elem = (char *) array->buf + (start * array->sz);
    void *ptr = bsearch(data, elem, count, array->sz, comp);

    if (!ptr)
        return 0;
    if (ret)
        *ret = (size_t) ((uintptr_t) ptr - (uintptr_t) array->buf);
    return 1;
}

int (array_unique)(struct arrayb *array, array_cmpcb_t comp) {
    void *list, *end;
    size_t num, i;
    char *elem;

    num = array->len;
    list = array_xrealloc(NULL, num, array->sz);
    if (!list)
        return 0;
    end = (char *) list + num * array->sz;
    memcpy(list, array->buf, num * array->sz);
    qsort(list, num, array->sz, comp);
    for (i = 0, elem = list; i < num - 1;) {
        char *next = elem + array->sz;

        if (!comp(elem, next)) {
            memmove(next, next + array->sz, (num - i - 2) * array->sz);
            num--;
        }
        else {
            elem = next;
            i++;
        }
    }
    for (i = 0, elem = array->buf; i < array->len;) {
        void *ptr = bsearch(elem, list, num, array->sz, comp);
        size_t rest;

        if (!ptr) {
            if (array->dtor)
                array->dtor(elem, array->userp);
            ptr = elem;
            rest = (--array->len - i) * array->sz;
        }
        else {
            elem += array->sz;
            num--;
            i++;
            rest = (size_t) ((uintptr_t) end - (uintptr_t) ptr) -
                array->sz;
        }
        memmove(ptr, (char *) ptr + array->sz, rest);
    }
    free(list);
    return 1;
}
