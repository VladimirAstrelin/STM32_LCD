/*

  ******************************************************************************
  * @file 			( фаил ):   LCD1602.c
  * @brief 		( описание ):  	
  ******************************************************************************
  * @attention 	( внимание ):	author: Golinskiy Konstantin	e-mail: golinskiy.konstantin@gmail.com
  ******************************************************************************
  
*/

/* Includes ----------------------------------------------------------*/
#include "LCD1602.h"


uint8_t portLcd = 0;	// переменная для хранения текущего состояния порта Экрана
	
/*
	******************************************************************************
	* @brief	 ( описание ):  Функция отправляющая 1 байт в Экран
	* @param	( параметры ):	1 байт информации
	* @return  ( возвращает ):	

	******************************************************************************
*/
static void LCD_WriteByte( uint8_t bt ){
	
	#if defined (LCD1602_I2C)
	
		HAL_I2C_Master_Transmit( &LCD_I2C, ADRESS_I2C_LCD, &bt, 1, 1000 );
	
	#elif defined (LCD1602_4BIT) 

		// 0b00000001
		if( bt & 0x01 ){ RS_GPIO_Port -> BSRR = RS_Pin;				}	// SET ( HIGH )
		else{	RS_GPIO_Port -> BSRR = ((uint32_t)RS_Pin << 16 );	}	// RESET ( LOW )

		// 0b00000010
//		if( bt & 0x02 ){ RW_GPIO_Port -> BSRR = RW_Pin;				}	// SET ( HIGH )
//		else{	RW_GPIO_Port -> BSRR = ((uint32_t)RW_Pin << 16 );	}	// RESET ( LOW )

		// 0b00000100
		if( bt & 0x04 ){ E_GPIO_Port -> BSRR = E_Pin;				}	// SET ( HIGH )
		else{	E_GPIO_Port -> BSRR = ((uint32_t)E_Pin << 16 );		}	// RESET ( LOW )

		// 0b00001000
//		if( bt & 0x08 ){ BLK_GPIO_Port -> BSRR = BLK_Pin;			}	// SET ( HIGH )
//		else{	BLK_GPIO_Port -> BSRR = ((uint32_t)BLK_Pin << 16 );	}	// RESET ( LOW )

		// 0b00010000
		if( bt & 0x10 ){ DB4_GPIO_Port -> BSRR = DB4_Pin;			}	// SET ( HIGH )
		else{	DB4_GPIO_Port -> BSRR = ((uint32_t)DB4_Pin << 16 );	}	// RESET ( LOW )

		// 0b00100000
		if( bt & 0x20 ){ DB5_GPIO_Port -> BSRR = DB5_Pin;			}	// SET ( HIGH )
		else{	DB5_GPIO_Port -> BSRR = ((uint32_t)DB5_Pin << 16 );	}	// RESET ( LOW )

		// 0b01000000
		if( bt & 0x40 ){ DB6_GPIO_Port -> BSRR = DB6_Pin;			}	// SET ( HIGH )
		else{	DB6_GPIO_Port -> BSRR = ((uint32_t)DB6_Pin << 16 );	}	// RESET ( LOW )

		// 0b10000000
		if( bt & 0x80 ){ DB7_GPIO_Port -> BSRR = DB7_Pin;			}	// SET ( HIGH )
		else{	DB7_GPIO_Port -> BSRR = ((uint32_t)DB7_Pin << 16 );	}	// RESET ( LOW )

	#endif
		
}
//------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ):  Функция для отправки полного байта информации ( для 8 битного режима )
	* @param	( параметры ):	1 байт информации
	* @return  ( возвращает ):	

	******************************************************************************
*/
static void LCD_SendCmd_8bit( uint8_t bt ){
	
	LCD_WriteByte( portLcd |= 0x04 );			// Включаем линию Е ставим в 1, активируем дисплей.
	HAL_Delay( 1 );
	LCD_WriteByte( portLcd | bt );				// Отправляем в дисплей полученный и сдвинутый байт
	LCD_WriteByte( portLcd &=~ 0x04 );			// Выключаем линию Е ставим в 0, деактивируем дисплей.
	HAL_Delay( 1 );
}
//-------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ):  Функция для отправки пол байта информации ( так как экран работает в четырех битном режиме )
	* @param	( параметры ):	1 байт информации
	* @return  ( возвращает ):	

	******************************************************************************
*/
static void LCD_SendCmd( uint8_t bt ){
	
	bt <<= 4;
	LCD_SendCmd_8bit( bt );
}
//-------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ):  Функция для отправки полного 1 байта информации или команды
	* @param	( параметры ):	Первый параметр байт данных второй режим RW 1-отправка данных, 0-отправка команды.
	* @return  ( возвращает ):	

	******************************************************************************
