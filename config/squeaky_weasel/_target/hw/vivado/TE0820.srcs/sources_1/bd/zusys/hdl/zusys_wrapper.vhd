--Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2019.2 (win64) Build 2708876 Wed Nov  6 21:40:23 MST 2019
--Date        : Fri Mar  6 18:40:09 2020
--Host        : LAPTOP-RVVOIP55 running 64-bit major release  (build 9200)
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
    GPIO_0_tri_io : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    SI5338_CLK0_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    SI5338_CLK0_D_clk_p : in STD_LOGIC_VECTOR ( 0 to 0 );
    SPI_0_0_io0_io : inout STD_LOGIC;
    SPI_0_0_io1_io : inout STD_LOGIC;
    SPI_0_0_sck_io : inout STD_LOGIC;
    SPI_0_0_ss_io : inout STD_LOGIC;
    SPI_1_0_io0_io : inout STD_LOGIC;
    SPI_1_0_io1_io : inout STD_LOGIC;
    SPI_1_0_sck_io : inout STD_LOGIC;
    SPI_1_0_ss_io : inout STD_LOGIC;
    UART_1_0_rxd : in STD_LOGIC;
    UART_1_0_txd : out STD_LOGIC;
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
    SI5338_CLK0_D_clk_n : in STD_LOGIC_VECTOR ( 0 to 0 );
    GPIO_0_tri_i : in STD_LOGIC_VECTOR ( 31 downto 0 );
    GPIO_0_tri_o : out STD_LOGIC_VECTOR ( 31 downto 0 );
    GPIO_0_tri_t : out STD_LOGIC_VECTOR ( 31 downto 0 );
    SPI_0_0_sck_i : in STD_LOGIC;
    SPI_0_0_sck_o : out STD_LOGIC;
    SPI_0_0_sck_t : out STD_LOGIC;
    SPI_0_0_io1_i : in STD_LOGIC;
    SPI_0_0_io0_o : out STD_LOGIC;
    SPI_0_0_io0_t : out STD_LOGIC;
    SPI_0_0_io0_i : in STD_LOGIC;
    SPI_0_0_io1_o : out STD_LOGIC;
    SPI_0_0_io1_t : out STD_LOGIC;
    SPI_0_0_ss_i : in STD_LOGIC;
    SPI_0_0_ss_o : out STD_LOGIC;
    SPI_0_0_ss_t : out STD_LOGIC;
    SPI_1_0_sck_i : in STD_LOGIC;
    SPI_1_0_sck_o : out STD_LOGIC;
    SPI_1_0_sck_t : out STD_LOGIC;
    SPI_1_0_io1_i : in STD_LOGIC;
    SPI_1_0_io0_o : out STD_LOGIC;
    SPI_1_0_io0_t : out STD_LOGIC;
    SPI_1_0_io0_i : in STD_LOGIC;
    SPI_1_0_io1_o : out STD_LOGIC;
    SPI_1_0_io1_t : out STD_LOGIC;
    SPI_1_0_ss_i : in STD_LOGIC;
    SPI_1_0_ss_o : out STD_LOGIC;
    SPI_1_0_ss_t : out STD_LOGIC;
    UART_1_0_txd : out STD_LOGIC;
    UART_1_0_rxd : in STD_LOGIC
  );
  end component zusys;
  component IOBUF is
  port (
    I : in STD_LOGIC;
    O : out STD_LOGIC;
    T : in STD_LOGIC;
    IO : inout STD_LOGIC
  );
  end component IOBUF;
  signal GPIO_0_tri_i_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal GPIO_0_tri_i_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal GPIO_0_tri_i_10 : STD_LOGIC_VECTOR ( 10 to 10 );
  signal GPIO_0_tri_i_11 : STD_LOGIC_VECTOR ( 11 to 11 );
  signal GPIO_0_tri_i_12 : STD_LOGIC_VECTOR ( 12 to 12 );
  signal GPIO_0_tri_i_13 : STD_LOGIC_VECTOR ( 13 to 13 );
  signal GPIO_0_tri_i_14 : STD_LOGIC_VECTOR ( 14 to 14 );
  signal GPIO_0_tri_i_15 : STD_LOGIC_VECTOR ( 15 to 15 );
  signal GPIO_0_tri_i_16 : STD_LOGIC_VECTOR ( 16 to 16 );
  signal GPIO_0_tri_i_17 : STD_LOGIC_VECTOR ( 17 to 17 );
  signal GPIO_0_tri_i_18 : STD_LOGIC_VECTOR ( 18 to 18 );
  signal GPIO_0_tri_i_19 : STD_LOGIC_VECTOR ( 19 to 19 );
  signal GPIO_0_tri_i_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal GPIO_0_tri_i_20 : STD_LOGIC_VECTOR ( 20 to 20 );
  signal GPIO_0_tri_i_21 : STD_LOGIC_VECTOR ( 21 to 21 );
  signal GPIO_0_tri_i_22 : STD_LOGIC_VECTOR ( 22 to 22 );
  signal GPIO_0_tri_i_23 : STD_LOGIC_VECTOR ( 23 to 23 );
  signal GPIO_0_tri_i_24 : STD_LOGIC_VECTOR ( 24 to 24 );
  signal GPIO_0_tri_i_25 : STD_LOGIC_VECTOR ( 25 to 25 );
  signal GPIO_0_tri_i_26 : STD_LOGIC_VECTOR ( 26 to 26 );
  signal GPIO_0_tri_i_27 : STD_LOGIC_VECTOR ( 27 to 27 );
  signal GPIO_0_tri_i_28 : STD_LOGIC_VECTOR ( 28 to 28 );
  signal GPIO_0_tri_i_29 : STD_LOGIC_VECTOR ( 29 to 29 );
  signal GPIO_0_tri_i_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal GPIO_0_tri_i_30 : STD_LOGIC_VECTOR ( 30 to 30 );
  signal GPIO_0_tri_i_31 : STD_LOGIC_VECTOR ( 31 to 31 );
  signal GPIO_0_tri_i_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal GPIO_0_tri_i_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal GPIO_0_tri_i_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal GPIO_0_tri_i_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal GPIO_0_tri_i_8 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal GPIO_0_tri_i_9 : STD_LOGIC_VECTOR ( 9 to 9 );
  signal GPIO_0_tri_io_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal GPIO_0_tri_io_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal GPIO_0_tri_io_10 : STD_LOGIC_VECTOR ( 10 to 10 );
  signal GPIO_0_tri_io_11 : STD_LOGIC_VECTOR ( 11 to 11 );
  signal GPIO_0_tri_io_12 : STD_LOGIC_VECTOR ( 12 to 12 );
  signal GPIO_0_tri_io_13 : STD_LOGIC_VECTOR ( 13 to 13 );
  signal GPIO_0_tri_io_14 : STD_LOGIC_VECTOR ( 14 to 14 );
  signal GPIO_0_tri_io_15 : STD_LOGIC_VECTOR ( 15 to 15 );
  signal GPIO_0_tri_io_16 : STD_LOGIC_VECTOR ( 16 to 16 );
  signal GPIO_0_tri_io_17 : STD_LOGIC_VECTOR ( 17 to 17 );
  signal GPIO_0_tri_io_18 : STD_LOGIC_VECTOR ( 18 to 18 );
  signal GPIO_0_tri_io_19 : STD_LOGIC_VECTOR ( 19 to 19 );
  signal GPIO_0_tri_io_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal GPIO_0_tri_io_20 : STD_LOGIC_VECTOR ( 20 to 20 );
  signal GPIO_0_tri_io_21 : STD_LOGIC_VECTOR ( 21 to 21 );
  signal GPIO_0_tri_io_22 : STD_LOGIC_VECTOR ( 22 to 22 );
  signal GPIO_0_tri_io_23 : STD_LOGIC_VECTOR ( 23 to 23 );
  signal GPIO_0_tri_io_24 : STD_LOGIC_VECTOR ( 24 to 24 );
  signal GPIO_0_tri_io_25 : STD_LOGIC_VECTOR ( 25 to 25 );
  signal GPIO_0_tri_io_26 : STD_LOGIC_VECTOR ( 26 to 26 );
  signal GPIO_0_tri_io_27 : STD_LOGIC_VECTOR ( 27 to 27 );
  signal GPIO_0_tri_io_28 : STD_LOGIC_VECTOR ( 28 to 28 );
  signal GPIO_0_tri_io_29 : STD_LOGIC_VECTOR ( 29 to 29 );
  signal GPIO_0_tri_io_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal GPIO_0_tri_io_30 : STD_LOGIC_VECTOR ( 30 to 30 );
  signal GPIO_0_tri_io_31 : STD_LOGIC_VECTOR ( 31 to 31 );
  signal GPIO_0_tri_io_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal GPIO_0_tri_io_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal GPIO_0_tri_io_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal GPIO_0_tri_io_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal GPIO_0_tri_io_8 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal GPIO_0_tri_io_9 : STD_LOGIC_VECTOR ( 9 to 9 );
  signal GPIO_0_tri_o_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal GPIO_0_tri_o_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal GPIO_0_tri_o_10 : STD_LOGIC_VECTOR ( 10 to 10 );
  signal GPIO_0_tri_o_11 : STD_LOGIC_VECTOR ( 11 to 11 );
  signal GPIO_0_tri_o_12 : STD_LOGIC_VECTOR ( 12 to 12 );
  signal GPIO_0_tri_o_13 : STD_LOGIC_VECTOR ( 13 to 13 );
  signal GPIO_0_tri_o_14 : STD_LOGIC_VECTOR ( 14 to 14 );
  signal GPIO_0_tri_o_15 : STD_LOGIC_VECTOR ( 15 to 15 );
  signal GPIO_0_tri_o_16 : STD_LOGIC_VECTOR ( 16 to 16 );
  signal GPIO_0_tri_o_17 : STD_LOGIC_VECTOR ( 17 to 17 );
  signal GPIO_0_tri_o_18 : STD_LOGIC_VECTOR ( 18 to 18 );
  signal GPIO_0_tri_o_19 : STD_LOGIC_VECTOR ( 19 to 19 );
  signal GPIO_0_tri_o_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal GPIO_0_tri_o_20 : STD_LOGIC_VECTOR ( 20 to 20 );
  signal GPIO_0_tri_o_21 : STD_LOGIC_VECTOR ( 21 to 21 );
  signal GPIO_0_tri_o_22 : STD_LOGIC_VECTOR ( 22 to 22 );
  signal GPIO_0_tri_o_23 : STD_LOGIC_VECTOR ( 23 to 23 );
  signal GPIO_0_tri_o_24 : STD_LOGIC_VECTOR ( 24 to 24 );
  signal GPIO_0_tri_o_25 : STD_LOGIC_VECTOR ( 25 to 25 );
  signal GPIO_0_tri_o_26 : STD_LOGIC_VECTOR ( 26 to 26 );
  signal GPIO_0_tri_o_27 : STD_LOGIC_VECTOR ( 27 to 27 );
  signal GPIO_0_tri_o_28 : STD_LOGIC_VECTOR ( 28 to 28 );
  signal GPIO_0_tri_o_29 : STD_LOGIC_VECTOR ( 29 to 29 );
  signal GPIO_0_tri_o_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal GPIO_0_tri_o_30 : STD_LOGIC_VECTOR ( 30 to 30 );
  signal GPIO_0_tri_o_31 : STD_LOGIC_VECTOR ( 31 to 31 );
  signal GPIO_0_tri_o_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal GPIO_0_tri_o_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal GPIO_0_tri_o_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal GPIO_0_tri_o_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal GPIO_0_tri_o_8 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal GPIO_0_tri_o_9 : STD_LOGIC_VECTOR ( 9 to 9 );
  signal GPIO_0_tri_t_0 : STD_LOGIC_VECTOR ( 0 to 0 );
  signal GPIO_0_tri_t_1 : STD_LOGIC_VECTOR ( 1 to 1 );
  signal GPIO_0_tri_t_10 : STD_LOGIC_VECTOR ( 10 to 10 );
  signal GPIO_0_tri_t_11 : STD_LOGIC_VECTOR ( 11 to 11 );
  signal GPIO_0_tri_t_12 : STD_LOGIC_VECTOR ( 12 to 12 );
  signal GPIO_0_tri_t_13 : STD_LOGIC_VECTOR ( 13 to 13 );
  signal GPIO_0_tri_t_14 : STD_LOGIC_VECTOR ( 14 to 14 );
  signal GPIO_0_tri_t_15 : STD_LOGIC_VECTOR ( 15 to 15 );
  signal GPIO_0_tri_t_16 : STD_LOGIC_VECTOR ( 16 to 16 );
  signal GPIO_0_tri_t_17 : STD_LOGIC_VECTOR ( 17 to 17 );
  signal GPIO_0_tri_t_18 : STD_LOGIC_VECTOR ( 18 to 18 );
  signal GPIO_0_tri_t_19 : STD_LOGIC_VECTOR ( 19 to 19 );
  signal GPIO_0_tri_t_2 : STD_LOGIC_VECTOR ( 2 to 2 );
  signal GPIO_0_tri_t_20 : STD_LOGIC_VECTOR ( 20 to 20 );
  signal GPIO_0_tri_t_21 : STD_LOGIC_VECTOR ( 21 to 21 );
  signal GPIO_0_tri_t_22 : STD_LOGIC_VECTOR ( 22 to 22 );
  signal GPIO_0_tri_t_23 : STD_LOGIC_VECTOR ( 23 to 23 );
  signal GPIO_0_tri_t_24 : STD_LOGIC_VECTOR ( 24 to 24 );
  signal GPIO_0_tri_t_25 : STD_LOGIC_VECTOR ( 25 to 25 );
  signal GPIO_0_tri_t_26 : STD_LOGIC_VECTOR ( 26 to 26 );
  signal GPIO_0_tri_t_27 : STD_LOGIC_VECTOR ( 27 to 27 );
  signal GPIO_0_tri_t_28 : STD_LOGIC_VECTOR ( 28 to 28 );
  signal GPIO_0_tri_t_29 : STD_LOGIC_VECTOR ( 29 to 29 );
  signal GPIO_0_tri_t_3 : STD_LOGIC_VECTOR ( 3 to 3 );
  signal GPIO_0_tri_t_30 : STD_LOGIC_VECTOR ( 30 to 30 );
  signal GPIO_0_tri_t_31 : STD_LOGIC_VECTOR ( 31 to 31 );
  signal GPIO_0_tri_t_4 : STD_LOGIC_VECTOR ( 4 to 4 );
  signal GPIO_0_tri_t_5 : STD_LOGIC_VECTOR ( 5 to 5 );
  signal GPIO_0_tri_t_6 : STD_LOGIC_VECTOR ( 6 to 6 );
  signal GPIO_0_tri_t_7 : STD_LOGIC_VECTOR ( 7 to 7 );
  signal GPIO_0_tri_t_8 : STD_LOGIC_VECTOR ( 8 to 8 );
  signal GPIO_0_tri_t_9 : STD_LOGIC_VECTOR ( 9 to 9 );
  signal SPI_0_0_io0_i : STD_LOGIC;
  signal SPI_0_0_io0_o : STD_LOGIC;
  signal SPI_0_0_io0_t : STD_LOGIC;
  signal SPI_0_0_io1_i : STD_LOGIC;
  signal SPI_0_0_io1_o : STD_LOGIC;
  signal SPI_0_0_io1_t : STD_LOGIC;
  signal SPI_0_0_sck_i : STD_LOGIC;
  signal SPI_0_0_sck_o : STD_LOGIC;
  signal SPI_0_0_sck_t : STD_LOGIC;
  signal SPI_0_0_ss_i : STD_LOGIC;
  signal SPI_0_0_ss_o : STD_LOGIC;
  signal SPI_0_0_ss_t : STD_LOGIC;
  signal SPI_1_0_io0_i : STD_LOGIC;
  signal SPI_1_0_io0_o : STD_LOGIC;
  signal SPI_1_0_io0_t : STD_LOGIC;
  signal SPI_1_0_io1_i : STD_LOGIC;
  signal SPI_1_0_io1_o : STD_LOGIC;
  signal SPI_1_0_io1_t : STD_LOGIC;
  signal SPI_1_0_sck_i : STD_LOGIC;
  signal SPI_1_0_sck_o : STD_LOGIC;
  signal SPI_1_0_sck_t : STD_LOGIC;
  signal SPI_1_0_ss_i : STD_LOGIC;
  signal SPI_1_0_ss_o : STD_LOGIC;
  signal SPI_1_0_ss_t : STD_LOGIC;
