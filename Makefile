kernel_source_files := $(shell find src/kernel -name *.c)
kernel_object_files := $(patsubst src/kernel/%.c, build/kernel/%.o, $(kernel_source_files))

x86_64_c_source_files := $(shell find src/x86_64 -name *.c)
x86_64_c_object_files := $(patsubst src/x86_64/%.c, build/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find src/x86_64/boot -name *.asm)
x86_64_asm_object_files := $(patsubst src/x86_64/boot/%.asm, build/x86_64/boot/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_c_object_files) $(x86_64_asm_object_files)

$(kernel_object_files): build/kernel/%.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	gcc -c -I src/include -ffreestanding -fno-asynchronous-unwind-tables -fno-zero-initialized-in-bss $(patsubst build/kernel/%.o, src/kernel/%.c, $@) -o $@

$(x86_64_c_object_files): build/x86_64/%.o : src/x86_64/%.c
	mkdir -p $(dir $@) && \
	gcc -c -I src/include -ffreestanding -fno-asynchronous-unwind-tables -fno-zero-initialized-in-bss $(patsubst build/x86_64/%.o, src/x86_64/%.c, $@) -o $@

$(x86_64_asm_object_files): build/x86_64/%.o : src/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/boot/%.o, src/x86_64/boot/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(kernel_object_files) $(x86_64_object_files)
	mkdir -p dist/x86_64 && \
	ld -n --no-relax -o dist/x86_64/kernal.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/kernal.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernal.iso targets/x86_64/iso

.PHONY: clean-x86_64
clean-x86_64:
	rm $(kernel_object_files) $(x86_64_object_files)
