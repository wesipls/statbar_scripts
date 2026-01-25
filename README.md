# statbar_scripts
Small C programs and shell scripts for swaybar.

> [!NOTE]  
> These programs are provided as-is and may require modifications.  
> if any program/script is not working there should be a comment in the beginning of said file explaining why.

### status.sh
A shell script to run the C programs and format their output for swaybar.
### memory.c
Displays current RAM usage:  
**Output**: `RAM: 8.2G/16G`
### swap.c
Displays current swap usage:  
**Output**: `SWP: 2.5G/8G`
### network_in_out.c
Displays current network usage:  
**Output**:`NET: ↓ 1.5M / ↑ 800K`
### cpu.c
Displays current CPU usage:  
**Output**: `CPU: 15%`
### gpu.c
Displays current GPU usage and temperature:  
**Output**: `GPU: 15% 15°C`
### sda.c
Displays current used disk space on sda:  
**Output**: `DISK SDA: 4%`
### disk_io.sh
Displays current disk I/O usage on sda:  
Output: `↓ 1.2M / ↑ 500.0K`
### sda_temp.sh
Displays current temperature on sda:  
Output: `15°C`
### weather.sh
Displays count of currently upgradeable packages.  
Output: `🌫   0.0mm   →10km/h   -1°C   (-4°C)`
### updates.sh
Displays count of currently upgradeable packages.  
Output: `2 Upgradeble packages`
