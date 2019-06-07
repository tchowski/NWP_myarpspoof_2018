/*
** EPITECH PROJECT, 2019
** set_structure.c
** File description:
** set_structur
*/

#include "arpspoof.h"

void set_structure(data_t *data, char **argv)
{
    data->interface = strdup(argv[3]);
    data->ip_source = inet_addr(argv[1]);
    data->ip_dest = inet_addr(argv[2]);
    data->mac_dest = malloc(sizeof(char) * 6);
    data->mac_source = malloc(sizeof(char) * 6);
}