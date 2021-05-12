#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/sched.h>
#include<linux/syscalls.h>

SYSCALL_DEFINE2(listSleepProcess, const long __user *, buf, int, size)
{
    struct task_struct *proces;
    long kbuf[256];
    int bufsz;
    int ret;
    int index = 0;
 
	/* Find the process */
	for_each_process(proces) {
		
		if(proces->state == TASK_INTERRUPTIBLE || proces->state == TASK_UNINTERRUPTIBLE){
			kbuf[index] = (long)task_pid_nr(proces);
			index = index + 1;
			
			
		}
	}
	bufsz = sizeof(kbuf);
	/* User buffer is too small */
	if(bufsz > size ){
		return -1;
	}

	if(index == 0){
		return 0;
	}
		
	/* success */
	ret = copy_to_user((void*)buf, (void*)kbuf, bufsz);
	
	return index;
}