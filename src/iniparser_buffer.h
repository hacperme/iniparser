#ifndef __INIPARSER_BUFFER__
#define __INIPARSER_BUFFER__

typedef struct
{
    void *data;
    int size;
    int r_offset;
    int w_offset;
}iniparser_buffer_t;

int iniparser_buffer_init(iniparser_buffer_t *in, int len);

int iniparser_buffer_deinit(iniparser_buffer_t *in);

int iniparser_buffer_write(const unsigned char *buffer, int n, iniparser_buffer_t *in);

int iniparser_buffer_read(char *buffer, int n, iniparser_buffer_t *in);

char *iniparser_buffer_gets(char *buffer, int n, iniparser_buffer_t *in);

int iniparser_buffer_eof(iniparser_buffer_t *in);

int iniparser_buffer_sprintf(iniparser_buffer_t *in, const char *fmt, ...);
#endif //__INIPARSER_BUFFER__
