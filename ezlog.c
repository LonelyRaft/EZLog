
#include "ezlog.h"
#include <assert.h>

/*
windows stderr: "CON"
linux stderr: "/dev/console"
rtthread stderr: "STDERR"
*/

void *ezlog_redirect(const char *_log_path)
{
    assert(0 != _log_path);
    return freopen(_log_path, "w", stderr);
}
