#include <common.h>
#include <command.h>

static int do_ciallo(cmd_tbl_t *cmdtp, int flag, int argc, char* const argv[])
{
    printf("Ciallo～(∠・ω < )⌒ ☆\n");
    return 0;
}

U_BOOT_CMD(
        ciallo, 4, 1, do_ciallo,
        "Show Ciallo",
        "- using 'ciallo' can do that!!!"
        );
