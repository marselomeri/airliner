--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2019.2 (lin64) Build 2708876 Wed Nov  6 21:39:14 MST 2019
--Date        : Wed Aug 19 03:53:33 2020
--Host        : vagrant running 64-bit Ubuntu 16.04.6 LTS
--Command     : generate_target zusys.bd
--Design      : zusys
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys is
  port (
    IIC_1_0_scl_i : in STD_LOGIC;
    IIC_1_0_scl_o : out STD_LOGIC;
    IIC_1_0_scl_t : out STD_LOGIC;
    IIC_1_0_sda_i : in STD_LOGIC;
    IIC_1_0_sda_o : out STD_LOGIC;
    IIC_1_0_sda_t : out STD_LOGIC;
    SI5338_CLK0_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK0_D_clk_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    SPI_0_0_io0_i : in STD_LOGIC;
    SPI_0_0_io0_o : out STD_LOGIC;
    SPI_0_0_io0_t : out STD_LOGIC;
    SPI_0_0_io1_i : in STD_LOGIC;
    SPI_0_0_io1_o : out STD_LOGIC;
    SPI_0_0_io1_t : out STD_LOGIC;
    SPI_0_0_sck_i : in STD_LOGIC;
    SPI_0_0_sck_o : out STD_LOGIC;
    SPI_0_0_sck_t : out STD_LOGIC;
    SPI_0_0_ss_i : in STD_LOGIC;
    SPI_0_0_ss_o : out STD_LOGIC;
    SPI_0_0_ss_t : out STD_LOGIC;
    SPI_1_0_io0_i : in STD_LOGIC;
    SPI_1_0_io0_o : out STD_LOGIC;
    SPI_1_0_io0_t : out STD_LOGIC;
    SPI_1_0_io1_i : in STD_LOGIC;
    SPI_1_0_io1_o : out STD_LOGIC;
    SPI_1_0_io1_t : out STD_LOGIC;
    SPI_1_0_sck_i : in STD_LOGIC;
    SPI_1_0_sck_o : out STD_LOGIC;
    SPI_1_0_sck_t : out STD_LOGIC;
    SPI_1_0_ss_i : in STD_LOGIC;
    SPI_1_0_ss_o : out STD_LOGIC;
    SPI_1_0_ss_t : out STD_LOGIC;
    UART_1_0_rxd : in STD_LOGIC;
    UART_1_0_txd : out STD_LOGIC;
    x0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    x1 : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute core_generation_info : string;
  attribute core_generation_info of zusys : entity is "zusys,IP_Integrator,{x_ipVendor=xilinx.com,x_ipLibrary=BlockDiagram,x_ipName=zusys,x_ipVersion=1.00.a,x_ipLanguage=VHDL,numBlks=7,numReposBlks=7,numNonXlnxBlks=1,numHierBlks=0,maxHierDepth=0,numSysgenBlks=0,numHlsBlks=0,numHdlrefBlks=0,numPkgbdBlks=0,bdsource=USER,da_zynq_ultra_ps_e_cnt=1,synth_mode=OOC_per_IP}";
  attribute hw_handoff : string;
  attribute hw_handoff of zusys : entity is "zusys.hwdef";
end zusys;

architecture STRUCTURE of zusys is
  component zusys_labtools_fmeter_0_0 is
  port (
    refclk : in STD_LOGIC;
    fin : in STD_LOGIC_VECTOR ( 0 to 0 );
    F0 : out STD_LOGIC_VECTOR ( 31 downto 0 );
    update : out STD_LOGIC
  );
  end component zusys_labtools_fmeter_0_0;
  component zusys_util_ds_buf_0_0 is
  port (
    IBUF_DS_P : in STD_LOGIC_VECTOR ( 0 to 0 );
    IBUF_DS_N : in STD_LOGIC_VECTOR ( 0 to 0 );
    IBUF_OUT : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_util_ds_buf_0_0;
  component zusys_vio_0_0 is
  port (
    clk : in STD_LOGIC;
    probe_in0 : in STD_LOGIC_VECTOR ( 31 downto 0 );
    probe_in1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe_in2 : in STD_LOGIC_VECTOR ( 0 to 0 );
    probe_in3 : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_vio_0_0;
  component zusys_xlconcat_0_0 is
  port (
    In0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    dout : out STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys_xlconcat_0_0;
  component zusys_zynq_ultra_ps_e_0_0 is
  port (
    maxihpm0_lpd_aclk : in STD_LOGIC;
    maxigp2_awid : out STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_awaddr : out STD_LOGIC_VECTOR ( 39 downto 0 );
    maxigp2_awlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    maxigp2_awsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    maxigp2_awburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    maxigp2_awlock : out STD_LOGIC;
    maxigp2_awcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    maxigp2_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    maxigp2_awvalid : out STD_LOGIC;
    maxigp2_awuser : out STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_awready : in STD_LOGIC;
    maxigp2_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    maxigp2_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    maxigp2_wlast : out STD_LOGIC;
    maxigp2_wvalid : out STD_LOGIC;
    maxigp2_wready : in STD_LOGIC;
    maxigp2_bid : in STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    maxigp2_bvalid : in STD_LOGIC;
    maxigp2_bready : out STD_LOGIC;
    maxigp2_arid : out STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_araddr : out STD_LOGIC_VECTOR ( 39 downto 0 );
    maxigp2_arlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    maxigp2_arsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    maxigp2_arburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    maxigp2_arlock : out STD_LOGIC;
    maxigp2_arcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    maxigp2_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    maxigp2_arvalid : out STD_LOGIC;
    maxigp2_aruser : out STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_arready : in STD_LOGIC;
    maxigp2_rid : in STD_LOGIC_VECTOR ( 15 downto 0 );
    maxigp2_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    maxigp2_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    maxigp2_rlast : in STD_LOGIC;
    maxigp2_rvalid : in STD_LOGIC;
    maxigp2_rready : out STD_LOGIC;
    maxigp2_awqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    maxigp2_arqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    emio_i2c1_scl_i : in STD_LOGIC;
    emio_i2c1_scl_o : out STD_LOGIC;
    emio_i2c1_scl_t : out STD_LOGIC;
    emio_i2c1_sda_i : in STD_LOGIC;
    emio_i2c1_sda_o : out STD_LOGIC;
    emio_i2c1_sda_t : out STD_LOGIC;
    emio_uart1_txd : out STD_LOGIC;
    emio_uart1_rxd : in STD_LOGIC;
    emio_spi0_sclk_i : in STD_LOGIC;
    emio_spi0_sclk_o : out STD_LOGIC;
    emio_spi0_sclk_t : out STD_LOGIC;
    emio_spi0_m_i : in STD_LOGIC;
    emio_spi0_m_o : out STD_LOGIC;
    emio_spi0_mo_t : out STD_LOGIC;
    emio_spi0_s_i : in STD_LOGIC;
    emio_spi0_s_o : out STD_LOGIC;
    emio_spi0_so_t : out STD_LOGIC;
    emio_spi0_ss_i_n : in STD_LOGIC;
    emio_spi0_ss_o_n : out STD_LOGIC;
    emio_spi0_ss_n_t : out STD_LOGIC;
    emio_spi1_sclk_i : in STD_LOGIC;
    emio_spi1_sclk_o : out STD_LOGIC;
    emio_spi1_sclk_t : out STD_LOGIC;
    emio_spi1_m_i : in STD_LOGIC;
    emio_spi1_m_o : out STD_LOGIC;
    emio_spi1_mo_t : out STD_LOGIC;
    emio_spi1_s_i : in STD_LOGIC;
    emio_spi1_s_o : out STD_LOGIC;
    emio_spi1_so_t : out STD_LOGIC;
    emio_spi1_ss_i_n : in STD_LOGIC;
    emio_spi1_ss_o_n : out STD_LOGIC;
    emio_spi1_ss_n_t : out STD_LOGIC;
    pl_resetn0 : out STD_LOGIC;
    pl_clk0 : out STD_LOGIC
  );
  end component zusys_zynq_ultra_ps_e_0_0;
  component zusys_system_ila_0_0 is
  port (
    clk : in STD_LOGIC;
    SLOT_0_IIC_scl_i : in STD_LOGIC;
    SLOT_0_IIC_scl_o : in STD_LOGIC;
    SLOT_0_IIC_scl_t : in STD_LOGIC;
    SLOT_0_IIC_sda_i : in STD_LOGIC;
    SLOT_0_IIC_sda_o : in STD_LOGIC;
    SLOT_0_IIC_sda_t : in STD_LOGIC;
    SLOT_1_UART_rxd : in STD_LOGIC;
    SLOT_1_UART_txd : in STD_LOGIC;
    SLOT_2_SPI_ss_i : in STD_LOGIC;
    SLOT_2_SPI_ss_o : in STD_LOGIC;
    SLOT_2_SPI_ss_t : in STD_LOGIC;
    SLOT_2_SPI_sck_i : in STD_LOGIC;
    SLOT_2_SPI_sck_o : in STD_LOGIC;
    SLOT_2_SPI_sck_t : in STD_LOGIC;
    SLOT_2_SPI_io0_i : in STD_LOGIC;
    SLOT_2_SPI_io0_o : in STD_LOGIC;
    SLOT_2_SPI_io0_t : in STD_LOGIC;
    SLOT_2_SPI_io1_i : in STD_LOGIC;
    SLOT_2_SPI_io1_o : in STD_LOGIC;
    SLOT_2_SPI_io1_t : in STD_LOGIC;
    SLOT_3_SPI_ss_i : in STD_LOGIC;
    SLOT_3_SPI_ss_o : in STD_LOGIC;
    SLOT_3_SPI_ss_t : in STD_LOGIC;
    SLOT_3_SPI_sck_i : in STD_LOGIC;
    SLOT_3_SPI_sck_o : in STD_LOGIC;
    SLOT_3_SPI_sck_t : in STD_LOGIC;
    SLOT_3_SPI_io0_i : in STD_LOGIC;
    SLOT_3_SPI_io0_o : in STD_LOGIC;
    SLOT_3_SPI_io0_t : in STD_LOGIC;
    SLOT_3_SPI_io1_i : in STD_LOGIC;
    SLOT_3_SPI_io1_o : in STD_LOGIC;
    SLOT_3_SPI_io1_t : in STD_LOGIC
  );
  end component zusys_system_ila_0_0;
  component zusys_clk_wiz_0_0 is
  port (
    clk_in1 : in STD_LOGIC;
    clk_out1 : out STD_LOGIC
  );
  end component zusys_clk_wiz_0_0;
  signal CLK_IN_D_1_CLK_N : STD_LOGIC_VECTOR ( 0 to 0 );
  signal CLK_IN_D_1_CLK_P : STD_LOGIC_VECTOR ( 0 to 0 );
  signal VIO_x0_firmware : STD_LOGIC_VECTOR ( 0 to 0 );
  signal clk_wiz_0_clk_out1 : STD_LOGIC;
  signal fm_SI5338_CLK0_D : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal labtools_fmeter_0_update : STD_LOGIC;
  signal util_ds_buf_0_IBUF_OUT : STD_LOGIC_VECTOR ( 0 to 0 );
  signal x1_phy_led : STD_LOGIC_VECTOR ( 0 to 0 );
  signal xlconcat_0_dout : STD_LOGIC_VECTOR ( 0 to 0 );
  signal zynq_ultra_ps_e_0_IIC_1_SCL_I : STD_LOGIC;
  attribute CONN_BUS_INFO : string;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_IIC_1_SCL_I : signal is "zynq_ultra_ps_e_0_IIC_1 xilinx.com:interface:iic:1.0 None SCL_I";
  attribute DONT_TOUCH : boolean;
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_IIC_1_SCL_I : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_IIC_1_SCL_O : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_IIC_1_SCL_O : signal is "zynq_ultra_ps_e_0_IIC_1 xilinx.com:interface:iic:1.0 None SCL_O";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_IIC_1_SCL_O : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_IIC_1_SCL_T : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_IIC_1_SCL_T : signal is "zynq_ultra_ps_e_0_IIC_1 xilinx.com:interface:iic:1.0 None SCL_T";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_IIC_1_SCL_T : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_IIC_1_SDA_I : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_IIC_1_SDA_I : signal is "zynq_ultra_ps_e_0_IIC_1 xilinx.com:interface:iic:1.0 None SDA_I";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_IIC_1_SDA_I : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_IIC_1_SDA_O : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_IIC_1_SDA_O : signal is "zynq_ultra_ps_e_0_IIC_1 xilinx.com:interface:iic:1.0 None SDA_O";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_IIC_1_SDA_O : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_IIC_1_SDA_T : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_IIC_1_SDA_T : signal is "zynq_ultra_ps_e_0_IIC_1 xilinx.com:interface:iic:1.0 None SDA_T";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_IIC_1_SDA_T : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_IO0_I : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_IO0_I : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None IO0_I";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_IO0_I : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_IO0_O : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_IO0_O : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None IO0_O";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_IO0_O : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_IO0_T : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_IO0_T : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None IO0_T";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_IO0_T : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_IO1_I : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_IO1_I : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None IO1_I";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_IO1_I : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_IO1_O : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_IO1_O : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None IO1_O";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_IO1_O : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_IO1_T : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_IO1_T : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None IO1_T";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_IO1_T : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_SCK_I : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_SCK_I : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None SCK_I";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_SCK_I : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_SCK_O : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_SCK_O : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None SCK_O";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_SCK_O : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_SCK_T : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_SCK_T : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None SCK_T";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_SCK_T : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_SS_I : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_SS_I : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None SS_I";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_SS_I : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_SS_O : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_SS_O : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None SS_O";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_SS_O : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_0_SS_T : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_0_SS_T : signal is "zynq_ultra_ps_e_0_SPI_0 xilinx.com:interface:spi:1.0 None SS_T";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_0_SS_T : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_IO0_I : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_IO0_I : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None IO0_I";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_IO0_I : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_IO0_O : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_IO0_O : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None IO0_O";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_IO0_O : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_IO0_T : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_IO0_T : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None IO0_T";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_IO0_T : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_IO1_I : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_IO1_I : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None IO1_I";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_IO1_I : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_IO1_O : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_IO1_O : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None IO1_O";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_IO1_O : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_IO1_T : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_IO1_T : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None IO1_T";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_IO1_T : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_SCK_I : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_SCK_I : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None SCK_I";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_SCK_I : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_SCK_O : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_SCK_O : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None SCK_O";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_SCK_O : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_SCK_T : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_SCK_T : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None SCK_T";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_SCK_T : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_SS_I : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_SS_I : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None SS_I";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_SS_I : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_SS_O : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_SS_O : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None SS_O";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_SS_O : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_SPI_1_SS_T : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_SPI_1_SS_T : signal is "zynq_ultra_ps_e_0_SPI_1 xilinx.com:interface:spi:1.0 None SS_T";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_SPI_1_SS_T : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_UART_1_RxD : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_UART_1_RxD : signal is "zynq_ultra_ps_e_0_UART_1 xilinx.com:interface:uart:1.0 None RxD";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_UART_1_RxD : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_UART_1_TxD : STD_LOGIC;
  attribute CONN_BUS_INFO of zynq_ultra_ps_e_0_UART_1_TxD : signal is "zynq_ultra_ps_e_0_UART_1 xilinx.com:interface:uart:1.0 None TxD";
  attribute DONT_TOUCH of zynq_ultra_ps_e_0_UART_1_TxD : signal is std.standard.true;
  signal zynq_ultra_ps_e_0_pl_clk1 : STD_LOGIC;
  signal NLW_zynq_ultra_ps_e_0_maxigp2_arlock_UNCONNECTED : STD_LOGIC;
  signal NLW_zynq_ultra_ps_e_0_maxigp2_arvalid_UNCONNECTED : STD_LOGIC;
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awlock_UNCONNECTED : STD_LOGIC;
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awvalid_UNCONNECTED : STD_LOGIC;
  signal NLW_zynq_ultra_ps_e_0_maxigp2_bready_UNCONNECTED : STD_LOGIC;
  signal NLW_zynq_ultra_ps_e_0_maxigp2_rready_UNCONNECTED : STD_LOGIC;
  signal NLW_zynq_ultra_ps_e_0_maxigp2_wlast_UNCONNECTED : STD_LOGIC;
  signal NLW_zynq_ultra_ps_e_0_maxigp2_wvalid_UNCONNECTED : STD_LOGIC;
  signal NLW_zynq_ultra_ps_e_0_pl_resetn0_UNCONNECTED : STD_LOGIC;
  signal NLW_zynq_ultra_ps_e_0_maxigp2_araddr_UNCONNECTED : STD_LOGIC_VECTOR ( 39 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_arburst_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_arcache_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_arid_UNCONNECTED : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_arlen_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_arprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_arqos_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_arsize_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_aruser_UNCONNECTED : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awaddr_UNCONNECTED : STD_LOGIC_VECTOR ( 39 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awburst_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awcache_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awid_UNCONNECTED : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awlen_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awprot_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awqos_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awsize_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_awuser_UNCONNECTED : STD_LOGIC_VECTOR ( 15 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_wdata_UNCONNECTED : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal NLW_zynq_ultra_ps_e_0_maxigp2_wstrb_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  attribute x_interface_info : string;
  attribute x_interface_info of IIC_1_0_scl_i : signal is "xilinx.com:interface:iic:1.0 IIC_1_0 SCL_I";
  attribute x_interface_info of IIC_1_0_scl_o : signal is "xilinx.com:interface:iic:1.0 IIC_1_0 SCL_O";
  attribute x_interface_info of IIC_1_0_scl_t : signal is "xilinx.com:interface:iic:1.0 IIC_1_0 SCL_T";
  attribute x_interface_info of IIC_1_0_sda_i : signal is "xilinx.com:interface:iic:1.0 IIC_1_0 SDA_I";
  attribute x_interface_info of IIC_1_0_sda_o : signal is "xilinx.com:interface:iic:1.0 IIC_1_0 SDA_O";
  attribute x_interface_info of IIC_1_0_sda_t : signal is "xilinx.com:interface:iic:1.0 IIC_1_0 SDA_T";
  attribute x_interface_info of SPI_0_0_io0_i : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 IO0_I";
  attribute x_interface_info of SPI_0_0_io0_o : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 IO0_O";
  attribute x_interface_info of SPI_0_0_io0_t : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 IO0_T";
  attribute x_interface_info of SPI_0_0_io1_i : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 IO1_I";
  attribute x_interface_info of SPI_0_0_io1_o : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 IO1_O";
  attribute x_interface_info of SPI_0_0_io1_t : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 IO1_T";
  attribute x_interface_info of SPI_0_0_sck_i : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 SCK_I";
  attribute x_interface_info of SPI_0_0_sck_o : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 SCK_O";
  attribute x_interface_info of SPI_0_0_sck_t : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 SCK_T";
  attribute x_interface_info of SPI_0_0_ss_i : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 SS_I";
  attribute x_interface_info of SPI_0_0_ss_o : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 SS_O";
  attribute x_interface_info of SPI_0_0_ss_t : signal is "xilinx.com:interface:spi:1.0 SPI_0_0 SS_T";
  attribute x_interface_info of SPI_1_0_io0_i : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 IO0_I";
  attribute x_interface_info of SPI_1_0_io0_o : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 IO0_O";
  attribute x_interface_info of SPI_1_0_io0_t : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 IO0_T";
  attribute x_interface_info of SPI_1_0_io1_i : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 IO1_I";
  attribute x_interface_info of SPI_1_0_io1_o : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 IO1_O";
  attribute x_interface_info of SPI_1_0_io1_t : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 IO1_T";
  attribute x_interface_info of SPI_1_0_sck_i : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 SCK_I";
  attribute x_interface_info of SPI_1_0_sck_o : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 SCK_O";
  attribute x_interface_info of SPI_1_0_sck_t : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 SCK_T";
  attribute x_interface_info of SPI_1_0_ss_i : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 SS_I";
  attribute x_interface_info of SPI_1_0_ss_o : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 SS_O";
  attribute x_interface_info of SPI_1_0_ss_t : signal is "xilinx.com:interface:spi:1.0 SPI_1_0 SS_T";
  attribute x_interface_info of UART_1_0_rxd : signal is "xilinx.com:interface:uart:1.0 UART_1_0 RxD";
  attribute x_interface_info of UART_1_0_txd : signal is "xilinx.com:interface:uart:1.0 UART_1_0 TxD";
  attribute x_interface_info of SI5338_CLK0_D_clk_n : signal is "xilinx.com:interface:diff_clock:1.0 SI5338_CLK0_D CLK_N";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of SI5338_CLK0_D_clk_n : signal is "XIL_INTERFACENAME SI5338_CLK0_D, CAN_DEBUG false, FREQ_HZ 100000000";
  attribute x_interface_info of SI5338_CLK0_D_clk_p : signal is "xilinx.com:interface:diff_clock:1.0 SI5338_CLK0_D CLK_P";
begin
  CLK_IN_D_1_CLK_N(0) <= SI5338_CLK0_D_clk_n(0);
  CLK_IN_D_1_CLK_P(0) <= SI5338_CLK0_D_clk_p(0);
  IIC_1_0_scl_o <= zynq_ultra_ps_e_0_IIC_1_SCL_O;
  IIC_1_0_scl_t <= zynq_ultra_ps_e_0_IIC_1_SCL_T;
  IIC_1_0_sda_o <= zynq_ultra_ps_e_0_IIC_1_SDA_O;
  IIC_1_0_sda_t <= zynq_ultra_ps_e_0_IIC_1_SDA_T;
  SPI_0_0_io0_o <= zynq_ultra_ps_e_0_SPI_0_IO0_O;
  SPI_0_0_io0_t <= zynq_ultra_ps_e_0_SPI_0_IO0_T;
  SPI_0_0_io1_o <= zynq_ultra_ps_e_0_SPI_0_IO1_O;
  SPI_0_0_io1_t <= zynq_ultra_ps_e_0_SPI_0_IO1_T;
  SPI_0_0_sck_o <= zynq_ultra_ps_e_0_SPI_0_SCK_O;
  SPI_0_0_sck_t <= zynq_ultra_ps_e_0_SPI_0_SCK_T;
  SPI_0_0_ss_o <= zynq_ultra_ps_e_0_SPI_0_SS_O;
  SPI_0_0_ss_t <= zynq_ultra_ps_e_0_SPI_0_SS_T;
  SPI_1_0_io0_o <= zynq_ultra_ps_e_0_SPI_1_IO0_O;
  SPI_1_0_io0_t <= zynq_ultra_ps_e_0_SPI_1_IO0_T;
  SPI_1_0_io1_o <= zynq_ultra_ps_e_0_SPI_1_IO1_O;
  SPI_1_0_io1_t <= zynq_ultra_ps_e_0_SPI_1_IO1_T;
  SPI_1_0_sck_o <= zynq_ultra_ps_e_0_SPI_1_SCK_O;
  SPI_1_0_sck_t <= zynq_ultra_ps_e_0_SPI_1_SCK_T;
  SPI_1_0_ss_o <= zynq_ultra_ps_e_0_SPI_1_SS_O;
  SPI_1_0_ss_t <= zynq_ultra_ps_e_0_SPI_1_SS_T;
  UART_1_0_txd <= zynq_ultra_ps_e_0_UART_1_TxD;
  VIO_x0_firmware(0) <= x0(0);
  x1_phy_led(0) <= x1(0);
  zynq_ultra_ps_e_0_IIC_1_SCL_I <= IIC_1_0_scl_i;
  zynq_ultra_ps_e_0_IIC_1_SDA_I <= IIC_1_0_sda_i;
  zynq_ultra_ps_e_0_SPI_0_IO0_I <= SPI_0_0_io0_i;
  zynq_ultra_ps_e_0_SPI_0_IO1_I <= SPI_0_0_io1_i;
  zynq_ultra_ps_e_0_SPI_0_SCK_I <= SPI_0_0_sck_i;
  zynq_ultra_ps_e_0_SPI_0_SS_I <= SPI_0_0_ss_i;
  zynq_ultra_ps_e_0_SPI_1_IO0_I <= SPI_1_0_io0_i;
  zynq_ultra_ps_e_0_SPI_1_IO1_I <= SPI_1_0_io1_i;
  zynq_ultra_ps_e_0_SPI_1_SCK_I <= SPI_1_0_sck_i;
  zynq_ultra_ps_e_0_SPI_1_SS_I <= SPI_1_0_ss_i;
  zynq_ultra_ps_e_0_UART_1_RxD <= UART_1_0_rxd;
clk_wiz_0: component zusys_clk_wiz_0_0
     port map (
      clk_in1 => zynq_ultra_ps_e_0_pl_clk1,
      clk_out1 => clk_wiz_0_clk_out1
    );
labtools_fmeter_0: component zusys_labtools_fmeter_0_0
     port map (
      F0(31 downto 0) => fm_SI5338_CLK0_D(31 downto 0),
      fin(0) => xlconcat_0_dout(0),
      refclk => zynq_ultra_ps_e_0_pl_clk1,
      update => labtools_fmeter_0_update
    );
system_ila_0: component zusys_system_ila_0_0
     port map (
      SLOT_0_IIC_scl_i => zynq_ultra_ps_e_0_IIC_1_SCL_I,
      SLOT_0_IIC_scl_o => zynq_ultra_ps_e_0_IIC_1_SCL_O,
      SLOT_0_IIC_scl_t => zynq_ultra_ps_e_0_IIC_1_SCL_T,
      SLOT_0_IIC_sda_i => zynq_ultra_ps_e_0_IIC_1_SDA_I,
      SLOT_0_IIC_sda_o => zynq_ultra_ps_e_0_IIC_1_SDA_O,
      SLOT_0_IIC_sda_t => zynq_ultra_ps_e_0_IIC_1_SDA_T,
      SLOT_1_UART_rxd => zynq_ultra_ps_e_0_UART_1_RxD,
      SLOT_1_UART_txd => zynq_ultra_ps_e_0_UART_1_TxD,
      SLOT_2_SPI_io0_i => zynq_ultra_ps_e_0_SPI_0_IO0_I,
      SLOT_2_SPI_io0_o => zynq_ultra_ps_e_0_SPI_0_IO0_O,
      SLOT_2_SPI_io0_t => zynq_ultra_ps_e_0_SPI_0_IO0_T,
      SLOT_2_SPI_io1_i => zynq_ultra_ps_e_0_SPI_0_IO1_I,
      SLOT_2_SPI_io1_o => zynq_ultra_ps_e_0_SPI_0_IO1_O,
      SLOT_2_SPI_io1_t => zynq_ultra_ps_e_0_SPI_0_IO1_T,
      SLOT_2_SPI_sck_i => zynq_ultra_ps_e_0_SPI_0_SCK_I,
      SLOT_2_SPI_sck_o => zynq_ultra_ps_e_0_SPI_0_SCK_O,
      SLOT_2_SPI_sck_t => zynq_ultra_ps_e_0_SPI_0_SCK_T,
      SLOT_2_SPI_ss_i => zynq_ultra_ps_e_0_SPI_0_SS_I,
      SLOT_2_SPI_ss_o => zynq_ultra_ps_e_0_SPI_0_SS_O,
      SLOT_2_SPI_ss_t => zynq_ultra_ps_e_0_SPI_0_SS_T,
      SLOT_3_SPI_io0_i => zynq_ultra_ps_e_0_SPI_1_IO0_I,
      SLOT_3_SPI_io0_o => zynq_ultra_ps_e_0_SPI_1_IO0_O,
      SLOT_3_SPI_io0_t => zynq_ultra_ps_e_0_SPI_1_IO0_T,
      SLOT_3_SPI_io1_i => zynq_ultra_ps_e_0_SPI_1_IO1_I,
      SLOT_3_SPI_io1_o => zynq_ultra_ps_e_0_SPI_1_IO1_O,
      SLOT_3_SPI_io1_t => zynq_ultra_ps_e_0_SPI_1_IO1_T,
      SLOT_3_SPI_sck_i => zynq_ultra_ps_e_0_SPI_1_SCK_I,
      SLOT_3_SPI_sck_o => zynq_ultra_ps_e_0_SPI_1_SCK_O,
      SLOT_3_SPI_sck_t => zynq_ultra_ps_e_0_SPI_1_SCK_T,
      SLOT_3_SPI_ss_i => zynq_ultra_ps_e_0_SPI_1_SS_I,
      SLOT_3_SPI_ss_o => zynq_ultra_ps_e_0_SPI_1_SS_O,
      SLOT_3_SPI_ss_t => zynq_ultra_ps_e_0_SPI_1_SS_T,
      clk => clk_wiz_0_clk_out1
    );
util_ds_buf_0: component zusys_util_ds_buf_0_0
     port map (
      IBUF_DS_N(0) => CLK_IN_D_1_CLK_N(0),
      IBUF_DS_P(0) => CLK_IN_D_1_CLK_P(0),
      IBUF_OUT(0) => util_ds_buf_0_IBUF_OUT(0)
    );
vio_0: component zusys_vio_0_0
     port map (
      clk => zynq_ultra_ps_e_0_pl_clk1,
      probe_in0(31 downto 0) => fm_SI5338_CLK0_D(31 downto 0),
      probe_in1(0) => labtools_fmeter_0_update,
      probe_in2(0) => VIO_x0_firmware(0),
      probe_in3(0) => x1_phy_led(0)
    );
xlconcat_0: component zusys_xlconcat_0_0
     port map (
      In0(0) => util_ds_buf_0_IBUF_OUT(0),
      dout(0) => xlconcat_0_dout(0)
    );
zynq_ultra_ps_e_0: component zusys_zynq_ultra_ps_e_0_0
     port map (
      emio_i2c1_scl_i => zynq_ultra_ps_e_0_IIC_1_SCL_I,
      emio_i2c1_scl_o => zynq_ultra_ps_e_0_IIC_1_SCL_O,
      emio_i2c1_scl_t => zynq_ultra_ps_e_0_IIC_1_SCL_T,
      emio_i2c1_sda_i => zynq_ultra_ps_e_0_IIC_1_SDA_I,
      emio_i2c1_sda_o => zynq_ultra_ps_e_0_IIC_1_SDA_O,
      emio_i2c1_sda_t => zynq_ultra_ps_e_0_IIC_1_SDA_T,
      emio_spi0_m_i => zynq_ultra_ps_e_0_SPI_0_IO1_I,
      emio_spi0_m_o => zynq_ultra_ps_e_0_SPI_0_IO0_O,
      emio_spi0_mo_t => zynq_ultra_ps_e_0_SPI_0_IO0_T,
      emio_spi0_s_i => zynq_ultra_ps_e_0_SPI_0_IO0_I,
      emio_spi0_s_o => zynq_ultra_ps_e_0_SPI_0_IO1_O,
      emio_spi0_sclk_i => zynq_ultra_ps_e_0_SPI_0_SCK_I,
      emio_spi0_sclk_o => zynq_ultra_ps_e_0_SPI_0_SCK_O,
      emio_spi0_sclk_t => zynq_ultra_ps_e_0_SPI_0_SCK_T,
      emio_spi0_so_t => zynq_ultra_ps_e_0_SPI_0_IO1_T,
      emio_spi0_ss_i_n => zynq_ultra_ps_e_0_SPI_0_SS_I,
      emio_spi0_ss_n_t => zynq_ultra_ps_e_0_SPI_0_SS_T,
      emio_spi0_ss_o_n => zynq_ultra_ps_e_0_SPI_0_SS_O,
      emio_spi1_m_i => zynq_ultra_ps_e_0_SPI_1_IO1_I,
      emio_spi1_m_o => zynq_ultra_ps_e_0_SPI_1_IO0_O,
      emio_spi1_mo_t => zynq_ultra_ps_e_0_SPI_1_IO0_T,
      emio_spi1_s_i => zynq_ultra_ps_e_0_SPI_1_IO0_I,
      emio_spi1_s_o => zynq_ultra_ps_e_0_SPI_1_IO1_O,
      emio_spi1_sclk_i => zynq_ultra_ps_e_0_SPI_1_SCK_I,
      emio_spi1_sclk_o => zynq_ultra_ps_e_0_SPI_1_SCK_O,
      emio_spi1_sclk_t => zynq_ultra_ps_e_0_SPI_1_SCK_T,
      emio_spi1_so_t => zynq_ultra_ps_e_0_SPI_1_IO1_T,
      emio_spi1_ss_i_n => zynq_ultra_ps_e_0_SPI_1_SS_I,
      emio_spi1_ss_n_t => zynq_ultra_ps_e_0_SPI_1_SS_T,
      emio_spi1_ss_o_n => zynq_ultra_ps_e_0_SPI_1_SS_O,
      emio_uart1_rxd => zynq_ultra_ps_e_0_UART_1_RxD,
      emio_uart1_txd => zynq_ultra_ps_e_0_UART_1_TxD,
      maxigp2_araddr(39 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_araddr_UNCONNECTED(39 downto 0),
      maxigp2_arburst(1 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_arburst_UNCONNECTED(1 downto 0),
      maxigp2_arcache(3 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_arcache_UNCONNECTED(3 downto 0),
      maxigp2_arid(15 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_arid_UNCONNECTED(15 downto 0),
      maxigp2_arlen(7 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_arlen_UNCONNECTED(7 downto 0),
      maxigp2_arlock => NLW_zynq_ultra_ps_e_0_maxigp2_arlock_UNCONNECTED,
      maxigp2_arprot(2 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_arprot_UNCONNECTED(2 downto 0),
      maxigp2_arqos(3 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_arqos_UNCONNECTED(3 downto 0),
      maxigp2_arready => '0',
      maxigp2_arsize(2 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_arsize_UNCONNECTED(2 downto 0),
      maxigp2_aruser(15 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_aruser_UNCONNECTED(15 downto 0),
      maxigp2_arvalid => NLW_zynq_ultra_ps_e_0_maxigp2_arvalid_UNCONNECTED,
      maxigp2_awaddr(39 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_awaddr_UNCONNECTED(39 downto 0),
      maxigp2_awburst(1 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_awburst_UNCONNECTED(1 downto 0),
      maxigp2_awcache(3 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_awcache_UNCONNECTED(3 downto 0),
      maxigp2_awid(15 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_awid_UNCONNECTED(15 downto 0),
      maxigp2_awlen(7 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_awlen_UNCONNECTED(7 downto 0),
      maxigp2_awlock => NLW_zynq_ultra_ps_e_0_maxigp2_awlock_UNCONNECTED,
      maxigp2_awprot(2 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_awprot_UNCONNECTED(2 downto 0),
      maxigp2_awqos(3 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_awqos_UNCONNECTED(3 downto 0),
      maxigp2_awready => '0',
      maxigp2_awsize(2 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_awsize_UNCONNECTED(2 downto 0),
      maxigp2_awuser(15 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_awuser_UNCONNECTED(15 downto 0),
      maxigp2_awvalid => NLW_zynq_ultra_ps_e_0_maxigp2_awvalid_UNCONNECTED,
      maxigp2_bid(15 downto 0) => B"0000000000000000",
      maxigp2_bready => NLW_zynq_ultra_ps_e_0_maxigp2_bready_UNCONNECTED,
      maxigp2_bresp(1 downto 0) => B"00",
      maxigp2_bvalid => '0',
      maxigp2_rdata(31 downto 0) => B"00000000000000000000000000000000",
      maxigp2_rid(15 downto 0) => B"0000000000000000",
      maxigp2_rlast => '0',
      maxigp2_rready => NLW_zynq_ultra_ps_e_0_maxigp2_rready_UNCONNECTED,
      maxigp2_rresp(1 downto 0) => B"00",
      maxigp2_rvalid => '0',
      maxigp2_wdata(31 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_wdata_UNCONNECTED(31 downto 0),
      maxigp2_wlast => NLW_zynq_ultra_ps_e_0_maxigp2_wlast_UNCONNECTED,
      maxigp2_wready => '0',
      maxigp2_wstrb(3 downto 0) => NLW_zynq_ultra_ps_e_0_maxigp2_wstrb_UNCONNECTED(3 downto 0),
      maxigp2_wvalid => NLW_zynq_ultra_ps_e_0_maxigp2_wvalid_UNCONNECTED,
      maxihpm0_lpd_aclk => zynq_ultra_ps_e_0_pl_clk1,
      pl_clk0 => zynq_ultra_ps_e_0_pl_clk1,
      pl_resetn0 => NLW_zynq_ultra_ps_e_0_pl_resetn0_UNCONNECTED
    );
end STRUCTURE;
