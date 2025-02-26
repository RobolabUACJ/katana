/*********************************************************************
*
*     Microchip TCP/IP Stack Demo Application Configuration Header
*
*********************************************************************/

#ifndef __TCPIPCONFIG_H
#define __TCPIPCONFIG_H

#include "GenericTypeDefs.h"
#include "../Compiler.h"
#define GENERATED_BY_TCPIPCONFIG "Version 1.0.3383.23374"

// =======================================================================
//   Application Options
// =======================================================================

/* Application Level Module Selection
 *   Uncomment or comment the following lines to enable or
 *   disabled the following high-level application modules.
 */
//#define STACK_USE_AUTO_IP               // Dynamic link-layer IP address automatic configuration protocol
//#define STACK_USE_DHCP_CLIENT			// Dynamic Host Configuration Protocol client for obtaining IP address and other parameters
//#define STACK_USE_DHCP_SERVER			// Single host DHCP server
//#define STACK_USE_GENERIC_TCP_CLIENT_EXAMPLE	// HTTP Client example in GenericTCPClient.c
#define STACK_USE_GENERIC_TCP_SERVER_EXAMPLE	// ToUpper server example in GenericTCPServer.c

#define MPFS_RESERVE_BLOCK				(137ul)

/* MPFS File Handles
 *   Maximum number of simultaneously open MPFS2 files.
 *   For MPFS Classic, this has no effect.
 */
#define MAX_MPFS_HANDLES				(7ul)


// =======================================================================
//   Network Addressing Options
// =======================================================================

/* Default Network Configuration
 *   These settings are only used if data is not found in EEPROM.
 *   To clear EEPROM, hold BUTTON0, reset the board, and continue
 *   holding until the LEDs flash.  Release, and reset again.
 */
#define MY_DEFAULT_HOST_NAME			"MCHPBOARD"

//MAC Address dada de alta en la red robonet0
#define MY_DEFAULT_MAC_BYTE1            (0x00)	// Use the default of 00-04-A3-00-00-00
#define MY_DEFAULT_MAC_BYTE2            (0x04)	// if using an ENCX24J600, MRF24WB0M, or
#define MY_DEFAULT_MAC_BYTE3            (0xA3)	// PIC32MX6XX/7XX internal Ethernet 
#define MY_DEFAULT_MAC_BYTE4            (0x00)	// controller and wish to use the 
#define MY_DEFAULT_MAC_BYTE5            (0x00)	// internal factory programmed MAC
#define MY_DEFAULT_MAC_BYTE6            (0x00)	// address instead.

//IP  asignada al cerebot:
#define MY_DEFAULT_IP_ADDR_BYTE1        (192ul)
#define MY_DEFAULT_IP_ADDR_BYTE2        (0ul)
#define MY_DEFAULT_IP_ADDR_BYTE3        (0ul)
#define MY_DEFAULT_IP_ADDR_BYTE4        (63ul)

#define MY_DEFAULT_MASK_BYTE1           (255ul)
#define MY_DEFAULT_MASK_BYTE2           (255ul)
#define MY_DEFAULT_MASK_BYTE3           (0ul)
#define MY_DEFAULT_MASK_BYTE4           (0ul)

#define MY_DEFAULT_GATE_BYTE1           (169ul)
#define MY_DEFAULT_GATE_BYTE2           (254ul)
#define MY_DEFAULT_GATE_BYTE3           (1ul)
#define MY_DEFAULT_GATE_BYTE4           (1ul)

#define MY_DEFAULT_PRIMARY_DNS_BYTE1	(169ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE2	(254ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE3	(1ul)
#define MY_DEFAULT_PRIMARY_DNS_BYTE4	(1ul)

#define MY_DEFAULT_SECONDARY_DNS_BYTE1	(0ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE2	(0ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE3	(0ul)
#define MY_DEFAULT_SECONDARY_DNS_BYTE4	(0ul)

