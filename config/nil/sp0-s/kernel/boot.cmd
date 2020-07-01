cd "exe" 
ld < core-bin
taskSpawn ("bootcmd", 100, 0, 8192, CFE, 0, 0)
