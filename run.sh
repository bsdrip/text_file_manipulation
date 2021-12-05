#!/bin/bash
gcc main.c impl/utils.c -Wall -Werror -Wextra -std=c89 -o hegyvidek && ./hegyvidek
