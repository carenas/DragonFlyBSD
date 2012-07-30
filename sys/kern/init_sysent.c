/*
 * System call switch table.
 *
 * DO NOT EDIT-- this file is automatically generated.
 */

#include "opt_compat.h"

#include "opt_compatdf12.h"

#include <sys/param.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>
#include <sys/statvfs.h>
#include <emulation/43bsd/stat.h>
#include <emulation/dragonfly12/stat.h>

#define AS(name) ((sizeof(struct name) - sizeof(struct sysmsg)) / sizeof(register_t))

#ifdef COMPAT_43
#define compat(n, name) n, (sy_call_t *)__CONCAT(sys_,__CONCAT(o,name))
#else
#define compat(n, name) 0, (sy_call_t *)sys_nosys
#endif

#ifdef COMPAT_DF12
#define compatdf12(n, name) n, (sy_call_t *)__CONCAT(sys_,__CONCAT(dfbsd12_,name))
#else
#define compatdf12(n, name) 0, (sy_call_t *)sys_nosys
#endif

/* The casts are bogus but will do for now. */
struct sysent sysent[] = {
#ifdef COMPAT_43
#endif
	{ 0, (sy_call_t *)sys_nosys },			/* 0 = syscall */
	{ AS(exit_args), (sy_call_t *)sys_exit },	/* 1 = exit */
	{ 0, (sy_call_t *)sys_fork },			/* 2 = fork */
	{ AS(read_args), (sy_call_t *)sys_read },	/* 3 = read */
	{ AS(write_args), (sy_call_t *)sys_write },	/* 4 = write */
	{ AS(open_args), (sy_call_t *)sys_open },	/* 5 = open */
	{ AS(close_args), (sy_call_t *)sys_close },	/* 6 = close */
	{ AS(wait_args), (sy_call_t *)sys_wait4 },	/* 7 = wait4 */
	{ compat(AS(ocreat_args),creat) },		/* 8 = old creat */
	{ AS(link_args), (sy_call_t *)sys_link },	/* 9 = link */
	{ AS(unlink_args), (sy_call_t *)sys_unlink },	/* 10 = unlink */
	{ 0, (sy_call_t *)sys_nosys },			/* 11 = obsolete execv */
	{ AS(chdir_args), (sy_call_t *)sys_chdir },	/* 12 = chdir */
	{ AS(fchdir_args), (sy_call_t *)sys_fchdir },	/* 13 = fchdir */
	{ AS(mknod_args), (sy_call_t *)sys_mknod },	/* 14 = mknod */
	{ AS(chmod_args), (sy_call_t *)sys_chmod },	/* 15 = chmod */
	{ AS(chown_args), (sy_call_t *)sys_chown },	/* 16 = chown */
	{ AS(obreak_args), (sy_call_t *)sys_obreak },	/* 17 = break */
	{ AS(getfsstat_args), (sy_call_t *)sys_getfsstat },	/* 18 = getfsstat */
	{ compat(AS(olseek_args),lseek) },		/* 19 = old lseek */
	{ 0, (sy_call_t *)sys_getpid },			/* 20 = getpid */
	{ AS(mount_args), (sy_call_t *)sys_mount },	/* 21 = mount */
	{ AS(unmount_args), (sy_call_t *)sys_unmount },	/* 22 = unmount */
	{ AS(setuid_args), (sy_call_t *)sys_setuid },	/* 23 = setuid */
	{ 0, (sy_call_t *)sys_getuid },			/* 24 = getuid */
	{ 0, (sy_call_t *)sys_geteuid },		/* 25 = geteuid */
	{ AS(ptrace_args), (sy_call_t *)sys_ptrace },	/* 26 = ptrace */
	{ AS(recvmsg_args), (sy_call_t *)sys_recvmsg },	/* 27 = recvmsg */
	{ AS(sendmsg_args), (sy_call_t *)sys_sendmsg },	/* 28 = sendmsg */
	{ AS(recvfrom_args), (sy_call_t *)sys_recvfrom },	/* 29 = recvfrom */
	{ AS(accept_args), (sy_call_t *)sys_accept },	/* 30 = accept */
	{ AS(getpeername_args), (sy_call_t *)sys_getpeername },	/* 31 = getpeername */
	{ AS(getsockname_args), (sy_call_t *)sys_getsockname },	/* 32 = getsockname */
	{ AS(access_args), (sy_call_t *)sys_access },	/* 33 = access */
	{ AS(chflags_args), (sy_call_t *)sys_chflags },	/* 34 = chflags */
	{ AS(fchflags_args), (sy_call_t *)sys_fchflags },	/* 35 = fchflags */
	{ 0, (sy_call_t *)sys_sync },			/* 36 = sync */
	{ AS(kill_args), (sy_call_t *)sys_kill },	/* 37 = kill */
	{ compat(AS(ostat_args),stat) },		/* 38 = old stat */
	{ 0, (sy_call_t *)sys_getppid },		/* 39 = getppid */
	{ compat(AS(olstat_args),lstat) },		/* 40 = old lstat */
	{ AS(dup_args), (sy_call_t *)sys_dup },		/* 41 = dup */
	{ 0, (sy_call_t *)sys_pipe },			/* 42 = pipe */
	{ 0, (sy_call_t *)sys_getegid },		/* 43 = getegid */
	{ AS(profil_args), (sy_call_t *)sys_profil },	/* 44 = profil */
	{ AS(ktrace_args), (sy_call_t *)sys_ktrace },	/* 45 = ktrace */
	{ 0, (sy_call_t *)sys_nosys },			/* 46 = obsolete freebsd3_sigaction */
	{ 0, (sy_call_t *)sys_getgid },			/* 47 = getgid */
	{ 0, (sy_call_t *)sys_nosys },			/* 48 = obsolete freebsd3_sigprocmask */
	{ AS(getlogin_args), (sy_call_t *)sys_getlogin },	/* 49 = getlogin */
	{ AS(setlogin_args), (sy_call_t *)sys_setlogin },	/* 50 = setlogin */
	{ AS(acct_args), (sy_call_t *)sys_acct },	/* 51 = acct */
	{ 0, (sy_call_t *)sys_nosys },			/* 52 = obsolete freebsd3_sigpending */
	{ AS(sigaltstack_args), (sy_call_t *)sys_sigaltstack },	/* 53 = sigaltstack */
	{ AS(ioctl_args), (sy_call_t *)sys_ioctl },	/* 54 = ioctl */
	{ AS(reboot_args), (sy_call_t *)sys_reboot },	/* 55 = reboot */
	{ AS(revoke_args), (sy_call_t *)sys_revoke },	/* 56 = revoke */
	{ AS(symlink_args), (sy_call_t *)sys_symlink },	/* 57 = symlink */
	{ AS(readlink_args), (sy_call_t *)sys_readlink },	/* 58 = readlink */
	{ AS(execve_args), (sy_call_t *)sys_execve },	/* 59 = execve */
	{ AS(umask_args), (sy_call_t *)sys_umask },	/* 60 = umask */
	{ AS(chroot_args), (sy_call_t *)sys_chroot },	/* 61 = chroot */
	{ compat(AS(ofstat_args),fstat) },		/* 62 = old fstat */
	{ compat(AS(getkerninfo_args),getkerninfo) },	/* 63 = old getkerninfo */
	{ compat(0,getpagesize) },			/* 64 = old getpagesize */
	{ AS(msync_args), (sy_call_t *)sys_msync },	/* 65 = msync */
	{ 0, (sy_call_t *)sys_vfork },			/* 66 = vfork */
	{ 0, (sy_call_t *)sys_nosys },			/* 67 = obsolete vread */
	{ 0, (sy_call_t *)sys_nosys },			/* 68 = obsolete vwrite */
	{ AS(sbrk_args), (sy_call_t *)sys_sbrk },	/* 69 = sbrk */
	{ AS(sstk_args), (sy_call_t *)sys_sstk },	/* 70 = sstk */
	{ compat(AS(ommap_args),mmap) },		/* 71 = old mmap */
	{ compat(AS(ovadvise_args),vadvise) },		/* 72 = old vadvise */
	{ AS(munmap_args), (sy_call_t *)sys_munmap },	/* 73 = munmap */
	{ AS(mprotect_args), (sy_call_t *)sys_mprotect },	/* 74 = mprotect */
	{ AS(madvise_args), (sy_call_t *)sys_madvise },	/* 75 = madvise */
	{ 0, (sy_call_t *)sys_nosys },			/* 76 = obsolete vhangup */
	{ 0, (sy_call_t *)sys_nosys },			/* 77 = obsolete vlimit */
	{ AS(mincore_args), (sy_call_t *)sys_mincore },	/* 78 = mincore */
	{ AS(getgroups_args), (sy_call_t *)sys_getgroups },	/* 79 = getgroups */
	{ AS(setgroups_args), (sy_call_t *)sys_setgroups },	/* 80 = setgroups */
	{ 0, (sy_call_t *)sys_getpgrp },		/* 81 = getpgrp */
	{ AS(setpgid_args), (sy_call_t *)sys_setpgid },	/* 82 = setpgid */
	{ AS(setitimer_args), (sy_call_t *)sys_setitimer },	/* 83 = setitimer */
	{ compat(0,wait) },				/* 84 = old wait */
	{ AS(swapon_args), (sy_call_t *)sys_swapon },	/* 85 = swapon */
	{ AS(getitimer_args), (sy_call_t *)sys_getitimer },	/* 86 = getitimer */
	{ compat(AS(gethostname_args),gethostname) },	/* 87 = old gethostname */
	{ compat(AS(sethostname_args),sethostname) },	/* 88 = old sethostname */
	{ 0, (sy_call_t *)sys_getdtablesize },		/* 89 = getdtablesize */
	{ AS(dup2_args), (sy_call_t *)sys_dup2 },	/* 90 = dup2 */
	{ 0, (sy_call_t *)sys_nosys },			/* 91 = getdopt */
	{ AS(fcntl_args), (sy_call_t *)sys_fcntl },	/* 92 = fcntl */
	{ AS(select_args), (sy_call_t *)sys_select },	/* 93 = select */
	{ 0, (sy_call_t *)sys_nosys },			/* 94 = setdopt */
	{ AS(fsync_args), (sy_call_t *)sys_fsync },	/* 95 = fsync */
	{ AS(setpriority_args), (sy_call_t *)sys_setpriority },	/* 96 = setpriority */
	{ AS(socket_args), (sy_call_t *)sys_socket },	/* 97 = socket */
	{ AS(connect_args), (sy_call_t *)sys_connect },	/* 98 = connect */
	{ compat(AS(accept_args),accept) },		/* 99 = old accept */
	{ AS(getpriority_args), (sy_call_t *)sys_getpriority },	/* 100 = getpriority */
	{ compat(AS(osend_args),send) },		/* 101 = old send */
	{ compat(AS(orecv_args),recv) },		/* 102 = old recv */
	{ 0, (sy_call_t *)sys_nosys },			/* 103 = obsolete freebsd3_sigreturn */
	{ AS(bind_args), (sy_call_t *)sys_bind },	/* 104 = bind */
	{ AS(setsockopt_args), (sy_call_t *)sys_setsockopt },	/* 105 = setsockopt */
	{ AS(listen_args), (sy_call_t *)sys_listen },	/* 106 = listen */
	{ 0, (sy_call_t *)sys_nosys },			/* 107 = obsolete vtimes */
	{ compat(AS(osigvec_args),sigvec) },		/* 108 = old sigvec */
	{ compat(AS(osigblock_args),sigblock) },	/* 109 = old sigblock */
	{ compat(AS(osigsetmask_args),sigsetmask) },	/* 110 = old sigsetmask */
	{ 0, (sy_call_t *)sys_nosys },			/* 111 = obsolete freebsd3_sigsuspend */
	{ compat(AS(osigstack_args),sigstack) },	/* 112 = old sigstack */
	{ compat(AS(orecvmsg_args),recvmsg) },		/* 113 = old recvmsg */
	{ compat(AS(osendmsg_args),sendmsg) },		/* 114 = old sendmsg */
	{ 0, (sy_call_t *)sys_nosys },			/* 115 = obsolete vtrace */
	{ AS(gettimeofday_args), (sy_call_t *)sys_gettimeofday },	/* 116 = gettimeofday */
	{ AS(getrusage_args), (sy_call_t *)sys_getrusage },	/* 117 = getrusage */
	{ AS(getsockopt_args), (sy_call_t *)sys_getsockopt },	/* 118 = getsockopt */
	{ 0, (sy_call_t *)sys_nosys },			/* 119 = resuba */
	{ AS(readv_args), (sy_call_t *)sys_readv },	/* 120 = readv */
	{ AS(writev_args), (sy_call_t *)sys_writev },	/* 121 = writev */
	{ AS(settimeofday_args), (sy_call_t *)sys_settimeofday },	/* 122 = settimeofday */
	{ AS(fchown_args), (sy_call_t *)sys_fchown },	/* 123 = fchown */
	{ AS(fchmod_args), (sy_call_t *)sys_fchmod },	/* 124 = fchmod */
	{ compat(AS(recvfrom_args),recvfrom) },		/* 125 = old recvfrom */
	{ AS(setreuid_args), (sy_call_t *)sys_setreuid },	/* 126 = setreuid */
	{ AS(setregid_args), (sy_call_t *)sys_setregid },	/* 127 = setregid */
	{ AS(rename_args), (sy_call_t *)sys_rename },	/* 128 = rename */
	{ compat(AS(otruncate_args),truncate) },	/* 129 = old truncate */
	{ compat(AS(oftruncate_args),ftruncate) },	/* 130 = old ftruncate */
	{ AS(flock_args), (sy_call_t *)sys_flock },	/* 131 = flock */
	{ AS(mkfifo_args), (sy_call_t *)sys_mkfifo },	/* 132 = mkfifo */
	{ AS(sendto_args), (sy_call_t *)sys_sendto },	/* 133 = sendto */
	{ AS(shutdown_args), (sy_call_t *)sys_shutdown },	/* 134 = shutdown */
	{ AS(socketpair_args), (sy_call_t *)sys_socketpair },	/* 135 = socketpair */
	{ AS(mkdir_args), (sy_call_t *)sys_mkdir },	/* 136 = mkdir */
	{ AS(rmdir_args), (sy_call_t *)sys_rmdir },	/* 137 = rmdir */
	{ AS(utimes_args), (sy_call_t *)sys_utimes },	/* 138 = utimes */
	{ 0, (sy_call_t *)sys_nosys },			/* 139 = obsolete 4.2 sigreturn */
	{ AS(adjtime_args), (sy_call_t *)sys_adjtime },	/* 140 = adjtime */
	{ compat(AS(ogetpeername_args),getpeername) },	/* 141 = old getpeername */
	{ compat(0,gethostid) },			/* 142 = old gethostid */
	{ compat(AS(osethostid_args),sethostid) },	/* 143 = old sethostid */
	{ compat(AS(ogetrlimit_args),getrlimit) },	/* 144 = old getrlimit */
	{ compat(AS(osetrlimit_args),setrlimit) },	/* 145 = old setrlimit */
	{ compat(AS(okillpg_args),killpg) },		/* 146 = old killpg */
	{ 0, (sy_call_t *)sys_setsid },			/* 147 = setsid */
	{ AS(quotactl_args), (sy_call_t *)sys_quotactl },	/* 148 = quotactl */
	{ compat(0,quota) },				/* 149 = old quota */
	{ compat(AS(getsockname_args),getsockname) },	/* 150 = old getsockname */
	{ 0, (sy_call_t *)sys_nosys },			/* 151 = sem_lock */
	{ 0, (sy_call_t *)sys_nosys },			/* 152 = sem_wakeup */
	{ 0, (sy_call_t *)sys_nosys },			/* 153 = asyncdaemon */
	{ 0, (sy_call_t *)sys_nosys },			/* 154 = nosys */
	{ AS(nfssvc_args), (sy_call_t *)sys_nosys },	/* 155 = nfssvc */
	{ compat(AS(ogetdirentries_args),getdirentries) },	/* 156 = old getdirentries */
	{ AS(statfs_args), (sy_call_t *)sys_statfs },	/* 157 = statfs */
	{ AS(fstatfs_args), (sy_call_t *)sys_fstatfs },	/* 158 = fstatfs */
	{ 0, (sy_call_t *)sys_nosys },			/* 159 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 160 = nosys */
	{ AS(getfh_args), (sy_call_t *)sys_getfh },	/* 161 = getfh */
	{ AS(getdomainname_args), (sy_call_t *)sys_getdomainname },	/* 162 = getdomainname */
	{ AS(setdomainname_args), (sy_call_t *)sys_setdomainname },	/* 163 = setdomainname */
	{ AS(uname_args), (sy_call_t *)sys_uname },	/* 164 = uname */
	{ AS(sysarch_args), (sy_call_t *)sys_sysarch },	/* 165 = sysarch */
	{ AS(rtprio_args), (sy_call_t *)sys_rtprio },	/* 166 = rtprio */
	{ 0, (sy_call_t *)sys_nosys },			/* 167 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 168 = nosys */
	{ AS(semsys_args), (sy_call_t *)sys_semsys },	/* 169 = semsys */
	{ AS(msgsys_args), (sy_call_t *)sys_msgsys },	/* 170 = msgsys */
	{ AS(shmsys_args), (sy_call_t *)sys_shmsys },	/* 171 = shmsys */
	{ 0, (sy_call_t *)sys_nosys },			/* 172 = nosys */
	{ AS(extpread_args), (sy_call_t *)sys_extpread },	/* 173 = extpread */
	{ AS(extpwrite_args), (sy_call_t *)sys_extpwrite },	/* 174 = extpwrite */
	{ 0, (sy_call_t *)sys_nosys },			/* 175 = nosys */
	{ AS(ntp_adjtime_args), (sy_call_t *)sys_ntp_adjtime },	/* 176 = ntp_adjtime */
	{ 0, (sy_call_t *)sys_nosys },			/* 177 = sfork */
	{ 0, (sy_call_t *)sys_nosys },			/* 178 = getdescriptor */
	{ 0, (sy_call_t *)sys_nosys },			/* 179 = setdescriptor */
	{ 0, (sy_call_t *)sys_nosys },			/* 180 = nosys */
	{ AS(setgid_args), (sy_call_t *)sys_setgid },	/* 181 = setgid */
	{ AS(setegid_args), (sy_call_t *)sys_setegid },	/* 182 = setegid */
	{ AS(seteuid_args), (sy_call_t *)sys_seteuid },	/* 183 = seteuid */
	{ 0, (sy_call_t *)sys_nosys },			/* 184 = lfs_bmapv */
	{ 0, (sy_call_t *)sys_nosys },			/* 185 = lfs_markv */
	{ 0, (sy_call_t *)sys_nosys },			/* 186 = lfs_segclean */
	{ 0, (sy_call_t *)sys_nosys },			/* 187 = lfs_segwait */
	{ compatdf12(AS(dfbsd12_stat_args),stat) },		/* 188 = old stat */
	{ compatdf12(AS(dfbsd12_fstat_args),fstat) },	/* 189 = old fstat */
	{ compatdf12(AS(dfbsd12_lstat_args),lstat) },	/* 190 = old lstat */
	{ AS(pathconf_args), (sy_call_t *)sys_pathconf },	/* 191 = pathconf */
	{ AS(fpathconf_args), (sy_call_t *)sys_fpathconf },	/* 192 = fpathconf */
	{ 0, (sy_call_t *)sys_nosys },			/* 193 = nosys */
	{ AS(__getrlimit_args), (sy_call_t *)sys_getrlimit },	/* 194 = getrlimit */
	{ AS(__setrlimit_args), (sy_call_t *)sys_setrlimit },	/* 195 = setrlimit */
	{ compatdf12(AS(dfbsd12_getdirentries_args),getdirentries) },	/* 196 = old getdirentries */
	{ AS(mmap_args), (sy_call_t *)sys_mmap },	/* 197 = mmap */
	{ 0, (sy_call_t *)sys_nosys },			/* 198 = __syscall */
	{ AS(lseek_args), (sy_call_t *)sys_lseek },	/* 199 = lseek */
	{ AS(truncate_args), (sy_call_t *)sys_truncate },	/* 200 = truncate */
	{ AS(ftruncate_args), (sy_call_t *)sys_ftruncate },	/* 201 = ftruncate */
	{ AS(sysctl_args), (sy_call_t *)sys___sysctl },	/* 202 = __sysctl */
	{ AS(mlock_args), (sy_call_t *)sys_mlock },	/* 203 = mlock */
	{ AS(munlock_args), (sy_call_t *)sys_munlock },	/* 204 = munlock */
	{ AS(undelete_args), (sy_call_t *)sys_undelete },	/* 205 = undelete */
	{ AS(futimes_args), (sy_call_t *)sys_futimes },	/* 206 = futimes */
	{ AS(getpgid_args), (sy_call_t *)sys_getpgid },	/* 207 = getpgid */
	{ 0, (sy_call_t *)sys_nosys },			/* 208 = newreboot */
	{ AS(poll_args), (sy_call_t *)sys_poll },	/* 209 = poll */
	{ AS(nosys_args), (sy_call_t *)sys_lkmnosys },	/* 210 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)sys_lkmnosys },	/* 211 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)sys_lkmnosys },	/* 212 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)sys_lkmnosys },	/* 213 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)sys_lkmnosys },	/* 214 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)sys_lkmnosys },	/* 215 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)sys_lkmnosys },	/* 216 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)sys_lkmnosys },	/* 217 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)sys_lkmnosys },	/* 218 = lkmnosys */
	{ AS(nosys_args), (sy_call_t *)sys_lkmnosys },	/* 219 = lkmnosys */
	{ AS(__semctl_args), (sy_call_t *)sys___semctl },	/* 220 = __semctl */
	{ AS(semget_args), (sy_call_t *)sys_semget },	/* 221 = semget */
	{ AS(semop_args), (sy_call_t *)sys_semop },	/* 222 = semop */
	{ 0, (sy_call_t *)sys_nosys },			/* 223 = semconfig */
	{ AS(msgctl_args), (sy_call_t *)sys_msgctl },	/* 224 = msgctl */
	{ AS(msgget_args), (sy_call_t *)sys_msgget },	/* 225 = msgget */
	{ AS(msgsnd_args), (sy_call_t *)sys_msgsnd },	/* 226 = msgsnd */
	{ AS(msgrcv_args), (sy_call_t *)sys_msgrcv },	/* 227 = msgrcv */
	{ AS(shmat_args), (sy_call_t *)sys_shmat },	/* 228 = shmat */
	{ AS(shmctl_args), (sy_call_t *)sys_shmctl },	/* 229 = shmctl */
	{ AS(shmdt_args), (sy_call_t *)sys_shmdt },	/* 230 = shmdt */
	{ AS(shmget_args), (sy_call_t *)sys_shmget },	/* 231 = shmget */
	{ AS(clock_gettime_args), (sy_call_t *)sys_clock_gettime },	/* 232 = clock_gettime */
	{ AS(clock_settime_args), (sy_call_t *)sys_clock_settime },	/* 233 = clock_settime */
	{ AS(clock_getres_args), (sy_call_t *)sys_clock_getres },	/* 234 = clock_getres */
	{ 0, (sy_call_t *)sys_nosys },			/* 235 = timer_create */
	{ 0, (sy_call_t *)sys_nosys },			/* 236 = timer_delete */
	{ 0, (sy_call_t *)sys_nosys },			/* 237 = timer_settime */
	{ 0, (sy_call_t *)sys_nosys },			/* 238 = timer_gettime */
	{ 0, (sy_call_t *)sys_nosys },			/* 239 = timer_getoverrun */
	{ AS(nanosleep_args), (sy_call_t *)sys_nanosleep },	/* 240 = nanosleep */
	{ 0, (sy_call_t *)sys_nosys },			/* 241 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 242 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 243 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 244 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 245 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 246 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 247 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 248 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 249 = nosys */
	{ AS(minherit_args), (sy_call_t *)sys_minherit },	/* 250 = minherit */
	{ AS(rfork_args), (sy_call_t *)sys_rfork },	/* 251 = rfork */
	{ AS(openbsd_poll_args), (sy_call_t *)sys_openbsd_poll },	/* 252 = openbsd_poll */
	{ 0, (sy_call_t *)sys_issetugid },		/* 253 = issetugid */
	{ AS(lchown_args), (sy_call_t *)sys_lchown },	/* 254 = lchown */
	{ 0, (sy_call_t *)sys_nosys },			/* 255 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 256 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 257 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 258 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 259 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 260 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 261 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 262 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 263 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 264 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 265 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 266 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 267 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 268 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 269 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 270 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 271 = nosys */
	{ compatdf12(AS(dfbsd12_getdents_args),getdents) },	/* 272 = old getdents */
	{ 0, (sy_call_t *)sys_nosys },			/* 273 = nosys */
	{ AS(lchmod_args), (sy_call_t *)sys_lchmod },	/* 274 = lchmod */
	{ AS(lchown_args), (sy_call_t *)sys_lchown },	/* 275 = netbsd_lchown */
	{ AS(lutimes_args), (sy_call_t *)sys_lutimes },	/* 276 = lutimes */
	{ AS(msync_args), (sy_call_t *)sys_msync },	/* 277 = netbsd_msync */
	{ 0, (sy_call_t *)sys_nosys },			/* 278 = obsolete { */
	{ 0, (sy_call_t *)sys_nosys },			/* 279 = obsolete { */
	{ 0, (sy_call_t *)sys_nosys },			/* 280 = obsolete { */
	{ 0, (sy_call_t *)sys_nosys },			/* 281 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 282 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 283 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 284 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 285 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 286 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 287 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 288 = nosys */
	{ AS(extpreadv_args), (sy_call_t *)sys_extpreadv },	/* 289 = extpreadv */
	{ AS(extpwritev_args), (sy_call_t *)sys_extpwritev },	/* 290 = extpwritev */
	{ 0, (sy_call_t *)sys_nosys },			/* 291 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 292 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 293 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 294 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 295 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 296 = nosys */
	{ AS(fhstatfs_args), (sy_call_t *)sys_fhstatfs },	/* 297 = fhstatfs */
	{ AS(fhopen_args), (sy_call_t *)sys_fhopen },	/* 298 = fhopen */
	{ compatdf12(AS(dfbsd12_fhstat_args),fhstat) },	/* 299 = old fhstat */
	{ AS(modnext_args), (sy_call_t *)sys_modnext },	/* 300 = modnext */
	{ AS(modstat_args), (sy_call_t *)sys_modstat },	/* 301 = modstat */
	{ AS(modfnext_args), (sy_call_t *)sys_modfnext },	/* 302 = modfnext */
	{ AS(modfind_args), (sy_call_t *)sys_modfind },	/* 303 = modfind */
	{ AS(kldload_args), (sy_call_t *)sys_kldload },	/* 304 = kldload */
	{ AS(kldunload_args), (sy_call_t *)sys_kldunload },	/* 305 = kldunload */
	{ AS(kldfind_args), (sy_call_t *)sys_kldfind },	/* 306 = kldfind */
	{ AS(kldnext_args), (sy_call_t *)sys_kldnext },	/* 307 = kldnext */
	{ AS(kldstat_args), (sy_call_t *)sys_kldstat },	/* 308 = kldstat */
	{ AS(kldfirstmod_args), (sy_call_t *)sys_kldfirstmod },	/* 309 = kldfirstmod */
	{ AS(getsid_args), (sy_call_t *)sys_getsid },	/* 310 = getsid */
	{ AS(setresuid_args), (sy_call_t *)sys_setresuid },	/* 311 = setresuid */
	{ AS(setresgid_args), (sy_call_t *)sys_setresgid },	/* 312 = setresgid */
	{ 0, (sy_call_t *)sys_nosys },			/* 313 = obsolete signanosleep */
	{ AS(aio_return_args), (sy_call_t *)sys_aio_return },	/* 314 = aio_return */
	{ AS(aio_suspend_args), (sy_call_t *)sys_aio_suspend },	/* 315 = aio_suspend */
	{ AS(aio_cancel_args), (sy_call_t *)sys_aio_cancel },	/* 316 = aio_cancel */
	{ AS(aio_error_args), (sy_call_t *)sys_aio_error },	/* 317 = aio_error */
	{ AS(aio_read_args), (sy_call_t *)sys_aio_read },	/* 318 = aio_read */
	{ AS(aio_write_args), (sy_call_t *)sys_aio_write },	/* 319 = aio_write */
	{ AS(lio_listio_args), (sy_call_t *)sys_lio_listio },	/* 320 = lio_listio */
	{ 0, (sy_call_t *)sys_yield },			/* 321 = yield */
	{ 0, (sy_call_t *)sys_nosys },			/* 322 = thr_sleep */
	{ 0, (sy_call_t *)sys_nosys },			/* 323 = thr_wakeup */
	{ AS(mlockall_args), (sy_call_t *)sys_mlockall },	/* 324 = mlockall */
	{ 0, (sy_call_t *)sys_munlockall },		/* 325 = munlockall */
	{ AS(__getcwd_args), (sy_call_t *)sys___getcwd },	/* 326 = __getcwd */
	{ AS(sched_setparam_args), (sy_call_t *)sys_sched_setparam },	/* 327 = sched_setparam */
	{ AS(sched_getparam_args), (sy_call_t *)sys_sched_getparam },	/* 328 = sched_getparam */
	{ AS(sched_setscheduler_args), (sy_call_t *)sys_sched_setscheduler },	/* 329 = sched_setscheduler */
	{ AS(sched_getscheduler_args), (sy_call_t *)sys_sched_getscheduler },	/* 330 = sched_getscheduler */
	{ 0, (sy_call_t *)sys_sched_yield },		/* 331 = sched_yield */
	{ AS(sched_get_priority_max_args), (sy_call_t *)sys_sched_get_priority_max },	/* 332 = sched_get_priority_max */
	{ AS(sched_get_priority_min_args), (sy_call_t *)sys_sched_get_priority_min },	/* 333 = sched_get_priority_min */
	{ AS(sched_rr_get_interval_args), (sy_call_t *)sys_sched_rr_get_interval },	/* 334 = sched_rr_get_interval */
	{ AS(utrace_args), (sy_call_t *)sys_utrace },	/* 335 = utrace */
	{ 0, (sy_call_t *)sys_nosys },			/* 336 = obsolete freebsd4_sendfile */
	{ AS(kldsym_args), (sy_call_t *)sys_kldsym },	/* 337 = kldsym */
	{ AS(jail_args), (sy_call_t *)sys_jail },	/* 338 = jail */
	{ 0, (sy_call_t *)sys_nosys },			/* 339 = pioctl */
	{ AS(sigprocmask_args), (sy_call_t *)sys_sigprocmask },	/* 340 = sigprocmask */
	{ AS(sigsuspend_args), (sy_call_t *)sys_sigsuspend },	/* 341 = sigsuspend */
	{ AS(sigaction_args), (sy_call_t *)sys_sigaction },	/* 342 = sigaction */
	{ AS(sigpending_args), (sy_call_t *)sys_sigpending },	/* 343 = sigpending */
	{ AS(sigreturn_args), (sy_call_t *)sys_sigreturn },	/* 344 = sigreturn */
	{ AS(sigtimedwait_args), (sy_call_t *)sys_sigtimedwait },	/* 345 = sigtimedwait */
	{ AS(sigwaitinfo_args), (sy_call_t *)sys_sigwaitinfo },	/* 346 = sigwaitinfo */
	{ AS(__acl_get_file_args), (sy_call_t *)sys___acl_get_file },	/* 347 = __acl_get_file */
	{ AS(__acl_set_file_args), (sy_call_t *)sys___acl_set_file },	/* 348 = __acl_set_file */
	{ AS(__acl_get_fd_args), (sy_call_t *)sys___acl_get_fd },	/* 349 = __acl_get_fd */
	{ AS(__acl_set_fd_args), (sy_call_t *)sys___acl_set_fd },	/* 350 = __acl_set_fd */
	{ AS(__acl_delete_file_args), (sy_call_t *)sys___acl_delete_file },	/* 351 = __acl_delete_file */
	{ AS(__acl_delete_fd_args), (sy_call_t *)sys___acl_delete_fd },	/* 352 = __acl_delete_fd */
	{ AS(__acl_aclcheck_file_args), (sy_call_t *)sys___acl_aclcheck_file },	/* 353 = __acl_aclcheck_file */
	{ AS(__acl_aclcheck_fd_args), (sy_call_t *)sys___acl_aclcheck_fd },	/* 354 = __acl_aclcheck_fd */
	{ AS(extattrctl_args), (sy_call_t *)sys_extattrctl },	/* 355 = extattrctl */
	{ AS(extattr_set_file_args), (sy_call_t *)sys_extattr_set_file },	/* 356 = extattr_set_file */
	{ AS(extattr_get_file_args), (sy_call_t *)sys_extattr_get_file },	/* 357 = extattr_get_file */
	{ AS(extattr_delete_file_args), (sy_call_t *)sys_extattr_delete_file },	/* 358 = extattr_delete_file */
	{ AS(aio_waitcomplete_args), (sy_call_t *)sys_aio_waitcomplete },	/* 359 = aio_waitcomplete */
	{ AS(getresuid_args), (sy_call_t *)sys_getresuid },	/* 360 = getresuid */
	{ AS(getresgid_args), (sy_call_t *)sys_getresgid },	/* 361 = getresgid */
	{ 0, (sy_call_t *)sys_kqueue },			/* 362 = kqueue */
	{ AS(kevent_args), (sy_call_t *)sys_kevent },	/* 363 = kevent */
	{ AS(sctp_peeloff_args), (sy_call_t *)sys_sctp_peeloff },	/* 364 = sctp_peeloff */
	{ 0, (sy_call_t *)sys_nosys },			/* 365 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 366 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 367 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 368 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 369 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 370 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 371 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 372 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 373 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 374 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 375 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 376 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 377 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 378 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 379 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 380 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 381 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 382 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 383 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 384 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 385 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 386 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 387 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 388 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 389 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 390 = nosys */
	{ AS(lchflags_args), (sy_call_t *)sys_lchflags },	/* 391 = lchflags */
	{ AS(uuidgen_args), (sy_call_t *)sys_uuidgen },	/* 392 = uuidgen */
	{ AS(sendfile_args), (sy_call_t *)sys_sendfile },	/* 393 = sendfile */
	{ 0, (sy_call_t *)sys_nosys },			/* 394 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 395 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 396 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 397 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 398 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 399 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 400 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 401 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 402 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 403 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 404 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 405 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 406 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 407 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 408 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 409 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 410 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 411 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 412 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 413 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 414 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 415 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 416 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 417 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 418 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 419 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 420 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 421 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 422 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 423 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 424 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 425 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 426 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 427 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 428 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 429 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 430 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 431 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 432 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 433 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 434 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 435 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 436 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 437 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 438 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 439 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 440 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 441 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 442 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 443 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 444 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 445 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 446 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 447 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 448 = nosys */
	{ 0, (sy_call_t *)sys_nosys },			/* 449 = nosys */
	{ AS(varsym_set_args), (sy_call_t *)sys_varsym_set },	/* 450 = varsym_set */
	{ AS(varsym_get_args), (sy_call_t *)sys_varsym_get },	/* 451 = varsym_get */
	{ AS(varsym_list_args), (sy_call_t *)sys_varsym_list },	/* 452 = varsym_list */
	{ AS(upc_register_args), (sy_call_t *)sys_upc_register },	/* 453 = upc_register */
	{ AS(upc_control_args), (sy_call_t *)sys_upc_control },	/* 454 = upc_control */
	{ AS(caps_sys_service_args), (sy_call_t *)sys_caps_sys_service },	/* 455 = caps_sys_service */
	{ AS(caps_sys_client_args), (sy_call_t *)sys_caps_sys_client },	/* 456 = caps_sys_client */
	{ AS(caps_sys_close_args), (sy_call_t *)sys_caps_sys_close },	/* 457 = caps_sys_close */
	{ AS(caps_sys_put_args), (sy_call_t *)sys_caps_sys_put },	/* 458 = caps_sys_put */
	{ AS(caps_sys_reply_args), (sy_call_t *)sys_caps_sys_reply },	/* 459 = caps_sys_reply */
	{ AS(caps_sys_get_args), (sy_call_t *)sys_caps_sys_get },	/* 460 = caps_sys_get */
	{ AS(caps_sys_wait_args), (sy_call_t *)sys_caps_sys_wait },	/* 461 = caps_sys_wait */
	{ AS(caps_sys_abort_args), (sy_call_t *)sys_caps_sys_abort },	/* 462 = caps_sys_abort */
	{ AS(caps_sys_getgen_args), (sy_call_t *)sys_caps_sys_getgen },	/* 463 = caps_sys_getgen */
	{ AS(caps_sys_setgen_args), (sy_call_t *)sys_caps_sys_setgen },	/* 464 = caps_sys_setgen */
	{ AS(exec_sys_register_args), (sy_call_t *)sys_exec_sys_register },	/* 465 = exec_sys_register */
	{ AS(exec_sys_unregister_args), (sy_call_t *)sys_exec_sys_unregister },	/* 466 = exec_sys_unregister */
	{ AS(sys_checkpoint_args), (sy_call_t *)sys_sys_checkpoint },	/* 467 = sys_checkpoint */
	{ AS(mountctl_args), (sy_call_t *)sys_mountctl },	/* 468 = mountctl */
	{ AS(umtx_sleep_args), (sy_call_t *)sys_umtx_sleep },	/* 469 = umtx_sleep */
	{ AS(umtx_wakeup_args), (sy_call_t *)sys_umtx_wakeup },	/* 470 = umtx_wakeup */
	{ AS(jail_attach_args), (sy_call_t *)sys_jail_attach },	/* 471 = jail_attach */
	{ AS(set_tls_area_args), (sy_call_t *)sys_set_tls_area },	/* 472 = set_tls_area */
	{ AS(get_tls_area_args), (sy_call_t *)sys_get_tls_area },	/* 473 = get_tls_area */
	{ AS(closefrom_args), (sy_call_t *)sys_closefrom },	/* 474 = closefrom */
	{ AS(stat_args), (sy_call_t *)sys_stat },	/* 475 = stat */
	{ AS(fstat_args), (sy_call_t *)sys_fstat },	/* 476 = fstat */
	{ AS(lstat_args), (sy_call_t *)sys_lstat },	/* 477 = lstat */
	{ AS(fhstat_args), (sy_call_t *)sys_fhstat },	/* 478 = fhstat */
	{ AS(getdirentries_args), (sy_call_t *)sys_getdirentries },	/* 479 = getdirentries */
	{ AS(getdents_args), (sy_call_t *)sys_getdents },	/* 480 = getdents */
	{ AS(usched_set_args), (sy_call_t *)sys_usched_set },	/* 481 = usched_set */
	{ AS(extaccept_args), (sy_call_t *)sys_extaccept },	/* 482 = extaccept */
	{ AS(extconnect_args), (sy_call_t *)sys_extconnect },	/* 483 = extconnect */
	{ AS(syslink_args), (sy_call_t *)sys_syslink },	/* 484 = syslink */
	{ AS(mcontrol_args), (sy_call_t *)sys_mcontrol },	/* 485 = mcontrol */
	{ AS(vmspace_create_args), (sy_call_t *)sys_vmspace_create },	/* 486 = vmspace_create */
	{ AS(vmspace_destroy_args), (sy_call_t *)sys_vmspace_destroy },	/* 487 = vmspace_destroy */
	{ AS(vmspace_ctl_args), (sy_call_t *)sys_vmspace_ctl },	/* 488 = vmspace_ctl */
	{ AS(vmspace_mmap_args), (sy_call_t *)sys_vmspace_mmap },	/* 489 = vmspace_mmap */
	{ AS(vmspace_munmap_args), (sy_call_t *)sys_vmspace_munmap },	/* 490 = vmspace_munmap */
	{ AS(vmspace_mcontrol_args), (sy_call_t *)sys_vmspace_mcontrol },	/* 491 = vmspace_mcontrol */
	{ AS(vmspace_pread_args), (sy_call_t *)sys_vmspace_pread },	/* 492 = vmspace_pread */
	{ AS(vmspace_pwrite_args), (sy_call_t *)sys_vmspace_pwrite },	/* 493 = vmspace_pwrite */
	{ AS(extexit_args), (sy_call_t *)sys_extexit },	/* 494 = extexit */
	{ AS(lwp_create_args), (sy_call_t *)sys_lwp_create },	/* 495 = lwp_create */
	{ 0, (sy_call_t *)sys_lwp_gettid },		/* 496 = lwp_gettid */
	{ AS(lwp_kill_args), (sy_call_t *)sys_lwp_kill },	/* 497 = lwp_kill */
	{ AS(lwp_rtprio_args), (sy_call_t *)sys_lwp_rtprio },	/* 498 = lwp_rtprio */
	{ AS(pselect_args), (sy_call_t *)sys_pselect },	/* 499 = pselect */
	{ AS(statvfs_args), (sy_call_t *)sys_statvfs },	/* 500 = statvfs */
	{ AS(fstatvfs_args), (sy_call_t *)sys_fstatvfs },	/* 501 = fstatvfs */
	{ AS(fhstatvfs_args), (sy_call_t *)sys_fhstatvfs },	/* 502 = fhstatvfs */
	{ AS(getvfsstat_args), (sy_call_t *)sys_getvfsstat },	/* 503 = getvfsstat */
	{ AS(openat_args), (sy_call_t *)sys_openat },	/* 504 = openat */
	{ AS(fstatat_args), (sy_call_t *)sys_fstatat },	/* 505 = fstatat */
	{ AS(fchmodat_args), (sy_call_t *)sys_fchmodat },	/* 506 = fchmodat */
	{ AS(fchownat_args), (sy_call_t *)sys_fchownat },	/* 507 = fchownat */
	{ AS(unlinkat_args), (sy_call_t *)sys_unlinkat },	/* 508 = unlinkat */
	{ AS(faccessat_args), (sy_call_t *)sys_faccessat },	/* 509 = faccessat */
	{ AS(mq_open_args), (sy_call_t *)sys_mq_open },	/* 510 = mq_open */
	{ AS(mq_close_args), (sy_call_t *)sys_mq_close },	/* 511 = mq_close */
	{ AS(mq_unlink_args), (sy_call_t *)sys_mq_unlink },	/* 512 = mq_unlink */
	{ AS(mq_getattr_args), (sy_call_t *)sys_mq_getattr },	/* 513 = mq_getattr */
	{ AS(mq_setattr_args), (sy_call_t *)sys_mq_setattr },	/* 514 = mq_setattr */
	{ AS(mq_notify_args), (sy_call_t *)sys_mq_notify },	/* 515 = mq_notify */
	{ AS(mq_send_args), (sy_call_t *)sys_mq_send },	/* 516 = mq_send */
	{ AS(mq_receive_args), (sy_call_t *)sys_mq_receive },	/* 517 = mq_receive */
	{ AS(mq_timedsend_args), (sy_call_t *)sys_mq_timedsend },	/* 518 = mq_timedsend */
	{ AS(mq_timedreceive_args), (sy_call_t *)sys_mq_timedreceive },	/* 519 = mq_timedreceive */
	{ AS(ioprio_set_args), (sy_call_t *)sys_ioprio_set },	/* 520 = ioprio_set */
	{ AS(ioprio_get_args), (sy_call_t *)sys_ioprio_get },	/* 521 = ioprio_get */
	{ AS(chroot_kernel_args), (sy_call_t *)sys_chroot_kernel },	/* 522 = chroot_kernel */
	{ AS(renameat_args), (sy_call_t *)sys_renameat },	/* 523 = renameat */
	{ AS(mkdirat_args), (sy_call_t *)sys_mkdirat },	/* 524 = mkdirat */
	{ AS(mkfifoat_args), (sy_call_t *)sys_mkfifoat },	/* 525 = mkfifoat */
	{ AS(mknodat_args), (sy_call_t *)sys_mknodat },	/* 526 = mknodat */
	{ AS(readlinkat_args), (sy_call_t *)sys_readlinkat },	/* 527 = readlinkat */
	{ AS(symlinkat_args), (sy_call_t *)sys_symlinkat },	/* 528 = symlinkat */
	{ AS(swapoff_args), (sy_call_t *)sys_swapoff },	/* 529 = swapoff */
	{ AS(vquotactl_args), (sy_call_t *)sys_vquotactl },	/* 530 = vquotactl */
	{ AS(linkat_args), (sy_call_t *)sys_linkat },	/* 531 = linkat */
};
