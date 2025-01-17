#
# This file is generated by ModusToolbox during the 'make getlibs' operation
# Any edits to this file will be lost the next time the library manager is run or
# the next time 'make getlibs' is run.
#
# List of local libraries


# Path to the current BSP
SEARCH_TARGET_APP_KIT_XMC47_RELAX_V1=bsps/TARGET_APP_KIT_XMC47_RELAX_V1

# The search paths for the included middleware
SEARCH_freertos=../mtb_shared/freertos/release-v10.5.002
SEARCH_retarget-io-cat3=../mtb_shared/retarget-io-cat3/release-v1.1.0
SEARCH_abstraction-rtos=../mtb_shared/abstraction-rtos/release-v1.8.1
SEARCH_clib-support=../mtb_shared/clib-support/release-v1.5.0
SEARCH_cmsis=../mtb_shared/cmsis/release-v5.8.0
SEARCH_core-lib=../mtb_shared/core-lib/release-v1.4.2
SEARCH_core-make=../mtb_shared/core-make/release-v3.3.1
SEARCH_mtb-xmclib-cat3=../mtb_shared/mtb-xmclib-cat3/release-v4.4.0
SEARCH_recipe-make-cat3=../mtb_shared/recipe-make-cat3/release-v2.2.0

# Search libraries added to build
SEARCH_MTB_MK+=$(SEARCH_freertos)
SEARCH_MTB_MK+=$(SEARCH_retarget-io-cat3)
SEARCH_MTB_MK+=$(SEARCH_abstraction-rtos)
SEARCH_MTB_MK+=$(SEARCH_clib-support)
SEARCH_MTB_MK+=$(SEARCH_cmsis)
SEARCH_MTB_MK+=$(SEARCH_core-lib)
SEARCH_MTB_MK+=$(SEARCH_core-make)
SEARCH_MTB_MK+=$(SEARCH_device-db)
SEARCH_MTB_MK+=$(SEARCH_mtb-xmclib-cat3)
SEARCH_MTB_MK+=$(SEARCH_recipe-make-cat3)

-include $(CY_INTERNAL_APP_PATH)/importedbsp.mk
COMPONENTS += MW_FREERTOS
COMPONENTS += MW_RETARGET_IO_CAT3
COMPONENTS += MW_ABSTRACTION_RTOS
COMPONENTS += MW_CLIB_SUPPORT
COMPONENTS += MW_CMSIS
COMPONENTS += MW_CORE_LIB
COMPONENTS += MW_CORE_MAKE
COMPONENTS += MW_DEVICE_DB
COMPONENTS += MW_MTB_XMCLIB_CAT3
COMPONENTS += MW_RECIPE_MAKE_CAT3

# Register map file
DEVICE_XMC4700-F144x2048_SVD=$(SEARCH_mtb-xmclib-cat3)/CMSIS/Infineon/SVD/XMC4700.svd


#
# generate make targets for the graphical editors that are specific to this project
#

modlibs:
	$(CY_TOOL_mtblaunch_EXE_ABS) --project . --short-name library-manager
.PHONY: modlibs

CY_HELP_modlibs=Launches the Library Manager 2.10 GUI
CY_HELP_modlibs_VERBOSE=Launches the Library Manager 2.10 GUI. Check the Library Manager 2.10 User Guide for more information.
mtb_help_tool_modlibs:
	@:
	$(info $(MTB__SPACE)modlibs             $(CY_HELP_modlibs))

mtb_help_tools_end: mtb_help_tool_modlibs
mtb_help_tool_modlibs: mtb_help_tools_start
.PHONY: mtb_help_tool_modlibs

library-manager:
	$(CY_TOOL_mtblaunch_EXE_ABS) --project . --short-name library-manager
.PHONY: library-manager

CY_HELP_library-manager=Launches the Library Manager 2.10 GUI
CY_HELP_library-manager_VERBOSE=Launches the Library Manager 2.10 GUI. Check the Library Manager 2.10 User Guide for more information.
mtb_help_tool_library-manager:
	@:
	$(info $(MTB__SPACE)library-manager     $(CY_HELP_library-manager))

mtb_help_tools_end: mtb_help_tool_library-manager
mtb_help_tool_library-manager: mtb_help_tools_start
.PHONY: mtb_help_tool_library-manager

config:
	$(CY_TOOL_mtblaunch_EXE_ABS) --project . --short-name device-configurator
.PHONY: config

CY_HELP_config=Launches the Device Configurator 4.10 GUI for the target's modus file
CY_HELP_config_VERBOSE=Launches the Device Configurator 4.10 GUI. Check the Device Configurator 4.10 User Guide for more information.
mtb_help_tool_config:
	@:
	$(info $(MTB__SPACE)config              $(CY_HELP_config))

mtb_help_tools_end: mtb_help_tool_config
mtb_help_tool_config: mtb_help_tools_start
.PHONY: mtb_help_tool_config

device-configurator:
	$(CY_TOOL_mtblaunch_EXE_ABS) --project . --short-name device-configurator
.PHONY: device-configurator

CY_HELP_device-configurator=Launches the Device Configurator 4.10 GUI for the target's modus file
CY_HELP_device-configurator_VERBOSE=Launches the Device Configurator 4.10 GUI. Check the Device Configurator 4.10 User Guide for more information.
mtb_help_tool_device-configurator:
	@:
	$(info $(MTB__SPACE)device-configurator $(CY_HELP_device-configurator))

mtb_help_tools_end: mtb_help_tool_device-configurator
mtb_help_tool_device-configurator: mtb_help_tools_start
.PHONY: mtb_help_tool_device-configurator

bsp-assistant:
	$(CY_TOOL_mtblaunch_EXE_ABS) --project . --short-name bsp-assistant
.PHONY: bsp-assistant

CY_HELP_bsp-assistant=Launches the BSP Assistant 1.10 GUI
CY_HELP_bsp-assistant_VERBOSE=Launches the BSP Assistant 1.10 GUI. Check the BSP Assistant 1.10 User Guide for more information.
mtb_help_tool_bsp-assistant:
	@:
	$(info $(MTB__SPACE)bsp-assistant       $(CY_HELP_bsp-assistant))

mtb_help_tools_end: mtb_help_tool_bsp-assistant
mtb_help_tool_bsp-assistant: mtb_help_tools_start
.PHONY: mtb_help_tool_bsp-assistant

.PHONY: mtb_help_tools_start mtb_help_tools_end
