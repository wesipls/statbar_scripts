#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 64

void read_bytes(int *counter, char *bytes, char *read_file); /* Read files from rx_bytes and define to variable */
void write_bytes(int *counter, char *bytes, char *read_file); /* Write rx_bytes from variable to tmp file for last received bytes tracking */
int bytes_diff(int counter, char *bytes_current, char *bytes_last); /* Calculate last received bytes and current received bytes for difference in recived bytes for last x seconds */

int main() {
  
  char rx_bytes_current[] = "/sys/class/net/enp5s0/statistics/rx_bytes"; /* File to fetch rx_bytes from */
  char rx_bytes_last[] = "./tmp/net_in_tmp"; /* tmp file to store rx_bytes in */
  char bytes_in_current[STRSIZE]; /* String of bytes form rx_bytes */
  char bytes_in_last[STRSIZE]; /* Last copied value to tmp file from rx_bytes */
  int i = 0; /* int for counting failed file functions */

  read_bytes(&i, bytes_in_current, rx_bytes_current);
  read_bytes(&i, bytes_in_last, rx_bytes_last); 
  write_bytes(&i, bytes_in_current, rx_bytes_last);
 
  int converted_bytes_diff = bytes_diff(i, bytes_in_current, bytes_in_last);  /* Difference in bytes_in_current and bytes_in_last */


//DEBUG
//  printf("%d\n", i); 
//  printf("%s / %s\n", bytes_in_current, bytes_in_last);
  printf("%d\n", converted_bytes_diff);
  return 0;
};


void read_bytes(int *counter, char *bytes, char *read_file) {
  FILE *file = fopen(read_file, "r");
  if(file == NULL) {
    (*counter)++;
  } else {
    fgets(bytes, STRSIZE, file);
    fclose(file);
  }
}

void write_bytes(int *counter, char *bytes, char *read_file) {
  FILE *file = fopen(read_file, "w");
  fputs(bytes, file);
  fclose(file);
}

int bytes_diff(int counter, char *bytes_current, char *bytes_last) {
  if(counter < 1) {
    unsigned long long converted_bytes_current = strtoul(bytes_current, NULL, 10);
    unsigned long long converted_bytes_last = strtoul(bytes_last, NULL, 10);
    int converted_bytes_diff = (converted_bytes_current - converted_bytes_last) / 1024;
    return converted_bytes_diff;
  } else {
    return 0;
  }
}
