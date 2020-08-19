-- Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
-- Date        : Wed Feb 26 16:07:20 2020
-- Host        : LAPTOP-RVVOIP55 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/TE0820/vivado/TE0820.srcs/sources_1/bd/zusys/ip/zusys_labtools_fmeter_0_0/zusys_labtools_fmeter_0_0_sim_netlist.vhdl
-- Design      : zusys_labtools_fmeter_0_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu2cg-sfvc784-1-i
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO is
  port (
    update : out STD_LOGIC;
    F : out STD_LOGIC;
    \bl.DSP48E_2_0\ : out STD_LOGIC;
    refclk : in STD_LOGIC;
    toggle : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO : entity is "unimacro_COUNTER_TC_MACRO";
end zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO;

architecture STRUCTURE of zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO is
  signal CNTR_OUT : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \F[31]_i_2_n_0\ : STD_LOGIC;
  signal \F[31]_i_3_n_0\ : STD_LOGIC;
  signal \F[31]_i_4_n_0\ : STD_LOGIC;
  signal \bl.DSP48E_2_i_1_n_0\ : STD_LOGIC;
  signal update_INST_0_i_10_n_0 : STD_LOGIC;
  signal update_INST_0_i_11_n_0 : STD_LOGIC;
  signal update_INST_0_i_12_n_0 : STD_LOGIC;
  signal update_INST_0_i_1_n_0 : STD_LOGIC;
  signal update_INST_0_i_2_n_0 : STD_LOGIC;
  signal update_INST_0_i_3_n_0 : STD_LOGIC;
  signal update_INST_0_i_4_n_0 : STD_LOGIC;
  signal update_INST_0_i_5_n_0 : STD_LOGIC;
  signal update_INST_0_i_6_n_0 : STD_LOGIC;
  signal update_INST_0_i_7_n_0 : STD_LOGIC;
  signal update_INST_0_i_8_n_0 : STD_LOGIC;
  signal update_INST_0_i_9_n_0 : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_bl.DSP48E_2_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_bl.DSP48E_2_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_bl.DSP48E_2_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_bl.DSP48E_2_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \F[31]_i_3\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of \F[31]_i_4\ : label is "soft_lutpair0";
  attribute XILINX_LEGACY_PRIM : string;
  attribute XILINX_LEGACY_PRIM of \bl.DSP48E_2\ : label is "DSP48E1";
  attribute XILINX_TRANSFORM_PINMAP : string;
  attribute XILINX_TRANSFORM_PINMAP of \bl.DSP48E_2\ : label is "D[24]:D[26],D[25]";
  attribute box_type : string;
  attribute box_type of \bl.DSP48E_2\ : label is "PRIMITIVE";
  attribute SOFT_HLUTNM of update_INST_0_i_1 : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of update_INST_0_i_2 : label is "soft_lutpair0";
begin
\F[31]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000004"
    )
        port map (
      I0 => toggle,
      I1 => CNTR_OUT(0),
      I2 => \F[31]_i_2_n_0\,
      I3 => update_INST_0_i_3_n_0,
      I4 => update_INST_0_i_4_n_0,
      I5 => update_INST_0_i_5_n_0,
      O => F
    );
\F[31]_i_2\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => update_INST_0_i_6_n_0,
      I1 => \F[31]_i_3_n_0\,
      I2 => update_INST_0_i_7_n_0,
      I3 => \F[31]_i_4_n_0\,
      O => \F[31]_i_2_n_0\
    );
\F[31]_i_3\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"7FFF"
    )
        port map (
      I0 => CNTR_OUT(3),
      I1 => CNTR_OUT(2),
      I2 => CNTR_OUT(5),
      I3 => CNTR_OUT(4),
      O => \F[31]_i_3_n_0\
    );
\F[31]_i_4\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFEF"
    )
        port map (
      I0 => CNTR_OUT(11),
      I1 => CNTR_OUT(10),
      I2 => CNTR_OUT(13),
      I3 => CNTR_OUT(12),
      O => \F[31]_i_4_n_0\
    );
