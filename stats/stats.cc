#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>

int main(){
	while (1) {
		sleep(1);
        	
		struct sysinfo info;
	        sysinfo(&info);

		size_t size = 0;
		struct stat _stat;
		auto ret = stat("/tmp/access.log", &_stat);
		if (!ret) {
			size = _stat.st_size;
		}

		printf("System memory -> total:%d Kb, free:%d Kb, access log:%d Kb\n", 
				info.totalram >> 10, info.freeram >> 10, size >> 10);
	}

	return 0;
}
