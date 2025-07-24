/*
 * potenciometro.c
 *
 *  Created on: Jul 24, 2025
 *      Author: mechi
 */
/* Project includes. */
#include "main.h"


/* App includes. */
#include "logger.h"

/* Application includes. */

/********************** macros and definitions *******************************/

#define SAMPLES_COUNTER (100)
#define AVERAGER_SIZE (16)
#define MATRIX_ROWS 16
#define MATRIX_COLS 32


/********************** external data declaration *****************************/

extern ADC_HandleTypeDef hadc1;

/********************** external functions definition ************************/



/********************** internal data declaration ****************************/
uint32_t tickstart;
uint16_t sample_idx = 0;


uint16_t sample_array[SAMPLES_COUNTER];
bool b_trig_new_conversion = false;

/********************** internal data definition *****************************/

/********************** internal functions definitions ***********************/

// Buffer para un frame RGB, 1 bit por color (simple)
// Para simplificar, usamos 1 bit color ON/OFF. 
// Cada bit representa un LED R, G o B para una fila y columna.

uint8_t framebuffer_red[MATRIX_ROWS][MATRIX_COLS];
uint8_t framebuffer_green[MATRIX_ROWS][MATRIX_COLS];
uint8_t framebuffer_blue[MATRIX_ROWS][MATRIX_COLS];

void clear_matrix(void);
void set_pixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
void send_row(uint8_t row);
void refresh_display(void);

bool potenciometro_lectura();

bool potenciometro_obtencion_datos(uint1t_t *array);

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef ADC_Poll_Read(uint16_t *value);

/********************** internal functions declaration ***********************/

void clear_matrix(void) {
    for (int r = 0; r < MATRIX_ROWS; r++) {
        for (int c = 0; c < MATRIX_COLS; c++) {
            framebuffer_red[r][c] = 0;
            framebuffer_green[r][c] = 0;
            framebuffer_blue[r][c] = 0;
		}
	}
}

void set_pixel(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
    if (x >= MATRIX_COLS || y >= MATRIX_ROWS) return;
    framebuffer_red[y][x] = (r > 0) ? 1 : 0;
    framebuffer_green[y][x] = (g > 0) ? 1 : 0;
    framebuffer_blue[y][x] = (b > 0) ? 1 : 0;
}

// Mapear cada bit de framebuffer a los pines GPIO según tu conexión HUB75
// Esto es un ejemplo muy simplificado de envío por columna.

void send_row(uint8_t row) {
    // Set fila A-D (pines GPIOA 0-3 ejemplo)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, (row & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, (row & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, (row & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, (row & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    for (int col = 0; col < MATRIX_COLS; col++) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, framebuffer_red[row][col] ? GPIO_PIN_SET : GPIO_PIN_RESET);   
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, framebuffer_green[row][col] ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, framebuffer_blue[row][col] ? GPIO_PIN_SET : GPIO_PIN_RESET);

        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);   // CLK
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
    }

    // Latch y OE (GPIOC 1 y 2 ejemplo)
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
}

void refresh_display(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        send_row(row);
    }
}

void potenciometro_init(void) {


	HAL_NVIC_SetPriority(ADC1_2_IRQn, 2, 0);
	HAL_NVIC_EnableIRQ(ADC1_2_IRQn);

	sample_idx = 0;
	LOGGER_LOG ("Potenciómetro test starts\n");
	tickstart = HAL_GetTick();
}

void potenciometro_update(void)
{
	static bool b_test_done = false;

	if (!b_test_done) {

		b_test_done = potenciometro_lectura();

		if (b_test_done) {
			LOGGER_LOG("Test ends. Ticks: %lu\n", HAL_GetTick()-tickstart);
			potenciometro_obtencion_datos(sample_array);
		}
	}

}


//	Requests start of conversion, waits until conversion done
HAL_StatusTypeDef ADC_Poll_Read(uint16_t *value) {
	HAL_StatusTypeDef res;

	res=HAL_ADC_Start(&hadc1);
	if ( HAL_OK==res ) {
		res=HAL_ADC_PollForConversion(&hadc1, 0);
		if ( HAL_OK==res ) {
			*value = HAL_ADC_GetValue(&hadc1);
		}
	}
	return res;
}

/* ADC callback */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	sample_array[sample_idx++] = HAL_ADC_GetValue(hadc);
    if (sample_idx < SAMPLES_COUNTER) {
        b_trig_new_conversion = true;
    }
}

bool potenciometro_lectura() {
static bool b_test_done = false;

    if (!b_test_done) {
        if (sample_idx >= SAMPLES_COUNTER) {
            b_test_done = true;
            potenciometro_obtencion_datos(sample_array);
            sample_idx = 0;
        }

        if (sample_idx == 0 || b_trig_new_conversion) {
            b_trig_new_conversion = false;
            HAL_ADC_Start_IT(&hadc1);
        }
    }
}

bool potenciometro_obtencion_datos(uint16_t * arr) {
	uint32_t suma = 0;
    for (uint16_t i = 0; i < SAMPLES_COUNTER; i++) {
        suma += arr[i];
    }
    uint16_t promedio = suma / SAMPLES_COUNTER;

    uint16_t index = promedio * 1023 / 4095;
    uint8_t x = index % 32;
    uint8_t y = index / 32;

    clear_matrix();
    set_pixel(x, y, 255, 255, 255);
    refresh_display();

    return true;
}


/********************** end of file ******************************************/


