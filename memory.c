#include <stdio.h>
#include <sys/sysinfo.h>
#include <string.h>

/* /proc/meminfo has a MemAvailable for a more accurate guesstimation, freeram returns RAM that is currently empty */

struct sysinfo info;

int main (){
  sysinfo(&info);
 
  /* Get free ram and total ram converted to GB */
  float ram_used = (info.totalram - info.freeram) / ((float)1073741824);
  float ram_total = info.totalram / ((float)1073741824);

  printf("%.1fG/%.1fG\n", ram_used, ram_total);
  return 0;
}
