
#ifndef BIT_H__INCLUDED__
#define BIT_H__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************************************/

/* maximum attempts */
#define UART_DL_ATTEMPT_MAX  3

/* the acceptable window of load sequence number. */
#define DEFAULT_MAX_INCREMENT_FOR_LOAD_SEQ_NUM (99)

/* the acceptable window of load sequence number. */
#define DEFAULT_MAX_INCREMENT_FOR_MODULE_VERSION (99)



#define DG_SIZE_MAX  0x10000  /* Datagram :   64KB */
#define SAFE_MARGIN  0x3000  /* more than (PT_SIZE_MAX * 5%) at least. */

#define DG_BUF_SIZE_MAX   (DG_SIZE_MAX + SAFE_MARGIN)


/* Maximum count of datagram for each module. */
#define MODULE_DATAGRAM_COUNT_MAX          (65536)

/* fixed size of module download header */
#define MODULE_DOWNLOAD_HEADER_STATIC_SIZE (28) 

/******************************************************************************/

/** Memory type */
typedef enum _lc_module_memory_type
{
    /**
     * This module must be saved into FLASH.
     */
    MOD_MEM_TYPE_FLASH = 0x00,

    /**
     * This module must be saved into NVRAM.
     */
    MOD_MEM_TYPE_NVRAM  = 0x01
    
} lc_module_memory_type;


/** data type of serial download */
typedef enum _lc_uart_packet_type
{
    /**
     * UART download header packet type.
     */
    UART_DLH_ID = 0x11,

    /**
     * UART module header packet type.
     */
    UART_MH_ID  = 0x22,

    /**
     * UART datagram pakcet type.
     */
    UART_DG_ID  = 0x33
    
} lc_uart_packet_type;

/** data packet for UART download format. */
typedef struct _lc_serial_download_packet
{
    lc_uchar data_id; /**< (1 byte) - variable, refer to lc_uart_packet_type */
    lc_uint16 length; /**< (2 bytes) - length of field below. */
    lc_uchar *payload;
    
} lc_serial_download_packet;


/******************************************************************************/

/* make sure it is an even number of bytes. */
#define DLH_TEXT_CHAR_MAX  30

typedef struct _module_id_info_st
{
    lc_uint16 module_id; /**< (2 bytes) - variable */
    lc_uint16 module_version; /**< (2 bytes) - variable */
	lc_buffer_st *moduleDataBuffer;	
} module_id_info_st;

/* download header structure */
typedef struct  _lc_module_dlh_st
{

    lc_uint16 manufacturer_id; /**< (2 bytes) - variable */
    lc_uint16 hardware_version; /**< (2 bytes) - variable */

    lc_uchar loader_gte_v4;  /**< (1 bit) - must be 0b0 */
    lc_uchar loader_gte_v3;  /**< (1 bit) - must be 0b0 */
    lc_uchar loader_gte_v5;  /**< (1 bit) - must be 0b1 */
    lc_uchar reserved; /**< (5 bits) - variable */

    lc_uchar loader_minor_version; /**< (1 byte) - variable */
    lc_uint16 download_id; /**< (2 bytes) - variable */
    lc_uint16 variant; /**< (2 bytes) - variable */
    lc_uint16 sub_variant; /**< (2 bytes) - variable */
    lc_char isign_version[4]; /**< (4 bytes) - variable */
    lc_char isign_serial_number[4]; /**< (4 bytes) - variable */
    lc_uint16 download_sequence_number; /**< (2 bytes) - variable */
    
    lc_uint16 number_of_modules; /**< (2 bytes) - variable */

    module_id_info_st *pModuleIdList;


    lc_uint16 header_signature_length; /**< (2 bytes) - length of download header signature */
    lc_uchar *header_signature; /**< (n bytes) - This is the signature for the above fields in 
                                    the download header, n = header_signature_length */

    lc_uint16 download_signature_length; /**< (2 bytes) - length of globle download signature */
    lc_uchar *download_signature; /**< (n bytes) - This is the signature for the complete download, 
                                    n = download_signature_length */

    lc_uint16 crc16; /**< 2 bytes) - checksum of entire module_download_header (except itself) */
    

} lc_module_dlh_st;

