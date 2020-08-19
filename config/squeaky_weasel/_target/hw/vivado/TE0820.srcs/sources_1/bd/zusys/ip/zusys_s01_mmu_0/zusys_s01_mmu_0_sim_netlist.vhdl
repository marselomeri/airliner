-- Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
-- Date        : Wed Mar  4 11:48:40 2020
-- Host        : LAPTOP-RVVOIP55 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim -rename_top zusys_s01_mmu_0 -prefix
--               zusys_s01_mmu_0_ zusys_s01_mmu_0_sim_netlist.vhdl
-- Design      : zusys_s01_mmu_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xczu2cg-sfvc784-1-i
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_s01_mmu_0_axi_register_slice_v2_1_20_axic_register_slice is
  port (
    m_axi_arvalid : out STD_LOGIC;
    \gen_read.ar_cnt_reg[5]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \gen_read.ar_cnt_reg[2]\ : out STD_LOGIC_VECTOR ( 4 downto 0 );
    s_axi_arready : out STD_LOGIC;
    \m_payload_i_reg[35]_0\ : out STD_LOGIC_VECTOR ( 34 downto 0 );
    m_valid_i_reg_0 : in STD_LOGIC;
    aclk : in STD_LOGIC;
    s_ready_i_reg_0 : in STD_LOGIC;
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready_0 : in STD_LOGIC_VECTOR ( 5 downto 0 );
    m_axi_arready : in STD_LOGIC;
    ar_pop0 : in STD_LOGIC;
    s_axi_rready : in STD_LOGIC;
    m_axi_rvalid : in STD_LOGIC;
    s_ready_i_reg_1 : in STD_LOGIC;
    \m_payload_i_reg[35]_1\ : in STD_LOGIC_VECTOR ( 34 downto 0 )
  );
end zusys_s01_mmu_0_axi_register_slice_v2_1_20_axic_register_slice;

architecture STRUCTURE of zusys_s01_mmu_0_axi_register_slice_v2_1_20_axic_register_slice is
  signal ar_cnt13_out : STD_LOGIC;
  signal \gen_read.ar_cnt[5]_i_4_n_0\ : STD_LOGIC;
  signal \^m_axi_arvalid\ : STD_LOGIC;
  signal \m_payload_i[31]_i_1__0_n_0\ : STD_LOGIC;
  signal m_valid_i_i_1_n_0 : STD_LOGIC;
  signal p_2_in : STD_LOGIC;
  signal \s_ready_i_i_1__0_n_0\ : STD_LOGIC;
  signal sr_axi_arready : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \gen_read.ar_cnt[2]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \gen_read.ar_cnt[3]_i_1\ : label is "soft_lutpair0";
  attribute SOFT_HLUTNM of \gen_read.ar_cnt[5]_i_5\ : label is "soft_lutpair1";
  attribute SOFT_HLUTNM of m_valid_i_i_1 : label is "soft_lutpair1";
begin
  m_axi_arvalid <= \^m_axi_arvalid\;
\gen_read.ar_cnt[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"69"
    )
        port map (
      I0 => s_axi_arready_0(0),
      I1 => ar_cnt13_out,
      I2 => s_axi_arready_0(1),
      O => \gen_read.ar_cnt_reg[2]\(0)
    );
\gen_read.ar_cnt[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"78E1"
    )
        port map (
      I0 => s_axi_arready_0(0),
      I1 => ar_cnt13_out,
      I2 => s_axi_arready_0(2),
      I3 => s_axi_arready_0(1),
      O => \gen_read.ar_cnt_reg[2]\(1)
    );
\gen_read.ar_cnt[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"7F80FE01"
    )
        port map (
      I0 => ar_cnt13_out,
      I1 => s_axi_arready_0(0),
      I2 => s_axi_arready_0(1),
      I3 => s_axi_arready_0(3),
      I4 => s_axi_arready_0(2),
      O => \gen_read.ar_cnt_reg[2]\(2)
    );
\gen_read.ar_cnt[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFF8000FFFE0001"
    )
        port map (
      I0 => s_axi_arready_0(1),
      I1 => s_axi_arready_0(0),
      I2 => ar_cnt13_out,
      I3 => s_axi_arready_0(2),
      I4 => s_axi_arready_0(4),
      I5 => s_axi_arready_0(3),
      O => \gen_read.ar_cnt_reg[2]\(3)
    );
\gen_read.ar_cnt[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0008080808080808"
    )
        port map (
      I0 => sr_axi_arready,
      I1 => s_axi_arvalid,
      I2 => s_axi_arready_0(5),
      I3 => m_axi_rvalid,
      I4 => s_axi_rready,
      I5 => ar_pop0,
      O => ar_cnt13_out
    );
\gen_read.ar_cnt[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BF40404040404040"
    )
        port map (
      I0 => s_axi_arready_0(5),
      I1 => s_axi_arvalid,
      I2 => sr_axi_arready,
      I3 => ar_pop0,
      I4 => s_axi_rready,
      I5 => m_axi_rvalid,
      O => \gen_read.ar_cnt_reg[5]\(0)
    );
\gen_read.ar_cnt[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFF8000FFFE0001"
    )
        port map (
      I0 => s_axi_arready_0(2),
      I1 => \gen_read.ar_cnt[5]_i_4_n_0\,
      I2 => s_axi_arready_0(1),
      I3 => s_axi_arready_0(3),
      I4 => s_axi_arready_0(5),
      I5 => s_axi_arready_0(4),
      O => \gen_read.ar_cnt_reg[2]\(4)
    );
\gen_read.ar_cnt[5]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFF555515550000"
    )
        port map (
      I0 => s_axi_arready_0(1),
      I1 => ar_pop0,
      I2 => s_axi_rready,
      I3 => m_axi_rvalid,
      I4 => p_2_in,
      I5 => s_axi_arready_0(0),
      O => \gen_read.ar_cnt[5]_i_4_n_0\
    );
\gen_read.ar_cnt[5]_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => s_axi_arready_0(5),
      I1 => s_axi_arvalid,
      I2 => sr_axi_arready,
      O => p_2_in
    );
\m_payload_i[31]_i_1__0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^m_axi_arvalid\,
      O => \m_payload_i[31]_i_1__0_n_0\
    );
\m_payload_i_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(0),
      Q => \m_payload_i_reg[35]_0\(0),
      R => '0'
    );
\m_payload_i_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(10),
      Q => \m_payload_i_reg[35]_0\(10),
      R => '0'
    );
\m_payload_i_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(11),
      Q => \m_payload_i_reg[35]_0\(11),
      R => '0'
    );
\m_payload_i_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(12),
      Q => \m_payload_i_reg[35]_0\(12),
      R => '0'
    );
\m_payload_i_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(13),
      Q => \m_payload_i_reg[35]_0\(13),
      R => '0'
    );
\m_payload_i_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(14),
      Q => \m_payload_i_reg[35]_0\(14),
      R => '0'
    );
\m_payload_i_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(15),
      Q => \m_payload_i_reg[35]_0\(15),
      R => '0'
    );
\m_payload_i_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(16),
      Q => \m_payload_i_reg[35]_0\(16),
      R => '0'
    );
\m_payload_i_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(17),
      Q => \m_payload_i_reg[35]_0\(17),
      R => '0'
    );
\m_payload_i_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(18),
      Q => \m_payload_i_reg[35]_0\(18),
      R => '0'
    );
\m_payload_i_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(19),
      Q => \m_payload_i_reg[35]_0\(19),
      R => '0'
    );
\m_payload_i_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(1),
      Q => \m_payload_i_reg[35]_0\(1),
      R => '0'
    );
\m_payload_i_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(20),
      Q => \m_payload_i_reg[35]_0\(20),
      R => '0'
    );
\m_payload_i_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(21),
      Q => \m_payload_i_reg[35]_0\(21),
      R => '0'
    );
\m_payload_i_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(22),
      Q => \m_payload_i_reg[35]_0\(22),
      R => '0'
    );
\m_payload_i_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(23),
      Q => \m_payload_i_reg[35]_0\(23),
      R => '0'
    );
\m_payload_i_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(24),
      Q => \m_payload_i_reg[35]_0\(24),
      R => '0'
    );
\m_payload_i_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(25),
      Q => \m_payload_i_reg[35]_0\(25),
      R => '0'
    );
\m_payload_i_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(26),
      Q => \m_payload_i_reg[35]_0\(26),
      R => '0'
    );
\m_payload_i_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(27),
      Q => \m_payload_i_reg[35]_0\(27),
      R => '0'
    );
\m_payload_i_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(28),
      Q => \m_payload_i_reg[35]_0\(28),
      R => '0'
    );
\m_payload_i_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(29),
      Q => \m_payload_i_reg[35]_0\(29),
      R => '0'
    );
\m_payload_i_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(2),
      Q => \m_payload_i_reg[35]_0\(2),
      R => '0'
    );
\m_payload_i_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(30),
      Q => \m_payload_i_reg[35]_0\(30),
      R => '0'
    );
\m_payload_i_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(31),
      Q => \m_payload_i_reg[35]_0\(31),
      R => '0'
    );
\m_payload_i_reg[33]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(32),
      Q => \m_payload_i_reg[35]_0\(32),
      R => '0'
    );
\m_payload_i_reg[34]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(33),
      Q => \m_payload_i_reg[35]_0\(33),
      R => '0'
    );
\m_payload_i_reg[35]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(34),
      Q => \m_payload_i_reg[35]_0\(34),
      R => '0'
    );
\m_payload_i_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(3),
      Q => \m_payload_i_reg[35]_0\(3),
      R => '0'
    );
