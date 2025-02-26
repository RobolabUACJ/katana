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
OBJECTFILES_QUOTED_IF_SPACED="${OBJECTDIR}/TCPIP Stack/Announce.o" "${OBJECTDIR}/TCPIP Stack/ARCFOUR.o" "${OBJECTDIR}/TCPIP Stack/ARP.o" "${OBJECTDIR}/TCPIP Stack/AutoIP.o" "${OBJECTDIR}/TCPIP Stack/BerkeleyAPI.o" "${OBJECTDIR}/TCPIP Stack/BigInt.o" "${OBJECTDIR}/TCPIP Stack/Delay.o" "${OBJECTDIR}/TCPIP Stack/DHCP.o" "${OBJECTDIR}/TCPIP Stack/DHCPs.o" "${OBJECTDIR}/TCPIP Stack/DNS.o" "${OBJECTDIR}/TCPIP Stack/DNSs.o" "${OBJECTDIR}/TCPIP Stack/DynDNS.o" "${OBJECTDIR}/TCPIP Stack/ENC28J60.o" "${OBJECTDIR}/TCPIP Stack/ENCX24J600.o" "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhyDP83640.o" "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8700.o" "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8720.o" "${OBJECTDIR}/TCPIP Stack/FileSystem.o" "${OBJECTDIR}/TCPIP Stack/FTP.o" "${OBJECTDIR}/TCPIP Stack/Hashes.o" "${OBJECTDIR}/TCPIP Stack/Helpers.o" "${OBJECTDIR}/TCPIP Stack/HTTP2.o" "${OBJECTDIR}/TCPIP Stack/ICMP.o" "${OBJECTDIR}/TCPIP Stack/IP.o" "${OBJECTDIR}/TCPIP Stack/LCDBlocking.o" "${OBJECTDIR}/TCPIP Stack/MPFS2.o" "${OBJECTDIR}/TCPIP Stack/NBNS.o" "${OBJECTDIR}/TCPIP Stack/Random.o" "${OBJECTDIR}/TCPIP Stack/Reboot.o" "${OBJECTDIR}/TCPIP Stack/RSA.o" "${OBJECTDIR}/TCPIP Stack/SMTP.o" "${OBJECTDIR}/TCPIP Stack/SNMP.o" "${OBJECTDIR}/TCPIP Stack/SNMPv3.o" "${OBJECTDIR}/TCPIP Stack/SNMPv3USM.o" "${OBJECTDIR}/TCPIP Stack/SNTP.o" "${OBJECTDIR}/TCPIP Stack/SPIEEPROM.o" "${OBJECTDIR}/TCPIP Stack/SPIFlash.o" "${OBJECTDIR}/TCPIP Stack/SPIRAM.o" "${OBJECTDIR}/TCPIP Stack/SSL.o" "${OBJECTDIR}/TCPIP Stack/StackTsk.o" "${OBJECTDIR}/TCPIP Stack/TCP.o" "${OBJECTDIR}/TCPIP Stack/TCPPerformanceTest.o" "${OBJECTDIR}/TCPIP Stack/Telnet.o" "${OBJECTDIR}/TCPIP Stack/TFTPc.o" "${OBJECTDIR}/TCPIP Stack/Tick.o" "${OBJECTDIR}/TCPIP Stack/UART.o" "${OBJECTDIR}/TCPIP Stack/UART2TCPBridge.o" "${OBJECTDIR}/TCPIP Stack/UDP.o" "${OBJECTDIR}/TCPIP Stack/UDPPerformanceTest.o" "${OBJECTDIR}/TCPIP Stack/ZeroconfHelper.o" "${OBJECTDIR}/TCPIP Stack/ZeroconfLinkLocal.o" "${OBJECTDIR}/TCPIP Stack/ZeroconfMulticastDNS.o" ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/usb_device.o ${OBJECTDIR}/usb_function_generic.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/main.o ${OBJECTDIR}/posicion.o ${OBJECTDIR}/sensores.o
POSSIBLE_DEPFILES="${OBJECTDIR}/TCPIP Stack/Announce.o.d" "${OBJECTDIR}/TCPIP Stack/ARCFOUR.o.d" "${OBJECTDIR}/TCPIP Stack/ARP.o.d" "${OBJECTDIR}/TCPIP Stack/AutoIP.o.d" "${OBJECTDIR}/TCPIP Stack/BerkeleyAPI.o.d" "${OBJECTDIR}/TCPIP Stack/BigInt.o.d" "${OBJECTDIR}/TCPIP Stack/Delay.o.d" "${OBJECTDIR}/TCPIP Stack/DHCP.o.d" "${OBJECTDIR}/TCPIP Stack/DHCPs.o.d" "${OBJECTDIR}/TCPIP Stack/DNS.o.d" "${OBJECTDIR}/TCPIP Stack/DNSs.o.d" "${OBJECTDIR}/TCPIP Stack/DynDNS.o.d" "${OBJECTDIR}/TCPIP Stack/ENC28J60.o.d" "${OBJECTDIR}/TCPIP Stack/ENCX24J600.o.d" "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhyDP83640.o.d" "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8700.o.d" "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8720.o.d" "${OBJECTDIR}/TCPIP Stack/FileSystem.o.d" "${OBJECTDIR}/TCPIP Stack/FTP.o.d" "${OBJECTDIR}/TCPIP Stack/Hashes.o.d" "${OBJECTDIR}/TCPIP Stack/Helpers.o.d" "${OBJECTDIR}/TCPIP Stack/HTTP2.o.d" "${OBJECTDIR}/TCPIP Stack/ICMP.o.d" "${OBJECTDIR}/TCPIP Stack/IP.o.d" "${OBJECTDIR}/TCPIP Stack/LCDBlocking.o.d" "${OBJECTDIR}/TCPIP Stack/MPFS2.o.d" "${OBJECTDIR}/TCPIP Stack/NBNS.o.d" "${OBJECTDIR}/TCPIP Stack/Random.o.d" "${OBJECTDIR}/TCPIP Stack/Reboot.o.d" "${OBJECTDIR}/TCPIP Stack/RSA.o.d" "${OBJECTDIR}/TCPIP Stack/SMTP.o.d" "${OBJECTDIR}/TCPIP Stack/SNMP.o.d" "${OBJECTDIR}/TCPIP Stack/SNMPv3.o.d" "${OBJECTDIR}/TCPIP Stack/SNMPv3USM.o.d" "${OBJECTDIR}/TCPIP Stack/SNTP.o.d" "${OBJECTDIR}/TCPIP Stack/SPIEEPROM.o.d" "${OBJECTDIR}/TCPIP Stack/SPIFlash.o.d" "${OBJECTDIR}/TCPIP Stack/SPIRAM.o.d" "${OBJECTDIR}/TCPIP Stack/SSL.o.d" "${OBJECTDIR}/TCPIP Stack/StackTsk.o.d" "${OBJECTDIR}/TCPIP Stack/TCP.o.d" "${OBJECTDIR}/TCPIP Stack/TCPPerformanceTest.o.d" "${OBJECTDIR}/TCPIP Stack/Telnet.o.d" "${OBJECTDIR}/TCPIP Stack/TFTPc.o.d" "${OBJECTDIR}/TCPIP Stack/Tick.o.d" "${OBJECTDIR}/TCPIP Stack/UART.o.d" "${OBJECTDIR}/TCPIP Stack/UART2TCPBridge.o.d" "${OBJECTDIR}/TCPIP Stack/UDP.o.d" "${OBJECTDIR}/TCPIP Stack/UDPPerformanceTest.o.d" "${OBJECTDIR}/TCPIP Stack/ZeroconfHelper.o.d" "${OBJECTDIR}/TCPIP Stack/ZeroconfLinkLocal.o.d" "${OBJECTDIR}/TCPIP Stack/ZeroconfMulticastDNS.o.d" ${OBJECTDIR}/usb_descriptors.o.d ${OBJECTDIR}/usb_device.o.d ${OBJECTDIR}/usb_function_generic.o.d ${OBJECTDIR}/adc.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/posicion.o.d ${OBJECTDIR}/sensores.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/TCPIP\ Stack/Announce.o ${OBJECTDIR}/TCPIP\ Stack/ARCFOUR.o ${OBJECTDIR}/TCPIP\ Stack/ARP.o ${OBJECTDIR}/TCPIP\ Stack/AutoIP.o ${OBJECTDIR}/TCPIP\ Stack/BerkeleyAPI.o ${OBJECTDIR}/TCPIP\ Stack/BigInt.o ${OBJECTDIR}/TCPIP\ Stack/Delay.o ${OBJECTDIR}/TCPIP\ Stack/DHCP.o ${OBJECTDIR}/TCPIP\ Stack/DHCPs.o ${OBJECTDIR}/TCPIP\ Stack/DNS.o ${OBJECTDIR}/TCPIP\ Stack/DNSs.o ${OBJECTDIR}/TCPIP\ Stack/DynDNS.o ${OBJECTDIR}/TCPIP\ Stack/ENC28J60.o ${OBJECTDIR}/TCPIP\ Stack/ENCX24J600.o ${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhyDP83640.o ${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhySMSC8700.o ${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhySMSC8720.o ${OBJECTDIR}/TCPIP\ Stack/FileSystem.o ${OBJECTDIR}/TCPIP\ Stack/FTP.o ${OBJECTDIR}/TCPIP\ Stack/Hashes.o ${OBJECTDIR}/TCPIP\ Stack/Helpers.o ${OBJECTDIR}/TCPIP\ Stack/HTTP2.o ${OBJECTDIR}/TCPIP\ Stack/ICMP.o ${OBJECTDIR}/TCPIP\ Stack/IP.o ${OBJECTDIR}/TCPIP\ Stack/LCDBlocking.o ${OBJECTDIR}/TCPIP\ Stack/MPFS2.o ${OBJECTDIR}/TCPIP\ Stack/NBNS.o ${OBJECTDIR}/TCPIP\ Stack/Random.o ${OBJECTDIR}/TCPIP\ Stack/Reboot.o ${OBJECTDIR}/TCPIP\ Stack/RSA.o ${OBJECTDIR}/TCPIP\ Stack/SMTP.o ${OBJECTDIR}/TCPIP\ Stack/SNMP.o ${OBJECTDIR}/TCPIP\ Stack/SNMPv3.o ${OBJECTDIR}/TCPIP\ Stack/SNMPv3USM.o ${OBJECTDIR}/TCPIP\ Stack/SNTP.o ${OBJECTDIR}/TCPIP\ Stack/SPIEEPROM.o ${OBJECTDIR}/TCPIP\ Stack/SPIFlash.o ${OBJECTDIR}/TCPIP\ Stack/SPIRAM.o ${OBJECTDIR}/TCPIP\ Stack/SSL.o ${OBJECTDIR}/TCPIP\ Stack/StackTsk.o ${OBJECTDIR}/TCPIP\ Stack/TCP.o ${OBJECTDIR}/TCPIP\ Stack/TCPPerformanceTest.o ${OBJECTDIR}/TCPIP\ Stack/Telnet.o ${OBJECTDIR}/TCPIP\ Stack/TFTPc.o ${OBJECTDIR}/TCPIP\ Stack/Tick.o ${OBJECTDIR}/TCPIP\ Stack/UART.o ${OBJECTDIR}/TCPIP\ Stack/UART2TCPBridge.o ${OBJECTDIR}/TCPIP\ Stack/UDP.o ${OBJECTDIR}/TCPIP\ Stack/UDPPerformanceTest.o ${OBJECTDIR}/TCPIP\ Stack/ZeroconfHelper.o ${OBJECTDIR}/TCPIP\ Stack/ZeroconfLinkLocal.o ${OBJECTDIR}/TCPIP\ Stack/ZeroconfMulticastDNS.o ${OBJECTDIR}/usb_descriptors.o ${OBJECTDIR}/usb_device.o ${OBJECTDIR}/usb_function_generic.o ${OBJECTDIR}/adc.o ${OBJECTDIR}/main.o ${OBJECTDIR}/posicion.o ${OBJECTDIR}/sensores.o


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
${OBJECTDIR}/TCPIP\ Stack/Announce.o: TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Announce.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Announce.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Announce.o.d" -o "${OBJECTDIR}/TCPIP Stack/Announce.o" "TCPIP Stack/Announce.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ARCFOUR.o: TCPIP\ Stack/ARCFOUR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ARCFOUR.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ARCFOUR.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ARCFOUR.o.d" -o "${OBJECTDIR}/TCPIP Stack/ARCFOUR.o" "TCPIP Stack/ARCFOUR.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ARP.o: TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ARP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ARP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ARP.o.d" -o "${OBJECTDIR}/TCPIP Stack/ARP.o" "TCPIP Stack/ARP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/AutoIP.o: TCPIP\ Stack/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/AutoIP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/AutoIP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/AutoIP.o.d" -o "${OBJECTDIR}/TCPIP Stack/AutoIP.o" "TCPIP Stack/AutoIP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/BerkeleyAPI.o: TCPIP\ Stack/BerkeleyAPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/BerkeleyAPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/BerkeleyAPI.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/BerkeleyAPI.o.d" -o "${OBJECTDIR}/TCPIP Stack/BerkeleyAPI.o" "TCPIP Stack/BerkeleyAPI.c"  
	
${OBJECTDIR}/TCPIP\ Stack/BigInt.o: TCPIP\ Stack/BigInt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/BigInt.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/BigInt.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/BigInt.o.d" -o "${OBJECTDIR}/TCPIP Stack/BigInt.o" "TCPIP Stack/BigInt.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Delay.o: TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Delay.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Delay.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Delay.o.d" -o "${OBJECTDIR}/TCPIP Stack/Delay.o" "TCPIP Stack/Delay.c"  
	
${OBJECTDIR}/TCPIP\ Stack/DHCP.o: TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/DHCP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/DHCP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/DHCP.o.d" -o "${OBJECTDIR}/TCPIP Stack/DHCP.o" "TCPIP Stack/DHCP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/DHCPs.o: TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/DHCPs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/DHCPs.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/DHCPs.o.d" -o "${OBJECTDIR}/TCPIP Stack/DHCPs.o" "TCPIP Stack/DHCPs.c"  
	
${OBJECTDIR}/TCPIP\ Stack/DNS.o: TCPIP\ Stack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/DNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/DNS.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/DNS.o.d" -o "${OBJECTDIR}/TCPIP Stack/DNS.o" "TCPIP Stack/DNS.c"  
	
${OBJECTDIR}/TCPIP\ Stack/DNSs.o: TCPIP\ Stack/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/DNSs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/DNSs.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/DNSs.o.d" -o "${OBJECTDIR}/TCPIP Stack/DNSs.o" "TCPIP Stack/DNSs.c"  
	
${OBJECTDIR}/TCPIP\ Stack/DynDNS.o: TCPIP\ Stack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/DynDNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/DynDNS.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/DynDNS.o.d" -o "${OBJECTDIR}/TCPIP Stack/DynDNS.o" "TCPIP Stack/DynDNS.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ENC28J60.o: TCPIP\ Stack/ENC28J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ENC28J60.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ENC28J60.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ENC28J60.o.d" -o "${OBJECTDIR}/TCPIP Stack/ENC28J60.o" "TCPIP Stack/ENC28J60.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ENCX24J600.o: TCPIP\ Stack/ENCX24J600.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ENCX24J600.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ENCX24J600.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ENCX24J600.o.d" -o "${OBJECTDIR}/TCPIP Stack/ENCX24J600.o" "TCPIP Stack/ENCX24J600.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhyDP83640.o: TCPIP\ Stack/ETHPIC32ExtPhyDP83640.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhyDP83640.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhyDP83640.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhyDP83640.o.d" -o "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhyDP83640.o" "TCPIP Stack/ETHPIC32ExtPhyDP83640.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhySMSC8700.o: TCPIP\ Stack/ETHPIC32ExtPhySMSC8700.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhySMSC8700.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8700.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8700.o.d" -o "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8700.o" "TCPIP Stack/ETHPIC32ExtPhySMSC8700.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhySMSC8720.o: TCPIP\ Stack/ETHPIC32ExtPhySMSC8720.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhySMSC8720.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8720.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8720.o.d" -o "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8720.o" "TCPIP Stack/ETHPIC32ExtPhySMSC8720.c"  
	
${OBJECTDIR}/TCPIP\ Stack/FileSystem.o: TCPIP\ Stack/FileSystem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/FileSystem.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/FileSystem.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/FileSystem.o.d" -o "${OBJECTDIR}/TCPIP Stack/FileSystem.o" "TCPIP Stack/FileSystem.c"  
	
${OBJECTDIR}/TCPIP\ Stack/FTP.o: TCPIP\ Stack/FTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/FTP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/FTP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/FTP.o.d" -o "${OBJECTDIR}/TCPIP Stack/FTP.o" "TCPIP Stack/FTP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Hashes.o: TCPIP\ Stack/Hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Hashes.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Hashes.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Hashes.o.d" -o "${OBJECTDIR}/TCPIP Stack/Hashes.o" "TCPIP Stack/Hashes.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Helpers.o: TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Helpers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Helpers.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Helpers.o.d" -o "${OBJECTDIR}/TCPIP Stack/Helpers.o" "TCPIP Stack/Helpers.c"  
	
${OBJECTDIR}/TCPIP\ Stack/HTTP2.o: TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/HTTP2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/HTTP2.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/HTTP2.o.d" -o "${OBJECTDIR}/TCPIP Stack/HTTP2.o" "TCPIP Stack/HTTP2.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ICMP.o: TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ICMP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ICMP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ICMP.o.d" -o "${OBJECTDIR}/TCPIP Stack/ICMP.o" "TCPIP Stack/ICMP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/IP.o: TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/IP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/IP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/IP.o.d" -o "${OBJECTDIR}/TCPIP Stack/IP.o" "TCPIP Stack/IP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/LCDBlocking.o: TCPIP\ Stack/LCDBlocking.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/LCDBlocking.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/LCDBlocking.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/LCDBlocking.o.d" -o "${OBJECTDIR}/TCPIP Stack/LCDBlocking.o" "TCPIP Stack/LCDBlocking.c"  
	
${OBJECTDIR}/TCPIP\ Stack/MPFS2.o: TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/MPFS2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/MPFS2.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/MPFS2.o.d" -o "${OBJECTDIR}/TCPIP Stack/MPFS2.o" "TCPIP Stack/MPFS2.c"  
	
${OBJECTDIR}/TCPIP\ Stack/NBNS.o: TCPIP\ Stack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/NBNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/NBNS.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/NBNS.o.d" -o "${OBJECTDIR}/TCPIP Stack/NBNS.o" "TCPIP Stack/NBNS.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Random.o: TCPIP\ Stack/Random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Random.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Random.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Random.o.d" -o "${OBJECTDIR}/TCPIP Stack/Random.o" "TCPIP Stack/Random.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Reboot.o: TCPIP\ Stack/Reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Reboot.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Reboot.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Reboot.o.d" -o "${OBJECTDIR}/TCPIP Stack/Reboot.o" "TCPIP Stack/Reboot.c"  
	
${OBJECTDIR}/TCPIP\ Stack/RSA.o: TCPIP\ Stack/RSA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/RSA.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/RSA.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/RSA.o.d" -o "${OBJECTDIR}/TCPIP Stack/RSA.o" "TCPIP Stack/RSA.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SMTP.o: TCPIP\ Stack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SMTP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SMTP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SMTP.o.d" -o "${OBJECTDIR}/TCPIP Stack/SMTP.o" "TCPIP Stack/SMTP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SNMP.o: TCPIP\ Stack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SNMP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SNMP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SNMP.o.d" -o "${OBJECTDIR}/TCPIP Stack/SNMP.o" "TCPIP Stack/SNMP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SNMPv3.o: TCPIP\ Stack/SNMPv3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SNMPv3.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SNMPv3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SNMPv3.o.d" -o "${OBJECTDIR}/TCPIP Stack/SNMPv3.o" "TCPIP Stack/SNMPv3.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SNMPv3USM.o: TCPIP\ Stack/SNMPv3USM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SNMPv3USM.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SNMPv3USM.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SNMPv3USM.o.d" -o "${OBJECTDIR}/TCPIP Stack/SNMPv3USM.o" "TCPIP Stack/SNMPv3USM.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SNTP.o: TCPIP\ Stack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SNTP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SNTP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SNTP.o.d" -o "${OBJECTDIR}/TCPIP Stack/SNTP.o" "TCPIP Stack/SNTP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SPIEEPROM.o: TCPIP\ Stack/SPIEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SPIEEPROM.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SPIEEPROM.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SPIEEPROM.o.d" -o "${OBJECTDIR}/TCPIP Stack/SPIEEPROM.o" "TCPIP Stack/SPIEEPROM.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SPIFlash.o: TCPIP\ Stack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SPIFlash.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SPIFlash.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SPIFlash.o.d" -o "${OBJECTDIR}/TCPIP Stack/SPIFlash.o" "TCPIP Stack/SPIFlash.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SPIRAM.o: TCPIP\ Stack/SPIRAM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SPIRAM.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SPIRAM.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SPIRAM.o.d" -o "${OBJECTDIR}/TCPIP Stack/SPIRAM.o" "TCPIP Stack/SPIRAM.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SSL.o: TCPIP\ Stack/SSL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SSL.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SSL.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SSL.o.d" -o "${OBJECTDIR}/TCPIP Stack/SSL.o" "TCPIP Stack/SSL.c"  
	
${OBJECTDIR}/TCPIP\ Stack/StackTsk.o: TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/StackTsk.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/StackTsk.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/StackTsk.o.d" -o "${OBJECTDIR}/TCPIP Stack/StackTsk.o" "TCPIP Stack/StackTsk.c"  
	
${OBJECTDIR}/TCPIP\ Stack/TCP.o: TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/TCP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/TCP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/TCP.o.d" -o "${OBJECTDIR}/TCPIP Stack/TCP.o" "TCPIP Stack/TCP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/TCPPerformanceTest.o: TCPIP\ Stack/TCPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/TCPPerformanceTest.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/TCPPerformanceTest.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/TCPPerformanceTest.o.d" -o "${OBJECTDIR}/TCPIP Stack/TCPPerformanceTest.o" "TCPIP Stack/TCPPerformanceTest.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Telnet.o: TCPIP\ Stack/Telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Telnet.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Telnet.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Telnet.o.d" -o "${OBJECTDIR}/TCPIP Stack/Telnet.o" "TCPIP Stack/Telnet.c"  
	
${OBJECTDIR}/TCPIP\ Stack/TFTPc.o: TCPIP\ Stack/TFTPc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/TFTPc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/TFTPc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/TFTPc.o.d" -o "${OBJECTDIR}/TCPIP Stack/TFTPc.o" "TCPIP Stack/TFTPc.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Tick.o: TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Tick.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Tick.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Tick.o.d" -o "${OBJECTDIR}/TCPIP Stack/Tick.o" "TCPIP Stack/Tick.c"  
	
${OBJECTDIR}/TCPIP\ Stack/UART.o: TCPIP\ Stack/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/UART.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/UART.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/UART.o.d" -o "${OBJECTDIR}/TCPIP Stack/UART.o" "TCPIP Stack/UART.c"  
	
${OBJECTDIR}/TCPIP\ Stack/UART2TCPBridge.o: TCPIP\ Stack/UART2TCPBridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/UART2TCPBridge.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/UART2TCPBridge.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/UART2TCPBridge.o.d" -o "${OBJECTDIR}/TCPIP Stack/UART2TCPBridge.o" "TCPIP Stack/UART2TCPBridge.c"  
	
${OBJECTDIR}/TCPIP\ Stack/UDP.o: TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/UDP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/UDP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/UDP.o.d" -o "${OBJECTDIR}/TCPIP Stack/UDP.o" "TCPIP Stack/UDP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/UDPPerformanceTest.o: TCPIP\ Stack/UDPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/UDPPerformanceTest.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/UDPPerformanceTest.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/UDPPerformanceTest.o.d" -o "${OBJECTDIR}/TCPIP Stack/UDPPerformanceTest.o" "TCPIP Stack/UDPPerformanceTest.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ZeroconfHelper.o: TCPIP\ Stack/ZeroconfHelper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ZeroconfHelper.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ZeroconfHelper.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ZeroconfHelper.o.d" -o "${OBJECTDIR}/TCPIP Stack/ZeroconfHelper.o" "TCPIP Stack/ZeroconfHelper.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ZeroconfLinkLocal.o: TCPIP\ Stack/ZeroconfLinkLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ZeroconfLinkLocal.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ZeroconfLinkLocal.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ZeroconfLinkLocal.o.d" -o "${OBJECTDIR}/TCPIP Stack/ZeroconfLinkLocal.o" "TCPIP Stack/ZeroconfLinkLocal.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ZeroconfMulticastDNS.o: TCPIP\ Stack/ZeroconfMulticastDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ZeroconfMulticastDNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ZeroconfMulticastDNS.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ZeroconfMulticastDNS.o.d" -o "${OBJECTDIR}/TCPIP Stack/ZeroconfMulticastDNS.o" "TCPIP Stack/ZeroconfMulticastDNS.c"  
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c  
	
${OBJECTDIR}/usb_device.o: usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_device.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_device.o.d" -o ${OBJECTDIR}/usb_device.o usb_device.c  
	
${OBJECTDIR}/usb_function_generic.o: usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_function_generic.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_function_generic.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_function_generic.o.d" -o ${OBJECTDIR}/usb_function_generic.o usb_function_generic.c  
	
${OBJECTDIR}/adc.o: adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/adc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/adc.o.d" -o ${OBJECTDIR}/adc.o adc.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/posicion.o: posicion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/posicion.o.d 
	@${FIXDEPS} "${OBJECTDIR}/posicion.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/posicion.o.d" -o ${OBJECTDIR}/posicion.o posicion.c  
	
${OBJECTDIR}/sensores.o: sensores.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensores.o.d 
	@${FIXDEPS} "${OBJECTDIR}/sensores.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensores.o.d" -o ${OBJECTDIR}/sensores.o sensores.c  
	
else
${OBJECTDIR}/TCPIP\ Stack/Announce.o: TCPIP\ Stack/Announce.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Announce.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Announce.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Announce.o.d" -o "${OBJECTDIR}/TCPIP Stack/Announce.o" "TCPIP Stack/Announce.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ARCFOUR.o: TCPIP\ Stack/ARCFOUR.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ARCFOUR.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ARCFOUR.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ARCFOUR.o.d" -o "${OBJECTDIR}/TCPIP Stack/ARCFOUR.o" "TCPIP Stack/ARCFOUR.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ARP.o: TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ARP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ARP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ARP.o.d" -o "${OBJECTDIR}/TCPIP Stack/ARP.o" "TCPIP Stack/ARP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/AutoIP.o: TCPIP\ Stack/AutoIP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/AutoIP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/AutoIP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/AutoIP.o.d" -o "${OBJECTDIR}/TCPIP Stack/AutoIP.o" "TCPIP Stack/AutoIP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/BerkeleyAPI.o: TCPIP\ Stack/BerkeleyAPI.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/BerkeleyAPI.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/BerkeleyAPI.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/BerkeleyAPI.o.d" -o "${OBJECTDIR}/TCPIP Stack/BerkeleyAPI.o" "TCPIP Stack/BerkeleyAPI.c"  
	
${OBJECTDIR}/TCPIP\ Stack/BigInt.o: TCPIP\ Stack/BigInt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/BigInt.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/BigInt.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/BigInt.o.d" -o "${OBJECTDIR}/TCPIP Stack/BigInt.o" "TCPIP Stack/BigInt.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Delay.o: TCPIP\ Stack/Delay.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Delay.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Delay.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Delay.o.d" -o "${OBJECTDIR}/TCPIP Stack/Delay.o" "TCPIP Stack/Delay.c"  
	
${OBJECTDIR}/TCPIP\ Stack/DHCP.o: TCPIP\ Stack/DHCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/DHCP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/DHCP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/DHCP.o.d" -o "${OBJECTDIR}/TCPIP Stack/DHCP.o" "TCPIP Stack/DHCP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/DHCPs.o: TCPIP\ Stack/DHCPs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/DHCPs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/DHCPs.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/DHCPs.o.d" -o "${OBJECTDIR}/TCPIP Stack/DHCPs.o" "TCPIP Stack/DHCPs.c"  
	
${OBJECTDIR}/TCPIP\ Stack/DNS.o: TCPIP\ Stack/DNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/DNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/DNS.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/DNS.o.d" -o "${OBJECTDIR}/TCPIP Stack/DNS.o" "TCPIP Stack/DNS.c"  
	
${OBJECTDIR}/TCPIP\ Stack/DNSs.o: TCPIP\ Stack/DNSs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/DNSs.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/DNSs.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/DNSs.o.d" -o "${OBJECTDIR}/TCPIP Stack/DNSs.o" "TCPIP Stack/DNSs.c"  
	
${OBJECTDIR}/TCPIP\ Stack/DynDNS.o: TCPIP\ Stack/DynDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/DynDNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/DynDNS.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/DynDNS.o.d" -o "${OBJECTDIR}/TCPIP Stack/DynDNS.o" "TCPIP Stack/DynDNS.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ENC28J60.o: TCPIP\ Stack/ENC28J60.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ENC28J60.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ENC28J60.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ENC28J60.o.d" -o "${OBJECTDIR}/TCPIP Stack/ENC28J60.o" "TCPIP Stack/ENC28J60.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ENCX24J600.o: TCPIP\ Stack/ENCX24J600.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ENCX24J600.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ENCX24J600.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ENCX24J600.o.d" -o "${OBJECTDIR}/TCPIP Stack/ENCX24J600.o" "TCPIP Stack/ENCX24J600.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhyDP83640.o: TCPIP\ Stack/ETHPIC32ExtPhyDP83640.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhyDP83640.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhyDP83640.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhyDP83640.o.d" -o "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhyDP83640.o" "TCPIP Stack/ETHPIC32ExtPhyDP83640.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhySMSC8700.o: TCPIP\ Stack/ETHPIC32ExtPhySMSC8700.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhySMSC8700.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8700.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8700.o.d" -o "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8700.o" "TCPIP Stack/ETHPIC32ExtPhySMSC8700.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhySMSC8720.o: TCPIP\ Stack/ETHPIC32ExtPhySMSC8720.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ETHPIC32ExtPhySMSC8720.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8720.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8720.o.d" -o "${OBJECTDIR}/TCPIP Stack/ETHPIC32ExtPhySMSC8720.o" "TCPIP Stack/ETHPIC32ExtPhySMSC8720.c"  
	
${OBJECTDIR}/TCPIP\ Stack/FileSystem.o: TCPIP\ Stack/FileSystem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/FileSystem.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/FileSystem.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/FileSystem.o.d" -o "${OBJECTDIR}/TCPIP Stack/FileSystem.o" "TCPIP Stack/FileSystem.c"  
	
${OBJECTDIR}/TCPIP\ Stack/FTP.o: TCPIP\ Stack/FTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/FTP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/FTP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/FTP.o.d" -o "${OBJECTDIR}/TCPIP Stack/FTP.o" "TCPIP Stack/FTP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Hashes.o: TCPIP\ Stack/Hashes.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Hashes.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Hashes.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Hashes.o.d" -o "${OBJECTDIR}/TCPIP Stack/Hashes.o" "TCPIP Stack/Hashes.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Helpers.o: TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Helpers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Helpers.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Helpers.o.d" -o "${OBJECTDIR}/TCPIP Stack/Helpers.o" "TCPIP Stack/Helpers.c"  
	
${OBJECTDIR}/TCPIP\ Stack/HTTP2.o: TCPIP\ Stack/HTTP2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/HTTP2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/HTTP2.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/HTTP2.o.d" -o "${OBJECTDIR}/TCPIP Stack/HTTP2.o" "TCPIP Stack/HTTP2.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ICMP.o: TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ICMP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ICMP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ICMP.o.d" -o "${OBJECTDIR}/TCPIP Stack/ICMP.o" "TCPIP Stack/ICMP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/IP.o: TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/IP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/IP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/IP.o.d" -o "${OBJECTDIR}/TCPIP Stack/IP.o" "TCPIP Stack/IP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/LCDBlocking.o: TCPIP\ Stack/LCDBlocking.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/LCDBlocking.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/LCDBlocking.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/LCDBlocking.o.d" -o "${OBJECTDIR}/TCPIP Stack/LCDBlocking.o" "TCPIP Stack/LCDBlocking.c"  
	
${OBJECTDIR}/TCPIP\ Stack/MPFS2.o: TCPIP\ Stack/MPFS2.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/MPFS2.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/MPFS2.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/MPFS2.o.d" -o "${OBJECTDIR}/TCPIP Stack/MPFS2.o" "TCPIP Stack/MPFS2.c"  
	
${OBJECTDIR}/TCPIP\ Stack/NBNS.o: TCPIP\ Stack/NBNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/NBNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/NBNS.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/NBNS.o.d" -o "${OBJECTDIR}/TCPIP Stack/NBNS.o" "TCPIP Stack/NBNS.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Random.o: TCPIP\ Stack/Random.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Random.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Random.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Random.o.d" -o "${OBJECTDIR}/TCPIP Stack/Random.o" "TCPIP Stack/Random.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Reboot.o: TCPIP\ Stack/Reboot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Reboot.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Reboot.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Reboot.o.d" -o "${OBJECTDIR}/TCPIP Stack/Reboot.o" "TCPIP Stack/Reboot.c"  
	
${OBJECTDIR}/TCPIP\ Stack/RSA.o: TCPIP\ Stack/RSA.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/RSA.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/RSA.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/RSA.o.d" -o "${OBJECTDIR}/TCPIP Stack/RSA.o" "TCPIP Stack/RSA.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SMTP.o: TCPIP\ Stack/SMTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SMTP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SMTP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SMTP.o.d" -o "${OBJECTDIR}/TCPIP Stack/SMTP.o" "TCPIP Stack/SMTP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SNMP.o: TCPIP\ Stack/SNMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SNMP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SNMP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SNMP.o.d" -o "${OBJECTDIR}/TCPIP Stack/SNMP.o" "TCPIP Stack/SNMP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SNMPv3.o: TCPIP\ Stack/SNMPv3.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SNMPv3.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SNMPv3.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SNMPv3.o.d" -o "${OBJECTDIR}/TCPIP Stack/SNMPv3.o" "TCPIP Stack/SNMPv3.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SNMPv3USM.o: TCPIP\ Stack/SNMPv3USM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SNMPv3USM.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SNMPv3USM.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SNMPv3USM.o.d" -o "${OBJECTDIR}/TCPIP Stack/SNMPv3USM.o" "TCPIP Stack/SNMPv3USM.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SNTP.o: TCPIP\ Stack/SNTP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SNTP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SNTP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SNTP.o.d" -o "${OBJECTDIR}/TCPIP Stack/SNTP.o" "TCPIP Stack/SNTP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SPIEEPROM.o: TCPIP\ Stack/SPIEEPROM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SPIEEPROM.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SPIEEPROM.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SPIEEPROM.o.d" -o "${OBJECTDIR}/TCPIP Stack/SPIEEPROM.o" "TCPIP Stack/SPIEEPROM.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SPIFlash.o: TCPIP\ Stack/SPIFlash.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SPIFlash.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SPIFlash.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SPIFlash.o.d" -o "${OBJECTDIR}/TCPIP Stack/SPIFlash.o" "TCPIP Stack/SPIFlash.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SPIRAM.o: TCPIP\ Stack/SPIRAM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SPIRAM.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SPIRAM.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SPIRAM.o.d" -o "${OBJECTDIR}/TCPIP Stack/SPIRAM.o" "TCPIP Stack/SPIRAM.c"  
	
${OBJECTDIR}/TCPIP\ Stack/SSL.o: TCPIP\ Stack/SSL.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/SSL.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/SSL.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/SSL.o.d" -o "${OBJECTDIR}/TCPIP Stack/SSL.o" "TCPIP Stack/SSL.c"  
	
${OBJECTDIR}/TCPIP\ Stack/StackTsk.o: TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/StackTsk.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/StackTsk.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/StackTsk.o.d" -o "${OBJECTDIR}/TCPIP Stack/StackTsk.o" "TCPIP Stack/StackTsk.c"  
	
${OBJECTDIR}/TCPIP\ Stack/TCP.o: TCPIP\ Stack/TCP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/TCP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/TCP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/TCP.o.d" -o "${OBJECTDIR}/TCPIP Stack/TCP.o" "TCPIP Stack/TCP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/TCPPerformanceTest.o: TCPIP\ Stack/TCPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/TCPPerformanceTest.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/TCPPerformanceTest.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/TCPPerformanceTest.o.d" -o "${OBJECTDIR}/TCPIP Stack/TCPPerformanceTest.o" "TCPIP Stack/TCPPerformanceTest.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Telnet.o: TCPIP\ Stack/Telnet.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Telnet.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Telnet.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Telnet.o.d" -o "${OBJECTDIR}/TCPIP Stack/Telnet.o" "TCPIP Stack/Telnet.c"  
	
${OBJECTDIR}/TCPIP\ Stack/TFTPc.o: TCPIP\ Stack/TFTPc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/TFTPc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/TFTPc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/TFTPc.o.d" -o "${OBJECTDIR}/TCPIP Stack/TFTPc.o" "TCPIP Stack/TFTPc.c"  
	
${OBJECTDIR}/TCPIP\ Stack/Tick.o: TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/Tick.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/Tick.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/Tick.o.d" -o "${OBJECTDIR}/TCPIP Stack/Tick.o" "TCPIP Stack/Tick.c"  
	
${OBJECTDIR}/TCPIP\ Stack/UART.o: TCPIP\ Stack/UART.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/UART.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/UART.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/UART.o.d" -o "${OBJECTDIR}/TCPIP Stack/UART.o" "TCPIP Stack/UART.c"  
	
${OBJECTDIR}/TCPIP\ Stack/UART2TCPBridge.o: TCPIP\ Stack/UART2TCPBridge.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/UART2TCPBridge.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/UART2TCPBridge.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/UART2TCPBridge.o.d" -o "${OBJECTDIR}/TCPIP Stack/UART2TCPBridge.o" "TCPIP Stack/UART2TCPBridge.c"  
	
${OBJECTDIR}/TCPIP\ Stack/UDP.o: TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/UDP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/UDP.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/UDP.o.d" -o "${OBJECTDIR}/TCPIP Stack/UDP.o" "TCPIP Stack/UDP.c"  
	
${OBJECTDIR}/TCPIP\ Stack/UDPPerformanceTest.o: TCPIP\ Stack/UDPPerformanceTest.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/UDPPerformanceTest.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/UDPPerformanceTest.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/UDPPerformanceTest.o.d" -o "${OBJECTDIR}/TCPIP Stack/UDPPerformanceTest.o" "TCPIP Stack/UDPPerformanceTest.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ZeroconfHelper.o: TCPIP\ Stack/ZeroconfHelper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ZeroconfHelper.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ZeroconfHelper.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ZeroconfHelper.o.d" -o "${OBJECTDIR}/TCPIP Stack/ZeroconfHelper.o" "TCPIP Stack/ZeroconfHelper.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ZeroconfLinkLocal.o: TCPIP\ Stack/ZeroconfLinkLocal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ZeroconfLinkLocal.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ZeroconfLinkLocal.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ZeroconfLinkLocal.o.d" -o "${OBJECTDIR}/TCPIP Stack/ZeroconfLinkLocal.o" "TCPIP Stack/ZeroconfLinkLocal.c"  
	
${OBJECTDIR}/TCPIP\ Stack/ZeroconfMulticastDNS.o: TCPIP\ Stack/ZeroconfMulticastDNS.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/TCPIP\ Stack 
	@${RM} ${OBJECTDIR}/TCPIP\ Stack/ZeroconfMulticastDNS.o.d 
	@${FIXDEPS} "${OBJECTDIR}/TCPIP Stack/ZeroconfMulticastDNS.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/TCPIP Stack/ZeroconfMulticastDNS.o.d" -o "${OBJECTDIR}/TCPIP Stack/ZeroconfMulticastDNS.o" "TCPIP Stack/ZeroconfMulticastDNS.c"  
	
${OBJECTDIR}/usb_descriptors.o: usb_descriptors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_descriptors.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_descriptors.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_descriptors.o.d" -o ${OBJECTDIR}/usb_descriptors.o usb_descriptors.c  
	
${OBJECTDIR}/usb_device.o: usb_device.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_device.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_device.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_device.o.d" -o ${OBJECTDIR}/usb_device.o usb_device.c  
	
${OBJECTDIR}/usb_function_generic.o: usb_function_generic.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/usb_function_generic.o.d 
	@${FIXDEPS} "${OBJECTDIR}/usb_function_generic.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/usb_function_generic.o.d" -o ${OBJECTDIR}/usb_function_generic.o usb_function_generic.c  
	
${OBJECTDIR}/adc.o: adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/adc.o.d 
	@${FIXDEPS} "${OBJECTDIR}/adc.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/adc.o.d" -o ${OBJECTDIR}/adc.o adc.c  
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c  
	
${OBJECTDIR}/posicion.o: posicion.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/posicion.o.d 
	@${FIXDEPS} "${OBJECTDIR}/posicion.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/posicion.o.d" -o ${OBJECTDIR}/posicion.o posicion.c  
	
${OBJECTDIR}/sensores.o: sensores.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/sensores.o.d 
	@${FIXDEPS} "${OBJECTDIR}/sensores.o.d" $(SILENT) -c ${MP_CC} $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/sensores.o.d" -o ${OBJECTDIR}/sensores.o sensores.c  
	
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
	${MP_CC_DIR}/pic32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/Firmware.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  
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
