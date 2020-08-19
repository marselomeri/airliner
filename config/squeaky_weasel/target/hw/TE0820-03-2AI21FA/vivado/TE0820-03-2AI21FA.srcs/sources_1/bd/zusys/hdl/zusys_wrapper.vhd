--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2019.2 (lin64) Build 2708876 Wed Nov  6 21:39:14 MST 2019
--Date        : Tue Aug 18 23:44:54 2020
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
    SI5338_CLK0_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK0_D_clk_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    x0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    x1 : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
end zusys_wrapper;

architecture STRUCTURE of zusys_wrapper is
  component zusys is
  port (
    x0 : in STD_LOGIC_VECTOR ( 0 to 0 );
    x1 : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK0_D_clk_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK0_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  end component zusys;
begin
zusys_i: component zusys
     port map (
      SI5338_CLK0_D_clk_n(0) => SI5338_CLK0_D_clk_n(0),
      SI5338_CLK0_D_clk_p(0) => SI5338_CLK0_D_clk_p(0),
      x0(0) => x0(0),
      x1(0) => x1(0)
    );
end STRUCTURE;
