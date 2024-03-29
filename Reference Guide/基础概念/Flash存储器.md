# Flash 储存器

Flash是存储芯片的一种，通过特定的程序可以修改里面的数据。Flash存储器又称为闪存，它结合了ROM和RAM的长处，不仅具备电子可擦除可编程(EEPROM)的性能，还不会断电丢失数据，同时可以快速读取数据(NVRAM的优势)。U盘和MP3里用的就是这种存储器。嵌入式系统以前一直使用ROM(ERROM)作为他们的存储设备，20世纪90年代中期开始，Flash全面代替了ROM(EEPROM)在嵌入式系统中的地位，用作存储程序代码或者Bootloader及操作系统，现在则直接当U盘使用。

目前Flash主要有两种NOR Flash和NAND Flash。NOR Flash的读取和我们常见的SDRAM的读取是一样的，用户可以直接运行装载在 NOR Flash 里的代码，这样可以减少SRAM的容量，从而节约了成本。NAND Flash没有采取随机读取技术，它的读取是以一次读取一块的形式来进行的，通常是一次读取512字节，采用这种技术的Flash比较廉价。用户不能直接运行 NAND Flash 上的代码，因此使用NAND Flash的嵌入式系统开发板除了使用NAND Flash以外，还做上了一块小的NOR Flash来运行启动代码。

一般小容量的用 NOR Flash，因为其读取速度快，多用来存储操作系统等重要信息，而大容量的用NAND Flash，最常见的NAND Flash应用是嵌入式系统采用的DOC(Disk On Chip)和我们通常用的“闪盘”,可以在线擦除。目前市面上的Flash主要来自Intel，AMD，Fujitsu和Mxic，而生产NAND Flash的主要厂家有Samsung和Toshiba及Hynix。