/* Module header structure */
typedef struct  _lc_module_mh_st
{
    lc_uint16 module_id; /**< (2 bytes) - variable */
    
    lc_bool compressed; /**< (1 bit) - This field is set to 1 if this module is compressed. */
    lc_bool obscured; /**< (1 bit) - This field is set to 1 if this module is obscured. */
    lc_bool encrypted; /**< (1 bit) - This field is set to 1 if this module is encrypted. */

    lc_uchar reserved; /**< (5 bits) - variable */
  
    lc_uint32 original_size; /**< (4 bytes) - This is the original size of this module. */
  
    lc_uint32 compressed_size; /**< (4 bytes) - This is the size of the compressed module. */
    lc_uint32 crc32; /**< (4 bytes) - This is the CRC_32 of the compressed module. */
  
    lc_uint16 block_size; /**< (2 bytes) - This is the size of the datagrams in this module. */
    lc_uint16 block_count; /**< (2 bytes) - This is the number of datagrams in this module. */
    lc_uint16 crc16; /**< 2 bytes) - checksum of entire module_header (except itself) */
  
} lc_module_mh_st;

/* Module datagram parameters */
typedef struct  _lc_module_dg_st
{
    lc_uint16 module_id; /**< (2 bytes) - variable */
    lc_uint16 data_length; /**< (2 bytes) - byte length of data_byte (except itself) */
    lc_uchar* data_byte; /**< (n bytes) - payload of datagram (except itself) */
    lc_uint16 crc16; /**< (2 bytes) - checksum of entire datagram (except itself) */
    
} lc_module_dg_st;


/* module_info_header stucture */
typedef struct _lc_module_info_header
{
    lc_uint16 module_id; /**< (2 bytes) - variable */
    lc_uint16 header_length; /**< (2 bytes) - size byte of the entire module_info_header */
    lc_uint32 module_size; /**< (4 bytes) - variable */

    /* segments below are not applicable for BBCB, Loader Core and Loader Partition */
    lc_uchar boot_check; /**< (1 bit) - If set to 0b1, this module shall be checked 
                            against its signature during boot */
    lc_uchar addressable; /**< (1 bit) - If set to 0b1, this module is an addressable 
                            module and shall be stored in the set-top box at 
                            the specified address in start_address. */
    lc_uchar reserved; /**< (6 bits) - variable */
    lc_uint16 module_version; /**< (2 bytes) - variable */
    lc_uint16 variant; /**< (2 bytes) - variable */
    lc_uint16 sub_variant; /**< (2 bytes) - variable, can be used to map IUC spatial 
                                variant, if set to 0,sub-variant should be ignord. */
    lc_uint16 download_sequence_number; /**< (2 bytes) - variable */
    lc_uchar memory_type; /**< (1 byte) - The type of memory this module is to be stored in. */
    lc_uint32 start_address; /**< (4 bytes) - If addressable is set to 1 this field will 
                                contain the start address of the memory space this module 
                                is to be stored in. */
                                
    lc_uint16 header_signature_length; /**< (2 bytes) - length of module_info_header signature */
    lc_uchar *header_signature_data; /**< (n bytes) - This is the signature for the above fields in 
                                    the module_info_header, n = header_signature_length */

    lc_uint16 module_signature_length; /**< (2 bytes) - length of globle module signature */
    lc_uchar *module_signature; /**< (n bytes) - This is the signature for the module, 
                                    n = module_signature_length */

    lc_uint32 crc32; /**< 4 bytes) - checksum of entire module_info_header (except itself) */
} lc_module_info_header; 

