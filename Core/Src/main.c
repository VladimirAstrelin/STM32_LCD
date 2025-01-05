/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  *
	https://www.youtube.com/watch?v=6gQ49cA09Og&ab_channel=ArduinoKit
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#include "LCD1602.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// Send printf to uart1
//int _write(int fd, char* ptr, int len) {
//  HAL_StatusTypeDef hstatus;
//
//  if (fd == 1 || fd == 2) {
//    hstatus = HAL_UART_Transmit(&huart1, (uint8_t *) ptr, len, HAL_MAX_DELAY);
//    if (hstatus == HAL_OK)
//      return len;
//    else
//      return -1;
//  }
//  return -1;
//}

// Под каждый символ отводится 8 байт, а в каждом байте используются только первые пять бит.
// Тогда наш символ можно представить в виде массива, состоящего из восьми элементов.
// один квадратик дисплея это массив точек 5x8
// https://chareditor.com/
// https://arduinointro.com/lcdcustomcharacter/
// https://maxpromer.github.io/LCD-Character-Creator/

//uint8_t myChar_1[8] = {
//							0xff,	// 11111
//							0x00,	// 00000
//							0x00,	// 00000
//							0x00,	// 00000
//							0x00,	// 00000
//							0x00,	// 00000
//							0x00,	// 00000
//							0x00	// 00000
//						  };

//uint8_t myChar_2[8] = {
//    0b11111,
//    0b10001,
//    0b10001,
//    0b10001,
//    0b10001,
//    0b10001,
//    0b10001,
//    0b11111
//};
// ИЛИ ТАК :
//uint8_t myChar_2[8] = { 0x1F, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1F };


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

// Функция инициализации дисплея
  LCD_Init();

	// функция создания своего символа и записи его в память Первый параметр массив с символом второй парамет номер ячеки куда записали от 0 до 7 ( всего 8 символов можно записать )--------
//	LCD_CreateChar( myChar_1, 1 );
//	LCD_CreateChar( myChar_2, 2 );

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//		// Функция позиционирования ( 1-й параметр позиция символа ( номер столбца ) , 2-й параметр строка ( номер строки ), ( Счет с нуля )------------------
//		LCD_SetCursor( 0, 0 );
//		// Функция печати строки на дисплее
//		LCD_PrintString("Hello Odessa");
//
//		// Функция позиционирования ( 1-й параметр позиция символа , 2-й параметр строка, ( Счет с нуля )------------------
//		LCD_SetCursor( 0, 1 );
//		LCD_PrintString("123456789");
//
//		// Функция позиционирования ( 1-й параметр позиция символа , 2-й параметр строка, ( Счет с нуля )------------------
//		LCD_SetCursor( 15, 1 );
//
//		// печатаем собственный символ под номером 0
//		// перед вызавом своего символа обязательно вызываем LCD_SetCursor();
//		LCD_PrintMyChar( 2 );
//		HAL_Delay (1000);
//
//		// Функция включения и выключения подсветки дисплея ( 0-выкл, 1 (либо другое от 0)- вкл -------------------------------------
//		LCD_LedOnOff( 0 );
//		HAL_Delay (1000);
//
//		// Функция включения и выключения подсветки дисплея ( 0-выкл, 1 (либо другое от 0)- вкл -------------------------------------
//		LCD_LedOnOff( 1 );
//		HAL_Delay (1000);

//		// функция двигает надпись вправо на 1 символ ( бегущая строка )
//		for( uint8_t i = 0; i < 10; i++ ){
//			LCD_StringRunR();
//			HAL_Delay (300);
//		}
//		// функция двигает надпись влево на 1 символ ( бегущая строка )
//		for( uint8_t i = 0; i < 10; i++ ){
//			LCD_StringRunL();
//			HAL_Delay (300);
//		}

//		// функция віключает надпись на єкране (єкран пустой ) и включает ее обратно ( 0- выкл, 1 ( или любое отличное от 0 ) вкл )--
//		LCD_TextOnOff( 0 );
//		HAL_Delay (1000);

