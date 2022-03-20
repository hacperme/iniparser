#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "iniparser_buffer.h"

int iniparser_buffer_init(iniparser_buffer_t *in, int len)
{
    int ret = -1;
    if(in == NULL || len <= 0)
    {
        goto exit;
    }

    in->data = malloc(len);
    if(in->data == NULL)
    {
        goto exit;
    }
    memset(in->data, 0, len);
    in->size = len;
    in->r_offset = 0;
    in->w_offset = 0;

    ret = 0;

exit:
    return ret;
}

int iniparser_buffer_deinit(iniparser_buffer_t *in)
{
    if(in == NULL)
    {
        return -1;
    }

    if(in->data!=NULL)
    {
        free(in->data);
        in->data = NULL;
    }

    in->r_offset = 0;
    in->w_offset = 0;
    in->size = 0;

    return 0;
}

int iniparser_buffer_write(const unsigned char *buffer, int n, iniparser_buffer_t *in)
{
    int len = 0;
    char *tmp = NULL;
    if(buffer == NULL || in == NULL)
    {
        return -1;
    }


    len = in->size - in->w_offset;

    if(len < n)
    {
        tmp = malloc(in->size+ n-len);
        if(tmp == NULL)
        {
            return -1;
        }
        memcpy(tmp, in->data, in->size);
        in->size += n-len;
        free(in->data);
        in->data = tmp;
        tmp = NULL;
    }

    memcpy(in->data+in->w_offset, buffer, n);
    in->w_offset += n;

    return n;
}

int iniparser_buffer_read(char *buffer, int n, iniparser_buffer_t *in)
{
    int len = 0;
    if(buffer == NULL || n<=0 || in == NULL)
    {
        return -1;
    }

    if(in->r_offset == in->size)
    {
        return 0;
    }

    len = in->w_offset - in->r_offset;

    if(n <= len)
    {
        len = n;
    }

    memcpy(buffer, in->data+in->r_offset, len);
    in->r_offset += len;

    return len;
}

char *iniparser_buffer_gets(char *buffer, int n, iniparser_buffer_t *in)
{
    char *s = NULL;
    unsigned char *p, *t;
    int len = 0;

    if(buffer == NULL || in == NULL)
    {
        return NULL;
    }

    if(n<=0)
    {
        return NULL;
    }

    s = buffer;

    n--;

    while (n != 0)
    {
        /* check eof */
        if(in->w_offset == in->r_offset)
        {
            if(s == buffer)
            {
                return NULL;
            }

            break;
        }

        len = in->w_offset - in->r_offset;

        if(len > n)
        {
            len = n;
        }

        p = in->data+in->r_offset;

        t = memchr((void *)p, '\n', len);
        if(t!=NULL)
        {
            len = ++t - p;
            in->r_offset+=len;
            memcpy((void *)s, (void *)p, len);
            s[len] = '\0';
            return buffer;
        }

        in->r_offset+=len;
        memcpy((void *)s, (void *)p, len);
        s += len;
        n -= len;

    }

    *s = '\0';

    return buffer;

}

int iniparser_buffer_eof(iniparser_buffer_t *in)
{
    if(in == NULL)
    {
        return 1;
    }

    if(in->w_offset == in->r_offset)
    {
        return 1;
    }

    return 0;
}

int iniparser_buffer_sprintf(iniparser_buffer_t *in, const char *fmt, ...)
{
    int ret = 0;
    va_list ap;
    if(in == NULL)
    {
        return -1;
    }

    if(in->size == in->w_offset)
    {
        return -1;
    }
    va_start(ap, fmt);
    ret = vsnprintf(in->data+in->w_offset, in->size-in->w_offset-1, fmt, ap);
    va_end(ap);
    in->w_offset+=ret;
    return ret;
}