\m_payload_i_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(4),
      Q => \m_payload_i_reg[35]_0\(4),
      R => '0'
    );
\m_payload_i_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(5),
      Q => \m_payload_i_reg[35]_0\(5),
      R => '0'
    );
\m_payload_i_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(6),
      Q => \m_payload_i_reg[35]_0\(6),
      R => '0'
    );
\m_payload_i_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(7),
      Q => \m_payload_i_reg[35]_0\(7),
      R => '0'
    );
\m_payload_i_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(8),
      Q => \m_payload_i_reg[35]_0\(8),
      R => '0'
    );
\m_payload_i_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1__0_n_0\,
      D => \m_payload_i_reg[35]_1\(9),
      Q => \m_payload_i_reg[35]_0\(9),
      R => '0'
    );
m_valid_i_i_1: unisim.vcomponents.LUT4
    generic map(
      INIT => X"202F"
    )
        port map (
      I0 => s_axi_arvalid,
      I1 => s_axi_arready_0(5),
      I2 => sr_axi_arready,
      I3 => m_axi_arready,
      O => m_valid_i_i_1_n_0
    );
m_valid_i_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => aclk,
      CE => '1',
      D => m_valid_i_i_1_n_0,
      Q => \^m_axi_arvalid\,
      R => m_valid_i_reg_0
    );
s_axi_arready_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => sr_axi_arready,
      I1 => s_axi_arready_0(5),
      O => s_axi_arready
    );
\s_ready_i_i_1__0\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FD0DFFFF"
    )
        port map (
      I0 => s_axi_arvalid,
      I1 => s_axi_arready_0(5),
      I2 => \^m_axi_arvalid\,
      I3 => m_axi_arready,
      I4 => s_ready_i_reg_1,
      O => \s_ready_i_i_1__0_n_0\
    );
s_ready_i_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => aclk,
      CE => '1',
      D => \s_ready_i_i_1__0_n_0\,
      Q => sr_axi_arready,
      R => s_ready_i_reg_0
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_s01_mmu_0_axi_register_slice_v2_1_20_axic_register_slice_0 is
  port (
    m_axi_awvalid : out STD_LOGIC;
    \aresetn_d_reg[1]_0\ : out STD_LOGIC;
    \aresetn_d_reg[0]_0\ : out STD_LOGIC;
    \aresetn_d_reg[1]_1\ : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    D : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \gen_write.w_mask_reg\ : out STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    \m_payload_i_reg[35]_0\ : out STD_LOGIC_VECTOR ( 34 downto 0 );
    aclk : in STD_LOGIC;
    s_axi_awvalid : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 5 downto 0 );
    m_axi_awready : in STD_LOGIC;
    aw_pop0 : in STD_LOGIC;
    m_axi_bvalid : in STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    w_mask : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    \m_payload_i_reg[35]_1\ : in STD_LOGIC_VECTOR ( 34 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of zusys_s01_mmu_0_axi_register_slice_v2_1_20_axic_register_slice_0 : entity is "axi_register_slice_v2_1_20_axic_register_slice";
end zusys_s01_mmu_0_axi_register_slice_v2_1_20_axic_register_slice_0;

architecture STRUCTURE of zusys_s01_mmu_0_axi_register_slice_v2_1_20_axic_register_slice_0 is
  signal \^aresetn_d_reg[0]_0\ : STD_LOGIC;
  signal \^aresetn_d_reg[1]_0\ : STD_LOGIC;
  signal \^aresetn_d_reg[1]_1\ : STD_LOGIC;
  signal \aresetn_d_reg_n_0_[0]\ : STD_LOGIC;
  signal aw_cnt119_out : STD_LOGIC;
  signal \gen_write.aw_cnt[5]_i_4_n_0\ : STD_LOGIC;
  signal \^m_axi_awvalid\ : STD_LOGIC;
  signal \m_payload_i[31]_i_1_n_0\ : STD_LOGIC;
  signal m_valid_i_i_2_n_0 : STD_LOGIC;
  signal \p_0_in__0\ : STD_LOGIC;
  signal p_18_in : STD_LOGIC;
  signal s_ready_i_i_2_n_0 : STD_LOGIC;
  signal sr_axi_awready : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \gen_write.aw_cnt[2]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \gen_write.aw_cnt[3]_i_1\ : label is "soft_lutpair2";
  attribute SOFT_HLUTNM of \gen_write.aw_cnt[5]_i_5\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of \gen_write.w_mask_i_1\ : label is "soft_lutpair3";
  attribute SOFT_HLUTNM of m_valid_i_i_2 : label is "soft_lutpair4";
  attribute SOFT_HLUTNM of s_axi_awready_INST_0 : label is "soft_lutpair4";
begin
  \aresetn_d_reg[0]_0\ <= \^aresetn_d_reg[0]_0\;
  \aresetn_d_reg[1]_0\ <= \^aresetn_d_reg[1]_0\;
  \aresetn_d_reg[1]_1\ <= \^aresetn_d_reg[1]_1\;
  m_axi_awvalid <= \^m_axi_awvalid\;
\aresetn_d[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => aresetn,
      O => \p_0_in__0\
    );
\aresetn_d_reg[0]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => aclk,
      CE => '1',
      D => '1',
      Q => \aresetn_d_reg_n_0_[0]\,
      R => \p_0_in__0\
    );
\aresetn_d_reg[1]\: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => aclk,
      CE => '1',
      D => \aresetn_d_reg_n_0_[0]\,
      Q => \^aresetn_d_reg[1]_1\,
      R => \p_0_in__0\
    );
\gen_write.aw_cnt[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"69"
    )
        port map (
      I0 => Q(0),
      I1 => aw_cnt119_out,
      I2 => Q(1),
      O => D(0)
    );
\gen_write.aw_cnt[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"78E1"
    )
        port map (
      I0 => Q(0),
      I1 => aw_cnt119_out,
      I2 => Q(2),
      I3 => Q(1),
      O => D(1)
    );
\gen_write.aw_cnt[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"7F80FE01"
    )
        port map (
      I0 => aw_cnt119_out,
      I1 => Q(0),
      I2 => Q(1),
      I3 => Q(3),
      I4 => Q(2),
      O => D(2)
    );
\gen_write.aw_cnt[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFF8000FFFE0001"
    )
        port map (
      I0 => Q(1),
      I1 => Q(0),
      I2 => aw_cnt119_out,
      I3 => Q(2),
      I4 => Q(4),
      I5 => Q(3),
      O => D(3)
    );
\gen_write.aw_cnt[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0008080808080808"
    )
        port map (
      I0 => sr_axi_awready,
      I1 => s_axi_awvalid,
      I2 => Q(5),
      I3 => s_axi_bready,
      I4 => m_axi_bvalid,
      I5 => aw_pop0,
      O => aw_cnt119_out
    );
\gen_write.aw_cnt[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"BF40404040404040"
    )
        port map (
      I0 => Q(5),
      I1 => s_axi_awvalid,
      I2 => sr_axi_awready,
      I3 => aw_pop0,
      I4 => m_axi_bvalid,
      I5 => s_axi_bready,
      O => E(0)
    );
\gen_write.aw_cnt[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFF8000FFFE0001"
    )
        port map (
      I0 => Q(2),
      I1 => \gen_write.aw_cnt[5]_i_4_n_0\,
      I2 => Q(1),
      I3 => Q(3),
      I4 => Q(5),
      I5 => Q(4),
      O => D(4)
    );
\gen_write.aw_cnt[5]_i_4\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFF555515550000"
    )
        port map (
      I0 => Q(1),
      I1 => aw_pop0,
      I2 => m_axi_bvalid,
      I3 => s_axi_bready,
      I4 => p_18_in,
      I5 => Q(0),
      O => \gen_write.aw_cnt[5]_i_4_n_0\
    );
\gen_write.aw_cnt[5]_i_5\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"40"
    )
        port map (
      I0 => Q(5),
      I1 => s_axi_awvalid,
      I2 => sr_axi_awready,
      O => p_18_in
    );
\gen_write.w_mask_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"A0A000E0"
    )
        port map (
      I0 => w_mask,
      I1 => s_axi_awvalid,
      I2 => \^aresetn_d_reg[1]_1\,
      I3 => sr_axi_awready,
      I4 => Q(5),
      O => \gen_write.w_mask_reg\
    );
\m_payload_i[31]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^m_axi_awvalid\,
      O => \m_payload_i[31]_i_1_n_0\
    );
\m_payload_i_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(0),
      Q => \m_payload_i_reg[35]_0\(0),
      R => '0'
    );
\m_payload_i_reg[10]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(10),
      Q => \m_payload_i_reg[35]_0\(10),
      R => '0'
    );
\m_payload_i_reg[11]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(11),
      Q => \m_payload_i_reg[35]_0\(11),
      R => '0'
    );
\m_payload_i_reg[12]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(12),
      Q => \m_payload_i_reg[35]_0\(12),
      R => '0'
    );
\m_payload_i_reg[13]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(13),
      Q => \m_payload_i_reg[35]_0\(13),
      R => '0'
    );
\m_payload_i_reg[14]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(14),
      Q => \m_payload_i_reg[35]_0\(14),
      R => '0'
    );
\m_payload_i_reg[15]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(15),
      Q => \m_payload_i_reg[35]_0\(15),
      R => '0'
    );
\m_payload_i_reg[16]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(16),
      Q => \m_payload_i_reg[35]_0\(16),
      R => '0'
    );
\m_payload_i_reg[17]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(17),
      Q => \m_payload_i_reg[35]_0\(17),
      R => '0'
    );
\m_payload_i_reg[18]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(18),
      Q => \m_payload_i_reg[35]_0\(18),
      R => '0'
    );