//		// функция віключает надпись на єкране (єкран пустой ) и включает ее обратно ( 0- выкл, 1 ( или любое отличное от 0 ) вкл )--
//		LCD_TextOnOff( 1 );
//		HAL_Delay (1000);
//
//		// Функция очистки дисплея ----------------------------------------------------------------------------------------------
//		LCD_Clear();
//		HAL_Delay (1000);

	// ВЫРУБИТЬ ПОДСВЕТКУ И ОЧИСТИТЬ ЭКРАН:
	LCD_LedOnOff( 0 );
	LCD_Clear();
	char buff[1024];

	uint32_t now = 0;
	uint32_t last_print = 0;
//
//	double d1, d2;
//	d1 = M_PI;
//	d2 = M_E;
//
//	LCD_SetCursor( 0, 0 );
//	sprintf(buff, "[%18.16f]", d1);
//	LCD_PrintString(buff);
//
//	LCD_SetCursor( 0, 1 );
//	sprintf(buff, "[%18.16f]", d2);
//	LCD_PrintString(buff);
//
//	LCD_SetCursor( 0, 2 );
//	sprintf(buff, "[RES:%14.12f]", d1 - d2);
//	LCD_PrintString(buff);
//
//	HAL_GPIO_WritePin(GPIOD, GREEN_Pin|ORANGE_Pin|RED_Pin|BLUE_Pin, GPIO_PIN_SET);
//
//	LCD_SetCursor( 0, 3 );




// ВЫДЕЛЕНИЕ ОПРЕДЕЛЕННОГО КОЛИЧЕСТВА ЗНАКОМЕСТ ПОД ВЫВОД:
//	LCD_SetCursor( 0, 1 );
//	sprintf(buff, "[%10d]", 1234);
//	LCD_PrintString(buff);
//
//	LCD_SetCursor( 0, 2 );
//	sprintf(buff, "[%10d]", 0xff);
//	LCD_PrintString(buff);
//
//	LCD_SetCursor( 0, 3 );
//	sprintf(buff, "[%10d]", 987654321);
//	LCD_PrintString(buff);

//	double d1, d2;
//	d1 = M_PI;
//	d2 = M_E;
//
//	LCD_SetCursor( 0, 0 );
//	sprintf(buff, "[%18.16f]", d1);
//	LCD_PrintString(buff);
//
//	LCD_SetCursor( 0, 1 );
//	sprintf(buff, "[%18.16f]", d2);
//	LCD_PrintString(buff);
//
//	LCD_SetCursor( 0, 2 );
//	sprintf(buff, "[RES:%14.12f]", d1+d2);
//	LCD_PrintString(buff);


//	// ЭКСПОНЕНЦИАЛЬНАЯ ЗАПИСЬ ЧИСЛА:
//	double d1, d2, d3, d4;
//
//	d1 = 3.14;
//	d2 = -7.;
//	d3 = 1e2; // = 1*10^2 = 100
//	d4 = 5e-3; // = 5 * 10^-3 = 0.005
//
//	LCD_Clear();
//	LCD_SetCursor( 0, 0 );
//	sprintf(buff, "%.f", d1);
//	LCD_PrintString(buff);
//
//	LCD_SetCursor( 0, 1 );
//	sprintf(buff, "%.f", d2);
//	LCD_PrintString(buff);
//
//	LCD_SetCursor( 0, 2 );
//	sprintf(buff, "%.f", d3);
//	LCD_PrintString(buff);
//
//	LCD_SetCursor( 0, 3 );
//	sprintf(buff, "%.3f", d4);
//	LCD_PrintString(buff);

// ЧИСЛО ЭЙЛЕРА:
	//#define M_E		2.7182818284590452354

// ЧИСЛО ПИ:
//	//	double a = 3.1415926;
//	// #define M_PI		3.14 15 926 53 58 97 93 23 8 4 6
//		sprintf(buff, "%.15lf", M_PI);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buff);

	// СИМВОЛ И ЕГО КОД
