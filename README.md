# SHA-3 Using Revamp

## Keccak-f1600.ins
This file contains the composite instruction set.
Currently contains Load stage, Theta stage, Rho stage and Pi stage.

## load_helper.c
Used to generate the Load stage instruction set.

## Theta_helper.c
Used to generate the Theta stage instruction set.

## RhoPi_helper.c
Used to generate Rho and Pi stages instruction sets.

## inp_gen.c
Used to randomly generate PIR inputs for the initial SHA-3 states.
Also contains String of 1 used to reset wordlines
