/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, Sara Echeverria (bl33h)
@author Sara Echeverria
FileName: CoffeeShopInventory
@version: I
Creation: 01/09/2022
Last modification: 09/09/2022
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

// Variable bills per month
// JULY
const float variableBillsJ = 45640.00;
// AUGUST
const float variableBillsA = 40590.00;

// Threads quantity available for the process
const int threadsQuantity = 16;

// Arrays in order to construct a matrix that will contain all the information of the summary
// ------- Products available -------
string products[8] = {"American Coffee", "Cappuccino", "Latte", "Toffe Coffee", "White Mocha", "S'mores Latte", "Chocolate cake", "Toasted Coffee"};
// ------- Prices of each product -------
float prices[16] = {americanCoffee, cappuccino, latte, toffeCoffee, whiteMocha, smoresLatte, chocolateCake, toastedCoffee};
// ------- Cost of each product -------
float costs[16] = {americanCoffeeUnit, cappuccinoUnit, latteUnit, toffeCoffeeUnit, whiteMochaUnit, smoresLatteUnit, chocolateCakeUnit, toastedCoffeeUnit};
// ------- Sales -------
float sales[32] = {americanCoffeeJSales, cappuccinoJSales, latteJSales, toffeCoffeeJSales, whiteMochaJSales, smoresLatteJSales, chocolateCakeJSales, toastedCoffeeJSales,
americanCoffeeASales, cappuccinoASales, latteASales, toffeCoffeeASales, whiteMochaASales, smoresLatteASales, chocolateCakeASales, toastedCoffeeASales};

// Summary results
float salesQ[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
float salesU[16] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
// ------- Sales per month -------
// JULY (established as a float in order to keep the same type of data when the operations os the summary take place)
float jSales = 0.0; 
// AUGUST (established as a float in order to keep the same type of data when the operations os the summary take place)
float aSales = 0.0;

// ------- Utility per month -------
// JULY (established as a float in order to keep the same type of data when the operations os the summary take place)
float julyU = 0.0;
// AUGUST (established as a float in order to keep the same type of data when the operations os the summary take place)
float augustU = 0.0;

// ------- Reports per month -------
string julyReport = "--- July Report ---\n";
string augustReport = "--- August Report ---\n";

// ------- Calculations -------
// *Threads method*
void *threadsMethod(void *argument)
{
    int *input = (int *)argument;
    int threadsID = *input;
    // *Mutex lock*
    pthread_mutex_lock(&lock);
    // *Sales quantity calculation*
    salesQ[threadsID] = prices[threadsID] * sales[threadsID];
    // *Sales utility calculation*
    salesU[threadsID] = salesQ[threadsID] - (costs[threadsID] * sales[threadsID]);
    // *Mutex unlock*
    pthread_mutex_unlock(&lock);
    return NULL;
}

// *Method to make the calculation per month*
void *calcsPerMonth(void *argument) 
{
	int *input = (int *)argument;
    int threadsID = *input;
    float totalSalesPerMonth = 0.0;
    float totalUperMonth = 0.0;
    // JULY
    if (threadsID == 1)
    {
        // *Mutex lock*
        pthread_mutex_lock(&lock);
        for (int i = 0; i < 8; i++)
        {   
            totalSalesPerMonth += salesQ[i];
            totalUperMonth += salesU[i];
        }
        jSales += totalSalesPerMonth;
        julyU = totalUperMonth - variableBillsJ;
        // *Mutex unlock*
        pthread_mutex_unlock(&lock);
    }
    // AUGUST
    if (threadsID == 2)
    {
        // *Mutex lock*
        pthread_mutex_lock(&lock);
        for (int i = 8; i < 16; i++)
        {   
            totalSalesPerMonth += salesQ[i];
            totalUperMonth += salesU[i];
        }
        aSales += totalSalesPerMonth;
        augustU = totalUperMonth - variableBillsA;
        // *Mutex unlock*
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *reports(void *argument) 
{
	int *input = (int *)argument;
    int threadsID = *input;
    string report = "";
    // JULY
    if (threadsID == 1)
    {
        report = " --- Sales per product --- \n";
        for (int i = 0; i < 8; i++)
        {
            report += products[i] + ": Q" + to_string((int)round(salesQ[i])) + " \n";
            
        }

        report += "\n--- Utility per product --- \n";
        for (int i = 0; i < 8; i++)
        {
            report += products[i] + ": Q" + to_string((int)round(salesU[i])) + " \n";
        }
        report += "\nSales total: Q" + to_string((int)jSales) + " \n";
        report += "Variable bills: Q" + to_string((int)variableBillsJ) + " \n";
        report += "Utility of the month: Q" + to_string((int)julyU) + " \n";
        julyReport += report;
    }
    // AUGUST
    if (threadsID == 2)
    {
        int c = 8;
        report = "--- Sales per product --- \n";
        for (int i = 0; i < 8; i++)
        {   
            c = i + 8; // *Counter
            report += products[i] + ": Q" + to_string((int)round(salesQ[c])) + " \n";
        }
        report += "\n--- Utility per product --- \n";
        for (int i = 0; i < 8; i++)
        {
            c = i + 8; // *Counter
            report += products[i] + ": Q" + to_string((int)round(salesU[c])) + " \n";
        }
        report += "\nSales total: Q" + to_string((int)aSales) + " \n";
        report += "Variable bills: Q" + to_string((int)variableBillsA) + " \n";
        report += "Utility of the month: Q" + to_string((int)augustU) + " \n";
        augustReport += report;
    }
    return NULL;
}

// ------- Main method -------
int main(void) {
    pthread_attr_t attr;
    pthread_t threadsID[threadsQuantity];
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&lock, NULL);
    cout << "--- Initializing program...---" << endl;
    for(int i = 0; i < threadsQuantity; i++)
    {
        int id = i;
        pthread_create(&(threadsID[i]), &attr, &threadsMethod, ( void *)&id);  
    }
    for(int i = 0; i < threadsQuantity; i++)
    {
        int id = i ;
        pthread_join(threadsID[id], NULL);
    }
    cout << endl;
    // *Calcs per month*
    for(int i = 1; i < 3; i++)
    {
        int id = i;
        pthread_create(&(threadsID[i]), &attr, &calcsPerMonth, ( void *)&id);
        sleep(1); 
    }
    for(int i = 1; i < 3; i++)
    {
        int id = i ;
        pthread_join(threadsID[id], NULL);   
    }
    // *Reports*
    for(int i = 1; i < 3; i++)
    {
        int id = i;
        pthread_create(&(threadsID[i]), &attr, &reports, ( void *)&id);
        sleep(1);
    }
    for(int i = 1; i < 3; i++)
    {
        int id = i ;
        pthread_join(threadsID[id], NULL);
    }
    // --- Reports print ---
    cout << julyReport << endl;
    cout << augustReport << endl;
    // *Mutex end*
    pthread_mutex_destroy(&lock);
    pthread_attr_destroy(&attr);
	pthread_exit(NULL);
    return 0;
}