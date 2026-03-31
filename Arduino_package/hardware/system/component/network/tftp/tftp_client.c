#include <FreeRTOS.h>
#include <task.h>
#include <platform_stdlib.h>
#include <lwipconf.h>
#include "tftp.h"

#include "wifi_conf.h"

int req_packet(int opcode, const char *filename, const char *mode, char buf[], int size)
{
	/* To avoid gcc warnings */
	(void) size;
#if 0 //The sprintf don;t get the correct result
	int len;
	len = sprintf(buf, "%c%c%s%c%s%c", 0x00, opcode, filename, 0x00, mode, 0x00);
#else
	int len = 0;
	int i = 0;
	buf[len] = 0x00;
	len++;
	buf[len] = opcode;
	len++;
	for (i = 0; i < strlen(filename); i++) {
		buf[len + i] = filename[i];
	}
	len += strlen(filename);
	buf[len] = 0x00;
	len++;
	for (i = 0; i < strlen(mode); i++) {
		buf[len + i] = mode[i];
	}
	len += strlen(mode);
	buf[len] = 0x00;
	len++;
#endif
	if (len == 0) {
		printf("Error in creating the request packet\r\n");	/*could not print to the client buffer */
		return -1;
	}
	return len;
}

void ip_port(struct sockaddr_in host)
{
	printf("The IP port pair for the host is: IP:%s Port:%d \n", inet_ntoa(host.sin_addr), ntohs(host.sin_port));
}


