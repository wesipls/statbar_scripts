#include <stdio.h>
#include <sys/sysinfo.h>

struct sysinfo info;

int main (){
  sysinfo(&info);
 
  /* Get free and total swap converted to GB */
  float swap_used = (info.totalswap - info.freeswap) / ((float)1073741824);
  float swap_total = info.totalswap / ((float)1073741824);

  printf("%.1fG/%.1fG\n", swap_used, swap_total);
  return 0;
}
