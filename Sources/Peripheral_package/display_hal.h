/* ***************************************************************** */
/* File name:        display_hal.h                                   */
/* File description: Header of display_hal.h.			     		 */
/*                   												 */
/* Authors names:    Paulo Lage, Frederic Devloo                     */
/* Creation date:    26mar2018                                       */
/* Revision date:    02abr2018                                       */
/* ***************************************************************** */

#ifndef SOURCES_DISPLAY_HAL_H_
#define SOURCES_DISPLAY_HAL_H_


/* ************************************************ */
/* Method name:        disp_initDSP                 */
/* Method description: Initialize all 7seg device	*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void disp_initDSP(void);


/* ************************************************ */
/* Method name:        seg7_clear                   */
/* Method description: Clear all 7seg devices. 		*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void seg7_clear(void);

/* ************************************************ */
/* Method name:        disp_setDSP                  */
/* Method description: Initialize the buzzer device */
/* Input params:       Display number(dispNum)      */
/* 				       Display show(dispSeg)        */
/* Output params:      n/a                          */
/* ************************************************ */
void disp_setDSP(char dispNum, char dispSeg);

#endif
