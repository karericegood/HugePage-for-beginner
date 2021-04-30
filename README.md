# HugePage for beginner

1. Hello! This page is just a summary of my study. you can freely email me for question! 
2. If you want to check the Ununtu's Hugepage option and wanna use, this page will help you! 

1. You can check the hugepage option by this! 

First, you can check that you're using hugepage now like this.(Of course, you don't have a experience of this, this is just a check)

Enter this command on terminal.

```jsx
cat /proc/meminfo
```

and you can see like this page.

```jsx
MemTotal:        8013984 kB
MemFree:          330808 kB
MemAvailable:    3247948 kB
Buffers:          128420 kB
Cached:          3277436 kB
SwapCached:         1168 kB
Active:          3528604 kB
Inactive:        1406272 kB
Active(anon):    1496236 kB
Inactive(anon):   453960 kB
Active(file):    2032368 kB
Inactive(file):   952312 kB
Unevictable:      191840 kB
Mlocked:              32 kB
SwapTotal:       2097148 kB
SwapFree:        2090748 kB
Dirty:               580 kB
Writeback:             0 kB
AnonPages:       1719940 kB
Mapped:           697784 kB
Shmem:            421728 kB
KReclaimable:     237672 kB
Slab:             363520 kB
SReclaimable:     237672 kB
SUnreclaim:       125848 kB
KernelStack:       10720 kB
PageTables:        27176 kB
NFS_Unstable:          0 kB
Bounce:                0 kB
WritebackTmp:          0 kB
CommitLimit:     5055564 kB
Committed_AS:    7878536 kB
VmallocTotal:   34359738367 kB
VmallocUsed:       31496 kB
VmallocChunk:          0 kB
Percpu:             3392 kB
HardwareCorrupted:     0 kB
AnonHugePages:         0 kB
ShmemHugePages:        0 kB
ShmemPmdMapped:        0 kB
FileHugePages:         0 kB
FilePmdMapped:         0 kB
HugePages_Total:       0
HugePages_Free:        0
HugePages_Rsvd:        0
HugePages_Surp:        0
Hugepagesize:       2048 kB
Hugetlb:         2097152 kB
DirectMap4k:      290780 kB
DirectMap2M:     6912000 kB
DirectMap1G:     1048576 kB
```

At first time, you can see that the 'HugePages_Total = 0' that the hugepage option is not activated. 

If you want to activate the hugepage option, press this command 

```jsx
$ echo 1024 | sudo tee /proc/sys/vm/nr_hugepages
```

Then, you can freely use the hugepage now! if you can use the htop, you can see that your memory usage is bigger than before. Because the hugepage option is pre-allocation so that you can only use pre-allocation memory for hugepage. (eg. you can use only 2GB for hugepage if you allocate 1024 pages because of that 2MB*1024 = 2GB)

2. You can test the Hugepage's effect in real machine

First, find the blast.cpp. this is the file that you can see the memory stress. 

Before you compile this file, you have to install the libhugetlbfs! 

the link is here! 

[https://github.com/libhugetlbfs/libhugetlbfs](https://github.com/libhugetlbfs/libhugetlbfs)

you can follow this and use the hugepage malloc.

Then, compile the blast.cpp like this,

```jsx
gcc -o blast - blast.cpp -O0
```

Then, run the file in two ways. 

First, run like this command

```jsx
./blast 100
```

This command means you allocate 100MB  sequencely for physical memory. Then, See the htop. you can see the 100~101MB is allocate! 

Then, command like this 

```jsx
LD_PRELOAD=libhugetlbfs.so LD_LIBRARY_PATH=~/libhugetlbfs/obj64 HUGETLB_MULTICORE=yes ./blast 100	
```

This command wiil use the hugepage malloc. if you not allocate the hugepage, you can see this message.

```jsx
....
Currently allocating 92 MB
Currently allocating 93 MB
libhugetlbfs: WARNING: New heap segment map at 0x55eefd600000 failed: Cannot allocate memory
Currently allocating 94 MB
Currently allocating 95 MB
libhugetlbfs: WARNING: New heap segment map at 0x55eefd600000 failed: Cannot allocate memory
Currently allocating 96 MB
Currently allocating 97 MB
libhugetlbfs: WARNING: New heap segment map at 0x55eefd600000 failed: Cannot allocate memory
Currently allocating 98 MB
Currently allocating 99 MB
libhugetlbfs: WARNING: New heap segment map at 0x55eefd600000 failed: Cannot allocate memory
Currently allocating 100 MB
Hit 'y' to exit...
```

If you do correctly, you can see like this.

```jsx
.....
Currently allocating 92 MB
Currently allocating 93 MB
Currently allocating 94 MB
Currently allocating 95 MB
Currently allocating 96 MB
Currently allocating 97 MB
Currently allocating 98 MB
Currently allocating 99 MB
Currently allocating 100 MB
```

And you can see like this with the command cat /proc/meminfo

```jsx
....
HugePages_Total:    1024
HugePages_Free:      973
HugePages_Rsvd:        0
HugePages_Surp:        0
....
```

You can see the hugepage_free is reduced by using the application! 

3. Memory bloating

What is the disadvantage of using Hugepage? Many of them say that the memory bloating(internal fragmentation)(the concept is not equal but almost same). 

 There is a file called memory_bloating.c. This is simple code for finding memory bloating with Hugepages. 

first, compile like this,

```jsx
$ gcc -o memory_bloating memory_bloating.c 
$ gcc -o memory_bloating_on memory_bloating.c -DON
```

Then, you can find the memory bloating by run this app and use the htop and this commad.

 

```jsx
$ grep -B 11 'KernelPageSize:     2048 kB' /proc/[proc id]/smaps | grep "^Size:" | awk 'BEGIN{sum=0}{sum+=$2}END{print sum}'
```

then, you can see the usage of process's physical memory that you can't find the htop. Htop can't find the real physical memory usage when we use the hugepage option. So you have to like this command.

If you have a question, email me sungju_kim@dgist.ac.kr.
