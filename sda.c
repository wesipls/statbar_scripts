#include <stdio.h>
#include <sys/statvfs.h>

#include <stdbool.h> // Required for boolean values
#include <stdlib.h>  // Required for getenv, atol
#include <string.h>  // Required for strstr function
#include <unistd.h>

int main() {

  int wait = 5; // User-defined wait time from command line

  struct statvfs stat;

  // Point to the root directory or other mount point
  if (statvfs("/", &stat) != 0) {
    perror("statvfs failed");
    return 1;
  }

  // Calculate disk usage in percentage
  unsigned long total_blocks = stat.f_blocks;
  unsigned long free_blocks = stat.f_bfree;
  double used_percentage = 100.0 * (1.0 - ((double)free_blocks / total_blocks));
  int rounded_used_percentage =
      (int)(used_percentage + 0.5); // Round to nearest integer

  printf("Used disk space: %d%%\n", rounded_used_percentage);

  // Add disk I/O monitoring logic in MB
  char *disk = "sda"; // Change this to your disk name
  FILE *fp;
  char buffer[1024];
  long reads_start = 0, reads_end;
  long writes_start = 0, writes_end;
  // Assuming sector size is 512 bytes
  unsigned long sector_size = 512;

  // Read previous values from file
  FILE *temp_fp = fopen("/tmp/disk", "r");
  if (temp_fp) {
    fscanf(temp_fp, "%ld %ld", &reads_start, &writes_start);
    fclose(temp_fp);
  }

  fp = fopen("/proc/diskstats", "r");
  if (!fp) {
    perror("Failed to open /proc/diskstats");
    return 1;
  }

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    if (strstr(buffer, disk)) {
      sscanf(buffer, "%*d %*d %*s %lu %*u %*u %*u %lu", &reads_end,
             &writes_end);
      break;
    }
  }
  fclose(fp);

  // Save current values to file for next run
  temp_fp = fopen("/tmp/disk", "w");
  if (temp_fp) {
    fprintf(temp_fp, "%ld %ld", reads_end, writes_end);
    fclose(temp_fp);
  } else {
    perror("Failed to open /tmp/disk");
  }

  // Calculate IOPS in MB
  long read_diff = reads_end - reads_start;
  long write_diff = writes_end - writes_start;
  double reads_mb = (read_diff * sector_size) / (1024.0 * 1024.0);
  double writes_mb = (write_diff * sector_size) / (1024.0 * 1024.0);

  printf("Disk I/O per second - Reads: %.2f MB, Writes: %.2f MB\n",
         reads_mb / wait, writes_mb / wait);

  return 0;
}
