/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: CoffeeShopInventory
@version: I
Creation: 01/09/2022
Last modification: 06/09/2022
------------------------------------------------------------------------------*/
// Imports
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <math.h>
#include <errno.h>

// Namespace
using namespace std;

// Mutex lock
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// &Cafe information (gotten from an xlsx file/constants)
// ------- Prices -------
// *Drinks*
const float americanCoffee = 22.00;
const float cappuccino = 24.00;
const float latte = 24.00;
const float toffeCoffee = 28.00;
const float whiteMocha = 32.00;
const float smoresLatte = 32.00;
// *Food*
const float chocolateCake = 60.00;
const float toastedCoffee = 60.00;

// ------- Costs -------
// *Drinks*
const float americanCoffeeUnit = 13.20;
const float cappuccinoUnit = 17.20;
const float latteUnit = 17.20;
const float toffeCoffeeUnit = 20.10;
const float whiteMochaUnit = 19.20;
const float smoresLatteUnit = 23.00;
// *Food*
const float chocolateCakeUnit = 20.00;
const float toastedCoffeeUnit = 20.00;

// ------- Sales ------- (established as a float in order to keep the same type of data when the operations os the summary take place)
// JULY
// *Drinks*
const float americanCoffeeJSales = 1590;
const float cappuccinoJSales = 1455;
const float latteJSales = 200;
const float toffeCoffeeJSales = 390;
const float whiteMochaJSales = 400;
const float smoresLatteJSales = 800;
// *Food*
const float chocolateCakeJSales = 300;
const float toastedCoffeeJSales = 60;

// AUGUST
// *Drinks*
const float americanCoffeeASales = 800;
const float cappuccinoASales = 1200;
const float latteASales = 250;
const float toffeCoffeeASales = 600;
const float whiteMochaASales = 380;
const float smoresLatteASales = 1540;
// *Food*
const float chocolateCakeASales = 250;
const float toastedCoffeeASales = 15;
