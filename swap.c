/*
  Usage: ./swap
  Example Output: SWAP: 7.8G/15.6G

  Not much else to say here, does what its suppsoed to as long as you have swap.
 */

#include <stdio.h>
#include <sys/sysinfo.h>

double bytes_to_gb(unsigned long bytes) { return bytes / (double)1073741824; }

struct sysinfo get_swap_info() {
  struct sysinfo info;
  if (sysinfo(&info) != 0) {
    perror("Failed to get system info");
  }
  return info;
}

void calculate_swap_usage(struct sysinfo info, double *swap_used,
                          double *swap_total) {
  *swap_total = bytes_to_gb(info.totalswap);
  *swap_used = *swap_total - bytes_to_gb(info.freeswap);
}

void display_swap_usage(double swap_used, double swap_total) {
  printf("SWAP: %.1fG/%.1fG\n", swap_used, swap_total);
}

int main() {
  struct sysinfo info = get_swap_info();

  double swap_used = 0, swap_total = 0;
  calculate_swap_usage(info, &swap_used, &swap_total);

  display_swap_usage(swap_used, swap_total);
  return 0;
}
