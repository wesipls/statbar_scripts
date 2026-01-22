/*
  Usage: ./memory
  Example Output: RAM: 7.8G/15.6G

  There is a more accurate way to get memory usage on Linux systems using the
  free -m command which returns AvailableMemory This program does not take into
  account freeable memory, only empty memory vs used memory. Just a heads up if
  you're planning on using this program, each to their own needs.
 */

#include <stdio.h>
#include <sys/sysinfo.h>

double bytes_to_gb(unsigned long bytes) { return bytes / (double)1073741824; }

struct sysinfo get_memory_info() {
  struct sysinfo info;
  if (sysinfo(&info) != 0) {
    perror("Failed to get system info");
  }
  return info;
}

void calculate_memory_usage(struct sysinfo info, double *ram_used,
                            double *ram_total) {
  *ram_total = bytes_to_gb(info.totalram);
  *ram_used = *ram_total - bytes_to_gb(info.freeram);
}

void display_memory_usage(double ram_used, double ram_total) {
  printf("RAM: %.1fG/%.1fG\n", ram_used, ram_total);
}

int main() {
  struct sysinfo info = get_memory_info();

  double ram_used = 0, ram_total = 0;
  calculate_memory_usage(info, &ram_used, &ram_total);

  display_memory_usage(ram_used, ram_total);
  return 0;
}
