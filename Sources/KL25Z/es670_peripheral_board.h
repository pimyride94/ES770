/* ***************************************************************** */
/* File name:        es670_peripheral_board.h                        */
/* File description: Header file containing the peripherals mapping  */
/*                     of the peripheral board for the ES670 hardware*/
/* Author name:      dloubach                                        */
/* Creation date:    16out2015                                       */
/* Revision date:    25fev2016                                       */
/* ***************************************************************** */

#ifndef SOURCES_ES670_PERIPHERAL_BOARD_H_
#define SOURCES_ES670_PERIPHERAL_BOARD_H_

/* system includes */
#include <MKL25Z4.h>

/*                 General uC definitions                 */

/* Clock gate control */
#define  CGC_CLOCK_DISABLED         0x00U
#define  CGC_CLOCK_ENABLED          0x01U

/* GPIO input / output */
#define GPIO_INPUT                  0x00U
#define GPIO_OUTPUT                 0x01U


/*                 END OF General uC definitions         */


/*                 BUZZER Definitions                    */
#define BUZZER_PORT_BASE_PNT        PORTD                                   /* peripheral port base pointer */
#define BUZZER_GPIO_BASE_PNT        PTD                                     /* peripheral gpio base pointer */

#define BUZZER_PIN                  1U                                      /* buzzer pin */
#define BUZZER_DIR                  kGpioDigitalOutput
#define BUZZER_ALT                  0x01u
/*                 END OF BUZZER definitions             */


/*                 LED and SWITCH Definitions                    */
#define LS_PORT_BASE_PNT            PORTA                                   /* peripheral port base pointer */
#define LS_GPIO_BASE_PNT            PTA                                     /* peripheral gpio base pointer */

/* THIS PIN CONFLICTS WITH PTA1 USED AS UART0_RX IN THE OPENSDA SERIAL DEBUG PORT */
#define LS1_PIN                     1U                                      /* led/switch #1 pin */
#define LS1_DIR_OUTPUT              (GPIO_OUTPUT << LS1_PIN)
#define LS1_DIR_INPUT               (GPIO_OUTPUT << LS1_PIN)
#define LS1_ALT                     0x01u                                   /* GPIO alternative */

/* THIS PIN CONFLICTS WITH PTA2 USED AS UART0_TX IN THE OPENSDA SERIAL DEBUG PORT */
#define LS2_PIN                     2U                                      /* led/switch #2 pin */
#define LS2_DIR_OUTPUT              (GPIO_OUTPUT << LS2_PIN)
#define LS2_DIR_INPUT               (GPIO_OUTPUT << LS2_PIN)
#define LS2_ALT                     LS1_ALT

#define LS3_PIN                     4U                                      /* led/switch #3 pin */
#define LS3_DIR_OUTPUT              (GPIO_OUTPUT << LS3_PIN)
#define LS3_DIR_INPUT               (GPIO_OUTPUT << LS3_PIN)
#define LS3_ALT                     LS1_ALT

#define LS4_PIN                     5U                                      /* led/switch #4 pin */
#define LS4_DIR_OUTPUT              (GPIO_OUTPUT << LS4_PIN)
#define LS4_DIR_INPUT               (GPIO_OUTPUT << LS4_PIN)
#define LS4_ALT                     LS1_ALT

/*                 END OF LED and SWITCH definitions             */


/*					DISPLAY Definitions							*/
#define DISP_PORT_BASE_PNT			PORTC
#define DISP_GPIO 					PTC

#define DSPA_PIN					0U
#define DSPA_DIR_OUTPUT				(GPIO_OUTPUT << DSPA_PIN)
#define DSPA_ALT					0x01u

#define DSPB_PIN					1U
#define DSPB_DIR_OUTPUT				(GPIO_OUTPUT << DSPB_PIN)
#define DSPB_ALT					0x01u

#define DSPC_PIN					2U
#define DSPC_DIR_OUTPUT				(GPIO_OUTPUT << DSPC_PIN)
#define DSPC_ALT					0x01u

#define DSPD_PIN					3U
#define DSPD_DIR_OUTPUT				(GPIO_OUTPUT << DSPD_PIN)
#define DSPD_ALT					0x01u

#define DSPE_PIN					4U
#define DSPE_DIR_OUTPUT				(GPIO_OUTPUT << DSPE_PIN)
#define DSPE_ALT					0x01u

#define DSPF_PIN					5U
#define DSPF_DIR_OUTPUT				(GPIO_OUTPUT << DSPF_PIN)
#define DSPF_ALT					0x01u