*/
static void LCD_SendByte( uint8_t bt, uint8_t mode ){
	
	if( mode == 0 ){ 
		LCD_WriteByte( portLcd &=~ 0x01 ); // RS = 0;
	}	
	else {
		LCD_WriteByte( portLcd |= 0x01 ); // RS = 1;
	}	
	
	
	// Дальше отправка команды или данных двумя пакетами ( делим полученный байт на 2 ) и по 4 бита СТАРШпХ передаем
	uint8_t tempBuf = 0;
	tempBuf = bt>>4;			// Сдвигаем полученный байт на 4 позичии и записываем в переменную
	
	LCD_SendCmd( tempBuf );		// Отправляем первые 4 бита полученного байта
	LCD_SendCmd( bt );	   		// Отправляем последние 4 бита полученного байта
}
//---------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ):  Функция инициализации дисплея
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_Init(void){
	
	// если по одному варианту инициализация не прошла пробуем другой или пишем свой по даташиту
	// так как у каждого производителя немного отличается инициализация
	
//######## вариант инициализации номер 1 #######################################################	
//	// отправляем 3 раза команду ( указана в даташите ) ------------------------------
//	HAL_Delay( 40 );
//	LCD_SendCmd_8bit( 0x30 );	
//	HAL_Delay( 40 );
//	LCD_SendCmd_8bit( 0x30 );	
//	HAL_Delay( 40 );
//	LCD_SendCmd_8bit( 0x30 );
//	//---------------------------------------------------------------------------------
//	// Включаем 4х-битный интерфейс ---------------------------------------------------
//	HAL_Delay( 1 );
//	LCD_SendCmd_8bit( 0x20 );	
//	HAL_Delay( 1 );
// 	//---------------------------------------------------------------------------------
//	// 2 строки, шрифт 5х11	
//	LCD_SendCmd_8bit( 0x20 );
//	HAL_Delay( 1 );
//	LCD_SendCmd_8bit( 0x80 );
//	HAL_Delay( 1 );
//	//---------------------------------------------------------------------------------
//	// Очистить дисплей ---------------------------------------------------------------	
//	LCD_SendCmd_8bit( 0x00 );
//	HAL_Delay( 1 );
//	LCD_SendCmd_8bit( 0x10 );
//	HAL_Delay( 1 );
//	//---------------------------------------------------------------------------------
//	// Режим сдвига курсора -----------------------------------------------------------	
//	LCD_SendCmd_8bit( 0x00 );
//	HAL_Delay( 1 );
//	LCD_SendCmd_8bit( 0x30 );
//	HAL_Delay( 1 );
//	//---------------------------------------------------------------------------------
//	// Инициализация завершена. Включить дисплей --------------------------------------
//	LCD_SendCmd_8bit( 0x00 );
//	HAL_Delay( 1 );
//	LCD_SendCmd_8bit( 0x30 );
//	//---------------------------------------------------------------------------------
//###############################################################################################

//######## вариант инициализации номер 2 #######################################################
	// данные пораметры нужны по даташиту экрана -------------------------------------------
	HAL_Delay( 50 );
	LCD_SendCmd( 0x03 );	// 0x03
	HAL_Delay( 5 );
	LCD_SendCmd( 0x03 );	// 0x03
	HAL_Delay( 1 );
	LCD_SendCmd( 0x03 );	// 0x03
	HAL_Delay( 10 );
	
	LCD_SendCmd( 0x02 );	// 0x02 // 4bit mode
	HAL_Delay( 2 );
	
	//---------------------------------------------------------------------------------
	// режим 4 бит, 2 линии ( для 2004 4 линии ), 0x28 шрифт 5*8 ( либо 0x38 режим 4 бит, 2 линии , шрифт 5*7 )	
	LCD_SendByte( 0x38, 0 );	
	HAL_Delay( 2 );
	//---------------------------------------------------------------------------------
	
	LCD_SendByte( 0x02, 0 );	// возвращаем курсор в 0 позицию
	HAL_Delay( 2 );
	LCD_SendByte( 0x0C, 0 );	// дисплей активируем без курсора
	HAL_Delay( 2 );
	LCD_SendByte( 0x01, 0 );	// очищаем дисплей
	HAL_Delay( 2 );
	LCD_SendByte( 0x06, 0 );	// пишем в лево
	HAL_Delay( 1 );
	//---------------------------------------------------------------------------------
	
	LCD_WriteByte( portLcd |= 0x08 );	// Включаем подсветку
	LCD_WriteByte (portLcd &=~ 0x02 );	// устанавливаем в режим записи ( чтобы отправлять данные или команды )
	//---------------------------------------------------------------------------------	
	
//###############################################################################################
}
//----------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ): Функция печати строки на дисплее ( поддерживает как Киррилицу так и латиницу )
	* @param	( параметры ): Строка
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_PrintString( char* str ){

	#ifndef	FONT_CYRILLIC
		uint8_t i = 0;
		
		while( str[i] != 0 ){
			LCD_SendByte( str[i], 1 );
			i++;
		}
	#else
		unsigned char buff_char;
		
		uint8_t i = 0;
		
		while( str[i] != 0 ){
			
			//---------------------------------------------------------------------
			// проверка на кириллицу UTF-8, если латиница то пропускаем if
			// Расширенные символы ASCII Win-1251 кириллица (код символа 128-255)
			// проверяем первый байт из двух ( так как UTF-8 ето два байта )
			// если он больше либо равен 0xC0 ( первый байт в кириллеце будет равен 0xD0 либо 0xD1 именно в алфавите )
			if ( (uint8_t)str[i] >= 0xC0 ){	// код 0xC0 соответствует символу кириллица 'A' по ASCII Win-1251

				// проверяем какой именно байт первый 0xD0 либо 0xD1
				switch ((uint8_t)str[i]) {
					case 0xD0: {
						// увеличиваем массив так как нам нужен второй байт
						i++;
						// проверяем второй байт там сам символ
						if ((uint8_t)str[i] >= 0x90 && (uint8_t)str[i] <= 0xBF){ buff_char = str[i] + 0x30; }	// байт символов А...Я а...п  делаем здвиг на +48
						else if ((uint8_t)str[i] == 0x81) { buff_char = 0xA8; break; }		// байт символа Ё ( если нужнф еще символы добавляем )
						else if ((uint8_t)str[i] == 0x84) { buff_char = 0xAA; break; }		// байт символа Є ( если нужнф еще символы добавляем )
						else if ((uint8_t)str[i] == 0x86) { buff_char = 0xB2; break; }		// байт символа І ( если нужнф еще символы добавляем )
						else if ((uint8_t)str[i] == 0x87) { buff_char = 0xAF; break; }		// байт символа Ї ( если нужнф еще символы добавляем )
						break;
					}
					case 0xD1: {
						// увеличиваем массив так как нам нужен второй байт
						i++;
						// проверяем второй байт там сам символ
						if ((uint8_t)str[i] >= 0x80 && (uint8_t)str[i] <= 0x8F){ buff_char = str[i] + 0x70; }	// байт символов п...я	елаем здвиг на +112
						else if ((uint8_t)str[i] == 0x91) { buff_char = 0xB8; break; }		// байт символа ё ( если нужнф еще символы добавляем )
						else if ((uint8_t)str[i] == 0x94) { buff_char = 0xBA; break; }		// байт символа є ( если нужнф еще символы добавляем )
						else if ((uint8_t)str[i] == 0x96) { buff_char = 0xB3; break; }		// байт символа і ( если нужнф еще символы добавляем )
						else if ((uint8_t)str[i] == 0x97) { buff_char = 0xBF; break; }		// байт символа ї ( если нужнф еще символы добавляем )
						break;
					}
				}
				
				//-- Киррилица -----------------------------------------------------------
				if( (uint8_t) buff_char > 191 ){
					LCD_SendByte( Font_Cyrillic[(buff_char - 192)], 1 );
				}
				if( (uint8_t) buff_char == 168 ){	// 168 символ по ASCII - Ё
					LCD_SendByte( Font_Cyrillic[64], 1 );
				}
				if( (uint8_t) buff_char == 184 ){	// 184 символ по ASCII - ё
					LCD_SendByte( Font_Cyrillic[65], 1 );
				}
				//-----------------------------------------------------------------------
				//----  Украинская раскладка --------------------------------------------
				if( (uint8_t) buff_char == 170 ){	// 168 символ по ASCII - Є
					LCD_SendByte( Font_Cyrillic[66], 1 );
				}
				if( (uint8_t) buff_char == 175 ){	// 184 символ по ASCII - Ї
					LCD_SendByte( Font_Cyrillic[67], 1 );
				}	
				if( (uint8_t) buff_char == 178 ){	// 168 символ по ASCII - І
					LCD_SendByte( Font_Cyrillic[68], 1 );
				}
				if( (uint8_t) buff_char == 179 ){	// 184 символ по ASCII - і
					LCD_SendByte( Font_Cyrillic[69], 1 );
				}
				if( (uint8_t) buff_char == 186 ){	// 184 символ по ASCII - є
					LCD_SendByte( Font_Cyrillic[70], 1 );
				}
				if( (uint8_t) buff_char == 191 ){	// 168 символ по ASCII - ї
					LCD_SendByte( Font_Cyrillic[71], 1 );
				}				
				//-----------------------------------------------------------------------
			}
			//---------------------------------------------------------------------
			else{
				LCD_SendByte( str[i], 1 );
			}
			// увеличеваем индекс
			i++;
		}
	#endif
}
//-----------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ):  Функция очистки всего дисплея
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_Clear(void){
	
	LCD_SendByte( 0x01, 0 );
	HAL_Delay(2);
}
//--------------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ):  Функция включения и выключения подсветки дисплея
	* @param	( параметры ):	( 0-выкл, 1 (либо другое от 0)- вкл )
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_LedOnOff( uint8_t status ){
	
	if( status == 0 ){
		LCD_WriteByte( portLcd &=~ 0x08 ); 		// Выключаем подсветку 
	}	
	else {
		LCD_WriteByte( portLcd |= 0x08 ); 		// Включаем подсветку  
	}	
}
//-----------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ):  Функция установки курсора ( позиционирования )
	* @param	( параметры ):	( 1-й параметр позиция символа , 2-й параметр строка, ( Счет с нуля )
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_SetCursor( uint8_t x, uint8_t y ){
	
	switch( y ){
		// Для дисплея 2004 нужно 4 кейса для 1602 два кейса
		case 0:
			LCD_SendByte( x | 0x80, 0 );
			HAL_Delay( 1 );
			break;
		case 1:
			LCD_SendByte( ( 0x40 + x ) | 0x80, 0 );
			HAL_Delay( 1 );
			break;
		case 2:
			LCD_SendByte( ( 0x14 + x ) | 0x80, 0 );
			HAL_Delay( 1 );
			break;
		case 3:
			LCD_SendByte( ( 0x54 + x ) | 0x80, 0 );
			HAL_Delay( 1 );
			break;
		default:
			break;
	}
}
//--------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ): функция двигает надпись вправо на 1 символ ( бегущая строка ) 
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_StringRunR( void ){
	
	LCD_SendByte( 0x1C , 0);
}
//--------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ): функция двигает надпись влево на 1 символ ( бегущая строка ) 
	* @param	( параметры ):	
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_StringRunL( void ){
	
	  LCD_SendByte( 0x18 , 0);
}
//--------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ): функция выключает надпись на єкране (єкран пустой ) и включает ее обратно 
	* @param	( параметры ): ( 0- выкл, 1 ( или любое отличное от 0 ) вкл )
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_TextOnOff( uint8_t status ){
	
	if( status == 0 ){
		LCD_SendByte( 0x08, 0 );	// отключение на дисплее надписи ( подсветка остается вкл ) надпись храниться но не видема
	}	
	else {
		LCD_SendByte( 0x0C, 0 ); 	// включение надписи на дисплее после того как ее отключили
	}	
}
//---------------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ):	функция создания своего символа и записи его в память 
	* @param	( параметры ): 	Первый параметр массив с символом
								второй парамет номер ячеки куда записали от 0 до 7 ( всего 8 символов можно записать )
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_CreateChar( uint8_t *mc , uint8_t add ){
	
	if( add < 8 ){
		// Команда для того что мы будем писать данные в память CGRAM он начинаеться с адресса 0x00
		// Таким образом, начав запись с адреса 0х00, мы записали наш символ в первый столбец(отсчет столбцов начинается с нуля).
		// Память на 8 символов адресса 0=0x00; 1=0x08; 2=0x10; и т.д каждый рас увеличиваем на 8
		LCD_SendByte( ( ( add * 0x08 ) | 0x40 ) , 0 );	
		
			// записываем данные побайтово в память
			for (uint8_t i = 0; i < 8; i++)
			{
				LCD_SendByte( mc[i], 1 );
			}
	}
		
}
//----------------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ): функция для отображения собственного символа ( печать на дисплей ) 
								перед вызавом своего символа обязательно вызываем LCD_SetCursor();
	* @param	( параметры ):	номер памяти куда сохранили символ от 0 до 7
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_PrintMyChar( uint8_t numChar ){
	
	if( numChar < 8 ){
		//указываем тот самый столбец, который хотим вывести
		LCD_SendByte ( numChar , 1 );
	}
}

//------------------------------------------------------------------------------------------------------------------------------



/*
	******************************************************************************
	* @brief	 ( описание ):  Функция включения и выключения мигания курсора
	* @param	( параметры ):	( 0-выкл, 1 (либо другое от 0)- вкл )
	* @return  ( возвращает ):	

	******************************************************************************
*/
void LCD_CursorOnOff( uint8_t status ){
	
	if( status == 0 ){
		LCD_SendByte( 0x0C, 0 ); 
	}	
	else {
		LCD_SendByte( 0x0F, 0 ); 
	}	
}
//------------------------------------------------------------------------------------------------------------------------------
//============================================

int summa(int a, int b){
	return a+b;
}
//============================================



//----------------------------------------------------------------------------------

/************************ (C) COPYRIGHT GKP *****END OF FILE****/
