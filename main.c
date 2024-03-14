/* SPDX-FileCopyrightText: Copyright (c) Randall Bohn 2024 */
/* SPDX-License-Identifier: gpl3 */
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "fujinet-network.h"

#define BSIZE 256
char api[] = "N:HTTPS://fdo.rocketlaunch.live/json/launches/next/1";

void print_field(char *query) {
    uint8_t err;
    char *result = malloc(BSIZE);
    err = network_json_query(api, query, result);
    if (!err) {
        cputs(result);
        cputc(' ');
    } else {
        cputs("ERR: json_query failed");
    }
    free(result);
}

void show_next_launch() {
    uint8_t err;
    err = network_open(api, OPEN_MODE_HTTP_GET, OPEN_TRANS_NONE);
    if (!err) {
        err = network_json_parse(api);
        if (!err) {
            print_field("/result/0/win_open");
            cputs("\r\n");
            print_field("/result/0/name");
            cputs("\r\n");
            print_field("/result/0/mission_description");
            cputs("\r\n");
        }
    }
}

int main(void) {
    clrscr();
    cputs("Next Rocket Launch:\r\n\n");
    show_next_launch();
    while (1) {
        sleep(30);
    }
    return 0;
}