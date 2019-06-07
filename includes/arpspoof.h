/*
** EPITECH PROJECT, 2019
** arpspoof.h
** File description:
** arpspoof
*/

#ifndef ARPSPOOF_H_
#define ARPSPOOF_H_

#include <arpa/inet.h>
#include <asm/types.h>
#include <linux/if_arp.h>
#include <linux/if_ether.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct data_s {
    uint32_t ip_source;
    uint32_t ip_dest;
    unsigned char *mac_source;
    unsigned char *mac_dest;
    char *interface;
    int index_interface;
    int arp_fd;
} data_t;

typedef struct arp_header_s {
    unsigned short hardware_type;
    unsigned short protocol_type;
    unsigned char hardware_len;
    unsigned char protocol_len;
    unsigned short opcode;
    unsigned char sender_mac[6];
    unsigned char target_mac[6];
    unsigned char sender_ip[4];
    unsigned char target_ip[4];
} arp_header_t;

void set_structure(data_t *data, char **argv);
void run_broadcast(data_t *data);
void run_spoof(data_t *data);
void my_perror(const char *str);
void get_mac_adresse_source(data_t *data);
void print_arp_packet(struct ethhdr *send_req, arp_header_t *arp_hdr);
void print_broadcast(data_t *data);
void get_mac_adresse_destination(data_t *data, char *mac);
void print_spoof(data_t *data);

#endif /* !ARPSPOOF_H_ */
