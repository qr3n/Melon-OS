from os import *

SRC = "src"
OBJ = "obj"
BIN = "bin"

# Bootloader
BOOTLOADER = "boot.asm"

# Kernel
LINK_SCRIPT = "link.ld"

# Program
PROGRAM = "testProgram.asm"

KERNEL = {
    "ASM_FILES": [
        "entry.asm",
    ],

    "CPP_FILES": [
        "kernel.cpp",
        "Managers/Output/Output.cpp",
        "Managers/Disk/Disk.cpp",
        "Managers/Interrupts/Interrupts.cpp",
        "Managers/Programs/Programs.cpp",

        "utils/ports/ports.cpp"
    ]
}

# Compiling
index = 0

def build(files, flags):
    global index
    for file in files:
        system(f"{flags} -o {OBJ}/{str(index)}.o {SRC}/kernel/{file}")
        index += 1

system(f"nasm -f bin {SRC}/{BOOTLOADER} -o {BIN}/boot.bin")
system(f"nasm -fbin {SRC}/{PROGRAM} -o {BIN}/{PROGRAM}.bin")

build(KERNEL["ASM_FILES"], "nasm -f elf32")
build(KERNEL["CPP_FILES"], "g++ -m32 -fno-pie -fno-stack-protector -mno-red-zone -mgeneral-regs-only -c")

system(f"ld -m elf_i386 -T {LINK_SCRIPT} -o {OBJ}/kernel.o {OBJ}/*.o")
system(f"objcopy -O binary {OBJ}/kernel.o {BIN}/kernel.bin")

system(f"dd if={BIN}/boot.bin of={BIN}/disk.img seek=0 count=1 conv=notrunc")
system(f"dd if={BIN}/kernel.bin of={BIN}/disk.img seek=1 conv=notrunc")
system(f"dd if={BIN}/{PROGRAM}.bin of={BIN}/disk.img seek=9 count=1 conv=notrunc")

system(f"rm {OBJ}/*")

system(f"qemu-system-i386 -drive format=raw,file={BIN}/disk.img -D log.txt")