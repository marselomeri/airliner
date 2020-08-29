
################################################################
# This is a generated script based on design: bd_71cc
#
# Though there are limitations about the generated script,
# the main purpose of this utility is to make learning
# IP Integrator Tcl commands easier.
################################################################

namespace eval _tcl {
proc get_script_folder {} {
   set script_path [file normalize [info script]]
   set script_folder [file dirname $script_path]
   return $script_folder
}
}
variable script_folder
set script_folder [_tcl::get_script_folder]

################################################################
# Check if script is running in correct Vivado version.
################################################################
set scripts_vivado_version 2019.2
set current_vivado_version [version -short]

if { [string first $scripts_vivado_version $current_vivado_version] == -1 } {
   puts ""
   catch {common::send_msg_id "BD_TCL-109" "ERROR" "This script was generated using Vivado <$scripts_vivado_version> and is being run in <$current_vivado_version> of Vivado. Please run the script in Vivado <$scripts_vivado_version> then open the design in Vivado <$current_vivado_version>. Upgrade the design by running \"Tools => Report => Report IP Status...\", then run write_bd_tcl to create an updated script."}

   return 1
}

################################################################
# START
################################################################

# To test this script, run the following commands from Vivado Tcl console:
# source bd_71cc_script.tcl

# If there is no project opened, this script will create a
# project, but make sure you do not have an existing project
# <./myproj/project_1.xpr> in the current working folder.

set list_projs [get_projects -quiet]
if { $list_projs eq "" } {
   create_project project_1 myproj -part xczu2cg-sfvc784-1-i
   set_property BOARD_PART trenz.biz:te0820_2cg_1i:part0:2.0 [current_project]
}


# CHANGE DESIGN NAME HERE
variable design_name
set design_name bd_71cc

# If you do not already have an existing IP Integrator design open,
# you can create a design using the following command:
#    create_bd_design $design_name

# Creating design if needed
set errMsg ""
set nRet 0

set cur_design [current_bd_design -quiet]
set list_cells [get_bd_cells -quiet]

if { ${design_name} eq "" } {
   # USE CASES:
   #    1) Design_name not set

   set errMsg "Please set the variable <design_name> to a non-empty value."
   set nRet 1

} elseif { ${cur_design} ne "" && ${list_cells} eq "" } {
   # USE CASES:
   #    2): Current design opened AND is empty AND names same.
   #    3): Current design opened AND is empty AND names diff; design_name NOT in project.
   #    4): Current design opened AND is empty AND names diff; design_name exists in project.

   if { $cur_design ne $design_name } {
      common::send_msg_id "BD_TCL-001" "INFO" "Changing value of <design_name> from <$design_name> to <$cur_design> since current design is empty."
      set design_name [get_property NAME $cur_design]
   }
   common::send_msg_id "BD_TCL-002" "INFO" "Constructing design in IPI design <$cur_design>..."

} elseif { ${cur_design} ne "" && $list_cells ne "" && $cur_design eq $design_name } {
   # USE CASES:
   #    5) Current design opened AND has components AND same names.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 1
} elseif { [get_files -quiet ${design_name}.bd] ne "" } {
   # USE CASES: 
   #    6) Current opened design, has components, but diff names, design_name exists in project.
   #    7) No opened design, design_name exists in project.

   set errMsg "Design <$design_name> already exists in your project, please set the variable <design_name> to another value."
   set nRet 2

} else {
   # USE CASES:
   #    8) No opened design, design_name not in project.
   #    9) Current opened design, has components, but diff names, design_name not in project.

   common::send_msg_id "BD_TCL-003" "INFO" "Currently there is no design <$design_name> in project, so creating one..."

   create_bd_design -bdsource SBD $design_name

   common::send_msg_id "BD_TCL-004" "INFO" "Making design <$design_name> as current_bd_design."
   current_bd_design $design_name

}

common::send_msg_id "BD_TCL-005" "INFO" "Currently the variable <design_name> is equal to \"$design_name\"."

if { $nRet != 0 } {
   catch {common::send_msg_id "BD_TCL-114" "ERROR" $errMsg}
   return $nRet
}

##################################################################
# DESIGN PROCs
##################################################################



