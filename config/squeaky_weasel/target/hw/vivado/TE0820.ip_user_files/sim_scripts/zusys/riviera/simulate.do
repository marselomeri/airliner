onbreak {quit -force}
onerror {quit -force}

asim -t 1ps +access +r +m+zusys -L xilinx_vip -L xpm -L xil_defaultlib -L xlconcat_v2_1_3 -L axi_infrastructure_v1_1_0 -L axi_vip_v1_1_6 -L zynq_ultra_ps_e_vip_v1_0_6 -L axi_lite_ipif_v3_0_4 -L lib_cdc_v1_0_2 -L interrupt_control_v3_1_4 -L axi_gpio_v2_0_22 -L proc_sys_reset_v5_0_13 -L microblaze_v11_0_2 -L lmb_v10_v3_0_10 -L lmb_bram_if_cntlr_v4_0_17 -L blk_mem_gen_v8_4_4 -L axi_intc_v4_1_14 -L mdm_v3_2_17 -L generic_baseblocks_v2_1_0 -L axi_register_slice_v2_1_20 -L fifo_generator_v13_2_5 -L axi_data_fifo_v2_1_19 -L axi_crossbar_v2_1_21 -L xlconstant_v1_1_6 -L axi_protocol_converter_v2_1_20 -L axi_clock_converter_v2_1_19 -L axi_dwidth_converter_v2_1_20 -L xilinx_vip -L unisims_ver -L unimacro_ver -L secureip -O5 xil_defaultlib.zusys xil_defaultlib.glbl

do {wave.do}

view wave
view structure

do {zusys.udo}

run -all

endsim

quit -force
