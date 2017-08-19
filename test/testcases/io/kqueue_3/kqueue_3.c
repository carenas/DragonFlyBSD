#include <sys/types.h>
#include <sys/time.h>
#include <sys/event.h>
#include <sysexits.h>

#include <err.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int
main()
{
    int kq;
    int n;
    int fd[2];
    struct kevent ev;
    struct timespec ts;
    char buf[8000];

    if (pipe(fd) == -1)
        err(EX_TEMPFAIL, "pipe");

    if (fcntl(fd[1], F_SETFL, O_NONBLOCK) == -1)
        err(EX_TEMPFAIL, "fcntl");

    while ((n = write(fd[1], buf, sizeof(buf))) == sizeof(buf))
        ;

    if ((kq = kqueue()) == -1)
        err(EX_TEMPFAIL, "kqueue");

    EV_SET(&ev, fd[1], EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, 0);

    n = kevent(kq, &ev, 1, NULL, 0, NULL);
    if (n == -1)
        err(EX_TEMPFAIL, "kevent1");

    read(fd[0], buf, sizeof(buf));

    ts.tv_sec = ts.tv_nsec = 0;
    n = kevent(kq, NULL, 0, &ev, 1, &ts);
    if (n == -1 || n == 0)
	err(EX_TEMPFAIL, "kevent2");

    exit(0);
}
