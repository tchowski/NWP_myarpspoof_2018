/*
** EPITECH PROJECT, 2019
** bind_arp
** File description:
** bind_arp
*/

#include "arpspoof.h"

int bind_arp(data_t *data)
{
    struct sockaddr_ll sll;
    int error;

    data->arp_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (data->arp_fd < 1)
        my_perror("socket()");
    memset(&sll, 0, sizeof(struct sockaddr_ll));
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = data->index_interface;
    error = bind(data->arp_fd, (struct sockaddr *)&sll,
        sizeof(struct sockaddr_ll));
    if (error < 0)
        my_perror("bind()");
    return 0;
}