--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Command: generate_target bd_71cc.bd
--Design : bd_71cc
--Purpose: IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity bd_71cc is
  port (
    SLOT_0_IIC_scl_i : in STD_LOGIC;
    SLOT_0_IIC_scl_o : in STD_LOGIC;
    SLOT_0_IIC_scl_t : in STD_LOGIC;
    SLOT_0_IIC_sda_i : in STD_LOGIC;
    SLOT_0_IIC_sda_o : in STD_LOGIC;
    SLOT_0_IIC_sda_t : in STD_LOGIC;
    SLOT_1_UART_rxd : in STD_LOGIC;
    SLOT_1_UART_txd : in STD_LOGIC;
    SLOT_2_SPI_io0_i : in STD_LOGIC;
    SLOT_2_SPI_io0_o : in STD_LOGIC;
    SLOT_2_SPI_io0_t : in STD_LOGIC;
    SLOT_2_SPI_io1_i : in STD_LOGIC;
    SLOT_2_SPI_io1_o : in STD_LOGIC;
    SLOT_2_SPI_io1_t : in STD_LOGIC;
    SLOT_2_SPI_sck_i : in STD_LOGIC;
    SLOT_2_SPI_sck_o : in STD_LOGIC;
    SLOT_2_SPI_sck_t : in STD_LOGIC;
    SLOT_2_SPI_ss_i : in STD_LOGIC;
    SLOT_2_SPI_ss_o : in STD_LOGIC;
    SLOT_2_SPI_ss_t : in STD_LOGIC;
    SLOT_3_SPI_io0_i : in STD_LOGIC;
    SLOT_3_SPI_io0_o : in STD_LOGIC;
    SLOT_3_SPI_io0_t : in STD_LOGIC;
    SLOT_3_SPI_io1_i : in STD_LOGIC;
    SLOT_3_SPI_io1_o : in STD_LOGIC;
    SLOT_3_SPI_io1_t : in STD_LOGIC;
    SLOT_3_SPI_sck_i : in STD_LOGIC;
    SLOT_3_SPI_sck_o : in STD_LOGIC;
    SLOT_3_SPI_sck_t : in STD_LOGIC;
    SLOT_3_SPI_ss_i : in STD_LOGIC;
    SLOT_3_SPI_ss_o : in STD_LOGIC;
    SLOT_3_SPI_ss_t : in STD_LOGIC;
    clk : in STD_LOGIC
  );
  attribute CORE_GENERATION_INFO : string;
  attribute CORE_GENERATION_INFO of bd_71cc : entity is "bd_71cc,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=bd_71cc,x_ipVersion=1.00.a,x_ipLanguage=VHDL,numBlks=1,numReposBlks=1,numNonXlnxBlks=0,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=SBD,synth_mode=Global}";
  attribute HW_HANDOFF : string;
  attribute HW_HANDOFF of bd_71cc : entity is "zusys_system_ila_0_0.hwdef";
end bd_71cc;

