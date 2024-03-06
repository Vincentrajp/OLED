/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "SSD1322_OLED_lib/SSD1322_HW_Driver.h"
#include "SSD1322_OLED_lib/SSD1322_API.h"
#include "SSD1322_OLED_lib/SSD1322_GFX.h"

#include "SSD1322_OLED_lib/Fonts/FreeMono12pt7b.h"
#include "SSD1322_OLED_lib/Fonts/FreeSansOblique9pt7b.h"

#include "tom_and_jerry.h"
#include "creeper.h"
#include "krecik.h"
#include "pat_i_mat.h"
#include "stars_4bpp.h"

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
I2S_HandleTypeDef hi2s3;

SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2S3_Init(void);
static void MX_SPI1_Init(void);
void MX_USB_HOST_Process(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_I2S3_Init();
  MX_SPI1_Init();
  MX_USB_HOST_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  /*==================================== DEMO CODE START ============================================*/

  	// Declare bytes array for a frame buffer.
  	// Dimensions are divided by 2 because one byte contains two 4-bit grayscale pixels
  	uint8_t tx_buf[256 * 64 / 2];

  	//Call initialization seqence for SSD1322
  	SSD1322_API_init();
  while (1)
  {
    /* USER CODE END WHILE */
    MX_USB_HOST_Process();

    /* USER CODE BEGIN 3 */
    //Set frame buffer size in pixels - it is used to avoid writing to memory outside frame buffer.
    		//Normally it has to only be done once on initialization, but buffer size is changed near the end of while(1);
    		set_buffer_size(256, 64);
    		// Fill buffer with zeros to clear any garbage values
    		fill_buffer(tx_buf, 0);

    		// send a frame buffer to the display
    		send_buffer_to_OLED(tx_buf, 0, 0);
    		HAL_Delay(2000);

    		// Let's try some features of this OLED display

    		// First, draw some pixels on frame buffer
    		// draw_pixel(frame_buffer, x, y, brightness);
    		draw_pixel(tx_buf, 10, 10, 1);
    		draw_pixel(tx_buf, 15, 15, 5);
    		draw_pixel(tx_buf, 20, 20, 9);
    		draw_pixel(tx_buf, 25, 25, 15);

    		// send a frame buffer to the display
    		send_buffer_to_OLED(tx_buf, 0, 0);
    		HAL_Delay(2000);

    		// draw vertical and horizontal lines
    		draw_hline(tx_buf, 31, 20, 50, 10);
    		draw_vline(tx_buf, 31, 0, 31, 10);

    		// send a frame buffer to the display
    		send_buffer_to_OLED(tx_buf, 0, 0);
    		HAL_Delay(2000);

    		// draw simple oblique line
    		draw_line(tx_buf, 40, 0, 80, 31, 12);
    		// send a frame buffer to the display
    		send_buffer_to_OLED(tx_buf, 0, 0);
    		HAL_Delay(2000);

    		// draw antialiased oblique line. It should appear softer and nicer than a simple one
    		draw_AA_line(tx_buf, 50, 0, 90, 31, 12);
    		// send a frame buffer to the display
    		send_buffer_to_OLED(tx_buf, 0, 0);
    		HAL_Delay(2000);

    		//draw circle, empty rectangle and filled rectangle
    		draw_circle(tx_buf, 180, 20, 20, 15);
    		draw_rect(tx_buf, 100, 5, 120, 25, 15);
    		draw_rect_filled(tx_buf, 124, 5, 144, 25, 8);
    		// send a frame buffer to the display
    		send_buffer_to_OLED(tx_buf, 0, 0);
    		HAL_Delay(2000);

    		//clean buffer
    		fill_buffer(tx_buf, 0);

    		//display 8-bit grayscale bitmap (ony first 4 bits are actually written to memory)
    		draw_bitmap_8bpp(tx_buf, pat_i_mat, 0, 0, 64, 64);
    		draw_bitmap_8bpp(tx_buf, krecik, 128, 0, 64, 64);
    		// send a frame buffer to the display
    		send_buffer_to_OLED(tx_buf, 0, 0);
    		HAL_Delay(5000);

    		//display 4-bit grayscale bitmap (one byte in bitmap array corresponds to two pixels)
    		draw_bitmap_4bpp(tx_buf, stars_4bpp, 0, 0, 256, 64);
    		send_buffer_to_OLED(tx_buf, 0, 0);
    		HAL_Delay(3000);

    		//you can invert screen colors using API function
    		SSD1322_API_set_display_mode(SSD1322_MODE_INVERTED);
    		HAL_Delay(2000);
    		//pixels can be also turned on or off
    		SSD1322_API_set_display_mode(SSD1322_MODE_ON);
    		HAL_Delay(1000);
    		SSD1322_API_set_display_mode(SSD1322_MODE_OFF);
    		HAL_Delay(1000);
    		//ok, go back to normal
    		SSD1322_API_set_display_mode(SSD1322_MODE_NORMAL);
    		HAL_Delay(500);

    		//exact grayscale values can be set individually for each level from 0 to 15 - always send 16 byte array of values 0-180
    		uint8_t grayscale_tab[16] = {0, 5, 10, 15, 20, 25, 30, 35, 145, 150, 155, 160, 165, 170, 175, 180};
    		SSD1322_API_custom_grayscale(grayscale_tab);
    		HAL_Delay(2000);
    		//New grayscale values should be close to black in darker areas and close to white in brighter

    		//reset grayscale to default linear values
    		SSD1322_API_default_grayscale();
    		HAL_Delay(2000);

    		//display can be set to sleep mode and then woken up
    		SSD1322_API_sleep_on();
    		HAL_Delay(1000);
    		SSD1322_API_sleep_off();

    		//clean buffer
    		fill_buffer(tx_buf, 0);

    		// now let's try to write some text with a font
    		// first thing to do is font selection
    		select_font(&FreeMono12pt7b);
    		// now text will we written with that font
    		draw_text(tx_buf, "Lorem ipsum", 10, 20, 15);
    		// send a frame buffer to the display
    		send_buffer_to_OLED(tx_buf, 0, 0);
    		HAL_Delay(2000);

    		//change font to a differen one
    		select_font(&FreeSansOblique9pt7b);
    		draw_text(tx_buf, "dolor sit amet", 10, 45, 15);
    		// send a frame buffer to the display
    		send_buffer_to_OLED(tx_buf, 0, 0);
    		HAL_Delay(2000);

    		//you can use frame buffer that is bigger than default 256x64 pixels.
    		//Remember to divide size by two, because one byte stores two pixels.

    		uint8_t tx_buf2[256*256 / 2];
    		set_buffer_size(256, 256);

    		//now print a huge bitmap into frame buffer
    		draw_bitmap_8bpp(tx_buf2, creeper, 0, 0, 256, 256);
    		send_buffer_to_OLED(tx_buf2, 0, 0);
    		HAL_Delay(2000);

    		//only 1/4 of image is seen, so let's scroll the frame buffer down
    		for(int i = 0; i < 192; i++)
    		{
    			send_buffer_to_OLED(tx_buf2, 0, i);
    			HAL_Delay(5);
    		}
    		HAL_Delay(200);
    		for (int i = 191; i >= 0; i--)
    		{
    			send_buffer_to_OLED(tx_buf2, 0, i);
    			HAL_Delay(5);
    		}
    		HAL_Delay(2000);
    		/*==================================== DEMO CODE END ============================================*/

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
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2S3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S3_Init(void)
{

  /* USER CODE BEGIN I2S3_Init 0 */

  /* USER CODE END I2S3_Init 0 */

  /* USER CODE BEGIN I2S3_Init 1 */

  /* USER CODE END I2S3_Init 1 */
  hi2s3.Instance = SPI3;
  hi2s3.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s3.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s3.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s3.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;
  hi2s3.Init.AudioFreq = I2S_AUDIOFREQ_96K;
  hi2s3.Init.CPOL = I2S_CPOL_LOW;
  hi2s3.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s3.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S3_Init 2 */

  /* USER CODE END I2S3_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(CS_I2C_SPI_GPIO_Port, CS_I2C_SPI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PowerSwitchOn_GPIO_Port, OTG_FS_PowerSwitchOn_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RES_Pin|CS_Pin|SHDN_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BS1_GPIO_Port, BS1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BS0_GPIO_Port, BS0_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, DC_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD6_Pin|Audio_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : CS_I2C_SPI_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(CS_I2C_SPI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PDM_OUT_Pin */
  GPIO_InitStruct.Pin = PDM_OUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(PDM_OUT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BOOT1_Pin */
  GPIO_InitStruct.Pin = BOOT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BOOT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : CLK_IN_Pin */
  GPIO_InitStruct.Pin = CLK_IN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
  HAL_GPIO_Init(CLK_IN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RES_Pin CS_Pin SHDN_Pin BS1_Pin */
  GPIO_InitStruct.Pin = RES_Pin|CS_Pin|SHDN_Pin|BS1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BS0_Pin DC_Pin LD4_Pin LD3_Pin
                           LD5_Pin LD6_Pin Audio_RST_Pin */
  GPIO_InitStruct.Pin = BS0_Pin|DC_Pin|LD4_Pin|LD3_Pin
                          |LD5_Pin|LD6_Pin|Audio_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_OverCurrent_Pin */
  GPIO_InitStruct.Pin = OTG_FS_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OTG_FS_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Audio_SCL_Pin Audio_SDA_Pin */
  GPIO_InitStruct.Pin = Audio_SCL_Pin|Audio_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(MEMS_INT2_GPIO_Port, &GPIO_InitStruct);

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
