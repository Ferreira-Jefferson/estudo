#ifndef JF_STRING_H
#define JF_STRING_H

int jf_strlen(char *str);

struct string {
    char *value;
    int (*jf_strlen)(char *);
};

extern struct string String;

#endif