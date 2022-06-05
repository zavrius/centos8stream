#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
int main(void) {
    // check path before chroot()
    char t_cwd[PATH_MAX];
    getcwd(t_cwd, sizeof(t_cwd));
    printf("Current dir before chroot(): %s\n", t_cwd);
    // do chroot()
    chdir("/ct6/");
    if (chroot("/ct6/") != 0) {
        perror("chroot /ct6/");
        return 1;
    }
    // check path path after chroot()
    char a_cwd[PATH_MAX];
    getcwd(a_cwd, sizeof(a_cwd));
    printf("Current dir after chroot(): %s\n", a_cwd);
    // point dr struct to the "root"
    struct dirent *de;
    DIR *dr = opendir("/");

    // run readdir() and list "root"'s content
    while ((de = readdir(dr)) != NULL)
        printf("%s\n", de->d_name);
    // try to open /etc/passwd from a "host" filesystem
    FILE *f;
    f = fopen("/etc/passwd", "r");
    if (f == NULL) {
        perror("/etc/passwd");
        return 1;
    } else {
        char buf[100];
        while (fgets(buf, sizeof(buf), f)) {
             printf("%s", buf);
        }
    }
    return 0;
}
