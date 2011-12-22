#ifndef __VEGA_H__
#define __VEGA_H__

#include <stdio.h>
#include <stdlib.h>

#define MALLOC_ATTEMPTS 42
#define CONTINOUS_OPERATION 1
#define BUFFERSIZE 4096

enum log_level {
	muted,
	fatal,
	error,
	warning,
	info,
	decision,
	trace
};

struct tuple {
	char *key;
	char *value;
};

struct bufer {
	size_t cursor;
	char byte[BUFFERSIZE - sizeof (size_t)];
};

enum http_request_header_field {
	_request_accept,
	_request_accept_charset,
	_request_accept_encondig,
	_request_accept_language,
	_request_authorization,
	_request_cache_control,
	_request_connection,
	_request_cookie,
	_request_content_length,
	_request_content_md5,
	_request_content_type,
	_request_date,
	_request_expect,
	_request_from,
	_request_host,
	_request_if_match,
	_request_if_modified_since,
	_request_if_none_match,
	_request_if_range,
	_request_if_unmodified_since,
	_request_max_forwards,
	_request_pragma,
	_request_proxy_authorization,
	_request_range,
	_request_referer,
	_request_te,
	_request_upgrade,
	_request_user_agent,
	_request_via,
	_request_warning,
	_request_x_requested_with,
	_request_x_do_not_trak,
	_request_dnt,
	_request_x_forwarded_for
};

enum http_response_header_field {
	_response_accept_ranges,
	_response_age,
	_response_allow,
	_response_cache_control,
	_response_connection,
	_response_content_enconding,
	_response_content_language,
	_response_content_length,
	_response_content_location,
	_response_content_md5,
	_response_content_disposition,
	_response_content_range,
	_response_content_type,
	_response_date,
	_response_etag,
	_response_expires,
	_response_last_modified,
	_response_link,
	_response_location,
	_response_p3p,
	_response_pragma,
	_response_proxy_authenticate,
	_response_refresh,
	_response_retry_after,
	_response_server,
	_response_set_cookie,
	_response_strict_transport_security,
	_response_trailer,
	_response_transfer_encoding,
	_response_vary,
	_response_via,
	_response_warning,
	_response_www_authenticate,
	_response_x_frame_options,
	_response_x_xss_protection,
	_response_x_content_type_options,
	_response_x_forwarded_proto,
	_response_x_powered_by
};

enum http_status_code {
	_status_continue				= 100,
	_status_switching_protocols			= 101,
	_status_processing				= 102,
	_status_checkpoint				= 103,
	_status_ok					= 200,
	_status_created					= 201,
	_status_accepted				= 202,
	_status_non_authoritative_information		= 203,
	_status_no_content				= 204,
	_status_reset_content				= 205,
	_status_partial_content				= 206,
	_status_multi_status				= 207,
	_status_already_reported			= 208,
	_status_im_used					= 226,
	_status_multiple_choices			= 300,
	_status_moved_permanently			= 301,
	_status_found					= 302,
	_status_see_other				= 303,
	_status_not_modified				= 304,
	_status_use_proxy				= 305,
	_status_switch_proxy				= 306,
	_status_temporary_redirect			= 307,
	_status_resume_incomplete			= 308,
	_status_client_error				= 400,
	_status_unauthorized				= 401,
	_status_payment_required			= 402,
	_status_forbidden				= 403,
	_status_not_found				= 404,
	_status_method_not_allowed			= 405,
	_status_not_acceptable				= 406,
	_status_proxy_authentication_required		= 407,
	_status_request_timeout				= 408,
	_status_conflict				= 409,
	_status_gone					= 410,
	_status_length_required				= 411,
	_status_precondition_failed			= 412,
	_status_request_entity_too_large		= 413,
	_status_request_uri_too_long			= 414,
	_status_unsupported_media_type			= 415,
	_status_requested_range_not_satisfiable		= 416,
	_status_expectation_failed			= 417,
	_status_i_am_a_teapot				= 418,
	_status_unprocessable_entity			= 422,
	_status_locked					= 423,
	_status_failed_dependency			= 424,
	_status_unordered_collection			= 425,
	_status_upgrade_required			= 426,
	_status_precondition_require			= 428,
	_status_too_many_requests			= 429,
	_status_request_header_fileds_too_large		= 431,
	_status_no_response				= 444,
	_status_retry_with				= 449,
	_status_blocked_by_windows_parental_controls	= 450,
	_status_client_closed_request			= 499,
	_status_internal_server_error			= 500,
	_status_not_implemented				= 501,
	_status_bad_gateway				= 502,
	_status_service_unavailable			= 503,
	_status_gateway_timeout				= 504,
	_status_http_version_not_supported		= 505,
	_status_variant_also_negotiates			= 506,
	_status_insuficient_storage			= 507,
	_status_loop_detected				= 508,
	_status_bandwidth_limit_exceeded		= 509,
	_status_not_extended				= 510,
	_status_network_authentication_required		= 511
};

struct http_request_header {
	char *field[34];
	struct buffer *buffer;
};
struct parser {
	struct parser *next;
};

struct page {
	struct page *next;
	char *url;
	struct tuple *header;
	char *body;
};

struct perspective {
	struct perspective *next;
};

struct self {
	int pid;
	char *source;
	char *destination;
	char *configuration;
	int verbosity;
	char *log_file;
	FILE *log;
};

extern void vega_check_self(struct self *self);
extern void vega_print_self(struct self *self);
extern void vega_check_arguments(struct self *self, int argc, char *argv[]);
extern void *vega_malloc(const size_t size);
extern void *vega_realloc(void *pointer, const size_t size);
extern void vega_log(struct self *self, const int severity,
	const char *format, ...);
extern struct page *vega_request_page(char *page);
extern int vega_connect_page(struct self *self, const char *page);
extern void vega_read_page(struct self *self, struct page);
extern void vega_analyse_page(struct self *self, struct page *page,
	struct parser *parser);
extern void vega_build_perspective(struct self *self, struct page *page);
extern void vega_adjust_perspective(struct self *self, struct page *page);
extern void vega_change_perspective(struct self *self, struct perspective
	*perspective);

extern int http_ok(void);
#endif

