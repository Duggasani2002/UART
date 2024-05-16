typedef unsigned int u32;
typedef signed int s32;
typedef unsigned char u8;
typedef signed char s8;

/*CAN DEF*/
typedef struct can1_msg
{
	u32 id;
	u8 rtr;
	u8 dlc;
	u32 byteA;
	u32 byteB;
}CAN1;
extern void can1_init(void);
extern void can1_tx(CAN1 v);

/*UART DEF*/
extern void uart0_init(int baud);
extern void uart0_tx(u8 data);
extern u8 uart0_rx(void);
extern void uart0_tx_int(u32 data);
extern void uart0_tx_float(float data);
extern void uart0_rx_string(s8 *ptr,u8 max_bytes);
extern void uart0_tx_hex(u8 temp);

/*LCD DEF*/
extern void lcd_init(void);
extern void lcd_data(u8 data);
extern void lcd_cmd(u8 data);
extern void lcd_string(u8 *ptr);
extern void lcd_int(u32 data);
extern void print_two_digit(u32 data);

/*ADC DEF*/
extern void adc_init(void);
extern u32 adc_read(u8 ch_num);

extern void delay_ms(u32 ms);

/*I2C DEF*/
extern void i2c_init(void);
extern void i2c_byte_write_frame(u8 sa,u8 mr,u8 data);
extern u8 i2c_byte_read_frame(u8 sa,u8 mr);
