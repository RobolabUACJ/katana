#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/usb_device.o ${OBJECTDIR}/usb_function_generic.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/main.o ${OBJECTDIR}/posicion.o ${OBJECTDIR}/sensores.o
POSSIBLE_DEPFILES=${OBJECTDIR}/usb_descriptors.o.d ${OBJECTDIR}/usb_device.o.d ${OBJECTDIR}/usb_function_generic.o.d ${OBJECTDIR}/adc.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/posicion.o.d ${OBJECTDIR}/sensores.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/usb_device.o ${OBJECTDIR}/usb_function_generic.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/main.o ${OBJECTDIR}/posicion.o ${OBJECTDIR}/sensores.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX460F512L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c  
	
${OBJECTDIR}/usb_device.o: usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_device.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/usb_device.o.d" -o ${OBJECTDIR}/usb_device.o usb_device.c  
	
${OBJECTDIR}/usb_function_generic.o: usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_function_generic.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_function_generic.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/usb_function_generic.o.d" -o ${OBJECTDIR}/usb_function_generic.o usb_function_generic.c  
	
${OBJECTDIR}/adc.o: adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/adc.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/adc.o.d" -o ${OBJECTDIR}/adc.o adc.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/posicion.o: posicion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/posicion.o.d 
	@${FIXDEPS} "${OBJECTDIR}/posicion.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/posicion.o.d" -o ${OBJECTDIR}/posicion.o posicion.c  
	
${OBJECTDIR}/sensores.o: sensores.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensores.o.d 
	@${FIXDEPS} "${OBJECTDIR}/sensores.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/sensores.o.d" -o ${OBJECTDIR}/sensores.o sensores.c  
	
else
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c  
	
${OBJECTDIR}/usb_device.o: usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_device.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/usb_device.o.d" -o ${OBJECTDIR}/usb_device.o usb_device.c  
	
${OBJECTDIR}/usb_function_generic.o: usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_function_generic.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_function_generic.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/usb_function_generic.o.d" -o ${OBJECTDIR}/usb_function_generic.o usb_function_generic.c  
	
${OBJECTDIR}/adc.o: adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/adc.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/adc.o.d" -o ${OBJECTDIR}/adc.o adc.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/posicion.o: posicion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/posicion.o.d 
	@${FIXDEPS} "${OBJECTDIR}/posicion.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/posicion.o.d" -o ${OBJECTDIR}/posicion.o posicion.c  
	
${OBJECTDIR}/sensores.o: sensores.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensores.o.d 
	@${FIXDEPS} "${OBJECTDIR}/sensores.o.d" $(SILENT) -c  ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"/opt/microchip/xc32/v1.00/pic32-libs/include" -I"/opt/microchip/xc32/v1.00/pic32mx/include" -MMD -MF "${OBJECTDIR}/sensores.o.d" -o ${OBJECTDIR}/sensores.o sensores.c  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1
else
dist/${CND_CONF}/${IMAGE_TYPE}/Firmware.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/Firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}       -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION)
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
