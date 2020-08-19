// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
// Date        : Wed Mar  4 12:33:33 2020
// Host        : LAPTOP-RVVOIP55 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               C:/TE0820/vivado/TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/zusys_zynq_ultra_ps_e_0_0_stub.v
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
  saxi_lpd_aclk, saxigp6_aruser, saxigp6_awuser, saxigp6_awid, saxigp6_awaddr, saxigp6_awlen, 
  saxigp6_awsize, saxigp6_awburst, saxigp6_awlock, saxigp6_awcache, saxigp6_awprot, 
  saxigp6_awvalid, saxigp6_awready, saxigp6_wdata, saxigp6_wstrb, saxigp6_wlast, 
  saxigp6_wvalid, saxigp6_wready, saxigp6_bid, saxigp6_bresp, saxigp6_bvalid, saxigp6_bready, 
  saxigp6_arid, saxigp6_araddr, saxigp6_arlen, saxigp6_arsize, saxigp6_arburst, 
  saxigp6_arlock, saxigp6_arcache, saxigp6_arprot, saxigp6_arvalid, saxigp6_arready, 
  saxigp6_rid, saxigp6_rdata, saxigp6_rresp, saxigp6_rlast, saxigp6_rvalid, saxigp6_rready, 
  saxigp6_awqos, saxigp6_arqos, emio_gpio_i, emio_gpio_o, emio_gpio_t, emio_i2c1_scl_i, 
  emio_i2c1_scl_o, emio_i2c1_scl_t, emio_i2c1_sda_i, emio_i2c1_sda_o, emio_i2c1_sda_t, 
  emio_uart1_txd, emio_uart1_rxd, emio_spi0_sclk_i, emio_spi0_sclk_o, emio_spi0_sclk_t, 
  emio_spi0_m_i, emio_spi0_m_o, emio_spi0_mo_t, emio_spi0_s_i, emio_spi0_s_o, emio_spi0_so_t, 
  emio_spi0_ss_i_n, emio_spi0_ss_o_n, emio_spi0_ss_n_t, emio_spi1_sclk_i, emio_spi1_sclk_o, 
  emio_spi1_sclk_t, emio_spi1_m_i, emio_spi1_m_o, emio_spi1_mo_t, emio_spi1_s_i, 
  emio_spi1_s_o, emio_spi1_so_t, emio_spi1_ss_i_n, emio_spi1_ss_o_n, emio_spi1_ss_n_t, 
  pl_resetn0, pl_clk0)
