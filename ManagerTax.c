#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int taxUnit[100][100];
char taxName[30][100];
int n = 0; //n - number of employee

void optionalScreen ();

int checkInput (int k, int x) {
	int checkFlag = 0;
	switch (k) {
		case 0:
			checkFlag = ((x >= 0) && x <= 8)?1:0;
			break;
		case 1:
			checkFlag = (x == 0)?2:1;
			break;
		case 2:
			checkFlag = (x>0)?1:0;
			break;
		case 3:
			checkFlag = (x == 121 || x == 110)?1:0;
			break;
		case 4:
			checkFlag = (x == 121 || x == 110)?1:0;
			break;
		case 5:
			checkFlag = (x>=0)?1:0;
			break;
		case 6:
			checkFlag = (x>=0)?1:0;
			break;
		case 7:
			checkFlag = (x != 0)?1:0;
			break;
		case 8:
			checkFlag = (x == 0)?0:1;
			break;
	}
	return checkFlag;
}

void clear_stream(FILE *f) { //clear stream from input
    int c;
    clearerr(f); //clears the end of file and error indicators for the given stream
    do {
		c = getc(f); //gets the next character
	}  
    while (c != '\n' && c != EOF);
    clearerr(f);
}

void input (int k, int *x) { //For check if input is valid or not
	char msg [100];
	switch (k) {
		case 0:
			strcpy (msg, "Your selection (0 -> 8): ");
			break;
		// 1 - code, 2 - income, 3 - pens, 4 - health, 5 - dependant, 6 - charity
		case 1:
			strcpy (msg, "Enter code (0 to stop): ");
			break;
		case 2:
			strcpy (msg, "Income for the current month (in thousand VND): ");
			break;
		case 3:
			strcpy (msg, "Pension contributions (5%) y/n ? ");
			break;
		case 4:
			strcpy (msg, "Health insurance (1%) y/n ? ");
			break; 
		case 5:
			strcpy (msg, "Number of dependants < 18 years old: ");
			break;
		case 6:
			strcpy (msg, "Gift of charity: ");
			break;
		case 7:
			strcpy (msg, "Enter code to be searched: ");
			break;
		case 8:
			strcpy (msg, "Enter code to be deleted: ");
			break;
	}
	while (1) {
		printf ("%s", msg);
		fflush (stdin);
		if (k == 4 || k == 3) { //For character input only
			scanf ("%c", x);
		} else {
			//For number input only
			while (scanf("%d", x) != 1) {
        		clear_stream(stdin);
        		printf ("Invalid input, try again.\n");
        		fflush(stdout); //release the current contents of the output buffer
    		}
			
		}
		if (checkInput (k, *x) == 0) {
			printf ("Invalid input, try again.\n");
		} else {
			break;
		}
	}
}

int taxSecondCalc (int k) { //tax calculator
	int i, sum = 0;
	for (i = 1; k > 0; i++) {
		switch (i) {
			case 1: 
				sum += (k <= 5000)?((k*5)/100):((5000*5)/100);
				k -= 5000;
				break;
			case 2:
				sum += (k <= 5000)?((k*10)/100):((5000*10)/100);
				k -= 5000;
				break;
			case 3:
				sum += (k <= 10000)?((k*15)/100):((10000*15)/100);
				k -= 10000;
				break;
			case 4:
				sum += (k <= 10000)?((k*20)/100):((10000*20)/100);
				k -= 10000;
				break;
			case 5:
				sum += (k <= 20000)?((k*25)/100):((20000*25)/100);
				k -= 20000;
				break;
			case 6:
				sum += (k <= 30000)?((k*30)/100):((30000*30)/100);
				k -= 30000;
				break;
			case 7:
				sum += ((k*35)/100);
				k = -1;
				break;
		}
	}
	return sum;
}

void readFile (char fileName [100]) { //read data from the file
	FILE *fileData = fopen (fileName, "a+");
	int i, temp;
	(n) = 0;
	while (fscanf(fileData,"%d",temp) != EOF) { // Check if the line is end
        fscanf (fileData, "%[^\n]", taxName [n]);
        for (i = 1; i < 7; i++) {
        	if (i == 3 || i == 4) { //For character input only
				fscanf (fileData, "%d", &taxUnit[n][i]);
			} else {
				fscanf (fileData, "%d", &taxUnit[n][i]);
			}
		}
        (n) ++;
    }
	fclose (fileData);
}

void overwriteFile (char fileName [100]) { //overwrite the existed file
	int i, j;
	remove(fileName);
	FILE* fileData = fopen (fileName, "w"); //mode w - creating empty and writing only
	for (j = 0; j < n; j++) {
		fprintf (fileData, "\n%s", taxName [j]);
		for (i = 1; i < 7; i ++) {
			fprintf (fileData, "\n%d", taxUnit [j][i]);
		}
	}
	fclose (fileData);
}

