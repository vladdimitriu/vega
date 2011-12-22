#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include <vega.h>


static void vega_print_command_line_help(void)
{
	puts("vega [OPTIONS]");
	puts("  -c --config           configuration.file");
	puts("  -l --log              log.file");
	puts("  -s --source           source.url[,source.url]");
	puts("  -d --destination      destination.url[,destination.url]");
	puts("  -v --verbosity        1..6");
	puts("  -V --version");
}

void vega_print_self(struct self *self)
{
	if (!self) return;

	vega_log(self, info, " PID:	      %d", self->pid);
	vega_log(self, info, " Configuration: %s", self->configuration);
	vega_log(self, info, " Source:        %s", self->source);
	vega_log(self, info, " Destination:   %s", self->destination);
	vega_log(self, info, " Verbosity:     %d", self->verbosity);
	vega_log(self, info, " Log File:      %s", self->log_file);
}

void vega_check_arguments(struct self *self, int argc, char *argv[])
{
        struct option l_opts[] = {
                {"config", 1, NULL, 'c'},
                {"log", 1, NULL, 'l'},
                {"verbosity", 1, NULL, 'v'},
                {"source", 1, NULL, 's'},
                {"destination", 1, NULL, 'd'},
                {"version", 0, NULL, 'V'}
        };
	char *options = "c:v:u:s:d:l:V" ;
        int c;

	if (argc < 2) {
		vega_print_command_line_help();
		exit(EXIT_FAILURE);
	}

        while ((c = getopt_long(argc, argv, options, l_opts, NULL)) != -1) {
                switch (c) {
                case 'V':
                        printf("\tversion 1\n");
                        exit(0);
                case 'c':
                        self->configuration = strdup(optarg);
                        break;
                case 'v':
                        self->verbosity = atoi(optarg);
                        break;
		case 's':
			self->source = strdup(optarg);
			break;
		case 'd':
			self->destination = strdup(optarg);
			break;
		case 'l':
			self->log_file = strdup(optarg);
			break;
                default:
			break;
                }
		self->pid = getpid();
        }
}

void vega_check_self(struct self *self)
{
        if (!self) {
                exit(EXIT_FAILURE);
        }
	if (self->log_file && !self->log) {
		self->log = fopen(self->log_file, "a+");
		if (!self->log) {
			exit(EXIT_FAILURE);
		}
	}
}

void *vega_malloc(const size_t size)
{
        void *pointer;
        int attempts = MALLOC_ATTEMPTS;

#ifdef CONTINOUS_OPERATION
start:  do {
#endif
                pointer = malloc(size);
#ifndef CONTINOUS_OPERATION
                if (!pointer) exit(EXIT_FAILURE);
#else
                attempts--;
        } while (!pointer || !attempts);

	if (!pointer) {
		sleep(1);
		goto start;
	}
#endif
        return pointer;
}

void *vega_realloc(void *pointer, const size_t size)
{
	if(!(pointer = realloc(pointer, size))) exit(EXIT_FAILURE);

	return pointer;
}

void vega_log(struct self *self, const int severity, const char *format, ...)
{
        int n;
        int size = 512;
        char *buffer;
        va_list ap;
        char date[22];
        time_t current_time;
        struct tm *local_time;

        current_time = time(NULL);
        local_time = localtime(&current_time);
        strftime(date, 22, "[%Y-%m-%d %H:%M:%S]", local_time);
        buffer = vega_malloc(size);
        while (1) {
                va_start(ap, format);
                n = vsnprintf(buffer, size, format, ap);
                va_end(ap);
                if (n > -1 && n < size) {
                        break;
                }
                if (n > -1) {
                        size = n + 1;
                } else {
                        size *= 2;
                }
                buffer = vega_realloc(buffer, size);
        }
	if (!self->log) self->log = stderr;
        flockfile(self->log);
        fprintf(self->log, "%s %u %d %s\n", date, self->pid, severity, buffer);
#ifdef SAFE_OPERATIONS
        fflush(self->log);
#endif
        funlockfile(self->log);
}

