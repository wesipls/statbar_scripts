#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 64

int main() {
/* Change enp5s0 to what your network interface is called */
  FILE *in_current = fopen("/sys/class/net/enp5s0/statistics/rx_bytes", "r");

  /* current = total bytes in since boot, last = bytes in tmp before overwriting */
  /* i is for checking if the if statements have triggered */
  char bytes_in_current[STRSIZE];
  char bytes_in_last[STRSIZE];
  int i = 0;

  /* Get total bytes since boot, increment i if file not available */
  if(in_current == NULL) {
    i++;
  }
  else {
    fgets(bytes_in_current, STRSIZE, in_current);
    fclose(in_current);

    /* Get last checked bytes from tmp file, increment i and create file, if file not available */
    FILE *in_last_r = fopen("./tmp/net_in_tmp", "r");

    if(in_last_r == NULL) {
      FILE *in_last_w = fopen("./tmp/net_in_tmp", "w");
      fclose(in_last_w);
      i++;
    }
    else {
    fgets(bytes_in_last, STRSIZE, in_last_r);
    fclose(in_last_r);

    /* Write new last value to tmp file */
    FILE *in_last_w = fopen("./tmp/net_in_tmp", "w");
    fputs(bytes_in_current, in_last_w);
    fclose(in_last_w);

    }
  }

  /* Check if bytes_in_diff is still empty, and calculate diff */

  /*TODO! Check if value of i is 0, and if so convert last and current to long long, calculate diff and convert to K, otherwise print diff as is */
  if(i < 1) {
    unsigned long long converted_bytes_in_current = strtoul(bytes_in_current, NULL, 10);
    unsigned long long converted_bytes_in_last = strtoul(bytes_in_last, NULL, 10);
    int converted_bytes_diff = (converted_bytes_in_current - converted_bytes_in_last) / 1024;
    printf("%d", converted_bytes_diff);
  } else {
    printf("IN NA\n");
  }

  return 0;
}
