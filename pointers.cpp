// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <iomanip>


typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;

    //get id number
    student.id = promptInt("Please enter the student's id number: ", 0, 999999999);
    
    //get first name
    student.f_name = new char[128];
    while (true) {
        std::cout << "Please enter the student's first name: ";
        std::cin.getline(student.f_name, 128);

        if (true) break; //assume valid name is given for now

        std::cout << "Sorry, I cannot understand your answer";
    }

    //get last name
    student.l_name = new char[128];
    while (true) {
        std::cout << "Please enter the student's last name: ";
        std::cin.getline(student.l_name, 128);

        if (true) break; //assume valid name is given for now

        std::cout << "Sorry, I cannot understand your answer";
    }
    
    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1, 134217728);

    //allocate n_assignments + 1 amount of memory and set index zero to n_assignments
    student.grades = new double[student.n_assignments + 1];
    student.grades[0] = student.n_assignments;

    for (int i = 1; i <= student.n_assignments; i++) { //index of assignments starts at 1 -> grades[0] is n_assignments
        std::string text = "Please enter grade for assignment ";
        text += std::to_string(i);
        text += ": ";
        student.grades[i] = promptDouble(text, 0, 1000.0);
    }

    double average = 0.0;
    calculateStudentAverage(student.grades, &average);
    std::cout << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]\n";
    
    //key for decimal precision: you need to used fixed to tell how many you want after decimal place, as well as showpoint,
    //otherwise, it will just show the first x numbers regardless of where the decimal is
    std::cout << "  Average grade: " << std::fixed << std::showpoint << std ::setprecision(1) << average;
    
    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    char *str = new char[128];
    int common_int = -1;
    bool is_all_numbers = false;

    while (true) {
        std::cout << message;
        std::cin.getline(str, 128);

        //check if all numbers
        int size = std::char_traits<char>::length(str); //find length of char array
        for (int i = 0; i < size; i++) {

            //break 
            if (str[i] < '0' || str[i] > '9') break;

            //if you make it all the way through and haven't found a non-int, you're good
            if (i == size - 1) {
                is_all_numbers = true;
                common_int = atoi(str);
            }
        }

        if (common_int >= min && common_int <= max && is_all_numbers == true) break;
        std::cout << "Sorry, I cannot understand your answer\n";
    }
    
    return common_int;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    double common_double = -1.0;
    char *str = new char[128];
    

    while(true) {
        int num_decimals = 0;
        bool is_all_numbers = false;
        std::cout << message;
        std::cin.getline(str, 128);

        int size = std::char_traits<char>::length(str); //find length of char array
        for (int i = 0; i < size; i++) {
            //check to see if the one decimal that can occur is here
            if (str[i] == '.' && num_decimals > 0) {
                break;
            } else if (str[i] == '.' && num_decimals == 0) {
                num_decimals++;
                continue;
            }
        
            if ((str[i] < '0' || str[i] > '9')) break; //not valid 
            if (i == size - 1) is_all_numbers = true; //if made to end of string -< make true
        }
        
        //at this point, you know whether you have a valid number ot not -> execute based on that
        if (is_all_numbers) {
            //parse the number
            common_double = atof(str);
            
            //if common_number in range, break so you can return it return it. else, continue to sorry statememt
             if (common_double >= min && common_double <= max) break;
        } 
        

        std::cout << "Sorry, I cannot understand your answer \n";
    }

    return common_double;
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    
    /*
    std::cout << object; //prints memory location of object
    std::cout << " " << *(double*)object; //prints first element in array
    std::cout << " " << (((double*)object)[0]); //prints first element in array

    NOTES: When sending a value to a pointer, you want to send a memory address to work the
    value at that address
    */

    //CODE:
    int size = (int) (((double*)object)[0]); //i passed length in as the first item in array
    double total = 0;
    std::cout << size << "\n\n";

    for (int i = 1; i <= size; i++) {
        
        total += (((double*)object)[i]);
        std::cout << (((double*)object)[i]) << "\n";
    }

    *avg = total / size;
}