/* synthesis syn_black_box black_box_pad_pin="maxihpm0_lpd_aclk,maxigp2_awid[15:0],maxigp2_awaddr[39:0],maxigp2_awlen[7:0],maxigp2_awsize[2:0],maxigp2_awburst[1:0],maxigp2_awlock,maxigp2_awcache[3:0],maxigp2_awprot[2:0],maxigp2_awvalid,maxigp2_awuser[15:0],maxigp2_awready,maxigp2_wdata[31:0],maxigp2_wstrb[3:0],maxigp2_wlast,maxigp2_wvalid,maxigp2_wready,maxigp2_bid[15:0],maxigp2_bresp[1:0],maxigp2_bvalid,maxigp2_bready,maxigp2_arid[15:0],maxigp2_araddr[39:0],maxigp2_arlen[7:0],maxigp2_arsize[2:0],maxigp2_arburst[1:0],maxigp2_arlock,maxigp2_arcache[3:0],maxigp2_arprot[2:0],maxigp2_arvalid,maxigp2_aruser[15:0],maxigp2_arready,maxigp2_rid[15:0],maxigp2_rdata[31:0],maxigp2_rresp[1:0],maxigp2_rlast,maxigp2_rvalid,maxigp2_rready,maxigp2_awqos[3:0],maxigp2_arqos[3:0],saxi_lpd_aclk,saxigp6_aruser,saxigp6_awuser,saxigp6_awid[5:0],saxigp6_awaddr[48:0],saxigp6_awlen[7:0],saxigp6_awsize[2:0],saxigp6_awburst[1:0],saxigp6_awlock,saxigp6_awcache[3:0],saxigp6_awprot[2:0],saxigp6_awvalid,saxigp6_awready,saxigp6_wdata[127:0],saxigp6_wstrb[15:0],saxigp6_wlast,saxigp6_wvalid,saxigp6_wready,saxigp6_bid[5:0],saxigp6_bresp[1:0],saxigp6_bvalid,saxigp6_bready,saxigp6_arid[5:0],saxigp6_araddr[48:0],saxigp6_arlen[7:0],saxigp6_arsize[2:0],saxigp6_arburst[1:0],saxigp6_arlock,saxigp6_arcache[3:0],saxigp6_arprot[2:0],saxigp6_arvalid,saxigp6_arready,saxigp6_rid[5:0],saxigp6_rdata[127:0],saxigp6_rresp[1:0],saxigp6_rlast,saxigp6_rvalid,saxigp6_rready,saxigp6_awqos[3:0],saxigp6_arqos[3:0],emio_gpio_i[1:0],emio_gpio_o[1:0],emio_gpio_t[1:0],emio_i2c1_scl_i,emio_i2c1_scl_o,emio_i2c1_scl_t,emio_i2c1_sda_i,emio_i2c1_sda_o,emio_i2c1_sda_t,emio_uart1_txd,emio_uart1_rxd,emio_spi0_sclk_i,emio_spi0_sclk_o,emio_spi0_sclk_t,emio_spi0_m_i,emio_spi0_m_o,emio_spi0_mo_t,emio_spi0_s_i,emio_spi0_s_o,emio_spi0_so_t,emio_spi0_ss_i_n,emio_spi0_ss_o_n,emio_spi0_ss_n_t,emio_spi1_sclk_i,emio_spi1_sclk_o,emio_spi1_sclk_t,emio_spi1_m_i,emio_spi1_m_o,emio_spi1_mo_t,emio_spi1_s_i,emio_spi1_s_o,emio_spi1_so_t,emio_spi1_ss_i_n,emio_spi1_ss_o_n,emio_spi1_ss_n_t,pl_resetn0,pl_clk0" */;
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
  input saxi_lpd_aclk;
  input saxigp6_aruser;
  input saxigp6_awuser;
  input [5:0]saxigp6_awid;
  input [48:0]saxigp6_awaddr;
  input [7:0]saxigp6_awlen;
  input [2:0]saxigp6_awsize;
  input [1:0]saxigp6_awburst;
  input saxigp6_awlock;
  input [3:0]saxigp6_awcache;
  input [2:0]saxigp6_awprot;
  input saxigp6_awvalid;
  output saxigp6_awready;
  input [127:0]saxigp6_wdata;
  input [15:0]saxigp6_wstrb;
  input saxigp6_wlast;
  input saxigp6_wvalid;
  output saxigp6_wready;
  output [5:0]saxigp6_bid;
  output [1:0]saxigp6_bresp;
  output saxigp6_bvalid;
  input saxigp6_bready;
  input [5:0]saxigp6_arid;
  input [48:0]saxigp6_araddr;
  input [7:0]saxigp6_arlen;
  input [2:0]saxigp6_arsize;
  input [1:0]saxigp6_arburst;
  input saxigp6_arlock;
  input [3:0]saxigp6_arcache;
  input [2:0]saxigp6_arprot;
  input saxigp6_arvalid;
  output saxigp6_arready;
  output [5:0]saxigp6_rid;
  output [127:0]saxigp6_rdata;
  output [1:0]saxigp6_rresp;
  output saxigp6_rlast;
  output saxigp6_rvalid;
  input saxigp6_rready;
  input [3:0]saxigp6_awqos;
  input [3:0]saxigp6_arqos;
  input [1:0]emio_gpio_i;
  output [1:0]emio_gpio_o;
  output [1:0]emio_gpio_t;
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
