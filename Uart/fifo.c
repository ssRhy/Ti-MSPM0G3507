#include "fifo.h"


volatile FIFO_t rxFIFO_d = {0};
volatile FIFO_t rxFIFO_u = {0};

/**
	* @brief   初始化队列
	* @param   无
	* @retval  无
	*/
void initQueue(void)
{
	rxFIFO_d.ptrRead  = 0;
	rxFIFO_d.ptrWrite = 0;
	rxFIFO_u.ptrRead  = 0;
	rxFIFO_u.ptrWrite = 0;
}

/**
	* @brief   入队
	* @param   无
	* @retval  无
	*/
void fifo_enQueue(uint16_t data, uint8_t add)
{
	if(add == 1)
	{
		rxFIFO_d.buffer[rxFIFO_d.ptrWrite] = data;
		
		++rxFIFO_d.ptrWrite;
		
		if(rxFIFO_d.ptrWrite >= FIFO_SIZE)
		{
			rxFIFO_d.ptrWrite = 0;
		}
	}
	else if(add == 2)
	{
		rxFIFO_u.buffer[rxFIFO_u.ptrWrite] = data;
		
		++rxFIFO_u.ptrWrite;
		
		if(rxFIFO_u.ptrWrite >= FIFO_SIZE)
		{
			rxFIFO_u.ptrWrite = 0;
		}
	}
}

/**
	* @brief   出队
	* @param   无
	* @retval  无
	*/
uint16_t fifo_deQueue(uint8_t add)
{
	uint16_t element = 0;
	if(add == 1)
	{
		element = rxFIFO_d.buffer[rxFIFO_d.ptrRead];

		++rxFIFO_d.ptrRead;

		if(rxFIFO_d.ptrRead >= FIFO_SIZE)
		{
			rxFIFO_d.ptrRead = 0;
		}
	}
	else if(add == 2)
	{
		element = rxFIFO_u.buffer[rxFIFO_u.ptrRead];

		++rxFIFO_u.ptrRead;

		if(rxFIFO_u.ptrRead >= FIFO_SIZE)
		{
			rxFIFO_u.ptrRead = 0;
		}
	}
	return element;
}

/**
	* @brief   判断空队列
	* @param   无
	* @retval  无
	*/
bool fifo_isEmpty(uint8_t add)
{
	if(add == 1)
	{
		if(rxFIFO_d.ptrRead == rxFIFO_d.ptrWrite)
		{
			return true;
		}
	}
	else if(add == 2)
	{
		if(rxFIFO_u.ptrRead == rxFIFO_u.ptrWrite)
		{
			return true;
		}
	}
	return false;
}

/**
	* @brief   计算队列长度
	* @param   无
	* @retval  无
	*/
uint16_t fifo_queueLength(uint8_t add)
{
	if(add == 1)
	{
		if(rxFIFO_d.ptrRead <= rxFIFO_d.ptrWrite)
		{
			return (rxFIFO_d.ptrWrite - rxFIFO_d.ptrRead);
		}
		else
		{
			return (FIFO_SIZE - rxFIFO_d.ptrRead + rxFIFO_d.ptrWrite);
		}
	}
	else if(add == 2)
	{
		if(rxFIFO_u.ptrRead <= rxFIFO_u.ptrWrite)
		{
			return (rxFIFO_u.ptrWrite - rxFIFO_u.ptrRead);
		}
		else
		{
			return (FIFO_SIZE - rxFIFO_u.ptrRead + rxFIFO_u.ptrWrite);
		}
	}
}
