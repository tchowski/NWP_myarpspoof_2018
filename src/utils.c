/*
** EPITECH PROJECT, 2019
** utils.c
** File description:
** utils
*/

#include "arpspoof.h"

void print_arp_packet(struct ethhdr *send_req, arp_header_t *arp_req)
{
    unsigned char print[42];

    memcpy(print, &send_req->h_dest, 6);
    memcpy(print + 6, &send_req->h_source, 6);
    memcpy(print + 12, &send_req->h_proto, 2);
    memcpy(print + 14, &arp_req->hardware_type, 2);
    memcpy(print + 16, &arp_req->protocol_type, 2);
    memcpy(print + 18, &arp_req->hardware_len, 1);
    memcpy(print + 19, &arp_req->protocol_len, 1);
    memcpy(print + 20, &arp_req->opcode, 2);
    memcpy(print + 22, &arp_req->sender_mac, 6);
    memcpy(print + 28, &arp_req->sender_ip, 4);
    memcpy(print + 32, &arp_req->target_mac, 6);
    memcpy(print + 38, &arp_req->target_ip, 4);
    for (int i = 0; i < 42; i++) {
        printf("%02x", print[i]);
        printf("%c", (i < 41) ? ' ' : '\n');
    }
}

void my_perror(const char *str)
{
    perror(str);
    exit(84);
}