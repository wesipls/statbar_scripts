#!/bin/bash
if [ -e /tmp/weather ]; then
  # File exists, check age and if it is empty
  if [ ! -s /tmp/weather ] || [ -z "$(cat /tmp/weather)" ] || [ $(($(date +%s) - $(stat -c %Y /tmp/weather))) -gt 1800 ]; then
    # File is empty or older than 30 min (1800 seconds), re-fetch weather data
    weather=$(curl -s https://wttr.in/Espoo?format="%c+%p+%w+%t+%f")
    echo "$weather" >/tmp/weather
  else
    # File is recent and not empty, read data from it
    weather=$(cat /tmp/weather)
  fi
else
  # File doesn't exist, fetch weather data
  weather=$(curl -s https://wttr.in/Espoo?format="%c+%p+%w+%t+%f")
  echo "$weather" >/tmp/weather
fi

echo $weather | awk -F " " '{print $1 "   " $2 "   " $3 "   " $4 "   (" $5")"}'
