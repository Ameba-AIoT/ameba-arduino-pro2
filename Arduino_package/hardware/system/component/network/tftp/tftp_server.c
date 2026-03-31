#include <FreeRTOS.h>
#include <task.h>
#include <platform_stdlib.h>
#include <lwipconf.h>
#include "tftp.h"

#include <errno.h>

#include "wifi_conf.h"

int tftp_server_recv(int sock, char *pFilename, struct sockaddr_in client, char *pMode, int tid, tftp *tftp_handler) //client put data into server
{
	/* To avoid gcc warnings */
	(void) pFilename;
	(void) pMode;

	/* local variables */
	int len, client_len, opcode, i, n;
	unsigned short int count = 0, rcount = 0;
	//unsigned char filebuf[64];
	unsigned char packetbuf[64];
	char *bufindex, ackbuf[12];
	struct sockaddr_in data;
	n = BLOCK_SIZE;

	client_len = sizeof(data);

	fd_set read_fds;
	struct timeval time_out;

	while (1) {

		//printf("count = %d\r\n",count);

		len = sprintf(ackbuf, "%c%c%c%c", 0x00, 0x04, 0x00, 0x00);
		ackbuf[2] = (count & 0xFF00) >> 8;	//fill in the count (top number first)
		ackbuf[3] = (count & 0x00FF);	//fill in the lower part of the count

		//printf ("Sending ack # %04d (length: %d)\n", count, len);

		if (sendto(sock, ackbuf, len, 0, (struct sockaddr *) &client, sizeof(client)) != len) {
			printf("Mismatch in number of sent bytes\n");
			goto EXIT;
		}

		if (n != BLOCK_SIZE) {	/* remember if our datasize is less than a full packet this was the last packet to be received */
			printf("Last chunk detected (file chunk size: %d). exiting while loop\n", n - 4);
			goto FINISH;		/* gotos are not optimal, but a good solution when exiting a multi-layer loop */
		}

		count++;

		for (i = 0; i < tftp_handler->tftp_retry_num; i++) {

			time_out.tv_sec = tftp_handler->tftp_timeout;	// Set select timeout of 3 seconds
			time_out.tv_usec = 0;
			FD_ZERO(&read_fds) ;
			FD_SET(sock, &read_fds);	// Only set server fd

			if (select(sock + 1, &read_fds, NULL, NULL, &time_out) == 1) {
				n = recvfrom(sock, tftp_handler->tftp_buf, BLOCK_SIZE, 0, (struct sockaddr *) &data, (socklen_t *) & client_len);
				if (n < 0) {
					printf("could not read datagram\r\n");
					goto EXIT;
				}
			} else {
				printf("timeout\r\n");
			}

			if (client.sin_addr.s_addr != data.sin_addr.s_addr)  {	/* checks to ensure get from ip is same from ACK IP */
				printf("Error recieving file (data from invalid address)\r\n");
				continue;	/* we aren't going to let another connection spoil our first connection */
			}

			if (tid != ntohs(client.sin_port)) {	/* checks to ensure get from the correct TID */
				printf("Error recieving file (data from invalid tid)\r\n");
				len = sprintf((char *) packetbuf, "%c%c%c%cBad/Unknown TID%c", 0x00, 0x05, 0x00, 0x05, 0x00);
				if (sendto(sock, packetbuf, len, 0, (struct sockaddr *) &client, sizeof(client)) != len) {	/* send the data packet */
					printf("Mismatch in number of sent bytes while trying to send mode error packet\r\n");
				}
				i--;
				//j--;
				continue;	/* we aren't going to let another connection spoil our first connection */
			}

			/* this formatting code is just like the code in the main function */
			bufindex = (char *) tftp_handler->tftp_buf;	//start our pointer going

			if (bufindex++[0] != 0x00) {
				printf("bad first nullbyte!\n");
				goto EXIT;
			}

			opcode = *bufindex++;
			rcount = *bufindex++ << 8;
			rcount &= 0xff00;
			rcount += (*bufindex++ & 0x00ff);

			//printf("rcount = %d count = %d\r\n",rcount,count);

			if (opcode != 3 || rcount != count) {	/* ack packet should have code 3 (data) and should be ack+1 the packet we just sent */

				printf("Badly ordered/invalid data packet (Got OP: %d Block: %d) (Wanted Op: 3 Block: %d)\n", opcode, rcount, count);
				/* sending error message */
				if (opcode > 5) {
					len = sprintf((char *) packetbuf, "%c%c%c%cIllegal operation%c", 0x00, 0x05, 0x00, 0x04, 0x00);
					if (sendto(sock, packetbuf, len, 0, (struct sockaddr *) &client, sizeof(client)) != len) {	/* send the data packet */
						printf("Mismatch in number of sent bytes while trying to send mode error packet\n");
					}
				}
				if (rcount != count) {
					len = sprintf(ackbuf, "%c%c%c%c", 0x00, 0x04, 0x00, 0x00);
					ackbuf[2] = ((count - 1) & 0xFF00) >> 8;	//fill in the count (top number first)
					ackbuf[3] = ((count - 1) & 0x00FF);	//fill in the lower part of the count

					//printf ("Sending ack # %04d (length: %d)\n", count, len);

					if (sendto(sock, ackbuf, len, 0, (struct sockaddr *) &client, sizeof(client)) != len) {
						printf("Mismatch in number of sent bytes\n");
						goto EXIT;
					}
				}
				//goto EXIT;
			} else {
				//sum_count++;
				//printf("correct \r\n");
				tftp_handler->recv_handle(tftp_handler->tftp_buf + 4, n - 4, count);
				break;
			}

		}
		if (i == tftp_handler->tftp_retry_num) {
			printf("Retry error\r\n");
			goto EXIT;
		}
	}
FINISH:
	return 0;
EXIT:
	return -1;
}

