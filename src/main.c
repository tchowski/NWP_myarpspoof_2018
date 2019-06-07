/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "arpspoof.h"

void print_usage(void)
{
    fprintf(stderr, "USAGE: source_ip dest_ip interface\n");
    exit(84);
}

int main(int argc, char const **argv)
{
    data_t data;

    if (argc > 6 || argc < 4)
        print_usage();
    set_structure(&data, (char **)argv);
    if (argv[4] && strcmp(argv[4], "--printBroadcast") == 0)
        run_broadcast(&data);
    else if (argv[4] && strcmp(argv[4], "--printSpoof") == 0) {
        get_mac_adresse_destination(&data, (char *)argv[5]);
        run_spoof(&data);
    } else
        return (0);
    return (0);
}
