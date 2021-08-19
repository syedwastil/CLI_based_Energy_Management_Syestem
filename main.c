#include<stdio.h>
#include<Windows.h>
void grid(int, int);//to control position of cursor
void Beginning(void);//display front page
void Headings(void);//display timing of day
float Scanning(void);//gets readings and convert it to month reading
float Bill_Calculator(float);//apply math to calculate bill
float taxAddition(float);//apply taxes to bill
void File_handling(void);//create or open file and check count etc and last reading from saved file
void Report(void);// create statistical report
void Month(int);// check name of month
void save_file(void);// update backend file
void record_display(void);// display record save in backend file
FILE *record;
unsigned int last_reading = 0, count = 0, year;
unsigned int readings[4][7] = { 0 };
float monthly_record[12][2] = { 0 };
int main()
{

	Beginning();//display the Front page
	int option = 1;;//double semicolon to recieve option many times
	do {
		year = 2018;
		File_handling();
		printf("\n%47s", "ENTER THE METER READINGS FOR ");
		Month(count % 12);
		printf("-%d", year);
		printf("\n\n%s", "    TIME     ");
		for (int i = 1; i < 8; i++)
		{
			printf("%s %d    ", "DAY", i);
		}
		Headings();
		monthly_record[count % 12][0] = Scanning();//save units consumed in first dimension of monthly_record array
		monthly_record[count % 12][1] = Bill_Calculator(monthly_record[count % 12][0]);//save price in second dimension of monthly_record array
		printf("\nYOUR ESTIMATED ELECTRICITY BILL FOR THIS MONTH IS: Rs %.2f", monthly_record[count % 12][1]);
		save_file();// update backend file
	o:printf("\n\nENTER '1' TO SEE A STATISTICAL REPORT ON YOUR BILL\n\nENTER '2'TO SEE THE COMPLETE RECORD OF PAST 1 YEAR BILLS\n\nENTER '3' TO PERFORM CALCULATIONS FOR NEXT MONTH\n\nENTER '0' TO EXIT\n\n");
		scanf_s("%d", &option);
		fflush(stdin);//flush out unnecessary input
		switch (option)
		{
		case 1:
		{
			Report();
			goto o;//move to label o
		}
		break;
		case 2:
		{
			record_display();
			goto o;
		}
		break;
		case 3:
			system("cls");//clear out console
			break;
		default:
			return 0;
			break;
		}
	} while (option != 0);
	system("pause");
}
void grid(int row, int column)//to control position of cursor
{
	COORD coord;//COORD is defined in windows.h 
	coord.X = column;
	coord.Y = row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//it is used to set the position of cursor
}
void Beginning(void)//display front page
{
	grid(12, 47);//move cursor to given coordinates
	printf("WELCOME");
	grid(14, 49);//move cursor to given coordinates
	printf("TO");
	grid(16, 37);//move cursor to given coordinates
	printf("ONLINE BILL CALCULATING PORTAL");
	Sleep(4000);//hold console for 4 sec
	system("cls");
	grid(15, 40);
	printf("ENTER THE REQUIRED DATA PLEASE");
	Sleep(2000);//hold console for 2 sec
	system("cls");
}
void Headings(void)//display timing of day
{
	printf("\n");
	int initial_time = 0, final_time = 6;
	for (int i = 0; i < 4; i++)
	{
		if (i<1)
			printf("\n0%d:00-0%d:00\n", initial_time, final_time);
		if (i == 1)
		{
			printf("\n06:00-12:00\n");
		}
		if (i > 1)
			printf("\n%d:00-%d:00\n", initial_time, final_time);
		initial_time += 6;
		final_time += 6;
	}
}
float Scanning(void)//gets readings and convert it to month reading
{
	int column = 0;
	unsigned int final_meter, sum = 0;
	for (int i = 13; i < 70; i += 9)
	{
		int row = 0;
		for (int j = 5; j < 12; j += 2)
		{
		x:grid(j, i);//move cursor to given coordinates
			scanf_s("%u", &final_meter);
			fflush(stdin);
			if (final_meter <last_reading || (final_meter / 10000000) != 0)
			{
				grid(j, i);//move cursor to given coordinates
				printf("                                                     ");
				goto x;
			}
			readings[row][column] = final_meter - last_reading;//store units consumed to array reading
			sum = sum + readings[row][column];//sum up units consumed
			last_reading = final_meter;//update last reading
			row++;
		}
		column++;
	}
	return sum * 4;//as a month contain average 4 week
}
float Bill_Calculator(float reading)//apply math to calculate bill
{
	float x = 0;
	if (reading <= 50)
	{
		x = reading * 2;
	}
	else if (reading >50 || reading <= 100)
	{
		x = 50 * 2 + (reading - 50) * 4.79;
	}
	else if (reading >100 || reading <= 200)
	{
		x = (50 * 2 + 50 * 4.79 + (reading - 100)*8.11);
	}
	else if (reading >200 || reading <= 300)
	{
		x = (50 * 2 + 50 * 4.79 + 100 * 8.11 + (reading - 200)*10.2);
	}
	else if (reading>300 || reading <= 700)
	{
		x = (((50 * 2 + 50 * 4.79 + 100 * 8.11 + (100)*10.2 + (reading - 300)*13.33)) + (reading*2.67));//Tariff Rationalization Surcharge included
	}
	else if (reading > 700)
	{
		x = (((50 * 2 + 50 * 4.79 + 100 * 8.11 + (100)*10.2 + (400)*13.33 + (reading - 700) * 16)) + (reading*3.9));//Tariff Rationalization Surcharge included
	}
	x = x + taxAddition(x);
	return x;
}
float taxAddition(float cost)//apply taxes to bill
{
	float price = cost;
	if (price <= 500)
	{
		price += price * 0;
	}
	else if (500 <price || price <= 3000)
	{
		price = (price + 0.05*price);
	}
	else if (price>3000)
	{
		price = (price + 0.15*price);
	}
	float x = price;
	x = x + (0.0125*x);//Electricity Duty and N.J Surcharge
	x = x - (0.0199*price);//fuel price adjustment
	x = x + (0.05*price);//Financing Coast Surcharge
	x = x + 35;//PTV Fee
	x = x + (0.03*price); //GST Tax
	return x;
}

