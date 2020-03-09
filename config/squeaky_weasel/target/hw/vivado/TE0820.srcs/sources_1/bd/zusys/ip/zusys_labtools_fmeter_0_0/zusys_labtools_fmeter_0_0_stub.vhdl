-- Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
-- Date        : Mon Mar  2 21:44:08 2020
-- Host        : LAPTOP-RVVOIP55 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               C:/TE0820/vivado/TE0820.srcs/sources_1/bd/zusys/ip/zusys_labtools_fmeter_0_0/zusys_labtools_fmeter_0_0_stub.vhdl
-- Design      : zusys_labtools_fmeter_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xczu2cg-sfvc784-1-i
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity zusys_labtools_fmeter_0_0 is
  Port ( 
    refclk : in STD_LOGIC;
    fin : in STD_LOGIC_VECTOR ( 0 to 0 );
    F0 : out STD_LOGIC_VECTOR ( 31 downto 0 );
    update : out STD_LOGIC
  );

end zusys_labtools_fmeter_0_0;

architecture stub of zusys_labtools_fmeter_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "refclk,fin[0:0],F0[31:0],update";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "labtools_fmeter,Vivado 2019.2";
begin
end;