// =======================================================================
//   PIC32MX7XX/6XX MAC Layer Options
//   If not using a PIC32MX7XX/6XX device, ignore this section.
// =======================================================================
#define	ETH_CFG_LINK			0		// set to 1 if you need to config the link to specific following parameters
										// otherwise the default connection will be attempted
										// depending on the selected PHY
	#define	ETH_CFG_AUTO		1		// use auto negotiation
	#define	ETH_CFG_10			1		// use/advertise 10 Mbps capability
	#define	ETH_CFG_100			1		// use/advertise 100 Mbps capability
	#define	ETH_CFG_HDUPLEX		1		// use/advertise half duplex capability
	#define	ETH_CFG_FDUPLEX		1		// use/advertise full duplex capability
	#define	ETH_CFG_AUTO_MDIX	1		// use/advertise auto MDIX capability
	#define	ETH_CFG_SWAP_MDIX	1		// use swapped MDIX. else normal MDIX

#define EMAC_TX_DESCRIPTORS		2		// number of the TX descriptors to be created
#define EMAC_RX_DESCRIPTORS		8		// number of the RX descriptors and RX buffers to be created

#define	EMAC_RX_BUFF_SIZE		1536	// size of a RX buffer. should be multiple of 16
										// this is the size of all receive buffers processed by the ETHC
										// The size should be enough to accomodate any network received packet
										// If the packets are larger, they will have to take multiple RX buffers
										// The current implementation does not handle this situation right now and the packet is discarded.
// =======================================================================
//   Transport Layer Options
// =======================================================================

/* Transport Layer Configuration
 *   The following low level modules are automatically enabled
 *   based on module selections above.  If your custom module
 *   requires them otherwise, enable them here.
 */
//#define STACK_USE_TCP
//#define STACK_USE_UDP

/* Client Mode Configuration
 *   Uncomment following line if this stack will be used in CLIENT
 *   mode.  In CLIENT mode, some functions specific to client operation
 *   are enabled.
 */
#define STACK_CLIENT_MODE

/* TCP Socket Memory Allocation
 *   TCP needs memory to buffer incoming and outgoing data.  The
 *   amount and medium of storage can be allocated on a per-socket
 *   basis using the example below as a guide.
 */
	// Allocate how much total RAM (in bytes) you want to allocate
	// for use by your TCP TCBs, RX FIFOs, and TX FIFOs.
	#define TCP_ETH_RAM_SIZE					(3900ul)
	#define TCP_PIC_RAM_SIZE					(0ul)
	#define TCP_SPI_RAM_SIZE					(0ul)
	#define TCP_SPI_RAM_BASE_ADDRESS			(0x00)

	// Define names of socket types
	#define TCP_SOCKET_TYPES
		#define TCP_PURPOSE_GENERIC_TCP_CLIENT 0
		#define TCP_PURPOSE_GENERIC_TCP_SERVER 1
		#define TCP_PURPOSE_TELNET 2
		#define TCP_PURPOSE_FTP_COMMAND 3
		#define TCP_PURPOSE_FTP_DATA 4
		#define TCP_PURPOSE_TCP_PERFORMANCE_TX 5
		#define TCP_PURPOSE_TCP_PERFORMANCE_RX 6
		#define TCP_PURPOSE_UART_2_TCP_BRIDGE 7
		#define TCP_PURPOSE_HTTP_SERVER 8
		#define TCP_PURPOSE_DEFAULT 9
		#define TCP_PURPOSE_BERKELEY_SERVER 10
		#define TCP_PURPOSE_BERKELEY_CLIENT 11
	#define END_OF_TCP_SOCKET_TYPES

	#if defined(__TCP_C)
		// Define what types of sockets are needed, how many of
		// each to include, where their TCB, TX FIFO, and RX FIFO
		// should be stored, and how big the RX and TX FIFOs should
		// be.  Making this initializer bigger or smaller defines
		// how many total TCP sockets are available.
		//
		// Each socket requires up to 56 bytes of PIC RAM and
		// 48+(TX FIFO size)+(RX FIFO size) bytes of TCP_*_RAM each.
		//
		// Note: The RX FIFO must be at least 1 byte in order to
		// receive SYN and FIN messages required by TCP.  The TX
		// FIFO can be zero if desired.
		#define TCP_CONFIGURATION
		ROM struct
		{
			BYTE vSocketPurpose;
			BYTE vMemoryMedium;
			WORD wTXBufferSize;
			WORD wRXBufferSize;
		} TCPSocketInitializer[] =
		{
			{TCP_PURPOSE_GENERIC_TCP_SERVER, TCP_ETH_RAM, 30, 30},
                        {TCP_PURPOSE_GENERIC_TCP_SERVER, TCP_ETH_RAM, 30, 30},
		};
		#define END_OF_TCP_CONFIGURATION
	#endif

