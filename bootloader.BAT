SET PATH=D:\Keil_v5\ARM\ARMCC\Bin;D:\Program Files\Java\jdk1.8.0_152\bin;C:\ProgramData\Oracle\Java\javapath;C:\Program Files (x86)\Intel\iCLS Client\;C:\Program Files\Intel\iCLS Client\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;D:\Program Files\WIDCOMM\Bluetooth Software\;D:\Program Files\WIDCOMM\Bluetooth Software\syswow64;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\IPT;D:\Program Files\Java\jdk1.8.0_152\jre\bin;C:\Program Files (x86)\STMicroelectronics\STM32 ST-LINK Utility\ST-LINK Utility;d:\Program Files\Git\cmd
SET CPU_TYPE=STM32F103RC
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=bootloader
SET CPU_CLOCK=0x00B71B00
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\mian.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\utils.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\iap.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\usart1.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\flash.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\misc.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_exti.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_flash.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_gpio.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_rcc.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\stm32f10x_usart.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmAsm" --Via ".\objects\startup_stm32f10x_hd._ia"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\objects\system_stm32f10x.__i"
"D:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\Objects\BootLoader.lnp"
"D:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\Objects\BootLoader.axf" --i32combined --output ".\Objects\BootLoader.hex"