begin
GPIO_0_tri_iobuf_0: component IOBUF
     port map (
      I => GPIO_0_tri_o_0(0),
      IO => GPIO_0_tri_io(0),
      O => GPIO_0_tri_i_0(0),
      T => GPIO_0_tri_t_0(0)
    );
GPIO_0_tri_iobuf_1: component IOBUF
     port map (
      I => GPIO_0_tri_o_1(1),
      IO => GPIO_0_tri_io(1),
      O => GPIO_0_tri_i_1(1),
      T => GPIO_0_tri_t_1(1)
    );
GPIO_0_tri_iobuf_10: component IOBUF
     port map (
      I => GPIO_0_tri_o_10(10),
      IO => GPIO_0_tri_io(10),
      O => GPIO_0_tri_i_10(10),
      T => GPIO_0_tri_t_10(10)
    );
GPIO_0_tri_iobuf_11: component IOBUF
     port map (
      I => GPIO_0_tri_o_11(11),
      IO => GPIO_0_tri_io(11),
      O => GPIO_0_tri_i_11(11),
      T => GPIO_0_tri_t_11(11)
    );
GPIO_0_tri_iobuf_12: component IOBUF
     port map (
      I => GPIO_0_tri_o_12(12),
      IO => GPIO_0_tri_io(12),
      O => GPIO_0_tri_i_12(12),
      T => GPIO_0_tri_t_12(12)
    );
