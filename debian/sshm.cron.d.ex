#
# Regular cron jobs for the sshm package.
#
0 4	* * *	root	[ -x /usr/bin/sshm_maintenance ] && /usr/bin/sshm_maintenance
