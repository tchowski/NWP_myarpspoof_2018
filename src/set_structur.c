/*
** EPITECH PROJECT, 2019
** set_structure.c
** File description:
** set_structur
*/

#include "arpspoof.h"

void set_structure(data_t *data, char **argv)
{
    target_g = strdup(argv[2]);
    data->interface = strdup(argv[3]);
    data->ip_source = inet_addr(argv[1]);
    data->ip_dest = inet_addr(argv[2]);
    data->mac_dest = malloc(sizeof(char) * 6);
    data->mac_source = malloc(sizeof(char) * 6);
}

void fill_sockaddr_ll(struct sockaddr_ll *socket_address, data_t *data)
{
    socket_address->sll_family = AF_PACKET;
    socket_address->sll_protocol = htons(ETH_P_ARP);
    socket_address->sll_ifindex = data->index_interface;
    socket_address->sll_hatype = htons(ARPHRD_ETHER);
    socket_address->sll_pkttype = (PACKET_BROADCAST);
    socket_address->sll_halen = 6;
    socket_address->sll_addr[6] = 0x00;
    socket_address->sll_addr[7] = 0x00;
}

void set_arp_stuff_request(arp_header_t *arp_req)
{
    arp_req->hardware_type = htons(1);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = 6;
    arp_req->protocol_len = 4;
    arp_req->opcode = htons(0x02);
}

void set_arp_stuff_response(arp_header_t *arp_req)
{
    arp_req->hardware_type = htons(1);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = 6;
    arp_req->protocol_len = 4;
    arp_req->opcode = htons(0x01);
}