void enterList () { //enter the employee information
	int j, a, k = 1;
	int i = n, c = 0;
	system("cls");
	while (k != 0) {
		printf ("Enter personal information:\n");
		input (1, &taxUnit [i][1]);
		k = taxUnit [i][1];
		if (k != 0) {
			printf ("Enter name: ");
			fflush (stdin);
			scanf ("%[^\n]", taxName [i]);
			fflush (stdin);
			for (j = 2; j < 7; j++) {
				input (j, &taxUnit [i][j]);
			}
			printf ("--------------------------------------------------------------------------------------------------\n");
			(i)++;
			c++;
		}
		system ("cls");
	}
	n += c;
	printf ("List has been updated!\n");
}

void displayLayout (int x, int code, char name[100], int income, int allow, int pens, int ins, int depend, int charity, int taxable, int tax, int net) { //for display
	char msgDisplay [100];
	switch (x) {
		case 0:
			strcpy (msgDisplay, "Code      name     income    allow    pens     ins   depend   charity     taxable     tax      net\n"); 
			printf ("%s", msgDisplay);
			printf ("--------------------------------------------------------------------------------------------------\n");
			break;
		case 1:
			printf ("%4.3d%10s%11d%9d%8d%8d%9d%10d%12d%8d%9d\n", code, name, income, allow, pens, ins, depend, charity, taxable, tax, net);
	}
}

