#include <inttypes.h>
#include <rocm_smi/rocm_smi.h>
#include <stdint.h>
#include <stdio.h>

int main() {
  uint32_t device_count;
  rsmi_status_t status = rsmi_init(RSMI_INIT_FLAG_ALL_GPUS);
  if (status != RSMI_STATUS_SUCCESS) {
    fprintf(stderr,
            "Failed to initialize ROCm SMI (Error Code: %d). Please ensure the "
            "ROCm SMI library is properly installed and that this program is "
            "run with the required permissions to access GPU hardware.\n",
            status);
    return -1;
  }

  // Retrieve number of GPU devices
  status = rsmi_num_monitor_devices(&device_count);
  if (status != RSMI_STATUS_SUCCESS) {
    fprintf(stderr, "Failed to retrieve the number of GPU devices: %d\n",
            status);
    return -1;
  }

  for (uint32_t i = 0; i < device_count; ++i) {
    uint32_t gpu_busy_percent;

    rsmi_status_t status = rsmi_dev_busy_percent_get(i, &gpu_busy_percent);
    if (status == RSMI_STATUS_SUCCESS) {
      printf("GPU %u Usage: %u%%\n", i, gpu_busy_percent);
    } else {
      fprintf(stderr, "Failed to retrieve GPU usage for device %u\n", i);
    }
  }

  rsmi_shut_down();
  return 0;
}
