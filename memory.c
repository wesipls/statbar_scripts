#include <stdio.h>
#include <sys/sysinfo.h>

/* Converts bytes to gigabytes */
double bytes_to_gb(unsigned long bytes) { return bytes / (double)1073741824; }

/* Retrieves memory statistics */
struct sysinfo get_memory_info() {
  struct sysinfo info;
  if (sysinfo(&info) != 0) {
    perror("Failed to get system info");
  }
  return info;
}

/* Calculates memory usage */
void calculate_memory_usage(struct sysinfo info, double *ram_used,
                            double *ram_total) {
  *ram_total = bytes_to_gb(info.totalram);
  *ram_used = *ram_total - bytes_to_gb(info.freeram);
}

/* Displays memory usage */
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
