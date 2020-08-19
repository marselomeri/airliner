--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2019.2 (lin64) Build 2708876 Wed Nov  6 21:39:14 MST 2019
--Date        : Wed Aug 19 03:53:33 2020
--Host        : vagrant running 64-bit Ubuntu 16.04.6 LTS
--Command     : generate_target zusys_wrapper.bd
--Design      : zusys_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_wrapper is
  port (
    IIC_1_0_scl_io : inout STD_LOGIC;
    IIC_1_0_sda_io : inout STD_LOGIC;
    SI5338_CLK0_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK0_D_clk_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    SPI_0_0_io0_io : inout STD_LOGIC;
    SPI_0_0_io1_io : inout STD_LOGIC;
    SPI_0_0_sck_io : inout STD_LOGIC;
    SPI_0_0_ss_io : inout STD_LOGIC;
    SPI_1_0_io0_io : inout STD_LOGIC;
    SPI_1_0_io1_io : inout STD_LOGIC;
    SPI_1_0_sck_io : inout STD_LOGIC;
    SPI_1_0_ss_io : inout STD_LOGIC;
    UART_1_0_rxd : in STD_LOGIC;
    UART_1_0_txd : out STD_LOGIC;
    x0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    x1 : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
end zusys_wrapper;

architecture STRUCTURE of zusys_wrapper is
  component zusys is
  port (
    x0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    x1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    SPI_1_0_sck_i : in STD_LOGIC;
    SPI_1_0_sck_o : out STD_LOGIC;
    SPI_1_0_sck_t : out STD_LOGIC;
    SPI_1_0_io1_i : in STD_LOGIC;
    SPI_1_0_io0_o : out STD_LOGIC;
    SPI_1_0_io0_t : out STD_LOGIC;
    SPI_1_0_io0_i : in STD_LOGIC;
    SPI_1_0_io1_o : out STD_LOGIC;
    SPI_1_0_io1_t : out STD_LOGIC;
    SPI_1_0_ss_i : in STD_LOGIC;
    SPI_1_0_ss_o : out STD_LOGIC;
    SPI_1_0_ss_t : out STD_LOGIC;
    IIC_1_0_scl_i : in STD_LOGIC;
    IIC_1_0_scl_o : out STD_LOGIC;
    IIC_1_0_scl_t : out STD_LOGIC;
    IIC_1_0_sda_i : in STD_LOGIC;
    IIC_1_0_sda_o : out STD_LOGIC;
    IIC_1_0_sda_t : out STD_LOGIC;
    UART_1_0_txd : out STD_LOGIC;
    UART_1_0_rxd : in STD_LOGIC;
    SI5338_CLK0_D_clk_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK0_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    SPI_0_0_sck_i : in STD_LOGIC;
    SPI_0_0_sck_o : out STD_LOGIC;
    SPI_0_0_sck_t : out STD_LOGIC;
    SPI_0_0_io1_i : in STD_LOGIC;
    SPI_0_0_io0_o : out STD_LOGIC;
    SPI_0_0_io0_t : out STD_LOGIC;
    SPI_0_0_io0_i : in STD_LOGIC;
    SPI_0_0_io1_o : out STD_LOGIC;
    SPI_0_0_io1_t : out STD_LOGIC;
    SPI_0_0_ss_i : in STD_LOGIC;
    SPI_0_0_ss_o : out STD_LOGIC;
    SPI_0_0_ss_t : out STD_LOGIC
  );
  end component zusys;
  component IOBUF is
  port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC;
    IO : inout STD_LOGIC
  );
  end component IOBUF;
  signal IIC_1_0_scl_i : STD_LOGIC;
  signal IIC_1_0_scl_o : STD_LOGIC;
  signal IIC_1_0_scl_t : STD_LOGIC;
  signal IIC_1_0_sda_i : STD_LOGIC;
  signal IIC_1_0_sda_o : STD_LOGIC;
  signal IIC_1_0_sda_t : STD_LOGIC;
  signal SPI_0_0_io0_i : STD_LOGIC;
  signal SPI_0_0_io0_o : STD_LOGIC;
  signal SPI_0_0_io0_t : STD_LOGIC;
  signal SPI_0_0_io1_i : STD_LOGIC;
  signal SPI_0_0_io1_o : STD_LOGIC;
  signal SPI_0_0_io1_t : STD_LOGIC;
  signal SPI_0_0_sck_i : STD_LOGIC;
  signal SPI_0_0_sck_o : STD_LOGIC;
  signal SPI_0_0_sck_t : STD_LOGIC;
  signal SPI_0_0_ss_i : STD_LOGIC;
  signal SPI_0_0_ss_o : STD_LOGIC;
  signal SPI_0_0_ss_t : STD_LOGIC;
  signal SPI_1_0_io0_i : STD_LOGIC;
  signal SPI_1_0_io0_o : STD_LOGIC;
  signal SPI_1_0_io0_t : STD_LOGIC;
  signal SPI_1_0_io1_i : STD_LOGIC;
  signal SPI_1_0_io1_o : STD_LOGIC;
  signal SPI_1_0_io1_t : STD_LOGIC;
  signal SPI_1_0_sck_i : STD_LOGIC;
  signal SPI_1_0_sck_o : STD_LOGIC;
  signal SPI_1_0_sck_t : STD_LOGIC;
  signal SPI_1_0_ss_i : STD_LOGIC;
  signal SPI_1_0_ss_o : STD_LOGIC;
  signal SPI_1_0_ss_t : STD_LOGIC;