\m_payload_i_reg[19]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(19),
      Q => \m_payload_i_reg[35]_0\(19),
      R => '0'
    );
\m_payload_i_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(1),
      Q => \m_payload_i_reg[35]_0\(1),
      R => '0'
    );
\m_payload_i_reg[20]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(20),
      Q => \m_payload_i_reg[35]_0\(20),
      R => '0'
    );
\m_payload_i_reg[21]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(21),
      Q => \m_payload_i_reg[35]_0\(21),
      R => '0'
    );
\m_payload_i_reg[22]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(22),
      Q => \m_payload_i_reg[35]_0\(22),
      R => '0'
    );
\m_payload_i_reg[23]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(23),
      Q => \m_payload_i_reg[35]_0\(23),
      R => '0'
    );
\m_payload_i_reg[24]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(24),
      Q => \m_payload_i_reg[35]_0\(24),
      R => '0'
    );
\m_payload_i_reg[25]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(25),
      Q => \m_payload_i_reg[35]_0\(25),
      R => '0'
    );
\m_payload_i_reg[26]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(26),
      Q => \m_payload_i_reg[35]_0\(26),
      R => '0'
    );
\m_payload_i_reg[27]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(27),
      Q => \m_payload_i_reg[35]_0\(27),
      R => '0'
    );
\m_payload_i_reg[28]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(28),
      Q => \m_payload_i_reg[35]_0\(28),
      R => '0'
    );
\m_payload_i_reg[29]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(29),
      Q => \m_payload_i_reg[35]_0\(29),
      R => '0'
    );
\m_payload_i_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(2),
      Q => \m_payload_i_reg[35]_0\(2),
      R => '0'
    );
\m_payload_i_reg[30]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(30),
      Q => \m_payload_i_reg[35]_0\(30),
      R => '0'
    );
\m_payload_i_reg[31]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(31),
      Q => \m_payload_i_reg[35]_0\(31),
      R => '0'
    );
\m_payload_i_reg[33]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(32),
      Q => \m_payload_i_reg[35]_0\(32),
      R => '0'
    );
\m_payload_i_reg[34]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(33),
      Q => \m_payload_i_reg[35]_0\(33),
      R => '0'
    );
\m_payload_i_reg[35]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(34),
      Q => \m_payload_i_reg[35]_0\(34),
      R => '0'
    );
\m_payload_i_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(3),
      Q => \m_payload_i_reg[35]_0\(3),
      R => '0'
    );
\m_payload_i_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(4),
      Q => \m_payload_i_reg[35]_0\(4),
      R => '0'
    );
\m_payload_i_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(5),
      Q => \m_payload_i_reg[35]_0\(5),
      R => '0'
    );
\m_payload_i_reg[6]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(6),
      Q => \m_payload_i_reg[35]_0\(6),
      R => '0'
    );
\m_payload_i_reg[7]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(7),
      Q => \m_payload_i_reg[35]_0\(7),
      R => '0'
    );
\m_payload_i_reg[8]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(8),
      Q => \m_payload_i_reg[35]_0\(8),
      R => '0'
    );
\m_payload_i_reg[9]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \m_payload_i[31]_i_1_n_0\,
      D => \m_payload_i_reg[35]_1\(9),
      Q => \m_payload_i_reg[35]_0\(9),
      R => '0'
    );
\m_valid_i_i_1__0\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \^aresetn_d_reg[1]_1\,
      O => \^aresetn_d_reg[1]_0\
    );
m_valid_i_i_2: unisim.vcomponents.LUT4
    generic map(
      INIT => X"202F"
    )
        port map (
      I0 => s_axi_awvalid,
      I1 => Q(5),
      I2 => sr_axi_awready,
      I3 => m_axi_awready,
      O => m_valid_i_i_2_n_0
    );
m_valid_i_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => aclk,
      CE => '1',
      D => m_valid_i_i_2_n_0,
      Q => \^m_axi_awvalid\,
      R => \^aresetn_d_reg[1]_0\
    );
s_axi_awready_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => sr_axi_awready,
      I1 => Q(5),
      O => s_axi_awready
    );
s_ready_i_i_1: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \aresetn_d_reg_n_0_[0]\,
      O => \^aresetn_d_reg[0]_0\
    );
s_ready_i_i_2: unisim.vcomponents.LUT5
    generic map(
      INIT => X"FD0DFFFF"
    )
        port map (
      I0 => s_axi_awvalid,
      I1 => Q(5),
      I2 => \^m_axi_awvalid\,
      I3 => m_axi_awready,
      I4 => \^aresetn_d_reg[1]_1\,
      O => s_ready_i_i_2_n_0
    );
