// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (lin64) Build 2708876 Wed Nov  6 21:39:14 MST 2019
// Date        : Sat Aug 29 15:13:46 2020
// Host        : vagrant running 64-bit Ubuntu 16.04.6 LTS
// Command     : write_verilog -force -mode synth_stub
//               /home/vagrant/git/airliner/config/squeaky_weasel/target/hw/TE0820/vivado/TE0820-03-2AI21FA.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/zusys_zynq_ultra_ps_e_0_0_stub.v
// Design      : zusys_zynq_ultra_ps_e_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu2cg-sfvc784-1-i
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "zynq_ultra_ps_e_v3_3_1_zynq_ultra_ps_e,Vivado 2019.2" *)
module zusys_zynq_ultra_ps_e_0_0(maxihpm0_lpd_aclk, maxigp2_awid, 
  maxigp2_awaddr, maxigp2_awlen, maxigp2_awsize, maxigp2_awburst, maxigp2_awlock, 
  maxigp2_awcache, maxigp2_awprot, maxigp2_awvalid, maxigp2_awuser, maxigp2_awready, 
  maxigp2_wdata, maxigp2_wstrb, maxigp2_wlast, maxigp2_wvalid, maxigp2_wready, maxigp2_bid, 
  maxigp2_bresp, maxigp2_bvalid, maxigp2_bready, maxigp2_arid, maxigp2_araddr, maxigp2_arlen, 
  maxigp2_arsize, maxigp2_arburst, maxigp2_arlock, maxigp2_arcache, maxigp2_arprot, 
  maxigp2_arvalid, maxigp2_aruser, maxigp2_arready, maxigp2_rid, maxigp2_rdata, 
  maxigp2_rresp, maxigp2_rlast, maxigp2_rvalid, maxigp2_rready, maxigp2_awqos, maxigp2_arqos, 
  emio_i2c1_scl_i, emio_i2c1_scl_o, emio_i2c1_scl_t, emio_i2c1_sda_i, emio_i2c1_sda_o, 
  emio_i2c1_sda_t, emio_uart1_txd, emio_uart1_rxd, emio_spi0_sclk_i, emio_spi0_sclk_o, 
  emio_spi0_sclk_t, emio_spi0_m_i, emio_spi0_m_o, emio_spi0_mo_t, emio_spi0_s_i, 
  emio_spi0_s_o, emio_spi0_so_t, emio_spi0_ss_i_n, emio_spi0_ss_o_n, emio_spi0_ss_n_t, 
  emio_spi1_sclk_i, emio_spi1_sclk_o, emio_spi1_sclk_t, emio_spi1_m_i, emio_spi1_m_o, 
  emio_spi1_mo_t, emio_spi1_s_i, emio_spi1_s_o, emio_spi1_so_t, emio_spi1_ss_i_n, 
  emio_spi1_ss_o_n, emio_spi1_ss_n_t, pl_resetn0, pl_clk0)
