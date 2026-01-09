#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRSIZE 32

void read_bytes(int *counter, char *bytes, char *read_file); /* Read files from rx_bytes and define to variable */
void write_bytes(char *bytes, char *read_file); /* Write rx_bytes from variable to tmp file for last received bytes tracking */
void bytes_diff(int counter, int time, char *bytes_current, char *bytes_last, char *converted_bytes); /* Calculate last received bytes and current received bytes for difference in recived bytes for last x seconds */

int main() {
  
  char rx_bytes_current[] = "/sys/class/net/enp5s0/statistics/rx_bytes"; /* File to fetch rx_bytes from */
  char rx_bytes_last[] = "./tmp/net_in_tmp"; /* Tmp file to store rx_bytes in */
  char tx_bytes_current[] = "/sys/class/net/enp5s0/statistics/tx_bytes"; /* File to fetch tx_bytes from */
  char tx_bytes_last[] = "./tmp/net_out_tmp"; /* Tmp file to store tx_bytes in */
  
  char bytes_in_current[STRSIZE]; /* String of bytes form rx_bytes */
  char bytes_in_last[STRSIZE]; /* Last copied value to tmp file from rx_bytes */
  char converted_in_bytes_diff[STRSIZE]; /* String of converted rx difference in kilobytes or megabytes */
  char bytes_out_current[STRSIZE]; /* String of bytes form tx_bytes */
  char bytes_out_last[STRSIZE]; /* Last copied value to tmp file from tx_bytes */
  char converted_out_bytes_diff[STRSIZE]; /* String of converted tx difference in kilobytes or megabytes */

  int i = 0; /* Int for counting failed file functions */
  int time_diff = 5; /* Time since last diff check, just set it to the interval the script will run on, or use the time header to check tmp file filestamp */

  read_bytes(&i, bytes_in_current, rx_bytes_current);
  read_bytes(&i, bytes_in_last, rx_bytes_last); 
  write_bytes(bytes_in_current, rx_bytes_last);

  i = 0; /* Resetting i for counting bytes out */

  read_bytes(&i, bytes_out_current, tx_bytes_current);
  read_bytes(&i, bytes_out_last, tx_bytes_last); 
  write_bytes(bytes_out_current, tx_bytes_last);

  bytes_diff(i, time_diff, bytes_in_current, bytes_in_last, converted_in_bytes_diff);
  bytes_diff(i, time_diff, bytes_out_current, bytes_out_last, converted_out_bytes_diff);
  printf("\u21F5 %s/%s\n", converted_in_bytes_diff, converted_out_bytes_diff);

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

void write_bytes( char *bytes, char *read_file) {
  FILE *file = fopen(read_file, "w");
  fputs(bytes, file);
  fclose(file);
}

void bytes_diff(int counter, int time, char *bytes_current, char *bytes_last, char *converted_bytes) {
  if(counter < 1) {
    unsigned long long converted_bytes_current = strtoul(bytes_current, NULL, 10);
    unsigned long long converted_bytes_last = strtoul(bytes_last, NULL, 10);
    int converted_bytes_diff = ((converted_bytes_current - converted_bytes_last) / 1024) / 5;
    if (converted_bytes_diff > 1024) {
      float tmp_result = (float) converted_bytes_diff / (float) 1024;
      sprintf(converted_bytes, "%.1fM", tmp_result);   
    } else {
      sprintf(converted_bytes, "%dK", converted_bytes_diff);
    }
  } else {
    sprintf(converted_bytes, "NA");
  }
}