GPIO_0_tri_iobuf_13: component IOBUF
     port map (
      I => GPIO_0_tri_o_13(13),
      IO => GPIO_0_tri_io(13),
      O => GPIO_0_tri_i_13(13),
      T => GPIO_0_tri_t_13(13)
    );
GPIO_0_tri_iobuf_14: component IOBUF
     port map (
      I => GPIO_0_tri_o_14(14),
      IO => GPIO_0_tri_io(14),
      O => GPIO_0_tri_i_14(14),
      T => GPIO_0_tri_t_14(14)
    );
GPIO_0_tri_iobuf_15: component IOBUF
     port map (
      I => GPIO_0_tri_o_15(15),
      IO => GPIO_0_tri_io(15),
      O => GPIO_0_tri_i_15(15),
      T => GPIO_0_tri_t_15(15)
    );
GPIO_0_tri_iobuf_16: component IOBUF
     port map (
      I => GPIO_0_tri_o_16(16),
      IO => GPIO_0_tri_io(16),
      O => GPIO_0_tri_i_16(16),
      T => GPIO_0_tri_t_16(16)
    );
GPIO_0_tri_iobuf_17: component IOBUF
     port map (
      I => GPIO_0_tri_o_17(17),
      IO => GPIO_0_tri_io(17),
      O => GPIO_0_tri_i_17(17),
      T => GPIO_0_tri_t_17(17)
    );
