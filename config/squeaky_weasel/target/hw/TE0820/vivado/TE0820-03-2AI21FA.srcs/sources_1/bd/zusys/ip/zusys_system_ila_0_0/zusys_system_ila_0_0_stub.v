// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (lin64) Build 2708876 Wed Nov  6 21:39:14 MST 2019
// Date        : Sat Aug 29 15:50:25 2020
// Host        : vagrant running 64-bit Ubuntu 16.04.6 LTS
// Command     : write_verilog -force -mode synth_stub
//               /home/vagrant/git/airliner/config/squeaky_weasel/target/hw/TE0820/vivado/TE0820-03-2AI21FA.srcs/sources_1/bd/zusys/ip/zusys_system_ila_0_0/zusys_system_ila_0_0_stub.v
// Design      : zusys_system_ila_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu2cg-sfvc784-1-i
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "bd_71cc,Vivado 2019.2" *)
module zusys_system_ila_0_0(clk, SLOT_0_IIC_scl_i, SLOT_0_IIC_scl_o, 
  SLOT_0_IIC_scl_t, SLOT_0_IIC_sda_i, SLOT_0_IIC_sda_o, SLOT_0_IIC_sda_t, SLOT_1_UART_rxd, 
  SLOT_1_UART_txd, SLOT_2_SPI_ss_i, SLOT_2_SPI_ss_o, SLOT_2_SPI_ss_t, SLOT_2_SPI_sck_i, 
  SLOT_2_SPI_sck_o, SLOT_2_SPI_sck_t, SLOT_2_SPI_io0_i, SLOT_2_SPI_io0_o, SLOT_2_SPI_io0_t, 
  SLOT_2_SPI_io1_i, SLOT_2_SPI_io1_o, SLOT_2_SPI_io1_t, SLOT_3_SPI_ss_i, SLOT_3_SPI_ss_o, 
  SLOT_3_SPI_ss_t, SLOT_3_SPI_sck_i, SLOT_3_SPI_sck_o, SLOT_3_SPI_sck_t, SLOT_3_SPI_io0_i, 
  SLOT_3_SPI_io0_o, SLOT_3_SPI_io0_t, SLOT_3_SPI_io1_i, SLOT_3_SPI_io1_o, SLOT_3_SPI_io1_t)
/* synthesis syn_black_box black_box_pad_pin="clk,SLOT_0_IIC_scl_i,SLOT_0_IIC_scl_o,SLOT_0_IIC_scl_t,SLOT_0_IIC_sda_i,SLOT_0_IIC_sda_o,SLOT_0_IIC_sda_t,SLOT_1_UART_rxd,SLOT_1_UART_txd,SLOT_2_SPI_ss_i,SLOT_2_SPI_ss_o,SLOT_2_SPI_ss_t,SLOT_2_SPI_sck_i,SLOT_2_SPI_sck_o,SLOT_2_SPI_sck_t,SLOT_2_SPI_io0_i,SLOT_2_SPI_io0_o,SLOT_2_SPI_io0_t,SLOT_2_SPI_io1_i,SLOT_2_SPI_io1_o,SLOT_2_SPI_io1_t,SLOT_3_SPI_ss_i,SLOT_3_SPI_ss_o,SLOT_3_SPI_ss_t,SLOT_3_SPI_sck_i,SLOT_3_SPI_sck_o,SLOT_3_SPI_sck_t,SLOT_3_SPI_io0_i,SLOT_3_SPI_io0_o,SLOT_3_SPI_io0_t,SLOT_3_SPI_io1_i,SLOT_3_SPI_io1_o,SLOT_3_SPI_io1_t" */;
  input clk;
  input SLOT_0_IIC_scl_i;
  input SLOT_0_IIC_scl_o;
  input SLOT_0_IIC_scl_t;
  input SLOT_0_IIC_sda_i;
  input SLOT_0_IIC_sda_o;
  input SLOT_0_IIC_sda_t;
  input SLOT_1_UART_rxd;
  input SLOT_1_UART_txd;
  input SLOT_2_SPI_ss_i;
  input SLOT_2_SPI_ss_o;
  input SLOT_2_SPI_ss_t;
  input SLOT_2_SPI_sck_i;
  input SLOT_2_SPI_sck_o;
  input SLOT_2_SPI_sck_t;
  input SLOT_2_SPI_io0_i;
  input SLOT_2_SPI_io0_o;
  input SLOT_2_SPI_io0_t;
  input SLOT_2_SPI_io1_i;
  input SLOT_2_SPI_io1_o;
  input SLOT_2_SPI_io1_t;
  input SLOT_3_SPI_ss_i;
  input SLOT_3_SPI_ss_o;
  input SLOT_3_SPI_ss_t;
  input SLOT_3_SPI_sck_i;
  input SLOT_3_SPI_sck_o;
  input SLOT_3_SPI_sck_t;
  input SLOT_3_SPI_io0_i;
  input SLOT_3_SPI_io0_o;
  input SLOT_3_SPI_io0_t;
  input SLOT_3_SPI_io1_i;
  input SLOT_3_SPI_io1_o;
  input SLOT_3_SPI_io1_t;
endmodule