\bl.DSP48E_2\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 1,
      ADREG => 0,
      ALUMODEREG => 1,
      AMULTSEL => "A",
      AREG => 1,
      AUTORESET_PATDET => "NO_RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 1,
      BREG => 1,
      B_INPUT => "DIRECT",
      CARRYINREG => 1,
      CARRYINSELREG => 1,
      CREG => 1,
      DREG => 0,
      INMODEREG => 1,
      IS_ALUMODE_INVERTED => B"0000",
      IS_CARRYIN_INVERTED => '0',
      IS_CLK_INVERTED => '0',
      IS_INMODE_INVERTED => B"00000",
      IS_OPMODE_INVERTED => B"000000000",
      MASK => X"3FFFFFFFFFFF",
      MREG => 0,
      OPMODEREG => 1,
      PATTERN => X"000000000000",
      PREG => 1,
      SEL_MASK => "MASK",
      SEL_PATTERN => "PATTERN",
      USE_MULT => "NONE",
      USE_PATTERN_DETECT => "NO_PATDET",
      USE_SIMD => "ONE48"
    )
        port map (
      A(29 downto 0) => B"000000000000000000000000000000",
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_bl.DSP48E_2_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17 downto 0) => B"000000000000000001",
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_bl.DSP48E_2_BCOUT_UNCONNECTED\(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_bl.DSP48E_2_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_bl.DSP48E_2_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => '1',
      CEAD => '0',
      CEALUMODE => '1',
      CEB1 => '0',
      CEB2 => '1',
      CEC => '1',
      CECARRYIN => '1',
      CECTRL => '1',
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => '1',
      CLK => refclk,
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_bl.DSP48E_2_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 6) => B"000",
      OPMODE(5) => \bl.DSP48E_2_i_1_n_0\,
      OPMODE(4 downto 2) => B"000",
      OPMODE(1) => \bl.DSP48E_2_i_1_n_0\,
      OPMODE(0) => \bl.DSP48E_2_i_1_n_0\,
      OVERFLOW => \NLW_bl.DSP48E_2_OVERFLOW_UNCONNECTED\,
      P(47 downto 0) => CNTR_OUT(47 downto 0),
      PATTERNBDETECT => \NLW_bl.DSP48E_2_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_bl.DSP48E_2_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_bl.DSP48E_2_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => '0',
      RSTALLCARRYIN => '0',
      RSTALUMODE => '0',
      RSTB => '0',
      RSTC => '0',
      RSTCTRL => '0',
      RSTD => '0',
      RSTINMODE => '0',
      RSTM => '0',
      RSTP => '0',
      UNDERFLOW => \NLW_bl.DSP48E_2_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_bl.DSP48E_2_XOROUT_UNCONNECTED\(7 downto 0)
    );
\bl.DSP48E_2_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => update_INST_0_i_1_n_0,
      I1 => update_INST_0_i_2_n_0,
      I2 => update_INST_0_i_3_n_0,
      I3 => update_INST_0_i_4_n_0,
      I4 => update_INST_0_i_5_n_0,
      I5 => CNTR_OUT(0),
      O => \bl.DSP48E_2_i_1_n_0\
    );
toggle_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFEFFFF00010000"
    )
        port map (
      I0 => update_INST_0_i_5_n_0,
      I1 => update_INST_0_i_4_n_0,
      I2 => update_INST_0_i_3_n_0,
      I3 => \F[31]_i_2_n_0\,
      I4 => CNTR_OUT(0),
      I5 => toggle,
      O => \bl.DSP48E_2_0\
    );
update_INST_0: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0000000000000002"
    )
        port map (
      I0 => CNTR_OUT(0),
      I1 => update_INST_0_i_1_n_0,
      I2 => update_INST_0_i_2_n_0,
      I3 => update_INST_0_i_3_n_0,
      I4 => update_INST_0_i_4_n_0,
      I5 => update_INST_0_i_5_n_0,
      O => update
    );
update_INST_0_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFF7FFF"
    )
        port map (
      I0 => CNTR_OUT(4),
      I1 => CNTR_OUT(5),
      I2 => CNTR_OUT(2),
      I3 => CNTR_OUT(3),
      I4 => update_INST_0_i_6_n_0,
      O => update_INST_0_i_1_n_0
    );
update_INST_0_i_10: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => CNTR_OUT(39),
      I1 => CNTR_OUT(38),
      I2 => CNTR_OUT(41),
      I3 => CNTR_OUT(40),
      O => update_INST_0_i_10_n_0
    );
update_INST_0_i_11: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => CNTR_OUT(35),
      I1 => CNTR_OUT(34),
      I2 => CNTR_OUT(37),
      I3 => CNTR_OUT(36),
      O => update_INST_0_i_11_n_0
    );
update_INST_0_i_12: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => CNTR_OUT(43),
      I1 => CNTR_OUT(42),
      I2 => CNTR_OUT(45),
      I3 => CNTR_OUT(44),
      O => update_INST_0_i_12_n_0
    );
