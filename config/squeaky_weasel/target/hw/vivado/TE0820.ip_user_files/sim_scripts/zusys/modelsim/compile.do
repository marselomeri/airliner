vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xilinx_vip
vlib modelsim_lib/msim/xpm
vlib modelsim_lib/msim/xil_defaultlib
vlib modelsim_lib/msim/xlconcat_v2_1_3
vlib modelsim_lib/msim/axi_infrastructure_v1_1_0
vlib modelsim_lib/msim/axi_vip_v1_1_6
vlib modelsim_lib/msim/zynq_ultra_ps_e_vip_v1_0_6
vlib modelsim_lib/msim/axi_lite_ipif_v3_0_4
vlib modelsim_lib/msim/lib_cdc_v1_0_2
vlib modelsim_lib/msim/interrupt_control_v3_1_4
vlib modelsim_lib/msim/axi_gpio_v2_0_22
vlib modelsim_lib/msim/proc_sys_reset_v5_0_13
vlib modelsim_lib/msim/microblaze_v11_0_2
vlib modelsim_lib/msim/lmb_v10_v3_0_10
vlib modelsim_lib/msim/lmb_bram_if_cntlr_v4_0_17
vlib modelsim_lib/msim/blk_mem_gen_v8_4_4
vlib modelsim_lib/msim/axi_intc_v4_1_14
vlib modelsim_lib/msim/mdm_v3_2_17
vlib modelsim_lib/msim/generic_baseblocks_v2_1_0
vlib modelsim_lib/msim/axi_register_slice_v2_1_20
vlib modelsim_lib/msim/fifo_generator_v13_2_5
vlib modelsim_lib/msim/axi_data_fifo_v2_1_19
vlib modelsim_lib/msim/axi_crossbar_v2_1_21
vlib modelsim_lib/msim/xlconstant_v1_1_6
vlib modelsim_lib/msim/axi_protocol_converter_v2_1_20
vlib modelsim_lib/msim/axi_clock_converter_v2_1_19
vlib modelsim_lib/msim/axi_dwidth_converter_v2_1_20

vmap xilinx_vip modelsim_lib/msim/xilinx_vip
vmap xpm modelsim_lib/msim/xpm
vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib
vmap xlconcat_v2_1_3 modelsim_lib/msim/xlconcat_v2_1_3
vmap axi_infrastructure_v1_1_0 modelsim_lib/msim/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_6 modelsim_lib/msim/axi_vip_v1_1_6
vmap zynq_ultra_ps_e_vip_v1_0_6 modelsim_lib/msim/zynq_ultra_ps_e_vip_v1_0_6
vmap axi_lite_ipif_v3_0_4 modelsim_lib/msim/axi_lite_ipif_v3_0_4
vmap lib_cdc_v1_0_2 modelsim_lib/msim/lib_cdc_v1_0_2
vmap interrupt_control_v3_1_4 modelsim_lib/msim/interrupt_control_v3_1_4
vmap axi_gpio_v2_0_22 modelsim_lib/msim/axi_gpio_v2_0_22
vmap proc_sys_reset_v5_0_13 modelsim_lib/msim/proc_sys_reset_v5_0_13
vmap microblaze_v11_0_2 modelsim_lib/msim/microblaze_v11_0_2
vmap lmb_v10_v3_0_10 modelsim_lib/msim/lmb_v10_v3_0_10
vmap lmb_bram_if_cntlr_v4_0_17 modelsim_lib/msim/lmb_bram_if_cntlr_v4_0_17
vmap blk_mem_gen_v8_4_4 modelsim_lib/msim/blk_mem_gen_v8_4_4
vmap axi_intc_v4_1_14 modelsim_lib/msim/axi_intc_v4_1_14
vmap mdm_v3_2_17 modelsim_lib/msim/mdm_v3_2_17
vmap generic_baseblocks_v2_1_0 modelsim_lib/msim/generic_baseblocks_v2_1_0
vmap axi_register_slice_v2_1_20 modelsim_lib/msim/axi_register_slice_v2_1_20
vmap fifo_generator_v13_2_5 modelsim_lib/msim/fifo_generator_v13_2_5
vmap axi_data_fifo_v2_1_19 modelsim_lib/msim/axi_data_fifo_v2_1_19
vmap axi_crossbar_v2_1_21 modelsim_lib/msim/axi_crossbar_v2_1_21
vmap xlconstant_v1_1_6 modelsim_lib/msim/xlconstant_v1_1_6
vmap axi_protocol_converter_v2_1_20 modelsim_lib/msim/axi_protocol_converter_v2_1_20
vmap axi_clock_converter_v2_1_19 modelsim_lib/msim/axi_clock_converter_v2_1_19
vmap axi_dwidth_converter_v2_1_20 modelsim_lib/msim/axi_dwidth_converter_v2_1_20

