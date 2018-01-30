// copyright 2017 war10ck

#ifndef GDU_UNIX_HPP_
#define GDU_UNIX_HPP_

#include <unistd.h>
#include <execinfo.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/resource.h>

#include <cstring>
#include <cstdio>

namespace gdp {
namespace gdu {

inline int CreateDaemon() {
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    } else if (pid) {
        // parent terminates
        _exit(0);
    }

    // child 1 continues
    // become session leader
    if (setsid() < 0) {
        return -1;
    }

    signal(SIGHUP, SIG_IGN);
    pid = fork();
    if (pid < 0) {
        return -1;
    } else if (pid) {
        // child 1 terminates
        _exit(0);
    }
    // child 2 continues...

    // close off file descriptors
    for (auto i = 0; i < 64; i++)
        close(i);

    // redirect stdin, stdout, and stderr to /dev/null
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);

    return 0; 
}

inline bool CreatePidFile() {
    int fd = open(".pid", O_TRUNC | O_RDWR);
    if (fd == -1) {
        fd = open(".pid", O_CREAT | O_RDWR, 0644);
        if (fd == -1) {
            // create failed
            return false;
        }
        // create success
    }
    pid_t pid = getpid();
    char sz_pid[64];
    memset(sz_pid, 0, sizeof(sz_pid));
    sprintf(sz_pid, "%d", pid);

    write(fd, sz_pid, strlen(sz_pid));
    close(fd);
    return true;
}

inline bool SetRLimit() {
    struct rlimit limit;
    limit.rlim_cur = RLIM_INFINITY;
    limit.rlim_max = RLIM_INFINITY;

    if (setrlimit(RLIMIT_CORE, &limit) == -1) {
        return false;
    }

    struct rlimit limitF;
    limitF.rlim_cur = 65535;
    limitF.rlim_max = 65535;

    if (setrlimit(RLIMIT_NOFILE, &limitF) == -1) {
        // set failed
        return false;
    }

    return true;
}

}  // namespace gdu
}  // namespace gdp

#endif  // GDU_PROCESS_HPP_
