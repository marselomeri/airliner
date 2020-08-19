set_property PACKAGE_PIN K9 [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property PACKAGE_PIN J9 [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property PACKAGE_PIN H1 [get_ports {x0[0]}]
set_property PACKAGE_PIN J1 [get_ports {x1[0]}]
set_property DIRECTION IN [get_ports {x1[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {x1[0]}]
set_property DIRECTION IN [get_ports {x0[0]}]
set_property IOSTANDARD LVCMOS18 [get_ports {x0[0]}]
set_property DIRECTION IN [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property IOSTANDARD LVDS [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property DIFF_TERM TRUE [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property EQUALIZATION EQ_NONE [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property LVDS_PRE_EMPHASIS FALSE [get_ports {SI5338_CLK0_D_clk_n[0]}]
set_property DIRECTION IN [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property IOSTANDARD LVDS [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property DIFF_TERM TRUE [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property EQUALIZATION EQ_NONE [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property DIFF_TERM_ADV TERM_100 [get_ports {SI5338_CLK0_D_clk_p[0]}]
set_property LVDS_PRE_EMPHASIS FALSE [get_ports {SI5338_CLK0_D_clk_p[0]}]
current_instance dbg_hub/inst
create_waiver -type CDC -id {CDC-6} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD2/stat_reg_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD2/stat_reg_1_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-6} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD3/stat_reg_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD3/stat_reg_1_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-6} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_WR/U_WR_FIFO/SUBCORE_FIFO.xsdbm_v3_0_0_wrfifo_inst/inst_fifo_gen/gconvfifo.rf/grf.rf/gntv_or_sync_fifo.gcx.clkx/gnxpm_cdc.wr_pntr_gc_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_WR/U_WR_FIFO/SUBCORE_FIFO.xsdbm_v3_0_0_wrfifo_inst/inst_fifo_gen/gconvfifo.rf/grf.rf/gntv_or_sync_fifo.gcx.clkx/*.gsync_stage[1].rd_stg_inst/Q_reg_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-6} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_RD/U_RD_FIFO/SUBCORE_FIFO.xsdbm_v3_0_0_rdfifo_inst/inst_fifo_gen/gconvfifo.rf/grf.rf/gntv_or_sync_fifo.gcx.clkx/gnxpm_cdc.wr_pntr_gc_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_RD/U_RD_FIFO/SUBCORE_FIFO.xsdbm_v3_0_0_rdfifo_inst/inst_fifo_gen/gconvfifo.rf/grf.rf/gntv_or_sync_fifo.gcx.clkx/*.gsync_stage[1].rd_stg_inst/Q_reg_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-6} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_WR/U_WR_FIFO/SUBCORE_FIFO.xsdbm_v3_0_0_wrfifo_inst/inst_fifo_gen/gconvfifo.rf/grf.rf/gntv_or_sync_fifo.gcx.clkx/gnxpm_cdc.rd_pntr_gc_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_WR/U_WR_FIFO/SUBCORE_FIFO.xsdbm_v3_0_0_wrfifo_inst/inst_fifo_gen/gconvfifo.rf/grf.rf/gntv_or_sync_fifo.gcx.clkx/*.gsync_stage[1].wr_stg_inst/Q_reg_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-6} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_RD/U_RD_FIFO/SUBCORE_FIFO.xsdbm_v3_0_0_rdfifo_inst/inst_fifo_gen/gconvfifo.rf/grf.rf/gntv_or_sync_fifo.gcx.clkx/gnxpm_cdc.rd_pntr_gc_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_RD/U_RD_FIFO/SUBCORE_FIFO.xsdbm_v3_0_0_rdfifo_inst/inst_fifo_gen/gconvfifo.rf/grf.rf/gntv_or_sync_fifo.gcx.clkx/*.gsync_stage[1].wr_stg_inst/Q_reg_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-6} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD7_STAT/stat_reg_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD7_STAT/stat_reg_1_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~CLK -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_RD/U_RD_FIFO/SUBCORE_FIFO.xsdbm_v3_0_0_rdfifo_inst/inst_fifo_gen/gconvfifo.rf/grf.rf/gntv_or_sync_fifo.mem/gdm.dm_gen.dm/RAM_reg*/RAM*"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ *U_RD_FIFO*gdm.dm_gen.dm*/gpr1.dout_i_reg*}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~CLK -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_WR/U_WR_FIFO/SUBCORE_FIFO.xsdbm_v3_0_0_wrfifo_inst/inst_fifo_gen/gconvfifo.rf/grf.rf/gntv_or_sync_fifo.mem/gdm.dm_gen.dm/RAM_reg*/RAM*"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ *U_WR_FIFO*gdm.dm_gen.dm*/gpr1.dout_i_reg*}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD1/ctl_reg_reg[0]"}]] -to [get_pins -filter REF_PIN_NAME=~R -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD4/shift_reg_in_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD1/ctl_reg_reg[0]"}]] -to [get_pins -filter REF_PIN_NAME=~R -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD5/shift_reg_in_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD1/ctl_reg_reg[0]"}]] -to [get_pins -filter REF_PIN_NAME=~R -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD7_CTL/shift_reg_in_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD1/shift_reg_in_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD1/ctl_reg_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD4/shift_reg_in_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD4/ctl_reg_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD5/shift_reg_in_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD5/ctl_reg_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD7_CTL/shift_reg_in_reg[0]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD7_STAT/stat_reg_reg[0]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD7_CTL/shift_reg_in_reg[*]"}]] -to [get_pins -filter REF_PIN_NAME=~D -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD7_CTL/ctl_reg_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
create_waiver -type CDC -id {CDC-15} -user "xsdbm" -desc "CDC is handled through handshake process" -tags "1025927" -scope -internal -from [get_pins -filter REF_PIN_NAME=~C -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/rddata_rst_reg"}]] -to [get_pins -filter REF_PIN_NAME=~CLR -of_objects [get_cells -hierarchical -filter {NAME =~ "*BSCANID.u_xsdbm_id/CORE_XSDB.UUT_MASTER/U_ICON_INTERFACE/U_CMD6_RD/shift_reg_in_reg[*]"}]] -timestamp "Mon Jan 13 14:08:35 GMT 2020"
#revert back to original instance
current_instance -quiet
