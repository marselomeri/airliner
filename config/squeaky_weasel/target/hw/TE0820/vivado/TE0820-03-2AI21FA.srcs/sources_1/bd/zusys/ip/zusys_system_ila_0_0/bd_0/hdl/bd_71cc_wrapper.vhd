--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Command: generate_target bd_71cc_wrapper.bd
--Design : bd_71cc_wrapper
--Purpose: IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity bd_71cc_wrapper is
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
end bd_71cc_wrapper;

architecture STRUCTURE of bd_71cc_wrapper is
  component bd_71cc is
  port (
    clk : in STD_LOGIC;
    SLOT_0_IIC_scl_i : in STD_LOGIC;
    SLOT_0_IIC_scl_o : in STD_LOGIC;
    SLOT_0_IIC_scl_t : in STD_LOGIC;
    SLOT_0_IIC_sda_i : in STD_LOGIC;
    SLOT_0_IIC_sda_o : in STD_LOGIC;
    SLOT_0_IIC_sda_t : in STD_LOGIC;
    SLOT_1_UART_txd : in STD_LOGIC;
    SLOT_1_UART_rxd : in STD_LOGIC;
    SLOT_2_SPI_sck_i : in STD_LOGIC;
    SLOT_2_SPI_sck_o : in STD_LOGIC;
    SLOT_2_SPI_sck_t : in STD_LOGIC;
    SLOT_2_SPI_io1_i : in STD_LOGIC;
    SLOT_2_SPI_io0_o : in STD_LOGIC;
    SLOT_2_SPI_io0_t : in STD_LOGIC;
    SLOT_2_SPI_io0_i : in STD_LOGIC;
    SLOT_2_SPI_io1_o : in STD_LOGIC;
    SLOT_2_SPI_io1_t : in STD_LOGIC;
    SLOT_2_SPI_ss_i : in STD_LOGIC;
    SLOT_2_SPI_ss_o : in STD_LOGIC;
    SLOT_2_SPI_ss_t : in STD_LOGIC;
    SLOT_3_SPI_sck_i : in STD_LOGIC;
    SLOT_3_SPI_sck_o : in STD_LOGIC;
    SLOT_3_SPI_sck_t : in STD_LOGIC;
    SLOT_3_SPI_io1_i : in STD_LOGIC;
    SLOT_3_SPI_io0_o : in STD_LOGIC;
    SLOT_3_SPI_io0_t : in STD_LOGIC;
    SLOT_3_SPI_io0_i : in STD_LOGIC;
    SLOT_3_SPI_io1_o : in STD_LOGIC;
    SLOT_3_SPI_io1_t : in STD_LOGIC;
    SLOT_3_SPI_ss_i : in STD_LOGIC;
    SLOT_3_SPI_ss_o : in STD_LOGIC;
    SLOT_3_SPI_ss_t : in STD_LOGIC
  );
  end component bd_71cc;
begin
bd_71cc_i: component bd_71cc
     port map (
      SLOT_0_IIC_scl_i => SLOT_0_IIC_scl_i,
      SLOT_0_IIC_scl_o => SLOT_0_IIC_scl_o,
      SLOT_0_IIC_scl_t => SLOT_0_IIC_scl_t,
      SLOT_0_IIC_sda_i => SLOT_0_IIC_sda_i,
      SLOT_0_IIC_sda_o => SLOT_0_IIC_sda_o,
      SLOT_0_IIC_sda_t => SLOT_0_IIC_sda_t,
      SLOT_1_UART_rxd => SLOT_1_UART_rxd,
      SLOT_1_UART_txd => SLOT_1_UART_txd,
      SLOT_2_SPI_io0_i => SLOT_2_SPI_io0_i,
      SLOT_2_SPI_io0_o => SLOT_2_SPI_io0_o,
      SLOT_2_SPI_io0_t => SLOT_2_SPI_io0_t,
      SLOT_2_SPI_io1_i => SLOT_2_SPI_io1_i,
      SLOT_2_SPI_io1_o => SLOT_2_SPI_io1_o,
      SLOT_2_SPI_io1_t => SLOT_2_SPI_io1_t,
      SLOT_2_SPI_sck_i => SLOT_2_SPI_sck_i,
      SLOT_2_SPI_sck_o => SLOT_2_SPI_sck_o,
      SLOT_2_SPI_sck_t => SLOT_2_SPI_sck_t,
      SLOT_2_SPI_ss_i => SLOT_2_SPI_ss_i,
      SLOT_2_SPI_ss_o => SLOT_2_SPI_ss_o,
      SLOT_2_SPI_ss_t => SLOT_2_SPI_ss_t,
      SLOT_3_SPI_io0_i => SLOT_3_SPI_io0_i,
      SLOT_3_SPI_io0_o => SLOT_3_SPI_io0_o,
      SLOT_3_SPI_io0_t => SLOT_3_SPI_io0_t,
      SLOT_3_SPI_io1_i => SLOT_3_SPI_io1_i,
      SLOT_3_SPI_io1_o => SLOT_3_SPI_io1_o,
      SLOT_3_SPI_io1_t => SLOT_3_SPI_io1_t,
      SLOT_3_SPI_sck_i => SLOT_3_SPI_sck_i,
      SLOT_3_SPI_sck_o => SLOT_3_SPI_sck_o,
      SLOT_3_SPI_sck_t => SLOT_3_SPI_sck_t,
      SLOT_3_SPI_ss_i => SLOT_3_SPI_ss_i,
      SLOT_3_SPI_ss_o => SLOT_3_SPI_ss_o,
      SLOT_3_SPI_ss_t => SLOT_3_SPI_ss_t,
      clk => clk
    );
end STRUCTURE;
