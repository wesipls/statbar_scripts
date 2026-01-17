# statbar_scripts
Small C programs for swaybar.
## status.sh
A shell script to run the C programs and format their output for swaybar.
## memory.c
Displays current RAM usage:  
**Output**: `RAM: 8.2G/16G`
## swap.c
Displays current swap usage:  
**Output**: `SWP: 2.5G/8G`
## network_in_out.c
Displays current network usage:  
**Output**:`NET: ↓ 1.5M / ↑ 800K`
## cpu.c
Displays current CPU usage:  
**Output**: `CPU: 15%`
## gpu.c
Displays current GPU usage and temperature:  
**Output**: `GPU: 15% 15°C`

[NOTE]: These programs are provided as-is and may require modifications, below are a few suggestion on the top of my head:  
status.sh:  
-Change the path for the scripts  

network_in_out.c:  
-Check the network interface in the path (enop5s0).  
-Change int time_diff to the interval of seconds you plan on running the script.  

gpu.c:  
-Requires rocm-smi to be installed and a compatible AMD GPU.  
-Assumes the first GPU (index 0) is the one to monitor.  
