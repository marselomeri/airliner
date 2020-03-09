-makelib xcelium_lib/xilinx_vip -sv \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib xcelium_lib/xpm -sv \
  "C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
  "C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib xcelium_lib/xpm \
  "C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/2bc4/labtools_fmeter.vhd" \
  "../../../bd/zusys/ip/zusys_labtools_fmeter_0_0/sim/zusys_labtools_fmeter_0_0.vhd" \
  "../../../bd/zusys/ip/zusys_util_ds_buf_0_0/util_ds_buf.vhd" \
  "../../../bd/zusys/ip/zusys_util_ds_buf_0_0/sim/zusys_util_ds_buf_0_0.vhd" \
  "../../../bd/zusys/ip/zusys_vio_0_0/sim/zusys_vio_0_0.vhd" \
-endlib
-makelib xcelium_lib/xlconcat_v2_1_3 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/442e/hdl/xlconcat_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_xlconcat_0_0/sim/zusys_xlconcat_0_0.v" \
-endlib
-makelib xcelium_lib/axi_infrastructure_v1_1_0 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_vip_v1_1_6 -sv \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/dc12/hdl/axi_vip_v1_1_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/zynq_ultra_ps_e_vip_v1_0_6 -sv \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl/zynq_ultra_ps_e_vip_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim/zusys_zynq_ultra_ps_e_0_0_vip_wrapper.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/sim/zusys.vhd" \
-endlib
-makelib xcelium_lib/axi_lite_ipif_v3_0_4 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/lib_cdc_v1_0_2 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/interrupt_control_v3_1_4 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/axi_gpio_v2_0_22 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f71e/hdl/axi_gpio_v2_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_axi_gpio_0_0/sim/zusys_axi_gpio_0_0.vhd" \
-endlib
-makelib xcelium_lib/proc_sys_reset_v5_0_13 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_rst_ps8_0_99M_1/sim/zusys_rst_ps8_0_99M_1.vhd" \
-endlib
-makelib xcelium_lib/microblaze_v11_0_2 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f871/hdl/microblaze_v11_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_microblaze_0_0/sim/zusys_microblaze_0_0.vhd" \
-endlib
-makelib xcelium_lib/lmb_v10_v3_0_10 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/2e88/hdl/lmb_v10_v3_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_dlmb_v10_0/sim/zusys_dlmb_v10_0.vhd" \
  "../../../bd/zusys/ip/zusys_ilmb_v10_0/sim/zusys_ilmb_v10_0.vhd" \
-endlib
-makelib xcelium_lib/lmb_bram_if_cntlr_v4_0_17 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/db6f/hdl/lmb_bram_if_cntlr_v4_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_dlmb_bram_if_cntlr_0/sim/zusys_dlmb_bram_if_cntlr_0.vhd" \
  "../../../bd/zusys/ip/zusys_ilmb_bram_if_cntlr_0/sim/zusys_ilmb_bram_if_cntlr_0.vhd" \
-endlib
-makelib xcelium_lib/blk_mem_gen_v8_4_4 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/2985/simulation/blk_mem_gen_v8_4.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_lmb_bram_0/sim/zusys_lmb_bram_0.v" \
-endlib
-makelib xcelium_lib/axi_intc_v4_1_14 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f78a/hdl/axi_intc_v4_1_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_microblaze_0_axi_intc_0/sim/zusys_microblaze_0_axi_intc_0.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_microblaze_0_xlconcat_0/sim/zusys_microblaze_0_xlconcat_0.v" \
-endlib
-makelib xcelium_lib/mdm_v3_2_17 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f9aa/hdl/mdm_v3_2_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_mdm_1_0/sim/zusys_mdm_1_0.vhd" \
-endlib
-makelib xcelium_lib/generic_baseblocks_v2_1_0 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_register_slice_v2_1_20 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/72d4/hdl/axi_register_slice_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_5 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/276e/simulation/fifo_generator_vlog_beh.v" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_5 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/276e/hdl/fifo_generator_v13_2_rfs.vhd" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_5 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/276e/hdl/fifo_generator_v13_2_rfs.v" \
-endlib
-makelib xcelium_lib/axi_data_fifo_v2_1_19 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/60de/hdl/axi_data_fifo_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_crossbar_v2_1_21 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/6b0d/hdl/axi_crossbar_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_xbar_0/sim/zusys_xbar_0.v" \
-endlib
-makelib xcelium_lib/xlconstant_v1_1_6 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/34f7/hdl/xlconstant_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_xlconstant_0_0/sim/zusys_xlconstant_0_0.v" \
-endlib
-makelib xcelium_lib/axi_protocol_converter_v2_1_20 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/c4a6/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_clock_converter_v2_1_19 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/9e81/hdl/axi_clock_converter_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_dwidth_converter_v2_1_20 \
  "../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/d394/hdl/axi_dwidth_converter_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/zusys/ip/zusys_auto_us_0/sim/zusys_auto_us_0.v" \
  "../../../bd/zusys/ip/zusys_auto_pc_2/sim/zusys_auto_pc_2.v" \
  "../../../bd/zusys/ip/zusys_auto_us_1/sim/zusys_auto_us_1.v" \
  "../../../bd/zusys/ip/zusys_auto_pc_3/sim/zusys_auto_pc_3.v" \
  "../../../bd/zusys/ip/zusys_auto_us_2/sim/zusys_auto_us_2.v" \
  "../../../bd/zusys/ip/zusys_auto_ds_0/sim/zusys_auto_ds_0.v" \
  "../../../bd/zusys/ip/zusys_auto_pc_0/sim/zusys_auto_pc_0.v" \
  "../../../bd/zusys/ip/zusys_auto_ds_1/sim/zusys_auto_ds_1.v" \
  "../../../bd/zusys/ip/zusys_auto_pc_1/sim/zusys_auto_pc_1.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  glbl.v
-endlib