int tftp_server_send(int sock, char *pFilename, struct sockaddr_in client, char *pMode, int tid, tftp *tftp_handler) //client put the data into server
{
	/* To avoid gcc warnings */
	(void) pFilename;
	(void) pMode;

	/* local variables */
	int len, client_len, opcode, i, n;
	unsigned short int count = 0, rcount = 0;
	//unsigned char filebuf[64];
	unsigned char packetbuf[64];
	unsigned char *bufindex;
	struct sockaddr_in data;
	fd_set read_fds;
	struct timeval time_out;

	len = BLOCK_SIZE;
	client_len = sizeof(data);

	while (1) {

		count++;

		if (len != BLOCK_SIZE) {
			printf("Send file finish last chunk = %d\r\n", len - 4);
			goto FINISH;
		}

		sprintf((char *) tftp_handler->tftp_buf, "%c%c%c%c", 0x00, 0x03, 0x00, 0x00);	/* build data packet but write out the count as zero */
		tftp_handler->send_handle(tftp_handler->tftp_buf + 4, &len, count - 1);
		tftp_handler->tftp_buf[2] = (count & 0xFF00) >> 8;	//fill in the count (top number first)
		tftp_handler->tftp_buf[3] = (count & 0x00FF);	//fill in the lower part of the count
		len += 4;
		//printf("len = %d\r\n",len);
		if (sendto(sock, tftp_handler->tftp_buf, len, 0, (struct sockaddr *) &client, sizeof(client)) != len) {
			printf("Mismatch in number of sent bytes\n");
			goto EXIT;
		}

		for (i = 0; i < tftp_handler->tftp_retry_num; i++) {

			time_out.tv_sec = 5;	// Set select timeout of 3 seconds
			time_out.tv_usec = 0;
			FD_ZERO(&read_fds) ;
			FD_SET(sock, &read_fds);	// Only set server fd

			if (select(sock + 1, &read_fds, NULL, NULL, &time_out) == 1) {
				n = recvfrom(sock, tftp_handler->tftp_buf, BLOCK_SIZE, 0, (struct sockaddr *) &data, (socklen_t *) & client_len);
				if (n < 0) {
					printf("could not read datagram\r\n");
					goto EXIT;
				}
			} else {
				//continue;
				printf("timeout\r\n");
				continue;
			}

			if (client.sin_addr.s_addr != data.sin_addr.s_addr)  {	/* checks to ensure get from ip is same from ACK IP */
				printf("Error recieving file (data from invalid address)\r\n");
				i--;
				continue;	/* we aren't going to let another connection spoil our first connection */
			}

			if (tid != ntohs(client.sin_port)) {	/* checks to ensure get from the correct TID */
				printf("Error recieving file (data from invalid tid)\r\n");
				len = sprintf((char *) packetbuf, "%c%c%c%cBad/Unknown TID%c", 0x00, 0x05, 0x00, 0x05, 0x00);
				if (sendto(sock, packetbuf, len, 0, (struct sockaddr *) &client, sizeof(client)) != len) {	/* send the data packet */
					printf("Mismatch in number of sent bytes while trying to send mode error packet\r\n");
				}
				//j--;
				i--;
				continue;	/* we aren't going to let another connection spoil our first connection */
			}

			/* this formatting code is just like the code in the main function */
			bufindex =  tftp_handler->tftp_buf;	//start our pointer going

			if (bufindex++[0] != 0x00) {
				printf("bad first nullbyte!\n");
				goto EXIT;
			}

			opcode = *bufindex++;
			rcount = *bufindex++ << 8;
			rcount &= 0xff00;
			rcount += (*bufindex++ & 0x00ff);

			if (opcode != 4 || rcount != count) {	/* ack packet should have code 3 (data) and should be ack+1 the packet we just sent */

				printf("Badly ordered/invalid data packet (Got OP: %d Block: %d) (Wanted Op: 4 Block: %d)\n", opcode, rcount, count);
				/* sending error message */
				if (opcode > 5) {
					len = sprintf((char *) packetbuf, "%c%c%c%cIllegal operation%c", 0x00, 0x05, 0x00, 0x04, 0x00);
					if (sendto(sock, packetbuf, len, 0, (struct sockaddr *) &client, sizeof(client)) != len) {	/* send the data packet */
						printf("Mismatch in number of sent bytes while trying to send mode error packet\n");
					}
					goto EXIT;
				}
				if (rcount != count) {
					sprintf((char *) tftp_handler->tftp_buf, "%c%c%c%c", 0x00, 0x03, 0x00, 0x00);	/* build data packet but write out the count as zero */
					tftp_handler->send_handle(tftp_handler->tftp_buf + 4, &len, count - 2);
					tftp_handler->tftp_buf[2] = ((count - 1) & 0xFF00) >> 8;	//fill in the count (top number first)
					tftp_handler->tftp_buf[3] = ((count - 1) & 0x00FF);	//fill in the lower part of the count
					len += 4;
					//printf("len = %d\r\n",len);
					if (sendto(sock, tftp_handler->tftp_buf, len, 0, (struct sockaddr *) &client, sizeof(client)) != len) {
						printf("Mismatch in number of sent bytes\n");
						goto EXIT;
					}
				}
				//goto EXIT;
			} else {
				break;
			}
		}

		if (i == tftp_handler->tftp_retry_num) {
			printf("Retry error\r\n");
			goto EXIT;
		}

	}
FINISH:
	return 0;
EXIT:
	return -1;
}