int tftp_client_send(const char *pFilename, struct sockaddr_in server, const char *pMode, int sock, tftp *tftp_handler)
{
	/* To avoid gcc warnings */
	(void) pFilename;
	(void) pMode;

	/* local variables */
	int len, server_len, opcode, j, n, tid = 0;
	unsigned short int count = 0, rcount = 0;
	unsigned char packetbuf[64];
	char *bufindex;
	struct sockaddr_in data;

	n = BLOCK_SIZE;

	fd_set read_fds;
	struct timeval time_out;

	while (1) {

		for (j = 0; j < tftp_handler->tftp_retry_num;
			 j++) {	/* this allows us to loop until we either break out by getting the correct ack OR time out because we've looped more than RETRIES times */

			server_len = sizeof(data);
			time_out.tv_sec = tftp_handler->tftp_timeout;	// Set select timeout of 3 seconds
			time_out.tv_usec = 0;
			FD_ZERO(&read_fds) ;
			FD_SET(sock, &read_fds);	// Only set server fd
			if (select(sock + 1, &read_fds, NULL, NULL, &time_out) == 1) {
				n = recvfrom(sock, tftp_handler->tftp_buf, BLOCK_SIZE, 0, (struct sockaddr *) &data, (socklen_t *) & server_len);
				if (n < 0) {
					printf("could not read datagram\r\n");
					goto exit;
				}
			} else {
				if (count == 0) {
					printf("Resend the wrq request");
					goto exit;
				} else {
					printf("timeout\r\n");
					continue;
				}
			}
			//printf("get count = %d num = %d\r\n",count,n);

			if (!tid) {
				tid = ntohs(data.sin_port);	//get the tid of the server.
				server.sin_port = htons(tid);	//set the tid for rest of the transfer
			}

			if (server.sin_addr.s_addr != data.sin_addr.s_addr) {	/* checks to ensure get from ip is same from ACK IP */
				printf("Error recieving file (data from invalid address)\n");
				j--;
				continue;	/* we aren't going to let another connection spoil our first connection */
			}

			if (tid != ntohs(server.sin_port)) {	/* checks to ensure get from the correct TID */
				printf("Error recieving file (data from invalid tid)\n");
				len = sprintf((char *) packetbuf, "%c%c%c%cBad/Unknown TID%c", 0x00, 0x05, 0x00, 0x05, 0x00);
				if (sendto(sock, packetbuf, len, 0, (struct sockaddr *) &server, sizeof(server)) != len) {	/* send the data packet */
					printf("Mismatch in number of sent bytes while trying to send mode error packet\n");
				}
				j--;
				continue;	/* we aren't going to let another connection spoil our first connection */
			}

			/* this formatting code is just like the code in the main function */
			bufindex = (char *) tftp_handler->tftp_buf;	//start our pointer going
			if (bufindex++[0] != 0x00) {
				printf("bad first nullbyte!\n");
				goto exit;
			}
			opcode = *bufindex++;
			rcount = *bufindex++ << 8;
			rcount &= 0xff00;
			rcount += (*bufindex++ & 0x00ff);

			if (opcode != 0X04) {	/* ack packet should have code 3 (data) and should be ack+1 the packet we just sent */
				printf("Client: Remote host failed to ACK proper data packet # %d (got OP: %d Block: %d)\n", count, opcode, rcount);
				//printf("Badly ordered/invalid data packet (Got OP: %d Block: %d) (Wanted Op: 3 Block: %d)\n",opcode, rcount, count);
				/* sending error message */
				if (opcode > 5) {
					len = sprintf((char *) packetbuf, "%c%c%c%cIllegal operation%c", 0x00, 0x05, 0x00, 0x04, 0x00);
					if (sendto(sock, packetbuf, len, 0, (struct sockaddr *) &server, sizeof(server)) != len) {	/* send the data packet */
						printf("Mismatch in number of sent bytes while trying to send mode error packet\n");
					}
				} else {
					bufindex = (char *) tftp_handler->tftp_buf;
					bufindex += 3;
					printf("error opcode = %d message = %s\r\n", opcode, bufindex);
					goto exit;
				}
			}

			if (rcount != count) {
				//printf("error:rcount = %d count = %d\r\n",rcount,count);
				len = sprintf((char *) tftp_handler->tftp_buf, "%c%c%c%c", 0x00, 0x03, 0x00, 0x00);	/* build data packet but write out the count as zero */
				//tftp_handler->send_handle(tftp_handler->tftp_buf+4,&len,count);
				tftp_handler->tftp_buf[2] = (count & 0xFF00) >> 8;	//fill in the count (top number first)
				tftp_handler->tftp_buf[3] = (count & 0x00FF);	//fill in the lower part of the count
				//len+=4;
				if (sendto(sock, tftp_handler->tftp_buf, len, 0, (struct sockaddr *) &server, sizeof(server)) != len) {
					printf("Mismatch in number of sent bytes\n");
					goto exit;
				}
				continue;
			}

			//send file to tftp server
			//printf("ok:rcount = %d count = %d\r\n",rcount,count);
			count++;

			sprintf((char *) tftp_handler->tftp_buf, "%c%c%c%c", 0x00, 0x03, 0x00, 0x00);	/* build data packet but write out the count as zero */
			tftp_handler->send_handle(tftp_handler->tftp_buf + 4, &len, count);
			tftp_handler->tftp_buf[2] = (count & 0xFF00) >> 8;	//fill in the count (top number first)
			tftp_handler->tftp_buf[3] = (count & 0x00FF);	//fill in the lower part of the count
			len += 4;
			//printf("len = %d\r\n",len);
			if (sendto(sock, tftp_handler->tftp_buf, len, 0, (struct sockaddr *) &server, sizeof(server)) != len) {
				printf("Mismatch in number of sent bytes\n");
				goto exit;
			} else if (len != BLOCK_SIZE) {
				printf("Send file finish last chunk = %d\r\n", len - 4);
				goto done;
			} else {
				break;
			}
		}

		if (j == tftp_handler->tftp_retry_num) {
			printf("Data recieve Timeout. Aborting transfer\n");
			goto exit;
		}

	}
exit:
	return -1;
done:
	return 0;
}

