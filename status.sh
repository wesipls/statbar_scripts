#!/bin/bash

#Status script for swaybar

# Header
echo '{ "version": 1 }'

# Start infinite loop for status updates
echo '['
echo '[],'

# Mark that we are starting the infinite loop
while true; do
  # Current Time
  CURRENT_TIME=$(date +'%a %d %b %H:%M')
  CPUTMP=$(
    i=$(sensors | awk '/Tccd1/{print $2}' | rev | cut -c6- | rev)
    echo "$i°C"
  ) #Rebuild this bad boy in C if possible, hwmon might change per reboot, the internet told me so and im to lazy to check for now.
  RAM=$(/home/wesipls/.config/sway/statbar/memory)
  SWAP=$(/home/wesipls/.config/sway/statbar/swap)
  CPU=$(/home/wesipls/.config/sway/statbar/cpu)
  GPU=$(/home/wesipls/.config/sway/statbar/gpu)
  NET=$(/home/wesipls/.config/sway/statbar/network_in_out)
  SDA=$(/home/wesipls/.config/sway/statbar/sda)
  DISK_IO=$(/home/wesipls/.config/sway/statbar/disk_io.sh)
  WEATHER=$(/home/wesipls/.config/sway/statbar/weather.sh)

  # Create JSON array for bar items
  echo '['
  echo '{ "full_text": "'"$RAM"'",
          "min_width": 144,
          "align": "center"
        },'
  echo '{ "full_text": "'"$SWAP"'",
          "min_width": 144,
          "align": "center"
        },'
  echo '{ "full_text": "'"$CPU $CPUTMP"'",
          "min_width": 144,
          "align": "center"
        },'
  echo '{ "full_text": "'"$GPU"'",
          "min_width": 144,
          "align": "center"
        },'
  echo '{ 
          "full_text": "'"$SDA $DISK_IO"'",
          "min_width": 240,
          "align": "center"
        },'
  echo '{ 
          "full_text": "'"$NET"'",
          "min_width": 192,
          "align": "center"
        },'
  echo '{ 
          "full_text": "'"$WEATHER"'",
          "min_width": 144,
          "align": "center"
        },'
  echo '{ 
          "full_text": "'"$CURRENT_TIME"'",
          "min_width": 144,
          "align": "center"
        },'
  echo '],'

  sleep 5 # Update every second
done
