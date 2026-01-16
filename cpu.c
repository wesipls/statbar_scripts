#include <stdio.h>

/* Retrieves CPU stats from /proc/stat */
void read_proc_stat(unsigned long *prev_total, unsigned long *prev_idle,
                    unsigned long *current_total, unsigned long *current_idle) {
  FILE *file = fopen("/proc/stat", "r");
  if (!file) {
    perror("Failed to open /proc/stat");
    return;
  }

  char line[256];

  if (fgets(line, sizeof(line), file)) {
    unsigned long user, nice, system, idle, iowait, irq, softirq, steal, guest,
        guest_nice;
    sscanf(line, "cpu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", &user, &nice,
           &system, &idle, &iowait, &irq, &softirq, &steal, &guest,
           &guest_nice);
    *current_total = user + nice + system + irq + softirq + steal + guest +
                     guest_nice + idle + iowait;
    *current_idle = idle + iowait;
  }
  fclose(file);
}

/* Retrieves previous values from tmp file*/
void read_prev_usage(unsigned long *prev_total, unsigned long *prev_idle) {
  FILE *tmp_file = fopen("/tmp/cpu_usage", "r");
  if (tmp_file) {
    if (fscanf(tmp_file, "%lu %lu", prev_total, prev_idle) != 2) {
      perror("Failed to open /tmp/cpu_usage");
    }
    fclose(tmp_file);
  }
}
/* Calculates and prints CPU usage */
void calculate_cpu_usage(unsigned long prev_total, unsigned long prev_idle,
                         unsigned long current_total,
                         unsigned long current_idle) {
  unsigned long total_final = current_total - prev_total;
  unsigned long total_idle = current_idle - prev_idle;
  double usage =
      ((double)(total_final - total_idle) * 100) / (double)total_final;
  printf("CPU: %.2f%%\n", usage);
}
/* Writes current values to tmp file */
void write_tmp_file(unsigned long current_total, unsigned long current_idle) {
  FILE *file = fopen("/tmp/cpu_usage", "w");
  if (!file) {
    perror("Failed to open /tmp/cpu_usage");
    return;
  }
  fprintf(file, "%lu %lu\n", current_total, current_idle);
  fclose(file);
}

int main() {
  unsigned long prev_total = 0, prev_idle = 0, current_total = 0,
                current_idle = 0;
  read_proc_stat(&prev_total, &prev_idle, &current_total, &current_idle);
  read_prev_usage(&prev_total, &prev_idle);
  calculate_cpu_usage(prev_total, prev_idle, current_total, current_idle);
  write_tmp_file(current_total, current_idle);
  return 0;
}