begin
IIC_1_0_scl_iobuf: component IOBUF
     port map (
      I => IIC_1_0_scl_o,
      IO => IIC_1_0_scl_io,
      O => IIC_1_0_scl_i,
      T => IIC_1_0_scl_t
    );
IIC_1_0_sda_iobuf: component IOBUF
     port map (
      I => IIC_1_0_sda_o,
      IO => IIC_1_0_sda_io,
      O => IIC_1_0_sda_i,
      T => IIC_1_0_sda_t
    );
SPI_0_0_io0_iobuf: component IOBUF
     port map (
      I => SPI_0_0_io0_o,
      IO => SPI_0_0_io0_io,
      O => SPI_0_0_io0_i,
      T => SPI_0_0_io0_t
    );
SPI_0_0_io1_iobuf: component IOBUF
     port map (
      I => SPI_0_0_io1_o,
      IO => SPI_0_0_io1_io,
      O => SPI_0_0_io1_i,
      T => SPI_0_0_io1_t
    );
SPI_0_0_sck_iobuf: component IOBUF
     port map (
      I => SPI_0_0_sck_o,
      IO => SPI_0_0_sck_io,
      O => SPI_0_0_sck_i,
      T => SPI_0_0_sck_t
    );
SPI_0_0_ss_iobuf: component IOBUF
     port map (
      I => SPI_0_0_ss_o,
      IO => SPI_0_0_ss_io,
      O => SPI_0_0_ss_i,
      T => SPI_0_0_ss_t
    );
SPI_1_0_io0_iobuf: component IOBUF
     port map (
      I => SPI_1_0_io0_o,
      IO => SPI_1_0_io0_io,
      O => SPI_1_0_io0_i,
      T => SPI_1_0_io0_t
    );
SPI_1_0_io1_iobuf: component IOBUF
     port map (
      I => SPI_1_0_io1_o,
      IO => SPI_1_0_io1_io,
      O => SPI_1_0_io1_i,
      T => SPI_1_0_io1_t
    );
SPI_1_0_sck_iobuf: component IOBUF
     port map (
      I => SPI_1_0_sck_o,
      IO => SPI_1_0_sck_io,
      O => SPI_1_0_sck_i,
      T => SPI_1_0_sck_t
    );
SPI_1_0_ss_iobuf: component IOBUF
     port map (
      I => SPI_1_0_ss_o,
      IO => SPI_1_0_ss_io,
      O => SPI_1_0_ss_i,
      T => SPI_1_0_ss_t
    );
zusys_i: component zusys
     port map (
      IIC_1_0_scl_i => IIC_1_0_scl_i,
      IIC_1_0_scl_o => IIC_1_0_scl_o,
      IIC_1_0_scl_t => IIC_1_0_scl_t,
      IIC_1_0_sda_i => IIC_1_0_sda_i,
      IIC_1_0_sda_o => IIC_1_0_sda_o,
      IIC_1_0_sda_t => IIC_1_0_sda_t,
      SI5338_CLK0_D_clk_n(0) => SI5338_CLK0_D_clk_n(0),
      SI5338_CLK0_D_clk_p(0) => SI5338_CLK0_D_clk_p(0),
      SPI_0_0_io0_i => SPI_0_0_io0_i,
      SPI_0_0_io0_o => SPI_0_0_io0_o,
      SPI_0_0_io0_t => SPI_0_0_io0_t,
      SPI_0_0_io1_i => SPI_0_0_io1_i,
      SPI_0_0_io1_o => SPI_0_0_io1_o,
      SPI_0_0_io1_t => SPI_0_0_io1_t,
      SPI_0_0_sck_i => SPI_0_0_sck_i,
      SPI_0_0_sck_o => SPI_0_0_sck_o,
      SPI_0_0_sck_t => SPI_0_0_sck_t,
      SPI_0_0_ss_i => SPI_0_0_ss_i,
      SPI_0_0_ss_o => SPI_0_0_ss_o,
      SPI_0_0_ss_t => SPI_0_0_ss_t,
      SPI_1_0_io0_i => SPI_1_0_io0_i,
      SPI_1_0_io0_o => SPI_1_0_io0_o,
      SPI_1_0_io0_t => SPI_1_0_io0_t,
      SPI_1_0_io1_i => SPI_1_0_io1_i,
      SPI_1_0_io1_o => SPI_1_0_io1_o,
      SPI_1_0_io1_t => SPI_1_0_io1_t,
      SPI_1_0_sck_i => SPI_1_0_sck_i,
      SPI_1_0_sck_o => SPI_1_0_sck_o,
      SPI_1_0_sck_t => SPI_1_0_sck_t,
      SPI_1_0_ss_i => SPI_1_0_ss_i,
      SPI_1_0_ss_o => SPI_1_0_ss_o,
      SPI_1_0_ss_t => SPI_1_0_ss_t,
      UART_1_0_rxd => UART_1_0_rxd,
      UART_1_0_txd => UART_1_0_txd,
      x0(0) => x0(0),
      x1(0) => x1(0)
    );
end STRUCTURE;