s_ready_i_reg: unisim.vcomponents.FDRE
    generic map(
      INIT => '0'
    )
        port map (
      C => aclk,
      CE => '1',
      D => s_ready_i_i_2_n_0,
      Q => sr_axi_awready,
      R => \^aresetn_d_reg[0]_0\
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_s01_mmu_0_axi_register_slice_v2_1_20_axi_register_slice is
  port (
    m_axi_awvalid : out STD_LOGIC;
    \aresetn_d_reg[1]\ : out STD_LOGIC;
    m_axi_arvalid : out STD_LOGIC;
    E : out STD_LOGIC_VECTOR ( 0 to 0 );
    D : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \gen_read.ar_cnt_reg[5]\ : out STD_LOGIC_VECTOR ( 0 to 0 );
    \gen_read.ar_cnt_reg[2]\ : out STD_LOGIC_VECTOR ( 4 downto 0 );
    \gen_write.w_mask_reg\ : out STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    \m_payload_i_reg[35]\ : out STD_LOGIC_VECTOR ( 34 downto 0 );
    \m_payload_i_reg[35]_0\ : out STD_LOGIC_VECTOR ( 34 downto 0 );
    aclk : in STD_LOGIC;
    s_axi_awvalid : in STD_LOGIC;
    Q : in STD_LOGIC_VECTOR ( 5 downto 0 );
    m_axi_awready : in STD_LOGIC;
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready_0 : in STD_LOGIC_VECTOR ( 5 downto 0 );
    m_axi_arready : in STD_LOGIC;
    aw_pop0 : in STD_LOGIC;
    m_axi_bvalid : in STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    ar_pop0 : in STD_LOGIC;
    s_axi_rready : in STD_LOGIC;
    m_axi_rvalid : in STD_LOGIC;
    w_mask : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    \m_payload_i_reg[35]_1\ : in STD_LOGIC_VECTOR ( 34 downto 0 );
    \m_payload_i_reg[35]_2\ : in STD_LOGIC_VECTOR ( 34 downto 0 )
  );
end zusys_s01_mmu_0_axi_register_slice_v2_1_20_axi_register_slice;

architecture STRUCTURE of zusys_s01_mmu_0_axi_register_slice_v2_1_20_axi_register_slice is
  signal \^aresetn_d_reg[1]\ : STD_LOGIC;
  signal \aw.aw_pipe_n_2\ : STD_LOGIC;
  signal \aw.aw_pipe_n_3\ : STD_LOGIC;
begin
  \aresetn_d_reg[1]\ <= \^aresetn_d_reg[1]\;
\ar.ar_pipe\: entity work.zusys_s01_mmu_0_axi_register_slice_v2_1_20_axic_register_slice
     port map (
      aclk => aclk,
      ar_pop0 => ar_pop0,
      \gen_read.ar_cnt_reg[2]\(4 downto 0) => \gen_read.ar_cnt_reg[2]\(4 downto 0),
      \gen_read.ar_cnt_reg[5]\(0) => \gen_read.ar_cnt_reg[5]\(0),
      m_axi_arready => m_axi_arready,
      m_axi_arvalid => m_axi_arvalid,
      m_axi_rvalid => m_axi_rvalid,
      \m_payload_i_reg[35]_0\(34 downto 0) => \m_payload_i_reg[35]_0\(34 downto 0),
      \m_payload_i_reg[35]_1\(34 downto 0) => \m_payload_i_reg[35]_2\(34 downto 0),
      m_valid_i_reg_0 => \^aresetn_d_reg[1]\,
      s_axi_arready => s_axi_arready,
      s_axi_arready_0(5 downto 0) => s_axi_arready_0(5 downto 0),
      s_axi_arvalid => s_axi_arvalid,
      s_axi_rready => s_axi_rready,
      s_ready_i_reg_0 => \aw.aw_pipe_n_2\,
      s_ready_i_reg_1 => \aw.aw_pipe_n_3\
    );
\aw.aw_pipe\: entity work.zusys_s01_mmu_0_axi_register_slice_v2_1_20_axic_register_slice_0
     port map (
      D(4 downto 0) => D(4 downto 0),
      E(0) => E(0),
      Q(5 downto 0) => Q(5 downto 0),
      aclk => aclk,
      aresetn => aresetn,
      \aresetn_d_reg[0]_0\ => \aw.aw_pipe_n_2\,
      \aresetn_d_reg[1]_0\ => \^aresetn_d_reg[1]\,
      \aresetn_d_reg[1]_1\ => \aw.aw_pipe_n_3\,
      aw_pop0 => aw_pop0,
      \gen_write.w_mask_reg\ => \gen_write.w_mask_reg\,
      m_axi_awready => m_axi_awready,
      m_axi_awvalid => m_axi_awvalid,
      m_axi_bvalid => m_axi_bvalid,
      \m_payload_i_reg[35]_0\(34 downto 0) => \m_payload_i_reg[35]\(34 downto 0),
      \m_payload_i_reg[35]_1\(34 downto 0) => \m_payload_i_reg[35]_1\(34 downto 0),
      s_axi_awready => s_axi_awready,
      s_axi_awvalid => s_axi_awvalid,
      s_axi_bready => s_axi_bready,
      w_mask => w_mask
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_s01_mmu_0_axi_mmu_v2_1_18_top is
  port (
    aclk : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    s_axi_awid : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_awlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    s_axi_awsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_awburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_awlock : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_awcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_awqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_awuser : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    s_axi_wid : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_wlast : in STD_LOGIC;
    s_axi_wuser : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_wvalid : in STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_bid : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_buser : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_bvalid : out STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_arid : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_araddr : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_arlen : in STD_LOGIC_VECTOR ( 7 downto 0 );
    s_axi_arsize : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_arburst : in STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_arlock : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_arcache : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_arqos : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_aruser : in STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_rid : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_rlast : out STD_LOGIC;
    s_axi_ruser : out STD_LOGIC_VECTOR ( 0 to 0 );
    s_axi_rvalid : out STD_LOGIC;
    s_axi_rready : in STD_LOGIC;
    m_axi_awid : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_awaddr : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_awlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_awsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_awburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_awlock : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_awcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_awqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_awuser : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_awvalid : out STD_LOGIC;
    m_axi_awready : in STD_LOGIC;
    m_axi_wid : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_wlast : out STD_LOGIC;
    m_axi_wuser : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_wvalid : out STD_LOGIC;
    m_axi_wready : in STD_LOGIC;
    m_axi_bid : in STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_buser : in STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_bvalid : in STD_LOGIC;
    m_axi_bready : out STD_LOGIC;
    m_axi_arid : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_araddr : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_arlen : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_arsize : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_arburst : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_arlock : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_arcache : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_arqos : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_aruser : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_arvalid : out STD_LOGIC;
    m_axi_arready : in STD_LOGIC;
    m_axi_rid : in STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_rlast : in STD_LOGIC;
    m_axi_ruser : in STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_rvalid : in STD_LOGIC;
    m_axi_rready : out STD_LOGIC
  );
  attribute C_AXI_ARUSER_WIDTH : integer;
  attribute C_AXI_ARUSER_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_AXI_AWUSER_WIDTH : integer;
  attribute C_AXI_AWUSER_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_AXI_BUSER_WIDTH : integer;
  attribute C_AXI_BUSER_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_AXI_DATA_WIDTH : integer;
  attribute C_AXI_DATA_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 32;
  attribute C_AXI_ID_WIDTH : integer;
  attribute C_AXI_ID_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_AXI_PROTOCOL : integer;
  attribute C_AXI_PROTOCOL of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 2;
  attribute C_AXI_RUSER_WIDTH : integer;
  attribute C_AXI_RUSER_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_AXI_SUPPORTS_USER_SIGNALS : integer;
  attribute C_AXI_SUPPORTS_USER_SIGNALS of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 0;
  attribute C_AXI_WUSER_WIDTH : integer;
  attribute C_AXI_WUSER_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_BASE_ADDR : string;
  attribute C_BASE_ADDR of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "64'b0000000000000000000000000000000000000000000000000000000000000000";
  attribute C_DEST : string;
  attribute C_DEST of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "1'b0";
  attribute C_DEST_WIDTH : integer;
  attribute C_DEST_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_FAMILY : string;
  attribute C_FAMILY of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "zynquplus";
  attribute C_M_AXI_ADDR_WIDTH : integer;
  attribute C_M_AXI_ADDR_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 32;
  attribute C_M_AXI_SUPPORTS_READ : string;
  attribute C_M_AXI_SUPPORTS_READ of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "1'b1";
  attribute C_M_AXI_SUPPORTS_WRITE : string;
  attribute C_M_AXI_SUPPORTS_WRITE of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "1'b1";
  attribute C_NUM_RANGES : integer;
  attribute C_NUM_RANGES of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_PREFIX : string;
  attribute C_PREFIX of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "1'b0";
  attribute C_PREFIX_WIDTH : integer;
  attribute C_PREFIX_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_RANGE_SIZE : integer;
  attribute C_RANGE_SIZE of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 32;
  attribute C_S_AXI_ADDR_WIDTH : integer;
  attribute C_S_AXI_ADDR_WIDTH of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 32;
  attribute C_S_AXI_SUPPORTS_READ : integer;
  attribute C_S_AXI_SUPPORTS_READ of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_S_AXI_SUPPORTS_WRITE : integer;
  attribute C_S_AXI_SUPPORTS_WRITE of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute C_USES_DEST : integer;
  attribute C_USES_DEST of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 0;
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "yes";
  attribute P_AXI3 : integer;
  attribute P_AXI3 of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute P_AXI4 : integer;
  attribute P_AXI4 of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 0;
  attribute P_AXILITE : integer;
  attribute P_AXILITE of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 2;
  attribute P_DECERR : string;
  attribute P_DECERR of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "2'b11";
  attribute P_NUM_RANGES_LOG : integer;
  attribute P_NUM_RANGES_LOG of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is 1;
  attribute R_DECERR : string;
  attribute R_DECERR of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "2'b11";
  attribute R_IDLE : string;
  attribute R_IDLE of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "2'b00";
  attribute R_PENDING : string;
  attribute R_PENDING of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "2'b01";
  attribute W_DECERR : string;
  attribute W_DECERR of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "2'b11";
  attribute W_IDLE : string;
  attribute W_IDLE of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "2'b00";
  attribute W_PENDING : string;
  attribute W_PENDING of zusys_s01_mmu_0_axi_mmu_v2_1_18_top : entity is "2'b01";
end zusys_s01_mmu_0_axi_mmu_v2_1_18_top;

architecture STRUCTURE of zusys_s01_mmu_0_axi_mmu_v2_1_18_top is
  signal \<const0>\ : STD_LOGIC;
  signal \<const1>\ : STD_LOGIC;
  signal ar_pop0 : STD_LOGIC;
  signal aw_pop0 : STD_LOGIC;
  signal \gen_read.ar_cnt[0]_i_1_n_0\ : STD_LOGIC;
  signal \gen_read.ar_cnt_reg\ : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal \gen_write.aw_cnt[0]_i_1_n_0\ : STD_LOGIC;
  signal \gen_write.aw_cnt_reg\ : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal \gen_write.w_cnt[0]_i_1_n_0\ : STD_LOGIC;
  signal \gen_write.w_cnt[1]_i_1_n_0\ : STD_LOGIC;
  signal \gen_write.w_cnt[2]_i_1_n_0\ : STD_LOGIC;
  signal \gen_write.w_cnt[3]_i_1_n_0\ : STD_LOGIC;
  signal \gen_write.w_cnt[4]_i_1_n_0\ : STD_LOGIC;
  signal \gen_write.w_cnt[5]_i_1_n_0\ : STD_LOGIC;
  signal \gen_write.w_cnt[5]_i_2_n_0\ : STD_LOGIC;
  signal \gen_write.w_cnt[5]_i_3_n_0\ : STD_LOGIC;
  signal \gen_write.w_cnt_reg\ : STD_LOGIC_VECTOR ( 5 downto 0 );
  signal \^m_axi_bresp\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \^m_axi_bvalid\ : STD_LOGIC;
  signal \^m_axi_rdata\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \^m_axi_rresp\ : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal \^m_axi_rvalid\ : STD_LOGIC;
  signal p_14_in : STD_LOGIC;
  signal register_slice_inst_n_1 : STD_LOGIC;
  signal register_slice_inst_n_10 : STD_LOGIC;
  signal register_slice_inst_n_11 : STD_LOGIC;
  signal register_slice_inst_n_12 : STD_LOGIC;
  signal register_slice_inst_n_13 : STD_LOGIC;
  signal register_slice_inst_n_14 : STD_LOGIC;
  signal register_slice_inst_n_15 : STD_LOGIC;
  signal register_slice_inst_n_3 : STD_LOGIC;
  signal register_slice_inst_n_4 : STD_LOGIC;
  signal register_slice_inst_n_5 : STD_LOGIC;
  signal register_slice_inst_n_6 : STD_LOGIC;
  signal register_slice_inst_n_7 : STD_LOGIC;
  signal register_slice_inst_n_8 : STD_LOGIC;
  signal register_slice_inst_n_9 : STD_LOGIC;
  signal \^s_axi_bready\ : STD_LOGIC;
  signal \^s_axi_rready\ : STD_LOGIC;
  signal \^s_axi_wdata\ : STD_LOGIC_VECTOR ( 31 downto 0 );
  signal \^s_axi_wstrb\ : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal sr_axi_wvalid122_in : STD_LOGIC;
  signal w_cnt115_out : STD_LOGIC;
  signal w_mask : STD_LOGIC;
  attribute SOFT_HLUTNM : string;
  attribute SOFT_HLUTNM of \gen_write.w_cnt[2]_i_1\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of \gen_write.w_cnt[3]_i_1\ : label is "soft_lutpair5";
  attribute SOFT_HLUTNM of m_axi_wvalid_INST_0 : label is "soft_lutpair6";
  attribute SOFT_HLUTNM of s_axi_wready_INST_0 : label is "soft_lutpair6";
begin
  \^m_axi_bresp\(1 downto 0) <= m_axi_bresp(1 downto 0);
  \^m_axi_bvalid\ <= m_axi_bvalid;
  \^m_axi_rdata\(31 downto 0) <= m_axi_rdata(31 downto 0);
  \^m_axi_rresp\(1 downto 0) <= m_axi_rresp(1 downto 0);
  \^m_axi_rvalid\ <= m_axi_rvalid;
  \^s_axi_bready\ <= s_axi_bready;
  \^s_axi_rready\ <= s_axi_rready;
  \^s_axi_wdata\(31 downto 0) <= s_axi_wdata(31 downto 0);
  \^s_axi_wstrb\(3 downto 0) <= s_axi_wstrb(3 downto 0);
  m_axi_arburst(1) <= \<const0>\;
  m_axi_arburst(0) <= \<const0>\;
  m_axi_arcache(3) <= \<const0>\;
  m_axi_arcache(2) <= \<const0>\;
  m_axi_arcache(1) <= \<const0>\;
  m_axi_arcache(0) <= \<const0>\;
  m_axi_arid(0) <= \<const0>\;
  m_axi_arlen(7) <= \<const0>\;
  m_axi_arlen(6) <= \<const0>\;
  m_axi_arlen(5) <= \<const0>\;
  m_axi_arlen(4) <= \<const0>\;
  m_axi_arlen(3) <= \<const0>\;
  m_axi_arlen(2) <= \<const0>\;
  m_axi_arlen(1) <= \<const0>\;
  m_axi_arlen(0) <= \<const0>\;
  m_axi_arlock(0) <= \<const0>\;
  m_axi_arqos(3) <= \<const0>\;
  m_axi_arqos(2) <= \<const0>\;
  m_axi_arqos(1) <= \<const0>\;
  m_axi_arqos(0) <= \<const0>\;
  m_axi_arsize(2) <= \<const0>\;
  m_axi_arsize(1) <= \<const1>\;
  m_axi_arsize(0) <= \<const0>\;
  m_axi_aruser(0) <= \<const0>\;
  m_axi_awburst(1) <= \<const0>\;
  m_axi_awburst(0) <= \<const0>\;
  m_axi_awcache(3) <= \<const0>\;
  m_axi_awcache(2) <= \<const0>\;
  m_axi_awcache(1) <= \<const0>\;
  m_axi_awcache(0) <= \<const0>\;
  m_axi_awid(0) <= \<const0>\;
  m_axi_awlen(7) <= \<const0>\;
  m_axi_awlen(6) <= \<const0>\;
  m_axi_awlen(5) <= \<const0>\;
  m_axi_awlen(4) <= \<const0>\;
  m_axi_awlen(3) <= \<const0>\;
  m_axi_awlen(2) <= \<const0>\;
  m_axi_awlen(1) <= \<const0>\;
  m_axi_awlen(0) <= \<const0>\;
  m_axi_awlock(0) <= \<const0>\;
  m_axi_awqos(3) <= \<const0>\;
  m_axi_awqos(2) <= \<const0>\;
  m_axi_awqos(1) <= \<const0>\;
  m_axi_awqos(0) <= \<const0>\;
  m_axi_awsize(2) <= \<const0>\;
  m_axi_awsize(1) <= \<const1>\;
  m_axi_awsize(0) <= \<const0>\;
  m_axi_awuser(0) <= \<const0>\;
  m_axi_bready <= \^s_axi_bready\;
  m_axi_rready <= \^s_axi_rready\;
  m_axi_wdata(31 downto 0) <= \^s_axi_wdata\(31 downto 0);
  m_axi_wid(0) <= \<const0>\;
  m_axi_wlast <= \<const1>\;
  m_axi_wstrb(3 downto 0) <= \^s_axi_wstrb\(3 downto 0);
  m_axi_wuser(0) <= \<const0>\;
  s_axi_bid(0) <= \<const0>\;
  s_axi_bresp(1 downto 0) <= \^m_axi_bresp\(1 downto 0);
  s_axi_buser(0) <= \<const0>\;
  s_axi_bvalid <= \^m_axi_bvalid\;
  s_axi_rdata(31 downto 0) <= \^m_axi_rdata\(31 downto 0);
  s_axi_rid(0) <= \<const0>\;
  s_axi_rlast <= \<const1>\;
  s_axi_rresp(1 downto 0) <= \^m_axi_rresp\(1 downto 0);
  s_axi_ruser(0) <= \<const0>\;
  s_axi_rvalid <= \^m_axi_rvalid\;
GND: unisim.vcomponents.GND
     port map (
      G => \<const0>\
    );
VCC: unisim.vcomponents.VCC
     port map (
      P => \<const1>\
    );
\gen_read.ar_cnt[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \gen_read.ar_cnt_reg\(0),
      O => \gen_read.ar_cnt[0]_i_1_n_0\
    );
\gen_read.ar_cnt[5]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => \gen_read.ar_cnt_reg\(5),
      I1 => \gen_read.ar_cnt_reg\(4),
      I2 => \gen_read.ar_cnt_reg\(1),
      I3 => \gen_read.ar_cnt_reg\(0),
      I4 => \gen_read.ar_cnt_reg\(3),
      I5 => \gen_read.ar_cnt_reg\(2),
      O => ar_pop0
    );
\gen_read.ar_cnt_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_9,
      D => \gen_read.ar_cnt[0]_i_1_n_0\,
      Q => \gen_read.ar_cnt_reg\(0),
      R => register_slice_inst_n_1
    );
