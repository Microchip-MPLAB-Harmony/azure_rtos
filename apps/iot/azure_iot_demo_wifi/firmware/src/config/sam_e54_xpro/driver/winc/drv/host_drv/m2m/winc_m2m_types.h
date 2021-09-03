/**
 *
 * \file
 *
 * \brief WINC Application Interface Types.
 *
 * Copyright (c) 2021 Microchip Technology Inc. and its subsidiaries.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Subject to your compliance with these terms, you may use Microchip
 * software and any derivatives exclusively with Microchip products.
 * It is your responsibility to comply with third party license terms applicable
 * to your use of third party software (including open source software) that
 * may accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
 * INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP BE
 * LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE
 * SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE
 * POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY
 * RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
 * THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#ifndef _M2M_TYPES_H_
#define _M2M_TYPES_H_

/*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
MACROS
*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*/
/**@addtogroup  VERSIONDEF
 */
/**@{*/
#define M2M_MAJOR_SHIFT (8)
#define M2M_MINOR_SHIFT (4)
#define M2M_PATCH_SHIFT (0)

#define M2M_DRV_VERSION_SHIFT (16)
#define M2M_FW_VERSION_SHIFT (0)

#define M2M_GET_MAJOR(ver_info_hword) ((uint8_t)((ver_info_hword) >> M2M_MAJOR_SHIFT) & 0xff)
#define M2M_GET_MINOR(ver_info_hword) ((uint8_t)((ver_info_hword) >> M2M_MINOR_SHIFT) & 0x0f)
#define M2M_GET_PATCH(ver_info_hword) ((uint8_t)((ver_info_hword) >> M2M_PATCH_SHIFT) & 0x0f)

#define M2M_GET_FW_VER(ver_info_word)  ((uint16_t) ((ver_info_word) >> M2M_FW_VERSION_SHIFT))
#define M2M_GET_DRV_VER(ver_info_word) ((uint16_t) ((ver_info_word) >> M2M_DRV_VERSION_SHIFT))

#define M2M_GET_DRV_MAJOR(ver_info_word) M2M_GET_MAJOR(M2M_GET_DRV_VER(ver_info_word))
#define M2M_GET_DRV_MINOR(ver_info_word) M2M_GET_MINOR(M2M_GET_DRV_VER(ver_info_word))
#define M2M_GET_DRV_PATCH(ver_info_word) M2M_GET_PATCH(M2M_GET_DRV_VER(ver_info_word))

#define M2M_GET_FW_MAJOR(ver_info_word) M2M_GET_MAJOR(M2M_GET_FW_VER(ver_info_word))
#define M2M_GET_FW_MINOR(ver_info_word) M2M_GET_MINOR(M2M_GET_FW_VER(ver_info_word))
#define M2M_GET_FW_PATCH(ver_info_word) M2M_GET_PATCH(M2M_GET_FW_VER(ver_info_word))

#define M2M_MAKE_VERSION(major, minor, patch) ( \
    ((uint16_t)((major)  & 0xff)  << M2M_MAJOR_SHIFT) | \
    ((uint16_t)((minor)  & 0x0f)  << M2M_MINOR_SHIFT) | \
    ((uint16_t)((patch)  & 0x0f)  << M2M_PATCH_SHIFT))

#define M2M_MAKE_VERSION_INFO(fw_major, fw_minor, fw_patch, drv_major, drv_minor, drv_patch) \
    ( \
    ( ((uint32_t)M2M_MAKE_VERSION((fw_major),  (fw_minor),  (fw_patch)))  << M2M_FW_VERSION_SHIFT) | \
    ( ((uint32_t)M2M_MAKE_VERSION((drv_major), (drv_minor), (drv_patch))) << M2M_DRV_VERSION_SHIFT))

/*======*======*======*======*
        FIRMWARE VERSION NO INFO
 *======*======*======*======*/

#define M2M_RELEASE_VERSION_MAJOR_NO                        (19)
/*!< Firmware Major release version number. */

#define M2M_RELEASE_VERSION_MINOR_NO                        (7)
/*!< Firmware Minor release version number. */

#define M2M_RELEASE_VERSION_PATCH_NO                        (3)
/*!< Firmware patch release version number. */

/*======*======*======*======*
  SUPPORTED DRIVER VERSION NO INFO
 *======*======*======*======*/

#define M2M_MIN_REQ_DRV_VERSION_MAJOR_NO                        (19)
/*!< Driver Major release version number. */

#define M2M_MIN_REQ_DRV_VERSION_MINOR_NO                        (3)
/*!< Driver Minor release version number. */

#define M2M_MIN_REQ_DRV_VERSION_PATCH_NO                        (0)
/*!< Driver patch release version number. */

#if !defined(M2M_RELEASE_VERSION_MAJOR_NO) || !defined(M2M_RELEASE_VERSION_MINOR_NO)
#error Undefined version number
#endif

/**@}*/     // VERSIONDEF

/**@addtogroup  WLANDefines
 * @{
 */

#define M2M_BUFFER_MAX_SIZE                             (1600UL - 4)
/*!< Maximum size for the shared packet buffer. */

#define M2M_MAC_ADDRES_LEN                              6
/*!< The size of the 802 MAC address. */

#define M2M_ETHERNET_HDR_OFFSET                         34
/*!< The offset of the Ethernet header within the WLAN Tx Buffer. */

#define M2M_ETHERNET_HDR_LEN                            14
/*!< Length of the Ethernet header in bytes. */

#define M2M_MAX_SSID_LEN                                33
/*!< 1 more than the max SSID length.
    This matches the size of SSID buffers (max SSID length + 1-byte length field).
 */

#define M2M_MAX_PSK_LEN                                 65
/*!< 1 more than the WPA PSK length (in ASCII format).
    This matches the size of the WPA PSK/Passphrase buffer (max ASCII contents + 1-byte length field).
    Alternatively it matches the WPA PSK length (in ASCII format) + 1 byte NULL termination.
 */

#define M2M_MIN_PSK_LEN                                 9
/*!< 1 more than the minimum WPA PSK Passphrase length.
    It matches the minimum WPA PSK Passphrase length + 1 byte NULL termination.
 */

#define M2M_DEVICE_NAME_MAX                             48
/*!< Maximum Size for the device name including the NULL termination. */

#define M2M_NTP_MAX_SERVER_NAME_LENGTH                  32
/*!< Maximum NTP server name length */

#define M2M_LISTEN_INTERVAL                             1
/*!< The STA uses the Listen Interval parameter to indicate to the AP how
    many beacon intervals it shall sleep before it retrieves the queued frames
    from the AP.
*/

#define MAX_HIDDEN_SITES                                4
/*!< Max number of hidden SSID supported by scan request */

#define M2M_CUST_IE_LEN_MAX                             252
/*!< The maximum size of IE (Information Element). */

#define M2M_CRED_STORE_FLAG                             0x01
/*!< Flag used in @ref tstrM2mConnCredHdr to indicate that WiFi connection
    credentials should be stored in WINC flash.
*/
#define M2M_CRED_ENCRYPT_FLAG                           0x02
/*!< Flag used in @ref tstrM2mConnCredHdr to indicate that WiFi connection
    credentials should be encrypted when stored in WINC flash.
*/
#define M2M_CRED_IS_STORED_FLAG                         0x10
/*!< Flag used in @ref tstrM2mConnCredHdr to indicate that WiFi connection
    credentials are stored in WINC flash. May only be set by WINC firmware.
*/
#define M2M_CRED_IS_ENCRYPTED_FLAG                      0x20
/*!< Flag used in @ref tstrM2mConnCredHdr to indicate that WiFi connection
    credentials are encrypted in WINC flash. May only be set by WINC firmware.
*/

#define M2M_WIFI_CONN_BSSID_FLAG                        0x01
/*!< Flag used in @ref tstrM2mConnCredCmn to indicate that WiFi connection
    must be restricted to an AP with a certain BSSID.
*/

#define M2M_AUTH_1X_USER_LEN_MAX                        100
/*!< The maximum length (in ASCII characters) of domain name + username (including '@' or '\')
    for authentication with Enterprise methods.
*/
#define M2M_AUTH_1X_PASSWORD_LEN_MAX                    256
/*!< The maximum length (in ASCII characters) of password for authentication with Enterprise MSCHAPv2 methods. */
#define M2M_AUTH_1X_PRIVATEKEY_LEN_MAX                  256
/*!< The maximum length (in bytes) of private key modulus for authentication with Enterprise TLS methods.
    Private key exponent must be the same length as modulus, pre-padded with 0s if necessary.
*/
#define M2M_AUTH_1X_CERT_LEN_MAX                        1584
/*!< The maximum length (in bytes) of certificate for authentication with Enterprise TLS methods. */

#define M2M_802_1X_UNENCRYPTED_USERNAME_FLAG            0x80
/*!< Flag to indicate that the 802.1x user-name should be sent (unencrypted) in the initial EAP
    identity response. Intended for use with EAP-TLS only.
*/
#define M2M_802_1X_PREPEND_DOMAIN_FLAG                  0x40
/*!< Flag to indicate that the 802.1x domain name should be prepended to the user-name:
    "Domain\Username". If the flag is not set then domain name is appended to the user-name:
    "Username@Domain". (Note that the '@' or '\' must be included in the domain name.)
*/
#define M2M_802_1X_MSCHAP2_FLAG                         0x01
/*!< Flag to indicate 802.1x MsChapV2 credentials: domain/user-name/password. */
#define M2M_802_1X_TLS_FLAG                             0x02
/*!< Flag to indicate 802.1x TLS credentials: domain/user-name/private-key/certificate. */

#define M2M_802_1X_TLS_CLIENT_CERTIFICATE               1
/*!< Info type used in @ref tstrM2mWifiAuthInfoHdr to indicate Enterprise TLS client certificate. */

#define PSK_CALC_LEN                                    40
/*!< PSK is 32 bytes generated either:
    - from 64 ASCII characters
    - by SHA1 operations on up to 63 ASCII characters
    40 byte array is required during SHA1 operations, so we define PSK_CALC_LEN as 40.
*/

/*********************
 *
 * WIFI GROUP requests
 */

#define M2M_CONFIG_CMD_BASE                                 1
/*!< The base value of all the host configuration commands opcodes. */
#define M2M_STA_CMD_BASE                                    40
/*!< The base value of all the station mode host commands opcodes. */
#define M2M_AP_CMD_BASE                                     70
/*!< The base value of all the Access Point mode host commands opcodes. */
#define M2M_SERVER_CMD_BASE                                 100
/*!< The base value of all the power save mode host commands codes. */
#define M2M_GEN_CMD_BASE                                    105
/*!< The base value of additional host WiFi command opcodes.
 * Usage restrictions (eg STA mode only) should always be made clear at the API layer in any case.
*/
/**********************
 * OTA GROUP requests
 */
#define M2M_OTA_CMD_BASE                                    100
/*!< The base value of all the OTA mode host commands opcodes.
 * The OTA Have special group so can extended from 1-M2M_MAX_GRP_NUM_REQ
*/
/***********************
 *
 * CRYPTO group requests
 */
#define M2M_CRYPTO_CMD_BASE                                 1
/*!< The base value of all the crypto mode host commands opcodes.
 * The crypto Have special group so can extended from 1-M2M_MAX_GRP_NUM_REQ
*/

#define M2M_MAX_GRP_NUM_REQ                                 (127)
/*!< Max number of request in one group equal to 127 as the last bit reserved for config or data pkt */

#define WEP_40_KEY_SIZE                                     (5)
/*!< The size in bytes of a 40-bit wep key. */
#define WEP_104_KEY_SIZE                                    (13)
/*!< The size in bytes of a 104-bit wep key. */

#define WEP_40_KEY_STRING_SIZE                              (10)
/*!< The string length of a 40-bit wep key. */
#define WEP_104_KEY_STRING_SIZE                             (26)
/*!< The string length of a 104-bit wep key. */

