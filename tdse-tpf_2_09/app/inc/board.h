/*
 * Copyright (c) 2023 Juan Manuel Cruz <jcruz@fi.uba.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @file   : board.h
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

#ifndef BOARD_INC_BOARD_H_
#define BOARD_INC_BOARD_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/
#define NUCLEO_F103RC		(0)
#define NUCLEO_F401RE		(1)
#define NUCLEO_F446RE		(2)
#define NUCLEO_F429ZI		(3)
#define NUCLEO_F439ZI		(4)
#define NUCLEO_F413ZH		(5)
#define STM32F429I_DISCO1	(6)

#define BOARD (NUCLEO_F103RC)

/* STM32 Nucleo Boards - 64 Pins */
#if ((BOARD == NUCLEO_F103RC) || (BOARD == NUCLEO_F401RE) || (BOARD == NUCLEO_F446RE))

//BOTON Y LED A
#define BTN_ARR_PIN		B_ARR_Pin
#define BTN_ARR_PORT		B_ARR_GPIO_Port
#define BTN_ARR_PRESSED	GPIO_PIN_RESET
#define BTN_ARR_HOVER		GPIO_PIN_SET

#define LED_A_PIN		LD2_Pin
#define LED_A_PORT		LD2_GPIO_Port
#define LED_A_ON		GPIO_PIN_SET
#define LED_A_OFF		GPIO_PIN_RESET

//BOTON Y LED B
#define BTN_ABJ_PIN		B_ABJ_Pin
#define BTN_ABJ_PORT		B_ABJ_GPIO_Port
#define BTN_ABJ_PRESSED	GPIO_PIN_RESET
#define BTN_ABJ_HOVER		GPIO_PIN_SET

#define LED_B_PIN		LD2_Pin
#define LED_B_PORT		LD2_GPIO_Port
#define LED_B_ON		GPIO_PIN_SET
#define LED_B_OFF		GPIO_PIN_RESET

//BOTON Y LED C
#define BTN_IZQ_PIN		B_IZQ_Pin
#define BTN_IZQ_PORT		B_IZQ_GPIO_Port
#define BTN_IZQ_PRESSED	GPIO_PIN_RESET
#define BTN_IZQ_HOVER		GPIO_PIN_SET

#define LED_C_PIN		LD2_Pin
#define LED_C_PORT		LD2_GPIO_Port
#define LED_C_ON		GPIO_PIN_SET
#define LED_C_OFF		GPIO_PIN_RESET

//BOTON Y LED D
#define BTN_DER_PIN		B_DER_Pin
#define BTN_DER_PORT		B_DER_GPIO_Port
#define BTN_DER_PRESSED	GPIO_PIN_RESET
#define BTN_DER_HOVER		GPIO_PIN_SET

#define LED_D_PIN		LD2_Pin
#define LED_D_PORT		LD2_GPIO_Port
#define LED_D_ON		GPIO_PIN_SET
#define LED_D_OFF		GPIO_PIN_RESET


/* STM32 Nucleo Boards - 144 Pins */

#define BTN_ENT_PIN		B_ENT_Pin
#define BTN_ENT_PORT	B_ENT_GPIO_Port
#define BTN_ENT_PRESSED	GPIO_PIN_RESET
#define BTN_ENT_HOVER	GPIO_PIN_SET

#define BTN_NEX_PIN		D11_Pin
#define BTN_NEX_PORT	D11_GPIO_Port
#define BTN_NEX_PRESSED	GPIO_PIN_RESET
#define BTN_NEX_HOVER	GPIO_PIN_SET

#define BTN_ESC_PIN		D12_Pin
#define BTN_ESC_PORT	D12_GPIO_Port
#define BTN_ESC_PRESSED	GPIO_PIN_RESET
#define BTN_ESC_HOVER	GPIO_PIN_SET

#define LED_A_PIN		LD2_Pin
#define LED_A_PORT		LD2_GPIO_Port
#define LED_A_ON		GPIO_PIN_SET
#define LED_A_OFF		GPIO_PIN_RESET

#endif/* STM32 Nucleo Boards - 144 Pins */

#if ((BOARD == NUCLEO_F429ZI) || (BOARD == NUCLEO_F439ZI) || (BOARD == NUCLEO_F413ZH))

#define BTN_A_PIN		USER_Btn_Pin
#define BTN_A_PORT		USER_Btn_GPIO_Port
#define BTN_A_PRESSED	GPIO_PIN_SET
#define BTN_A_HOVER		GPIO_PIN_RESET

#define LED_A_PIN		LD1_Pin
#define LED_A_PORT		LD1_GPIO_Port
#define LED_A_ON		GPIO_PIN_SET
#define LED_A_OFF		GPIO_PIN_RESET

#endif

/* STM32 Discovery Kits */
#if (BOARD == STM32F429I_DISCO1)

#define BTN_A_PIN		B1_Pin
#define BTN_A_PORT		B1_GPIO_Port
#define BTN_A_PRESSED	GPIO_PIN_SET
#define BTN_A_HOVER		GPIO_PIN_RESET

#define LED_A_PIN		LD3_Pin
#define LED_A_PORT		LD3_GPIO_Port
#define LED_A_ON		GPIO_PIN_SET
#define LED_A_OFF		GPIO_PIN_RESET

#endif

/********************** typedef **********************************************/

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* BOARD_INC_BOARD_H_ */

/********************** end of file ******************************************/