\gen_read.ar_cnt_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_9,
      D => register_slice_inst_n_14,
      Q => \gen_read.ar_cnt_reg\(1),
      R => register_slice_inst_n_1
    );
\gen_read.ar_cnt_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_9,
      D => register_slice_inst_n_13,
      Q => \gen_read.ar_cnt_reg\(2),
      R => register_slice_inst_n_1
    );
\gen_read.ar_cnt_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_9,
      D => register_slice_inst_n_12,
      Q => \gen_read.ar_cnt_reg\(3),
      R => register_slice_inst_n_1
    );
\gen_read.ar_cnt_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_9,
      D => register_slice_inst_n_11,
      Q => \gen_read.ar_cnt_reg\(4),
      R => register_slice_inst_n_1
    );
\gen_read.ar_cnt_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_9,
      D => register_slice_inst_n_10,
      Q => \gen_read.ar_cnt_reg\(5),
      R => register_slice_inst_n_1
    );
\gen_write.aw_cnt[0]_i_1\: unisim.vcomponents.LUT1
    generic map(
      INIT => X"1"
    )
        port map (
      I0 => \gen_write.aw_cnt_reg\(0),
      O => \gen_write.aw_cnt[0]_i_1_n_0\
    );
\gen_write.aw_cnt[5]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => \gen_write.aw_cnt_reg\(5),
      I1 => \gen_write.aw_cnt_reg\(4),
      I2 => \gen_write.aw_cnt_reg\(1),
      I3 => \gen_write.aw_cnt_reg\(0),
      I4 => \gen_write.aw_cnt_reg\(3),
      I5 => \gen_write.aw_cnt_reg\(2),
      O => aw_pop0
    );
\gen_write.aw_cnt_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_3,
      D => \gen_write.aw_cnt[0]_i_1_n_0\,
      Q => \gen_write.aw_cnt_reg\(0),
      R => register_slice_inst_n_1
    );
\gen_write.aw_cnt_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_3,
      D => register_slice_inst_n_8,
      Q => \gen_write.aw_cnt_reg\(1),
      R => register_slice_inst_n_1
    );
\gen_write.aw_cnt_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_3,
      D => register_slice_inst_n_7,
      Q => \gen_write.aw_cnt_reg\(2),
      R => register_slice_inst_n_1
    );
\gen_write.aw_cnt_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_3,
      D => register_slice_inst_n_6,
      Q => \gen_write.aw_cnt_reg\(3),
      R => register_slice_inst_n_1
    );
\gen_write.aw_cnt_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_3,
      D => register_slice_inst_n_5,
      Q => \gen_write.aw_cnt_reg\(4),
      R => register_slice_inst_n_1
    );
\gen_write.aw_cnt_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => register_slice_inst_n_3,
      D => register_slice_inst_n_4,
      Q => \gen_write.aw_cnt_reg\(5),
      R => register_slice_inst_n_1
    );
\gen_write.w_cnt[0]_i_1\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"6"
    )
        port map (
      I0 => \gen_write.w_cnt[5]_i_1_n_0\,
      I1 => \gen_write.w_cnt_reg\(0),
      O => \gen_write.w_cnt[0]_i_1_n_0\
    );
\gen_write.w_cnt[1]_i_1\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"69"
    )
        port map (
      I0 => \gen_write.w_cnt_reg\(0),
      I1 => w_cnt115_out,
      I2 => \gen_write.w_cnt_reg\(1),
      O => \gen_write.w_cnt[1]_i_1_n_0\
    );
\gen_write.w_cnt[2]_i_1\: unisim.vcomponents.LUT4
    generic map(
      INIT => X"78E1"
    )
        port map (
      I0 => \gen_write.w_cnt_reg\(0),
      I1 => w_cnt115_out,
      I2 => \gen_write.w_cnt_reg\(2),
      I3 => \gen_write.w_cnt_reg\(1),
      O => \gen_write.w_cnt[2]_i_1_n_0\
    );
\gen_write.w_cnt[3]_i_1\: unisim.vcomponents.LUT5
    generic map(
      INIT => X"7F80FE01"
    )
        port map (
      I0 => w_cnt115_out,
      I1 => \gen_write.w_cnt_reg\(0),
      I2 => \gen_write.w_cnt_reg\(1),
      I3 => \gen_write.w_cnt_reg\(3),
      I4 => \gen_write.w_cnt_reg\(2),
      O => \gen_write.w_cnt[3]_i_1_n_0\
    );
\gen_write.w_cnt[4]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFF8000FFFE0001"
    )
        port map (
      I0 => \gen_write.w_cnt_reg\(1),
      I1 => \gen_write.w_cnt_reg\(0),
      I2 => w_cnt115_out,
      I3 => \gen_write.w_cnt_reg\(2),
      I4 => \gen_write.w_cnt_reg\(4),
      I5 => \gen_write.w_cnt_reg\(3),
      O => \gen_write.w_cnt[4]_i_1_n_0\
    );
