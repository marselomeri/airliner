// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2019.2 (lin64) Build 2708876 Wed Nov  6 21:39:14 MST 2019
// Date        : Sat Aug 29 15:10:51 2020
// Host        : vagrant running 64-bit Ubuntu 16.04.6 LTS
// Command     : write_verilog -force -mode funcsim
//               /home/vagrant/git/airliner/config/squeaky_weasel/target/hw/TE0820/vivado/TE0820-03-2AI21FA.srcs/sources_1/bd/zusys/ip/zusys_labtools_fmeter_0_0/zusys_labtools_fmeter_0_0_sim_netlist.v
// Design      : zusys_labtools_fmeter_0_0
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xczu2cg-sfvc784-1-i
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "zusys_labtools_fmeter_0_0,labtools_fmeter,{}" *) (* downgradeipidentifiedwarnings = "yes" *) (* x_core_info = "labtools_fmeter,Vivado 2019.2" *) 
(* NotValidForBitStream *)
module zusys_labtools_fmeter_0_0
   (refclk,
    fin,
    F0,
    update);
  (* x_interface_info = "xilinx.com:signal:clock:1.0 refclk CLK" *) (* x_interface_parameter = "XIL_INTERFACENAME refclk, FREQ_HZ 99999985, PHASE 0.000, CLK_DOMAIN zusys_zynq_ultra_ps_e_0_0_pl_clk0, INSERT_VIP 0" *) input refclk;
  input [0:0]fin;
  output [31:0]F0;
  output update;

  wire [31:0]F0;
  wire [0:0]fin;
  wire refclk;
  wire update;

  zusys_labtools_fmeter_0_0_labtools_fmeter U0
       (.F0(F0),
        .fin(fin),
        .refclk(refclk),
        .update(update));
endmodule

