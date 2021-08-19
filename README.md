# CLI_based_Energy_Management_Syestem
## Introduction  : 
The project that is named as “Energy Management System” written in C language.
###### Here are some introductory points about our program :
>	* This program calculates the electricity bill for a month. It prepares a statistical report which includes an hour-by-hour description and units.
>	* It also includes a histogram which is plotted by calculating the average consumption of units.
>	* The program also calculates the peak values of energy consumption.
>	* In addition, it also prepares a year-by-year report and you can see your previous year’s record very easily.
>	* Last but not the least, this program also displays some useful energy saving tips keeping in view, the energy usage.   
## How to run :
This program takes only integer values. Hour-by-hour values for units are required by the user to enter and after that, it will calculate estimated bill for a month by using data collected from just 1 week!  After that, it gives 3 options:
1. Statistical Report
2. Record	
3. Exit
Note : Wait for 6 seconds at starting of the execution.
   ## Function Signatures :
 •   Following are the functions that were used for the program:
#### void grid ( int, int) :
  •    This function was used for the proper positioning of the cursor i.e when you execute the program, see how the arrays are formatted in proper grid positions. This function takes 2 integer values as rows and columns and returns nothing.
#### void Beginning (void) :
   •     This function takes no inputs and returns nothing. This function is only used to display the front Welcome Page and it includes some formatting for it to be at the very centre of the console.

#### void Headings (void) : 
   •   This function takes no values and returns nothing. Actually, it was used for displaying the timings in hours  at the start of programs. It only displays the headings.

#### float Scanning (void) : 
   •     This function is a float-type. It takes void as input and returns a floating point value. What this function does, is that it takes the input values of units from the user and stores it. Interestingly, you cannot put a next unit smaller that previous unit. It also includes some formatting using previously discussed grid function as well. 

#### float Bill_Calculator (float) : 
   •    This function does some of the main task. It calculates the estimated bill of the month by using the values of units from the user. Actually, it also uses the taxAddition function for calculating the estimated bill for a month. 

#### float taxAddition(float) :
   •   This function takes inputs of floating types and returns a float value. It applies taxes to the  bill including GST  surcharges etc.

#### void File_handling(void) :
   •   This function again does not have any values for inputs and outputs. This function is used to create, open, read and write the file for the saved report for last year at the backend from the saved file.

#### void Report (void) :
   •                                This function takes no values and returns nothing. This function makes the statistical report of the month which includes the histogram and the useful energy saving tips. It also determines the peak usage time. 

#### Void Month (int) :
   •                              This function is mainly loop oriented. It actually runs a cycle for the months for example, when you have entered usage for the month January, next time at the execution, you will have the month February to put values about. It returns nothing but takes integer as an input. 

#### Void save_file(void) :
   •                                     This function updates the file saved at the backend whenever the program is executed successfully to the end. This function takes no inputs and returns nothing. 

#### Void record_display(void) :
   •                                             This function makes the use of the file saved at the backend. It reads the file and displays the file on the console whenever you wish to see the year-by-year report.
