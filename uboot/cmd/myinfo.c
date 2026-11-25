#include <common.h>
#include <command.h>
#include <cli.h>
#include <console.h>

static int do_myinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int len;
	char *p;
	char *end;

	printf("chenjunzhe-202410214103\n");

	while (1) {
		len = cli_readline("If you want to continue? (y/n): ");
		if (len < 0) {
			printf("Aborted.\n");
			return 0;
		}

		/* 去除首尾空白字符 */
		p = console_buffer;
		while (*p == ' ' || *p == '\t')
			p++;

		end = p + strlen(p);
		while (end > p && (end[-1] == ' ' || end[-1] == '\t'))
			*--end = '\0';

		if (strcmp(p, "y") == 0 || strcmp(p, "Y") == 0 ||
		    strcmp(p, "yes") == 0 || strcmp(p, "YES") == 0) {
			printf("Study makes perfect, What Sutady wants to be.   =w=\n");
			return 0;
		}

		if (strcmp(p, "n") == 0 || strcmp(p, "N") == 0 ||
		    strcmp(p, "no") == 0 || strcmp(p, "NO") == 0) {
			printf("Okay, bye! =w=\n");
			return 0;
		}

		if (*p == '\0')
			printf("Empty input! Please enter y or n (Ctrl+C to quit).\n");
		else
			printf("Invalid input '%s'! Please enter y or n (Ctrl+C to quit).\n", p);
	}
}

U_BOOT_CMD(
	myinfo, 1, 0, do_myinfo,
	"Show cjz's info",
	"- using 'myinfo', you can know about me =w="
);
