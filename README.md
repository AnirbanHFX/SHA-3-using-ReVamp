# SHA-3 Using Revamp

### Keccak-f1600.ins
This file contains the composite instruction set.
Can be generated using Ins_gen.c
It has been tested and verified again Reference SHA-3 implementations.

### Keccak-f1600.inp
Contains the example PIR inputs. Can be created using inp_gen.c.
Currently contains PIR inputs for the ASCII string "abc".

### Ins_gen.c
Used to generate the instruction set Keccak-f1600.ins
Also generated RCt.csv which is used by inp_gen to determine the cycle number where Round Constants are required by Iota stage of Instruction set.

### inp_gen.c
Takes a null terminated ASCII string as input and generates the PIR inputs for the simulator.
Also contains String of 1's used to reset wordlines.
Uses RCt.csv to determine the cycle numbers where Round Constants are loaded to the PIR.

### revamp.py
ReRam crossbar simulator

### config_data.json
Used to specify which files are used for instruction set and input.

## gen_demo_config.py
Used to generate config_data.json