GPIO_0_tri_iobuf_18: component IOBUF
     port map (
      I => GPIO_0_tri_o_18(18),
      IO => GPIO_0_tri_io(18),
      O => GPIO_0_tri_i_18(18),
      T => GPIO_0_tri_t_18(18)
    );
GPIO_0_tri_iobuf_19: component IOBUF
     port map (
      I => GPIO_0_tri_o_19(19),
      IO => GPIO_0_tri_io(19),
      O => GPIO_0_tri_i_19(19),
      T => GPIO_0_tri_t_19(19)
    );
GPIO_0_tri_iobuf_2: component IOBUF
     port map (
      I => GPIO_0_tri_o_2(2),
      IO => GPIO_0_tri_io(2),
      O => GPIO_0_tri_i_2(2),
      T => GPIO_0_tri_t_2(2)
    );
GPIO_0_tri_iobuf_20: component IOBUF
     port map (
      I => GPIO_0_tri_o_20(20),
      IO => GPIO_0_tri_io(20),
      O => GPIO_0_tri_i_20(20),
      T => GPIO_0_tri_t_20(20)
    );
GPIO_0_tri_iobuf_21: component IOBUF
     port map (
      I => GPIO_0_tri_o_21(21),
      IO => GPIO_0_tri_io(21),
      O => GPIO_0_tri_i_21(21),
      T => GPIO_0_tri_t_21(21)
    );
