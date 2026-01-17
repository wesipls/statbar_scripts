#include <inttypes.h>
#include <rocm_smi/rocm_smi.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  rsmi_status_t status = rsmi_init(RSMI_INIT_FLAG_ALL_GPUS);
  if (status != RSMI_STATUS_SUCCESS) {
    fprintf(stderr, "Failed to initialize ROCm SMI (Error Code: %d)", status);
    return -1;
  }

  uint32_t gpu_busy_percent;
  uint32_t gpu_id = 0;

  status = rsmi_dev_busy_percent_get(gpu_id, &gpu_busy_percent);
  if (status == RSMI_STATUS_SUCCESS) {
    printf("GPU %u Usage: %u%%\n", gpu_id, gpu_busy_percent);
  } else {
    fprintf(stderr, "Failed to retrieve GPU usage for device %u\n", gpu_id);
  }

  rsmi_shut_down();
  return 0;
}