vlog -work xilinx_vip -64 -incr -sv -L axi_vip_v1_1_6 -L zynq_ultra_ps_e_vip_v1_0_6 -L xilinx_vip "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2019.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm -64 -incr -sv -L axi_vip_v1_1_6 -L zynq_ultra_ps_e_vip_v1_0_6 -L xilinx_vip "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm -64 -93 \
"C:/Xilinx/Vivado/2019.2/data/ip/xpm/xpm_VCOMP.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/2bc4/labtools_fmeter.vhd" \
"../../../bd/zusys/ip/zusys_labtools_fmeter_0_0/sim/zusys_labtools_fmeter_0_0.vhd" \
"../../../bd/zusys/ip/zusys_util_ds_buf_0_0/util_ds_buf.vhd" \
"../../../bd/zusys/ip/zusys_util_ds_buf_0_0/sim/zusys_util_ds_buf_0_0.vhd" \
"../../../bd/zusys/ip/zusys_vio_0_0/sim/zusys_vio_0_0.vhd" \

vlog -work xlconcat_v2_1_3 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/442e/hdl/xlconcat_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_xlconcat_0_0/sim/zusys_xlconcat_0_0.v" \

vlog -work axi_infrastructure_v1_1_0 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_6 -64 -incr -sv -L axi_vip_v1_1_6 -L zynq_ultra_ps_e_vip_v1_0_6 -L xilinx_vip "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/dc12/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work zynq_ultra_ps_e_vip_v1_0_6 -64 -incr -sv -L axi_vip_v1_1_6 -L zynq_ultra_ps_e_vip_v1_0_6 -L xilinx_vip "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl/zynq_ultra_ps_e_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim/zusys_zynq_ultra_ps_e_0_0_vip_wrapper.v" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/zusys/sim/zusys.vhd" \

vcom -work axi_lite_ipif_v3_0_4 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \

vcom -work lib_cdc_v1_0_2 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work interrupt_control_v3_1_4 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \

vcom -work axi_gpio_v2_0_22 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f71e/hdl/axi_gpio_v2_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/zusys/ip/zusys_axi_gpio_0_0/sim/zusys_axi_gpio_0_0.vhd" \

vcom -work proc_sys_reset_v5_0_13 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/zusys/ip/zusys_rst_ps8_0_99M_1/sim/zusys_rst_ps8_0_99M_1.vhd" \

vcom -work microblaze_v11_0_2 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f871/hdl/microblaze_v11_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/zusys/ip/zusys_microblaze_0_0/sim/zusys_microblaze_0_0.vhd" \

vcom -work lmb_v10_v3_0_10 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/2e88/hdl/lmb_v10_v3_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/zusys/ip/zusys_dlmb_v10_0/sim/zusys_dlmb_v10_0.vhd" \
"../../../bd/zusys/ip/zusys_ilmb_v10_0/sim/zusys_ilmb_v10_0.vhd" \

vcom -work lmb_bram_if_cntlr_v4_0_17 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/db6f/hdl/lmb_bram_if_cntlr_v4_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/zusys/ip/zusys_dlmb_bram_if_cntlr_0/sim/zusys_dlmb_bram_if_cntlr_0.vhd" \
"../../../bd/zusys/ip/zusys_ilmb_bram_if_cntlr_0/sim/zusys_ilmb_bram_if_cntlr_0.vhd" \

vlog -work blk_mem_gen_v8_4_4 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/2985/simulation/blk_mem_gen_v8_4.v" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_lmb_bram_0/sim/zusys_lmb_bram_0.v" \

vcom -work axi_intc_v4_1_14 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f78a/hdl/axi_intc_v4_1_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/zusys/ip/zusys_microblaze_0_axi_intc_0/sim/zusys_microblaze_0_axi_intc_0.vhd" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_microblaze_0_xlconcat_0/sim/zusys_microblaze_0_xlconcat_0.v" \

vcom -work mdm_v3_2_17 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/f9aa/hdl/mdm_v3_2_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/zusys/ip/zusys_mdm_1_0/sim/zusys_mdm_1_0.vhd" \

vlog -work generic_baseblocks_v2_1_0 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_20 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/72d4/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_5 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/276e/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_5 -64 -93 \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/276e/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_5 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/276e/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_19 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/60de/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_21 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/6b0d/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_xbar_0/sim/zusys_xbar_0.v" \

vlog -work xlconstant_v1_1_6 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/34f7/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../bd/zusys/ip/zusys_xlconstant_0_0/sim/zusys_xlconstant_0_0.v" \

vlog -work axi_protocol_converter_v2_1_20 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/c4a6/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work axi_clock_converter_v2_1_19 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/9e81/hdl/axi_clock_converter_v2_1_vl_rfs.v" \

vlog -work axi_dwidth_converter_v2_1_20 -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
"../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/d394/hdl/axi_dwidth_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 -incr "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/ec67/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/0eaf/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/1b7e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/122e/hdl/verilog" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ipshared/46fd/hdl" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0/sim_tlm" "+incdir+../../../../TE0820.srcs/sources_1/bd/zusys/ip/zusys_zynq_ultra_ps_e_0_0" "+incdir+C:/Xilinx/Vivado/2019.2/data/xilinx_vip/include" \
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

