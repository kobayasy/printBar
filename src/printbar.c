/* printbar.c - Last modified: 09-Feb-2024 (kobayasy)
 *
 * Copyright (C) 2024 by Yuichi Kobayashi <kobayasy@kobayasy.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <float.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "common.h"
#include "tpbar.h"

typedef struct s_llist {
    struct s_llist *next, *prev;
    int row;
    double current;
    char name[1];
} LLIST;

static LLIST *new_LLIST(LLIST *llist) {
    LIST_NEW(llist);
    llist->row = 0;
    llist->current = 0;
    return llist;
}

static LLIST *add_LLIST(LLIST *llist, const char *name) {
    LLIST *l = NULL;

    if (!*name)
        name = "\n";
    l = malloc(offsetof(LLIST, name) + strlen(name) + 1);
    if (l == NULL)
        goto error;
    strcpy(l->name, name);
    l->row = 0;
    l->current = 0;
    LIST_INSERT_NEXT(l, llist);
error:
    return l;
}

static each_next(LLIST)

typedef struct {
    unsigned int header;
    unsigned int col;
    int fdout;
    double max, min;
    TPBAR tpbar;
    int row;
} PARAM;

static int read_line(LLIST *llist, FILE *fpin) {
    int status = INT_MIN;
    char buffer[1024], *s;

    while (fgets(buffer, sizeof(buffer), fpin) != NULL) {
        s = strchr(buffer, '\n');
        if (s != NULL)
            *s = 0;
        llist = add_LLIST(llist, buffer);
        if (llist == NULL) {
            status = -1;
            goto error;
        }
    }
    status = 0;
error:
    return status;
}

static int parse_each(LLIST *l, void *data) {
    int status = INT_MIN;
    PARAM *param = data;
    char *line = NULL;
    unsigned int col;
    char *s, *e;

    l->row = param->row++;
    if (*l->name == '\n' || l->row < param->header)
        status = 1;
    else {
        line = strdup(l->name);
        if (line == NULL) {
            status = -1;
            goto error;
        }
        col = 0;
        for (s = strtok_r(line, " \t", &e); s != NULL; s = strtok_r(NULL, " \t", &e)) {
            if (col == param->col) {
                l->current = strtod(s, NULL);
                break;
            }
            ++col;
        }
        if (l->current > param->max)
            param->max = l->current;
        if (l->current < param->min)
            param->min = l->current;
        status = 0;
error:
        if (line != NULL)
            free(line);
    }
    return status;
}

static int print_each(LLIST *l, void *data) {
    int status = INT_MIN;
    PARAM *param = data;
    int co;
    char buffer[1024], *s;
    double n;

    if (*l->name == '\n')
        status = 1;
    else {
        co = param->tpbar.co - 1;
        s = buffer;
        s += tpbar_setrow(s, l->row, &param->tpbar);
        if (l->row < param->header)
            s += sprintf(s, "%-*.*s", co, co, l->name);
        else {
            n = param->max - param->min;
            n = n > 0 ? (l->current - param->min) * INT16_MAX / n : INT16_MAX;
            s += tpbar_printf(s, n, INT16_MAX, &param->tpbar, "%-*.*s", co, co, l->name );
        }
        if (write(STDOUT_FILENO, buffer, s - buffer) == -1) {
            status = -1;
            goto error;
        }
        status = 0;
error:
        ;
    }
    return status;
}

static int delete_each(LLIST *l, void *data) {
    int status = INT_MIN;

    LIST_DELETE(l);
    free(l);
    status = 0;
    return status;
}

static int printbar(FILE *fpin, unsigned int header, unsigned int col, int fdout) {
    int status = INT_MIN;
    PARAM param = {
        .header = header,
        .col = col,
        .fdout = fdout,
        .max = -DBL_MAX,
        .min =  DBL_MAX
    };
    LLIST llist;
    char buffer[1024], *s;

    new_LLIST(&llist);
    tpbar_init(&param.tpbar);
    param.row = tpbar_getrow(0, &param.tpbar);
    ONERR(read_line(&llist, fpin), -1);
    each_next_LLIST(&llist, parse_each, &param, NULL);
    each_next_LLIST(&llist, print_each, &param, NULL);
    s = buffer;
    s += tpbar_setrow(s, INT_MAX, &param.tpbar);
    if (write(STDOUT_FILENO, buffer, s - buffer) == -1) {
        status = -1;
        goto error;
    }
    status = 0;
error:
    each_next_LLIST(&llist, delete_each, NULL, NULL);
    return status;
}

typedef struct {
    bool usage;
    FILE *fpin;
    unsigned int header;
    unsigned int col;
    int fdout;
} OPT;

static int parse_arg(int argc, char *argv[], OPT *opt) {
    int status = INT_MIN;
    long n;
    char *e;

    while (*++argv != NULL)
        if (!strcmp(*argv, "--help")) {
            opt->usage = true;
            break;
        }
        else if (**argv == '+') {
            n = strtol(*argv + 1, &e, 10);
            if (*e || n < 0) {
                fprintf(stderr, "Error: invalid option: %s\n", *argv);
                status = -1;
                goto error;
            }
            opt->header = n;
        }
        else {
            n = strtol(*argv, &e, 10);
            if (*e || n < 0) {
                fprintf(stderr, "Error: invalid parameter: %s\n", *argv);
                status = -1;
                goto error;
            }
            opt->col = n;
        }
    status = 0;
error:
    return status;
}

static int usage(FILE *fp) {
    int status = INT_MIN;

    fprintf(fp, PACKAGE_STRING"\n"
                "\n"
                "Usage: "PACKAGE_TARNAME" [+HEADER] [COLUMN]\n"
                "       "PACKAGE_TARNAME" --help\n"
                "\n"
                "COLUMN    column for graph (default: 0)\n"
                "HEADER    header lines that do not graph (default: 0)\n"
                "\n"
                "subcommand\n"
                "  --help  show this help\n"
                "\n" );
    status = 0;
    return status;
}

int main(int argc, char *argv[]) {
    int status = INT_MIN;
    OPT opt = {
        .usage = false,
        .fpin = stdin,
        .header = 0,
        .col = 0,
        .fdout = STDOUT_FILENO
    };

    ONERR(parse_arg(argc, argv, &opt), -1);
    if (opt.usage)
        status = usage(stdout);
    else
        status = printbar(opt.fpin, opt.header, opt.col, opt.fdout);
error:
    return ISERR(status) ? 1 : 0;
}
