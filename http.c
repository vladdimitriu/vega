
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vega.h>

static char * http_request_header_field_name[34] = {
	"Accept",
	"Accept-Charset",
	"Accept-Encoding",
	"Accept-Language",
	"Authorization",
	"Cache-Control",
	"Connection",
	"Cookie",
	"Content-Length",
	"Content-MD5",
	"Content-Type",
	"Date",
	"Expect",
	"From",
	"Host",
	"If-Match",
	"If-Modified-Since",
	"If-None-Match",
	"If-Range",
	"If-Unmodified-Since",
	"Max-Forwards",
	"Pragma",
	"Proxy-Authorization",
	"Range",
	"Referer",
	"TE",
	"Upgrade",
	"User-Agent",
	"Via",
	"Warning",
	"X-Requested-With",
	"X-Do-Not-Track",
	"DNT",
	"X-Forwarded-For"
};


static void parse_http_header(struct page *page) {
	struct http_request_header *header = vega_malloc(sizeof *header);
	char *field = NULL;
	if (!strcmp(field, http_request_header_field_name[_request_accept])) {
		return;
	}
	if (!page) {
		return;
	}
}

int http_ok(void) {
	parse_http_header(NULL);

	return 0;
}