#define WEP_KEY_MAX_INDEX                                   (4)
/*!< WEP key index is in the range 1 to 4 inclusive. (This is decremented to
 * result in an index in the range 0 to 3 on air.)
*/
#define M2M_SHA256_CONTEXT_BUFF_LEN                         (128)
/*!< SHA256 context size */
#define M2M_SCAN_DEFAULT_NUM_SLOTS                          (2)
/*!< The default number of scan slots used by the WINC board. */
#define M2M_SCAN_DEFAULT_SLOT_TIME                          (30)
/*!< The default duration in milliseconds of an active scan slot used by the WINC board. */
#define M2M_SCAN_DEFAULT_PASSIVE_SLOT_TIME                  (300)
/*!< The passive scan slot default duration in ms. */
#define M2M_SCAN_DEFAULT_NUM_PROBE                          (2)
/*!< The default number of probes per scan slot. */
#define M2M_FASTCONNECT_DEFAULT_RSSI_THRESH                 (-45)
/*!< The default threshold RSSI for fast reconnection to an AP. */

/*======*======*======*======*
    TLS DEFINITIONS
 *======*======*======*======*/
#define TLS_FILE_NAME_MAX                               48
/*!< Maximum length for each TLS certificate file name including null terminator. */
#define TLS_SRV_SEC_MAX_FILES                           8
/*!< Maximum number of certificates allowed in TLS_SRV section. */
#define TLS_SRV_SEC_START_PATTERN_LEN                   8
/*!< Length of certificate struct start pattern. */

/*======*======*======*======*
    SSL DEFINITIONS
 *======*======*======*======*/

#define TLS_CRL_DATA_MAX_LEN    64
/*<!
    Maximum data length in a CRL entry (= Hash length for SHA512)
*/
#define TLS_CRL_MAX_ENTRIES     10
/*<!
    Maximum number of entries in a CRL
*/

#define TLS_CRL_TYPE_NONE       0
/*<!
    No CRL check
*/
#define TLS_CRL_TYPE_CERT_HASH  1
/*<!
    CRL contains certificate hashes
*/

/* Commonly used initializers for rate lists for B, G, N or mixed modes for iteration on rates. */
#define WLAN_11B_RATES_INITIALIZER { \
    TX_RATE_1, TX_RATE_2, TX_RATE_5_5, \
    TX_RATE_11 \
}

#define WLAN_11G_RATES_INITIALIZER  { \
    TX_RATE_6, TX_RATE_9, TX_RATE_12, \
    TX_RATE_18, TX_RATE_24, TX_RATE_36, \
    TX_RATE_48, TX_RATE_54 \
}

#define WLAN_11N_RATES_INITIALIZER { \
    TX_RATE_MCS_0, TX_RATE_MCS_1, TX_RATE_MCS_2, \
    TX_RATE_MCS_3, TX_RATE_MCS_4, TX_RATE_MCS_5, \
    TX_RATE_MCS_6, TX_RATE_MCS_7 \
}

#define WLAN_11BGN_RATES_ASC_INITIALIZER { \
    TX_RATE_1, TX_RATE_2, TX_RATE_5_5, \
    TX_RATE_6, TX_RATE_MCS_0, TX_RATE_9, \
    TX_RATE_11, TX_RATE_12, TX_RATE_MCS_1, \
    TX_RATE_18, TX_RATE_MCS_2, TX_RATE_24, \
    TX_RATE_MCS_3, TX_RATE_36, TX_RATE_MCS_4, \
    TX_RATE_48, TX_RATE_MCS_5, TX_RATE_54, \
    TX_RATE_MCS_6, TX_RATE_MCS_7, \
}

#define WLAN_11BG_RATES_ASC_INITIALIZER { \
     TX_RATE_1, TX_RATE_2, TX_RATE_5_5, \
     TX_RATE_6, TX_RATE_9, TX_RATE_11, \
     TX_RATE_12, TX_RATE_18, TX_RATE_24, \
     TX_RATE_36, TX_RATE_48, TX_RATE_54 \
}

#define DEFAULT_CONF_AR_INITIALIZER { 5, 1, TX_RATE_AUTO, TX_RATE_AUTO, 10, 5, 3 }

/**@}*/     // WLANDefines

/**@addtogroup OTADEFINE
 * @{
 */

/*======*======*======*======*
    OTA DEFINITIONS
 *======*======*======*======*/

#define OTA_STATUS_VALID                    (0x12526285)
/*!< Magic value in the control structure for a valid image after ROLLBACK. */
#define OTA_STATUS_INVALID                  (0x23987718)
/*!< Magic value in the control structure for a invalid image after ROLLBACK. */
#define OTA_MAGIC_VALUE                     (0x1ABCDEF9)
/*!< Magic value set at the beginning of the OTA image header. */
#define OTA_FORMAT_VER_0                    (0)
/*!<
    Control structure format version 0.\n
    Format used until version 19.2.2.
*/
#define OTA_FORMAT_VER_1                    (1)
/*!<
    Control structure format version 1.\n
    Starting from 19.3.0 CRC is used and sequence number is used.
*/
#define OTA_FORMAT_VER_2                    (2)
/*!<
    Control structure format version 2.\n
    Starting from 19.6.1 a flexible flash map is used.
*/
#define OTA_SHA256_DIGEST_SIZE              (32)
/*!<
    SHA256 digest size in the OTA image.
    The SHA256 digest is set at the beginning of image before the OTA header.
 */

#define MAX_FILE_READ_STEP                  128
/*!< Max amount of bytes to read a file via HIF messages. */

#define HFD_INVALID_HANDLER                 (0xff)
/*!< Defines an ID which symbolizes an invalid handler. */
/**@}*/     // OTADEFINE

#define tstrM2MSNTPConfig_PAD (4 - ((M2M_NTP_MAX_SERVER_NAME_LENGTH + 1 + 1) % 4))

/**@addtogroup WLANEnums
 * @{
 */

typedef enum
{
    ENTRY_ID_FW         = 0x0011,
    ENTRY_ID_PLLGAIN    = 0x0021,
    ENTRY_ID_TLSROOT    = 0x0031,
    ENTRY_ID_TLSCLIENT  = 0x0032,
    ENTRY_ID_TLSSERVER  = 0x0033,
    ENTRY_ID_CONNPARAMS = 0x0034,
    ENTRY_ID_HTTPFILES  = 0x0035,
    ENTRY_ID_TLSCOMMON  = 0x0036,
    ENTRY_ID_HOSTFILE   = 0x0041
} tenuFlashLUTEntryID;

/*!
@enum       tenuM2mDefaultConnErrcode

@brief

*/
typedef enum
{
    M2M_DEFAULT_CONN_INPROGRESS = (-23),
    /*!< Failure response due to another connection being already in progress */
    M2M_DEFAULT_CONN_FAIL,
    /*!< Failure to connect to the cached network */
    M2M_DEFAULT_CONN_SCAN_MISMATCH,
    /*!< Failure to find any of the cached networks in the scan results. */
    M2M_DEFAULT_CONN_EMPTY_LIST
    /*!< Failure due to empty network list. */
} tenuM2mDefaultConnErrcode;

/*!
@enum       tenuM2mConnChangedErrcode

@brief
*/
typedef enum
{
    M2M_ERR_SCAN_FAIL = (1),
    /*!< Failure to perform the scan operation. */
    M2M_ERR_JOIN_FAIL,
    /*!< Failure to join the BSS. */
    M2M_ERR_AUTH_FAIL,
    /*!< Failure to authenticate with the AP. */
    M2M_ERR_ASSOC_FAIL,
    /*!< Failure to associate with the AP. */
    M2M_ERR_CONN_INPROGRESS
    /*!< Failure due to another connection being in progress. */
} tenuM2mConnChangedErrcode;

/*!
@enum       tenuM2mWepKeyIndex

@brief
*/
typedef enum
{
    M2M_WIFI_WEP_KEY_INDEX_1 = (1),
    /*!< Index 1 for WEP key Authentication */
    M2M_WIFI_WEP_KEY_INDEX_2,
    /*!< Index 2 for WEP key Authentication */
    M2M_WIFI_WEP_KEY_INDEX_3,
    /*!< Index 3 for WEP key Authentication */
    M2M_WIFI_WEP_KEY_INDEX_4
    /*!< Index 4 for WEP key Authentication */
} tenuM2mWepKeyIndex;

/*!
@enum       tenuM2mPwrMode

@brief
*/
typedef enum
{
    PWR_AUTO = (1),
    /*!< Firmware will decide the best power mode to use internally. */
    PWR_LOW1,
    /*!< Low power mode #1 */
    PWR_LOW2,
    /*!< Low power mode #2 */
    PWR_HIGH
    /*!< High power mode */
} tenuM2mPwrMode;

