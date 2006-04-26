/*
 * System call hiders.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $DragonFly: src/sys/sys/syscall-hide.h,v 1.36 2006/04/26 17:17:57 dillon Exp $
 * created from DragonFly: src/sys/kern/syscalls.master,v 1.31 2006/03/24 06:45:04 dillon Exp 
 */

#ifdef COMPAT_43
#endif
HIDE_POSIX(fork)
HIDE_POSIX(read)
HIDE_POSIX(write)
HIDE_POSIX(open)
HIDE_POSIX(close)
HIDE_BSD(wait4)
HIDE_BSD(creat)
HIDE_POSIX(link)
HIDE_POSIX(unlink)
HIDE_POSIX(chdir)
HIDE_BSD(fchdir)
HIDE_POSIX(mknod)
HIDE_POSIX(chmod)
HIDE_POSIX(chown)
HIDE_BSD(obreak)
HIDE_BSD(getfsstat)
HIDE_POSIX(lseek)
HIDE_POSIX(getpid)
HIDE_BSD(mount)
HIDE_BSD(unmount)
HIDE_POSIX(setuid)
HIDE_POSIX(getuid)
HIDE_POSIX(geteuid)
HIDE_BSD(ptrace)
HIDE_BSD(recvmsg)
HIDE_BSD(sendmsg)
HIDE_BSD(recvfrom)
HIDE_BSD(accept)
HIDE_BSD(getpeername)
HIDE_BSD(getsockname)
HIDE_POSIX(access)
HIDE_BSD(chflags)
HIDE_BSD(fchflags)
HIDE_BSD(sync)
HIDE_POSIX(kill)
HIDE_POSIX(stat)
HIDE_POSIX(getppid)
HIDE_POSIX(lstat)
HIDE_POSIX(dup)
HIDE_POSIX(pipe)
HIDE_POSIX(getegid)
HIDE_BSD(profil)
HIDE_BSD(ktrace)
HIDE_POSIX(getgid)
HIDE_BSD(getlogin)
HIDE_BSD(setlogin)
HIDE_BSD(acct)
HIDE_BSD(sigaltstack)
HIDE_POSIX(ioctl)
HIDE_BSD(reboot)
HIDE_POSIX(revoke)
HIDE_POSIX(symlink)
HIDE_POSIX(readlink)
HIDE_POSIX(execve)
HIDE_POSIX(umask)
HIDE_BSD(chroot)
HIDE_POSIX(fstat)
HIDE_BSD(getkerninfo)
HIDE_BSD(getpagesize)
HIDE_BSD(msync)
HIDE_BSD(vfork)
HIDE_BSD(sbrk)
HIDE_BSD(sstk)
HIDE_BSD(mmap)
HIDE_BSD(ovadvise)
HIDE_BSD(munmap)
HIDE_BSD(mprotect)
HIDE_BSD(madvise)
HIDE_BSD(mincore)
HIDE_POSIX(getgroups)
HIDE_POSIX(setgroups)
HIDE_POSIX(getpgrp)
HIDE_POSIX(setpgid)
HIDE_BSD(setitimer)
HIDE_BSD(wait)
HIDE_BSD(swapon)
HIDE_BSD(getitimer)
HIDE_BSD(gethostname)
HIDE_BSD(sethostname)
HIDE_BSD(getdtablesize)
HIDE_POSIX(dup2)
HIDE_BSD(getdopt)
HIDE_POSIX(fcntl)
HIDE_BSD(select)
HIDE_BSD(setdopt)
HIDE_POSIX(fsync)
HIDE_BSD(setpriority)
HIDE_BSD(socket)
HIDE_BSD(connect)
HIDE_BSD(accept)
HIDE_BSD(getpriority)
HIDE_BSD(send)
HIDE_BSD(recv)
HIDE_BSD(bind)
HIDE_BSD(setsockopt)
HIDE_BSD(listen)
HIDE_BSD(sigvec)
HIDE_BSD(sigblock)
HIDE_BSD(sigsetmask)
HIDE_BSD(sigstack)
HIDE_BSD(recvmsg)
HIDE_BSD(sendmsg)
HIDE_BSD(gettimeofday)
HIDE_BSD(getrusage)
HIDE_BSD(getsockopt)
HIDE_BSD(readv)
HIDE_BSD(writev)
HIDE_BSD(settimeofday)
HIDE_BSD(fchown)
HIDE_BSD(fchmod)
HIDE_BSD(recvfrom)
HIDE_BSD(setreuid)
HIDE_BSD(setregid)
HIDE_POSIX(rename)
HIDE_BSD(truncate)
HIDE_BSD(ftruncate)
HIDE_BSD(flock)
HIDE_POSIX(mkfifo)
HIDE_BSD(sendto)
HIDE_BSD(shutdown)
HIDE_BSD(socketpair)
HIDE_POSIX(mkdir)
HIDE_POSIX(rmdir)
HIDE_BSD(utimes)
HIDE_BSD(adjtime)
HIDE_BSD(getpeername)
HIDE_BSD(gethostid)
HIDE_BSD(sethostid)
HIDE_BSD(getrlimit)
HIDE_BSD(setrlimit)
HIDE_BSD(killpg)
HIDE_POSIX(setsid)
HIDE_BSD(quotactl)
HIDE_BSD(quota)
HIDE_BSD(getsockname)
HIDE_BSD(nfssvc)
HIDE_BSD(getdirentries)
HIDE_BSD(statfs)
HIDE_BSD(fstatfs)
HIDE_BSD(getfh)
HIDE_BSD(getdomainname)
HIDE_BSD(setdomainname)
HIDE_BSD(uname)
HIDE_BSD(sysarch)
HIDE_BSD(rtprio)
HIDE_BSD(semsys)
HIDE_BSD(msgsys)
HIDE_BSD(shmsys)
HIDE_POSIX(pread)
HIDE_POSIX(pwrite)
HIDE_BSD(ntp_adjtime)
HIDE_POSIX(setgid)
HIDE_BSD(setegid)
HIDE_BSD(seteuid)
HIDE_BSD(lfs_bmapv)
HIDE_BSD(lfs_markv)
HIDE_BSD(lfs_segclean)
HIDE_BSD(lfs_segwait)
HIDE_POSIX(stat)
HIDE_POSIX(fstat)
HIDE_POSIX(lstat)
HIDE_POSIX(pathconf)
HIDE_POSIX(fpathconf)
HIDE_BSD(getrlimit)
HIDE_BSD(setrlimit)
HIDE_BSD(getdirentries)
HIDE_BSD(mmap)
HIDE_POSIX(lseek)
HIDE_BSD(truncate)
HIDE_BSD(ftruncate)
HIDE_BSD(__sysctl)
HIDE_BSD(mlock)
HIDE_BSD(munlock)
HIDE_BSD(undelete)
HIDE_BSD(futimes)
HIDE_BSD(getpgid)
HIDE_BSD(poll)
HIDE_BSD(__semctl)
HIDE_BSD(semget)
HIDE_BSD(semop)
HIDE_BSD(msgctl)
HIDE_BSD(msgget)
HIDE_BSD(msgsnd)
HIDE_BSD(msgrcv)
HIDE_BSD(shmat)
HIDE_BSD(shmctl)
HIDE_BSD(shmdt)
HIDE_BSD(shmget)
HIDE_POSIX(clock_gettime)
HIDE_POSIX(clock_settime)
HIDE_POSIX(clock_getres)
HIDE_POSIX(nanosleep)
HIDE_BSD(minherit)
HIDE_BSD(rfork)
HIDE_BSD(openbsd_poll)
HIDE_BSD(issetugid)
HIDE_BSD(lchown)
HIDE_BSD(getdents)
HIDE_BSD(lchmod)
HIDE_BSD(lchown)
HIDE_BSD(lutimes)
HIDE_BSD(msync)
HIDE_BSD({)
HIDE_BSD(preadv)
HIDE_BSD(pwritev)
HIDE_BSD(fhstatfs)
HIDE_BSD(fhopen)
HIDE_POSIX(fhstat)
HIDE_BSD(modnext)
HIDE_BSD(modstat)
HIDE_BSD(modfnext)
HIDE_BSD(modfind)
HIDE_BSD(kldload)
HIDE_BSD(kldunload)
HIDE_BSD(kldfind)
HIDE_BSD(kldnext)
HIDE_BSD(kldstat)
HIDE_BSD(kldfirstmod)
HIDE_BSD(getsid)
HIDE_BSD(setresuid)
HIDE_BSD(setresgid)
HIDE_BSD(aio_return)
HIDE_BSD(aio_suspend)
HIDE_BSD(aio_cancel)
HIDE_BSD(aio_error)
HIDE_BSD(aio_read)
HIDE_BSD(aio_write)
HIDE_BSD(lio_listio)
HIDE_BSD(yield)
HIDE_BSD(thr_sleep)
HIDE_BSD(thr_wakeup)
HIDE_BSD(mlockall)
HIDE_BSD(munlockall)
HIDE_BSD(__getcwd)
HIDE_POSIX(sched_setparam)
HIDE_POSIX(sched_getparam)
HIDE_POSIX(sched_setscheduler)
HIDE_POSIX(sched_getscheduler)
HIDE_POSIX(sched_yield)
HIDE_POSIX(sched_get_priority_max)
HIDE_POSIX(sched_get_priority_min)
HIDE_POSIX(sched_rr_get_interval)
HIDE_BSD(utrace)
HIDE_BSD(kldsym)
HIDE_BSD(jail)
HIDE_BSD(pioctl)
HIDE_POSIX(sigprocmask)
HIDE_POSIX(sigsuspend)
HIDE_POSIX(sigaction)
HIDE_POSIX(sigpending)
HIDE_BSD(sigreturn)
HIDE_POSIX(sigtimedwait)
HIDE_POSIX(sigwaitinfo)
HIDE_BSD(__acl_get_file)
HIDE_BSD(__acl_set_file)
HIDE_BSD(__acl_get_fd)
HIDE_BSD(__acl_set_fd)
HIDE_BSD(__acl_delete_file)
HIDE_BSD(__acl_delete_fd)
HIDE_BSD(__acl_aclcheck_file)
HIDE_BSD(__acl_aclcheck_fd)
HIDE_BSD(extattrctl)
HIDE_BSD(extattr_set_file)
HIDE_BSD(extattr_get_file)
HIDE_BSD(extattr_delete_file)
HIDE_BSD(aio_waitcomplete)
HIDE_BSD(getresuid)
HIDE_BSD(getresgid)
HIDE_BSD(kqueue)
HIDE_BSD(kevent)
HIDE_BSD(sctp_peeloff)
HIDE_BSD(sendfile)
HIDE_BSD(varsym_set)
HIDE_BSD(varsym_get)
HIDE_BSD(varsym_list)
HIDE_BSD(upc_register)
HIDE_BSD(upc_control)
HIDE_BSD(caps_sys_service)
HIDE_BSD(caps_sys_client)
HIDE_BSD(caps_sys_close)
HIDE_BSD(caps_sys_put)
HIDE_BSD(caps_sys_reply)
HIDE_BSD(caps_sys_get)
HIDE_BSD(caps_sys_wait)
HIDE_BSD(caps_sys_abort)
HIDE_BSD(caps_sys_getgen)
HIDE_BSD(caps_sys_setgen)
HIDE_BSD(exec_sys_register)
HIDE_BSD(exec_sys_unregister)
HIDE_BSD(sys_checkpoint)
HIDE_BSD(mountctl)
HIDE_BSD(umtx_sleep)
HIDE_BSD(umtx_wakeup)
HIDE_BSD(jail_attach)
HIDE_BSD(sys_set_tls_area)
HIDE_BSD(sys_get_tls_area)
HIDE_BSD(closefrom)
HIDE_POSIX(stat)
HIDE_POSIX(fstat)
HIDE_POSIX(lstat)
HIDE_BSD(fhstat)
HIDE_BSD(getdirentries)
HIDE_BSD(getdents)
HIDE_BSD(usched_set)