//	char number = 'A';
//  char buff[1024];
//	sprintf(buff, "Symbol: %c code: %d", number, number);
//	LCD_Clear();
//	LCD_SetCursor( 0, 0 );
//	LCD_PrintString(buff);


//	uint8_t number = 0b111; // В ДВОИЧНОМ ВИДЕ !!

//	for (int i = 0; i < 10; ++i) {
//		sprintf(buff, "%d", i);
//		LCD_Clear();
//		LCD_SetCursor( 19, 0 );
//		LCD_PrintString(buff);
//		HAL_Delay(500);
//	}

//    int number = 12345;
//
//    sprintf(buff, "%d", number);
//    LCD_SetCursor( 0, 0 );
//	LCD_PrintString(buff);
//
//    sprintf(buff, "%d", number+2);
//    LCD_SetCursor( 0, 1 );
//    LCD_PrintString(buff);
//
//    double base = 2.0;
//    double exponent = 10.0;
//    long double result = pow(base, exponent);
//	sprintf(buff, "Res: %.Lf", result);
//	LCD_SetCursor( 0, 2 );
//	LCD_PrintString(buff);

//	int rows = 4;
//	int columns = 20;
//	char buff[1];
//	for (int i = 0; i < rows; ++i) {
//		for (int j = 0; j < columns; ++j){
//			LCD_SetCursor( j , i );
////			sprintf(buff, "%d", j);
//			LCD_PrintString("F");
//		}
//	}

//	LCD_SetCursor( 0, 0 );
//	LCD_PrintString("01234567 9ABCDEFGHIJ");
//
//	LCD_SetCursor( 0, 1 );
//	LCD_PrintString("01234567 9ABCDEFGHIJ");
//
//	LCD_SetCursor( 0, 2 );
//	LCD_PrintString("0123456789ABCDEFGHIJ");
//
//	LCD_SetCursor( 0, 3 );
//	LCD_PrintString("0123456789ABCDEFGHIJ");


