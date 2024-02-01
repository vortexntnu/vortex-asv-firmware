
What are Registers?
	Registers are the basic building blocks of the firmware. Each microcontroller has a set of Special Function Registers
	(SFRs) that control the operation of the microcontroller. These registers are memory locations that are mapped into the
	microcontroller's address space. The firmware accesses these registers to control the operation of the microcontroller.
	AVR microcontrollers have 32 general purpose registers (R0-R31) and 64 I/O registers (0x00-0x3F). The 32 general purpose
	registers are used for arithmetic and logic operations. The 64 I/O registers are used to control the operation of the
	Tontroller. 
	The I/O registers control the behaviour of the microcontroller's peripherals. For example, the I/O
	registers control the operation of the UART, SPI, I2C peripherals, and general purpose I/O pins. 
	Each I/O register is 8-bits wide and is mapped into the microcontroller's address space. Each register is represented by
	a port name and a port address. Each port has control over 1 to 8 pins. 
	For example, in the ATmega2560, the PORTA register controls the operation of pins PA0-PA7. These are the same as 
	Arduino pins 22-29. The PORTA register is located at address 0x22. The PORTA register is 8-bits wide. 
	Each bit in the PORTA register controls the operation of one pin. For example, bit 0 of the PORTA register controls the
	operation of pin PA0. Bit 1 of the PORTA register controls the operation of pin PA1. 
	To manipulate the behaviour of a pin, the firmware must manipulate the bits in the I/O registers. In PORTA, for example,
	to set pin PA0 to be an output, the firmware must set bit 0 of PORTA to 1. There are two ways to do this. The first way is
	to use the SBI instruction. The second way is to use the ORI instruction. 
	The SBI instruction sets a bit in an I/O register. The ORI instruction performs a logical OR operation between a register
	and a constant. The result is stored in the register. 
	For example, to set bit 0 of PORTA to 1, the firmware can use the SBI instruction. The SBI instruction takes two operands.
	The first operand is the I/O register. The second operand is the bit number. The SBI instruction sets the bit number in
	the I/O register to 1. The SBI instruction is shown below.
		SBI PORTA, 0
	To set bit 0 of PORTA to 1, the firmware can also use the ORI instruction. The ORI instruction takes two operands. The
	first operand is the I/O register. The second operand is a constant. The ORI instruction performs a logical OR operation
	between the I/O register and the constant. The result is stored in the I/O register. The ORI instruction is shown below.
		ORI PORTA, 0x01
	To set bit 0 of PORTA to 0, the firmware can use the CBI instruction. The CBI instruction takes two operands. The first
	operand is the I/O register. The second operand is the bit number. The CBI instruction sets the bit number in the I/O
	register to 0. The CBI instruction is shown below.
		CBI PORTA, 0
	To set bit 0 of PORTA to 0, the firmware can also use the ANDI instruction. The ANDI instruction takes two operands. The
	first operand is the I/O register. The second operand is a constant. The ANDI instruction performs a logical AND operation
	between the I/O register and the constant. The result is stored in the I/O register. The ANDI instruction is shown below.
		ANDI PORTA, 0xFE
	To read the value of bit 0 of PORTA, the firmware can use the SBIC instruction. The SBIC instruction takes two operands.
	The first operand is the I/O register. The second operand is the bit number. The SBIC instruction skips the next
	instruction if the bit number in the I/O register is 0. The SBIC instruction is shown below.
		SBIC PORTA, 0
	To read the value of bit 0 of PORTA, the firmware can also use the ANDI instruction. The ANDI instruction takes two
	operands. The first operand is the I/O register. The second operand is a constant. The ANDI instruction performs a logical
	AND operation between the I/O register and the constant. The result is stored in the I/O register. The ANDI instruction
	is shown below.
		ANDI R0, 0x01