int tftp_client_get(const char *pFilename, struct sockaddr_in server, const char *pMode, int sock, tftp *tftp_handler)
{
	/* To avoid gcc warnings */
	(void) pFilename;
	(void) pMode;

	/* local variables */
	int len, server_len, opcode, j, n, tid = 0;
	unsigned short int count = 0, rcount = 0;
	unsigned char packetbuf[64];
	//int errno;
	char *bufindex, ackbuf[12];
	struct sockaddr_in data;

	n = BLOCK_SIZE;

	fd_set read_fds;
	struct timeval time_out;

	printf("tftp_client_get\r\n");

	while (1) {

		if (n != BLOCK_SIZE) {	/* remember if our datasize is less than a full packet this was the last packet to be received */

			printf("Last chunk detected (file chunk size: %d). exiting while loop\n", n - 4);
			len = sprintf(ackbuf, "%c%c%c%c", 0x00, 0x04, 0x00, 0x00);
			ackbuf[2] = (count & 0xFF00) >> 8;	//fill in the count (top number first)
			ackbuf[3] = (count & 0x00FF);	//fill in the lower part of the count
			printf("Sending ack # %04d (length: %d)\n", count, len);
			if (sendto(sock, ackbuf, len, 0, (struct sockaddr *) &server, sizeof(server)) != len) {
				printf("Mismatch in number of sent bytes\n");
				goto exit;
			}
			printf("The Client has sent an ACK for packet\n");
			goto done;		/* gotos are not optimal, but a good solution when exiting a multi-layer loop */
		}

		count++;

		for (j = 0; j < tftp_handler->tftp_retry_num;
			 j++) {	/* this allows us to loop until we either break out by getting the correct ack OR time out because we've looped more than RETRIES times */
			server_len = sizeof(data);
			time_out.tv_sec = tftp_handler->tftp_timeout;	// Set select timeout of 3 seconds
			time_out.tv_usec = 0;
			FD_ZERO(&read_fds) ;
			FD_SET(sock, &read_fds);	// Only set server fd
			if (select(sock + 1, &read_fds, NULL, NULL, &time_out) == 1) {
				n = recvfrom(sock, tftp_handler->tftp_buf, BLOCK_SIZE, 0, (struct sockaddr *) &data, (socklen_t *) & server_len);
				if (n < 0) {
					printf("could not read datagram\r\n");
					goto exit;
				}
			} else {
				printf("timeout...%d\r\n", j);
				continue;
			}

			if (!tid) {
				tid = ntohs(data.sin_port);	//get the tid of the server.
				server.sin_port = htons(tid);	//set the tid for rest of the transfer
			}

			if (server.sin_addr.s_addr != data.sin_addr.s_addr) {	/* checks to ensure get from ip is same from ACK IP */
				printf("Error recieving file (data from invalid address)\n");
				j--;
				continue;	/* we aren't going to let another connection spoil our first connection */
			}

			if (tid != ntohs(server.sin_port)) {	/* checks to ensure get from the correct TID */
				printf("Error recieving file (data from invalid tid)\n");
				len = sprintf((char *) packetbuf, "%c%c%c%cBad/Unknown TID%c", 0x00, 0x05, 0x00, 0x05, 0x00);
				if (sendto(sock, packetbuf, len, 0, (struct sockaddr *) &server, sizeof(server)) != len) {	/* send the data packet */
					printf("Mismatch in number of sent bytes while trying to send mode error packet\n");
				}
				j--;
				continue;	/* we aren't going to let another connection spoil our first connection */
			}

			/* this formatting code is just like the code in the main function */
			bufindex = (char *) tftp_handler->tftp_buf;	//start our pointer going
			if (bufindex++[0] != 0x00) {
				printf("bad first nullbyte!\n");
			}
			opcode = *bufindex++;
			rcount = *bufindex++ << 8;
			rcount &= 0xff00;
			rcount += (*bufindex++ & 0x00ff);

			if (opcode != 3) {	/* ack packet should have code 3 (data) and should be ack+1 the packet we just sent */

				//printf("Badly ordered/invalid data packet (Got OP: %d Block: %d) (Wanted Op: 3 Block: %d)\n",opcode, rcount, count);
				/* sending error message */
				if (opcode > 5) {
					len = sprintf((char *) packetbuf, "%c%c%c%cIllegal operation%c", 0x00, 0x05, 0x00, 0x04, 0x00);
					if (sendto(sock, packetbuf, len, 0, (struct sockaddr *) &server, sizeof(server)) != len) {	/* send the data packet */
						printf("Mismatch in number of sent bytes while trying to send mode error packet\n");
					}
				} else {
					bufindex = (char *) tftp_handler->tftp_buf;
					bufindex += 3;
					printf("error opcode = %d message = %s\r\n", opcode, bufindex);
					goto exit;
				}
			} else {
				len = sprintf(ackbuf, "%c%c%c%c", 0x00, 0x04, 0x00, 0x00);
				ackbuf[2] = (count & 0xFF00) >> 8;	//fill in the count (top number first)
				ackbuf[3] = (count & 0x00FF);	//fill in the lower part of the count
			}

			if (rcount != count) {
				//printf("rcount %d %d\r\n",rcount,count);
				len = sprintf(ackbuf, "%c%c%c%c", 0x00, 0x04, 0x00, 0x00);
				ackbuf[2] = ((count - 1) & 0xFF00) >> 8;	//fill in the count (top number first)
				ackbuf[3] = ((count - 1) & 0x00FF);	//fill in the lower part of the count
				if (sendto(sock, ackbuf, len, 0, (struct sockaddr *) &server, sizeof(server)) != len) {
					printf("Mismatch in number of sent bytes\n");
					goto exit;
				} else {
					continue;
				}
			}

			if (sendto(sock, ackbuf, len, 0, (struct sockaddr *) &server, sizeof(server)) != len) {
				printf("Mismatch in number of sent bytes\n");
				goto exit;
			} else {
				tftp_handler->recv_handle(tftp_handler->tftp_buf + 4, n - 4, count);
				break;
			}
		}

		if (j == tftp_handler->tftp_retry_num) {
			printf("Data recieve Timeout. Aborting transfer\n");
			goto exit;
		}

	}
exit:
	return -1;
done:
	return 0;
}

