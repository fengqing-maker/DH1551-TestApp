
#ifndef _ADI_SOCKET_H_
#define _ADI_SOCKET_H_

#include "adi_typedef.h"

#ifdef   __cplusplus
extern "C" {
#endif

#define  ADI_FD_MAX    						(1024)  					 ///< max file descriptor
#define  ADI_INVALID_SOCKET   				(-1)						 ///< invalid  socket
#define  ADI_SOCKET_ERROR    				(-1)						 ///< socket error
#define  ADI_IOCPARM_MASK   				(0x1fff)    				 ///< parameter length, at most 13 bits.

#define  ADI_FIONBIO        				(0x667e)                          	 ///< set/clear nonblocking io.
#define  ADI_FIONREAD      					(0x467f)                         	 ///< get # bytes to read.

#define  ADI_IPPROTO_IP         			(0)             				///< Dummy protocol for TCP. 
#define  ADI_IPPROTO_HOPOPTS 				(0)    					///< IPv6 Hop-by-Hop options.
#define  ADI_IPPROTO_ICMP       			(1)   	   				///< Internet Control Message Protocol.
#define  ADI_IPPROTO_IGMP        			(2)						///< Internet Group Management Protocol. 
#define  ADI_IPPROTO_IPIP        			(4)						///< IPIP tunnels (older KA9Q tunnels use 94).
#define  ADI_IPPROTO_TCP         			(6)						///< Transmission Control Protocol. 
#define  ADI_IPPROTO_EGP         			(8)						///< Exterior Gateway Protocol.
#define  ADI_IPPROTO_PUP        			(12)						///< PUP protocol.
#define  ADI_IPPROTO_UDP        			(17)						///< User Datagram Protocol.
#define  ADI_IPPROTO_IDP         			(22)						///< XNS IDP protocol.
#define  ADI_IPPROTO_TP          			(29)						///< SO Transport Protocol Class 4. 
#define  ADI_IPPROTO_IPV6       			(41)						///< IPv6 header.
#define  ADI_IPPROTO_ROUTING     			(43)						///< IPv6 routing header.
#define  ADI_IPPROTO_FRAGMENT   			(44)						///< IPv6 fragmentation header. 
#define  ADI_IPPROTO_RSVP        			(46)						///< Reservation Protocol.
#define  ADI_IPPROTO_GRE          			(47)						///< General Routing Encapsulation.
#define  ADI_IPPROTO_ESP          			(50)						///< encapsulating security payload.
#define  ADI_IPPROTO_AH            			(51)		 				///< authentication header. 
#define  ADI_IPPROTO_ICMPV6                 (58)                                    ///< ICMPv6. 
#define  ADI_IPPROTO_NONE         			(59)						///< IPv6 no next header. 
#define  ADI_IPPROTO_DSTOPTS    			(60)						///< IPv6 destination options.
#define  ADI_IPPROTO_MTP 		 			(92)						///< Multicast Transport Protocol. 
#define  ADI_IPPROTO_ENCAP       			(98)						///< Encapsulation Header. 
#define  ADI_IPPROTO_PIM           			(103)					///< Protocol Independent Multicast.
#define  ADI_IPPROTO_COMP        			(108)					///< Compression Header Protocol. 
#define  ADI_IPPROTO_RAW          			(255)					///< Raw IP packets. 


#define ADI_BTPROTO_L2CAP					(0)
#define ADI_BTPROTO_HCI	    				(1)
#define ADI_BTPROTO_SCO	    				(2)
#define ADI_BTPROTO_RFCOMM					(3)
#define ADI_BTPROTO_BNEP					(4)
#define ADI_BTPROTO_CMTP					(5)
#define ADI_BTPROTO_HIDP					(6)
#define ADI_BTPROTO_AVDTP					(7)


#define  ADI_IPPORT_ECHO             	   	(7)						///< Echo service. 
#define  ADI_IPPORT_DISCARD       	   		(9)						///< Discard transmissions service. 
#define  ADI_IPPORT_SYSTAT               	(11)						///< System status service.
#define  ADI_IPPORT_DAYTIME             	(13)						///< Time of day service.
#define  ADI_IPPORT_NETSTAT             	(15)						///< Network status service.
#define  ADI_IPPORT_FTP                     (21)						///< File Transfer Protocol. 
#define  ADI_IPPORT_TELNET                	(23)						///< Telnet protocol.
#define  ADI_IPPORT_SMTP                   	(25)						///< Simple Mail Transfer Protocol.
#define  ADI_IPPORT_TIMESERVER        		(37)						///< Timeserver service. 
#define  ADI_IPPORT_NAMESERVER       		(42)						///< Domain Name Service. 
#define  ADI_IPPORT_WHOIS                 	(43)						///< Internet Whois service.
#define  ADI_IPPORT_MTP                     (57)						///< Media Transfer Protocol 
#define  ADI_IPPORT_TFTP                    (69)						///< Trivial File Transfer Protocol.
#define  ADI_IPPORT_RJE                     (77)						///< Remote Job Entry 
#define  ADI_IPPORT_FINGER                 	(79)						///< Finger service.
#define  ADI_IPPORT_TTYLINK                	(87)						///< TTY link
#define  ADI_IPPORT_SUPDUP                 	(95)						///< SUPDUP protocol. 
#define  ADI_IPPORT_EXECSERVER 	 			(512)					///< execd service.  
#define  ADI_IPPORT_LOGINSERVER   			(513)					///< rlogind service.  
#define  ADI_IPPORT_CMDSERVER 	 			(514) 					///< command service. 
#define  ADI_IPPORT_EFSSERVER 	 			(520) 					///< EFS service. 

#define  ADI_IPPORT_BIFFUDP  		 		(512)					///< BIFF UDP service. 
#define  ADI_IPPORT_WHOSERVER 	 			(513)					///< WHO service. 
#define  ADI_IPPORT_ROUTESERVER   			(520)					///< ROUTE service. 
#define  ADI_IPPORT_RESERVED 	 			(1024)  					///< Ports less than this value are reserved for privileged processes.
#define  ADI_IPPORT_USERRESERVED 			(5000)   					///< Ports greater this value are reserved for (non-privileged) servers. 

#define  ADI_TCP_NODELAY	 				(1)						///< Don't delay send to coalesce packets.  
#define  ADI_TCP_MAXSEG						(2)						///< Set maximum segment size.  
#define  ADI_TCP_CORK	 					(3)						///< Control sending of partial frames.  
#define  ADI_TCP_KEEPIDLE	 				(4)						///< Start keeplives after this period. 
#define  ADI_TCP_KEEPINTVL					(5)						///< Interval between keepalives. 
#define  ADI_TCP_KEEPCNT	 				(6)						///< Number of keepalives before death. 
#define  ADI_TCP_SYNCNT	 					(7)						///< Number of SYN retransmits. 
#define  ADI_TCP_LINGER2					(8)						///< Life time of orphaned FIN-WAIT-2 state. 
#define  ADI_TCP_DEFER_ACCEPT				(9)						///< Wake up listener only when data arrive. 
#define  ADI_TCP_WINDOW_CLAMP 				(10)						///< Bound advertised window. 
#define  ADI_TCP_INFO	 					(11)						///< Information about this connection. 
#define  ADI_TCP_QUICKACK	 				(12)						///< Bock/reenable quick ACKs.  

#define  ADI_TCPOPT_EOL						(0)						///< end of option list 
#define  ADI_TCPOPT_NOP						(1)						///< no option
#define  ADI_TCPOPT_MAXSEG					(2)						///< max segment
#define  ADI_TCPOPT_WINDOW					(3)						///< wodow 
#define  ADI_TCPOPT_SACK_PERMITTED			(4)						///< Experimental. 
#define  ADI_TCPOPT_SACK					(5)		   				///< Experimental. 
#define  ADI_TCPOPT_TIMESTAMP				(8)						///< time stamp option
						
#define  ADI_TCPOLEN_SACK_PERMITTED			(2)						///< Experimental. 
#define  ADI_TCPOLEN_WINDOW					(3)                                      ///< length of wodow
#define  ADI_TCPOLEN_MAXSEG					(4)						///< length of max segment
#define  ADI_TCPOLEN_TIMESTAMP				(10)						///< length of time stamp
#define  ADI_TCPOLEN_TSTAMP_APPA			(ADI_TCPOLEN_TIMESTAMP+2)	 ///< appendix A 
#define  ADI_TCPOPT_TSTAMP_HDR	\
    (ADI_TCPOPT_NOP<<24|ADI_TCPOPT_NOP<<16|ADI_TCPOPT_TIMESTAMP<<8|ADI_TCPOLEN_TIMESTAMP)

#define  ADI_TCP_MSS						(512)					///< packet subsect
#define  ADI_TCP_MAXWIN						(65535)					///< largest value for (unscaled) window. 
#define  ADI_TCP_MAX_WINSHIFT				(14)						///< maximum window shift.  

#define  ADI_TCPI_OPT_TIMESTAMPS 			(1)						///< time stamp 
#define  ADI_TCPI_OPT_SACK					(2)						///< Selective Acknowledgment
#define  ADI_TCPI_OPT_WSCALE				(4)						///< Window Scale Option
#define  ADI_TCPI_OPT_ECN					(8)						///< explicit congestion notification

#define  ADI_PF_UNSPEC           			(0)						///< Unspecified.
#define  ADI_PF_LOCAL						(1)	 					///< Local to host (pipes and file-domain). 
#define  ADI_PF_UNIX						ADI_PF_LOCAL 			///< Old BSD name for ADI_PF_LOCAL.  
#define  ADI_PF_FILE						ADI_PF_LOCAL 			///< Another non-standard name for ADI_PF_LOCAL.  
#define  ADI_PF_INET                		(2)						///< IP protocol family.
#define  ADI_PF_AX25						(3)						///< Amateur Radio AX.25.  
#define  ADI_PF_IPX							(4)						///< Novell Internet Protocol.  
#define  ADI_PF_APPLETALK					(5)						///< Appletalk DDP.  
#define  ADI_PF_NETROM						(6)						///< Amateur radio NetROM.  
#define  ADI_PF_BRIDGE						(7)						///< Multiprotocol bridge.  
#define  ADI_PF_ATMPVC						(8)						///< ATM PVCs.  
#define  ADI_PF_X25							(9)						///< Reserved for X.25 project.  
#define  ADI_PF_INET6						(10)						///< IP version 6.  
#define  ADI_PF_ROSE						(11)						///< Amateur Radio X.25 PLP.  
#define  ADI_PF_DECnet						(12)						///< Reserved for DECnet project. 
#define  ADI_PF_NETBEUI						(13)						///< Reserved for 802.2LLC project.  
#define  ADI_PF_SECURITY					(14)						///< Security callback pseudo AF.  
#define  ADI_PF_KEY							(15)						///< PF_KEY key management API.  
#define  ADI_PF_NETLINK						(16)  					///< net link
#define  ADI_PF_ROUTE	 					ADI_PF_NETLINK 		///< Alias to emulate 4.4BSD.  
#define  ADI_PF_PACKET						(17)						///< Packet family.  
#define  ADI_PF_ASH							(18)						///< Ash.  
#define  ADI_PF_ECONET						(19)						///< Acorn Econet.  
#define  ADI_PF_ATMSVC						(20)						///< ATM SVCs.  
#define  ADI_PF_SNA							(22)						///< Linux SNA Project 
#define  ADI_PF_IRDA						(23)						///< IRDA sockets.  
#define  ADI_PF_PPPOX						(24)						///< PPPoX sockets.  
#define  ADI_PF_WANPIPE						(25)						///< Wanpipe API sockets.  
#define  ADI_PF_BLUETOOTH					(31)						///< Bluetooth sockets.  
#define  ADI_PF_MAX							(32)						///< For now.  

#define  ADI_AF_UNSPEC        				ADI_PF_UNSPEC      	 	///< Unspecified.
#define  ADI_AF_INET           	  			ADI_PF_INET      		///< IP address family.
#define  ADI_AF_LOCAL						ADI_PF_LOCAL			///< Local to host (pipes and file-domain).  
#define  ADI_AF_UNIX						ADI_PF_UNIX			///< Old BSD name for ADI_AF_LOCAL. 
#define  ADI_AF_FILE						ADI_PF_FILE			///< Another non-standard name for ADI_AF_LOCAL.  
#define  ADI_AF_AX25						ADI_PF_AX25			///< Amateur Radio AX.25.  
#define  ADI_AF_IPX							ADI_PF_IPX			///< Novell Internet Protocol.  
#define  ADI_AF_APPLETALK					ADI_PF_APPLETALK  		///< Appletalk DDP.  
#define  ADI_AF_NETROM						ADI_PF_NETROM		///< Amateur radio NetROM.  
#define  ADI_AF_BRIDGE						ADI_PF_BRIDGE		///< Multiprotocol bridge.  
#define  ADI_AF_ATMPVC						ADI_PF_ATMPVC		///< ATM PVCs.  
#define  ADI_AF_X25							ADI_PF_X25			///< Reserved for X.25 project.  
#define  ADI_AF_INET6						ADI_PF_INET6			///< IP version 6.  
#define  ADI_AF_ROSE						ADI_PF_ROSE			///< Amateur Radio X.25 PLP.  
#define  ADI_AF_DECnet						ADI_PF_DECnet			///< Reserved for DECnet project. 
#define  ADI_AF_NETBEUI						ADI_PF_NETBEUI		///< Reserved for 802.2LLC project.  
#define  ADI_AF_SECURITY					ADI_PF_SECURITY		///< Security callback pseudo AF.  
#define  ADI_AF_KEY							ADI_PF_KEY			///< AF_KEY key management API.  
#define  ADI_AF_NETLINK						ADI_PF_NETLINK		///< net link
#define  ADI_AF_ROUTE						ADI_PF_ROUTE			///< Alias to emulate 4.4BSD.  
#define  ADI_AF_PACKET						ADI_PF_PACKET		///< Packet family.  
#define  ADI_AF_ASH							ADI_PF_ASH			///< Ash.  
#define  ADI_AF_ECONET						ADI_PF_ECONET		///< Acorn Econet.  
#define  ADI_AF_ATMSVC						ADI_PF_ATMSVC		///< ATM SVCs.  
#define  ADI_AF_SNA							ADI_PF_SNA			///< Linux SNA Project 
#define  ADI_AF_IRDA						ADI_PF_IRDA			///< IRDA sockets.  
#define  ADI_AF_PPPOX						ADI_PF_PPPOX			///< PPPoX sockets.  
#define  ADI_AF_WANPIPE						ADI_PF_WANPIPE		///< Wanpipe API sockets.  
#define  ADI_AF_BLUETOOTH					ADI_PF_BLUETOOTH 		///< Bluetooth sockets.  
#define  ADI_AF_MAX							ADI_PF_MAX			///< For now. 

#define  ADI_SOCK_STREAM           			(1)						///< Connectionless, unreliable datagrams of fixed maximum length. 
#define  ADI_SOCK_DGRAM        		     	(2)						///< Sequenced, reliable, connection-based byte streams.  
#define  ADI_SOCK_RAW                 		(3)						///< Raw protocol interface. 
#define  ADI_SOCK_RDM              			(4)						///< Reliably-delivered messages.  
#define  ADI_SOCK_SEQPACKET  	 			(5)						///< Sequenced, reliable, connection-based, datagrams of fixed maximum length.
#define  ADI_SOCK_PACKET  					(10)						///< Linux specific way of getting packets at the dev level.  For writing rarp and other similar things on the user level.

#define  ADI_ETH_P_ALL						(0x0003)					///< Every packet (be careful!!!)
#define  ADI_ETH_P_ARP						(0x0806)					///< Address Resolution packet	
#define  ADI_ETH_P_IP						(0x0800)					///< Internet Protocol packet	
#define  ADI_ETH_P_RARP      				(0x8035)					///< Reverse Addr Res packet	
#define  ADI_ETH_P_IPV6						(0x86DD)					///< IPv6 over bluebook		

#define  ADI_SOL_RAW						(255)					///< RAW layer
#define  ADI_SOL_DECNET      				(261)					///< DECNET layer
#define  ADI_SOL_X25        				(262)					///< X25 layer
#define  ADI_SOL_PACKET						(263)					///< PACKET layer
#define  ADI_SOL_ATM						(264)					///< ATM layer (cell level).  
#define  ADI_SOL_AAL						(265)					///< ATM Adaption Layer (packet level).  
#define  ADI_SOL_IRDA						(266)					///< IRDA layer
#define  ADI_SOL_SOCKET         			(0xffff)					///< SOCKET layer
#define  ADI_SOL_IP                 		(0) 						///< To select the IP level. 
#define  ADI_SOL_TCP               			(6) 						///< TCP level
#define  ADI_SOL_UDP              			(17)						///< sockopt level for UDP


#define ADI_SOL_HCI							(0)
#define ADI_SOL_L2CAP	    				(6)
#define ADI_SOL_SCO							(17)
#define ADI_SOL_RFCOMM						(18)


#define  ADI_SO_DEBUG            			(0x0001)      				///< turn on debugging info recording. 
#define  ADI_SO_REUSEADDR      				(0x0004)  				///< Allow reuse of local addresses.
#define  ADI_SO_KEEPALIVE      				(0x0008)  				///< Keep connections alive and send SIGPIPE when they die. 
#define  ADI_SO_DONTROUTE      				(0x0010)  				///< Don't do local routing. 
#define  ADI_SO_BROADCAST      				(0x0020)  				///< Allow transmission of broadcast messages.
#define  ADI_SO_LINGER            			(0x0080)   	 			///< Block on close of a reliable socket to transmit pending data.
#define  ADI_SO_OOBINLINE      				(0x0100)  				///< Receive out-of-band data in-band.
#define  ADI_SO_SNDBUF          			(0x1001)    				///< send buffer size. 
#define  ADI_SO_RCVBUF          			(0x1002)    				///< receive buffer size. 
#define  ADI_SO_SNDLOWAT    				(0x1003)   				///< send low-water mark. 
#define  ADI_SO_RCVLOWAT     				(0x1004)    				///< receive low-water mark. 
#define  ADI_SO_SNDTIMEO      				(0x1005)    				///< send timeout.
#define  ADI_SO_RCVTIMEO      				(0x1006)    				///< receive timeout. 
#define  ADI_SO_ERROR         				(0x1007)     				///< get error status and clear (ro). 
#define  ADI_SO_TYPE          				(0x1008)     				///< get socket type (ro) ,Compatible name for SO_STYLE.
#define  ADI_SO_STYLE	                    ADI_SO_TYPE	              ///< Synonym 
#define  ADI_SO_ACCEPTCONN     				(0x1009)  				///< accept connection


/**@brief linux-specific, might as well be the same as on i386 */
#define ADI_SO_NO_CHECK						(11)
#define ADI_SO_PRIORITY						(12)
#define ADI_SO_BSDCOMPAT					(14)
#define ADI_SO_PASSCRED						(17)
#define ADI_SO_PEERCRED						(18)

/**@brief Security levels - as per NRL IPv6 - don't actually do anything */
#define ADI_SO_SECURITY_AUTHENTICATION		(22)
#define ADI_SO_SECURITY_ENCRYPTION_TRANSPORT (23)
#define ADI_SO_SECURITY_ENCRYPTION_NETWORK	(24)
#define ADI_SO_BINDTODEVICE					(25)

/**@brief Socket filtering */
#define ADI_SO_ATTACH_FILTER        		(26)
#define ADI_SO_DETACH_FILTER       			(27)
#define ADI_SO_PEERNAME             		(28)
#define ADI_SO_TIMESTAMP					(29)
#define ADI_SCM_TIMESTAMP					ADI_SO_TIMESTAMP
#define ADI_SO_PEERSEC						(30)


#define  ADI_IP_TOS               	 	 	(1)   					///< int; IP type of service and precedence.  
#define  ADI_IP_TTL               	 	 	(2)   					///< int; IP time to live.
#define  ADI_IP_HDRINCL           	 	 	(3)   					///< int; Header is included with data.  
#define  ADI_IP_OPTIONS         			(4)						///< ip_opts; IP per-packet options.  
#define  ADI_IP_ROUTER_ALERT    			(5)						///< bool 
#define  ADI_IP_RECVOPTS        			(6)						///< bool 
#define  ADI_IP_RETOPTS         			(7)						///< bool 
#define  ADI_IP_PKTINFO         			(8)						///< bool 
#define  ADI_IP_PKTOPTIONS      			(9)
#define  ADI_IP_PMTADISC        			(10)						///< obsolete name
#define  ADI_IP_MTU_DISCOVER    			(10)						///< int; see below 
#define  ADI_IP_RECVERR         			(11)						///< bool 
#define  ADI_IP_RECVTTL         			(12)						///< bool 
#define  ADI_IP_RECVTOS         			(13)						///< bool 
#define  ADI_IP_MULTICAST_IF        		(32)   					///< set/get IP multicast i/f .
#define  ADI_IP_MULTICAST_TTL       		(33)   					///< set/get IP multicast ttl  .
#define  ADI_IP_MULTICAST_LOOP      		(34)   					///< set/get IP multicast loopback .
#define  ADI_IP_ADD_MEMBERSHIP      		(35)   					///< add an IP group membership.
#define  ADI_IP_DROP_MEMBERSHIP     		(36)   					///< drop an IP group membership .
#define  ADI_IP_UNBLOCK_SOURCE				(37)
#define  ADI_IP_BLOCK_SOURCE				(38)
#define  ADI_IP_ADD_SOURCE_MEMBERSHIP		(39)
#define  ADI_IP_DROP_SOURCE_MEMBERSHIP		(40)
#define  ADI_IP_MSFILTER					(41)
#define  ADI_MCAST_JOIN_GROUP		        (42)
#define  ADI_MCAST_BLOCK_SOURCE		        (43)
#define  ADI_MCAST_UNBLOCK_SOURCE		    (44)
#define  ADI_MCAST_LEAVE_GROUP		        (45)
#define  ADI_MCAST_JOIN_SOURCE_GROUP		(46)
#define  ADI_MCAST_LEAVE_SOURCE_GROUP	    (47)
#define  ADI_MCAST_MSFILTER			        (48)

#define ADI_MCAST_EXCLUDE					(0)
#define ADI_MCAST_INCLUDE					(1)


#define ADI_IP_RECVRETOPTS					ADI_IP_RETOPTS		///< For BSD compatibility.  

#define ADI_IP_PMTADISC_DONT   				(0)						///< Never send DF frames.  
#define ADI_IP_PMTADISC_WANT   				(1)						///< Use per route hints.  
#define ADI_IP_PMTADISC_DO     				(2)						///< Always DF.  


#define ADI_IP_DEFAULT_MULTICAST_TTL        (1)
#define ADI_IP_DEFAULT_MULTICAST_LOOP       (1)
#define ADI_IP_MAX_MEMBERSHIPS              (20)


#define  ADI_MSG_OOB           	  			(0x01)    					///< Process out-of-band data. 
#define  ADI_MSG_PEEK          	 			(0x02)					///< Peek at incoming messages.  
#define  ADI_MSG_DONTROUTE 	  				(0x04)     				///< Don't use local routing. 
#define  ADI_MSG_CTRUNC						(0x08)					///< Control data lost before delivery.  
#define  ADI_MSG_PROXY						(0x10)					///< Supply or ask second address.  
#define  ADI_MSG_TRUNC          	 		(0x20)     				///< rcvd data truncated .
#define  ADI_MSG_DONTWAIT	 				(0x40) 					///< Nonblocking IO.  
#define  ADI_MSG_EOR              	 		(0x80)    					///< end of record. NG
#define  ADI_MSG_TRYHARD					ADI_MSG_DONTROUTE
#define  ADI_MSG_WAITALL					(0x100)					///< Wait for a full request.  
#define  ADI_MSG_FIN						(0x200)					///< Finished
#define  ADI_MSG_SYN						(0x400)					///< Synchronize   
#define  ADI_MSG_CONFIRM					(0x800)					///< Confirm path validity.
#define  ADI_MSG_RST						(0x1000)					///< Reset
#define  ADI_MSG_ERRQUEUE					(0x2000)					///< Fetch message from error queue. 
#define  ADI_MSG_NOSIGNAL					(0x4000)					///< Do not generate SIGPIPE.
#define  ADI_MSG_MORE						(0x8000)					///< Sender will send more.

#define  ADI_F_GETFL         				(1 << 3)     					///< Get file status flags.
#define  ADI_F_SETFL         				(1 << 4)     					///< Set file status flags.
#define  ADI_O_NONBLOCK      				(1 << 9)     				///< set/clear nonblocking io 
#define  ADI_O_NDELAY        				ADI_O_NONBLOCK		///< set/clear nonblocking io 

/**@brief the ip is class A  */
#define  ADI_IN_CLASSA(i)            		(((ADIInAddr_t)(i) & 0x80000000) == 0)
#define  ADI_IN_CLASSA_NET           		(0xff000000)
#define  ADI_IN_CLASSA_NSHIFT        		(24)
#define  ADI_IN_CLASSA_HOST          		(0x00ffffff)  
#define  ADI_IN_CLASSA_MAX           		(128)

/**@brief the ip is class B  */
#define  ADI_IN_CLASSB(i)            		(((ADIInAddr_t)(i) & 0xc0000000) == 0x80000000)
#define  ADI_IN_CLASSB_NET           		(0xffff0000)
#define  ADI_IN_CLASSB_NSHIFT        		(16)
#define  ADI_IN_CLASSB_HOST          		(0x0000ffff)
#define  ADI_IN_CLASSB_MAX           		(65536)

/**@brief the ip is class C  */
#define  ADI_IN_CLASSC(i)            		(((ADIInAddr_t)(i) & 0xe0000000) == 0xc0000000)
#define  ADI_IN_CLASSC_NET           		(0xffffff00)
#define  ADI_IN_CLASSC_NSHIFT        		(8)
#define  ADI_IN_CLASSC_HOST          		(0x000000ff)

/**@brief the ip is class D  */
#define  ADI_IN_CLASSD(i)            		(((ADIInAddr_t)(i) & 0xf0000000) == 0xe0000000)
#define  ADI_IN_MULTICAST(i)         		ADI_IN_CLASSD(i)

/**@brief the ip is class E  */
#define  ADI_IN_EXPERIMENTAL(i)      		(((ADIInAddr_t)(i) & 0xe0000000) == 0xe0000000)
#define  ADI_IN_BADCLASS(i)          		(((ADIInAddr_t)(i) & 0xf0000000) == 0xf0000000)

#define  ADI_IN_LOOPBACKNET					(127)						///< Network number for local host loopback.  			

#define  ADI_INADDR_ANY              		((ADIInAddr_t)0x00000000)    ///< Address to accept any incoming messages. 
#define  ADI_INADDR_LOOPBACK         		((ADIInAddr_t)0x7f000001)	///< Address to loopback in software to local host.  Inet 127.0.0.1. 
#define  ADI_INADDR_BROADCAST        		((ADIInAddr_t)0xffffffff)	///< Address to send to all hosts.
#define  ADI_INADDR_NONE             		((ADIInAddr_t)0xffffffff)	///< Address indicating an error return. 
#define  ADI_INADDR_UNSPEC_GROUP    	 	((ADIInAddr_t)0xe0000000)	///< 224.0.0.0
#define  ADI_INADDR_ALLHOSTS_GROUP  	 	((ADIInAddr_t)0xe0000001)	///< 224.0.0.1
#define  ADI_INADDR_ALLRTRS_GROUP      		((ADIInAddr_t)0xe0000002) 	//<  224.0.0.2 
#define  ADI_INADDR_MAX_LOCAL_GROUP 		((ADIInAddr_t)0xe00000ff)	///< 224.0.0.255

#define ADI_INET_ADDRSTRLEN 					(16)
#define ADI_INET6_ADDRSTRLEN 				(46)


#pragma pack(1)//1字节对齐
/* BD Address */
typedef struct
{
	unsigned char b[6];
} ADIBDAddrr_S;
#pragma pack()//恢复对齐状态

#define ADI_BDADDR_ANY   (&(ADIBDAddrr_S) {{0, 0, 0, 0, 0, 0}})
#define ADI_BDADDR_ALL   (&(ADIBDAddrr_S) {{0xff, 0xff, 0xff, 0xff, 0xff, 0xff}})
#define ADI_BDADDR_LOCAL (&(ADIBDAddrr_S) {{0, 0, 0, 0xff, 0xff, 0xff}})


#define ADISockaddr_Storage_S ADIKernel_Sockaddr_Storage_S
#define ADIK_SS_MAXSIZE	128												///< Implementation specific max size 


/**@brief 保存待检测的套接字句柄 */
typedef struct 
{
	long fds[( ADI_FD_MAX)/(8*sizeof(long))];
	#define ADI_FDS_BITS(set)  ((set)->fds)
} ADIFdSet_S;


/**@brief add a descripter to a set */
#define  ADI_FD_SET(fd, fdset)       (ADI_FDS_BITS (fdset)[(fd /(8*sizeof ( long)))] |= (1UL << ((fd) % (8*sizeof ( long)))))

/**@brief remove a descripter from a set	*/
#define  ADI_FD_CLR(fd, fdset)       (ADI_FDS_BITS (fdset)[(fd /(8*sizeof ( long)))] &= ~(1UL << ((fd) % (8*sizeof ( long)))))

/**@brief test to see if a descriptor is part of the set	*/
#define  ADI_FD_ISSET(fd, fdset)    ((ADI_FDS_BITS (fdset)[(fd /(8*sizeof ( long)))] & (1UL << ((fd) % (8*sizeof ( long))))) != 0)

/**@brief clear a set */
#define  ADI_FD_ZERO(fdset)  do \
{									      \
  unsigned int i;							      \
  ADIFdSet_S *arr = (fdset);						      \
  for (i = 0; i < sizeof (ADIFdSet_S) / sizeof ( long); ++i)	      \
  ADI_FDS_BITS (arr)[i] = 0;					      \
}while (0)



typedef char *  ADI_Caddr_tt;

/**@brief 延迟关闭socket */
typedef struct
{
	int		l_onoff;               ///< 是否延迟关闭		
	int		l_linger;	             ///< 延迟关闭的时间

} ADILinger_S;


/**@brief 输入输出缓存区 */
typedef struct 
{
  void *         iov_base;	      					///< 数据指针
  unsigned int   iov_len;	            			///< 数据长度
}ADIIovec_S;


/**@brief 消息发送和接收信息描述结构体 */
typedef struct 
{
  void           * msg_name;		       	///< 发送方存放目的地址，接收方存放发送地址
  unsigned int   msg_namelen;	       		///< 地址数据长度
  ADIIovec_S     * msg_iov;					///< 输入输出缓存数据
  int            msg_iovlen;		       	///< 缓存中数据成员个数
  void           * msg_control;				///< 辅助数据
  unsigned int   msg_controllen;	     	///< 辅助数据大小
  int            msg_flags;		       		///< 接收数据标志
}ADIMsghdr_S;	


/**@brief 主机信息 */
typedef  struct 
{
  char *   h_name;				  			///< 主机的规范名
  char **  h_aliases;			  			///< 主机的别名
  int      h_addrtype;				  		///< IP地址的类型
  int      h_length;				  		///< IP地址的长度
  char **  h_addr_list;		         		///< 主机的IP 地址 
  #define	h_addr	h_addr_list[0]	  		///< 取第一个IP 地址
}ADIHostent_S;


/**@brief 服务端信息  */
typedef struct 
{
  char *  	s_name;							///< 标准服务名
  char **	s_aliases;						///< 服务别名
  int      	s_port;							///< 端口号
  char *	s_proto;						///< 使用协议
}ADIServent_S;


/**@brief 协议信息  */
typedef struct 
{
  char *	p_name;							///< 协议名称
  char **	p_aliases;						///< 协议别名
  int 		p_proto;						///< 协议编号
}ADIProtoent_S;


typedef unsigned int  ADIInAddr_t;		///< 类型定义

/**@brief 地址信息结构体*/
typedef struct 
 {
   ADIInAddr_t s_addr;
 }ADIInAddr_S;


/**@brief 保存套接字信息结构体

@note 此结构保存的数据与ADISockAddr_S结构相同，详见ADISockAddr_S注释
*/
typedef struct 
{
    unsigned short 	sin_family;   				///< 地址族
    unsigned short  sin_port;   				///< 端口号
    ADIInAddr_S 	sin_addr;   				//< IP地址
    unsigned char 	sin_zero[8];   				///< 填充0以保持与struct ADISockAddr_S同样大小
}ADISockAddr_IN_S;


/**@brief 保存套接字信息结构体

@note 用户使用ADISockAddr_IN_S结构进行赋值后，强制转换为ADISockAddr_S结构作为ADISOCKConnect函数的参数传入
*/
typedef struct 
{
    unsigned short sa_family;   					///< 地址族
    char sa_data[14];   							///< 14字节地址
}ADISockAddr_S;


/**@brief IPv6 地址*/
typedef struct 
{
	union 
	{
		unsigned char		u6_addr8[16];
		unsigned short	u6_addr16[8];
		unsigned int		u6_addr32[4];
	} in6_u;
#define ADISock_s6_addr		in6_u.u6_addr8
#define ADISock_s6_addr16		in6_u.u6_addr16
#define ADISock_s6_addr32		in6_u.u6_addr32
}ADISockIn6_Addr_S;


extern const ADISockIn6_Addr_S ADI_IN6ADDR_ANY;        						///<ipv6 addr_any
extern const ADISockIn6_Addr_S ADI_IN6ADDR_LOOPBACK;   					///<ipv6 loopback


/**@brief ipv6  保存套接字信息结构体*/
typedef struct  
{
	unsigned short 		sin6_family;    		///<ipv6 地址族
	unsigned short		sin6_port;     			///<ipv6 端口号
	unsigned int		sin6_flowinfo;  		///<ipv6 流信息
	ADISockIn6_Addr_S	sin6_addr;     	        ///<ipv6 地址
	unsigned int		sin6_scope_id;  		///<ipv6 socpe id
}ADISockAddr_IN6_S;


/**@brief 加入或退出组播*/
typedef struct  
{
     ADIInAddr_S  imr_multiaddr;  				///< 组播地址
     ADIInAddr_S  imr_interface;  					///< 本地接口IP地址
}ADIIp_Mreq_S;


/**@brief 在指定接口加入或退出组播 */
typedef struct 
{
    ADIInAddr_S  imr_multiaddr;				///< 组播地址
    ADIInAddr_S  imr_address;				///< 本地接口IP地址
    int			 imr_ifindex;					///< 接口索引
 }ADIIp_Mreqn_S;


/**@brief ipv6 加入或退出组播*/
typedef struct
{
	unsigned int		imr_multiaddr;			///<组播组地址
	unsigned int		imr_interface;			///<网络接口IP地址
	unsigned int		imr_sourceaddr;			///<组播源地址
}ADIIp_Mreq_Source_S ;


/**@brief socket内核地址结构*/
typedef struct
{
	unsigned short	ss_family;								///<地址族
	char		data[ADIK_SS_MAXSIZE - sizeof(unsigned short)];	///<socket 地址信息
} ADIKernel_Sockaddr_Storage_S;	


/**@brief 组播组请求*/
typedef struct 
{
	unsigned int				 gr_interface;		///<网络接口索引
	ADIKernel_Sockaddr_Storage_S gr_group;		///<组播组地址
}ADIGroup_Req_S;


/**@brief组播组请求*/
typedef struct 
{
	unsigned int				 gsr_interface;		///<网络接口索引
	ADIKernel_Sockaddr_Storage_S gsr_group;	///<组播组地址
	ADIKernel_Sockaddr_Storage_S gsr_source;	///<组播源地址
}ADIGroup_Source_Req_S;


/**@brief组播过滤*/
typedef struct 
{
	unsigned int				 gf_interface;		///<网络接口索引
	ADIKernel_Sockaddr_Storage_S gf_group;		///<组播组地址
	unsigned int				 gf_fmode;			///<过滤模式
	unsigned int				 gf_numsrc;			///<组播源个数
	ADIKernel_Sockaddr_Storage_S gf_slist[1];		///<网络接口索引
}ADIGroup_Filter_S;



/**@brief 超时时间值结构体*/
typedef struct 
 {
   long int tv_sec;								///< 秒
   long int tv_usec;							///< 微秒,即一百万分之一秒
 }ADITimeval_S;

/**@brief RFCOMM socket address */
typedef struct  {
		unsigned short	addressFamily;
		ADIBDAddrr_S	btAddr;
		unsigned char port;
}ADISockAddr_RC_S;

 /**
 @brief 创建套接字。
 
 @param[in] nDomain 指定要创建的套接字协议族
 @param[in] nType 指定要创建的套接字类型              
 @param[in] nProtocol 指定哪种协议，通常设置为0
 @return 成功返回创建的套接字描述符；失败返回-1。
 @note 详细描述参见Linux下的socket接口说明。
 */
 int ADISOCKSocket(int nDomain,int nType,int nProtocol);


 /**
 @brief 将指定的主机地址与套接字进行绑定。
 
 @param[in] nFd 需要绑定的套接字描述符
 @param[in] psAddr 待绑定的主机地址结构体的指针
 @param[in] uAddrLen 地址结构体ADISockAddr的长度
 @return 成功返回0; 失败返回-1。
 @note 详细描述参见Linux下的bind接口说明。
 */
 ADI_Error_Code ADISOCKBind(int nFd,const ADISockAddr_S * psAddr,unsigned int uAddrLen);
 

 /**
 @brief 对连接进行监听。
 
 @param[in] nFd 套接字描述符
 @param[in] nNum 接收队列的最大长度
 @return 成功返回0; 失败返回-1。
 @note 详细描述参见Linux下的listen接口说明。
 */
 ADI_Error_Code ADISOCKListen(int nFd,int nNum);



 /**
 @brief 向指定地址发起连接。
 
 @param[in] nFd 套接字描述符
 @param[in] psAddr 指向待连接地址结构体的指针
 @param[in] uAddrLen 结构体ADISockAddr_S 的长度
 @return 成功返回0 ; 失败返回-1。
 @note 详细描述参见Linux下的connect接口说明。
 */
 ADI_Error_Code ADISOCKConnect(int nFd,const ADISockAddr_S * psAddr,unsigned int uAddrLen);
 

  /**
 @brief 在指定套接字上接收一个连接。
 
 @param[in] nFd 处于监听状态的套接字描述符
 @param[out] psAddr 指向保存连接方地址的结构体指针
 @param[out] puAddrLen 结构体ADISockAddr_S 的长度
 @return 成功返回新套接字描述符；失败返回-1  。
 @note 详细描述参见Linux下的accept接口说明。
 */
 ADI_Error_Code ADISOCKAccept(int nFd,ADISockAddr_S * psAddr,unsigned int * puAddrLen);


 /**
 @brief 发送数据。
 
 @param[in] nFd 发送端套接字描述符
 @param[in] pvBuf 待发送数据缓存区
 @param[in] uNum 缓存区中数据长度
 @param[in] nFlags 发送选项，一般设置为0
 @return 成功返回实际发送的数据长度; 失败返回-1  。
 @note 详细描述参见Linux下的send接口说明。
 */
 int ADISOCKSend(int nFd,const void * pvBuf,unsigned int uNum,int nFlags);


 /**
 @brief 接收数据。
 
 @param[in] nFd 接收端套接字描述符
 @param[out] pvBuf 用于接收数据的缓存区
 @param[in] uNum 缓存区长度
 @param[in] nFlags 操作选项，一般置为0
 @return 成功返回实际接收的字节数; 失败返回-1。
 @note 详细描述参见Linux下的recv接口说明。
 */
int ADISOCKRecv(int nFd,void * pvBuf,unsigned int uNum,int nFlags);


 /**
 @brief 发送数据到指定目的地址。
 
 @param[in] nFd 套接字描述符
 @param[in] pvBuf 待发送数据的缓存区
 @param[in] uNum 缓存区中数据的长度
 @param[in] nFlags 操作选项，一般为0
 @param[in] psAddr 指向ADISockAddr_S结构体的指针
 @param[in] uAddrLen ADISockAddr_S 的长度				                                        
 @return 成功返回实际发送出去的数据字节数;失败返回-1  。
 @note 详细描述参见Linux下的sendto接口说明。
 */
 int ADISOCKSendTo(int nFd,const void * pvBuf,unsigned int uNum,int nFlags,const ADISockAddr_S * psAddr,unsigned int uAddrLen);



 /**
 @brief 从指定源地址接收数据。
 
 @param[in] nFd 套接字描述符
 @param[out] pvBuf 用于接收数据的缓存区
 @param[in] uNum 缓存区长度
 @param[in] nFlags 操作选项，一般置为0
 @param[out] psAddr 指向ADISockAddr_S 结构体的指针
 @param[in] puAddrLen ADISockAddr_S 的长度，此参数亦作为输出参数
 @return 成功返回读取的字节数;失败返回-1 。
 @note 详细描述参见Linux下的recvfrom接口说明。
 */
int ADISOCKRecvFrom(int nFd,void * pvBuf,unsigned int uNum, int nFlags,ADISockAddr_S * psAddr,unsigned int * puAddrLen);


 /**
 @brief 确定一个或多个套接字的状态，判断套接字上是否有数据可读，能否向套接字写入数据，是否有意外情况。
 
 @param[in] nFds 需要管理的最大套接字数加一
 @param[in] psReadnFds 用来检查可读性的一组套接字描述符
 @param[in] psWritenFds 用来检查可写性的一组套接字描述符
 @param[in] psExceptnFds 用来检查意外状态的套接字文件描述符，错误不属于意外状态
 @param[in] psTimeout 等待时间
 @return 成功返回准备就绪的套接字数；超时返回0；失败返回错误码。
 @note 详细描述参见Linux下的select接口说明。
 */
 int ADISOCKSelect(int nFds,ADIFdSet_S * psReadnFds,ADIFdSet_S * psWritenFds,ADIFdSet_S * psExceptnFds,ADITimeval_S * psTimeout);


 /**
 @brief 根据套接字描述符来操作套接字的属性, 参考BSD Socket 标准定义。
 
 @param[in] nFd 被参数nCmd 操作的描述符
 @param[in] nCmd 操作命令，可供使用的操作命令参见标准Linux定义。
 @param[in] nArg 参数
 @return 成功对于不同的操作命令有不同的返回值；失败返回-1。
 */
int ADISOCKFcntl(int nFd,int nCmd,int nArg1,int nArg2);


 /**
 @brief 设备驱动程序中对设备的I/O通道进行管理，参考BSD Socket 标准定义。
 
 @param[in] nFd 套接字描述符
 @param[in] ulRequest 用户对程序的控制命令，可供使用的操作命令参见标准Linux定义。
 @param[in] pArg 参数
 @return 成功对于不同的操作命令有不同的返回值；失败返回-1。
 @note 详细描述参见Linux下的ioctl接口说明。
 */
 ADI_Error_Code ADISOCKIoctl(int nFd,unsigned int ulRequest,void * pArg1, void *pArg2);


 /**
 @brief 获取套接字选项。
 
 @param[in] nFd 套接字描述符
 @param[in] nLevel  选项定义的层次，可取值有 ADI_SOL_SOCKET，ADI_SOL_TCP，ADI_SOL_UDP， ADI_SOL_IP
 @param[in] nOptName 要获取的选项名
 @param[out] pvOptVal 指向保存选项值的缓存区
 @param[in] puOptLen 保存选项值缓存区的长度，此参数亦作为输出参数
 @return 成功返回0；失败返回错误码。
 @note 详细描述参见Linux下的getsockopt接口说明。
 */
 ADI_Error_Code ADISOCKGetSockOpt(int nFd,int nLevel,int nOptName,void * pvOptVal,unsigned int * puOptLen);


 /**
 @brief 设置套接字选项。
 
 @param[in] nFd 套接字描述符
 @param[in] nLevel  选项定义的层次，可取值有 ADI_SOL_SOCKET，ADI_SOL_TCP，ADI_SOL_UDP， ADI_SOL_IP
 @param[in] nOptName 需要设置的选项名
 @param[in] pvOptVal 指向保存选项值的缓存区
 @param[in] uOptLen  保存选项值缓存区的长度
 @return 成功返回0；失败返回错误码。
 @note 详细描述参见Linux下的setsockopt接口说明。
 */
 ADI_Error_Code ADISOCKSetSockOpt(int nFd,int nLevel,int nOptName,const void * pvOptVal, unsigned int uOptLen);


 /**
 @brief 根据协议名称获取协议的其它信息。
 
 @param[in] pcProtoName 协议名称
 @return 成功返回协议ADIProtoent_S结构体信息；失败返回ADI_NULL。
 @note 详细描述参见Linux下的getprotobyname接口说明。
 */
ADIProtoent_S * ADISOCKGetProtoByName(const char * pcProtoName);

 
 /**
 @brief 根据服务名和协议名获取服务信息。
 
 @param[in] pcServName 服务名称
 @param[in] pcProtoName 服务使用的协议
 @return 成功返回服务ADIServent_S 结构体信息；失败返回ADI_NULL。
 @note 详细描述参见Linux下的getservbyname接口说明。
 */
ADIServent_S * ADISOCKGetServByName(const char * pcServName,const char * pcProtoName);


 /**
 @brief 获取与套接字相关的远端地址。

 @param[in] nFd 标识已连接的套接字描述符
 @param[out] psAddr 结构体ADISockAddr_S 的指针，保存连接的另一方的信息
 @param[in] puAddrLen 指向sizeof(ADISockAddr_S)的指针，此指针亦作为输出参数
 @return 成功返回0 ,失败返回错误码。
 @note 详细描述参见Linux下的getpeername接口说明。
 */
 ADI_Error_Code ADISOCKGetPeerName(int nFd,ADISockAddr_S * psAddr,unsigned int * puAddrLen);


 /**
 @brief 获取与套接字相关的本地地址。
 
 @param[in] nFd 套接字描述符
 @param[out] psAddr 指向接收套接字地址
 @param[in] puAddrLen 作为输入参数时，为空间的最大长度。作为输出参数时，为缓存区的实际大小，以字节为单位。
 @return 成功返回0,失败返回错误码。
 @note 详细描述参见Linux下的getsockname接口说明。
 */
 ADI_Error_Code ADISOCKGetSockName(int nFd,ADISockAddr_S * psAddr, unsigned int * puAddrLen);


 /**
 @brief 获取本地主机的主机名。

 @param[out] pcHostName 接收本地主机名的缓存区
 @param[in] uAddrLen 缓存区的长度
 @return 成功返回0；失败返回错误码。
 @note 详细描述参见Linux下的gethostname接口说明。
 */
 ADI_Error_Code ADISOCKGetHostName(char * pcHostName,unsigned int uAddrLen);


 /**
 @brief 根据主机名获取主机的其它信息。
 
 @param[in] pcHostName 主机名
 @return 成功返回获取的主机ADIHostent_S结构体信息；失败返回ADI_NULL
 @note 详细描述参见Linux下的gethostbyname接口说明。
 @note 该接口已废弃，中间件不再使用
 */
 ADIHostent_S * ADISOCKGetHostByName(const char * pcHostName);


/**
 @brief 根据主机名获取主机的其它信息。
 
 @param[in] pcHostName 主机名
 @param[in] psResultBuf 指向一个主机结构
 @param[in] pcBuf 指向一个缓存，此指针亦作为输出
 @param[in] uBufLen 缓存区大小，此参数亦作为输出
 @param[out] psResult 函数成功调用后指向获取的主机结构ADIHostent_S
 @param[out] pnErrCode 错误码
 @return 成功返回0；失败返回错误号。
 @note 详细描述参见Linux下的gethostbyname_r接口说明。
 @note 该接口已废弃，中间件不再使用
 */
int ADISOCKGetHostByName_r(const char * pcHostName,ADIHostent_S * psResultBuf,char * pcBuf,unsigned int uBufLen,ADIHostent_S ** psResult,int * pnErrCode);


 /**
 @brief 根据给定的地址获取主机的其它信息。
 
 @param[in] pvAddr 主机地址(IP地址网络字节序)
 @param[in] uAddrLen 地址的长度
 @param[in] nType 地址类型
 @return 成功返回获取的主机ADIHostent_S 结构体信息；失败返回ADI_NULL
 @note 详细描述参见Linux下的gethostbyaddr接口说明。
 */
ADIHostent_S * ADISOCKGetHostByAddr(const void * pvAddr,unsigned int uAddrLen,int nType);


  /**
 @brief 把点分IP地址转换为网络字节序的网络地址。
 @param[in] pcIp 需要转化的标准点分IP地址字符串,例如"192.168.0.1"
 @note 当IP是255.255.255.255时，函数ADIInet_addr()会认为这是个无效的IP地址
 @return 成功返回无符号整数；失败返回-1。
 @note 详细描述参见Linux下的inet_addr接口说明。
 */
signed long ADISOCKInet_addr(const char * pcIp);


 /**
 @brief 把点分IP地址转换为网络字节序的网络地址。
 
 @param[in] pcIp 需要转化的点分IP地址
 @param[out] psIpNet IP地址结构体
 @return 成功返回非0；失败返回0。
 @note 详细描述参见Linux下的inet_aton接口说明。
 */
 ADIInAddr_t ADISOCKInet_aton(const char * pcIp, ADIInAddr_S * psIpNet);

 
 /**
 @brief 把网络字节序地址转换为点分IP地址。
 
 @param[in] sIpNet 网络字节序地址
 @return 转换后的点分IP 地址字符串；失败返回ADI_NULL。
 @note 详细描述参见Linux下的inet_ntoa接口说明。
 */
 char * ADISOCKInet_ntoa(ADIInAddr_S sIpNet);


 
 /**
 @brief 把字符串转换成网络地址。
 
 @param[in] nAf 地址族
 @param[in] pSrc 字符型地址
 @param[out] pDst 地址转换为in_addr的结构体，并复制在pDst中
 @return 成功返回1；失败返回0
 @note 详细描述参见Linux下的inet_pton接口说明。
 */
 int ADISOCKInet_pton(int nAf,const char *pSrc, void *pDst);


  
 /**
 @brief 把网络二进制结构地址转换成字符串地址。
 
 @param[in] nAf 地址族
 @param[in] pSrc 网络地址
 @param[out] pDst 字符型地址
 @param[in] nDsrLen pDst 缓存区
 @return 成功返回转换后的字符串地址；失败返回ADI_NULL
 @note 详细描述参见Linux下的inet_ntop接口说明。
 */
 const char * ADISOCKInet_ntop(int nAf,const void *pSrc,char *pDst,int nDsrLen);



 /**
 @brief 把short型的网络字节序转化为主机字节序。
 
 @param[in] ushNet 网络字节序的16bit数据
 @return 主机字节序值。
 @note 详细描述参见Linux下的ntohs接口说明。
 */
unsigned short ADISOCKNtohs(unsigned short ushNet);


 /**
 @brief 把short型的主机字节序转换为网络字节序。
 
 @param[in] ushHost 主机字节序的16bit数据
 @return 网络字节序值
 @note 详细描述参见Linux下的htons接口说明。
 */
unsigned short ADISOCKHtons(unsigned short ushHost);
  

 /**
 @brief 把32位的网络字节序转化为主机字节序。
 
 @param[in] uNet 网络字节序的32bit数据
 @return 主机字节序值
 @note 详细描述参见Linux下的ntohl接口说明。
 */
unsigned int ADISOCKNtohl(unsigned int uNet);
 

 /**
 @brief 把32位的主机字节序转换为网络字节序。
 
 @param[in] uHost 主机字节序的32bit数据
 @return 网络字节序值
 @note 详细描述参见Linux下的htonl接口说明。
 */
unsigned int ADISOCKHtonl(unsigned int uHost);


 /**
 @brief  在指定套接字上禁止数据的接收、发送或同时禁止数据接收和发送。
 
 @param[in] nFd 需要关闭的套接字描述符
 @param[in] nHow 关闭方式 
 @return 成功返回0；失败返回-1。
 @note nHow=0:禁止数据接收
 @note nHow=1:禁止数据发送
 @note nHow=2:同时禁止数据发送和接收
 */
 ADI_Error_Code ADISOCKShutDown(int nFd,int nHow);


 /**
 @brief 关闭指定的套接字。
 
 @param[in] nFd 套接字描述符
 @return 成功返回0；失败返回-1。
 @note 详细描述参见Linux下的close接口说明。
 */
ADI_Error_Code ADISOCKClose(int nFd);


 /**@brief 获取错误号。

 @return 返回错误号,详见adi_sockerror.h头文件定义。
 */
int ADISOCKGetLastError(void);


#ifdef __cplusplus
}
#endif
/** @} */
#endif

