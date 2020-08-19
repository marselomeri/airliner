vlib work
vlib riviera

vlib riviera/xilinx_vip
vlib riviera/xpm
vlib riviera/xil_defaultlib
vlib riviera/xlconcat_v2_1_3
vlib riviera/axi_infrastructure_v1_1_0
vlib riviera/axi_vip_v1_1_6
vlib riviera/zynq_ultra_ps_e_vip_v1_0_6
vlib riviera/axi_lite_ipif_v3_0_4
vlib riviera/lib_cdc_v1_0_2
vlib riviera/interrupt_control_v3_1_4
vlib riviera/axi_gpio_v2_0_22
vlib riviera/proc_sys_reset_v5_0_13
vlib riviera/microblaze_v11_0_2
vlib riviera/lmb_v10_v3_0_10
vlib riviera/lmb_bram_if_cntlr_v4_0_17
vlib riviera/blk_mem_gen_v8_4_4
vlib riviera/axi_intc_v4_1_14
vlib riviera/mdm_v3_2_17
vlib riviera/generic_baseblocks_v2_1_0
vlib riviera/axi_register_slice_v2_1_20
vlib riviera/fifo_generator_v13_2_5
vlib riviera/axi_data_fifo_v2_1_19
vlib riviera/axi_crossbar_v2_1_21
vlib riviera/xlconstant_v1_1_6
vlib riviera/axi_protocol_converter_v2_1_20
vlib riviera/axi_clock_converter_v2_1_19
vlib riviera/axi_dwidth_converter_v2_1_20

vmap xilinx_vip riviera/xilinx_vip
vmap xpm riviera/xpm
vmap xil_defaultlib riviera/xil_defaultlib
vmap xlconcat_v2_1_3 riviera/xlconcat_v2_1_3
vmap axi_infrastructure_v1_1_0 riviera/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_6 riviera/axi_vip_v1_1_6
vmap zynq_ultra_ps_e_vip_v1_0_6 riviera/zynq_ultra_ps_e_vip_v1_0_6
vmap axi_lite_ipif_v3_0_4 riviera/axi_lite_ipif_v3_0_4
vmap lib_cdc_v1_0_2 riviera/lib_cdc_v1_0_2
vmap interrupt_control_v3_1_4 riviera/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_22 riviera/axi_gpio_v2_0_22
vmap proc_sys_reset_v5_0_13 riviera/proc_sys_reset_v5_0_13
vmap microblaze_v11_0_2 riviera/microblaze_v11_0_2
vmap lmb_v10_v3_0_10 riviera/lmb_v10_v3_0_10
vmap lmb_bram_if_cntlr_v4_0_17 riviera/lmb_bram_if_cntlr_v4_0_17
vmap blk_mem_gen_v8_4_4 riviera/blk_mem_gen_v8_4_4
vmap axi_intc_v4_1_14 riviera/axi_intc_v4_1_14
vmap mdm_v3_2_17 riviera/mdm_v3_2_17
vmap generic_baseblocks_v2_1_0 riviera/generic_baseblocks_v2_1_0
vmap axi_register_slice_v2_1_20 riviera/axi_register_slice_v2_1_20
vmap fifo_generator_v13_2_5 riviera/fifo_generator_v13_2_5
vmap axi_data_fifo_v2_1_19 riviera/axi_data_fifo_v2_1_19
vmap axi_crossbar_v2_1_21 riviera/axi_crossbar_v2_1_21
vmap xlconstant_v1_1_6 riviera/xlconstant_v1_1_6
vmap axi_protocol_converter_v2_1_20 riviera/axi_protocol_converter_v2_1_20
vmap axi_clock_converter_v2_1_19 riviera/axi_clock_converter_v2_1_19
vmap axi_dwidth_converter_v2_1_20 riviera/axi_dwidth_converter_v2_1_20

vlog -work xilinx_vip  -sv2k12 "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -sv2k12 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -93 \
"C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_VCOMP.vhd" \

vcom -work xil_defaultlib -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/2bc4/labtools_fmeter.vhd" \
"../../../bd/zusys/ip/zusys_labtools_fmeter_0_0/sim/zusys_labtools_fmeter_0_0.vhd" \
"../../../bd/zusys/ip/zusys_util_ds_buf_0_0/util_ds_buf.vhd" \
"../../../bd/zusys/ip/zusys_util_ds_buf_0_0/sim/zusys_util_ds_buf_0_0.vhd" \
"../../../bd/zusys/ip/zusys_vio_0_0/sim/zusys_vio_0_0.vhd" \

