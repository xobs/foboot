#ifndef BB_SPI_H_
#define BB_SPI_H_

#include <stdint.h>

enum spi_state {
	SS_UNCONFIGURED = 0,
	SS_SINGLE,
	SS_DUAL_RX,
	SS_DUAL_TX,
	SS_QUAD_RX,
	SS_QUAD_TX,
	SS_HARDWARE,
};

enum spi_type {
	ST_UNCONFIGURED,
	ST_SINGLE,
	ST_DUAL,
	ST_QUAD,
	ST_QPI,
};

enum spi_pin {
	SP_MOSI,
	SP_MISO,
	SP_HOLD,
	SP_WP,
	SP_CS,
	SP_CLK,
	SP_D0,
	SP_D1,
	SP_D2,
	SP_D3,
};

struct spi_id {
	uint8_t manufacturer_id;	// Result from 0x90
	uint8_t device_id;		// Result from 0x90
	uint8_t _manufacturer_id;	// Result from 0x9f
	uint8_t memory_type;		// Result from 0x9f
	uint8_t memory_size;		// Result from 0x9f
	uint8_t signature;		// Result from 0xab
	uint8_t serial[4];		// Result from 0x4b
	int bytes;			// -1 if unknown
	const char *manufacturer;
	const char *model;
	const char *capacity;
};

void spi_pause(void);
void spi_begin(void);
void spi_end(void);

//void spiSingleTx(uint8_t out);
//uint8_t spiSingleRx(void);
//void spiDualTx(uint8_t out);
//void spiQuadTx(uint8_t out);
//uint8_t spiDualRx(void);
//uint8_t spiQuadRx(void);
uint8_t spi_read_status(uint8_t sr);
void spiWriteStatus(uint8_t sr, uint8_t val);
void spiReadSecurity(uint8_t sr, uint8_t security[256]);
void spiWriteSecurity(uint8_t sr, uint8_t security[256]);
int spiSetType(enum spi_type type);
int spiRead(uint32_t addr, uint8_t *data, unsigned int count);
int spiIsBusy(void);
int spiBeginErase32(uint32_t erase_addr);
int spiBeginErase64(uint32_t erase_addr);
int spiBeginWrite(uint32_t addr, const void *data, unsigned int count);
void spiEnableQuad(void);

uint32_t spiId(void);

uint8_t spi_reset(void);
int spi_init(void);
void spi_free(void);

void spi_hold(void);
void spi_unhold(void);

void write_to_flash_page(unsigned int addr, const unsigned char *c, unsigned int len);
void erase_flash_sector(unsigned int addr);

#endif /* BB_SPI_H_ */
