#include <stdio.h>
#include <sys/sysinfo.h>

/* Converts bytes to gigabytes */
double bytes_to_gb(unsigned long bytes) { return bytes / (double)1073741824; }

/* Retrieves swap information */
struct sysinfo get_swap_info() {
  struct sysinfo info;
  if (sysinfo(&info) != 0) {
    perror("Failed to get system info");
  }
  return info;
}

/* Calculates swap usage */
void calculate_swap_usage(struct sysinfo info, double *swap_used,
                          double *swap_total) {
  *swap_total = bytes_to_gb(info.totalswap);
  *swap_used = *swap_total - bytes_to_gb(info.freeswap);
}

/* Displays swap usage */
void display_swap_usage(double swap_used, double swap_total) {
  printf("SWP: %.1fG/%.1fG\n", swap_used, swap_total);
}

int main() {
  struct sysinfo info = get_swap_info();

  double swap_used = 0, swap_total = 0;
  calculate_swap_usage(info, &swap_used, &swap_total);

  display_swap_usage(swap_used, swap_total);
  return 0;
}