void File_handling(void)//create or open file and check count etc and last reading from saved file
{
	int x;
	record = fopen("Bills.txt", "a");//opens file bills.txt for addition if exist othervise create it
	fseek(record, 0, SEEK_END);//reads file from after giving offset zero till end of file
	x = ftell(record);
	fclose(record);//close the file
	record = fopen("Bills.txt", "r");//again open the file to read
	/*Read values and store them in monthly record array*/
	if (x != 0)
	{
		for (int i = 0; i < 12; i++)
		{
			for (int j = 0; j < 2; j++) {
				fscanf_s(record, "%f", &monthly_record[i][j]);
			}
		}
		fscanf_s(record, "%u", &last_reading);//update last reading
		fscanf_s(record, "%u", &count);//update count
	}
	fclose(record);//close the file
	year = year + (count / 12);
}
void Report(void)// create statistical report
{
	system("cls");//clear out console
	int sort[4];//create a 4 integer array

	for (int i = 0; i < 4; i++) {
		int total = 0;
		for (int j = 0; j < 7; j++) {
			total += readings[i][j];//sum up all the units consumed for i(time interval) of whole week to total
		}
		total /= 7;//calculate average units consumed per day for same time interval i
		sort[i] = total; //store total units of that time interval in array sort
	}
	printf("\n\nTHE HISTOGRAM SHOWS AVERAGE CONSUMPTION OF UNITS WITH RESPECT TO TIME\n");
	printf("    TIME           UNITS CONSUMED");
	Headings();
	int element = 0;
	/*print histogram*/
	for (int i = 5; i < 14; i += 2)
	{
		grid(i, 13);//move cursor to given coordinates
		for (int j = 0; j < sort[element]; j++) 
		{
			if (j > 70)
				continue;
			printf("*");
		}
		element++;
	}
	/*store maximum units consumed from array sort to element*/
	element = sort[0];
	for (int i = 0; i < 4; i++) {
		if (element < sort[i])
			element = sort[i];
	}
	/*store index of sort[] containing max units consumed*/
	for (int i = 0; i < 4; i++) {
		if (sort[i] == element)
			element = i;
	}
	printf("\n\nYOUR MAXIMUM UNITS CONSUMPTION IS IN THE TIME INTERVAL: %d:00-%d:00\n", element * 2, (element * 2) + 6);
	Sleep(6000);//hold console for 6 sec
	printf("\nABIDE BY THE FOLLOWING STRATEGIES TO SAVE ENERGY AND REDUCE BILL\n\n");
	Sleep(2000);//hold console for 2 sec
	printf("1.TURN OFF LIGHTS NOT IN USE AND PREFER NATURAL LIGHT DURING DAY TIME\n\n");
	Sleep(3000);//hold console for 3 sec
	printf("2.USE ENERGY SAVER (15WATT,25WATT) RATHER THAN ORDINARY LIGHT BULB\n\n");
	Sleep(3000);//hold console for 3 sec
	printf("3.DO NOT USE HEAVY LOADS IN THE HIGH ENERGY CONSUMPTION HOURS ,FROM 6 PM TO 10 PM\n\n");
	Sleep(3000);//hold console for 3 sec
	printf("4.USE ELECTRIC HEATERS AND GEEZERS ONLY WHEN REQUIRED\n\n");
	Sleep(3000);//hold console for 3 sec
	printf("5.RUN AIR CONDITIONERS AT OPTIMUM TEMPERATURE ( 26 DEGREE)\n\n");
	Sleep(3000);//hold console for 3 sec
	printf("6.INSULATE THE ROOFS INSTEAD OF USING COOLING DEVICES\n\n");
	Sleep(3000);//hold console for 3 sec
	printf(" INSTRUMENT    QUANTITY    WATT     UNITS USED    SAVAGE\n\n");
	printf("  BULB          4           400      42            __\n\n");
	printf("  TUBE LIGHT    4           160      18            57%%\n\n");
	printf("  ENERGY SAVER  4           80       9             80%%\n\n");
	Sleep(3000);//hold console for 3 sec
	printf("In case of any HUMAN RIGHTS VIOLATIONS contact to helpline 1099 for free legal advice and service\n");
}
void Month(int a)// check name of month
{
	if (a == 0)
		printf("JAN");
	if (a == 1)
		printf("FEB");
	if (a == 2)
		printf("MAR");
	if (a == 3)
		printf("APR");
	if (a == 4)
		printf("MAY");
	if (a == 5)
		printf("JUN");
	if (a == 6)
		printf("JUL");
	if (a == 7)
		printf("AUG");
	if (a == 8)
		printf("SEP");
	if (a == 9)
		printf("OCT");
	if (a == 10)
		printf("NOV");
	if (a == 11)
		printf("DEC");
}
void save_file(void)// update backend saved text file
{
	record = fopen("Bills.txt", "w");//opens file Bills.txt
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 2; j++) {
			fprintf_s(record, "%10.2f", monthly_record[i][j]);//print array of monthly_record in text file
		}
		fprintf_s(record, "\n");
	}
	count++;
	fprintf_s(record, "%u\n", last_reading);//print array of in text file
	fprintf_s(record, "%u", count);
	fclose(record);//close file Biils.txt
}
void record_display(void)// display record save in backend file
{
	system("cls");//clear console
	printf("\nYOUR PREVIOUS 1 YEAR RECORD IS:\n\n");
	printf("%-15s%-15s%-12s\n\n", "MONTH", "UNITS", "BILL");
	for (int i = 0; i < 12; i++) {
		Month(i);
		if (i <= (count - 1) % 12)//for 12 times of program execution if statement remains true i.e prints same year
			printf("-%d       ", year);
		else
			printf("-%d       ", year - 1);//after a year it will show record of previous year
		for (int j = 0; j < 2; j++) {
			printf("%-10.2f", monthly_record[i][j]);//print array monthly record
		}
		printf("\n\n");
	}
}