/* UDP Socket Configuration
 *   Define the maximum number of available UDP Sockets, and whether
 *   or not to include a checksum on packets being transmitted.
 */
#define MAX_UDP_SOCKETS     (8u)
#define UDP_USE_TX_CHECKSUM		// This slows UDP TX performance by nearly 50%, except when using the ENCX24J600 or PIC32MX6XX/7XX, which have a super fast DMA and incurs virtually no speed pentalty.


/* Berkeley API Sockets Configuration
 *   Note that each Berkeley socket internally uses one TCP or UDP socket
 *   defined by MAX_UDP_SOCKETS and the TCPSocketInitializer[] array.
 *   Therefore, this number MUST be less than or equal to MAX_UDP_SOCKETS + the
 *   number of TCP sockets defined by the TCPSocketInitializer[] array
 *   (i.e. sizeof(TCPSocketInitializer)/sizeof(TCPSocketInitializer[0])).
 *   This define has no effect if STACK_USE_BERKELEY_API is not defined and
 *   Berkeley Sockets are disabled.  Set this value as low as your application
 *   requires to avoid waisting RAM.
 */
#define BSD_SOCKET_COUNT (5u)


// =======================================================================
//   Application-Specific Options
// =======================================================================

// -- HTTP2 Server options -----------------------------------------------

	// Maximum numbers of simultaneous HTTP connections allowed.
	// Each connection consumes 2 bytes of RAM and a TCP socket
	#define MAX_HTTP_CONNECTIONS	(2u)

	// Optional setting to use PIC RAM instead of Ethernet/Wi-Fi RAM for
	// storing HTTP Connection Context variables (HTTP_CONN structure for each 
	// HTTP connection).  Undefining this macro results in the Ethernet/Wi-Fi 
	// RAM being used (minimum PIC RAM usage, lower performance).  Defining 
	// this macro results in PIC RAM getting used (higher performance, but uses 
	// PIC RAM).  This option should not be enabled on PIC18 devices.  The 
	// performance increase of having this option defined is only apparent when 
	// the HTTP server is servicing multiple connections simultaneously.
	//#define HTTP_SAVE_CONTEXT_IN_PIC_RAM

	// Indicate what file to serve when no specific one is requested
	#define HTTP_DEFAULT_FILE		"index.htm"
	#define HTTPS_DEFAULT_FILE		"index.htm"
	#define HTTP_DEFAULT_LEN		(10u)		// For buffer overrun protection.
												// Set to longest length of above two strings.

	// Configure MPFS over HTTP updating
	// Comment this line to disable updating via HTTP
	#define HTTP_MPFS_UPLOAD		"mpfsupload"
	//#define HTTP_MPFS_UPLOAD_REQUIRES_AUTH	// Require password for MPFS uploads
		// Certain firewall and router combinations cause the MPFS2 Utility to fail
		// when uploading.  If this happens, comment out this definition.

	// Define which HTTP modules to use
	// If not using a specific module, comment it to save resources
	#define HTTP_USE_POST					// Enable POST support
	#define HTTP_USE_COOKIES				// Enable cookie support
	#define HTTP_USE_AUTHENTICATION			// Enable basic authentication support

	//#define HTTP_NO_AUTH_WITHOUT_SSL		// Uncomment to require SSL before requesting a password

    // Define the listening port for the HTTP server
  	#define HTTP_PORT               (80u)
	
    // Define the listening port for the HTTPS server (if STACK_USE_SSL_SERVER is enabled)
	#define HTTPS_PORT		(443u)
	
    // Define the maximum data length for reading cookie and GET/POST arguments (bytes)
	#define HTTP_MAX_DATA_LEN	(100u)
	
    // Define the minimum number of bytes free in the TX FIFO before executing callbacks
	#define HTTP_MIN_CALLBACK_FREE	(16u)

	#define STACK_USE_HTTP_APP_RECONFIG		// Use the AppConfig web page in the Demo App (~2.5kb ROM, ~0b RAM)
	#define STACK_USE_HTTP_MD5_DEMO			// Use the MD5 Demo web page (~5kb ROM, ~160b RAM)
	#define STACK_USE_HTTP_EMAIL_DEMO		// Use the e-mail demo web page

#endif