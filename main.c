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
// See the next five scheduled launches:
// curl https://fdo.rocketlaunch.live/json/launches/next/2 | jq ".result[].quicktext"

void print_wrap(const char* text) {
    // based on code from ChatGPT
    int i;
    int len = strlen(text);
    int start = 0; // Start index of the current line in the text

    while (start < len) {
        int end = start + 38; // Default end index if we need a hard break
        int spaceFound = 0; // Flag to indicate if we've found a space for a soft break

        // If end exceeds text length, adjust it to the end of the text
        if (end > len) end = len;

        // Look for a space between 32nd and 39th characters for a soft break
        for (i = start + 32; i < end && i < len; i++) {
            if (text[i] == ' ') {
                end = i; // Update the end index to the space's position
                spaceFound = 1; // Set flag to indicate we found a space
                break;
            }
        }

        // Print the substring from start to end
        for (i = start; i <= end && i < len; i++) {
            cputc(text[i]);
        }
        cputs("\r\n"); // New line after printing the line's content

        // Update start for the next line
        // If we found a space, start from the next character after the space
        // Otherwise, start from the next character after the last printed one
        start = (spaceFound) ? end + 1 : end + (end < len ? 1 : 0);
    }
}

void print_field(char *query) {
    uint8_t err;
    char *result = malloc(BSIZE);
    err = network_json_query(api, query, result);
    if (!err) {
        print_wrap(result);
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
            //print_field("/result/0/win_open");
            print_field("/result/0/t0");
            print_field("/result/0/name");
            print_field("/result/0/launch_description");
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