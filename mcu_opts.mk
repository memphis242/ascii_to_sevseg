.POSIX:

# Assign to these Make variables the ARM MCU specific options that the GCC
# toolchain supports (e.g., cpu/architecture target, arm vs thumb, FPU, FP ABI)
CC_ARM_OPTS = -mcpu=cortex-m0plus -mfloat-abi=soft -mthumb
MCU_OPTS = --specs=nosys.specs -static --specs=nano.specs -fstack-usage

# Example for ARM Cortex-M7 MCU (e.g., STM32H743)
# CC_ARM_OPTS = -mcpu=cortex-m7 -mfloat-abi=hard -mthumb
# MCU_OPTS = --specs=nosys.specs -static --specs=nano.specs -fstack-usage