int tftp_server_start(tftp *tftp_handler)
{
	int sock, n, client_len, status, tid, len;
	char opcode, filename[64], packetbuf[64];
	char mode[12] = {0};
	unsigned char *bufindex;

	struct sockaddr_in server, client;	/*the address structure for both the server and client */
START_AGAIN:

	memset(&server, 0, sizeof(struct sockaddr_in));
	memset(&client, 0, sizeof(struct sockaddr_in));

	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("Server Socket could not be created");
		goto EXIT;
	}


	/*set the address values for the server */
	server.sin_family = AF_INET;	/*address family for TCP and UDP */
	server.sin_addr.s_addr = htonl(INADDR_ANY);	/*use any address */
	server.sin_port = htons(tftp_handler->tftp_port);	/*pick a free port */

	/*Bind the socket */
	if (bind(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Server bind failed. Server already running? Proper permissions?\n");
		//return (2);
		goto EXIT;
	}

	client_len = sizeof(client);	/*get the length of the client */
	memset(tftp_handler->tftp_buf, 0, BLOCK_SIZE);	/*clear the buffer */

	fcntl(sock, F_SETFL, fcntl(sock, F_GETFL, 0) | O_NONBLOCK);

	fd_set read_fds;
	struct timeval time_out;

	while (1) {

		time_out.tv_sec = 3;	// Set select timeout of 3 seconds
		time_out.tv_usec = 0;
		FD_ZERO(&read_fds) ;
		FD_SET(sock, &read_fds);	// Only set server fd

		if (select(sock + 1, &read_fds, NULL, NULL, &time_out) == 1) {
			n = recvfrom(sock, tftp_handler->tftp_buf, BLOCK_SIZE, 0, (struct sockaddr *) &client, (socklen_t *) & client_len);
			if (n < 0) {
				printf("could not read datagram\r\n");
			} else {
				break;
			}
		}
	}

	printf("Connection from %s, port %d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

	if (errno != EAGAIN) {
		printf("The server could not receive from the client");
		goto EXIT;
	}

	bufindex = tftp_handler->tftp_buf;		//start our pointer going
	if (bufindex++[0] != 0x00) {			//first TFTP packet byte needs to be null. Once the value is taken increment it.
		printf("Malformed tftp packet.\n");
		goto EXIT;
	}

	tid = ntohs(client.sin_port);	/* record the tid */
	opcode = *bufindex++;	//opcode is in the second byte.

	if (opcode == 1 || opcode == 2) {	// RRQ or WRQ. The only two really valid packets on port 69

		strncpy(filename, (char const *)bufindex, sizeof(filename) -
				1);	/* Our pointer has been nudged along the recieved string so the first char is the beginning of the filename. This filename is null deliimited so we can use the str family of functions */
		bufindex += strlen(filename) + 1;	/* move the pointer to after the filename + null byte in the string */
		strncpy(mode, (const char *)bufindex, sizeof(mode) - 1);	/* like the filename, we are at the beginning of the null delimited mode */
		bufindex += strlen(mode) + 1;	/* move pointer... */
		printf("opcode: %x filename: %s packet size: %d mode: %s\n", opcode, filename, n, mode);	/*show the message to the server */

	} else {
		printf("opcode: %x size: %d \n", opcode, sizeof(n));	/*show the message to the server */

	}

	if (!strncasecmp(mode, "octet", 5) && !strncasecmp(mode, "netascii", 8)) {	/* these two are the only modes we accept */

		if (!strncasecmp(mode, "mail", 4)) {
			len = sprintf((char *) packetbuf, "%c%c%c%cThis tftp server will not operate as a mail relay%c", 0x00, 0x05, 0x00, 0x04, 0x00);
		} else {
			len = sprintf((char *) packetbuf, "%c%c%c%cUnrecognized mode (%s)%c", 0x00, 0x05, 0x00, 0x04, mode, 0x00);
		}
		if (sendto(sock, packetbuf, len, 0, (struct sockaddr *) &client, sizeof(client)) != len) {	/* send the data packet */
			printf("Mismatch in number of sent bytes while trying to send mode error packet\n");
		}

	}

	if (strchr(filename, 0x5C) || strchr(filename, 0x2F)) {	//look for illegal characters in the filename string these are \ and /
		printf("Client requested to upload bad file: forbidden name\n");
		len = sprintf((char *) packetbuf, "%c%c%c%cIllegal filename.(%s) You may not attempt to descend or ascend directories.%c", 0x00, 0x05, 0x00, 0x00, filename,
					  0x00);
		if (sendto(sock, packetbuf, len, 0, (struct sockaddr *) &client, sizeof(client)) != len) {	/* send the data packet */
			printf("Mismatch in number of sent bytes while trying to send error packet\n");
		}
		goto EXIT;
	}

	if (opcode == WRQ) {
		if (tftp_server_recv(sock, filename, client, mode, tid, tftp_handler) != 0) {
			printf("Error Happen\r\n");
		} else {
			printf("tftp transfer finish\r\n");
		}
	} else if (opcode == RRQ) {
		if (tftp_server_send(sock, filename, client, mode, tid, tftp_handler) != 0) {
			printf("Error Happen\r\n");
		} else {
			printf("tftp transfer finish\r\n");
		}
	} else {
		printf("The type is not support\r\n");
		goto EXIT;
	}


	status = close(sock);
	if (status != 0) {
		printf("status error = %d\r\n", status);
	}


	goto START_AGAIN;

//DONE:
//        return 0;
EXIT:
	close(sock);
	return -1;
}