\gen_write.w_cnt[4]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"0004040404040404"
    )
        port map (
      I0 => w_mask,
      I1 => s_axi_awvalid,
      I2 => \gen_write.aw_cnt_reg\(5),
      I3 => sr_axi_wvalid122_in,
      I4 => s_axi_wvalid,
      I5 => m_axi_wready,
      O => w_cnt115_out
    );
\gen_write.w_cnt[5]_i_1\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FB04040404040404"
    )
        port map (
      I0 => \gen_write.aw_cnt_reg\(5),
      I1 => s_axi_awvalid,
      I2 => w_mask,
      I3 => m_axi_wready,
      I4 => s_axi_wvalid,
      I5 => sr_axi_wvalid122_in,
      O => \gen_write.w_cnt[5]_i_1_n_0\
    );
\gen_write.w_cnt[5]_i_2\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFF8000FFFE0001"
    )
        port map (
      I0 => \gen_write.w_cnt_reg\(2),
      I1 => \gen_write.w_cnt[5]_i_3_n_0\,
      I2 => \gen_write.w_cnt_reg\(1),
      I3 => \gen_write.w_cnt_reg\(3),
      I4 => \gen_write.w_cnt_reg\(5),
      I5 => \gen_write.w_cnt_reg\(4),
      O => \gen_write.w_cnt[5]_i_2_n_0\
    );
\gen_write.w_cnt[5]_i_3\: unisim.vcomponents.LUT6
    generic map(
      INIT => X"7FFF555515550000"
    )
        port map (
      I0 => \gen_write.w_cnt_reg\(1),
      I1 => m_axi_wready,
      I2 => s_axi_wvalid,
      I3 => sr_axi_wvalid122_in,
      I4 => p_14_in,
      I5 => \gen_write.w_cnt_reg\(0),
      O => \gen_write.w_cnt[5]_i_3_n_0\
    );
\gen_write.w_cnt[5]_i_4\: unisim.vcomponents.LUT3
    generic map(
      INIT => X"04"
    )
        port map (
      I0 => \gen_write.aw_cnt_reg\(5),
      I1 => s_axi_awvalid,
      I2 => w_mask,
      O => p_14_in
    );
\gen_write.w_cnt_reg[0]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => '1',
      D => \gen_write.w_cnt[0]_i_1_n_0\,
      Q => \gen_write.w_cnt_reg\(0),
      R => register_slice_inst_n_1
    );
\gen_write.w_cnt_reg[1]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \gen_write.w_cnt[5]_i_1_n_0\,
      D => \gen_write.w_cnt[1]_i_1_n_0\,
      Q => \gen_write.w_cnt_reg\(1),
      R => register_slice_inst_n_1
    );
\gen_write.w_cnt_reg[2]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \gen_write.w_cnt[5]_i_1_n_0\,
      D => \gen_write.w_cnt[2]_i_1_n_0\,
      Q => \gen_write.w_cnt_reg\(2),
      R => register_slice_inst_n_1
    );
\gen_write.w_cnt_reg[3]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \gen_write.w_cnt[5]_i_1_n_0\,
      D => \gen_write.w_cnt[3]_i_1_n_0\,
      Q => \gen_write.w_cnt_reg\(3),
      R => register_slice_inst_n_1
    );
\gen_write.w_cnt_reg[4]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \gen_write.w_cnt[5]_i_1_n_0\,
      D => \gen_write.w_cnt[4]_i_1_n_0\,
      Q => \gen_write.w_cnt_reg\(4),
      R => register_slice_inst_n_1
    );
\gen_write.w_cnt_reg[5]\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => \gen_write.w_cnt[5]_i_1_n_0\,
      D => \gen_write.w_cnt[5]_i_2_n_0\,
      Q => \gen_write.w_cnt_reg\(5),
      R => register_slice_inst_n_1
    );
\gen_write.w_mask_reg\: unisim.vcomponents.FDRE
     port map (
      C => aclk,
      CE => '1',
      D => register_slice_inst_n_15,
      Q => w_mask,
      R => '0'
    );
m_axi_wvalid_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => sr_axi_wvalid122_in,
      I1 => s_axi_wvalid,
      O => m_axi_wvalid
    );
register_slice_inst: entity work.zusys_s01_mmu_0_axi_register_slice_v2_1_20_axi_register_slice
     port map (
      D(4) => register_slice_inst_n_4,
      D(3) => register_slice_inst_n_5,
      D(2) => register_slice_inst_n_6,
      D(1) => register_slice_inst_n_7,
      D(0) => register_slice_inst_n_8,
      E(0) => register_slice_inst_n_3,
      Q(5 downto 0) => \gen_write.aw_cnt_reg\(5 downto 0),
      aclk => aclk,
      ar_pop0 => ar_pop0,
      aresetn => aresetn,
      \aresetn_d_reg[1]\ => register_slice_inst_n_1,
      aw_pop0 => aw_pop0,
      \gen_read.ar_cnt_reg[2]\(4) => register_slice_inst_n_10,
      \gen_read.ar_cnt_reg[2]\(3) => register_slice_inst_n_11,
      \gen_read.ar_cnt_reg[2]\(2) => register_slice_inst_n_12,
      \gen_read.ar_cnt_reg[2]\(1) => register_slice_inst_n_13,
      \gen_read.ar_cnt_reg[2]\(0) => register_slice_inst_n_14,
      \gen_read.ar_cnt_reg[5]\(0) => register_slice_inst_n_9,
      \gen_write.w_mask_reg\ => register_slice_inst_n_15,
      m_axi_arready => m_axi_arready,
      m_axi_arvalid => m_axi_arvalid,
      m_axi_awready => m_axi_awready,
      m_axi_awvalid => m_axi_awvalid,
      m_axi_bvalid => \^m_axi_bvalid\,
      m_axi_rvalid => \^m_axi_rvalid\,
      \m_payload_i_reg[35]\(34 downto 32) => m_axi_awprot(2 downto 0),
      \m_payload_i_reg[35]\(31 downto 0) => m_axi_awaddr(31 downto 0),
      \m_payload_i_reg[35]_0\(34 downto 32) => m_axi_arprot(2 downto 0),
      \m_payload_i_reg[35]_0\(31 downto 0) => m_axi_araddr(31 downto 0),
      \m_payload_i_reg[35]_1\(34 downto 32) => s_axi_awprot(2 downto 0),
      \m_payload_i_reg[35]_1\(31 downto 0) => s_axi_awaddr(31 downto 0),
      \m_payload_i_reg[35]_2\(34 downto 32) => s_axi_arprot(2 downto 0),
      \m_payload_i_reg[35]_2\(31 downto 0) => s_axi_araddr(31 downto 0),
      s_axi_arready => s_axi_arready,
      s_axi_arready_0(5 downto 0) => \gen_read.ar_cnt_reg\(5 downto 0),
      s_axi_arvalid => s_axi_arvalid,
      s_axi_awready => s_axi_awready,
      s_axi_awvalid => s_axi_awvalid,
      s_axi_bready => \^s_axi_bready\,
      s_axi_rready => \^s_axi_rready\,
      w_mask => w_mask
    );
s_axi_wready_INST_0: unisim.vcomponents.LUT2
    generic map(
      INIT => X"8"
    )
        port map (
      I0 => m_axi_wready,
      I1 => sr_axi_wvalid122_in,
      O => s_axi_wready
    );
