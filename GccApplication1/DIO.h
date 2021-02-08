/*
 * DIO.h
 *
 * Created: 9/9/2019 11:08:38 AM
 *  Author: Nasser
 */ 


#ifndef DIO_H_
#define DIO_H_
	
	void DIO_setdir (unsigned char portname, unsigned char pinnumber, unsigned char direction);
	
	void DIO_write (unsigned char portname, unsigned char pinnumber, unsigned char outval);

	unsigned char DIO_read (unsigned char portname, unsigned char pinnumber);
	
	void DIO_write_port(unsigned char portname,unsigned char portvalue);
	
	void DIO_setdir_port(unsigned char portname,unsigned char direction);

#endif /* DIO_H_ */