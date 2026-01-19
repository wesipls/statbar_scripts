#!/bin/bash

# Define a custom timestamp file to track the last update
TIMESTAMP="/tmp/apt-update-timestamp"

# Check if the timestamp exists and if the last update was over 30 minutes ago
if [ -f "$TIMESTAMP" ]; then
  if [ $(($(date +%s) - $(date +%s -r "$TIMESTAMP"))) -ge 1800 ]; then
    sudo apt update
    touch "$TIMESTAMP"
  fi
else
  sudo apt update
  touch "$TIMESTAMP"
fi

# Count upgradeable packages
UPGRADE_COUNT=$(apt list --upgradeable 2>/dev/null | grep -c "upgradable")

# Display the appropriate message if no packages are upgradeable
if [[ $UPGRADE_COUNT -eq 0 ]]; then
  echo "Up to date"
else
  echo "$UPGRADE_COUNT upgrades available"
fi
