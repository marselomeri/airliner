// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (lin64) Build 2708876 Wed Nov  6 21:39:14 MST 2019
// Date        : Sat Aug 29 15:10:51 2020
// Host        : vagrant running 64-bit Ubuntu 16.04.6 LTS
// Command     : write_verilog -force -mode synth_stub
//               /home/vagrant/git/airliner/config/squeaky_weasel/target/hw/TE0820/vivado/TE0820-03-2AI21FA.srcs/sources_1/bd/zusys/ip/zusys_labtools_fmeter_0_0/zusys_labtools_fmeter_0_0_stub.v
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
