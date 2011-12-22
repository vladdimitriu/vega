
#include <stdio.h>
#include <stdlib.h>

#include <vega.h>

int main(int argc, char *argv[])
{
        struct self *self;

        self = vega_malloc(sizeof (struct self));
        vega_check_arguments(self, argc, argv);
	vega_check_self(self);
        vega_print_self(self);

        return 0;
}

