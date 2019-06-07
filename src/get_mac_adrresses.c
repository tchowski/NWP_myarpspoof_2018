/*
** EPITECH PROJECT, 2019
** get_mac_adresses.c
** File description:
** get_mac_adrresses
*/

#include "arpspoof.h"

void get_mac_adresse_destination(data_t *data, char *mac)
{
    int i = 0;
    const char s[2] = ":";
    char *token;

    token = strtok(mac, s);
    data->mac_dest[i] = (unsigned char)strtol(token, NULL, 16);
    i++;
    while (token != NULL) {
        token = strtok(NULL, s);
        if (token) {
            data->mac_dest[i] = (unsigned char)strtol(token, NULL, 16);
            i++;
        }
    }
}

void get_mac_adresse_source(data_t *data)
{
    struct ifreq ifr;
    int sd = socket(AF_INET, SOCK_STREAM, 0);

    if (sd <= 0)
        my_perror("socket()");
    strcpy(ifr.ifr_name, data->interface);
    if (ioctl(sd, SIOCGIFHWADDR, &ifr) == -1)
        my_perror("SIOCGIFINDEX");
    memcpy(data->mac_source, ifr.ifr_hwaddr.sa_data, 6);
    close(sd);
}