/* Generated by firmware/Makefile */
    .section .rodata
    .p2align 2
_fw_keyspan_usa28x_fw_bin:
    .incbin "firmware/keyspan/usa28x.fw"
_fw_end:
   .section .rodata.str,"aMS",@progbits,1
    .p2align 2
_fw_keyspan_usa28x_fw_name:
    .string "keyspan/usa28x.fw"
    .section .builtin_fw,"a",@progbits
    .p2align 2
    .long _fw_keyspan_usa28x_fw_name
    .long _fw_keyspan_usa28x_fw_bin
    .long _fw_end - _fw_keyspan_usa28x_fw_bin