//		// Функция позиционирования ( 1-й параметр позиция символа , 2-й параметр строка, ( Счет с нуля )------------------
//		LCD_SetCursor( 0, 0 );
//
//		// Функция печати строки на дисплее
//		LCD_PrintString("Hello Odessa");
//
//		// Функция включения и выключения мигания курсора ( 0-выкл, 1 (либо другое от 0)- вкл
//		LCD_CursorOnOff( 1 );
//
//		HAL_Delay (3000);
//
//		// Функция включения и выключения мигания курсора ( 0-выкл, 1 (либо другое от 0)- вкл
//		LCD_CursorOnOff( 0 );
//
//// ВЫВЕСТИ СВОЮ СТРОКУ ЧЕРЕЗ СФОРМИРОВАННЫЙ БУФЕР:
//
//		char buffer[32];
//		sprintf(buffer, "Hello, VLAD!");
//		LCD_Clear();
//		HAL_Delay (1000);
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// ВЫВЕСТИ СВОЁ ЧИСЛОВОЕ ЗНАЧЕНИЕ ЧЕРЕЗ СФОРМИРОВАННЫЙ БУФЕР:
//
//		uint32_t value = 1234;
//		sprintf(buffer, "Value: %ld", value);
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// ВЫВЕСТИ СВОЁ ВЕЩЕСТВЕННОЕ ЧИСЛОВОЕ ЗНАЧЕНИЕ ЧЕРЕЗ СФОРМИРОВАННЫЙ БУФЕР:
//
//		float temperature = 36.6;
//		sprintf(buffer, "Temp: %.2f", temperature);
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// КОМБИНИРОВАННЫЙ ВАРИАНТ_1:
//
//		char name[] = "Alice";
//		int age = 25;
//		sprintf(buffer, "Name: %s Age: %d", name, age);
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// КОМБИНИРОВАННЫЙ ВАРИАНТ_2:
//
//		char surname[] = "Astrelin";
//		char frmt[] = "S: %s Age: %d";
//		age = 45;
//		sprintf(buffer, frmt, surname, age);
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// ОТОБРАЖЕНИЕ HEXADECIMAL NUMBERS:
//
//		int val = 0xABCD;
//		sprintf(buffer, "Hex: 0x%X", val);
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// ОТОБРАЖЕНИЕ ВРЕМЕНИ:
//
//		int hours = 12, minutes = 30, seconds = 45;
//		sprintf(buffer, "Time: %02d:%02d:%02d", hours, minutes, seconds);
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// ОТОБРАЖЕНИЕ ВЕЩЕСТВЕННЫХ ЧИСЕЛ:
//
//		float voltage = 3.3, current = 0.5;
//		sprintf(buffer, "V: %.2fV I: %.2fA", voltage, current);
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// ОТОБРАЖЕНИЕ АДРЕСА В ПАМЯТИ:
//
//		void *ptr = (void *)0x20001000;
//		sprintf(buffer, "Address: %p", ptr);
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// ОТОБРАЖЕНИЕ В ЗАВИСИМОСТИ ОТ УСЛОВИЯ:
//
//		int status = 1; // 1 for success, 0 for failure
//		sprintf(buffer, "Status: %s", status ? "Success" : "Failure");
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//		status = 0;
//		sprintf(buffer, "Status: %s", status ? "Success" : "Failure");
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// ОТОБРАЖЕНИЕ ПРОГРЕССА:
//		int progress = 75; // 75% progress
//		sprintf(buffer, "Progress: %d%%", progress);
//		HAL_Delay (3000);
//		LCD_Clear();
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(buffer);
//
//// ПИШЕМ ВО ВСЕ СТРОКИ ДИСПЛЕЯ:
//		char str_1[] = "FIRST";
//		char str_2[] = "SECOND";
//		char str_3[] = "THIRD";
//		char str_4[] = "FOURTH";
//		HAL_Delay (3000);
//		LCD_Clear();
//
//		LCD_SetCursor( 0, 0 );
//		LCD_PrintString(str_1);
//
//		LCD_SetCursor( 0, 1 );
//		LCD_PrintString(str_2);
//
//		LCD_SetCursor( 0, 2 );
//		LCD_PrintString(str_3);
//
//		LCD_SetCursor( 0, 3 );
//		LCD_PrintString(str_4);
//
//		//*********************
//
//		char num_1[] = "1";
//		char num_2[] = "2";
//		char num_3[] = "3";
//		char num_4[] = "4";
//
//		LCD_SetCursor( 19, 0 );
//		LCD_PrintString(num_1);
//
//		LCD_SetCursor( 19, 1 );
//		LCD_PrintString(num_2);
//
//		LCD_SetCursor( 19, 2 );
//		LCD_PrintString(num_3);
//
//		LCD_SetCursor( 19, 3 );
//		LCD_PrintString(num_4);

// ВОЗВЕДЕНИЕ В СТЕПЕНЬ:

//  double base = 2.0;
//  double exponent = 3.0;
//  double result = pow(base, exponent);
//	sprintf(buff, "Res: %.2f", result); // БЕЗ ЗАПЯТЫХ "Res: %.f"
//	LCD_SetCursor( 0, 2 );
//	LCD_PrintString(buff);





	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  now = HAL_GetTick();
	  if(now - last_print >= 1000){
		  sprintf(buff, "%ld", now / 1000);
		  LCD_Clear();
		  LCD_SetCursor( 0, 0 );
		  LCD_PrintString(buff);
		  last_print = now;
	  }



	  // PORT D ( GPIOD )
	  // GPIO_PIN_15 = BLUE
	  // GPIO_PIN_14 = RED
	  // GPIO_PIN_13 = ORANGE
	  // GPIO_PIN_12 = GREEN

//	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
//	  HAL_Delay(100);
//
//	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
//	  HAL_Delay(100);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 12;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GREEN_Pin|ORANGE_Pin|RED_Pin|BLUE_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : USER_BTN_Pin */
  GPIO_InitStruct.Pin = USER_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(USER_BTN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : GREEN_Pin ORANGE_Pin RED_Pin BLUE_Pin */
  GPIO_InitStruct.Pin = GREEN_Pin|ORANGE_Pin|RED_Pin|BLUE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
