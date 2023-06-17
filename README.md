# coffeeShopInventory
This code simulates a coffee shop's inventory, generating monthly sales reports. It employs pthreads for parallel processing and handles data on coffee and food products, including prices, costs, and sales quantities for July and August. The code calculates monthly sales and utility, considering variable bills, and generates detailed reports per product. It ensures thread safety using mutex locks for shared data access and modification. Overall, it provides a synchronized and efficient system for inventory management and financial analysis in the coffee shop.

<p align="center">
  <br>
  <img src="https://i.pinimg.com/originals/4c/74/87/4c74874a249702e462e15f488924ff18.gif" alt="pic" width="500">
  <br>
</p>
<p align="center" >
  <a href="#Files">Files</a> •
  <a href="#Features">Features</a> •
  <a href="#how-to-use">How To Use</a> 
</p>

## Files

- src: the file that implements de solution.
- flowchart: flowchart: the model construction.

## Features
The main features of the application include:
- Simulation of a coffee shop's inventory: The code simulates the inventory of a coffee shop, including various coffee and food products. It keeps track of prices, costs, and sales quantities for different items.
- Parallel processing with pthreads: The code utilizes pthreads, a library for creating and managing threads, to achieve parallel processing. This allows for efficient execution of multiple tasks simultaneously.
- Monthly sales reports: The code generates detailed sales reports for each month, specifically for July and August. The reports include sales quantities and utility per product, as well as the overall sales total, variable bills, and monthly utility.
- Mutex locks for thread synchronization: Mutex locks are implemented to ensure thread safety when accessing and modifying shared data, such as the inventory and sales information. This prevents data corruption and race conditions among multiple threads.
- Efficient data handling: The code organizes data using arrays and constants, making it easy to manage and calculate various metrics such as sales quantities, prices, costs, and utilities. This promotes code readability and maintainability.
- Synchronized output: The code ensures synchronized output by using mutex locks when printing reports. This prevents conflicts and ensures that the reports are displayed in a coherent manner.


## How To Use
To clone and run this application, you'll need [Git](https://git-scm.com) and a [C++ compiler](https://www.fdi.ucm.es/profesor/luis/fp/devtools/mingw.html) installed on your computer. From your command line:

```bash
# Clone this repository
$ git clone https://github.com/bl33h/coffeeShopInventory

# Open the folder
$ cd src

# Run the app
$ g++ coffeeShopInventory.cpp -o coffeeShopInventory
$ ./coffeeShopInventory
```

Alternatively, you can run the code using Google Colab:
1. [Open Google Colab](https://colab.research.google.com) in your web browser.
2. Click on "File" in the top menu, then select "Open notebook".
3. In the "GitHub" tab, enter the repository URL: https://github.com/bl33h/coffeeShopInventory
4. Choose the desired notebook file and click "Open".
5. Follow the instructions within the Colab notebook to execute the code.

Note: Running the code in Google Colab requires an internet connection and a Google account. It provides a convenient online environment for executing code without the need for local setup or dependencies.