architecture STRUCTURE of bd_71cc is
  component bd_71cc_ila_lib_0 is
  port (
    clk : in STD_LOGIC;
    probe0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe3 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe4 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe5 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe6 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe7 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe8 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe9 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe10 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe11 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe12 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe13 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe14 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe15 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe16 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe17 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe18 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe19 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe20 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe21 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe22 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe23 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe24 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe25 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe26 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe27 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe28 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe29 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe30 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe31 : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component bd_71cc_ila_lib_0;
  signal SLOT_0_IIC_scl_i_1 : STD_LOGIC;
  signal SLOT_0_IIC_scl_o_1 : STD_LOGIC;
  signal SLOT_0_IIC_scl_t_1 : STD_LOGIC;
  signal SLOT_0_IIC_sda_i_1 : STD_LOGIC;
  signal SLOT_0_IIC_sda_o_1 : STD_LOGIC;
  signal SLOT_0_IIC_sda_t_1 : STD_LOGIC;
  signal SLOT_1_UART_rxd_1 : STD_LOGIC;
  signal SLOT_1_UART_txd_1 : STD_LOGIC;
  signal SLOT_2_SPI_io0_i_1 : STD_LOGIC;
  signal SLOT_2_SPI_io0_o_1 : STD_LOGIC;
  signal SLOT_2_SPI_io0_t_1 : STD_LOGIC;
  signal SLOT_2_SPI_io1_i_1 : STD_LOGIC;
  signal SLOT_2_SPI_io1_o_1 : STD_LOGIC;
  signal SLOT_2_SPI_io1_t_1 : STD_LOGIC;
  signal SLOT_2_SPI_sck_i_1 : STD_LOGIC;
  signal SLOT_2_SPI_sck_o_1 : STD_LOGIC;
  signal SLOT_2_SPI_sck_t_1 : STD_LOGIC;
  signal SLOT_2_SPI_ss_i_1 : STD_LOGIC;
  signal SLOT_2_SPI_ss_o_1 : STD_LOGIC;
  signal SLOT_2_SPI_ss_t_1 : STD_LOGIC;
  signal SLOT_3_SPI_io0_i_1 : STD_LOGIC;
  signal SLOT_3_SPI_io0_o_1 : STD_LOGIC;
  signal SLOT_3_SPI_io0_t_1 : STD_LOGIC;
  signal SLOT_3_SPI_io1_i_1 : STD_LOGIC;
  signal SLOT_3_SPI_io1_o_1 : STD_LOGIC;
  signal SLOT_3_SPI_io1_t_1 : STD_LOGIC;
  signal SLOT_3_SPI_sck_i_1 : STD_LOGIC;
  signal SLOT_3_SPI_sck_o_1 : STD_LOGIC;
  signal SLOT_3_SPI_sck_t_1 : STD_LOGIC;
  signal SLOT_3_SPI_ss_i_1 : STD_LOGIC;
  signal SLOT_3_SPI_ss_o_1 : STD_LOGIC;
  signal SLOT_3_SPI_ss_t_1 : STD_LOGIC;
  signal clk_1 : STD_LOGIC;
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of SLOT_0_IIC_scl_i : signal is "xilinx.com:interface:iic:1.0 SLOT_0_IIC SCL_I";
  attribute X_INTERFACE_INFO of SLOT_0_IIC_scl_o : signal is "xilinx.com:interface:iic:1.0 SLOT_0_IIC SCL_O";
  attribute X_INTERFACE_INFO of SLOT_0_IIC_scl_t : signal is "xilinx.com:interface:iic:1.0 SLOT_0_IIC SCL_T";
  attribute X_INTERFACE_INFO of SLOT_0_IIC_sda_i : signal is "xilinx.com:interface:iic:1.0 SLOT_0_IIC SDA_I";
  attribute X_INTERFACE_INFO of SLOT_0_IIC_sda_o : signal is "xilinx.com:interface:iic:1.0 SLOT_0_IIC SDA_O";
  attribute X_INTERFACE_INFO of SLOT_0_IIC_sda_t : signal is "xilinx.com:interface:iic:1.0 SLOT_0_IIC SDA_T";
  attribute X_INTERFACE_INFO of SLOT_1_UART_rxd : signal is "xilinx.com:interface:uart:1.0 SLOT_1_UART RxD";
  attribute X_INTERFACE_INFO of SLOT_1_UART_txd : signal is "xilinx.com:interface:uart:1.0 SLOT_1_UART TxD";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_io0_i : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI IO0_I";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_io0_o : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI IO0_O";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_io0_t : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI IO0_T";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_io1_i : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI IO1_I";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_io1_o : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI IO1_O";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_io1_t : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI IO1_T";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_sck_i : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI SCK_I";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_sck_o : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI SCK_O";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_sck_t : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI SCK_T";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_ss_i : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI SS_I";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_ss_o : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI SS_O";
  attribute X_INTERFACE_INFO of SLOT_2_SPI_ss_t : signal is "xilinx.com:interface:spi:1.0 SLOT_2_SPI SS_T";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_io0_i : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI IO0_I";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_io0_o : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI IO0_O";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_io0_t : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI IO0_T";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_io1_i : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI IO1_I";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_io1_o : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI IO1_O";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_io1_t : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI IO1_T";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_sck_i : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI SCK_I";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_sck_o : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI SCK_O";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_sck_t : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI SCK_T";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_ss_i : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI SS_I";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_ss_o : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI SS_O";
  attribute X_INTERFACE_INFO of SLOT_3_SPI_ss_t : signal is "xilinx.com:interface:spi:1.0 SLOT_3_SPI SS_T";
  attribute X_INTERFACE_INFO of clk : signal is "xilinx.com:signal:clock:1.0 CLK.CLK CLK";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of clk : signal is "XIL_INTERFACENAME CLK.CLK, CLK_DOMAIN zusys_clk_wiz_0_0_clk_out1, FREQ_HZ 20000000, INSERT_VIP 0, PHASE 0.0";
begin
  SLOT_0_IIC_scl_i_1 <= SLOT_0_IIC_scl_i;
  SLOT_0_IIC_scl_o_1 <= SLOT_0_IIC_scl_o;
  SLOT_0_IIC_scl_t_1 <= SLOT_0_IIC_scl_t;
  SLOT_0_IIC_sda_i_1 <= SLOT_0_IIC_sda_i;
  SLOT_0_IIC_sda_o_1 <= SLOT_0_IIC_sda_o;
  SLOT_0_IIC_sda_t_1 <= SLOT_0_IIC_sda_t;
  SLOT_1_UART_rxd_1 <= SLOT_1_UART_rxd;
  SLOT_1_UART_txd_1 <= SLOT_1_UART_txd;
  SLOT_2_SPI_io0_i_1 <= SLOT_2_SPI_io0_i;
  SLOT_2_SPI_io0_o_1 <= SLOT_2_SPI_io0_o;
  SLOT_2_SPI_io0_t_1 <= SLOT_2_SPI_io0_t;
  SLOT_2_SPI_io1_i_1 <= SLOT_2_SPI_io1_i;
  SLOT_2_SPI_io1_o_1 <= SLOT_2_SPI_io1_o;
  SLOT_2_SPI_io1_t_1 <= SLOT_2_SPI_io1_t;
  SLOT_2_SPI_sck_i_1 <= SLOT_2_SPI_sck_i;
  SLOT_2_SPI_sck_o_1 <= SLOT_2_SPI_sck_o;
  SLOT_2_SPI_sck_t_1 <= SLOT_2_SPI_sck_t;
  SLOT_2_SPI_ss_i_1 <= SLOT_2_SPI_ss_i;
  SLOT_2_SPI_ss_o_1 <= SLOT_2_SPI_ss_o;
  SLOT_2_SPI_ss_t_1 <= SLOT_2_SPI_ss_t;
  SLOT_3_SPI_io0_i_1 <= SLOT_3_SPI_io0_i;
  SLOT_3_SPI_io0_o_1 <= SLOT_3_SPI_io0_o;
  SLOT_3_SPI_io0_t_1 <= SLOT_3_SPI_io0_t;
  SLOT_3_SPI_io1_i_1 <= SLOT_3_SPI_io1_i;
  SLOT_3_SPI_io1_o_1 <= SLOT_3_SPI_io1_o;
  SLOT_3_SPI_io1_t_1 <= SLOT_3_SPI_io1_t;
  SLOT_3_SPI_sck_i_1 <= SLOT_3_SPI_sck_i;
  SLOT_3_SPI_sck_o_1 <= SLOT_3_SPI_sck_o;
  SLOT_3_SPI_sck_t_1 <= SLOT_3_SPI_sck_t;
  SLOT_3_SPI_ss_i_1 <= SLOT_3_SPI_ss_i;
  SLOT_3_SPI_ss_o_1 <= SLOT_3_SPI_ss_o;
  SLOT_3_SPI_ss_t_1 <= SLOT_3_SPI_ss_t;
  clk_1 <= clk;
ila_lib: component bd_71cc_ila_lib_0
     port map (
      clk => clk_1,
      probe0(0) => SLOT_0_IIC_scl_i_1,
      probe1(0) => SLOT_0_IIC_scl_o_1,
      probe10(0) => SLOT_2_SPI_sck_t_1,
      probe11(0) => SLOT_2_SPI_io1_i_1,
      probe12(0) => SLOT_2_SPI_io0_o_1,
      probe13(0) => SLOT_2_SPI_io0_t_1,
      probe14(0) => SLOT_2_SPI_io0_i_1,
      probe15(0) => SLOT_2_SPI_io1_o_1,
      probe16(0) => SLOT_2_SPI_io1_t_1,
      probe17(0) => SLOT_2_SPI_ss_i_1,
      probe18(0) => SLOT_2_SPI_ss_o_1,
      probe19(0) => SLOT_2_SPI_ss_t_1,
      probe2(0) => SLOT_0_IIC_scl_t_1,
      probe20(0) => SLOT_3_SPI_sck_i_1,
      probe21(0) => SLOT_3_SPI_sck_o_1,
      probe22(0) => SLOT_3_SPI_sck_t_1,
      probe23(0) => SLOT_3_SPI_io1_i_1,
      probe24(0) => SLOT_3_SPI_io0_o_1,
      probe25(0) => SLOT_3_SPI_io0_t_1,
      probe26(0) => SLOT_3_SPI_io0_i_1,
      probe27(0) => SLOT_3_SPI_io1_o_1,
      probe28(0) => SLOT_3_SPI_io1_t_1,
      probe29(0) => SLOT_3_SPI_ss_i_1,
      probe3(0) => SLOT_0_IIC_sda_i_1,
      probe30(0) => SLOT_3_SPI_ss_o_1,
      probe31(0) => SLOT_3_SPI_ss_t_1,
      probe4(0) => SLOT_0_IIC_sda_o_1,
      probe5(0) => SLOT_0_IIC_sda_t_1,
      probe6(0) => SLOT_1_UART_txd_1,
      probe7(0) => SLOT_1_UART_rxd_1,
      probe8(0) => SLOT_2_SPI_sck_i_1,
      probe9(0) => SLOT_2_SPI_sck_o_1
    );
end STRUCTURE;