/*!
@struct     tstrM2mPwrMode

@brief
            This struct stores the Power Save modes.
*/
typedef struct
{
    uint8_t u8PwrMode;
    /*!< Power Save Mode */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mPwrMode;

/*!
@enum       tenuM2mTxPwrLevel

@brief
*/
typedef enum
{
    TX_PWR_HIGH = (1),
    /*!< PPA Gain 6dbm  PA Gain 18dbm */
    TX_PWR_MED,
    /*!< PPA Gain 6dbm  PA Gain 12dbm */
    TX_PWR_LOW
    /*!< PPA Gain 6dbm  PA Gain 6dbm */
} tenuM2mTxPwrLevel;

/*!
@struct     tstrM2mTxPwrLevel

@brief
            This struct stores the Tx Power levels.
*/
typedef struct
{
    uint8_t u8TxPwrLevel;
    /*!< Tx power level */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mTxPwrLevel;

/*!
@struct     tstrM2mWiFiGainIdx

@brief
            Gain Table index selection corresponding to specific WiFi region.
*/
typedef struct
{
    uint8_t u8GainTableIdx;
    /*!< Gain table index */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mWiFiGainIdx;

/*!
@struct     tstrM2mEnableLogs

@brief
            This struct stores logging information.
*/
typedef struct
{
    uint8_t u8Enable;
    /*!< Enable/disable firmware logs */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mEnableLogs;

/*!
@struct     tstrM2mBatteryVoltage

@brief
            This struct stores the battery voltage.
*/
typedef struct
{
    //Note: on SAMD D21 the size of double is 8 Bytes
    uint16_t u16BattVolt;
    /*!< Battery Voltage */
    uint8_t  __PAD16__[2];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mBatteryVoltage;

/*!
@struct     tstrM2mWiFiRoaming

@brief
            Roaming related information.
*/
typedef struct
{
    uint8_t u8EnableRoaming;
    /*!< Enable/Disable Roaming */
    uint8_t u8EnableDhcp;
    /*!< Enable/Disable DHCP client when u8EnableRoaming is true */
    uint8_t __PAD16__[2];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mWiFiRoaming;

/*!
@struct     tstrM2mWiFiXOSleepEnable

@brief
            Choose to keep the XO on or off over deep sleep.
*/
typedef struct
{
    uint8_t u8EnableXODuringSleep;
    /*!< Enable/Disable XO during deep sleep */
    uint8_t __PAD16__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mWiFiXOSleepEnable;

/*!
@enum       tenuM2mReqGroup

@brief
*/
typedef enum
{
    M2M_REQ_GROUP_MAIN = 0,
    M2M_REQ_GROUP_WIFI,
    M2M_REQ_GROUP_IP,
    M2M_REQ_GROUP_HIF,
    M2M_REQ_GROUP_OTA,
    M2M_REQ_GROUP_SSL,
    M2M_REQ_GROUP_CRYPTO,
    M2M_REQ_GROUP_SIGMA,
    M2M_REQ_GROUP_INTERNAL
} tenuM2mReqGroup;

/*!
@enum       tenuM2mReqpkt

@brief
*/
typedef enum
{
    M2M_REQ_CONFIG_PKT,
    M2M_REQ_DATA_PKT = 0x80 /*BIT7*/
} tenuM2mReqpkt;

/*!
@enum       tenuM2mConfigCmd

@brief
            This enum contains host commands used to configure the WINC board.

*/
typedef enum
{
    M2M_WIFI_REQ_RESTART = M2M_CONFIG_CMD_BASE,
    /*!< Restart the WINC MAC layer, it's doesn't restart the IP layer. */
    M2M_WIFI_REQ_SET_MAC_ADDRESS,
    /*!< Set the WINC mac address (not possible for production effused boards). */
    M2M_WIFI_REQ_CURRENT_RSSI,
    /*!< Request the current connected AP RSSI. */
    M2M_WIFI_RESP_CURRENT_RSSI,
    /*!< Response to M2M_WIFI_REQ_CURRENT_RSSI with the RSSI value. */
    M2M_WIFI_REQ_GET_CONN_INFO,
    /*!< Request connection information. */
    M2M_WIFI_RESP_CONN_INFO,
    /*!< Response to M2M_WIFI_REQ_GET_CONN_INFO with the connection information. */
    M2M_WIFI_REQ_SET_DEVICE_NAME,
    /*!< Request to set WINC device name property. */
    M2M_WIFI_REQ_START_PROVISION_MODE,
    /*!< Request to start provisioning mode. */
    M2M_WIFI_RESP_PROVISION_INFO,
    /*!< Response to the host with the provisioning information.*/
    M2M_WIFI_REQ_STOP_PROVISION_MODE,
    /*!< Request to stop provision mode. */
    M2M_WIFI_REQ_SET_SYS_TIME,
    /*!< Request to set system time. */
    M2M_WIFI_REQ_ENABLE_SNTP_CLIENT,
    /*!<
        Request to enable the simple network time protocol to get the
        time from the Internet. This is required for security purposes.
    */
    M2M_WIFI_REQ_DISABLE_SNTP_CLIENT,
    /*!<
        Request to disable the simple network time protocol for applications that
        do not need it.
    */
    M2M_WIFI_RESP_MEMORY_RECOVER,
    /*!< Reserved for debugging */
    M2M_WIFI_REQ_CUST_INFO_ELEMENT,
    /*!< Request to add custom information to the Beacons IE. */
    M2M_WIFI_REQ_SCAN,
    /*!< Request scan command. */
    M2M_WIFI_RESP_SCAN_DONE,
    /*!< Response to notify scan complete. */
    M2M_WIFI_REQ_SCAN_RESULT,
    /*!< Request for scan results. */
    M2M_WIFI_RESP_SCAN_RESULT,
    /*!< Response to provide the scan results.  */
    M2M_WIFI_REQ_SET_SCAN_OPTION,
    /*!< Request to set scan options "slot time, slot number .. etc".   */
    M2M_WIFI_REQ_SET_SCAN_REGION,
    /*!< Request to set scan region. */
    M2M_WIFI_REQ_SET_POWER_PROFILE,
    /*!< Request to set the Power Profile. */
    M2M_WIFI_REQ_SET_TX_POWER,
    /*!< Request to set the TX Power. */
    M2M_WIFI_REQ_SET_BATTERY_VOLTAGE,
    /*!< Request to set the Battery Voltage. */
    M2M_WIFI_REQ_SET_ENABLE_LOGS,
    /*!< Request to enable logs. */
    M2M_WIFI_REQ_GET_SYS_TIME,
    /*!< Request to get system time. */
    M2M_WIFI_RESP_GET_SYS_TIME,
    /*!< Response to retrieve the system time. */
    M2M_WIFI_REQ_SEND_ETHERNET_PACKET,
    /*!< Request to send Ethernet packet in bypass mode. */
    M2M_WIFI_RESP_ETHERNET_RX_PACKET,
    /*!< Response to receive an Ethernet packet in bypass mode. */
    M2M_WIFI_REQ_SET_MAC_MCAST,
    /*!< Request to set multicast filters. */
    M2M_WIFI_REQ_GET_PRNG,
    /*!< Request PRNG. */
    M2M_WIFI_RESP_GET_PRNG,
    /*!< Response for PRNG. */
    M2M_WIFI_REQ_SCAN_SSID_LIST,
    /*!< Request scan with list of hidden SSID plus the broadcast scan. */
    M2M_WIFI_REQ_SET_GAINS,
    /*!< Request to set the PPA gain */
    M2M_WIFI_REQ_PASSIVE_SCAN,
    /*!< Request a passive scan. */
    M2M_WIFI_REQ_CONG_AUTO_RATE,
    /*!< Configure auto TX rate selection algorithm. */
    M2M_WIFI_REQ_CONFIG_SNTP,
    /*!< Configure NTP servers. */
    M2M_WIFI_REQ_SET_GAIN_TABLE_IDX,
    /*!< API to set Gain table index. */
    M2M_WIFI_REQRSP_DELETE_APID,
    /*!< Request/response to delete AP security credentials from WINC flash. */
    /* This enum is now 'full' in the sense that (M2M_WIFI_REQRSP_DELETE_APID+1) == M2M_STA_CMD_BASE.
     * Any new config values should be placed in tenuM2mGenCmd. */
    M2M_WIFI_MAX_CONFIG_ALL
} tenuM2mConfigCmd;

/*!
@enum       tenuM2mStaCmd

@brief
            This enum contains WINC commands while in Station mode.
*/
typedef enum
{
    M2M_WIFI_REQ_CONNECT = M2M_STA_CMD_BASE,
    /*!< Request to connect with a specified AP. This command is deprecated in favour of @ref M2M_WIFI_REQ_CONN. */
    M2M_WIFI_REQ_DEFAULT_CONNECT,
    /*!< Request to connect with a cached AP. */
    M2M_WIFI_RESP_DEFAULT_CONNECT,
    /*!< Response for the default connect.*/
    M2M_WIFI_REQ_DISCONNECT,
    /*!< Request to disconnect from the AP. */
    M2M_WIFI_RESP_CON_STATE_CHANGED,
    /*!< Response to indicate a change in the connection state. */
    M2M_WIFI_REQ_SLEEP,
    /*!< Request to sleep. */
    M2M_WIFI_REQ_WPS_SCAN,
    /*!< Request to WPS scan. */
    M2M_WIFI_REQ_WPS,
    /*!< Request to start WPS. */
    M2M_WIFI_REQ_START_WPS,
    /*!< This command is for internal use by the WINC and
        should not be used by the host driver.
    */
    M2M_WIFI_REQ_DISABLE_WPS,
    /*!< Request to disable WPS. */
    M2M_WIFI_REQ_DHCP_CONF,
    /*!< Response to indicate the obtained IP address.*/
    M2M_WIFI_RESP_IP_CONFIGURED,
    /*!< This command is for internal use by the WINC and
        should not be used by the host driver.
    */
    M2M_WIFI_RESP_IP_CONFLICT,
    /*!< Response to indicate a conflict in obtained IP address.
        The user should re attempt the DHCP request.
    */
    M2M_WIFI_REQ_ENABLE_MONITORING,
    /*!< Request to enable monitor mode. */
    M2M_WIFI_REQ_DISABLE_MONITORING,
    /*!< Request to disable monitor mode. */
    M2M_WIFI_RESP_WIFI_RX_PACKET,
    /*!< Response to indicate a packet was received in monitor mode. */
    M2M_WIFI_REQ_SEND_WIFI_PACKET,
    /*!< Request to send a packet in monitor mode. */
    M2M_WIFI_REQ_LSN_INT,
    /*!< Request to set the listen interval. */
    M2M_WIFI_REQ_DOZE,
    /*!< Request to doze */
    M2M_WIFI_REQ_CONN,
    /*!< New command to connect with AP.
        This replaces M2M_WIFI_REQ_CONNECT. (Firmware continues to handle
        M2M_WIFI_REQ_CONNECT for backwards compatibility purposes.)
    */
    M2M_WIFI_IND_CONN_PARAM,
    /*!< Provide extra information (such as Enterprise client certificate) required for connection. */
    M2M_WIFI_REQ_DHCP_FAILURE,
    /*!< Response indicating that IP address could not be obtained or renewed. If the IP could not be renewed then the previous IP will continue to be used. */
    M2M_WIFI_MAX_STA_ALL
} tenuM2mStaCmd;

/*!
@enum       tenuM2mApCmd

@brief
            This enum contains WINC commands while in AP mode.
*/
typedef enum
{
    M2M_WIFI_REQ_ENABLE_AP = M2M_AP_CMD_BASE,
    /*!< Request to enable AP mode. */
    M2M_WIFI_REQ_DISABLE_AP,
    /*!< Request to disable AP mode. */
    M2M_WIFI_REQ_RESTART_AP,
    /*!<  */
    M2M_WIFI_MAX_AP_ALL
} tenuM2mApCmd;

/*!
@enum       tenuM2mServerCmd

@brief
            These commands are currently not supported.
*/
typedef enum
{
    M2M_WIFI_REQ_CLIENT_CTRL = M2M_SERVER_CMD_BASE,
    /*!< Currently not supported.*/
    M2M_WIFI_RESP_CLIENT_INFO,
    /*!< Currently not supported.*/
    M2M_WIFI_REQ_SERVER_INIT,
    /*!< Currently not supported.*/
    M2M_WIFI_MAX_SERVER_ALL
} tenuM2mServerCmd;

/*!
@enum       tenuM2mGenCmd

@brief
            This enum contains additional WINC commands (overflow of previous enums).
*/
typedef enum
{
    M2M_WIFI_REQ_ROAMING = M2M_GEN_CMD_BASE,
    /*!< Request to enable/disable WiFi roaming.
        (Processing matches @ref tenuM2mConfigCmd.)
    */
    M2M_WIFI_REQ_XO_SLEEP_ENABLE,
    /*!< Request to enable/disable the crystal oscillator during deep sleep.
        (Processing matches @ref tenuM2mConfigCmd.)
    */
    M2M_WIFI_REQ_SET_STOP_SCAN_OPTION,
    /*!< Set Scan option to stop on first result.
        (Processing matches @ref tenuM2mConfigCmd.)
    */
    M2M_WIFI_MAX_GEN_ALL
} tenuM2mGenCmd;

/*!
@enum       tenuM2mCryptoCmd

@brief
*/
typedef enum
{
    M2M_CRYPTO_REQ_SHA256_INIT = M2M_CRYPTO_CMD_BASE,
    M2M_CRYPTO_RESP_SHA256_INIT,
    M2M_CRYPTO_REQ_SHA256_UPDATE,
    M2M_CRYPTO_RESP_SHA256_UPDATE,
    M2M_CRYPTO_REQ_SHA256_FINISH,
    M2M_CRYPTO_RESP_SHA256_FINISH,
    M2M_CRYPTO_REQ_RSA_SIGN_GEN,
    M2M_CRYPTO_RESP_RSA_SIGN_GEN,
    M2M_CRYPTO_REQ_RSA_SIGN_VERIFY,
    M2M_CRYPTO_RESP_RSA_SIGN_VERIFY,
    M2M_CRYPTO_MAX_ALL
} tenuM2mCryptoCmd;

/*!
@enum       tenuM2mIpCmd

@brief
            This enum contains all the WINC commands related to IP.
*/
typedef enum
{
    M2M_IP_REQ_STATIC_IP_CONF = (10),
    /*!< Request to set static IP.*/
    M2M_IP_REQ_ENABLE_DHCP,
    /*!< Request to enable DHCP.*/
    M2M_IP_REQ_DISABLE_DHCP
    /*!< Request to disable DHCP.*/
} tenuM2mIpCmd;

/*!
@enum       tenuM2mSigmaCmd

@brief
            This enum contains all the WINC commands related to Sigma.
*/
typedef enum
{
    M2M_SIGMA_ENABLE = (3),
    /*!< Enable Sigma.*/
    M2M_SIGMA_TA_START,
    /*!< Start the traffic agent.*/
    M2M_SIGMA_TA_STATS,
    /*!< Get traffic statistics.*/
    M2M_SIGMA_TA_RECEIVE_STOP,
    /*!< Stop receiving from the traffic agent.*/
    M2M_SIGMA_ICMP_ARP,
    /*!< Send ARP.*/
    M2M_SIGMA_ICMP_RX,
    /*!< Receive ICMP.*/
    M2M_SIGMA_ICMP_TX,
    /*!< Transmit ICMP.*/
    M2M_SIGMA_UDP_TX,
    /*!< Transmit UDP.*/
    M2M_SIGMA_UDP_TX_DEFER,
    /*!< Transmit UDP defer.*/
    M2M_SIGMA_SECURITY_POLICY,
    /*!< Set security policy.*/
    M2M_SIGMA_SET_SYSTIME
    /*!< Set system time.*/
} tenuM2mSigmaCmd;

/*!
@enum       tenuM2mConnState

@brief
            This enum contains all the WiFi connection states.
*/
typedef enum
{
    M2M_WIFI_DISCONNECTED = 0,
    /*!< WiFi state is disconnected. */
    M2M_WIFI_CONNECTED,
    /*!< WiFi state is connected. */
    M2M_WIFI_ROAMED,
    /*!< WiFi state is roamed to new AP. */
    M2M_WIFI_UNDEF = 0xff
                     /*!< Undefined WiFi State. */
} tenuM2mConnState;

/*!
@enum       tenuM2mSecType

@brief
            This enum contains all the supported WiFi security types.
*/
typedef enum
{
    M2M_WIFI_SEC_INVALID = 0,
    /*!< Invalid security type. */
    M2M_WIFI_SEC_OPEN,
    /*!< WiFi network is not secured. */
    M2M_WIFI_SEC_WPA_PSK,
    /*!< WiFi network is secured with WPA/WPA2 personal(PSK). */
    M2M_WIFI_SEC_WEP,
    /*!< Security type WEP (40 or 104) OPEN OR SHARED. */
    M2M_WIFI_SEC_802_1X,
    /*!< WiFi network is secured with WPA/WPA2 Enterprise.IEEE802.1x. */
    M2M_WIFI_NUM_AUTH_TYPES
    /*!< Upper limit for enum value. */
} tenuM2mSecType;

/*!
@enum       tenuM2mSecType

@brief
            This enum contains all the supported WiFi SSID types.
*/
typedef enum
{
    SSID_MODE_VISIBLE = 0,
    /*!< SSID is visible to others. */
    SSID_MODE_HIDDEN
    /*!< SSID is hidden. */
} tenuM2mSsidMode;

/*!
@enum       tenuM2mScanCh

@brief
            This enum contains all the WiFi RF channels.
@sa
            tstrM2MScan
            tstrM2MScanOption
*/
typedef enum
{
    M2M_WIFI_CH_1 = (1),
    /*!< Channel 1. */
    M2M_WIFI_CH_2,
    /*!< Channel 2. */
    M2M_WIFI_CH_3,
    /*!< Channel 3. */
    M2M_WIFI_CH_4,
    /*!< Channel 4. */
    M2M_WIFI_CH_5,
    /*!< Channel 5. */
    M2M_WIFI_CH_6,
    /*!< Channel 6. */
    M2M_WIFI_CH_7,
    /*!< Channel 7. */
    M2M_WIFI_CH_8,
    /*!< Channel 8. */
    M2M_WIFI_CH_9,
    /*!< Channel 9. */
    M2M_WIFI_CH_10,
    /*!< Channel 10. */
    M2M_WIFI_CH_11,
    /*!< Channel 11. */
    M2M_WIFI_CH_12,
    /*!< Channel 12. */
    M2M_WIFI_CH_13,
    /*!< Channel 13. */
    M2M_WIFI_CH_14,
    /*!< Channel 14. */
    M2M_WIFI_CH_ALL = (255)
} tenuM2mScanCh;

/*!
@enum       tenuM2mScanRegion

@brief
            This enum contains all the WiFi channel regions.
*/
typedef enum
{
    REG_CH_1 = ((uint16_t) 1 << 0),
    /*!< Region channel 1. */
    REG_CH_2 = ((uint16_t) 1 << 1),
    /*!< Region channel 2. */
    REG_CH_3 = ((uint16_t) 1 << 2),
    /*!< Region channel 3. */
    REG_CH_4 = ((uint16_t) 1 << 3),
    /*!< Region channel 4. */
    REG_CH_5 = ((uint16_t) 1 << 4),
    /*!< Region channel 5. */
    REG_CH_6 = ((uint16_t) 1 << 5),
    /*!< Region channel 6. */
    REG_CH_7 = ((uint16_t) 1 << 6),
    /*!< Region channel 7. */
    REG_CH_8 = ((uint16_t) 1 << 7),
    /*!< Region channel 8. */
    REG_CH_9 = ((uint16_t) 1 << 8),
    /*!< Region channel 9. */
    REG_CH_10 = ((uint16_t) 1 << 9),
    /*!< Region channel 10. */
    REG_CH_11 = ((uint16_t) 1 << 10),
    /*!< Region channel 11. */
    REG_CH_12 = ((uint16_t) 1 << 11),
    /*!< Region channel 12. */
    REG_CH_13 = ((uint16_t) 1 << 12),
    /*!< Region channel 13. */
    REG_CH_14 = ((uint16_t) 1 << 13),
    /*!< Region channel 14. */
    REG_CH_ALL = ((uint16_t) 0x3FFF),
    /*!< Region for all channels. */
    NORTH_AMERICA = ((uint16_t) 0x7FF),
    /*!< North America region with 11 channels. */
    EUROPE      = ((uint16_t) 0x1FFF),
    /*!<Europe region with 13 channels */
    ASIA        = ((uint16_t) 0x3FFF)
                  /*!<Asia region with 14 channels */
} tenuM2mScanRegion;

/*!
@enum       tenuPowerSaveModes

@brief
            This enum contains all the supported WiFi Power Save modes.
*/
typedef enum
{
    M2M_NO_PS,
    /*!< Power save is disabled. */
    M2M_PS_AUTOMATIC,
    /*!< Power save is done automatically by the WINC.
        This mode doesn't disable all of the WINC modules and
        use higher amount of power than the H_AUTOMATIC and
        the DEEP_AUTOMATIC modes..
    */
    M2M_PS_H_AUTOMATIC,
    /*!< Power save is done automatically by the WINC.
        Achieve higher power save than the AUTOMATIC mode
        by shutting down more parts of the WINC board.
    */
    M2M_PS_DEEP_AUTOMATIC,
    /*!< Power save is done automatically by the WINC.
        Achieves the highest possible power save.
    */
    M2M_PS_MANUAL
    /*!< Power save is done manually by the user. */
} tenuPowerSaveModes;

/*!
@enum       tenuM2mWifiMode

@brief
            This enum contains all the supported WiFi Operation Modes.
*/
typedef enum
{
    M2M_WIFI_MODE_NORMAL = (1),
    /*!< Normal Mode means to run customer firmware version. */
    M2M_WIFI_MODE_ATE_HIGH,
    /*!< Config Mode in HIGH POWER means to run production test firmware version which is known as ATE (Burst) firmware. */
    M2M_WIFI_MODE_ATE_LOW,
    /*!< Config Mode in LOW POWER means to run production test firmware version which is known as ATE (Burst) firmware. */
    M2M_WIFI_MODE_ETHERNET,
    /*!< Ethernet Mode */
    M2M_WIFI_MODE_MAX
} tenuM2mWifiMode;

/*!
@enum       tenuWPSTrigger

@brief
            This enum contains the WPS triggering methods.
*/
typedef enum
{
    WPS_PIN_TRIGGER = 0,
    /*!< WPS is triggered in PIN method. */
    WPS_PBC_TRIGGER = 4
                      /*!< WPS is triggered via push button. */
} tenuWPSTrigger;

/*!
@enum       tenuSNTPUseDHCP

@brief
            Use NTP server provided by the DHCP server.
*/
typedef enum
{
    SNTP_DISABLE_DHCP = 0,
    /*!< Don't use the NTP server provided by the DHCP server when falling back. */
    SNTP_ENABLE_DHCP = 1
                       /*!< Use the NTP server provided by the DHCP server when falling back. */
} tenuSNTPUseDHCP;

/*!
@struct     tstrM2mWifiGainsParams

@brief
            Gain Values
*/
typedef struct
{
    uint16_t u8PPAGFor11B;
    /*!< PPA gain for 11B (as the RF document representation)
    PPA_AGC<0:2> Every bit have 3dB gain control each.
    for example:
    1 ->3db
    3 ->6db
    7 ->9db
    */
    uint16_t u8PPAGFor11GN;
    /*!< PPA gain for 11GN (as the RF document represented)
    PPA_AGC<0:2> Every bit have 3dB gain control each.
        for example:
    1 ->3db
    3 ->6db
    7 ->9db
    */
} tstrM2mWifiGainsParams;

/*!
@struct     tstrM2mConnCredHdr

@brief
            WiFi Connect Credentials Header
*/
typedef struct
{
    uint16_t u16CredSize;
    /*!< Total size of connect credentials, not including tstrM2mConnCredHdr:
            tstrM2mConnCredCmn
            Auth details (variable size)
    */
    uint8_t u8CredStoreFlags;
    /*!< Credential storage options represented with flags:
            @ref M2M_CRED_STORE_FLAG
            @ref M2M_CRED_ENCRYPT_FLAG
            @ref M2M_CRED_IS_STORED_FLAG
            @ref M2M_CRED_IS_ENCRYPTED_FLAG
    */
    uint8_t u8Channel;
    /*!< WiFi channel(s) on which to attempt connection. */
} tstrM2mConnCredHdr;

/*!
@struct     tstrM2mConnCredCmn

@brief
            WiFi Connect Credentials Common section
*/
typedef struct
{
    uint8_t u8SsidLen;
    /*!< SSID length. */
    uint8_t au8Ssid[M2M_MAX_SSID_LEN - 1];
    /*!< SSID. */
    uint8_t u8Options;
    /*!< Common flags:
            @ref M2M_WIFI_CONN_BSSID_FLAG
    */
    uint8_t au8Bssid[M2M_MAC_ADDRES_LEN];
    /*!< BSSID to restrict on, or all 0 if @ref M2M_WIFI_CONN_BSSID_FLAG is not set in u8Options. */
    uint8_t u8AuthType;
    /*!< Connection auth type. See @ref tenuM2mSecType. */
    uint8_t au8Rsv[3];
    /*!< Reserved for future use. Set to 0. */
} tstrM2mConnCredCmn;

/*!
@struct     tstrM2mWifiWep

@brief
            WEP security key header.
*/
typedef struct
{
    uint8_t u8KeyIndex;
    /*!< WEP Key Index. */
    uint8_t u8KeyLen;
    /*!< WEP Key Size. */
    uint8_t au8WepKey[WEP_104_KEY_SIZE];
    /*!< WEP Key represented in bytes (padded with 0's if WEP-40). */
    uint8_t u8Rsv;
    /*!< Reserved for future use. Set to 0. */
} tstrM2mWifiWep;

/*!
@struct     tstrM2mWifiPsk

@brief
            Passphrase and PSK for WPA(2) PSK.
*/
typedef struct
{
    uint8_t u8PassphraseLen;
    /*!< Length of passphrase (8 to 63) or 64 if au8Passphrase contains ASCII representation of PSK. */
    uint8_t au8Passphrase[M2M_MAX_PSK_LEN - 1];
    /*!< Passphrase, or ASCII representation of PSK if u8PassphraseLen is 64. */
    uint8_t au8Psk[PSK_CALC_LEN];
    /*!< PSK calculated by firmware. Driver sets this to 0. */
    uint8_t u8PskCalculated;
    /*!< Flag used by firmware to avoid unnecessary recalculation of PSK. Driver sets this to 0. */
    uint8_t au8Rsv[2];
    /*!< Reserved for future use. Set to 0. */
} tstrM2mWifiPsk;

/*!
@struct     tstrM2mWifi1xHdr

@brief
            WiFi Authentication 802.1x header for parameters.
            The parameters (Domain, UserName, PrivateKey/Password) are appended to this structure.
*/
typedef struct
{
    uint8_t u8Flags;
    /*!< 802.1x-specific flags:
            @ref M2M_802_1X_MSCHAP2_FLAG
            @ref M2M_802_1X_TLS_FLAG
            @ref M2M_802_1X_UNENCRYPTED_USERNAME_FLAG
            @ref M2M_802_1X_PREPEND_DOMAIN_FLAG
    */
    uint8_t u8DomainLength;
    /*!< Length of Domain. (Offset of Domain, within au81xAuthDetails, understood to be 0.) */
    uint8_t u8UserNameLength;
    /*!< Length of UserName. (Offset of UserName, within au81xAuthDetails, understood to be u8DomainLength.) */
    uint8_t u8HdrLength;
    /*!< Length of header (offset of au81xAuthDetails within tstrM2mWifi1xHdr).
        Legacy implementations may have 0 here, in which case header is 12 bytes.
        The unusual placing of this field is in order to hit a zero in legacy implementations. */
    uint16_t u16PrivateKeyOffset;
    /*!< Offset within au81xAuthDetails of PrivateKey/Password. */
    uint16_t u16PrivateKeyLength;
    /*!< Length of PrivateKey/Password. In the case of PrivateKey, this is the length of the modulus. */
    uint16_t u16CertificateOffset;
    /*!< Offset within au81xAuthDetails of Certificate. */
    uint16_t u16CertificateLength;
    /*!< Length of Certificate. */
    uint8_t au8TlsSpecificRootNameSha1[20];
    /*!< SHA1 digest of subject name to identify specific root certificate for phase 1 server verification. */
    uint32_t u32Rsv1;
    /*!< Reserved, set to 0. */
    uint32_t u32TlsHsFlags;
    /*!< TLS handshake flags for phase 1. */
    uint32_t u32Rsv2;
    /*!< Reserved, set to 0. */
    uint8_t au81xAuthDetails[];
    /*!< Placeholder for concatenation of Domain, UserName, PrivateKey/Password, Certificate.
            Certificate (for 1x Tls only) is sent over HIF separately from the other parameters. */
} tstrM2mWifi1xHdr;

/*!
@struct     tstrM2mWifiAuthInfoHdr

@brief
            Generic WiFi authentication information to be sent in a separate HIF message of type
            @ref M2M_WIFI_IND_CONN_PARAM (preceding @ref M2M_WIFI_REQ_CONN).
*/
typedef struct
{
    uint8_t u8Type;
    /*!< Type of info:
            @ref M2M_802_1X_TLS_CLIENT_CERTIFICATE
    */
    uint8_t au8Rsv[3];
    /*!< Reserved for future use. Set to 0. */
    uint16_t u16InfoPos;
    /*!< Information about positioning of the Info. The interpretation depends on u8Type. */
    uint16_t u16InfoLen;
    /*!< Info length (not including this header). */
    uint8_t au8Info[];
    /*!< Placeholder for info. */
} tstrM2mWifiAuthInfoHdr;

/*!
@struct     tstrM2mWifiConnHdr

@brief
            WiFi Connect Request (new format) for use with @ref M2M_WIFI_REQ_CONN.
            This structure is sent across the HIF along with the relevant auth details. One of:
            @ref tstrM2mWifiPsk
            @ref tstrM2mWifiWep
            @ref tstrM2mWifi1xHdr
            If further authentication details need to be sent (such as client certificate for 1x TLS), they
            are sent with header @ref tstrM2mWifiAuthInfoHdr in a preceding HIF message of type
            @ref M2M_WIFI_IND_CONN_PARAM
*/
typedef struct
{
    tstrM2mConnCredHdr  strConnCredHdr;
    /*!< Credentials header. */
    tstrM2mConnCredCmn  strConnCredCmn;
    /*!< Credentials common section, including auth type and SSID. */
} tstrM2mWifiConnHdr;

/*!
@struct     tstrM2mWifiApId

@brief
            Specify an access point (by SSID)
*/
typedef struct
{
    uint8_t au8SSID[M2M_MAX_SSID_LEN];
    /*!<
        SSID of the desired AP, prefixed by length byte.
        First byte 0xFF used to mean all access points.
    */
    uint8_t __PAD__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mWifiApId;

/*!
@struct     tstrM2MGenericResp

@brief
            Generic success/error response
*/
typedef struct
{
    int8_t      s8ErrorCode;
    /*!<
        Generic success/error code. Possible values are:
        - @ref M2M_SUCCESS
        - @ref M2M_ERR_FAIL
    */
    uint8_t __PAD24__[3];
} tstrM2MGenericResp;

/*!
@struct     tstrM2MWPSConnect

@brief
            This struct stores the WPS configuration parameters.

@sa
            tenuWPSTrigger
*/
typedef struct
{
    uint8_t u8TriggerType;
    /*!< WPS triggering method (Push button or PIN) */
    char         acPinNumber[8];
    /*!< WPS PIN No (for PIN method) */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2MWPSConnect;

/*!
@struct     tstrM2MWPSInfo

@brief      WPS Result

            This structure is passed to the application in response to a WPS request. If the WPS session is completed successfully, the
            structure will have non-zero authentication type. If the WPS Session fails (due to error or timeout) the authentication type
            is set to zero.

@sa
            tenuM2mSecType
*/
typedef struct
{
    uint8_t u8AuthType;
    /*!< Network authentication type. */
    uint8_t u8Ch;
    /*!< RF Channel for the AP. */
    uint8_t au8SSID[M2M_MAX_SSID_LEN];
    /*!< SSID obtained from WPS. */
    uint8_t au8PSK[M2M_MAX_PSK_LEN];
    /*!< PSK for the network obtained from WPS. */
} tstrM2MWPSInfo;

/*!
@struct     tstrM2MDefaultConnResp

@brief
            This struct contains the response error of m2m_default_connect.

@sa
            M2M_DEFAULT_CONN_SCAN_MISMATCH
            M2M_DEFAULT_CONN_EMPTY_LIST
*/
typedef struct
{
    int8_t  s8ErrorCode;
    /*!<
        Default connect error code. possible values are:
        - M2M_DEFAULT_CONN_EMPTY_LIST
        - M2M_DEFAULT_CONN_SCAN_MISMATCH
    */
    uint8_t __PAD24__[3];
} tstrM2MDefaultConnResp;

/*!
@struct     tstrM2MScanOption

@brief
            This struct contains the configuration options for WiFi scan.

@sa
            tenuM2mScanCh
            tstrM2MScan
*/
typedef struct
{
    uint8_t u8NumOfSlot;
    /*!< The number of scan slots per channel. Refers to both active and passive scan.
         Valid settings are in the range 0<Slots<=255.
         Default setting is @ref M2M_SCAN_DEFAULT_NUM_SLOTS.
    */
    uint8_t u8SlotTime;
    /*!< The length of each scan slot in milliseconds. Refers to active scan only.
         The device listens for probe responses and beacons during this time.
         Valid settings are in the range 10<=SlotTime<=250.
         Default setting is @ref M2M_SCAN_DEFAULT_SLOT_TIME.
    */
    uint8_t u8ProbesPerSlot;
    /*!< Number of probe requests to be sent for each scan slot (when not specifying network to scan).
         Number of probe requests to be sent for each ssid to scan in each scan slot (when specifying network to scan).
         Refers to active scan only.
         Valid settings are in the range 0<Probes<=2.
         Default setting is @ref M2M_SCAN_DEFAULT_NUM_PROBE.
    */
    int8_t  s8RssiThresh;
    /*!< The Received Signal Strength Indicator threshold required for (fast) reconnection to an AP without scanning all channels first.
         Refers to active scan as part of reconnection to a previously connected AP.
         The device connects to the target AP immediately if it receives a sufficiently strong probe response on the expected channel.
         Low thresholds facilitate fast reconnection. High thresholds facilitate connection to the strongest signal.
         Valid settings are in the range -128<=Thresh<0.
         Default setting is @ref M2M_FASTCONNECT_DEFAULT_RSSI_THRESH.
    */
} tstrM2MScanOption;

/*!
@struct     tstrM2MStopScanOption

@brief      This struct holds additional configuration options for WiFi scan.

            These scan options should be set by the application prior to issuing the scan request, and once configured,
            WINC will keep the settings until the scan options are set again, via the same API, or until the device is
            either reset or power cycled.
*/
typedef struct
{
    uint8_t u8StopOnFirstResult;
    /*!<
        Stop scan as soon as an SSID is detected.
        1 = Enabled, 0 = Disabled (default)
    */

    uint8_t au8Rsv[3];
    /*!< Reserved for future use. Set to 0. */
} tstrM2MStopScanOption;

/*!
@struct     tstrM2MScanRegion

@brief
            This struct contains the WiFi information for the channel regions.

@sa
            tenuM2mScanRegion
*/
typedef struct
{
    uint16_t u16ScanRegion;
    /*|< Specifies the number of channels allowed in the region (e.g. North America = 11 ... etc.).
    */
    uint8_t __PAD16__[2];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2MScanRegion;

/*!
@struct     tstrM2MScan

@brief
            This struct contains the WiFi scan request.

@sa
            tenuM2mScanCh
            tstrM2MScanOption
*/
typedef struct
{
    uint8_t u8ChNum;
    /*!< The WiFi RF channel number */
    uint8_t __RSVD8__[1];
    /*!< Reserved for future use. */
    uint16_t u16PassiveScanTime;
    /*!< The length of each scan slot in milliseconds. Refers to passive scan only.
         The device listens for beacons during this time.
         Valid settings are in the range 10<=PassiveScanTime<=1200.
         Default setting is @ref M2M_SCAN_DEFAULT_PASSIVE_SLOT_TIME.
    */
} tstrM2MScan;

/*!
@struct     tstrCyptoResp

@brief
            crypto response
*/
typedef struct
{
    int8_t s8Resp;
    /***/
    uint8_t __PAD24__[3];
    /*
    */
} tstrCyptoResp;

/*!
@struct     tstrM2mScanDone

@brief
            This struct contains the WiFi scan result.
*/
typedef struct
{
    uint8_t u8NumofCh;
    /*!< Number of found APs */
    int8_t  s8ScanState;
    /*!< Scan status */
    uint8_t __PAD16__[2];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mScanDone;

/*!
@struct     tstrM2mReqScanResult

@brief
            The WiFi Scan results list is stored in firmware. This struct contains the index by which the application can request a certain scan result.
*/
typedef struct
{
    uint8_t u8Index;
    /*!< Index of the desired scan result */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mReqScanResult;

/*!
@struct     tstrM2mWifiscanResult

@brief
            This struct contains the information corresponding to an AP in the scan result list identified by its order (index) in the list.
*/
typedef struct
{
    uint8_t u8index;
    /*!< AP index in the scan result list. */
    int8_t  s8rssi;
    /*!< AP signal strength. */
    uint8_t u8AuthType;
    /*!< AP authentication type. */
    uint8_t u8ch;
    /*!< AP RF channel. */
    uint8_t au8BSSID[6];
    /*!< BSSID of the AP. */
    uint8_t au8SSID[M2M_MAX_SSID_LEN];
    /*!< AP SSID. */
    uint8_t _PAD8_;
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mWifiscanResult;

/*!
@struct     tstrM2mWifiStateChanged

@brief
            This struct contains the WiFi connection state

@sa
            M2M_WIFI_DISCONNECTED, M2M_WIFI_CONNECTED, M2M_WIFI_REQ_CON_STATE_CHANGED, tenuM2mConnChangedErrcode
*/
typedef struct
{
    uint8_t u8CurrState;
    /*!< Current WiFi connection state */
    uint8_t u8ErrCode;
    /*!< Error type, see tenuM2mConnChangedErrcode */
    uint8_t __PAD16__[2];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mWifiStateChanged;

/*!
@struct     tstrM2mPsType

@brief
            This struct contains the Power Save configuration.

@sa
            tenuPowerSaveModes
*/
typedef struct
{
    uint8_t u8PsType;
    /*!< Power save operating mode */
    uint8_t u8BcastEn;
    /*!< Broadcast Enable/Disable */
    uint8_t __PAD16__[2];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mPsType;

/*!
@struct     tstrM2mSlpReqTime

@brief
            This struct contains the sleep time for the Power Save request.

*/
typedef struct
{
    uint32_t u32SleepTime;
    /*!< Sleep time in ms */
} tstrM2mSlpReqTime;

/*!
@struct     tstrM2mLsnInt

@brief
            This struct contains the Listen Interval. It is the value of the WiFi STA Listen Interval when power save is enabled. It is given in units of Beacon period.
            It is the number of Beacon periods the WINC can sleep before it wakes up to receive data buffered for it in the AP.
*/
typedef struct
{
    uint16_t u16LsnInt;
    /*!< Listen interval in Beacon period counts. */
    uint8_t __PAD16__[2];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mLsnInt;

/*!
@struct     tstrM2MWifiMonitorModeCtrl

@brief      WiFi Monitor Mode Filter

            This structure sets the filtering criteria for WLAN packets when monitoring mode is enable.
            The received packets matching the filtering parameters, are passed directly to the application.
*/
typedef struct
{
    uint8_t u8ChannelID;
    /*!< RF Channel ID. It must use values from tenuM2mScanCh */
    uint8_t u8FrameType;
    /*!< It must use values from tenuWifiFrameType. */
    uint8_t u8FrameSubtype;
    /*!< It must use values from tenuSubTypes. */
    uint8_t au8SrcMacAddress[6];
    /* ZERO means DO NOT FILTER Source address.
    */
    uint8_t au8DstMacAddress[6];
    /* ZERO means DO NOT FILTER Destination address.
    */
    uint8_t au8BSSID[6];
    /* ZERO means DO NOT FILTER BSSID.
    */
    uint8_t u8EnRecvHdr;
    /*
     Enable receive the full header before the payload
    */
    uint8_t __PAD16__[2];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2MWifiMonitorModeCtrl;

/*!
@struct     tstrM2MWifiRxPacketInfo

@brief      WiFi RX Frame Header

            The M2M application has the ability to allow WiFi monitoring mode for receiving all WiFi Raw frames matching a well defined filtering criteria.
            When a target WiFi packet is received, the header information are extracted and assigned in this structure.
*/
typedef struct
{
    uint8_t u8FrameType;
    /*!< It must use values from tenuWifiFrameType. */
    uint8_t u8FrameSubtype;
    /*!< It must use values from tenuSubTypes. */
    uint8_t u8ServiceClass;
    /*!< Service class from WiFi header. */
    uint8_t u8Priority;
    /*!< Priority from WiFi header. */
    uint8_t u8HeaderLength;
    /*!< Frame Header length. */
    uint8_t u8CipherType;
    /*!< Encryption type for the rx packet. */
    uint8_t au8SrcMacAddress[6];
    /* ZERO means DO NOT FILTER Source address.
    */
    uint8_t au8DstMacAddress[6];
    /* ZERO means DO NOT FILTER Destination address.
    */
    uint8_t au8BSSID[6];
    /* ZERO means DO NOT FILTER BSSID.
    */
    uint16_t u16DataLength;
    /*!< Data payload length (Header excluded). */
    uint16_t u16FrameLength;
    /*!< Total frame length (Header + Data). */
    uint32_t u32DataRateKbps;
    /*!< Data Rate in Kbps. */
    int8_t      s8RSSI;
    /*!< RSSI. */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2MWifiRxPacketInfo;

/*!
@struct     tstrM2MWifiTxPacketInfo

@brief
            This struct contains the WiFi TX Packet Info. The M2M Application has the ability to compose raw WiFi frames (under the application responsibility).
            When transmitting a WiFi packet, the application must supply the firmware with this structure for sending the target frame.
*/
typedef struct
{
    uint16_t u16PacketSize;
    /*!< WLAN frame length. */
    uint16_t u16HeaderLength;
    /*!< WLAN frame header length. */
} tstrM2MWifiTxPacketInfo;

/*!
@struct     tstrM2MAPConfig

@brief
            This structure holds the configuration parameters for the AP mode. It should be set by the application when
            it requests to enable the AP operation mode. This mode supports either open, WEP or WPA/WPA2 mixed mode security types.
*/
typedef struct
{
    uint8_t au8SSID[M2M_MAX_SSID_LEN];
    /*!< AP SSID */
    uint8_t u8ListenChannel;
    /*!< WiFi RF Channel which the AP will operate on */
    uint8_t u8KeyIndx;
    /*!< WEP key index */
    uint8_t u8KeySz;
    /*!< WEP/WPA key Size */
    uint8_t au8WepKey[WEP_104_KEY_STRING_SIZE + 1];
    /*!< WEP key */
    uint8_t u8SecType;
    /*!< Security type: Open, WEP or WPA/WPA2 mixed mode */
    uint8_t u8SsidHide;
    /*!< SSID Status "Hidden(1)/Visible(0)" */
    uint8_t au8DHCPServerIP[4];
    /*!< AP DHCP server address */
    uint8_t au8Key[M2M_MAX_PSK_LEN];
    /*!< WPA key */
    uint8_t __PAD16__[2];
    /*!< Padding bytes for forcing alignment */
} tstrM2MAPConfig;

/*!
@struct     tstrM2MAPConfigExt

@brief      AP Configuration Extension

            This structure holds additional configuration parameters for the M2M AP mode. If modification of the extended parameters
            in AP mode is desired then @ref tstrM2MAPModeConfig should be set by the application, which contains the main AP configuration
            structure as well as this extended parameters structure.
            When configuring provisioning mode then @ref tstrM2MProvisionModeConfig should be used, which also contains the main AP configuration
            structure, this extended parameters structure and additional provisioning parameters.
*/
typedef struct
{
    uint8_t au8DefRouterIP[4];
    /*!< AP Default Router address */
    uint8_t au8DNSServerIP[4];
    /*!< AP DNS server address */
    uint8_t au8SubnetMask[4];
    /*!< Network Subnet Mask */
} tstrM2MAPConfigExt;

/*!
@struct     tstrM2MAPModeConfig

@brief      AP Configuration

            This structure holds the AP configuration parameters plus the extended AP configuration parameters for the AP mode.
            It should be set by the application when it requests to enable the AP operation mode. This mode supports
            either open, WEP or WPA/WPA2 mixed mode security types.
*/
typedef struct
{
    tstrM2MAPConfig     strApConfig;
    /*!< Configuration parameters for the WiFi AP. */
    tstrM2MAPConfigExt      strApConfigExt;
    /*!< Additional configuration parameters for the WiFi AP. */
} tstrM2MAPModeConfig;

/*!
@struct     tstrM2mServerInit

@brief
            This struct contains the information for the PS Server initialization.
*/
typedef struct
{
    uint8_t u8Channel;
    /*!< Server Listen channel */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mServerInit;

/*!
@struct     tstrM2mClientState

@brief
            This struct contains the information for the PS Client state.
*/
typedef struct
{
    uint8_t u8State;
    /*!< PS Client State */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mClientState;

/*!
@struct     tstrM2Mservercmd

@brief
            This struct contains the information for the PS Server command.
*/
typedef struct
{
    uint8_t u8cmd;
    /*!< PS Server Cmd */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2Mservercmd;

/*!
@struct     tstrM2mSetMacAddress

@brief
            This struct contains the MAC address to be used. The WINC loads the mac address from the efuse by default to the WINC configuration memory,
            however, the application can overwrite the configuration memory with the mac address indicated from the Host.

@note
            It's recommended to call this only once before calling connect request and after the m2m_wifi_init
*/
typedef struct
{
    uint8_t au8Mac[6];
    /*!< MAC address */
    uint8_t __PAD16__[2];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2mSetMacAddress;

/*!
@struct     tstrM2MDeviceNameConfig

@brief
            This struct contains the Device Name of the WINC. It is used mainly for WiFi Direct device discovery and WPS device information.
*/
typedef struct
{
    uint8_t au8DeviceName[M2M_DEVICE_NAME_MAX];
    /*!< NULL terminated device name */
} tstrM2MDeviceNameConfig;

/*!
@struct     tstrM2MIPConfig

@brief
            This struct contains the static IP configuration.

@note
            All member IP addresses are expressed in Network Byte Order (eg. "192.168.10.1" will be expressed as 0x010AA8C0).
*/
typedef struct
{
    uint32_t u32StaticIP;
    /*!< The static IP assigned to the device. */
    uint32_t u32Gateway;
    /*!< IP of the default internet gateway. */
    uint32_t u32DNS;
    /*!< IP for the DNS server. */
    uint32_t u32AlternateDNS;
    /*!< IP for the secondary DNS server (if any). Must set to zero if not provided in static IP configuration from the application. */
    uint32_t u32SubnetMask;
    /*!< Subnet mask for the local area network. */
    uint32_t u32DhcpLeaseTime;
    /*!< DHCP Lease Time in sec. This field is is ignored in static IP configuration. */
} tstrM2MIPConfig;

/*!
@struct     tstrM2mIpRsvdPkt

@brief
            This struct contains the size and data offset for the received packet.

*/
typedef struct
{
    uint16_t u16PktSz;
    /*<! Packet Size */
    uint16_t u16PktOffset;
    /*<! Packet offset */
} tstrM2mIpRsvdPkt;

/*!
@struct     tstrM2MProvisionModeConfig

@brief
            This struct contains the provisioning mode configuration.
*/

typedef struct
{
    tstrM2MAPConfig     strApConfig;
    /*!< Configuration parameters for the WiFi AP. */
    char                acHttpServerDomainName[64];
    /*!< The device domain name for HTTP provisioning. */
    uint8_t             u8EnableRedirect;
    /*!<
        A flag to enable/disable HTTP redirect feature for the HTTP provisioning server. If the redirect is enabled,
        all HTTP traffic (http://URL) from the device associated with WINC AP will be redirected to the HTTP Provisioning web page.
        - 0 : Disable HTTP Redirect.
        - 1 : Enable HTTP Redirect.
    */
    tstrM2MAPConfigExt      strApConfigExt;
    /*!< Additional configuration parameters for the WiFi AP. */
    uint8_t         __PAD24__[3];
} tstrM2MProvisionModeConfig;

/*!
@struct     tstrM2MProvisionInfo

@brief
            This struct contains the provisioning information obtained from the HTTP Provisioning server.
*/
typedef struct
{
    uint8_t au8SSID[M2M_MAX_SSID_LEN];
    /*!< Provisioned SSID. */
    uint8_t au8Password[M2M_MAX_PSK_LEN];
    /*!< Provisioned Password. */
    uint8_t u8SecType;
    /*!< WiFi Security type. */
    uint8_t u8Status;
    /*!<
        Provisioning status. To be checked before reading the provisioning information. It may be
        - M2M_SUCCESS   : Provision successful.
        - M2M_FAIL      : Provision Failed.
    */
} tstrM2MProvisionInfo;

/*!
@struct     tstrM2MConnInfo

@brief
            This struct contains the connection information.
*/
typedef struct
{
    char    acSSID[M2M_MAX_SSID_LEN];
    /*!< AP connection SSID name  */
    uint8_t u8SecType;
    /*!< Security type */
    uint8_t au8IPAddr[4];
    /*!< Connection IP address */
    uint8_t au8MACAddress[6];
    /*!< MAC address of the peer WiFi station */
    int8_t  s8RSSI;
    /*!< Connection RSSI signal */
    uint8_t u8CurrChannel;
    /*!< WiFi RF channel number  1,2,... 14.  */
    uint8_t __PAD16__[2];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2MConnInfo;

/*!
@struct     tstrM2MSNTPConfig

@brief      SNTP Client Configuration

            Configuration structure for the SNTP client.
*/
typedef struct
{
    /*!< Configuration parameters for the NTP Client. */
    char                acNTPServer[M2M_NTP_MAX_SERVER_NAME_LENGTH + 1];
    /*!< Custom NTP server name. */
    uint8_t             enuUseDHCP;
    /*!< Use NTP server provided by the DHCP server when falling back */
#if tstrM2MSNTPConfig_PAD != 4
    uint8_t             __PAD8__[tstrM2MSNTPConfig_PAD];
    /*!< Padding bytes for forcing 4-byte alignment */
#endif
} tstrM2MSNTPConfig;

/*!
@struct     tstrSystemTime

@brief
            This struct contains the system time.
*/
typedef struct
{
    uint16_t    u16Year;
    /*!< Year */
    uint8_t     u8Month;
    /*!< Month */
    uint8_t     u8Day;
    /*!< Day */
    uint8_t     u8Hour;
    /*!< Hour */
    uint8_t     u8Minute;
    /*!< Minutes */
    uint8_t     u8Second;
    /*!< Seconds */
    uint8_t   __PAD8__;
    /*!< Structure padding. */
} tstrSystemTime;

/*!
@struct     tstrM2MMulticastMac

@brief
            This struct contains the information from the Multicast filter.
*/
typedef struct
{
    uint8_t au8macaddress[M2M_MAC_ADDRES_LEN];
    /*!< Mac address needed to be added or removed from filter. */
    uint8_t u8AddRemove;
    /*!< Set by 1 to add or 0 to remove from filter. */
    uint8_t __PAD8__;
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrM2MMulticastMac;

/*!
@enum       tenuWlanTxRate

@brief      All possible supported 802.11 WLAN TX rates.
*/
typedef enum
{
    TX_RATE_AUTO  = 0xFF, /*!<  Automatic rate selection */
    TX_RATE_LOWEST  = 0xFE, /*!< Force the lowest possible data rate for longest range. */
    TX_RATE_1     = 0x00, /* 1 Mbps  */
    TX_RATE_2     = 0x01, /* 2 Mbps  */
    TX_RATE_5_5   = 0x02, /* 5 Mbps  */
    TX_RATE_11    = 0x03, /* 11 Mbps */
    TX_RATE_6     = 0x0B, /* 6 Mbps  */
    TX_RATE_9     = 0x0F, /* 9 Mbps  */
    TX_RATE_12    = 0x0A, /* 12 Mbps */
    TX_RATE_18    = 0x0E, /* 18 Mbps */
    TX_RATE_24    = 0x09, /* 24 Mbps */
    TX_RATE_36    = 0x0D, /* 36 Mbps */
    TX_RATE_48    = 0x08, /* 48 Mbps */
    TX_RATE_54    = 0x0C, /* 54 Mbps */
    TX_RATE_MCS_0 = 0x80, /* MCS-0: 6.5 Mbps */
    TX_RATE_MCS_1 = 0x81, /* MCS-1: 13 Mbps */
    TX_RATE_MCS_2 = 0x82, /* MCS-2: 19.5 Mbps */
    TX_RATE_MCS_3 = 0x83, /* MCS-3: 26 Mbps */
    TX_RATE_MCS_4 = 0x84, /* MCS-4: 39 Mbps */
    TX_RATE_MCS_5 = 0x85, /* MCS-5: 52 Mbps */
    TX_RATE_MCS_6 = 0x86, /* MCS-6: 58.5 Mbps */
    TX_RATE_MCS_7 = 0x87, /* MCS-7: 65 Mbps */
} tenuWlanTxRate;

/*!
@struct     tstrConfAutoRate

@brief
            Auto TX rate selection parameters passed to m2m_wifi_conf_auto_rate.
*/
typedef struct
{
    uint16_t u16ArMaxRecoveryFailThreshold;
    /*!<
        To stabilize the TX rate and avoid oscillation, the algorithm will not attempt to
        push the rate up again after a failed attempt to push the rate up.
        An attempt to push the rate up is considered failed if the next rate suffers from
        very high retransmission. In this case, WINC will not attempt again until a
        duration of time is elapsed to keep the TX rate stable.
        The min duration is (u16ArMinRecoveryFailThreshold) seconds and doubles
        on every failed attempt. The doubling continues until the duration is
        (u16ArMaxRecoveryFailThreshold) max.

        Increasing u16ArMaxRecoveryFailThreshold will cause the TX rate to be
        stable over a long period of time with fewer attempts to increase the data rate.
        However, increasing it to a very large value will deter the algorithm from
        attempting to increase the rate if, for instance, the wireless conditions before were better.

        Default is 5 seconds.
    */
    uint16_t u16ArMinRecoveryFailThreshold;
    /*!<
        To stabilize the TX rate and avoid oscillation, the algorithm will not attempt to
        push the rate up again after a failed attempt to push the rate up.
        An attempt to push the rate up is considered failed if the next rate suffers from
        very high retransmission. In this case, WINC will not attempt again until a
        duration of time is elapsed to keep the TX rate stable.
        The min duration is (u16ArMinRecoveryFailThreshold) seconds and doubles
        on every failed attempt. The doubling continues until the duration is
        (u16ArMaxRecoveryFailThreshold) max.

        Default is 1 second.
    */

    uint8_t enuWlanTxRate;
    /*!<
        The TX data rate selected as enumerated in tenuWlanTxRate
        Default is TX_RATE_AUTO.

        WINC shall override the rate provided through this API if it not supported by the peer WLAN device (STA/AP).
        For instance, if the TX_RATE_MCS_0 is requested while the connection is to a BG only AP, WINC shall
        elect the nearest BG data rate to the requested rate. In this example, it will be TX_RATE_9.
    */
    uint8_t enuArInitialRateSel;
    /*!<
        Configures the initial WLAN TX rate used right after association.
        This is the starting point for auto rate algorithm.
        The algorithm tunes the rate up or down based on the wireless
        medium condition if enuWlanTxRate is set to TX_RATE_AUTO.
        If enuWlanTxRate is set to any value other than TX_RATE_AUTO, then
        u8ArInitialRateSel is ignored.

        By default WINC selects the best initial rate based on the receive
        signal level from the WLAN peer. For applications that favor range
        right after association, TX_RATE_LOWEST can bs used.
    */
    uint8_t u8ArEnoughTxThreshold;
    /*!<
        Configures the minimum number of transmitted packets per second for auto
        rate selection algorithm to start to make rate up or down decisions.
        Default is 10.
    */
    uint8_t u8ArSuccessTXThreshold;
    /*!<
        Configures the threshold for rate up. Rate goes up if number of
        WLAN TX retries is less than (1/u8ArSuccessTXThreshold) of the
        number of packet transmitted within one second.
        This can be tuned to speed up or slow down the rate at which the algorithm
        moves the WLAN TX rate up. Default value is 5.
    */
    uint8_t u8ArFailTxThreshold;
    /*!<
        Configures the threshold for rate down. Rate goes down if number of
        WLAN TX retries is greater than (1/u8ArFailTxThreshold) of the
        number of packet transmitted within one second.
        This can be tuned to speed up or slow down the rate at which the algorithm
        moves the WLAN TX rate down. Default value is 3.
    */
    uint8_t __PAD24__[3];
    /*!< Pad bytes for forcing 4-byte alignment */
} tstrConfAutoRate;

/**@}*/     // WLANEnums
/**@addtogroup  SSLEnums
 * @{
 */
/*!
@enum       tenuM2mSslCmd

@brief
            This enum contains WINC commands related to TLS handshake.
*/
typedef enum
{
    M2M_SSL_REQ_CERT_VERIF,
    /*!< For internal use only during RSA signature verification. */
    M2M_SSL_REQ_ECC,
    /*!< Request from WINC for an elliptic curve operation. */
    M2M_SSL_RESP_ECC,
    /*!< Response to WINC with the result of an elliptic curve operation. */
    M2M_SSL_IND_CRL,
    /*!< Indication to WINC of a custom-format certificate revocation list. */
    M2M_SSL_REQ_WRITE_OWN_CERTS,
    /*!< Request to WINC with local certificates to write into WINC flash. */
    M2M_SSL_REQ_SET_CS_LIST,
    /*!< Request to WINC to set the list of ciphersuites to be globally enabled. */
    M2M_SSL_RESP_SET_CS_LIST,
    /*!< Response from WINC with the list of ciphersuites that are globally enabled. */
    M2M_SSL_RESP_WRITE_OWN_CERTS
    /*!< Response from WINC to indicate that local certificates have been written into WINC flash. */
} tenuM2mSslCmd;

/*
 * TLS certificate revocation list
 * Typedefs common between firmware and host
 */

/*!
@struct     tstrTlsCrlEntry

@brief
            Certificate data for inclusion in a revocation list (CRL)
*/
typedef struct
{
    uint8_t u8DataLen;
    /*!< Length of certificate data (maximum possible is @ref TLS_CRL_DATA_MAX_LEN) */
    uint8_t au8Data[TLS_CRL_DATA_MAX_LEN];
    /*!< Certificate data */
    uint8_t __PAD24__[3];
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrTlsCrlEntry;

/*!
@struct     tstrTlsCrlInfo

@brief
            Certificate revocation list details
*/
typedef struct
{
    uint8_t         u8CrlType;
    /*!< Type of certificate data contained in list */
    uint8_t         u8Rsv1;
    /*!< Reserved for future use */
    uint8_t         u8Rsv2;
    /*!< Reserved for future use */
    uint8_t         u8Rsv3;
    /*!< Reserved for future use */
    tstrTlsCrlEntry astrTlsCrl[TLS_CRL_MAX_ENTRIES];
    /*!< List entries */
} tstrTlsCrlInfo;

/*!
@enum       tenuSslCertExpSettings

@brief      SSL Certificate Expiry Validation Options
*/
typedef enum
{
    SSL_CERT_EXP_CHECK_DISABLE,
    /*!<
        ALWAYS OFF.
        Ignore certificate expiration date validation. If a certificate is
        expired or there is no configured system time, the SSL connection SUCCEEDs.
    */
    SSL_CERT_EXP_CHECK_ENABLE,
    /*!<
        ALWAYS ON.
        Validate certificate expiration date. If a certificate is expired or
        there is no configured system time, the SSL connection FAILs.
    */
    SSL_CERT_EXP_CHECK_EN_IF_SYS_TIME
    /*!<
        CONDITIONAL VALIDATION (Default setting at startup).
        Validate the certificate expiration date only if there is a configured system time.
        If there is no configured system time, the certificate expiration is bypassed and the
        SSL connection SUCCEEDs.
    */
} tenuSslCertExpSettings;

/*!
@struct     tstrTlsSrvSecFileEntry

@brief
            This struct contains a TLS certificate.
*/
typedef struct
{
    char    acFileName[TLS_FILE_NAME_MAX];
    /*!< Name of the certificate.   */
    uint32_t u32FileSize;
    /*!< Size of the certificate.   */
    uint32_t u32FileAddr;
    /*!< Error Code.    */
} tstrTlsSrvSecFileEntry;

/*!
@struct     tstrTlsSrvSecHdr

@brief
            This struct contains a set of TLS certificates.
*/
typedef struct
{
    uint8_t                 au8SecStartPattern[TLS_SRV_SEC_START_PATTERN_LEN];
    /*!< Start pattern. */
    uint32_t                u32nEntries;
    /*!< Number of certificates stored in the struct.   */
    uint32_t                u32NextWriteAddr;
    /*  */
    tstrTlsSrvSecFileEntry  astrEntries[TLS_SRV_SEC_MAX_FILES];
    /*!< TLS Certificate headers.   */
    uint32_t                u32CRC;
    /*!< CRC32 of entire cert block, only the cert writer computes this, the firmware just does a compare with replacement blocks.    */
} tstrTlsSrvSecHdr;

typedef enum
{
    TLS_FLASH_OK,
    /*!< Operation succeeded. Flash modified. */
    TLS_FLASH_OK_NO_CHANGE,
    /*!< Operation was unnecessary. Flash not modified. */
    TLS_FLASH_ERR_CORRUPT,
    /*!< Operation failed. Flash modified. */
    TLS_FLASH_ERR_NO_CHANGE,
    /*!< Operation failed. Flash not modified. */
    TLS_FLASH_ERR_UNKNOWN
    /*!< Operation failed. Flash status unknown. */
} tenuTlsFlashStatus;

typedef struct
{
    uint16_t u16Sig;
    uint16_t u16TotalSize32;
    uint16_t u16Offset32;
    uint16_t u16Size32;
} tstrTlsSrvChunkHdr;

typedef struct
{
    uint32_t u32CsBMP;
} tstrSslSetActiveCsList;

/**@}*/     // SSLEnums

/**@addtogroup TLSDefines
 * @{
 */
#define TLS_CERTS_CHUNKED_SIG_VALUE 0x6ec8
/**@}*/     // TLSDefines

/**@addtogroup OTATYPEDEF
 * @{
 */
/*!
@enum       tenuOtaError

@brief
            OTA Error codes.
*/
typedef enum
{
    OTA_SUCCESS = (0),
    /*!< OTA Success status */
    OTA_ERR_WORKING_IMAGE_LOAD_FAIL = (-1),
    /*!< Failure to load the firmware image */
    OTA_ERR_INVALID_CONTROL_SEC = (-2),
    /*!< Control structure is corrupted */
    M2M_ERR_OTA_SWITCH_FAIL = (-3),
    /*!< Switching to the updated image failed as may be the image is invalid */
    M2M_ERR_OTA_START_UPDATE_FAIL = (-4),
    /*!<
     OTA update fail due to multiple reasons:
     - Connection failure
     - Image integrity fail
     */
    M2M_ERR_OTA_ROLLBACK_FAIL = (-5),
    /*!< Roll-back failed due to Roll-back image is not valid */
    M2M_ERR_OTA_INVALID_FLASH_SIZE = (-6),
    /*!< The OTA Support at least 4MB flash size, this error code will appear if the current flash is less than 4M */
    M2M_ERR_OTA_INVALID_ARG = (-7),
    /*!< Invalid argument in any OTA Function */
    M2M_ERR_OTA_INPROGRESS = (-8)
    /*!< OTA still in progress */
} tenuOtaError;

/*!
@enum       tenuM2mOtaCmd

@brief
            This enum contains all the WINC commands used for OTA operation.
*/
typedef enum
{
    M2M_OTA_REQ_NOTIF_SET_URL = M2M_OTA_CMD_BASE,
    M2M_OTA_REQ_NOTIF_CHECK_FOR_UPDATE,
    M2M_OTA_REQ_NOTIF_SCHED,
    M2M_OTA_REQ_START_FW_UPDATE,
    /*!< Request to start an OTA update.*/
    M2M_OTA_REQ_SWITCH_FIRMWARE,
    /*!< Request to switch firmware.*/
    M2M_OTA_REQ_ROLLBACK_FW,
    /*!< Request to perform an OTA rollback.*/
    M2M_OTA_RESP_NOTIF_UPDATE_INFO,
    M2M_OTA_RESP_UPDATE_STATUS,
    /*!< Response to indicate the OTA update status. */
    M2M_OTA_REQ_TEST,
    M2M_OTA_REQ_START_CRT_UPDATE,
    M2M_OTA_REQ_SWITCH_CRT_IMG,
    M2M_OTA_REQ_ROLLBACK_CRT,
    M2M_OTA_REQ_ABORT,
    /*!< Request to abort OTA.*/
    M2M_OTA_REQ_HOST_FILE_STATUS,
    M2M_OTA_RESP_HOST_FILE_STATUS,
    M2M_OTA_REQ_HOST_FILE_DOWNLOAD,
    M2M_OTA_RESP_HOST_FILE_DOWNLOAD,
    M2M_OTA_REQ_HOST_FILE_READ,
    M2M_OTA_RESP_HOST_FILE_READ,
    M2M_OTA_REQ_HOST_FILE_ERASE,
    M2M_OTA_RESP_HOST_FILE_ERASE,
    M2M_OTA_MAX_ALL,
} tenuM2mOtaCmd;

/*!
@enum       tenuOtaUpdateStatus

@brief
            This struct contains the OTA return status.
*/
typedef enum
{
    OTA_STATUS_SUCCESS            = 0,
    /*!< OTA Success with no errors. */
    OTA_STATUS_FAIL               = 1,
    /*!< OTA generic fail. */
    OTA_STATUS_INVALID_ARG        = 2,
    /*!< Invalid or malformed download URL. */
    OTA_STATUS_INVALID_RB_IMAGE   = 3,
    /*!< Invalid rollback image. */
    OTA_STATUS_INVALID_FLASH_SIZE = 4,
    /*!< Flash size on device is not enough for OTA. */
    OTA_STATUS_ALREADY_ENABLED    = 5,
    /*!< An OTA operation is already enabled. */
    OTA_STATUS_UPDATE_INPROGRESS  = 6,
    /*!< An OTA operation update is in progress. */
    OTA_STATUS_IMAGE_VERIF_FAILED = 7,
    /*!< OTA Verification failed. */
    OTA_STATUS_CONNECTION_ERROR   = 8,
    /*!< OTA connection error. */
    OTA_STATUS_SERVER_ERROR       = 9,
    /*!< OTA server Error (file not found or else ...) */
    OTA_STATUS_ABORTED            = 10
                                    /*!< OTA download has been aborted by the application. */
} tenuOtaUpdateStatus;

/*!
@enum       tenuOtaUpdateStatusType

@brief
            This struct contains the OTA update status type.
*/
typedef enum
{
    DL_STATUS        = 1,
    /*!< Download OTA file status */
    SW_STATUS        = 2,
    /*!< Switching to the upgrade firmware status */
    RB_STATUS        = 3,
    /*!< Roll-back status */
    AB_STATUS        = 4,
    /*!< Abort status */
    HFD_STATUS       = 5,
    /*!< Host File Download status */
} tenuOtaUpdateStatusType;

/*!
@struct     tstrOtaInitHdr

@brief
            This struct contains the OTA image header.
*/
typedef struct
{
    uint32_t u32OtaMagicValue;
    /*!< Magic value kept in the OTA image after the
    SHA256 Digest buffer to define the Start of OTA Header. */
    uint32_t u32OtaPayloadSize;
    /*!< The Total OTA image payload size, include the SHA256 key size. */
} tstrOtaInitHdr;

/*!
@struct     tstrOtaControlSec

@brief
            Control Section Structure. The Control Section is used to define the working image and the validity
            of the roll-back image and its offset, also both firmware versions are kept in this structure.
*/
typedef struct
{
    uint32_t u32OtaMagicValue;
    /*!< Magic value used to ensure the structure is valid or not. */
    uint32_t u32OtaFormatVersion;
    /*!<
            NA   NA   NA   Flash version   cs struct version
            00   00   00   00              00
        Control structure format version, the value will be incremented in case of structure changed or updated
    */
    uint32_t u32OtaSequenceNumber;
    /*!< Sequence number is used while update the control structure to keep track of how many times that section updated. */
    uint32_t u32OtaLastCheckTime;
    /*!< Last time OTA check for update. */
    uint32_t u32OtaCurrentWorkingImagOffset;
    /*!< Current working offset in flash. */
    uint32_t u32OtaCurrentWorkingImagFirmwareVer;
    /*!< Current working image version ex 18.0.1. */
    uint32_t u32OtaRollbackImageOffset;
    /*!< Roll-back image offset in flash */
    uint32_t u32OtaRollbackImageValidStatus;
    /*!< Roll-back image valid status. */
    uint32_t u32OtaRollbackImagFirmwareVer;
    /*!< Roll-back image version (ex 18.0.3). */
    uint32_t u32OtaCortusAppWorkingOffset;
    /*!<
        Cortus app working offset in flash.
        Removed in v19.6.1.
    */
    uint32_t u32OtaCortusAppWorkingValidSts;
    /*!<
        Working Cortus app valid status.
        Removed in v19.6.1.
    */
    uint32_t u32OtaCortusAppWorkingVer;
    /*!<
        Working cortus app version (ex 18.0.3).
        Removed in v19.6.1.
    */
    uint32_t u32OtaCortusAppRollbackOffset;
    /*!<
        Cortus app rollback offset in flash.
        Removed in v19.6.1.
    */
    uint32_t u32OtaCortusAppRollbackValidSts;
    /*!<
        Roll-back cortus app valid status.
        Removed in v19.6.1.
    */
    uint32_t u32OtaCortusAppRollbackVer;
    /*!<
        Roll-back cortus app version (ex 18.0.3).
        Removed in v19.6.1.
    */
    uint32_t u32OtaControlSecCrc;
    /*!< CRC for the control structure to ensure validity. */
} tstrOtaControlSec;

/*!
@struct     tstrOtaUpdateStatusResp

@brief
            This struct contains the OTA update status.

@sa
            tenuWPSTrigger
*/
typedef struct
{
    uint8_t u8OtaUpdateStatusType;
    /*!< Status type, see @ref tenuOtaUpdateStatusType. */
    uint8_t u8OtaUpdateStatus;
    /*!< The status of the update, see @ref tenuOtaError. */
    uint8_t _PAD16_[2];
} tstrOtaUpdateStatusResp;

/*!
@struct     tstrOtaUpdateInfo

@brief
            This struct contains the OTA update information.

@sa
            tenuWPSTrigger
*/
typedef struct
{
    uint32_t u8NcfUpgradeVersion;
    /*!< NCF OTA Upgrade Version */
    uint32_t u8NcfCurrentVersion;
    /*!< NCF OTA Current firmware version */
    uint32_t u8NcdUpgradeVersion;
    /*!< NCD (host) upgraded version (if the u8NcdRequiredUpgrade == true) */
    uint8_t  u8NcdRequiredUpgrade;
    /*!< NCD Required upgrade to the above version */
    uint8_t  u8DownloadUrlOffset;
    /*!< Download URL offset in the received packet */
    uint8_t  u8DownloadUrlSize;
    /*!< Download URL size in the received packet */
    uint8_t  __PAD8__;
    /*!< Padding bytes for forcing 4-byte alignment */
} tstrOtaUpdateInfo;

/*!
@struct     tstrOtaHostFileGetStatusResp

@brief
            Host File OTA Information
*/
typedef struct
{
    uint32_t u32OtaFileSize;
    /*!<
    Reports the size of the downloaded file.
    Valid if u8OtaFileGetStatus=OTA_STATUS_SUCCESS.
    */
    uint8_t u8OtaFileGetStatus;
    /*!<
    The status of the File Get operation.
    See @ref tenuOtaUpdateStatus.
    */
    uint8_t u8CFHandler;
    /*!<
    The file handler stored in the WINC for a valid file.
    Valid if u8OtaFileGetStatus=OTA_STATUS_SUCCESS.
     */
    uint8_t __PAD16__[2];
    /*!< Padding byte for forcing 4-byte alignment */
} tstrOtaHostFileGetStatusResp;

/*!
@struct     tstrOtaHostFileReadStatusResp

@brief
            Host File OTA Information
*/
typedef struct
{
    uint16_t u16FileBlockSz;
    /*!<
    Reports the size of the block of data read via HIF.
    Valid if u8OtaFileReadStatus=OTA_STATUS_SUCCESS .
    */
    uint8_t u8OtaFileReadStatus;
    /*!<
    The status of the File Read operation.
    See @ref tenuOtaUpdateStatus.
    */
    uint8_t __PAD8__;
    /*!< Padding byte for forcing 4-byte alignment */
    uint8_t pFileBuf[MAX_FILE_READ_STEP];
    /*!<
    Pointer to the temporary buffer containing the data just read.
    Max size is @ref MAX_FILE_READ_STEP
     */
} tstrOtaHostFileReadStatusResp;

/*!
@struct     tstrOtaHostFileEraseStatusResp

@brief
            Host File OTA Information
*/
typedef struct
{
    uint8_t u8OtaFileEraseStatus;
    /*!<
    The status of the File Erase operation.
    See @ref tenuOtaUpdateStatus.
    */
    uint8_t __PAD24__[3];
    /*!< Padding byte for forcing 4-byte alignment */
} tstrOtaHostFileEraseStatusResp;

/**@}*/     // OTATYPEDEF

/*!
@struct     tstrPrng

@brief
            M2M Request PRNG
*/
typedef struct
{
    /*!< Return buffer address */
    uint8_t *pu8RngBuff;
#ifdef __AVR_ARCH__
    uint16_t __PAD_8BIT__;
#endif
    /*!< PRNG size requested */
    uint16_t u16PrngSize;
    /*!< PRNG pads */
    uint8_t __PAD16__[2];
} tstrPrng;

/*!
@struct     tstrM2mRev
@brief      Structure holding firmware version parameters and build date/time
*/
typedef struct
{
    uint32_t u32Chipid; /* HW revision which will be basically the chip ID */
    uint8_t u8FirmwareMajor; /* Version Major Number which represents the official release base */
    uint8_t u8FirmwareMinor; /* Version Minor Number which represents the engineering release base */
    uint8_t u8FirmwarePatch;  /* Version patch Number which represents the patches release base */
    uint8_t u8DriverMajor; /* Version Major Number which represents the official release base */
    uint8_t u8DriverMinor; /* Version Minor Number which represents the engineering release base */
    uint8_t u8DriverPatch; /* Version Patch Number which represents the patches release base */
    uint8_t BuildDate[sizeof(__DATE__)];
    uint8_t BuildTime[sizeof(__TIME__)];
    uint8_t _PAD8_;
    uint16_t u16FirmwareSvnNum;
    uint16_t _PAD16_[2];
} tstrM2mRev;

#endif