/* BBCB format */
typedef struct _lc_bbcb_st
{
    lc_uchar OUI[3]; /**< (3 bytes) - contains an IEEE OUI */
    lc_uint16 manufacturer_id; /**< (2 bytes) - variable */ 
    lc_uint16 hardware_version; /**< (2 bytes) - variable */
    lc_uchar loader_major_version; /**< (1 byte) - must be 0x05 */
    lc_uchar loader_minor_version; /**< (1 byte) - variable */
    lc_uint16 loader_version_buildnumber; /**< (2 bytes) - variable */ 
    lc_uchar boot_check_algorithm; /**< (1 byte) - 0x00 refers to CRC32; 
                                                  0x01 refers to MAC
                                                  0x02 refers to RSASSA-PKCS1-v1_5
                                                  0x03~0xff reserved  */
    lc_uchar serial_number[4]; /**< (4 bytes) - variable */
    lc_uchar random_number[4]; /**< (4 bytes) - variable */
    lc_uint32 crc32; /**< (4 bytes) - the checksum of the entire boot block (except itself). */
    
} lc_bbcb_st;


/** download parameters for IP multicast download */
typedef struct _lc_ip_dl_info_st
{
    lc_uint32 address; /**< (4 bytes) - IP address formatted as host byte array. */
    lc_uint16 port; /**< (2 bytes) - port number formatted as host byte array. */
    
} lc_ip_dl_info_st;

/** download parameters for DVB-SSU download */
typedef struct _lc_dvbssu_dl_info_st
{
    lc_uint16 pid; /**< (13 bits) - PID of download stream (ISO/IEC 13818-6 type B). */
    
} lc_dvbssu_dl_info_st;


/** download parameters for OTA download. */
typedef struct _lc_ota_dl_para_st
{
    lc_ip_dl_info_st ipInfo;    
    lc_dvbssu_dl_info_st dvbssuInfo;
    lc_uchar privateInfo[LC_MANUFACTURER_PRIVATE_INFO_LENGTH]; /**< Reserved space to hold manufacturer's private info for download. */
    
    lc_uint32 crc32; /**< (4 bytes) - the checksum of the fields above. */
    
} lc_ota_dl_para_st;

/** parameters for migration. */
typedef struct _lc_migration_info_st
{
    lc_uint16 variant;  /**< (2 bytes) - variant for Migration */ 
    lc_uint16 subvariant; /**< (2 bytes) - sub-variant for Migration */ 
} lc_migration_info_st;


/** 
 *  shared memory stored in Loader partition for sharing messages between Loader Core 
 *  and STB high-level application. 
 */
typedef struct _lc_shared_memory_st
{

    lc_uchar downloadIndicator; /**< (1 byte) - [7:4], 0x1 for download available, 
                                                      other for download unavailable.
                                               [3:0], 0x1 for Serial download, 
                                                      0x2 for OTA download, 
                                                      others reserved. */
    lc_uchar reserved;  /** (1 byte) - reserved. */
    lc_ota_dl_para_st otaDownloadPara; /** parameters for OTA download */
    lc_migration_info_st migrationInfo; /** variant & sub-variant for migration use. */
            
} lc_shared_memory_st;


/** latest download information stored in Loader Partition. */
typedef struct _lc_last_download_info_st
{
    lc_char isign_version[4]; /**< (4 bytes) - variable */
    lc_char isign_serial_number[4]; /**< (4 bytes) - variable */
    
    lc_uint16 download_sequence_number; /**< (2 bytes) - variable */
    
    lc_uint32 crc32; /**< (4 bytes) - the checksum of the entire download info segment (except itself). */
    
} lc_last_download_info_st;


/** high-level structure of Loader Partition. */
typedef struct _lc_loader_pt_st
{
    lc_shared_memory_st sharedMemory;
    lc_last_download_info_st downloadInfo;
    
} lc_loader_pt_st;


lc_result
MessageParser_ReadBits(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_uint32 bitlength,
    void *pDest);

lc_result
MessageParser_ReadBytes(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBytePos, 
    lc_uint32 bytelength,
    void *pDest);


void N2H16(lc_uint16 *pNbo);
void N2H32(lc_uint32 *pNbo);

