#!/bin/bash

# Usage: ./disk_io.sh
# Example output: ↑ 1.2M / ↓ 3.4M
#
# Fetches disk io statistics from /sys/class/block/$disk/stat, saves old values in /tmp/disk_in and /tmp/disk_out.
# Measures the $disk disk IO in kb/mb per second.
#
# Assumes this script is executed every 5 seconds, if you plan on running it with another interval update interval variable.
# Assumes $uuid is the uuid of your disk, wich is probably not the case, you can check your disk uuid from /dev/disk/by-uuid.
#
# Should work on any Linux as long as /sys/class/block/$disk/stat is available.

interval=5
uuid="8b33bb8a-2621-4d06-9645-9809f09e660b"

disk=$(readlink /dev/disk/by-uuid/$uuid | xargs basename)

to_human_readable() {
  local bytes=$1
  if [ "$bytes" -lt 1048576 ]; then
    echo "$(awk "BEGIN {printf \"%.1f\", ${bytes}/1024}")K"
  else
    echo "$(awk "BEGIN {printf \"%.1f\", ${bytes}/1048576}")M"
  fi
}

if [[ -f /tmp/disk_in && -f /tmp/disk_out ]]; then
  start_read=$(cat /tmp/disk_in)
  start_write=$(cat /tmp/disk_out)
else
  start_read=$(cat /sys/class/block/$disk/stat | awk '{print $3}')
  start_write=$(cat /sys/class/block/$disk/stat | awk '{print $7}')
  echo $start_read >/tmp/disk_in
  echo $start_write >/tmp/disk_out
  exit 0
fi

end_read=$(cat /sys/class/block/$disk/stat | awk '{print $3}')
end_write=$(cat /sys/class/block/$disk/stat | awk '{print $7}')

read_diff=$(((end_read - start_read) * 512 / interval))
write_diff=$(((end_write - start_write) * 512 / interval))

echo $end_read >/tmp/disk_in
echo $end_write >/tmp/disk_out

read_rate=$(to_human_readable $read_diff)
write_rate=$(to_human_readable $write_diff)

echo "↑ $read_rate / ↓ $write_rate"
