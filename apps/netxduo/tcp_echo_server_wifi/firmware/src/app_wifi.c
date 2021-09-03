/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    app_wifi.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app_wifi.h"
#include "wdrv_winc_client_api.h"
#include "system/console/sys_console.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// desired AP credentials
#define WLAN_SSID           "DEMO_AP" /* desired SSID */
#define WLAN_CHANNEL        WDRV_WINC_ALL_CHANNELS /* WINC1500's Working Channel e.g. 1, 6, 11 or WDRV_WINC_ALL_CHANNELS*/
#define WLAN_AUTH           WDRV_WINC_AUTH_TYPE_WPA_PSK /* WINC1500's Security, e.g. WDRV_WINC_AUTH_TYPE_OPEN, WDRV_WINC_AUTH_TYPE_WPA_PSK or WDRV_WINC_AUTH_TYPE_WEP */
#define WLAN_WEP_KEY        "1234567890" /* Key for WEP Security */
#define WLAN_WEP_KEY_INDEX  1 /* Key Index for WEP Security */
#define WLAN_WPA_PASSPHRASE "123456789" /* target AP's passphrase */

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_WIFI_Initialize function.

    Application strings and buffers are be defined outside this structure.
*/

APP_WIFI_DATA app_wifiData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************

static void _APP_ConnectNotifyCallback(DRV_HANDLE handle, WDRV_WINC_ASSOC_HANDLE assocHandle, WDRV_WINC_CONN_STATE currentState, WDRV_WINC_CONN_ERROR errorCode)
{
    (void) handle;
    (void) assocHandle;
    (void) errorCode;
    
    if (WDRV_WINC_CONN_STATE_CONNECTED == currentState)
    {
        SYS_CONSOLE_Print(app_wifiData.consoleHandle, "Connected\r\n");
    }
    else if (WDRV_WINC_CONN_STATE_DISCONNECTED == currentState)
    {
        SYS_CONSOLE_Print(app_wifiData.consoleHandle, "Disconnected\r\n");
    }
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_WIFI_Initialize ( void )

  Remarks:
    See prototype in app_wifi.h.
 */

void APP_WIFI_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    app_wifiData.state = APP_WIFI_STATE_INIT;



    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_WIFI_Tasks ( void )

  Remarks:
    See prototype in app_wifi.h.
 */

void APP_WIFI_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( app_wifiData.state )
    {
        /* Application's initial state. */
        case APP_WIFI_STATE_INIT:
        {
            if (SYS_STATUS_READY == WDRV_WINC_Status(sysObj.drvWifiWinc))
            {
                app_wifiData.state = APP_WIFI_STATE_WDRV_INIT_READY;
            }
            break;
        }
        
        case APP_WIFI_STATE_WDRV_INIT_READY:
        {
            app_wifiData.wdrvHandle = WDRV_WINC_Open(0, 0);

            if (DRV_HANDLE_INVALID != app_wifiData.wdrvHandle)
            {
                WDRV_WINC_AUTH_CONTEXT authCtx;
                WDRV_WINC_BSS_CONTEXT  bssCtx;

                /* Reset the internal BSS context */
                WDRV_WINC_BSSCtxSetDefaults(&bssCtx);

                /* Prepare the BSS context with desired AP's parameters */
                WDRV_WINC_BSSCtxSetChannel(&bssCtx, WLAN_CHANNEL);
                WDRV_WINC_BSSCtxSetSSID(&bssCtx, (uint8_t*)WLAN_SSID, strlen(WLAN_SSID));

                /* Reset the internal Auth context */
                WDRV_WINC_AuthCtxSetDefaults(&authCtx);

                /* Prepare the Auth context with desired AP's Security settings */
                if (WDRV_WINC_AUTH_TYPE_OPEN == WLAN_AUTH)
                {
                    WDRV_WINC_AuthCtxSetOpen(&authCtx);
                }
                else if (WDRV_WINC_AUTH_TYPE_WPA_PSK == WLAN_AUTH)
                {
                    WDRV_WINC_AuthCtxSetWPA(&authCtx, (uint8_t*)WLAN_WPA_PASSPHRASE, strlen(WLAN_WPA_PASSPHRASE));
                }
                else if (WDRV_WINC_AUTH_TYPE_WEP == WLAN_AUTH)
                {
                    WDRV_WINC_AuthCtxSetWEP(&authCtx, WLAN_WEP_KEY_INDEX, (uint8_t*)WLAN_WEP_KEY, strlen(WLAN_WEP_KEY));
                }
                else
                {
                    // other type not considered for this demo. default to open.
                    WDRV_WINC_AuthCtxSetOpen(&authCtx);
                }

                if (WDRV_WINC_STATUS_OK == WDRV_WINC_BSSConnect(app_wifiData.wdrvHandle, &bssCtx, &authCtx, &_APP_ConnectNotifyCallback))
                {
                    app_wifiData.state = APP_WIFI_STATE_SERVICE_TASKS;
                }
            }
            break;
        }

        case APP_WIFI_STATE_SERVICE_TASKS:
        {

            break;
        }

        /* TODO: implement your application state machine.*/


        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}


/*******************************************************************************
 End of File
 */
