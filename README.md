# edk2-trace
Proof-of-concept user space application for stack trace support in UEFI on x64 platforms.

The PE/COFF executable basically prints out call stack information at runtime.

# Dependencies

- x64 platform
- GNU make
- MinGW toolchain
- Wine (if you're using Linux)

# Build instructions

```
$ MINGW_PREFIX=x86_64-w64-mingw32- make
```

NOTE: Set MINGW_PREFIX to whatever you have in your system.

# Examples

```
$ MINGW_PREFIX=x86_64-w64-mingw32- make
x86_64-w64-mingw32-gcc -c -o src/main.o src/main.c -Wall -Werror -I./include
x86_64-w64-mingw32-gcc -c -o src/trace.o src/trace.c -Wall -Werror -I./include
x86_64-w64-mingw32-gcc -o main.exe src/main.o src/trace.o -Wall -Werror -I./include

$ wine main.exe
Start test:

Call __func_start()
Call __func_a()
Call __func_b()
Call __func_c()
Call __func_d()
Call __func_e()
Call __func_f()
Call __func_g()
Call __func_h()
Call __func_end()

Callstack:
0 0x00000000004017d2 in main (+0x17d1) (0x000000000032fa90)
1 0x00000000004017bc in main (+0x17bb) (0x000000000032fac0)
2 0x0000000000401781 in main (+0x1780) (0x000000000032faf0)
3 0x0000000000401746 in main (+0x1745) (0x000000000032fb20)
4 0x000000000040170b in main (+0x170a) (0x000000000032fb50)
5 0x00000000004016d0 in main (+0x16cf) (0x000000000032fb80)
6 0x0000000000401695 in main (+0x1694) (0x000000000032fbb0)
7 0x000000000040165a in main (+0x1659) (0x000000000032fbe0)
8 0x000000000040161f in main (+0x161e) (0x000000000032fc10)
9 0x00000000004015e4 in main (+0x15e3) (0x000000000032fc40)
10 0x0000000000401869 in main (+0x1868) (0x000000000032fc70)
11 0x00000000004013f8 in main (+0x13f7) (0x0000000000471940)

Stack dump:
0x000000000032fa50:  000000000032fa50 0000000000471940
0x000000000032fa60:  0000000000000000 0000000000000012
0x000000000032fa70:  0000000000000001 00000000004017d2
0x000000000032fa80:  000000000032fa90 000000000032fa50
0x000000000032fa90:  000000000032fac0 00000000004017bc
0x000000000032faa0:  0000000000000001 0000000000000001
0x000000000032fab0:  000000000000002b 0000000000010660
0x000000000032fac0:  000000000032faf0 0000000000401781
0x000000000032fad0:  0000000000000001 0000000000000001
0x000000000032fae0:  000000000000002b 0000000000010660
0x000000000032faf0:  000000000032fb20 0000000000401746
```