int tftp_client_start(tftp *tftp_handler)
{
	int sock = -1, server_len, len;	//,n;
	struct hostent *host;		/*for host information */
	struct sockaddr_in server;	//, client; /*the address structure for both the server and client */
	char request_buf[256] = {0};

	int retry_count = 0;

	//vTaskDelay(5000);

	printf("start to tftp client: %s\r\n", tftp_handler->tftp_host);

	if (!(host = gethostbyname(tftp_handler->tftp_host))) {
		printf("Client could not get host address information\r\n");
		goto EXIT;
	}

	/*Create the socket, a -1 will show us an error */
	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		printf("Client: Socket could not be created");
		goto EXIT;
	}


	/*set the address values for the server */
	memset(&server, 0, sizeof(server));	/*Clear the structure */
	server.sin_family = AF_INET;	/*address family for TCP and UDP */
	memcpy(&server.sin_addr, host->h_addr, 4);	/*set address of server taken from gethostbyname function */
	//server.sin_addr.s_addr = htonl (INADDR_ANY); /*use any address */
	server.sin_port = htons(tftp_handler->tftp_port);	/*pick a free port */

	server_len = sizeof(server);	/*get the length of the server address */
	ip_port(server);
	len = req_packet(tftp_handler->tftp_op, tftp_handler->tftp_file_name, tftp_handler->tftp_mode, request_buf, 0);
RETRY:
	if (retry_count == tftp_handler->tftp_retry_num) {
		printf("Try the maxium %d times \r\n", tftp_handler->tftp_retry_num);
		goto EXIT;
	}
	if (sendto(sock, request_buf, len, 0, (struct sockaddr *) &server, server_len) != len) {
		printf("Client: sendto has returend an error %d\r\n", len);
		goto EXIT;
	}
	if (tftp_handler->tftp_op == RRQ) {
		printf("recv file\r\n");
		if (tftp_client_get(tftp_handler->tftp_file_name, server, tftp_handler->tftp_mode, sock, tftp_handler) == 0) {
			printf("tget finish\r\n");
			close(sock);
		} else {
			printf("tget error\r\n");
			retry_count++;
			goto RETRY;
		}
	} else if (tftp_handler->tftp_op == WRQ) {
		printf("send file\r\n");
		if (tftp_client_send(tftp_handler->tftp_file_name, server, tftp_handler->tftp_mode, sock, tftp_handler) == 0) {
			printf("tput finish\r\n");
			close(sock);
			goto DONE;
		} else {
			printf("tput error\r\n");
			retry_count++;
			goto RETRY;
		}
	}
DONE:
	return 0;
EXIT:
	if (sock > 0) {
		close(sock);
	}
	return -1;
}