s_axi_wready_INST_0_i_1: unisim.vcomponents.LUT6
    generic map(
      INIT => X"FFFFFFFFFFFFFFFE"
    )
        port map (
      I0 => \gen_write.w_cnt_reg\(2),
      I1 => \gen_write.w_cnt_reg\(0),
      I2 => \gen_write.w_cnt_reg\(1),
      I3 => \gen_write.w_cnt_reg\(4),
      I4 => \gen_write.w_cnt_reg\(3),
      I5 => \gen_write.w_cnt_reg\(5),
      O => sr_axi_wvalid122_in
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity zusys_s01_mmu_0 is
  port (
    aclk : in STD_LOGIC;
    aresetn : in STD_LOGIC;
    s_axi_awaddr : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_awprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_awvalid : in STD_LOGIC;
    s_axi_awready : out STD_LOGIC;
    s_axi_wdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_wstrb : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_wvalid : in STD_LOGIC;
    s_axi_wready : out STD_LOGIC;
    s_axi_bresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_bvalid : out STD_LOGIC;
    s_axi_bready : in STD_LOGIC;
    s_axi_araddr : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_arprot : in STD_LOGIC_VECTOR ( 2 downto 0 );
    s_axi_arvalid : in STD_LOGIC;
    s_axi_arready : out STD_LOGIC;
    s_axi_rdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_rresp : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_rvalid : out STD_LOGIC;
    s_axi_rready : in STD_LOGIC;
    m_axi_awaddr : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_awprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_awvalid : out STD_LOGIC;
    m_axi_awready : in STD_LOGIC;
    m_axi_wdata : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_wstrb : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_wvalid : out STD_LOGIC;
    m_axi_wready : in STD_LOGIC;
    m_axi_bresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_bvalid : in STD_LOGIC;
    m_axi_bready : out STD_LOGIC;
    m_axi_araddr : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_arprot : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_arvalid : out STD_LOGIC;
    m_axi_arready : in STD_LOGIC;
    m_axi_rdata : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_rresp : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_rvalid : in STD_LOGIC;
    m_axi_rready : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of zusys_s01_mmu_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of zusys_s01_mmu_0 : entity is "zusys_s01_mmu_0,axi_mmu_v2_1_18_top,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of zusys_s01_mmu_0 : entity is "yes";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of zusys_s01_mmu_0 : entity is "axi_mmu_v2_1_18_top,Vivado 2019.2";
end zusys_s01_mmu_0;

architecture STRUCTURE of zusys_s01_mmu_0 is
  signal NLW_inst_m_axi_wlast_UNCONNECTED : STD_LOGIC;
  signal NLW_inst_s_axi_rlast_UNCONNECTED : STD_LOGIC;
  signal NLW_inst_m_axi_arburst_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_inst_m_axi_arcache_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_inst_m_axi_arid_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_m_axi_arlen_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_inst_m_axi_arlock_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_m_axi_arqos_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_inst_m_axi_arsize_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_inst_m_axi_aruser_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_m_axi_awburst_UNCONNECTED : STD_LOGIC_VECTOR ( 1 downto 0 );
  signal NLW_inst_m_axi_awcache_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_inst_m_axi_awid_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_m_axi_awlen_UNCONNECTED : STD_LOGIC_VECTOR ( 7 downto 0 );
  signal NLW_inst_m_axi_awlock_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_m_axi_awqos_UNCONNECTED : STD_LOGIC_VECTOR ( 3 downto 0 );
  signal NLW_inst_m_axi_awsize_UNCONNECTED : STD_LOGIC_VECTOR ( 2 downto 0 );
  signal NLW_inst_m_axi_awuser_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_m_axi_wid_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_m_axi_wuser_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_s_axi_bid_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_s_axi_buser_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_s_axi_rid_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  signal NLW_inst_s_axi_ruser_UNCONNECTED : STD_LOGIC_VECTOR ( 0 to 0 );
  attribute C_AXI_ARUSER_WIDTH : integer;
  attribute C_AXI_ARUSER_WIDTH of inst : label is 1;
  attribute C_AXI_AWUSER_WIDTH : integer;
  attribute C_AXI_AWUSER_WIDTH of inst : label is 1;
  attribute C_AXI_BUSER_WIDTH : integer;
  attribute C_AXI_BUSER_WIDTH of inst : label is 1;
  attribute C_AXI_DATA_WIDTH : integer;
  attribute C_AXI_DATA_WIDTH of inst : label is 32;
  attribute C_AXI_ID_WIDTH : integer;
  attribute C_AXI_ID_WIDTH of inst : label is 1;
  attribute C_AXI_PROTOCOL : integer;
  attribute C_AXI_PROTOCOL of inst : label is 2;
  attribute C_AXI_RUSER_WIDTH : integer;
  attribute C_AXI_RUSER_WIDTH of inst : label is 1;
  attribute C_AXI_SUPPORTS_USER_SIGNALS : integer;
  attribute C_AXI_SUPPORTS_USER_SIGNALS of inst : label is 0;
  attribute C_AXI_WUSER_WIDTH : integer;
  attribute C_AXI_WUSER_WIDTH of inst : label is 1;
  attribute C_BASE_ADDR : string;
  attribute C_BASE_ADDR of inst : label is "64'b0000000000000000000000000000000000000000000000000000000000000000";
  attribute C_DEST : string;
  attribute C_DEST of inst : label is "1'b0";
  attribute C_DEST_WIDTH : integer;
  attribute C_DEST_WIDTH of inst : label is 1;
  attribute C_FAMILY : string;
  attribute C_FAMILY of inst : label is "zynquplus";
  attribute C_M_AXI_ADDR_WIDTH : integer;
  attribute C_M_AXI_ADDR_WIDTH of inst : label is 32;
  attribute C_M_AXI_SUPPORTS_READ : string;
  attribute C_M_AXI_SUPPORTS_READ of inst : label is "1'b1";
  attribute C_M_AXI_SUPPORTS_WRITE : string;
  attribute C_M_AXI_SUPPORTS_WRITE of inst : label is "1'b1";
  attribute C_NUM_RANGES : integer;
  attribute C_NUM_RANGES of inst : label is 1;
  attribute C_PREFIX : string;
  attribute C_PREFIX of inst : label is "1'b0";
  attribute C_PREFIX_WIDTH : integer;
  attribute C_PREFIX_WIDTH of inst : label is 1;
  attribute C_RANGE_SIZE : integer;
  attribute C_RANGE_SIZE of inst : label is 32;
  attribute C_S_AXI_ADDR_WIDTH : integer;
  attribute C_S_AXI_ADDR_WIDTH of inst : label is 32;
  attribute C_S_AXI_SUPPORTS_READ : integer;
  attribute C_S_AXI_SUPPORTS_READ of inst : label is 1;
  attribute C_S_AXI_SUPPORTS_WRITE : integer;
  attribute C_S_AXI_SUPPORTS_WRITE of inst : label is 1;
  attribute C_USES_DEST : integer;
  attribute C_USES_DEST of inst : label is 0;
  attribute DowngradeIPIdentifiedWarnings of inst : label is "yes";
  attribute P_AXI3 : integer;
  attribute P_AXI3 of inst : label is 1;
  attribute P_AXI4 : integer;
  attribute P_AXI4 of inst : label is 0;
  attribute P_AXILITE : integer;
  attribute P_AXILITE of inst : label is 2;
  attribute P_DECERR : string;
  attribute P_DECERR of inst : label is "2'b11";
  attribute P_NUM_RANGES_LOG : integer;
  attribute P_NUM_RANGES_LOG of inst : label is 1;
  attribute R_DECERR : string;
  attribute R_DECERR of inst : label is "2'b11";
  attribute R_IDLE : string;
  attribute R_IDLE of inst : label is "2'b00";
  attribute R_PENDING : string;
  attribute R_PENDING of inst : label is "2'b01";
  attribute W_DECERR : string;
  attribute W_DECERR of inst : label is "2'b11";
  attribute W_IDLE : string;
  attribute W_IDLE of inst : label is "2'b00";
  attribute W_PENDING : string;
  attribute W_PENDING of inst : label is "2'b01";
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of aclk : signal is "xilinx.com:signal:clock:1.0 CLK CLK";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of aclk : signal is "XIL_INTERFACENAME CLK, FREQ_HZ 99999985, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, ASSOCIATED_BUSIF S_AXI:M_AXI, ASSOCIATED_RESET ARESETN, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of aresetn : signal is "xilinx.com:signal:reset:1.0 RST RST";
  attribute X_INTERFACE_PARAMETER of aresetn : signal is "XIL_INTERFACENAME RST, POLARITY ACTIVE_LOW, INSERT_VIP 0, TYPE INTERCONNECT";
  attribute X_INTERFACE_INFO of m_axi_arready : signal is "xilinx.com:interface:aximm:1.0 M_AXI ARREADY";
  attribute X_INTERFACE_INFO of m_axi_arvalid : signal is "xilinx.com:interface:aximm:1.0 M_AXI ARVALID";
  attribute X_INTERFACE_INFO of m_axi_awready : signal is "xilinx.com:interface:aximm:1.0 M_AXI AWREADY";
  attribute X_INTERFACE_INFO of m_axi_awvalid : signal is "xilinx.com:interface:aximm:1.0 M_AXI AWVALID";
  attribute X_INTERFACE_INFO of m_axi_bready : signal is "xilinx.com:interface:aximm:1.0 M_AXI BREADY";
  attribute X_INTERFACE_INFO of m_axi_bvalid : signal is "xilinx.com:interface:aximm:1.0 M_AXI BVALID";
  attribute X_INTERFACE_INFO of m_axi_rready : signal is "xilinx.com:interface:aximm:1.0 M_AXI RREADY";
  attribute X_INTERFACE_PARAMETER of m_axi_rready : signal is "XIL_INTERFACENAME M_AXI, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 99999985, ID_WIDTH 0, ADDR_WIDTH 32, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 1, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of m_axi_rvalid : signal is "xilinx.com:interface:aximm:1.0 M_AXI RVALID";
  attribute X_INTERFACE_INFO of m_axi_wready : signal is "xilinx.com:interface:aximm:1.0 M_AXI WREADY";
  attribute X_INTERFACE_INFO of m_axi_wvalid : signal is "xilinx.com:interface:aximm:1.0 M_AXI WVALID";
  attribute X_INTERFACE_INFO of s_axi_arready : signal is "xilinx.com:interface:aximm:1.0 S_AXI ARREADY";
  attribute X_INTERFACE_INFO of s_axi_arvalid : signal is "xilinx.com:interface:aximm:1.0 S_AXI ARVALID";
  attribute X_INTERFACE_INFO of s_axi_awready : signal is "xilinx.com:interface:aximm:1.0 S_AXI AWREADY";
  attribute X_INTERFACE_INFO of s_axi_awvalid : signal is "xilinx.com:interface:aximm:1.0 S_AXI AWVALID";
  attribute X_INTERFACE_INFO of s_axi_bready : signal is "xilinx.com:interface:aximm:1.0 S_AXI BREADY";
  attribute X_INTERFACE_INFO of s_axi_bvalid : signal is "xilinx.com:interface:aximm:1.0 S_AXI BVALID";
  attribute X_INTERFACE_INFO of s_axi_rready : signal is "xilinx.com:interface:aximm:1.0 S_AXI RREADY";
  attribute X_INTERFACE_PARAMETER of s_axi_rready : signal is "XIL_INTERFACENAME S_AXI, DATA_WIDTH 32, PROTOCOL AXI4LITE, FREQ_HZ 99999985, ID_WIDTH 0, ADDR_WIDTH 32, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, READ_WRITE_MODE READ_WRITE, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 1, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of s_axi_rvalid : signal is "xilinx.com:interface:aximm:1.0 S_AXI RVALID";
  attribute X_INTERFACE_INFO of s_axi_wready : signal is "xilinx.com:interface:aximm:1.0 S_AXI WREADY";
  attribute X_INTERFACE_INFO of s_axi_wvalid : signal is "xilinx.com:interface:aximm:1.0 S_AXI WVALID";
  attribute X_INTERFACE_INFO of m_axi_araddr : signal is "xilinx.com:interface:aximm:1.0 M_AXI ARADDR";
  attribute X_INTERFACE_INFO of m_axi_arprot : signal is "xilinx.com:interface:aximm:1.0 M_AXI ARPROT";
  attribute X_INTERFACE_INFO of m_axi_awaddr : signal is "xilinx.com:interface:aximm:1.0 M_AXI AWADDR";
  attribute X_INTERFACE_INFO of m_axi_awprot : signal is "xilinx.com:interface:aximm:1.0 M_AXI AWPROT";
  attribute X_INTERFACE_INFO of m_axi_bresp : signal is "xilinx.com:interface:aximm:1.0 M_AXI BRESP";
  attribute X_INTERFACE_INFO of m_axi_rdata : signal is "xilinx.com:interface:aximm:1.0 M_AXI RDATA";
  attribute X_INTERFACE_INFO of m_axi_rresp : signal is "xilinx.com:interface:aximm:1.0 M_AXI RRESP";
  attribute X_INTERFACE_INFO of m_axi_wdata : signal is "xilinx.com:interface:aximm:1.0 M_AXI WDATA";
  attribute X_INTERFACE_INFO of m_axi_wstrb : signal is "xilinx.com:interface:aximm:1.0 M_AXI WSTRB";
  attribute X_INTERFACE_INFO of s_axi_araddr : signal is "xilinx.com:interface:aximm:1.0 S_AXI ARADDR";
  attribute X_INTERFACE_INFO of s_axi_arprot : signal is "xilinx.com:interface:aximm:1.0 S_AXI ARPROT";
  attribute X_INTERFACE_INFO of s_axi_awaddr : signal is "xilinx.com:interface:aximm:1.0 S_AXI AWADDR";
  attribute X_INTERFACE_INFO of s_axi_awprot : signal is "xilinx.com:interface:aximm:1.0 S_AXI AWPROT";
  attribute X_INTERFACE_INFO of s_axi_bresp : signal is "xilinx.com:interface:aximm:1.0 S_AXI BRESP";
  attribute X_INTERFACE_INFO of s_axi_rdata : signal is "xilinx.com:interface:aximm:1.0 S_AXI RDATA";
  attribute X_INTERFACE_INFO of s_axi_rresp : signal is "xilinx.com:interface:aximm:1.0 S_AXI RRESP";
  attribute X_INTERFACE_INFO of s_axi_wdata : signal is "xilinx.com:interface:aximm:1.0 S_AXI WDATA";
  attribute X_INTERFACE_INFO of s_axi_wstrb : signal is "xilinx.com:interface:aximm:1.0 S_AXI WSTRB";
begin
inst: entity work.zusys_s01_mmu_0_axi_mmu_v2_1_18_top
     port map (
      aclk => aclk,
      aresetn => aresetn,
      m_axi_araddr(31 downto 0) => m_axi_araddr(31 downto 0),
      m_axi_arburst(1 downto 0) => NLW_inst_m_axi_arburst_UNCONNECTED(1 downto 0),
      m_axi_arcache(3 downto 0) => NLW_inst_m_axi_arcache_UNCONNECTED(3 downto 0),
      m_axi_arid(0) => NLW_inst_m_axi_arid_UNCONNECTED(0),
      m_axi_arlen(7 downto 0) => NLW_inst_m_axi_arlen_UNCONNECTED(7 downto 0),
      m_axi_arlock(0) => NLW_inst_m_axi_arlock_UNCONNECTED(0),
      m_axi_arprot(2 downto 0) => m_axi_arprot(2 downto 0),
      m_axi_arqos(3 downto 0) => NLW_inst_m_axi_arqos_UNCONNECTED(3 downto 0),
      m_axi_arready => m_axi_arready,
      m_axi_arsize(2 downto 0) => NLW_inst_m_axi_arsize_UNCONNECTED(2 downto 0),
      m_axi_aruser(0) => NLW_inst_m_axi_aruser_UNCONNECTED(0),
      m_axi_arvalid => m_axi_arvalid,
      m_axi_awaddr(31 downto 0) => m_axi_awaddr(31 downto 0),
      m_axi_awburst(1 downto 0) => NLW_inst_m_axi_awburst_UNCONNECTED(1 downto 0),
      m_axi_awcache(3 downto 0) => NLW_inst_m_axi_awcache_UNCONNECTED(3 downto 0),
      m_axi_awid(0) => NLW_inst_m_axi_awid_UNCONNECTED(0),
      m_axi_awlen(7 downto 0) => NLW_inst_m_axi_awlen_UNCONNECTED(7 downto 0),
      m_axi_awlock(0) => NLW_inst_m_axi_awlock_UNCONNECTED(0),
      m_axi_awprot(2 downto 0) => m_axi_awprot(2 downto 0),
      m_axi_awqos(3 downto 0) => NLW_inst_m_axi_awqos_UNCONNECTED(3 downto 0),
      m_axi_awready => m_axi_awready,
      m_axi_awsize(2 downto 0) => NLW_inst_m_axi_awsize_UNCONNECTED(2 downto 0),
      m_axi_awuser(0) => NLW_inst_m_axi_awuser_UNCONNECTED(0),
      m_axi_awvalid => m_axi_awvalid,
      m_axi_bid(0) => '0',
      m_axi_bready => m_axi_bready,
      m_axi_bresp(1 downto 0) => m_axi_bresp(1 downto 0),
      m_axi_buser(0) => '0',
      m_axi_bvalid => m_axi_bvalid,
      m_axi_rdata(31 downto 0) => m_axi_rdata(31 downto 0),
      m_axi_rid(0) => '0',
      m_axi_rlast => '1',
      m_axi_rready => m_axi_rready,
      m_axi_rresp(1 downto 0) => m_axi_rresp(1 downto 0),
      m_axi_ruser(0) => '0',
      m_axi_rvalid => m_axi_rvalid,
      m_axi_wdata(31 downto 0) => m_axi_wdata(31 downto 0),
      m_axi_wid(0) => NLW_inst_m_axi_wid_UNCONNECTED(0),
      m_axi_wlast => NLW_inst_m_axi_wlast_UNCONNECTED,
      m_axi_wready => m_axi_wready,
      m_axi_wstrb(3 downto 0) => m_axi_wstrb(3 downto 0),
      m_axi_wuser(0) => NLW_inst_m_axi_wuser_UNCONNECTED(0),
      m_axi_wvalid => m_axi_wvalid,
      s_axi_araddr(31 downto 0) => s_axi_araddr(31 downto 0),
      s_axi_arburst(1 downto 0) => B"01",
      s_axi_arcache(3 downto 0) => B"0000",
      s_axi_arid(0) => '0',
      s_axi_arlen(7 downto 0) => B"00000000",
      s_axi_arlock(0) => '0',
      s_axi_arprot(2 downto 0) => s_axi_arprot(2 downto 0),
      s_axi_arqos(3 downto 0) => B"0000",
      s_axi_arready => s_axi_arready,
      s_axi_arsize(2 downto 0) => B"000",
      s_axi_aruser(0) => '0',
      s_axi_arvalid => s_axi_arvalid,
      s_axi_awaddr(31 downto 0) => s_axi_awaddr(31 downto 0),
      s_axi_awburst(1 downto 0) => B"01",
      s_axi_awcache(3 downto 0) => B"0000",
      s_axi_awid(0) => '0',
      s_axi_awlen(7 downto 0) => B"00000000",
      s_axi_awlock(0) => '0',
      s_axi_awprot(2 downto 0) => s_axi_awprot(2 downto 0),
      s_axi_awqos(3 downto 0) => B"0000",
      s_axi_awready => s_axi_awready,
      s_axi_awsize(2 downto 0) => B"000",
      s_axi_awuser(0) => '0',
      s_axi_awvalid => s_axi_awvalid,
      s_axi_bid(0) => NLW_inst_s_axi_bid_UNCONNECTED(0),
      s_axi_bready => s_axi_bready,
      s_axi_bresp(1 downto 0) => s_axi_bresp(1 downto 0),
      s_axi_buser(0) => NLW_inst_s_axi_buser_UNCONNECTED(0),
      s_axi_bvalid => s_axi_bvalid,
      s_axi_rdata(31 downto 0) => s_axi_rdata(31 downto 0),
      s_axi_rid(0) => NLW_inst_s_axi_rid_UNCONNECTED(0),
      s_axi_rlast => NLW_inst_s_axi_rlast_UNCONNECTED,
      s_axi_rready => s_axi_rready,
      s_axi_rresp(1 downto 0) => s_axi_rresp(1 downto 0),
      s_axi_ruser(0) => NLW_inst_s_axi_ruser_UNCONNECTED(0),
      s_axi_rvalid => s_axi_rvalid,
      s_axi_wdata(31 downto 0) => s_axi_wdata(31 downto 0),
      s_axi_wid(0) => '0',
      s_axi_wlast => '1',
      s_axi_wready => s_axi_wready,
      s_axi_wstrb(3 downto 0) => s_axi_wstrb(3 downto 0),
      s_axi_wuser(0) => '0',
      s_axi_wvalid => s_axi_wvalid
    );
end STRUCTURE;
