#!/bin/sh

./change_allocation_policy first_fit
./testmem01 output_first_fit_01

./change_allocation_policy worst_fit
./testmem01 output_worst_fit_01

./change_allocation_policy best_fit
./testmem01 output_best_fit_01

./change_allocation_policy random_fit
./testmem01 output_random_fit_01
