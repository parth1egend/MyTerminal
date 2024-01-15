#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysctl.h>

int main() {
    struct kinfo_proc *proc_list = NULL;
    size_t proc_count = 0;
    int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0 };

    if (sysctl(mib, 4, NULL, &proc_count, NULL, 0) < 0) {
        printf("Error: Could not get process count.\n");
        exit(1);
    }

    proc_list = (struct kinfo_proc*)malloc(proc_count);
    if (proc_list == NULL) {
        printf("Error: Could not allocate memory.\n");
        exit(1);
    }

    if (sysctl(mib, 4, proc_list, &proc_count, NULL, 0) < 0) {
        printf("Error: Could not get process list.\n");
        exit(1);
    }

    printf("%5s %5s %5s %s\n", "PID", "PPID", "UID", "COMMAND");
    for (int i = 0; i < (int)(proc_count / sizeof(struct kinfo_proc)); i++) {
        printf("%5d %5d %5d %s\n", proc_list[i].kp_proc.p_pid,
               proc_list[i].kp_eproc.e_ppid, proc_list[i].kp_eproc.e_ucred.cr_uid,
               proc_list[i].kp_proc.p_comm);
    }

    free(proc_list);
    return 0;
}
