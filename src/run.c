/*
** EPITECH PROJECT, 2019
** run.c
** File description:
** run
*/

#include "arpspoof.h"

void run_broadcast(data_t *data)
{
    get_mac_adresse_source(data);
    print_broadcast(data);
}

void run_arp(data_t *data)
{
    get_mac_adresse_source(data);
    bind_arp(data);
    arp_run(data);
}

void run_spoof(data_t *data)
{
    get_mac_adresse_source(data);
    print_spoof(data);
}