GPIO_0_tri_iobuf_22: component IOBUF
     port map (
      I => GPIO_0_tri_o_22(22),
      IO => GPIO_0_tri_io(22),
      O => GPIO_0_tri_i_22(22),
      T => GPIO_0_tri_t_22(22)
    );
GPIO_0_tri_iobuf_23: component IOBUF
     port map (
      I => GPIO_0_tri_o_23(23),
      IO => GPIO_0_tri_io(23),
      O => GPIO_0_tri_i_23(23),
      T => GPIO_0_tri_t_23(23)
    );
GPIO_0_tri_iobuf_24: component IOBUF
     port map (
      I => GPIO_0_tri_o_24(24),
      IO => GPIO_0_tri_io(24),
      O => GPIO_0_tri_i_24(24),
      T => GPIO_0_tri_t_24(24)
    );
GPIO_0_tri_iobuf_25: component IOBUF
     port map (
      I => GPIO_0_tri_o_25(25),
      IO => GPIO_0_tri_io(25),
      O => GPIO_0_tri_i_25(25),
      T => GPIO_0_tri_t_25(25)
    );
GPIO_0_tri_iobuf_26: component IOBUF
     port map (
      I => GPIO_0_tri_o_26(26),
      IO => GPIO_0_tri_io(26),
      O => GPIO_0_tri_i_26(26),
      T => GPIO_0_tri_t_26(26)
    );
GPIO_0_tri_iobuf_27: component IOBUF
     port map (
      I => GPIO_0_tri_o_27(27),
      IO => GPIO_0_tri_io(27),
      O => GPIO_0_tri_i_27(27),
      T => GPIO_0_tri_t_27(27)
    );
GPIO_0_tri_iobuf_28: component IOBUF
     port map (
      I => GPIO_0_tri_o_28(28),
      IO => GPIO_0_tri_io(28),
      O => GPIO_0_tri_i_28(28),
      T => GPIO_0_tri_t_28(28)
    );
GPIO_0_tri_iobuf_29: component IOBUF
     port map (
      I => GPIO_0_tri_o_29(29),
      IO => GPIO_0_tri_io(29),
      O => GPIO_0_tri_i_29(29),
      T => GPIO_0_tri_t_29(29)
    );
GPIO_0_tri_iobuf_3: component IOBUF
     port map (
      I => GPIO_0_tri_o_3(3),
      IO => GPIO_0_tri_io(3),
      O => GPIO_0_tri_i_3(3),
      T => GPIO_0_tri_t_3(3)
    );
