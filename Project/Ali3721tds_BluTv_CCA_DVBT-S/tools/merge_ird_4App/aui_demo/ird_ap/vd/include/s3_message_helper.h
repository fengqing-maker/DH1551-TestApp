/**
 * $Id: s3_message_helper.h,v 1.5 2011/04/21 06:08:11 jcao Exp $
 *
 * Copyright 2004 Irdeto Access B.V.
 *
 * This file and the information contained herein are the subject of copyright
 * and intellectual property rights under international convention. All rights
 * reserved. No part of this file may be reproduced, stored in a retrieval
 * system or transmitted in any form by any means, electronic, mechanical or
 * optical, in whole or in part, without the prior written permission of Irdeto
 * Access B.V.
 *
 * This file is part of the SoftCell 3 Integration library.
 **/

#ifndef S3_MESSAGE_HELPER_H
#define S3_MESSAGE_HELPER_H

typedef void * ia_msg_handle;

/*
 * Pocessing of incomming messages.
 */

/* Open a message for reading.
 * 	pvMessage: pointer to the message to be read.
 *	wLength: length of the message to be read.
 *	return: handle to the message. 0 on error.
 */
ia_msg_handle IA_OpenInputMessage( void *pvMessage, ia_word16 wLength );

/* Read from a message.
 *	hMessage: Handle to the message to read from.
 * 	pvBuffer: buffer to copy the data into.
 *	wLength: Number of bytes to read.
 *	return: Actual number of bytes read.
 */
ia_word16 IA_ReadFromMessage( ia_msg_handle hMessage, void *pvBuffer, ia_word16 wLength );


/*
 * Creating outgoing messages.
 */

/* Create a message to send to SoftCell. \
 *	wLength: The initail size of the buffer.
 *	wIncrement: Number of bytes the buffer must be incremented if if it becomes too small.
 *	return: handle to the message. 0 on error.
 */
ia_msg_handle IA_OpenOutputMessage( ia_word16 wLength, ia_word16 wIncrement );

/* Write to a message.
 *	hMessage: Handle to the message to write to.
 * 	pvBuffer: buffer to copy the data into.
 *	wLength: Number of bytes to read.
 *	return: Actual number of bytes written.
 */
ia_word16 IA_WriteToMessage( ia_msg_handle hMessage, void *pvBuffer, ia_word16 wLength );

/* Get the pointer to the start of the buffer.
 *	hMessage: Handle to the message to get the buffer from.
 *	return: pointer to the buffer or 0 if there is no data.
 */
void *IA_GetOutputMessage( ia_msg_handle hMessage );

/* Get the length of the stored message.
 *	hMessage: Handle to the message to get the length of.
 *	return: length of the data stored in the message.
 */
ia_word16 IA_GetOutputMessageLength( ia_msg_handle hMessage );


/*
 * Shared for reading and writing.
 */

/* Close a message.
 *	hMessage: Handle to the message to close.
 *	fFreeBuffer:
 * 		IA_TRUE if IA_CloseMessage must free the buffer.
 * 		IA_FALSE if the application will free the buffer.
 */
void IA_CloseMessage( ia_msg_handle hMessage, ia_bool fFreeBuffer );

/* Examples:

	Process message from SoftCell (received with CA_DRV_Message or through the virtual driver API).

	ia_msg_handle				hMessage;
	ia_word16 					wCount;
	msg_ecm_source_status_st    stStatus;
	msg_stream_status_st		stStream;

	hMessage = IA_OpenInputMessage( pvMessage, wLength );
	IA_ReadFromMessage( hMessage, &stStatus, sizeof( msg_ecm_source_status_st ) );
	for ( wCount = 0; wCount < stStatus.bSystemCount; wCount++ )
	{
		IA_ReadFromMessage( hMessage, &stStream, sizeof( msg_stream_status_st ) );
		// Process stream.
		...
	}
	// Finished with the message. Close it and free the buffer.
	IA_CloseMessage( hMessage, IA_TRUE );


	Process message to SoftCell.

	ia_msg_handle				hMessage;
	ia_word16 					wCount;
	msg_ecm_source_status_st    stStatus;
	msg_stream_status_st		stStream;

	...

	wMessageId = IA_OpenOutputMessage( 50, 10 );
	// Set data in stStatus.
	...
	IA_WriteToMessage( hMessage, &stStatus, sizeof( msg_ecm_source_status_st ) );
	for ( wCount = 0; wCount < stStatus.bSystemCount; wCount++ )
	{
		// Set data for stream in stStream.
		...
		IA_WriteToMessage( hMessage, &stStream, sizeof( msg_stream_status_st ) );
	}
	// Send message to SoftCell.
	if ( SCELL_Message( eMyOpcode, wOpSeqNo, IA_GetOutputMessage( hMessage ),
		IA_GetOutputMessageLength( hMessage ) ) == IA_SUCCESS )
	{
		// The buffer will be freed by the receiver.
		IA_CloseMessage( hMessage, IA_FALSE );
	}
	else
	{
		// Message not sent. We must free the buffer.
		IA_CloseMessage( hMessage, IA_TRUE );
	}
 */

#endif /* S3_MESSAGE_HELPER_H */