#define DSPG_PIN					6U
#define DSPG_DIR_OUTPUT				(GPIO_OUTPUT << DSPG_PIN)
#define DSPG_ALT					0x01u

#define DSPDP_PIN					7U
#define DSPDP_DIR_OUTPUT			(GPIO_OUTPUT << DSPDP_PIN)
#define DSPDP_ALT					0x01u

#define DSP1_PIN					13U
#define DSP1_DIR_OUTPUT				(GPIO_OUTPUT << DSP1_PIN)
#define DSP1_ALT					0x01u

#define DSP2_PIN					12U
#define DSP2_DIR_OUTPUT				(GPIO_OUTPUT << DSP2_PIN)
#define DSP2_ALT					0x01u

#define DSP3_PIN					11U
#define DSP3_DIR_OUTPUT				(GPIO_OUTPUT << DSP3_PIN)
#define DSP3_ALT					0x01u

#define DSP4_PIN					10U
#define DSP4_DIR_OUTPUT				(GPIO_OUTPUT << DSP4_PIN)
#define DSP4_ALT					0x01u

/*                 END OF 7segments definitions             */


/*                 LCD definitions                 */

/* LCD Register Selector
 * Used as register selector input
 * When (LCD_RS = LCD_RS_HIGH) => DATA register is selected
 * When (LCD_RS = LCD_RS_LOW)  => INSTRUCTION register is selected
*/
#define LCD_PORT_BASE_PNT           PORTC                                   /* peripheral port base pointer */
#define LCD_GPIO_BASE_PNT           PTC                                     /* peripheral gpio base pointer */

#define LCD_RS_PIN                  8U                                      /* register selector */
#define LCD_RS_DIR                  (GPIO_OUTPUT << LCD_RS_PIN)
#define LCD_RS_ALT                  1U

#define LCD_ENABLE_PIN              9U                                      /* enable pin */
#define LCD_ENABLE_DIR              (GPIO_OUTPUT << LCD_ENABLE_PIN)
#define LCD_ENABLE_ALT              1U

#define LCD_RS_HIGH                 1U
#define LCD_RS_DATA                 LCD_RS_HIGH

#define LCD_RS_LOW                  0U
#define LCD_RS_CMD                  LCD_RS_LOW

#define LCD_ENABLED                 1U
#define LCD_DISABLED                0U


                      /* LCD data pins */
#define LCD_DATA_DIR				1U
#define LCD_DATA_ALT                1U

#define LCD_DATA_DB0_PIN            0U
#define LCD_DATA_DB0_DIR            (GPIO_OUTPUT << LCD_DATA_DB0_PIN)

#define LCD_DATA_DB1_PIN            1u
#define LCD_DATA_DB1_DIR            (GPIO_OUTPUT << LCD_DATA_DB1_PIN)

#define LCD_DATA_DB2_PIN            2u
#define LCD_DATA_DB2_DIR            (GPIO_OUTPUT << LCD_DATA_DB2_PIN)

#define LCD_DATA_DB3_PIN            3U
#define LCD_DATA_DB3_DIR            (GPIO_OUTPUT << LCD_DATA_DB3_PIN)

#define LCD_DATA_DB4_PIN            4U
#define LCD_DATA_DB4_DIR            (GPIO_OUTPUT << LCD_DATA_DB4_PIN)

#define LCD_DATA_DB5_PIN            5U
#define LCD_DATA_DB5_DIR            (GPIO_OUTPUT << LCD_DATA_DB5_PIN)

#define LCD_DATA_DB6_PIN            6U
#define LCD_DATA_DB6_DIR            (GPIO_OUTPUT << LCD_DATA_DB6_PIN)

#define LCD_DATA_DB7_PIN            7U
#define LCD_DATA_DB7_DIR            (GPIO_OUTPUT << LCD_DATA_DB7_PIN)

/*                 END OF LCD definitions                 */


                      /* Cooler e tacometro data pins */
#define COOLER_DATA_PIN				13U
#define COOLER_DATA_DIR				(GPIO_OUTPUT << COOLER_DATA_PIN)
#define COOLER_DATA_ALT             1U

#define TC_DATA_PIN					29U
#define TC_DATA_DIR					(GPIO_INPUT << TC_DATA_PIN)
#define TC_DATA_ALT             	4U
/*                 END OF cooler e tacometro definitions                 */


#endif /* SOURCES_ES670_PERIPHERAL_BOARD_H_ */
