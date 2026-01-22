#!/bin/bash

#Short script to check for available apt updates, and display count of available updates.
#Requires debian-based system with apt package manager.
#
#Stores last apt-get updated timestimap in /tmp/apt-update-timestamp.

TIMESTAMP="/tmp/apt-update-timestamp"

if [ -f "$TIMESTAMP" ]; then
  if [ $(($(date +%s) - $(date +%s -r "$TIMESTAMP"))) -ge 1800 ]; then
    sudo apt-get -qq update
    touch "$TIMESTAMP"
  fi
else
  sudo apt update
  touch "$TIMESTAMP"
fi

UPGRADE_COUNT=$(apt list --upgradeable 2>/dev/null | grep -c "upgradable")

if [[ $UPGRADE_COUNT -eq 0 ]]; then
  echo "Up to date"
elif [[ $UPGRADE_COUNT -eq 1 ]]; then
  echo "$UPGRADE_COUNT upgrade available"
else
  echo "$UPGRADE_COUNT upgrades available"
fi