/* synthesis syn_black_box black_box_pad_pin="maxihpm0_lpd_aclk,maxigp2_awid[15:0],maxigp2_awaddr[39:0],maxigp2_awlen[7:0],maxigp2_awsize[2:0],maxigp2_awburst[1:0],maxigp2_awlock,maxigp2_awcache[3:0],maxigp2_awprot[2:0],maxigp2_awvalid,maxigp2_awuser[15:0],maxigp2_awready,maxigp2_wdata[31:0],maxigp2_wstrb[3:0],maxigp2_wlast,maxigp2_wvalid,maxigp2_wready,maxigp2_bid[15:0],maxigp2_bresp[1:0],maxigp2_bvalid,maxigp2_bready,maxigp2_arid[15:0],maxigp2_araddr[39:0],maxigp2_arlen[7:0],maxigp2_arsize[2:0],maxigp2_arburst[1:0],maxigp2_arlock,maxigp2_arcache[3:0],maxigp2_arprot[2:0],maxigp2_arvalid,maxigp2_aruser[15:0],maxigp2_arready,maxigp2_rid[15:0],maxigp2_rdata[31:0],maxigp2_rresp[1:0],maxigp2_rlast,maxigp2_rvalid,maxigp2_rready,maxigp2_awqos[3:0],maxigp2_arqos[3:0],emio_i2c1_scl_i,emio_i2c1_scl_o,emio_i2c1_scl_t,emio_i2c1_sda_i,emio_i2c1_sda_o,emio_i2c1_sda_t,emio_uart1_txd,emio_uart1_rxd,emio_spi0_sclk_i,emio_spi0_sclk_o,emio_spi0_sclk_t,emio_spi0_m_i,emio_spi0_m_o,emio_spi0_mo_t,emio_spi0_s_i,emio_spi0_s_o,emio_spi0_so_t,emio_spi0_ss_i_n,emio_spi0_ss_o_n,emio_spi0_ss_n_t,emio_spi1_sclk_i,emio_spi1_sclk_o,emio_spi1_sclk_t,emio_spi1_m_i,emio_spi1_m_o,emio_spi1_mo_t,emio_spi1_s_i,emio_spi1_s_o,emio_spi1_so_t,emio_spi1_ss_i_n,emio_spi1_ss_o_n,emio_spi1_ss_n_t,pl_resetn0,pl_clk0" */;
  input maxihpm0_lpd_aclk;
  output [15:0]maxigp2_awid;
  output [39:0]maxigp2_awaddr;
  output [7:0]maxigp2_awlen;
  output [2:0]maxigp2_awsize;
  output [1:0]maxigp2_awburst;
  output maxigp2_awlock;
  output [3:0]maxigp2_awcache;
  output [2:0]maxigp2_awprot;
  output maxigp2_awvalid;
  output [15:0]maxigp2_awuser;
  input maxigp2_awready;
  output [31:0]maxigp2_wdata;
  output [3:0]maxigp2_wstrb;
  output maxigp2_wlast;
  output maxigp2_wvalid;
  input maxigp2_wready;
  input [15:0]maxigp2_bid;
  input [1:0]maxigp2_bresp;
  input maxigp2_bvalid;
  output maxigp2_bready;
  output [15:0]maxigp2_arid;
  output [39:0]maxigp2_araddr;
  output [7:0]maxigp2_arlen;
  output [2:0]maxigp2_arsize;
  output [1:0]maxigp2_arburst;
  output maxigp2_arlock;
  output [3:0]maxigp2_arcache;
  output [2:0]maxigp2_arprot;
  output maxigp2_arvalid;
  output [15:0]maxigp2_aruser;
  input maxigp2_arready;
  input [15:0]maxigp2_rid;
  input [31:0]maxigp2_rdata;
  input [1:0]maxigp2_rresp;
  input maxigp2_rlast;
  input maxigp2_rvalid;
  output maxigp2_rready;
  output [3:0]maxigp2_awqos;
  output [3:0]maxigp2_arqos;
  input emio_i2c1_scl_i;
  output emio_i2c1_scl_o;
  output emio_i2c1_scl_t;
  input emio_i2c1_sda_i;
  output emio_i2c1_sda_o;
  output emio_i2c1_sda_t;
  output emio_uart1_txd;
  input emio_uart1_rxd;
  input emio_spi0_sclk_i;
  output emio_spi0_sclk_o;
  output emio_spi0_sclk_t;
  input emio_spi0_m_i;
  output emio_spi0_m_o;
  output emio_spi0_mo_t;
  input emio_spi0_s_i;
  output emio_spi0_s_o;
  output emio_spi0_so_t;
  input emio_spi0_ss_i_n;
  output emio_spi0_ss_o_n;
  output emio_spi0_ss_n_t;
  input emio_spi1_sclk_i;
  output emio_spi1_sclk_o;
  output emio_spi1_sclk_t;
  input emio_spi1_m_i;
  output emio_spi1_m_o;
  output emio_spi1_mo_t;
  input emio_spi1_s_i;
  output emio_spi1_s_o;
  output emio_spi1_so_t;
  input emio_spi1_ss_i_n;
  output emio_spi1_ss_o_n;
  output emio_spi1_ss_n_t;
  output pl_resetn0;
  output pl_clk0;
endmodule