# Procedure to create entire design; Provide argument to make
# procedure reusable. If parentCell is "", will use root.
proc create_root_design { parentCell } {

  variable script_folder
  variable design_name

  if { $parentCell eq "" } {
     set parentCell [get_bd_cells /]
  }

  # Get object for parentCell
  set parentObj [get_bd_cells $parentCell]
  if { $parentObj == "" } {
     catch {common::send_msg_id "BD_TCL-100" "ERROR" "Unable to find parent cell <$parentCell>!"}
     return
  }

  # Make sure parentObj is hier blk
  set parentType [get_property TYPE $parentObj]
  if { $parentType ne "hier" } {
     catch {common::send_msg_id "BD_TCL-101" "ERROR" "Parent <$parentObj> has TYPE = <$parentType>. Expected to be <hier>."}
     return
  }

  # Save current instance; Restore later
  set oldCurInst [current_bd_instance .]

  # Set parent object as current
  current_bd_instance $parentObj


  # Create interface ports
  set SLOT_0_IIC [ create_bd_intf_port -mode Monitor -vlnv xilinx.com:interface:iic_rtl:1.0 SLOT_0_IIC ]

  set SLOT_1_UART [ create_bd_intf_port -mode Monitor -vlnv xilinx.com:interface:uart_rtl:1.0 SLOT_1_UART ]

  set SLOT_2_SPI [ create_bd_intf_port -mode Monitor -vlnv xilinx.com:interface:spi_rtl:1.0 SLOT_2_SPI ]

  set SLOT_3_SPI [ create_bd_intf_port -mode Monitor -vlnv xilinx.com:interface:spi_rtl:1.0 SLOT_3_SPI ]


  # Create ports
  set clk [ create_bd_port -dir I -type clk clk ]
  set_property -dict [ list \
   CONFIG.ASSOCIATED_BUSIF {} \
   CONFIG.ASSOCIATED_RESET {} \
 ] $clk

  # Create instance: ila_lib, and set properties
  set ila_lib [ create_bd_cell -type ip -vlnv xilinx.com:ip:ila:6.2 ila_lib ]
  set_property -dict [ list \
   CONFIG.ALL_PROBE_SAME_MU {TRUE} \
   CONFIG.ALL_PROBE_SAME_MU_CNT {1} \
   CONFIG.C_ADV_TRIGGER {FALSE} \
   CONFIG.C_DATA_DEPTH {1024} \
   CONFIG.C_EN_STRG_QUAL {0} \
   CONFIG.C_EN_TIME_TAG {0} \
   CONFIG.C_ILA_CLK_FREQ {99999985} \
   CONFIG.C_INPUT_PIPE_STAGES {0} \
   CONFIG.C_MONITOR_TYPE {Native} \
   CONFIG.C_NUM_OF_PROBES {32} \
   CONFIG.C_PROBE0_TYPE {0} \
   CONFIG.C_PROBE0_WIDTH {1} \
   CONFIG.C_PROBE10_TYPE {0} \
   CONFIG.C_PROBE10_WIDTH {1} \
   CONFIG.C_PROBE11_TYPE {0} \
   CONFIG.C_PROBE11_WIDTH {1} \
   CONFIG.C_PROBE12_TYPE {0} \
   CONFIG.C_PROBE12_WIDTH {1} \
   CONFIG.C_PROBE13_TYPE {0} \
   CONFIG.C_PROBE13_WIDTH {1} \
   CONFIG.C_PROBE14_TYPE {0} \
   CONFIG.C_PROBE14_WIDTH {1} \
   CONFIG.C_PROBE15_TYPE {0} \
   CONFIG.C_PROBE15_WIDTH {1} \
   CONFIG.C_PROBE16_TYPE {0} \
   CONFIG.C_PROBE16_WIDTH {1} \
   CONFIG.C_PROBE17_TYPE {0} \
   CONFIG.C_PROBE17_WIDTH {1} \
   CONFIG.C_PROBE18_TYPE {0} \
   CONFIG.C_PROBE18_WIDTH {1} \
   CONFIG.C_PROBE19_TYPE {0} \
   CONFIG.C_PROBE19_WIDTH {1} \
   CONFIG.C_PROBE1_TYPE {0} \
   CONFIG.C_PROBE1_WIDTH {1} \
   CONFIG.C_PROBE20_TYPE {0} \
   CONFIG.C_PROBE20_WIDTH {1} \
   CONFIG.C_PROBE21_TYPE {0} \
   CONFIG.C_PROBE21_WIDTH {1} \
   CONFIG.C_PROBE22_TYPE {0} \
   CONFIG.C_PROBE22_WIDTH {1} \
   CONFIG.C_PROBE23_TYPE {0} \
   CONFIG.C_PROBE23_WIDTH {1} \
   CONFIG.C_PROBE24_TYPE {0} \
   CONFIG.C_PROBE24_WIDTH {1} \
   CONFIG.C_PROBE25_TYPE {0} \
   CONFIG.C_PROBE25_WIDTH {1} \
   CONFIG.C_PROBE26_TYPE {0} \
   CONFIG.C_PROBE26_WIDTH {1} \
   CONFIG.C_PROBE27_TYPE {0} \
   CONFIG.C_PROBE27_WIDTH {1} \
   CONFIG.C_PROBE28_TYPE {0} \
   CONFIG.C_PROBE28_WIDTH {1} \
   CONFIG.C_PROBE29_TYPE {0} \
   CONFIG.C_PROBE29_WIDTH {1} \
   CONFIG.C_PROBE2_TYPE {0} \
   CONFIG.C_PROBE2_WIDTH {1} \
   CONFIG.C_PROBE30_TYPE {0} \
   CONFIG.C_PROBE30_WIDTH {1} \
   CONFIG.C_PROBE31_TYPE {0} \
   CONFIG.C_PROBE31_WIDTH {1} \
   CONFIG.C_PROBE3_TYPE {0} \
   CONFIG.C_PROBE3_WIDTH {1} \
   CONFIG.C_PROBE4_TYPE {0} \
   CONFIG.C_PROBE4_WIDTH {1} \
   CONFIG.C_PROBE5_TYPE {0} \
   CONFIG.C_PROBE5_WIDTH {1} \
   CONFIG.C_PROBE6_TYPE {0} \
   CONFIG.C_PROBE6_WIDTH {1} \
   CONFIG.C_PROBE7_TYPE {0} \
   CONFIG.C_PROBE7_WIDTH {1} \
   CONFIG.C_PROBE8_TYPE {0} \
   CONFIG.C_PROBE8_WIDTH {1} \
   CONFIG.C_PROBE9_TYPE {0} \
   CONFIG.C_PROBE9_WIDTH {1} \
   CONFIG.C_TIME_TAG_WIDTH {32} \
   CONFIG.C_TRIGIN_EN {false} \
   CONFIG.C_TRIGOUT_EN {false} \
   CONFIG.C_XLNX_HW_PROBE_INFO {DEFAULT} \
 ] $ila_lib

  # Create port connections
  connect_bd_net -net SLOT_0_IIC_scl_i_1 [get_bd_ports SLOT_0_IIC_scl_i] [get_bd_pins ila_lib/probe0]
  connect_bd_net -net SLOT_0_IIC_scl_o_1 [get_bd_ports SLOT_0_IIC_scl_o] [get_bd_pins ila_lib/probe1]
  connect_bd_net -net SLOT_0_IIC_scl_t_1 [get_bd_ports SLOT_0_IIC_scl_t] [get_bd_pins ila_lib/probe2]
  connect_bd_net -net SLOT_0_IIC_sda_i_1 [get_bd_ports SLOT_0_IIC_sda_i] [get_bd_pins ila_lib/probe3]
  connect_bd_net -net SLOT_0_IIC_sda_o_1 [get_bd_ports SLOT_0_IIC_sda_o] [get_bd_pins ila_lib/probe4]
  connect_bd_net -net SLOT_0_IIC_sda_t_1 [get_bd_ports SLOT_0_IIC_sda_t] [get_bd_pins ila_lib/probe5]
  connect_bd_net -net SLOT_1_UART_rxd_1 [get_bd_ports SLOT_1_UART_rxd] [get_bd_pins ila_lib/probe7]
  connect_bd_net -net SLOT_1_UART_txd_1 [get_bd_ports SLOT_1_UART_txd] [get_bd_pins ila_lib/probe6]
  connect_bd_net -net SLOT_2_SPI_io0_i_1 [get_bd_ports SLOT_2_SPI_io0_i] [get_bd_pins ila_lib/probe14]
  connect_bd_net -net SLOT_2_SPI_io0_o_1 [get_bd_ports SLOT_2_SPI_io0_o] [get_bd_pins ila_lib/probe12]
  connect_bd_net -net SLOT_2_SPI_io0_t_1 [get_bd_ports SLOT_2_SPI_io0_t] [get_bd_pins ila_lib/probe13]
  connect_bd_net -net SLOT_2_SPI_io1_i_1 [get_bd_ports SLOT_2_SPI_io1_i] [get_bd_pins ila_lib/probe11]
  connect_bd_net -net SLOT_2_SPI_io1_o_1 [get_bd_ports SLOT_2_SPI_io1_o] [get_bd_pins ila_lib/probe15]
  connect_bd_net -net SLOT_2_SPI_io1_t_1 [get_bd_ports SLOT_2_SPI_io1_t] [get_bd_pins ila_lib/probe16]
  connect_bd_net -net SLOT_2_SPI_sck_i_1 [get_bd_ports SLOT_2_SPI_sck_i] [get_bd_pins ila_lib/probe8]
  connect_bd_net -net SLOT_2_SPI_sck_o_1 [get_bd_ports SLOT_2_SPI_sck_o] [get_bd_pins ila_lib/probe9]
  connect_bd_net -net SLOT_2_SPI_sck_t_1 [get_bd_ports SLOT_2_SPI_sck_t] [get_bd_pins ila_lib/probe10]
  connect_bd_net -net SLOT_2_SPI_ss_i_1 [get_bd_ports SLOT_2_SPI_ss_i] [get_bd_pins ila_lib/probe17]
  connect_bd_net -net SLOT_2_SPI_ss_o_1 [get_bd_ports SLOT_2_SPI_ss_o] [get_bd_pins ila_lib/probe18]
  connect_bd_net -net SLOT_2_SPI_ss_t_1 [get_bd_ports SLOT_2_SPI_ss_t] [get_bd_pins ila_lib/probe19]
  connect_bd_net -net SLOT_3_SPI_io0_i_1 [get_bd_ports SLOT_3_SPI_io0_i] [get_bd_pins ila_lib/probe26]
  connect_bd_net -net SLOT_3_SPI_io0_o_1 [get_bd_ports SLOT_3_SPI_io0_o] [get_bd_pins ila_lib/probe24]
  connect_bd_net -net SLOT_3_SPI_io0_t_1 [get_bd_ports SLOT_3_SPI_io0_t] [get_bd_pins ila_lib/probe25]
  connect_bd_net -net SLOT_3_SPI_io1_i_1 [get_bd_ports SLOT_3_SPI_io1_i] [get_bd_pins ila_lib/probe23]
  connect_bd_net -net SLOT_3_SPI_io1_o_1 [get_bd_ports SLOT_3_SPI_io1_o] [get_bd_pins ila_lib/probe27]
  connect_bd_net -net SLOT_3_SPI_io1_t_1 [get_bd_ports SLOT_3_SPI_io1_t] [get_bd_pins ila_lib/probe28]
  connect_bd_net -net SLOT_3_SPI_sck_i_1 [get_bd_ports SLOT_3_SPI_sck_i] [get_bd_pins ila_lib/probe20]
  connect_bd_net -net SLOT_3_SPI_sck_o_1 [get_bd_ports SLOT_3_SPI_sck_o] [get_bd_pins ila_lib/probe21]
  connect_bd_net -net SLOT_3_SPI_sck_t_1 [get_bd_ports SLOT_3_SPI_sck_t] [get_bd_pins ila_lib/probe22]
  connect_bd_net -net SLOT_3_SPI_ss_i_1 [get_bd_ports SLOT_3_SPI_ss_i] [get_bd_pins ila_lib/probe29]
  connect_bd_net -net SLOT_3_SPI_ss_o_1 [get_bd_ports SLOT_3_SPI_ss_o] [get_bd_pins ila_lib/probe30]
  connect_bd_net -net SLOT_3_SPI_ss_t_1 [get_bd_ports SLOT_3_SPI_ss_t] [get_bd_pins ila_lib/probe31]
  connect_bd_net -net clk_1 [get_bd_ports clk] [get_bd_pins ila_lib/clk]

  # Create address segments


  # Restore current instance
  current_bd_instance $oldCurInst

  validate_bd_design
  save_bd_design
}
# End of create_root_design()


##################################################################
# MAIN FLOW
##################################################################

create_root_design ""


