# 1 "MCAL_LAYER/mcal_std_types.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "D:/IDE MCU/packs/Microchip/PIC18Fxxxx_DFP/1.4.151/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "MCAL_LAYER/mcal_std_types.c" 2

# 1 "MCAL_LAYER/mcal_std_types.h" 1
# 13 "MCAL_LAYER/mcal_std_types.h"
# 1 "MCAL_LAYER/std_lin.h" 1
# 13 "MCAL_LAYER/std_lin.h"
# 1 "D:\\IDE MCU\\pic\\include\\c99\\stdio.h" 1 3



# 1 "D:\\IDE MCU\\pic\\include\\c99\\musl_xc8.h" 1 3
# 5 "D:\\IDE MCU\\pic\\include\\c99\\stdio.h" 2 3





# 1 "D:\\IDE MCU\\pic\\include\\c99\\features.h" 1 3
# 11 "D:\\IDE MCU\\pic\\include\\c99\\stdio.h" 2 3
# 24 "D:\\IDE MCU\\pic\\include\\c99\\stdio.h" 3
# 1 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 12 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 3
typedef void * va_list[1];




typedef void * __isoc_va_list[1];
# 128 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned size_t;
# 143 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 ssize_t;
# 174 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __int24 int24_t;
# 210 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 255 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long long off_t;
# 409 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct _IO_FILE FILE;
# 25 "D:\\IDE MCU\\pic\\include\\c99\\stdio.h" 2 3
# 52 "D:\\IDE MCU\\pic\\include\\c99\\stdio.h" 3
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;





FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict, FILE *restrict);
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *restrict, fpos_t *restrict);
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);





int ungetc(int, FILE *);
int getch(void);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);





void putch(char);

char *fgets(char *restrict, int, FILE *restrict);

char *gets(char *);


int fputs(const char *restrict, FILE *restrict);
int puts(const char *);

__attribute__((__format__(__printf__, 1, 2)))
int printf(const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int fprintf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int sprintf(char *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 3, 4)))
int snprintf(char *restrict, size_t, const char *restrict, ...);

__attribute__((__format__(__printf__, 1, 0)))
int vprintf(const char *restrict, __isoc_va_list);
int vfprintf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 2, 0)))
int vsprintf(char *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 3, 0)))
int vsnprintf(char *restrict, size_t, const char *restrict, __isoc_va_list);

__attribute__((__format__(__scanf__, 1, 2)))
int scanf(const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int fscanf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int sscanf(const char *restrict, const char *restrict, ...);

__attribute__((__format__(__scanf__, 1, 0)))
int vscanf(const char *restrict, __isoc_va_list);
int vfscanf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__scanf__, 2, 0)))
int vsscanf(const char *restrict, const char *restrict, __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *restrict, char *restrict, int, size_t);
void setbuf(FILE *restrict, char *restrict);

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *restrict, size_t, const char *restrict);
FILE *open_memstream(char **, size_t *);
FILE *fdopen(int, const char *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int dprintf(int, const char *restrict, ...);
int vdprintf(int, const char *restrict, __isoc_va_list);
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
ssize_t getdelim(char **restrict, size_t *restrict, int, FILE *restrict);
ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
int renameat(int, const char *, int, const char *);
char *ctermid(char *);







char *tempnam(const char *, const char *);
# 13 "MCAL_LAYER/std_lin.h" 2

# 1 "D:\\IDE MCU\\pic\\include\\c99\\stdlib.h" 1 3
# 21 "D:\\IDE MCU\\pic\\include\\c99\\stdlib.h" 3
# 1 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 24 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long int wchar_t;
# 22 "D:\\IDE MCU\\pic\\include\\c99\\stdlib.h" 2 3

int atoi (const char *);
long atol (const char *);

long long atoll (const char *);

double atof (const char *);


float strtof (const char *restrict, char **restrict);
double strtod (const char *restrict, char **restrict);
long double strtold (const char *restrict, char **restrict);



long strtol (const char *restrict, char **restrict, int);
unsigned long strtoul (const char *restrict, char **restrict, int);

long long strtoll (const char *restrict, char **restrict, int);
unsigned long long strtoull (const char *restrict, char **restrict, int);


unsigned long __strtoxl(const char * s, char ** endptr, int base, char is_signed);

unsigned long long __strtoxll(const char * s, char ** endptr, int base, char is_signed);
# 55 "D:\\IDE MCU\\pic\\include\\c99\\stdlib.h" 3
int rand (void);
void srand (unsigned);

void *malloc (size_t);
void *calloc (size_t, size_t);
void *realloc (void *, size_t);
void free (void *);

          void abort (void);
int atexit (void (*) (void));
          void exit (int);
          void _Exit (int);

void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));







__attribute__((nonreentrant)) void qsort (void *, size_t, size_t, int (*)(const void *, const void *));

int abs (int);
long labs (long);

long long llabs (long long);


typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

typedef struct { long long quot, rem; } lldiv_t;


div_t div (int, int);
ldiv_t ldiv (long, long);

lldiv_t lldiv (long long, long long);


typedef struct { unsigned int quot, rem; } udiv_t;
typedef struct { unsigned long quot, rem; } uldiv_t;
udiv_t udiv (unsigned int, unsigned int);
uldiv_t uldiv (unsigned long, unsigned long);
# 14 "MCAL_LAYER/std_lin.h" 2

# 1 "D:\\IDE MCU\\pic\\include\\c99\\string.h" 1 3
# 25 "D:\\IDE MCU\\pic\\include\\c99\\string.h" 3
# 1 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 421 "D:\\IDE MCU\\pic\\include\\c99\\bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 26 "D:\\IDE MCU\\pic\\include\\c99\\string.h" 2 3

void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);




char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 15 "MCAL_LAYER/std_lin.h" 2
# 13 "MCAL_LAYER/mcal_std_types.h" 2

# 1 "MCAL_LAYER/compiler.h" 1
# 14 "MCAL_LAYER/mcal_std_types.h" 2
# 25 "MCAL_LAYER/mcal_std_types.h"
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef signed int sint32;
typedef signed char sint8;
typedef signed short sint16;
typedef uint8 Std_ReturnType;
# 2 "MCAL_LAYER/mcal_std_types.c" 2