update_INST_0_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFFFB"
    )
        port map (
      I0 => CNTR_OUT(12),
      I1 => CNTR_OUT(13),
      I2 => CNTR_OUT(10),
      I3 => CNTR_OUT(11),
      I4 => update_INST_0_i_7_n_0,
      O => update_INST_0_i_2_n_0
    );
update_INST_0_i_3: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFFEFF"
    )
        port map (
      I0 => CNTR_OUT(28),
      I1 => CNTR_OUT(29),
      I2 => CNTR_OUT(27),
      I3 => CNTR_OUT(26),
      I4 => update_INST_0_i_8_n_0,
      O => update_INST_0_i_3_n_0
    );
update_INST_0_i_4: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FFFFF7FF"
    )
        port map (
      I0 => CNTR_OUT(20),
      I1 => CNTR_OUT(21),
      I2 => CNTR_OUT(19),
      I3 => CNTR_OUT(18),
      I4 => update_INST_0_i_9_n_0,
      O => update_INST_0_i_4_n_0
    );
update_INST_0_i_5: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFEFFFF"
    )
        port map (
      I0 => update_INST_0_i_10_n_0,
      I1 => update_INST_0_i_11_n_0,
      I2 => CNTR_OUT(47),
      I3 => CNTR_OUT(46),
      I4 => CNTR_OUT(1),
      I5 => update_INST_0_i_12_n_0,
      O => update_INST_0_i_5_n_0
    );
update_INST_0_i_6: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFF7"
    )
        port map (
      I0 => CNTR_OUT(7),
      I1 => CNTR_OUT(6),
      I2 => CNTR_OUT(9),
      I3 => CNTR_OUT(8),
      O => update_INST_0_i_6_n_0
    );
update_INST_0_i_7: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FF7F"
    )
        port map (
      I0 => CNTR_OUT(15),
      I1 => CNTR_OUT(14),
      I2 => CNTR_OUT(16),
      I3 => CNTR_OUT(17),
      O => update_INST_0_i_7_n_0
    );
update_INST_0_i_8: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FFFE"
    )
        port map (
      I0 => CNTR_OUT(31),
      I1 => CNTR_OUT(30),
      I2 => CNTR_OUT(33),
      I3 => CNTR_OUT(32),
      O => update_INST_0_i_8_n_0
    );
update_INST_0_i_9: unisim.vcomponents.LUT4
    generic map(
      INIT => X"FF7F"
    )
        port map (
      I0 => CNTR_OUT(23),
      I1 => CNTR_OUT(22),
      I2 => CNTR_OUT(24),
      I3 => CNTR_OUT(25),
      O => update_INST_0_i_9_n_0
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity \zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO__parameterized0\ is
  port (
    P : out STD_LOGIC_VECTOR ( 31 downto 0 );
    fin : in STD_LOGIC_VECTOR ( 0 to 0 );
    toggle : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of \zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO__parameterized0\ : entity is "unimacro_COUNTER_TC_MACRO";
end \zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO__parameterized0\;

architecture STRUCTURE of \zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO__parameterized0\ is
  signal CE : STD_LOGIC;
  signal CNTR_OUT : STD_LOGIC_VECTOR ( 47 downto 32 );
  signal \NLW_bl.DSP48E_2_CARRYCASCOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_MULTSIGNOUT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_OVERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_PATTERNBDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_PATTERNDETECT_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_UNDERFLOW_UNCONNECTED\ : STD_LOGIC;
  signal \NLW_bl.DSP48E_2_ACOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 29 downto 0 );
  signal \NLW_bl.DSP48E_2_BCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 17 downto 0 );
  signal \NLW_bl.DSP48E_2_CARRYOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal \NLW_bl.DSP48E_2_PCOUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 47 downto 0 );
  signal \NLW_bl.DSP48E_2_XOROUT_UNCONNECTED\ : STD_LOGIC_VECTOR ( 7 downto 0 );
  attribute XILINX_LEGACY_PRIM : string;
  attribute XILINX_LEGACY_PRIM of \bl.DSP48E_2\ : label is "DSP48E1";
  attribute XILINX_TRANSFORM_PINMAP : string;
  attribute XILINX_TRANSFORM_PINMAP of \bl.DSP48E_2\ : label is "D[24]:D[26],D[25]";
  attribute box_type : string;
  attribute box_type of \bl.DSP48E_2\ : label is "PRIMITIVE";
