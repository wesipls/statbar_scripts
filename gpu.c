#include <inttypes.h>
#include <rocm_smi/rocm_smi.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  rsmi_status_t status;
  uint32_t gpu_busy_percent;
  uint32_t gpu_id = 0;

  /* Initialize the ROCm SMI library */
  if ((status = rsmi_init(RSMI_INIT_FLAG_ALL_GPUS)) != RSMI_STATUS_SUCCESS) {
    fprintf(stderr, "Failed to initialize ROCm SMI (Error Code: %d)\n", status);
    return -1;
  }

  /* Retrieve GPU usage */
  if ((status = rsmi_dev_busy_percent_get(gpu_id, &gpu_busy_percent)) !=
      RSMI_STATUS_SUCCESS) {
    fprintf(stderr, "Failed to retrieve GPU usage for device %u\n", gpu_id);
    rsmi_shut_down();
    return -1;
  }

  /* Retrieve GPU temperature */
  uint64_t temp;
  if ((status = rsmi_dev_temp_metric_get(gpu_id, 0, RSMI_TEMP_CURRENT,
                                         (int64_t *)&temp)) !=
      RSMI_STATUS_SUCCESS) {
    fprintf(stderr, "GPU %u: Usage %u%%, Failed to retrieve temperature\n",
            gpu_id, gpu_busy_percent);
    rsmi_shut_down();
    return -1;
  }

  /* Print GPU usage and temperature */
  printf("GPU: %u%% +%lu°C\n", gpu_busy_percent, temp / 1000);
  rsmi_shut_down();
  return 0;
}
