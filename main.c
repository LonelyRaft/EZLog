
#include "ezlog.h"
#include "ezexcept.h"

#include <stdlib.h>

const Except DemoExcept = {"it is a test exception"};

void raise_demo_except(void)
{
    RAISE(DemoExcept);
}

int main(int argc, char *argv[])
{
    TRY
    {
        raise_demo_except();
        // printf("%s\n", argv[0]);
    }
    EXCEPT(DemoExcept)
    {
        LOG_ERR("error test");
        LOG_WARN("warning test");
        LOG_INFO("infomation test");
        LOG_DBG("debug test");
    }
    ENDTRY
    return 0;
}
