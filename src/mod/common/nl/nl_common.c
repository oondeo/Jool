#include "mod/common/nl/nl_common.h"

#include "common/types.h"
#include "mod/common/log.h"

int verify_superpriv(void)
{
	if (!capable(CAP_NET_ADMIN)) {
		log_err("CAP_NET_ADMIN capability required. (Maybe try using su or sudo?)");
		return -EPERM;
	}

	return 0;
}

struct request_hdr *get_jool_hdr(struct genl_info *info)
{
	return nla_data(info->attrs[ATTR_DATA]);
}

int validate_request_size(struct genl_info *info, size_t min_expected)
{
	size_t request_size = nla_len(info->attrs[ATTR_DATA]);

	min_expected += sizeof(struct request_hdr);
	if (request_size < min_expected) {
		log_err("The minimum expected request size was %zu bytes; got %zu instead.",
				min_expected, request_size);
		return -EINVAL;
	}

	return 0;
}

char *get_iname(struct genl_info *info)
{
	return (info->attrs[ATTR_INAME])
			? nla_data(info->attrs[ATTR_INAME])
			: INAME_DEFAULT;
}
