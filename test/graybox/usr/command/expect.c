#include "expect.h"

#include <errno.h>
#include "common.h"
#include "common/types.h"
#include "usr/util/str_utils.h"
#include "usr/argp/log.h"

int parse_exceptions(char *exceptions, struct expect_add_request *req)
{
	__u16 len;
	struct jool_result result;

	result = str_to_plateaus_array(exceptions, req->exceptions, &len);
	if (result.error)
		return pr_result(&result);

	req->exceptions_len = len;
	return 0;
}

int expect_init_request(int argc, char **argv, enum graybox_command *cmd,
		struct expect_add_request *req)
{
	int error;

	if (argc < 1) {
		pr_err("expect needs an operation as first argument.");
		return -EINVAL;
	}

	if (strcasecmp(argv[0], "add") == 0) {
		*cmd = COMMAND_EXPECT_ADD;

		if (argc < 2) {
			pr_err("expect add needs a packet as argument.");
			return -EINVAL;
		}

		req->file_name = argv[1];
		error = load_pkt(argv[1], &req->pkt, &req->pkt_len);
		if (error)
			return error;
		return (argc >= 3) ? parse_exceptions(argv[2], req) : 0;

	} else if (strcasecmp(argv[0], "flush") == 0) {
		*cmd = COMMAND_EXPECT_FLUSH;
		return 0;
	}

	pr_err("Unknown operation for expect: %s", argv[0]);
	return -EINVAL;
}

void expect_add_clean(struct expect_add_request *req)
{
	if (req->pkt)
		free(req->pkt);
}

int expect_add_build_pkt(struct expect_add_request *req, struct nl_msg *pkt)
{
	int error;

	error = nla_put_string(pkt, ATTR_FILENAME, req->file_name);
	if (error)
		return error;

	error = nla_put(pkt, ATTR_PKT, req->pkt_len, req->pkt);
	if (error)
		return error;

	if (req->exceptions_len)
		error = nla_put(pkt, ATTR_EXCEPTIONS,
				sizeof(*req->exceptions) * req->exceptions_len,
				req->exceptions);

	return error;
}