begin
\bl.DSP48E_2\: unisim.vcomponents.DSP48E2
    generic map(
      ACASCREG => 1,
      ADREG => 0,
      ALUMODEREG => 1,
      AMULTSEL => "A",
      AREG => 1,
      AUTORESET_PATDET => "NO_RESET",
      A_INPUT => "DIRECT",
      BCASCREG => 1,
      BREG => 1,
      B_INPUT => "DIRECT",
      CARRYINREG => 1,
      CARRYINSELREG => 1,
      CREG => 1,
      DREG => 0,
      INMODEREG => 1,
      IS_ALUMODE_INVERTED => B"0000",
      IS_CARRYIN_INVERTED => '0',
      IS_CLK_INVERTED => '0',
      IS_INMODE_INVERTED => B"00000",
      IS_OPMODE_INVERTED => B"000000000",
      MASK => X"3FFFFFFFFFFF",
      MREG => 0,
      OPMODEREG => 1,
      PATTERN => X"000000000000",
      PREG => 1,
      SEL_MASK => "MASK",
      SEL_PATTERN => "PATTERN",
      USE_MULT => "NONE",
      USE_PATTERN_DETECT => "NO_PATDET",
      USE_SIMD => "ONE48"
    )
        port map (
      A(29 downto 0) => B"000000000000000000000000000000",
      ACIN(29 downto 0) => B"000000000000000000000000000000",
      ACOUT(29 downto 0) => \NLW_bl.DSP48E_2_ACOUT_UNCONNECTED\(29 downto 0),
      ALUMODE(3 downto 0) => B"0000",
      B(17 downto 0) => B"000000000000000001",
      BCIN(17 downto 0) => B"000000000000000000",
      BCOUT(17 downto 0) => \NLW_bl.DSP48E_2_BCOUT_UNCONNECTED\(17 downto 0),
      C(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      CARRYCASCIN => '0',
      CARRYCASCOUT => \NLW_bl.DSP48E_2_CARRYCASCOUT_UNCONNECTED\,
      CARRYIN => '0',
      CARRYINSEL(2 downto 0) => B"000",
      CARRYOUT(3 downto 0) => \NLW_bl.DSP48E_2_CARRYOUT_UNCONNECTED\(3 downto 0),
      CEA1 => '0',
      CEA2 => CE,
      CEAD => '0',
      CEALUMODE => CE,
      CEB1 => '0',
      CEB2 => CE,
      CEC => CE,
      CECARRYIN => CE,
      CECTRL => CE,
      CED => '0',
      CEINMODE => '0',
      CEM => '0',
      CEP => CE,
      CLK => fin(0),
      D(26 downto 0) => B"000000000000000000000000000",
      INMODE(4 downto 0) => B"00000",
      MULTSIGNIN => '0',
      MULTSIGNOUT => \NLW_bl.DSP48E_2_MULTSIGNOUT_UNCONNECTED\,
      OPMODE(8 downto 0) => B"000100011",
      OVERFLOW => \NLW_bl.DSP48E_2_OVERFLOW_UNCONNECTED\,
      P(47 downto 32) => CNTR_OUT(47 downto 32),
      P(31 downto 0) => P(31 downto 0),
      PATTERNBDETECT => \NLW_bl.DSP48E_2_PATTERNBDETECT_UNCONNECTED\,
      PATTERNDETECT => \NLW_bl.DSP48E_2_PATTERNDETECT_UNCONNECTED\,
      PCIN(47 downto 0) => B"000000000000000000000000000000000000000000000000",
      PCOUT(47 downto 0) => \NLW_bl.DSP48E_2_PCOUT_UNCONNECTED\(47 downto 0),
      RSTA => toggle,
      RSTALLCARRYIN => toggle,
      RSTALUMODE => toggle,
      RSTB => toggle,
      RSTC => toggle,
      RSTCTRL => toggle,
      RSTD => toggle,
      RSTINMODE => toggle,
      RSTM => toggle,
      RSTP => toggle,
      UNDERFLOW => \NLW_bl.DSP48E_2_UNDERFLOW_UNCONNECTED\,
      XOROUT(7 downto 0) => \NLW_bl.DSP48E_2_XOROUT_UNCONNECTED\(7 downto 0)
    );
\bl.DSP48E_2_i_1__0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => toggle,
      O => CE
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_labtools_fmeter_0_0_labtools_fmeter is
  port (
    F0 : out STD_LOGIC_VECTOR ( 31 downto 0 );
    update : out STD_LOGIC;
    refclk : in STD_LOGIC;
    fin : in STD_LOGIC_VECTOR ( 0 to 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_labtools_fmeter_0_0_labtools_fmeter : entity is "labtools_fmeter";
end zusys_labtools_fmeter_0_0_labtools_fmeter;

architecture STRUCTURE of zusys_labtools_fmeter_0_0_labtools_fmeter is
  signal CNTR_OUT : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal COUNTER_REFCLK_inst_n_2 : STD_LOGIC;
  signal F : STD_LOGIC;
  signal toggle : STD_LOGIC;
begin
COUNTER_REFCLK_inst: entity work.zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO
     port map (
      F => F,
      \bl.DSP48E_2_0\ => COUNTER_REFCLK_inst_n_2,
      refclk => refclk,
      toggle => toggle,
      update => update
    );
\FMETER_gen[0].COUNTER_F_inst\: entity work.\zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO__parameterized0\
     port map (
      P(31 downto 0) => CNTR_OUT(31 downto 0),
      fin(0) => fin(0),
      toggle => toggle
    );
\F_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(0),
      Q => F0(0),
      R => '0'
    );
\F_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(10),
      Q => F0(10),
      R => '0'
    );
\F_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(11),
      Q => F0(11),
      R => '0'
    );
