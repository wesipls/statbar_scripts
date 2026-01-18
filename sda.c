#include <stdio.h>
#include <sys/statvfs.h>

int main() {
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

  return 0;
}