GPIO_0_tri_iobuf_30: component IOBUF
     port map (
      I => GPIO_0_tri_o_30(30),
      IO => GPIO_0_tri_io(30),
      O => GPIO_0_tri_i_30(30),
      T => GPIO_0_tri_t_30(30)
    );
GPIO_0_tri_iobuf_31: component IOBUF
     port map (
      I => GPIO_0_tri_o_31(31),
      IO => GPIO_0_tri_io(31),
      O => GPIO_0_tri_i_31(31),
      T => GPIO_0_tri_t_31(31)
    );
GPIO_0_tri_iobuf_4: component IOBUF
     port map (
      I => GPIO_0_tri_o_4(4),
      IO => GPIO_0_tri_io(4),
      O => GPIO_0_tri_i_4(4),
      T => GPIO_0_tri_t_4(4)
    );
GPIO_0_tri_iobuf_5: component IOBUF
     port map (
      I => GPIO_0_tri_o_5(5),
      IO => GPIO_0_tri_io(5),
      O => GPIO_0_tri_i_5(5),
      T => GPIO_0_tri_t_5(5)
    );
GPIO_0_tri_iobuf_6: component IOBUF
     port map (
      I => GPIO_0_tri_o_6(6),
      IO => GPIO_0_tri_io(6),
      O => GPIO_0_tri_i_6(6),
      T => GPIO_0_tri_t_6(6)
    );
GPIO_0_tri_iobuf_7: component IOBUF
     port map (
      I => GPIO_0_tri_o_7(7),
      IO => GPIO_0_tri_io(7),
      O => GPIO_0_tri_i_7(7),
      T => GPIO_0_tri_t_7(7)
    );
GPIO_0_tri_iobuf_8: component IOBUF
     port map (
      I => GPIO_0_tri_o_8(8),
      IO => GPIO_0_tri_io(8),
      O => GPIO_0_tri_i_8(8),
      T => GPIO_0_tri_t_8(8)
    );
GPIO_0_tri_iobuf_9: component IOBUF
     port map (
      I => GPIO_0_tri_o_9(9),
      IO => GPIO_0_tri_io(9),
      O => GPIO_0_tri_i_9(9),
      T => GPIO_0_tri_t_9(9)
    );
SPI_0_0_io0_iobuf: component IOBUF
     port map (
      I => SPI_0_0_io0_o,
      IO => SPI_0_0_io0_io,
      O => SPI_0_0_io0_i,
      T => SPI_0_0_io0_t
    );
SPI_0_0_io1_iobuf: component IOBUF
     port map (
      I => SPI_0_0_io1_o,
      IO => SPI_0_0_io1_io,
      O => SPI_0_0_io1_i,
      T => SPI_0_0_io1_t
    );
SPI_0_0_sck_iobuf: component IOBUF
     port map (
      I => SPI_0_0_sck_o,
      IO => SPI_0_0_sck_io,
      O => SPI_0_0_sck_i,
      T => SPI_0_0_sck_t
    );
SPI_0_0_ss_iobuf: component IOBUF
     port map (
      I => SPI_0_0_ss_o,
      IO => SPI_0_0_ss_io,
      O => SPI_0_0_ss_i,
      T => SPI_0_0_ss_t
    );
SPI_1_0_io0_iobuf: component IOBUF
     port map (
      I => SPI_1_0_io0_o,
      IO => SPI_1_0_io0_io,
      O => SPI_1_0_io0_i,
      T => SPI_1_0_io0_t
    );
SPI_1_0_io1_iobuf: component IOBUF
     port map (
      I => SPI_1_0_io1_o,
      IO => SPI_1_0_io1_io,
      O => SPI_1_0_io1_i,
      T => SPI_1_0_io1_t
    );
SPI_1_0_sck_iobuf: component IOBUF
     port map (
      I => SPI_1_0_sck_o,
      IO => SPI_1_0_sck_io,
      O => SPI_1_0_sck_i,
      T => SPI_1_0_sck_t
    );
SPI_1_0_ss_iobuf: component IOBUF
     port map (
      I => SPI_1_0_ss_o,
      IO => SPI_1_0_ss_io,
      O => SPI_1_0_ss_i,
      T => SPI_1_0_ss_t
    );
