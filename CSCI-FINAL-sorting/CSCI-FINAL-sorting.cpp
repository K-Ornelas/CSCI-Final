#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// This function takes in the names of the students from an outsourced file
void readStudentsFromFile(ifstream& infile, string A[], int numStudents) {
    for (int i = 0; i < numStudents; i++)
    {
        getline(infile, A[i]);  
    }
}

// This function helps the sorting function switch the names around
void swap(string& x, string& y) {
    string temp = x;
    x = y;
    y = temp;
}

// This function grabs the last name from a full name
string lastName(const string& fullName) {
    size_t spaceIndex = fullName.find_last_of(' ');  
    if (spaceIndex != string::npos) 
    {
        return fullName.substr(spaceIndex + 1);  // Extracts last name
    } 
    return fullName; 
}

// This function gets the first name from a full name
string firstName(const string& fullName) {
    size_t spaceIndex = fullName.find(' '); 
    if (spaceIndex != string::npos)
    {
        return fullName.substr(0, spaceIndex);  // Extract first name
    }
    return ""; 
}

// This function gets the index of the student with the smallest last name, 
// and if the last name is the same, it compares the first name.
int lastNameindex(string A[], int start, int end) {
    int minLocation = start;

    for (int i = start + 1; i <= end; i++) 
    {
        if (lastName(A[i]) < lastName(A[minLocation]) ||
            (lastName(A[i]) == lastName(A[minLocation]) && firstName(A[i]) < firstName(A[minLocation]))) 
        {
            minLocation = i;
        }
    }
    return minLocation;
}

// This function sorts the students by last name
void sortStudents(string A[], int start, int end) {
    for (int i = start; i <= end; i++) 
    {
        int firstIndex = lastNameindex(A, i, end);
        swap(A[i], A[firstIndex]);  
    }
}

// This function prints the names in "Last Name, First Name" format
void print(string A[], int start, int end) {
    for (int i = start; i <= end; i++) 
    {
        string last = lastName(A[i]);
        string first = firstName(A[i]);
        cout << last << ", " << first << endl;  
    }
}

int main() {
    int numStudents;
    string filename = "StudentNames.txt";  

    cout << "Enter the number of students: ";
    cin >> numStudents;
   

    string* students = new string[numStudents];  // Dynamically allocate memory for student names

    ifstream infile(filename);
    if (!infile) 
    {
        cout << "Error opening file" << endl;
        delete[] students;  
        return 1; 
    }

   
    readStudentsFromFile(infile, students, numStudents);

    // Close the file after reading
    infile.close();

  
    sortStudents(students, 0, numStudents - 1);

  
    cout << "Sorted student names: " << endl;
    print(students, 0, numStudents - 1);

    delete[] students; 
    return 0;
}