\F_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(12),
      Q => F0(12),
      R => '0'
    );
\F_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(13),
      Q => F0(13),
      R => '0'
    );
\F_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(14),
      Q => F0(14),
      R => '0'
    );
\F_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(15),
      Q => F0(15),
      R => '0'
    );
\F_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(16),
      Q => F0(16),
      R => '0'
    );
\F_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(17),
      Q => F0(17),
      R => '0'
    );
\F_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(18),
      Q => F0(18),
      R => '0'
    );
\F_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(19),
      Q => F0(19),
      R => '0'
    );
\F_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(1),
      Q => F0(1),
      R => '0'
    );
\F_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(20),
      Q => F0(20),
      R => '0'
    );
\F_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(21),
      Q => F0(21),
      R => '0'
    );
\F_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(22),
      Q => F0(22),
      R => '0'
    );
\F_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(23),
      Q => F0(23),
      R => '0'
    );
\F_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(24),
      Q => F0(24),
      R => '0'
    );
\F_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(25),
      Q => F0(25),
      R => '0'
    );
\F_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(26),
      Q => F0(26),
      R => '0'
    );
\F_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(27),
      Q => F0(27),
      R => '0'
    );
\F_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(28),
      Q => F0(28),
      R => '0'
    );
\F_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(29),
      Q => F0(29),
      R => '0'
    );
\F_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(2),
      Q => F0(2),
      R => '0'
    );
\F_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(30),
      Q => F0(30),
      R => '0'
    );
\F_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(31),
      Q => F0(31),
      R => '0'
    );
\F_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(3),
      Q => F0(3),
      R => '0'
    );
\F_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(4),
      Q => F0(4),
      R => '0'
    );
\F_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(5),
      Q => F0(5),
      R => '0'
    );
\F_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(6),
      Q => F0(6),
      R => '0'
    );
\F_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(7),
      Q => F0(7),
      R => '0'
    );
\F_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(8),
      Q => F0(8),
      R => '0'
    );
\F_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => F,
      D => CNTR_OUT(9),
      Q => F0(9),
      R => '0'
    );
toggle_reg: unisim.vcomponents.FDRE
     port map (
      C => refclk,
      CE => '1',
      D => COUNTER_REFCLK_inst_n_2,
      Q => toggle,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_labtools_fmeter_0_0 is
  port (
    refclk : in STD_LOGIC;
    fin : in STD_LOGIC_VECTOR ( 0 to 0 );
    F0 : out STD_LOGIC_VECTOR ( 31 downto 0 );
    update : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of zusys_labtools_fmeter_0_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_labtools_fmeter_0_0 : entity is "zusys_labtools_fmeter_0_0,labtools_fmeter,{}";
  attribute downgradeipidentifiedwarnings : string;
  attribute downgradeipidentifiedwarnings of zusys_labtools_fmeter_0_0 : entity is "yes";
  attribute x_core_info : string;
  attribute x_core_info of zusys_labtools_fmeter_0_0 : entity is "labtools_fmeter,Vivado 2019.2";
end zusys_labtools_fmeter_0_0;

architecture STRUCTURE of zusys_labtools_fmeter_0_0 is
  attribute x_interface_info : string;
  attribute x_interface_info of refclk : signal is "xilinx.com:signal:clock:1.0 refclk CLK";
  attribute x_interface_parameter : string;
  attribute x_interface_parameter of refclk : signal is "XIL_INTERFACENAME refclk, FREQ_HZ 99999985, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0";
begin
U0: entity work.zusys_labtools_fmeter_0_0_labtools_fmeter
     port map (
      F0(31 downto 0) => F0(31 downto 0),
      fin(0) => fin(0),
      refclk => refclk,
      update => update
    );
end STRUCTURE;