zusys_i: component zusys
     port map (
      GPIO_0_tri_i(31) => GPIO_0_tri_i_31(31),
      GPIO_0_tri_i(30) => GPIO_0_tri_i_30(30),
      GPIO_0_tri_i(29) => GPIO_0_tri_i_29(29),
      GPIO_0_tri_i(28) => GPIO_0_tri_i_28(28),
      GPIO_0_tri_i(27) => GPIO_0_tri_i_27(27),
      GPIO_0_tri_i(26) => GPIO_0_tri_i_26(26),
      GPIO_0_tri_i(25) => GPIO_0_tri_i_25(25),
      GPIO_0_tri_i(24) => GPIO_0_tri_i_24(24),
      GPIO_0_tri_i(23) => GPIO_0_tri_i_23(23),
      GPIO_0_tri_i(22) => GPIO_0_tri_i_22(22),
      GPIO_0_tri_i(21) => GPIO_0_tri_i_21(21),
      GPIO_0_tri_i(20) => GPIO_0_tri_i_20(20),
      GPIO_0_tri_i(19) => GPIO_0_tri_i_19(19),
      GPIO_0_tri_i(18) => GPIO_0_tri_i_18(18),
      GPIO_0_tri_i(17) => GPIO_0_tri_i_17(17),
      GPIO_0_tri_i(16) => GPIO_0_tri_i_16(16),
      GPIO_0_tri_i(15) => GPIO_0_tri_i_15(15),
      GPIO_0_tri_i(14) => GPIO_0_tri_i_14(14),
      GPIO_0_tri_i(13) => GPIO_0_tri_i_13(13),
      GPIO_0_tri_i(12) => GPIO_0_tri_i_12(12),
      GPIO_0_tri_i(11) => GPIO_0_tri_i_11(11),
      GPIO_0_tri_i(10) => GPIO_0_tri_i_10(10),
      GPIO_0_tri_i(9) => GPIO_0_tri_i_9(9),
      GPIO_0_tri_i(8) => GPIO_0_tri_i_8(8),
      GPIO_0_tri_i(7) => GPIO_0_tri_i_7(7),
      GPIO_0_tri_i(6) => GPIO_0_tri_i_6(6),
      GPIO_0_tri_i(5) => GPIO_0_tri_i_5(5),
      GPIO_0_tri_i(4) => GPIO_0_tri_i_4(4),
      GPIO_0_tri_i(3) => GPIO_0_tri_i_3(3),
      GPIO_0_tri_i(2) => GPIO_0_tri_i_2(2),
      GPIO_0_tri_i(1) => GPIO_0_tri_i_1(1),
      GPIO_0_tri_i(0) => GPIO_0_tri_i_0(0),
      GPIO_0_tri_o(31) => GPIO_0_tri_o_31(31),
      GPIO_0_tri_o(30) => GPIO_0_tri_o_30(30),
      GPIO_0_tri_o(29) => GPIO_0_tri_o_29(29),
      GPIO_0_tri_o(28) => GPIO_0_tri_o_28(28),
      GPIO_0_tri_o(27) => GPIO_0_tri_o_27(27),
      GPIO_0_tri_o(26) => GPIO_0_tri_o_26(26),
      GPIO_0_tri_o(25) => GPIO_0_tri_o_25(25),
      GPIO_0_tri_o(24) => GPIO_0_tri_o_24(24),
      GPIO_0_tri_o(23) => GPIO_0_tri_o_23(23),
      GPIO_0_tri_o(22) => GPIO_0_tri_o_22(22),
      GPIO_0_tri_o(21) => GPIO_0_tri_o_21(21),
      GPIO_0_tri_o(20) => GPIO_0_tri_o_20(20),
      GPIO_0_tri_o(19) => GPIO_0_tri_o_19(19),
      GPIO_0_tri_o(18) => GPIO_0_tri_o_18(18),
      GPIO_0_tri_o(17) => GPIO_0_tri_o_17(17),
      GPIO_0_tri_o(16) => GPIO_0_tri_o_16(16),
      GPIO_0_tri_o(15) => GPIO_0_tri_o_15(15),
      GPIO_0_tri_o(14) => GPIO_0_tri_o_14(14),
      GPIO_0_tri_o(13) => GPIO_0_tri_o_13(13),
      GPIO_0_tri_o(12) => GPIO_0_tri_o_12(12),
      GPIO_0_tri_o(11) => GPIO_0_tri_o_11(11),
      GPIO_0_tri_o(10) => GPIO_0_tri_o_10(10),
      GPIO_0_tri_o(9) => GPIO_0_tri_o_9(9),
      GPIO_0_tri_o(8) => GPIO_0_tri_o_8(8),
      GPIO_0_tri_o(7) => GPIO_0_tri_o_7(7),
      GPIO_0_tri_o(6) => GPIO_0_tri_o_6(6),
      GPIO_0_tri_o(5) => GPIO_0_tri_o_5(5),
      GPIO_0_tri_o(4) => GPIO_0_tri_o_4(4),
      GPIO_0_tri_o(3) => GPIO_0_tri_o_3(3),
      GPIO_0_tri_o(2) => GPIO_0_tri_o_2(2),
      GPIO_0_tri_o(1) => GPIO_0_tri_o_1(1),
      GPIO_0_tri_o(0) => GPIO_0_tri_o_0(0),
      GPIO_0_tri_t(31) => GPIO_0_tri_t_31(31),
      GPIO_0_tri_t(30) => GPIO_0_tri_t_30(30),
      GPIO_0_tri_t(29) => GPIO_0_tri_t_29(29),
      GPIO_0_tri_t(28) => GPIO_0_tri_t_28(28),
      GPIO_0_tri_t(27) => GPIO_0_tri_t_27(27),
      GPIO_0_tri_t(26) => GPIO_0_tri_t_26(26),
      GPIO_0_tri_t(25) => GPIO_0_tri_t_25(25),
      GPIO_0_tri_t(24) => GPIO_0_tri_t_24(24),
      GPIO_0_tri_t(23) => GPIO_0_tri_t_23(23),
      GPIO_0_tri_t(22) => GPIO_0_tri_t_22(22),
      GPIO_0_tri_t(21) => GPIO_0_tri_t_21(21),
      GPIO_0_tri_t(20) => GPIO_0_tri_t_20(20),
      GPIO_0_tri_t(19) => GPIO_0_tri_t_19(19),
      GPIO_0_tri_t(18) => GPIO_0_tri_t_18(18),
      GPIO_0_tri_t(17) => GPIO_0_tri_t_17(17),
      GPIO_0_tri_t(16) => GPIO_0_tri_t_16(16),
      GPIO_0_tri_t(15) => GPIO_0_tri_t_15(15),
      GPIO_0_tri_t(14) => GPIO_0_tri_t_14(14),
      GPIO_0_tri_t(13) => GPIO_0_tri_t_13(13),
      GPIO_0_tri_t(12) => GPIO_0_tri_t_12(12),
      GPIO_0_tri_t(11) => GPIO_0_tri_t_11(11),
      GPIO_0_tri_t(10) => GPIO_0_tri_t_10(10),
      GPIO_0_tri_t(9) => GPIO_0_tri_t_9(9),
      GPIO_0_tri_t(8) => GPIO_0_tri_t_8(8),
      GPIO_0_tri_t(7) => GPIO_0_tri_t_7(7),
      GPIO_0_tri_t(6) => GPIO_0_tri_t_6(6),
      GPIO_0_tri_t(5) => GPIO_0_tri_t_5(5),
      GPIO_0_tri_t(4) => GPIO_0_tri_t_4(4),
      GPIO_0_tri_t(3) => GPIO_0_tri_t_3(3),
      GPIO_0_tri_t(2) => GPIO_0_tri_t_2(2),
      GPIO_0_tri_t(1) => GPIO_0_tri_t_1(1),
      GPIO_0_tri_t(0) => GPIO_0_tri_t_0(0),
      SI5338_CLK0_D_clk_n(0) => SI5338_CLK0_D_clk_n(0),
      SI5338_CLK0_D_clk_p(0) => SI5338_CLK0_D_clk_p(0),
      SPI_0_0_io0_i => SPI_0_0_io0_i,
      SPI_0_0_io0_o => SPI_0_0_io0_o,
      SPI_0_0_io0_t => SPI_0_0_io0_t,
      SPI_0_0_io1_i => SPI_0_0_io1_i,
      SPI_0_0_io1_o => SPI_0_0_io1_o,
      SPI_0_0_io1_t => SPI_0_0_io1_t,
      SPI_0_0_sck_i => SPI_0_0_sck_i,
      SPI_0_0_sck_o => SPI_0_0_sck_o,
      SPI_0_0_sck_t => SPI_0_0_sck_t,
      SPI_0_0_ss_i => SPI_0_0_ss_i,
      SPI_0_0_ss_o => SPI_0_0_ss_o,
      SPI_0_0_ss_t => SPI_0_0_ss_t,
      SPI_1_0_io0_i => SPI_1_0_io0_i,
      SPI_1_0_io0_o => SPI_1_0_io0_o,
      SPI_1_0_io0_t => SPI_1_0_io0_t,
      SPI_1_0_io1_i => SPI_1_0_io1_i,
      SPI_1_0_io1_o => SPI_1_0_io1_o,
      SPI_1_0_io1_t => SPI_1_0_io1_t,
      SPI_1_0_sck_i => SPI_1_0_sck_i,
      SPI_1_0_sck_o => SPI_1_0_sck_o,
      SPI_1_0_sck_t => SPI_1_0_sck_t,
      SPI_1_0_ss_i => SPI_1_0_ss_i,
      SPI_1_0_ss_o => SPI_1_0_ss_o,
      SPI_1_0_ss_t => SPI_1_0_ss_t,
      UART_1_0_rxd => UART_1_0_rxd,
      UART_1_0_txd => UART_1_0_txd,
      x0(0) => x0(0),
      x1(0) => x1(0)
    );
end STRUCTURE;
