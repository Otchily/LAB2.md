#include <stdio.h>
#include <stdlib.h>

static long long g_argc = 0;
static char** g_argv = NULL;

void mp_init_runtime(long long argc, char* argv) {
    g_argc = argc;
    g_argv = (char**)argv;
}

long long mp_argc(void) {
    return g_argc;
}

long long mp_argi(long long index) {
    if (!g_argv) return 0;
    if (index < 0 || index >= g_argc) return 0;
    return strtoll(g_argv[index], NULL, 10);
}

void mp_write_int(long long value) {
    printf("%lld", value);
}

void mp_writeln_int(long long value) {
    printf("%lld\n", value);
}

void mp_write_bool(int value) {
    fputs(value ? "true" : "false", stdout);
}

void mp_writeln_bool(int value) {
    fputs(value ? "true\n" : "false\n", stdout);
}

void mp_write_str(char* value) {
    if (value) fputs(value, stdout);
}

void mp_writeln(void) {
    fputc('\n', stdout);
}