(* ORIG_REF_NAME = "labtools_fmeter" *) 
module zusys_labtools_fmeter_0_0_labtools_fmeter
   (F0,
    update,
    refclk,
    fin);
  output [31:0]F0;
  output update;
  input refclk;
  input [0:0]fin;

  wire [31:0]CNTR_OUT;
  wire COUNTER_REFCLK_inst_n_2;
  wire F;
  wire [31:0]F0;
  wire [0:0]fin;
  wire refclk;
  wire toggle;
  wire update;

  zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO COUNTER_REFCLK_inst
       (.F(F),
        .\bl.DSP48E_2_0 (COUNTER_REFCLK_inst_n_2),
        .refclk(refclk),
        .toggle(toggle),
        .update(update));
  zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO__parameterized0 \FMETER_gen[0].COUNTER_F_inst 
       (.P(CNTR_OUT),
        .fin(fin),
        .toggle(toggle));
  FDRE \F_reg[0] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[0]),
        .Q(F0[0]),
        .R(1'b0));
  FDRE \F_reg[10] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[10]),
        .Q(F0[10]),
        .R(1'b0));
  FDRE \F_reg[11] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[11]),
        .Q(F0[11]),
        .R(1'b0));
  FDRE \F_reg[12] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[12]),
        .Q(F0[12]),
        .R(1'b0));
  FDRE \F_reg[13] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[13]),
        .Q(F0[13]),
        .R(1'b0));
  FDRE \F_reg[14] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[14]),
        .Q(F0[14]),
        .R(1'b0));
  FDRE \F_reg[15] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[15]),
        .Q(F0[15]),
        .R(1'b0));
  FDRE \F_reg[16] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[16]),
        .Q(F0[16]),
        .R(1'b0));
  FDRE \F_reg[17] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[17]),
        .Q(F0[17]),
        .R(1'b0));
  FDRE \F_reg[18] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[18]),
        .Q(F0[18]),
        .R(1'b0));
  FDRE \F_reg[19] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[19]),
        .Q(F0[19]),
        .R(1'b0));
  FDRE \F_reg[1] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[1]),
        .Q(F0[1]),
        .R(1'b0));
  FDRE \F_reg[20] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[20]),
        .Q(F0[20]),
        .R(1'b0));
  FDRE \F_reg[21] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[21]),
        .Q(F0[21]),
        .R(1'b0));
  FDRE \F_reg[22] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[22]),
        .Q(F0[22]),
        .R(1'b0));
  FDRE \F_reg[23] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[23]),
        .Q(F0[23]),
        .R(1'b0));
  FDRE \F_reg[24] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[24]),
        .Q(F0[24]),
        .R(1'b0));
  FDRE \F_reg[25] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[25]),
        .Q(F0[25]),
        .R(1'b0));
  FDRE \F_reg[26] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[26]),
        .Q(F0[26]),
        .R(1'b0));
  FDRE \F_reg[27] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[27]),
        .Q(F0[27]),
        .R(1'b0));
  FDRE \F_reg[28] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[28]),
        .Q(F0[28]),
        .R(1'b0));
  FDRE \F_reg[29] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[29]),
        .Q(F0[29]),
        .R(1'b0));
  FDRE \F_reg[2] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[2]),
        .Q(F0[2]),
        .R(1'b0));
  FDRE \F_reg[30] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[30]),
        .Q(F0[30]),
        .R(1'b0));
  FDRE \F_reg[31] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[31]),
        .Q(F0[31]),
        .R(1'b0));
  FDRE \F_reg[3] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[3]),
        .Q(F0[3]),
        .R(1'b0));
  FDRE \F_reg[4] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[4]),
        .Q(F0[4]),
        .R(1'b0));
  FDRE \F_reg[5] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[5]),
        .Q(F0[5]),
        .R(1'b0));
  FDRE \F_reg[6] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[6]),
        .Q(F0[6]),
        .R(1'b0));
  FDRE \F_reg[7] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[7]),
        .Q(F0[7]),
        .R(1'b0));
  FDRE \F_reg[8] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[8]),
        .Q(F0[8]),
        .R(1'b0));
  FDRE \F_reg[9] 
       (.C(refclk),
        .CE(F),
        .D(CNTR_OUT[9]),
        .Q(F0[9]),
        .R(1'b0));
  FDRE toggle_reg
       (.C(refclk),
        .CE(1'b1),
        .D(COUNTER_REFCLK_inst_n_2),
        .Q(toggle),
        .R(1'b0));
endmodule

(* ORIG_REF_NAME = "unimacro_COUNTER_TC_MACRO" *) 
module zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO
   (update,
    F,
    \bl.DSP48E_2_0 ,
    refclk,
    toggle);
  output update;
  output F;
  output \bl.DSP48E_2_0 ;
  input refclk;
  input toggle;

  wire [47:0]CNTR_OUT;
  wire F;
  wire \F[31]_i_2_n_0 ;
  wire \F[31]_i_3_n_0 ;
  wire \F[31]_i_4_n_0 ;
  wire \bl.DSP48E_2_0 ;
  wire \bl.DSP48E_2_i_1_n_0 ;
  wire refclk;
  wire toggle;
  wire update;
  wire update_INST_0_i_10_n_0;
  wire update_INST_0_i_11_n_0;
  wire update_INST_0_i_12_n_0;
  wire update_INST_0_i_1_n_0;
  wire update_INST_0_i_2_n_0;
  wire update_INST_0_i_3_n_0;
  wire update_INST_0_i_4_n_0;
  wire update_INST_0_i_5_n_0;
  wire update_INST_0_i_6_n_0;
  wire update_INST_0_i_7_n_0;
  wire update_INST_0_i_8_n_0;
  wire update_INST_0_i_9_n_0;
  wire \NLW_bl.DSP48E_2_CARRYCASCOUT_UNCONNECTED ;
  wire \NLW_bl.DSP48E_2_MULTSIGNOUT_UNCONNECTED ;
  wire \NLW_bl.DSP48E_2_OVERFLOW_UNCONNECTED ;
  wire \NLW_bl.DSP48E_2_PATTERNBDETECT_UNCONNECTED ;
  wire \NLW_bl.DSP48E_2_PATTERNDETECT_UNCONNECTED ;
  wire \NLW_bl.DSP48E_2_UNDERFLOW_UNCONNECTED ;
  wire [29:0]\NLW_bl.DSP48E_2_ACOUT_UNCONNECTED ;
  wire [17:0]\NLW_bl.DSP48E_2_BCOUT_UNCONNECTED ;
  wire [3:0]\NLW_bl.DSP48E_2_CARRYOUT_UNCONNECTED ;
  wire [47:0]\NLW_bl.DSP48E_2_PCOUT_UNCONNECTED ;
  wire [7:0]\NLW_bl.DSP48E_2_XOROUT_UNCONNECTED ;

  LUT6 #(
    .INIT(64'h0000000000000004)) 
    \F[31]_i_1 
       (.I0(toggle),
        .I1(CNTR_OUT[0]),
        .I2(\F[31]_i_2_n_0 ),
        .I3(update_INST_0_i_3_n_0),
        .I4(update_INST_0_i_4_n_0),
        .I5(update_INST_0_i_5_n_0),
        .O(F));
  LUT4 #(
    .INIT(16'hFFFE)) 
    \F[31]_i_2 
       (.I0(update_INST_0_i_6_n_0),
        .I1(\F[31]_i_3_n_0 ),
        .I2(update_INST_0_i_7_n_0),
        .I3(\F[31]_i_4_n_0 ),
        .O(\F[31]_i_2_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT4 #(
    .INIT(16'h7FFF)) 
    \F[31]_i_3 
       (.I0(CNTR_OUT[3]),
        .I1(CNTR_OUT[2]),
        .I2(CNTR_OUT[5]),
        .I3(CNTR_OUT[4]),
        .O(\F[31]_i_3_n_0 ));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT4 #(
    .INIT(16'hFFEF)) 
    \F[31]_i_4 
       (.I0(CNTR_OUT[11]),
        .I1(CNTR_OUT[10]),
        .I2(CNTR_OUT[13]),
        .I3(CNTR_OUT[12]),
        .O(\F[31]_i_4_n_0 ));
  (* XILINX_LEGACY_PRIM = "DSP48E1" *) 
  (* XILINX_TRANSFORM_PINMAP = "D[24]:D[26],D[25]" *) 
  (* box_type = "PRIMITIVE" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(0),
    .ALUMODEREG(1),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(1),
    .CARRYINSELREG(1),
    .CREG(1),
    .DREG(0),
    .INMODEREG(1),
    .IS_ALUMODE_INVERTED(4'b0000),
    .IS_CARRYIN_INVERTED(1'b0),
    .IS_CLK_INVERTED(1'b0),
    .IS_INMODE_INVERTED(5'b00000),
    .IS_OPMODE_INVERTED(9'b000000000),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(1),
    .PATTERN(48'h000000000000),
    .PREG(1),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("NONE"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48")) 
    \bl.DSP48E_2 
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(\NLW_bl.DSP48E_2_ACOUT_UNCONNECTED [29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(\NLW_bl.DSP48E_2_BCOUT_UNCONNECTED [17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(\NLW_bl.DSP48E_2_CARRYCASCOUT_UNCONNECTED ),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(\NLW_bl.DSP48E_2_CARRYOUT_UNCONNECTED [3:0]),
        .CEA1(1'b0),
        .CEA2(1'b1),
        .CEAD(1'b0),
        .CEALUMODE(1'b1),
        .CEB1(1'b0),
        .CEB2(1'b1),
        .CEC(1'b1),
        .CECARRYIN(1'b1),
        .CECTRL(1'b1),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(1'b1),
        .CLK(refclk),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(\NLW_bl.DSP48E_2_MULTSIGNOUT_UNCONNECTED ),
        .OPMODE({1'b0,1'b0,1'b0,\bl.DSP48E_2_i_1_n_0 ,1'b0,1'b0,1'b0,\bl.DSP48E_2_i_1_n_0 ,\bl.DSP48E_2_i_1_n_0 }),
        .OVERFLOW(\NLW_bl.DSP48E_2_OVERFLOW_UNCONNECTED ),
        .P(CNTR_OUT),
        .PATTERNBDETECT(\NLW_bl.DSP48E_2_PATTERNBDETECT_UNCONNECTED ),
        .PATTERNDETECT(\NLW_bl.DSP48E_2_PATTERNDETECT_UNCONNECTED ),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(\NLW_bl.DSP48E_2_PCOUT_UNCONNECTED [47:0]),
        .RSTA(1'b0),
        .RSTALLCARRYIN(1'b0),
        .RSTALUMODE(1'b0),
        .RSTB(1'b0),
        .RSTC(1'b0),
        .RSTCTRL(1'b0),
        .RSTD(1'b0),
        .RSTINMODE(1'b0),
        .RSTM(1'b0),
        .RSTP(1'b0),
        .UNDERFLOW(\NLW_bl.DSP48E_2_UNDERFLOW_UNCONNECTED ),
        .XOROUT(\NLW_bl.DSP48E_2_XOROUT_UNCONNECTED [7:0]));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFFFFFE)) 
    \bl.DSP48E_2_i_1 
       (.I0(update_INST_0_i_1_n_0),
        .I1(update_INST_0_i_2_n_0),
        .I2(update_INST_0_i_3_n_0),
        .I3(update_INST_0_i_4_n_0),
        .I4(update_INST_0_i_5_n_0),
        .I5(CNTR_OUT[0]),
        .O(\bl.DSP48E_2_i_1_n_0 ));
  LUT6 #(
    .INIT(64'hFFFEFFFF00010000)) 
    toggle_i_1
       (.I0(update_INST_0_i_5_n_0),
        .I1(update_INST_0_i_4_n_0),
        .I2(update_INST_0_i_3_n_0),
        .I3(\F[31]_i_2_n_0 ),
        .I4(CNTR_OUT[0]),
        .I5(toggle),
        .O(\bl.DSP48E_2_0 ));
  LUT6 #(
    .INIT(64'h0000000000000002)) 
    update_INST_0
       (.I0(CNTR_OUT[0]),
        .I1(update_INST_0_i_1_n_0),
        .I2(update_INST_0_i_2_n_0),
        .I3(update_INST_0_i_3_n_0),
        .I4(update_INST_0_i_4_n_0),
        .I5(update_INST_0_i_5_n_0),
        .O(update));
  (* SOFT_HLUTNM = "soft_lutpair1" *) 
  LUT5 #(
    .INIT(32'hFFFF7FFF)) 
    update_INST_0_i_1
       (.I0(CNTR_OUT[4]),
        .I1(CNTR_OUT[5]),
        .I2(CNTR_OUT[2]),
        .I3(CNTR_OUT[3]),
        .I4(update_INST_0_i_6_n_0),
        .O(update_INST_0_i_1_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    update_INST_0_i_10
       (.I0(CNTR_OUT[39]),
        .I1(CNTR_OUT[38]),
        .I2(CNTR_OUT[41]),
        .I3(CNTR_OUT[40]),
        .O(update_INST_0_i_10_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    update_INST_0_i_11
       (.I0(CNTR_OUT[35]),
        .I1(CNTR_OUT[34]),
        .I2(CNTR_OUT[37]),
        .I3(CNTR_OUT[36]),
        .O(update_INST_0_i_11_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    update_INST_0_i_12
       (.I0(CNTR_OUT[43]),
        .I1(CNTR_OUT[42]),
        .I2(CNTR_OUT[45]),
        .I3(CNTR_OUT[44]),
        .O(update_INST_0_i_12_n_0));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT5 #(
    .INIT(32'hFFFFFFFB)) 
    update_INST_0_i_2
       (.I0(CNTR_OUT[12]),
        .I1(CNTR_OUT[13]),
        .I2(CNTR_OUT[10]),
        .I3(CNTR_OUT[11]),
        .I4(update_INST_0_i_7_n_0),
        .O(update_INST_0_i_2_n_0));
  LUT5 #(
    .INIT(32'hFFFFFEFF)) 
    update_INST_0_i_3
       (.I0(CNTR_OUT[28]),
        .I1(CNTR_OUT[29]),
        .I2(CNTR_OUT[27]),
        .I3(CNTR_OUT[26]),
        .I4(update_INST_0_i_8_n_0),
        .O(update_INST_0_i_3_n_0));
  LUT5 #(
    .INIT(32'hFFFFF7FF)) 
    update_INST_0_i_4
       (.I0(CNTR_OUT[20]),
        .I1(CNTR_OUT[21]),
        .I2(CNTR_OUT[19]),
        .I3(CNTR_OUT[18]),
        .I4(update_INST_0_i_9_n_0),
        .O(update_INST_0_i_4_n_0));
  LUT6 #(
    .INIT(64'hFFFFFFFFFFFEFFFF)) 
    update_INST_0_i_5
       (.I0(update_INST_0_i_10_n_0),
        .I1(update_INST_0_i_11_n_0),
        .I2(CNTR_OUT[47]),
        .I3(CNTR_OUT[46]),
        .I4(CNTR_OUT[1]),
        .I5(update_INST_0_i_12_n_0),
        .O(update_INST_0_i_5_n_0));
  LUT4 #(
    .INIT(16'hFFF7)) 
    update_INST_0_i_6
       (.I0(CNTR_OUT[7]),
        .I1(CNTR_OUT[6]),
        .I2(CNTR_OUT[9]),
        .I3(CNTR_OUT[8]),
        .O(update_INST_0_i_6_n_0));
  LUT4 #(
    .INIT(16'hFF7F)) 
    update_INST_0_i_7
       (.I0(CNTR_OUT[15]),
        .I1(CNTR_OUT[14]),
        .I2(CNTR_OUT[16]),
        .I3(CNTR_OUT[17]),
        .O(update_INST_0_i_7_n_0));
  LUT4 #(
    .INIT(16'hFFFE)) 
    update_INST_0_i_8
       (.I0(CNTR_OUT[31]),
        .I1(CNTR_OUT[30]),
        .I2(CNTR_OUT[33]),
        .I3(CNTR_OUT[32]),
        .O(update_INST_0_i_8_n_0));
  LUT4 #(
    .INIT(16'hFF7F)) 
    update_INST_0_i_9
       (.I0(CNTR_OUT[23]),
        .I1(CNTR_OUT[22]),
        .I2(CNTR_OUT[24]),
        .I3(CNTR_OUT[25]),
        .O(update_INST_0_i_9_n_0));
endmodule

(* ORIG_REF_NAME = "unimacro_COUNTER_TC_MACRO" *) 
module zusys_labtools_fmeter_0_0_unimacro_COUNTER_TC_MACRO__parameterized0
   (P,
    fin,
    toggle);
  output [31:0]P;
  input [0:0]fin;
  input toggle;

  wire CE;
  wire [47:32]CNTR_OUT;
  wire [31:0]P;
  wire [0:0]fin;
  wire toggle;
  wire \NLW_bl.DSP48E_2_CARRYCASCOUT_UNCONNECTED ;
  wire \NLW_bl.DSP48E_2_MULTSIGNOUT_UNCONNECTED ;
  wire \NLW_bl.DSP48E_2_OVERFLOW_UNCONNECTED ;
  wire \NLW_bl.DSP48E_2_PATTERNBDETECT_UNCONNECTED ;
  wire \NLW_bl.DSP48E_2_PATTERNDETECT_UNCONNECTED ;
  wire \NLW_bl.DSP48E_2_UNDERFLOW_UNCONNECTED ;
  wire [29:0]\NLW_bl.DSP48E_2_ACOUT_UNCONNECTED ;
  wire [17:0]\NLW_bl.DSP48E_2_BCOUT_UNCONNECTED ;
  wire [3:0]\NLW_bl.DSP48E_2_CARRYOUT_UNCONNECTED ;
  wire [47:0]\NLW_bl.DSP48E_2_PCOUT_UNCONNECTED ;
  wire [7:0]\NLW_bl.DSP48E_2_XOROUT_UNCONNECTED ;

  (* XILINX_LEGACY_PRIM = "DSP48E1" *) 
  (* XILINX_TRANSFORM_PINMAP = "D[24]:D[26],D[25]" *) 
  (* box_type = "PRIMITIVE" *) 
  DSP48E2 #(
    .ACASCREG(1),
    .ADREG(0),
    .ALUMODEREG(1),
    .AMULTSEL("A"),
    .AREG(1),
    .AUTORESET_PATDET("NO_RESET"),
    .A_INPUT("DIRECT"),
    .BCASCREG(1),
    .BREG(1),
    .B_INPUT("DIRECT"),
    .CARRYINREG(1),
    .CARRYINSELREG(1),
    .CREG(1),
    .DREG(0),
    .INMODEREG(1),
    .IS_ALUMODE_INVERTED(4'b0000),
    .IS_CARRYIN_INVERTED(1'b0),
    .IS_CLK_INVERTED(1'b0),
    .IS_INMODE_INVERTED(5'b00000),
    .IS_OPMODE_INVERTED(9'b000000000),
    .MASK(48'h3FFFFFFFFFFF),
    .MREG(0),
    .OPMODEREG(1),
    .PATTERN(48'h000000000000),
    .PREG(1),
    .SEL_MASK("MASK"),
    .SEL_PATTERN("PATTERN"),
    .USE_MULT("NONE"),
    .USE_PATTERN_DETECT("NO_PATDET"),
    .USE_SIMD("ONE48")) 
    \bl.DSP48E_2 
       (.A({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .ACOUT(\NLW_bl.DSP48E_2_ACOUT_UNCONNECTED [29:0]),
        .ALUMODE({1'b0,1'b0,1'b0,1'b0}),
        .B({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b1}),
        .BCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .BCOUT(\NLW_bl.DSP48E_2_BCOUT_UNCONNECTED [17:0]),
        .C({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .CARRYCASCIN(1'b0),
        .CARRYCASCOUT(\NLW_bl.DSP48E_2_CARRYCASCOUT_UNCONNECTED ),
        .CARRYIN(1'b0),
        .CARRYINSEL({1'b0,1'b0,1'b0}),
        .CARRYOUT(\NLW_bl.DSP48E_2_CARRYOUT_UNCONNECTED [3:0]),
        .CEA1(1'b0),
        .CEA2(CE),
        .CEAD(1'b0),
        .CEALUMODE(CE),
        .CEB1(1'b0),
        .CEB2(CE),
        .CEC(CE),
        .CECARRYIN(CE),
        .CECTRL(CE),
        .CED(1'b0),
        .CEINMODE(1'b0),
        .CEM(1'b0),
        .CEP(CE),
        .CLK(fin),
        .D({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .INMODE({1'b0,1'b0,1'b0,1'b0,1'b0}),
        .MULTSIGNIN(1'b0),
        .MULTSIGNOUT(\NLW_bl.DSP48E_2_MULTSIGNOUT_UNCONNECTED ),
        .OPMODE({1'b0,1'b0,1'b0,1'b1,1'b0,1'b0,1'b0,1'b1,1'b1}),
        .OVERFLOW(\NLW_bl.DSP48E_2_OVERFLOW_UNCONNECTED ),
        .P({CNTR_OUT,P}),
        .PATTERNBDETECT(\NLW_bl.DSP48E_2_PATTERNBDETECT_UNCONNECTED ),
        .PATTERNDETECT(\NLW_bl.DSP48E_2_PATTERNDETECT_UNCONNECTED ),
        .PCIN({1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0,1'b0}),
        .PCOUT(\NLW_bl.DSP48E_2_PCOUT_UNCONNECTED [47:0]),
        .RSTA(toggle),
        .RSTALLCARRYIN(toggle),
        .RSTALUMODE(toggle),
        .RSTB(toggle),
        .RSTC(toggle),
        .RSTCTRL(toggle),
        .RSTD(toggle),
        .RSTINMODE(toggle),
        .RSTM(toggle),
        .RSTP(toggle),
        .UNDERFLOW(\NLW_bl.DSP48E_2_UNDERFLOW_UNCONNECTED ),
        .XOROUT(\NLW_bl.DSP48E_2_XOROUT_UNCONNECTED [7:0]));
  LUT1 #(
    .INIT(2'h1)) 
    \bl.DSP48E_2_i_1__0 
       (.I0(toggle),
        .O(CE));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
