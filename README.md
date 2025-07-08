# Trampoline

Building ViPER
on UNIX shell:
```
$ cd viper
$ make
$ export VIPER_PATH=`pwd`
```
It is recommended to get the path to ViPER in the environment variables, and define in the ~/.bashrc or ~/.profile the command:

```
$ export VIPER_PATH=PATH_TO_TRAMPOLINE/viper
```

Run example
Examples are easy to run: The first time, goil should be called directly. It will generate the appropriate Makefile:
```
$ cd examples/posix/periodic
$ goil --target=posix/linux  --templates=../../../goil/templates/ periodic.oil
```
Then, the makefile is generated, and it will call goil again when the .oil file is updated
```
$ ./make.py -s
```
Then, run the trampoline binary. This program will start another process to run ViPER silently.
```
$ ./periodic_exe
```