lc_result
MessageCombiner_WriteBits(
    const lc_buffer_st *pBytes,
    lc_uint32 *pBitPos,
    lc_uint32 bitlength,
    const void *pSrc );

void H2N16(lc_uint16 *pNbo);    
void H2N32(lc_uint32 *pNbo);


lc_uint32 LC_GetUint32(const lc_uchar* pBufffer, lc_uint32 offset);
lc_uint16 LC_GetUint16(const lc_uchar* pBufffer, lc_uint32 offset);



/* download protocol */

/** 
 * Parse download header.
 */
lc_result
MessageParser_ParseDPDownloadHeader(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_module_dlh_st *pParsed);

/** 
 * Free memory allocated in MessageParser_ParseDPDownloadHeader.
 */    
lc_result
MessageParser_FreeDPDownloadHeader( 
    lc_module_dlh_st *pParsed);


/** 
 * Parse module header.
 */
lc_result
MessageParser_ParseDPModuleHeader(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_module_mh_st *pParsed);

/** 
 * Parse datagram.
 */
lc_result
MessageParser_ParseDPDatagram(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_module_dg_st *pParsed);

lc_result
MessageParser_ParseDPDatagramBytes(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBytePos, 
    lc_module_dg_st *pParsed);

/** 
 * Parse module info header.
 */
lc_result
MessageParser_ParseModuleInfoHeader(
    lc_bool atDownloadPhase, 
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_module_info_header *pParsed);

/** 
 * Free memory allocated in MessageParser_ParseModuleInfoHeader.
 */
lc_result
MessageParser_FreeModuleInfoHeader( 
    lc_module_info_header *pParsed);

/** 
 * Combine a module info header.
 */
lc_result
MessageCombiner_CombineModuleInfoHeader(
    const lc_buffer_st *pBytes,
    lc_uint32 *pBitPos,
    const lc_module_info_header *pParsed);


/** 
 * Parse BBCB.
 */
lc_result
MessageParser_ParseBBCB(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_bbcb_st *pParsed);

/** 
 * Parse OTA download parameter field stored in Loader Partition.
 */
lc_result
MessageParser_ParseOtaDownloadParameters(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_ota_dl_para_st *pParsed);

/** 
 * Combine OTA download parameter field stored in Loader Partition.
 */
lc_result
MessageCombiner_CombineOtaDownloadParameters(
    lc_buffer_st *pBytes,
    lc_uint32 *pBitPos,
    lc_ota_dl_para_st *pParsed);

/** 
 * Parse shared memory field stored in Loader Partition.
 */
lc_result
MessageParser_ParseSharedMemory(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_shared_memory_st *pParsed);

/** 
 * Combine shared memory field stored in Loader Partition.
 */
lc_result
MessageCombiner_CombineSharedMemory(
    lc_buffer_st *pBytes,
    lc_uint32 *pBitPos,
    lc_shared_memory_st *pParsed);    


/** 
 * Parse Loader Partition.
 */
lc_result
MessageParser_ParseLoaderPt(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_loader_pt_st *pParsed);    

/** 
 * Parse latest download information field stored in Loader Partition.
 */
lc_result
MessageParser_ParseDownloadInfo(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_last_download_info_st *pParsed);

/** 
 * Combine latest download information field stored in Loader Partition.
 */
lc_result
MessageCombiner_CombineDownloadInfo( 
    lc_buffer_st *pBytes,
    lc_uint32 *pBitPos,
    lc_last_download_info_st *pParsed);    



/* UART download */

/** 
 * Parse UART download packet.
 */
lc_result
MessageParser_ParseSDPSerialDownloadPacket(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBitPos, 
    lc_serial_download_packet *pParsed);

lc_result
MessageParser_ParseSDPSerialDownloadPacketBytes(
    const lc_buffer_st *pBytes, 
    lc_uint32 *pBytesPos, 
    lc_serial_download_packet *pParsed);


#ifdef __cplusplus
}
#endif

#endif /* BIT_H__INCLUDED__ */