vlog -work xlconcat_v2_1_3  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/442e/hdl/xlconcat_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_xlconcat_0_0/sim/zusys_xlconcat_0_0.v" \

vlog -work axi_infrastructure_v1_1_0  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_6  -sv2k12 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/dc12/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work zynq_ultra_ps_e_vip_v1_0_6  -sv2k12 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl/zynq_ultra_ps_e_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim/zusys_zynq_ultra_ps_e_0_0_vip_wrapper.v" \

vcom -work xil_defaultlib -93 \
"../../../bd/zusys/sim/zusys.vhd" \

vcom -work axi_lite_ipif_v3_0_4 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work lib_cdc_v1_0_2 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work interrupt_control_v3_1_4 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_22 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f71e/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/zusys/ip/zusys_axi_gpio_0_0/sim/zusys_axi_gpio_0_0.vhd" \

vcom -work proc_sys_reset_v5_0_13 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/zusys/ip/zusys_rst_ps8_0_99M_1/sim/zusys_rst_ps8_0_99M_1.vhd" \

vcom -work microblaze_v11_0_2 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f871/hdl/microblaze_v11_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/zusys/ip/zusys_microblaze_0_0/sim/zusys_microblaze_0_0.vhd" \

vcom -work lmb_v10_v3_0_10 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/2e88/hdl/lmb_v10_v3_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/zusys/ip/zusys_dlmb_v10_0/sim/zusys_dlmb_v10_0.vhd" \
"../../../bd/zusys/ip/zusys_ilmb_v10_0/sim/zusys_ilmb_v10_0.vhd" \

vcom -work lmb_bram_if_cntlr_v4_0_17 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/db6f/hdl/lmb_bram_if_cntlr_v4_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/zusys/ip/zusys_dlmb_bram_if_cntlr_0/sim/zusys_dlmb_bram_if_cntlr_0.vhd" \
"../../../bd/zusys/ip/zusys_ilmb_bram_if_cntlr_0/sim/zusys_ilmb_bram_if_cntlr_0.vhd" \

vlog -work blk_mem_gen_v8_4_4  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/2985/simulation/blk_mem_gen_v8_4.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_lmb_bram_0/sim/zusys_lmb_bram_0.v" \

vcom -work axi_intc_v4_1_14 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f78a/hdl/axi_intc_v4_1_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/zusys/ip/zusys_microblaze_0_axi_intc_0/sim/zusys_microblaze_0_axi_intc_0.vhd" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_microblaze_0_xlconcat_0/sim/zusys_microblaze_0_xlconcat_0.v" \

vcom -work mdm_v3_2_17 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f9aa/hdl/mdm_v3_2_vh_rfs.vhd" \

vcom -work xil_defaultlib -93 \
"../../../bd/zusys/ip/zusys_mdm_1_0/sim/zusys_mdm_1_0.vhd" \

vlog -work generic_baseblocks_v2_1_0  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_20  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/72d4/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_5  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/276e/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_5 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/276e/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_5  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/276e/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_19  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/60de/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_21  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/6b0d/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_xbar_0/sim/zusys_xbar_0.v" \

vlog -work xlconstant_v1_1_6  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/34f7/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_xlconstant_0_0/sim/zusys_xlconstant_0_0.v" \

vlog -work axi_protocol_converter_v2_1_20  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/c4a6/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work axi_clock_converter_v2_1_19  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/9e81/hdl/axi_clock_converter_v2_1_vl_rfs.v" \

vlog -work axi_dwidth_converter_v2_1_20  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/d394/hdl/axi_dwidth_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -v2k5 "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_auto_us_0/sim/zusys_auto_us_0.v" \
"../../../bd/zusys/ip/zusys_auto_pc_2/sim/zusys_auto_pc_2.v" \
"../../../bd/zusys/ip/zusys_auto_us_1/sim/zusys_auto_us_1.v" \
"../../../bd/zusys/ip/zusys_auto_pc_3/sim/zusys_auto_pc_3.v" \
"../../../bd/zusys/ip/zusys_auto_us_2/sim/zusys_auto_us_2.v" \
"../../../bd/zusys/ip/zusys_auto_ds_0/sim/zusys_auto_ds_0.v" \
"../../../bd/zusys/ip/zusys_auto_pc_0/sim/zusys_auto_pc_0.v" \
"../../../bd/zusys/ip/zusys_auto_ds_1/sim/zusys_auto_ds_1.v" \
"../../../bd/zusys/ip/zusys_auto_pc_1/sim/zusys_auto_pc_1.v" \

vlog -work xil_defaultlib \
"glbl.v"

