#!/bin/bash

# Usage: ./disk_io.sh
# Example output: ↑ 1.2M / ↓ 3.4M
#
# Fetces disk io statistics from /sys/class/block/sdb/stat, saves old values in /tmp/disk_in and /tmp/disk_out.
# Measures the sdb disk IO in kb/mb per second.
#
# Assumes this script is executed every 5 seconds, if you plan on running it with another interval update interval variable.
# Assumes sdb is the disk to monitor, change disk variable if needed.
#
# Should work on any Linux as long as /sys/class/block/sdb/stat is available.

interval=5
disk=sdb

to_human_readable() {
  local bytes=$1
  if [ "$bytes" -lt 1048576 ]; then
    echo "$(awk "BEGIN {printf \"%.1f\", ${bytes}/1024}")K"
  else
    echo "$(awk "BEGIN {printf \"%.1f\", ${bytes}/1048576}")M"
  fi
}

# Get saved initial disk statistics
if [[ -f /tmp/disk_in && -f /tmp/disk_out ]]; then
  start_read=$(cat /tmp/disk_in)
  start_write=$(cat /tmp/disk_out)
else
  # If files don't exist, initialize them
  start_read=$(cat /sys/class/block/$disk/stat | awk '{print $3}')
  start_write=$(cat /sys/class/block/$disk/stat | awk '{print $7}')
  echo $start_read >/tmp/disk_in
  echo $start_write >/tmp/disk_out
  echo "No previous data available. Initialization complete."
  exit 0
fi

# Get current disk statistics
end_read=$(cat /sys/class/block/$disk/stat | awk '{print $3}')
end_write=$(cat /sys/class/block/$disk/stat | awk '{print $7}')

# Calculate the difference in bytes per second
read_diff=$(((end_read - start_read) * 512 / interval))
write_diff=$(((end_write - start_write) * 512 / interval))

# Save the current data for the next run
echo $end_read >/tmp/disk_in
echo $end_write >/tmp/disk_out

# Convert the differences to human-readable format
read_rate=$(to_human_readable $read_diff)
write_rate=$(to_human_readable $write_diff)

# Display the results
echo "↑ $read_rate / ↓ $write_rate"
