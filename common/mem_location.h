#ifndef __MEM_LOCATION_H__
#define __MEM_LOCATION_H__

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_SEC_CONCAT_2(a, b)          a.b
#define HAL_SEC_CONCAT_3(a, b, c)       a.b.c
#define HAL_SEC_TO_STR_A(s)             #s
#define HAL_SEC_TO_STR(s)               HAL_SEC_TO_STR_A(s)
#define HAL_SEC_NAME_ATTR(s)            __attribute__((section(s)))

#define HAL_SEC_DEF(section, name)      HAL_SEC_NAME_ATTR(HAL_SEC_TO_STR(HAL_SEC_CONCAT_2(section, name))) name
#define HAL_SEC_LOC(section)            HAL_SEC_NAME_ATTR(HAL_SEC_TO_STR(HAL_SEC_CONCAT_2(section, __LINE__)))

#if defined(__GNUC__) && !(defined(PROGRAMMER))
#define BOOT_TEXT_SRAM_LOC              HAL_SEC_LOC(.boot_text_sram)
#define BOOT_TEXT_SRAM_DEF(n)           HAL_SEC_DEF(.boot_text_sram, n)
#define BOOT_TEXT_FLASH_LOC             HAL_SEC_LOC(.boot_text_flash)
#define BOOT_TEXT_FLASH_DEF(n)          HAL_SEC_DEF(.boot_text_flash, n)
#define BOOT_RODATA_SRAM_LOC            HAL_SEC_LOC(.boot_rodata_sram)
#define BOOT_RODATA_SRAM_DEF(n)         HAL_SEC_DEF(.boot_rodata_sram, n)
#define BOOT_RODATA_FLASH_LOC           HAL_SEC_LOC(.boot_rodata_flash)
#define BOOT_RODATA_FLASH_DEF(n)        HAL_SEC_DEF(.boot_rodata_flash, n)
#define BOOT_DATA_LOC                   HAL_SEC_LOC(.boot_data)
#define BOOT_DATA_DEF(n)                HAL_SEC_DEF(.boot_data, n)
#define BOOT_BSS_LOC                    HAL_SEC_LOC(.boot_bss)
#define BOOT_BSS_DEF(n)                 HAL_SEC_DEF(.boot_bss, n)

#define SRAM_TEXT_LOC                   HAL_SEC_LOC(.sram_text)
#define SRAM_TEXT_DEF(n)                HAL_SEC_DEF(.sram_text, n)
#define SRAM_DATA_LOC                   HAL_SEC_LOC(.sram_data)
#define SRAM_DATA_DEF(n)                HAL_SEC_DEF(.sram_data, n)
#define SRAM_STACK_LOC                  ALIGNED(8) HAL_SEC_LOC(.sram_data)
#define SRAM_STACK_DEF(n)               ALIGNED(8) HAL_SEC_LOC(.sram_data, n)
#define SRAM_BSS_LOC                    HAL_SEC_LOC(.sram_bss)
#define SRAM_BSS_DEF(n)                 HAL_SEC_DEF(.sram_bss, n)

#define FRAM_TEXT_LOC                   HAL_SEC_LOC(.fast_text_sram)
#define FRAM_TEXT_DEF(n)                HAL_SEC_DEF(.fast_text_sram, n)

#define FLASH_TEXT_LOC                  HAL_SEC_LOC(.flash_text)
#define FLASH_TEXT_DEF(n)               HAL_SEC_DEF(.flash_text, n)
#define FLASH_RODATA_LOC                HAL_SEC_LOC(.flash_rodata)
#define FLASH_RODATA_DEF(n)             HAL_SEC_DEF(.flash_rodata, n)

#define REBOOT_CUSTOM_PARAM_LOC         HAL_SEC_LOC(.reboot_custom_param)
#define REBOOT_CUSTOM_PARAM_DEF         HAL_SEC_DEF(.reboot_custom_param)
#else

#define BOOT_TEXT_SRAM_LOC
#define BOOT_TEXT_SRAM_DEF(n)           n
#define BOOT_TEXT_FLASH_LOC
#define BOOT_TEXT_FLASH_DEF(n)          n
#define BOOT_RODATA_SRAM_LOC
#define BOOT_RODATA_SRAM_DEF(n)         n
#define BOOT_RODATA_FLASH_LOC
#define BOOT_RODATA_FLASH_DEF(n)        n
#define BOOT_DATA_LOC
#define BOOT_DATA_DEF(n)                n
#define BOOT_BSS_LOC
#define BOOT_BSS_DEF(n)                 n

#define SRAM_TEXT_LOC
#define SRAM_TEXT_DEF(n)                n
#define SRAM_DATA_LOC
#define SRAM_DATA_DEF(n)                n
#define SRAM_STACK_LOC
#define SRAM_STACK_DEF(n)               n
#define SRAM_BSS_LOC
#define SRAM_BSS_DEF(n)                 n

#define FRAM_TEXT_LOC
#define FRAM_TEXT_DEF(n)                n

#define FLASH_TEXT_LOC
#define FLASH_TEXT_DEF(n)               n
#define FLASH_RODATA_LOC
#define FLASH_RODATA_DEF(n)             n

#define REBOOT_CUSTOM_PARAM_LOC
#define REBOOT_CUSTOM_PARAM_DEF(n)      n

#endif // !__GNUC__ || PROGRAMMER

#ifdef __cplusplus
}
#endif

#endif
