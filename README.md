# The IDA-LET-Machine (ILM)
The ILM is a simple implementation of the logical execution time (LET) paradigm for the automotive domain.
In general it is based on a double buffering, to implement a zero-time communication between different cores.
You can find the doxygen generated documentation [here](https://matthiasb85.github.io/IDA-LET-Machine/files.html "ILM documentation")

The ILM based was developed as an operating system (OS) and hardware independent module.
At the moment, we support the standard OSEK/AUTOSAR OS API as the first OS port was based on ERIKA OS.
The current hardware port is based on the CCU6 module of the AURIX TC2xx which is usually used for PWM generation.

The ILM is developed by the "Institut für Datentechnik und Kommunikationsnetze" (engl: Institute of Computer and
Network Engineering, abbreviation **IDA**) of the TU Braunschweig.
During 2016 and 2017 the development was mainly influenced by a collabortaion between IDA and Daimler RD/EIS.

## Where is the ILM intended for?
Our mission is, to provide a simple and efficient test framework for the LET paradigm.
This framework can be used in academia (e.g. for evaluation) or also for prototyping.
In general the ILM can be used everywhere, where you would like to test something new, but don't want to have a huge ammount of 3rd party software in the background.   

## Where is the ILM not intended for?
Although the license model does not exclude it explicitly, we would recommend not to use the ILM in any kind of series implementation.
We have written the software to the best of our knowledge and belief, nevertheless it may still contain some bugs.
Therefore we can not provide any kind of guarantee for functional correctness.
For this kind of integegration there are several other commercial partners who provide their own implementation.
As an example, Bosch and Continental do both provide an implementation of their interpretation of the LET paradigm. 

## Folder Structure
* **ILM:** Core implementation of the ILM
* **Example:** Example with an generic application, using ERIKA OS on an Infineon AURIX TC275 (TriBoard TC275 or Hitex Shieldbuddy)
* **3rdParty:** Folder for external software (ERIKA OS, Infineon iLLD) including patches and build scripts 

## Where to start?
In order to test the example, you need a build environment for the AURIX microcontroller.
We use a Linux in combination with the HighTech tricore-gcc, but a cygwin installation (as used for ERIKA OS on a Windows) should also do the work.

```
git clone https://github.com/matthiasb85/IDA-LET-Machine.git
cd ./IDA-LET-Machine
cd Example
make
```
The Makefile checks if the 3rdParty software is available, if this is not the case the ./3rdParty/Setup3rdParty.sh script is executed.
The script downloads the corresponding standalone version of ERIKA OS and RT-Druid, and applies some patches on it. 
The hardware port for the AURIX microcontroller uses Infineons iLLD library, which unfortunately is only available after registration.
If the library is not available in ./3rdParty/Download when ./3rdParty/Setup3rdParty.sh is called, the script reports:

```
Can't find Infineon iLLD!
  1.) Please get in contact with Infineon
  2.) Download the AURIX_iLLD_Package_TC2xx_v1.0.1.3.0 driver package
  3.) Copy AURIX_iLLD_Package_TC2xx_v1.0.1.3.0.zip to ./3rdParty/Download
  4.) Run 'make'/'make prepare' in ./Example  or Setup3rdPartySoftware.sh in ./3rdParty
```
An important constraint is, that the entire library is available as source code. 
A Bug inside the official CCU6 driver of the iLLD (which is patched during ./3rdParty/Setup3rdParty.sh) is the reason for this constrain.t

## Application example
The application consist of 18 LET tasks.
The layout of the example application can be found in ./Example/ilm_example.ods
The example uses a setup with three application cores.
As the used AURIX microcontroller provides three cores, we use core C0 to generate the needed IRQ pattern.
In addition, the application tasks are executed on all three cores.
The worst-case execution time (WCET) of the corresponding block is assigned to an LET task on both application cores. 
If no function block is assigned to an LET task on C0, C1 or C2, the corresponding WCET is zero. 
In order to simulate an accurate timing behavior of the function blocks, we used an optimized **nop** loop consuming CPU time.
Due to the different periods of the system, the hyperperiod is 100ms.

During execution of the simulated function blocks, we use pin toggles to indentify the current states.
Those pin toggles are issued through the ILM hooks and at execution begin/end of a function block.
The physical pin magging is located in ./Example/IO/gpio.c and the hook functions in ./Example/ILM/ilm_hooks.c

If you use a Lauterbach Trace32 based setup, you can use the ''make debug'' command inside ./Example to start a debug session.
With ''t32_folder'', ''t32_arch`` and ''addr'' you can pass Trace32 base folder, host CPU architecure and IP address (DNS name) of your trace hardware to the system.
If you don't pass a parameter for ''addr'', Trace32 will search for an USB coupled device.
As an example, the ''make debug'' call on my PC looks like this:
```
make debug t32_folder=/home/matthiasb/opt/t32/files t32_arch=pc_linux addr=lauterbach1
```