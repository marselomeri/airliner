// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
// Date        : Mon Mar  2 21:44:08 2020
// Host        : LAPTOP-RVVOIP55 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               C:/TE0820/vivado/TE0820.srcs/sources_1/bd/zusys/ip/zusys_labtools_fmeter_0_0/zusys_labtools_fmeter_0_0_stub.v
// Design      : zusys_labtools_fmeter_0_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu2cg-sfvc784-1-i
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "labtools_fmeter,Vivado 2019.2" *)
module zusys_labtools_fmeter_0_0(refclk, fin, F0, update)
/* synthesis syn_black_box black_box_pad_pin="refclk,fin[0:0],F0[31:0],update" */;
  input refclk;
  input [0:0]fin;
  output [31:0]F0;
  output update;
endmodule