void displayLayoutHeader () { //for display
	displayLayout (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
}

void detailCalc (int i, int taxUnit[100][100], int *pens, int *ins, int *taxable, int *tax, int *net, int *total, int *dependant, int *charity) {
	//Calculate the detail number of tax
	*dependant = taxUnit[i][5] * 1600;
	*pens = (taxUnit[i][3] == 121)?(taxUnit[i][2]*5)/100:0;
	*ins = (taxUnit[i][4] == 121)?(taxUnit[i][2]*1)/100:0;
	*charity = taxUnit[i][6];
	*total = 4000 + *pens + *ins + *dependant + *charity;
	*taxable = (taxUnit[i][2] >= *total)?taxUnit[i][2] - *total:0;
	*tax = taxSecondCalc (*taxable);
	*net = taxUnit[i][2] - *tax;
}

void displayList (int m, int x) { //display all employee information
	system ("cls");
	int allow = 4000, pens, ins, taxable, tax, net, total, dependant, charity;
	int i;
	if (m == 0) {
		displayLayoutHeader ();
		for (i = 0; i < n; i++) {
			detailCalc (i, taxUnit, &pens, &ins, &taxable, &tax, &net, &total, &dependant, &charity);
			// 1 - code, 2 - income, 3 - pens, 4 - health, 5 - dependant, 6 - charity
			displayLayout (1, taxUnit[i][1], taxName[i], taxUnit[i][2], allow, pens,ins,dependant,charity, taxable, tax, net);
			
		}
	} else if (m == 1) { //For searching option only
		printf ("Result for searching code number %d:\n", x);
		displayLayoutHeader ();
		for (i = 0; i < n; i++) {
			if (taxUnit[i][1] == x) {
				detailCalc (i, taxUnit, &pens, &ins, &taxable, &tax, &net, &total, &dependant, &charity);
				displayLayout (1, taxUnit[i][1], taxName[i], taxUnit[i][2], allow, pens,ins,dependant,charity, taxable, tax, net);
			}
		}
	}
}
	
void searchEmployee () { //search by code
	int x;
	input (7, &x);
	system ("cls");
	displayList (1, x);
}

void swap (int *a, int *b) { //swap two value (for taxUnit)
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void sortOrder () { //sort by increasing order
	int i, j, k;
	char temp [100];
	for (i = 0; i < n; i ++) {
		for (j = i + 1; j < n; j ++) {
			if (taxUnit [i][1] > taxUnit [j][1]) {
				strcpy (temp, taxName [i]);
				strcpy (taxName [i], taxName [j]);
				strcpy (taxName [j], temp);
				for (k = 1; k < 7; k ++) {
					swap (&taxUnit [i][k], &taxUnit [j][k]);
				}
			}
		}
	}
	system ("cls");
	printf ("File list has been sorted directly!\n");
}

void bubbleSortIncr (char fileName [100]) { //bubble sort increasing
	int i, j;
	int count = n;
	char temp [100];
	while (count > 0) {
		for (i = 0; i < n - 1; i ++) {
			if (taxUnit [i][1] > taxUnit [i+1][1]) {
				strcpy (temp, taxName [i]);
				strcpy (taxName [i], taxName [i+1]);
				strcpy (taxName [i+1], temp);
				for (j = 1; j < 7; j ++) {
					swap (&taxUnit [i][j], &taxUnit [i + 1][j]);
				}
			}
		}
		count--;
	}
	//overwrite file
	overwriteFile (fileName);
	//finish overwrite file
	system ("cls");
	printf ("File list %s has been sorted by bubble sort!\n", fileName);
}

void bubbleSortDecr (char fileName [100]) { //bubble sort decreasing
	int i, j;
	int count = n;
	char temp [100];
	while (count > 0) {
		for (i = 0; i < n - 1; i ++) {
			if (taxUnit [i][1] < taxUnit [i+1][1]) {
				strcpy (temp, taxName [i]);
				strcpy (taxName [i], taxName [i+1]);
				strcpy (taxName [i+1], temp);
				for (j = 1; j < 7; j ++) {
					swap (&taxUnit [i][j], &taxUnit [i + 1][j]);
				}
			}
		}
		count--;
	}
	//overwrite file
	overwriteFile (fileName);
	//finish overwrite file
	system ("cls");
	printf ("File list %s has been sorted by bubble sort!\n", fileName);
}


void bubbleSort (char fileName [100], int m) { //bubble sort switch to mode
	switch (m) {
		case 1: 
			bubbleSortIncr (fileName);
			break;
		case 2:
			bubbleSortDecr (fileName);
			break;
	}
}

int checkSort (int m) { //check sort
	int i = 0;
	system ("cls");
	if (m == 1) {
		while (i < n - 1) {
			if (taxUnit[i][1] > taxUnit[i+1][1]) {
				return 1;
			}
			i++;
		}
	} else if (m == 2) {
		while (i < n - 1) {
			if (taxUnit[i][1] < taxUnit[i+1][1]) {
				return 1;
			}
			i++;
		}
	}
	
	return 0;
}

void deleteData () { //delete rows have the code
	int x, i, j, k;
	input (8, &x);
	//x - code to delete
	for (i = 0; i < n; i ++) {
		if (taxUnit [i][1] == x) {
			for (j = i; j < n - 1; j ++) {
				strcpy (taxName [j], taxName [j+1]);
				for (k = 1; k < 7; k ++) {
					taxUnit [j][k] = taxUnit [j+1][k];
				}
			}
			n--;
		}
	}
	system ("cls");
	printf ("Code number %d has been deleted!\n", x);
}

void optionShow () { //show list of option
	printf ("Choose one of the following options:\n1. Enter name of a file to store data\n2. Enter a list of employees\n3. Display a tax information\n4. Search an employee by code\n5. Sort in increasing order by code\n6. Sort directly on file by bubble sort\n7. Check if data on the file is sorted or not\n8. Delete an employee by code\n0. Exit\n");
}

/* ----- USER MANUAL
1. Stored exist data in file (overwrite or create new if data exist) (read file if data is null)
2. Update list then write to file (if file name exist)
3. Display list (prioritise displaying from the file if file exist)
4. Search the employees have the code (prioritise searching from the file if file exist)
5. Sort order by increasing code (without modify the existed file)
6. Sort directly on file by using bubble sort algorithm  (file existence is necessary)
7. Check if the list is sorted or not
8. Delete employees which have the typed code (modify the file if file exist)
------ */

void optionalScreen () { //main screen
	char fileName [100];
	fileName [0] = '\0';
	int x, k;
	optionShow ();	
	input (0, &x);
	while (1) {
		switch (x) {
			//0 - exit, 1 - enter file, 2 - enter list, 3 - display, 4 - search, 5 - sort directly, 6 - bubble sort, 7 - check sort, 8 - delete employee
			case 0:
				system ("cls");
				printf ("Thank you for using our product!");
				exit (0);
				break;
			case 1:
				printf ("Enter file name: ");
				fflush (stdin);
				scanf ("%s", fileName);
				system ("cls");
				
				if (taxUnit [0][1] != 0) {
					overwriteFile (fileName);
					printf ("List has been stored in file %s!\n", fileName);
				}
				else {
					readFile (fileName);
					printf ("List has been updated by reading file %s!\n", fileName);
				}
				break;
			case 2:
				enterList ();
				if (fileName[0] != '\0') {
					overwriteFile (fileName);
					printf ("List has been restored in file %s!\n", fileName);
				}
				break;
			case 3:
				displayList (0, 0);
				break;
			case 4:
				searchEmployee ();
				break;
			case 5:
				sortOrder ();
				break;
			case 6:
				while (fileName [0] == '\0') {
					printf ("You must enter the file name to bubble sort directly on file!\n");
					printf ("--------------------------------------------------------------------------------------------------\n");
					printf ("Enter file name: ");
					fflush (stdin);
					scanf ("%s", fileName);
				}
				k = 0;
				printf ("1. Increasing\n2. Decreasing\n");
				printf ("Choose type of sort (1 or 2): ");
				scanf ("%d", &k);
				while ((k != 1) && (k != 2)) {
					printf ("Invalid input, try again.\n");
					printf ("Choose type of sort (1 or 2): ");
					scanf ("%d", &k);
				}
				bubbleSort (fileName, k);
				break;
			case 7:
				k = 0;
				printf ("1. Check increasing\n2. Check decreasing\n");
				printf ("Choose type of check sort (1 or 2): ");
				scanf ("%d", &k);
				while ((k != 1) && (k != 2)) {
					printf ("Invalid input, try again.\n");
					printf ("Choose type of check sort (1 or 2): ");
					scanf ("%d", &k);
				}
				(checkSort (k) == 1)?printf ("Not sorted yet!\n"):printf ("Sorted!\n");
				break;
			case 8:
				deleteData ();
				overwriteFile (fileName); //TODO: fix
				break;
		}
		printf ("--------------------------------------------------------------------------------------------------\n");
		optionShow ();	
		input (0, &x);
	}
}
	
int main () {
	optionalScreen ();
}