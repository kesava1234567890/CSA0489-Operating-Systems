#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};
void addEmployee(FILE *file, struct Employee employee) {
    fseek(file, 0, SEEK_END); 
    fwrite(&employee, sizeof(struct Employee), 1, file);

    printf("Employee added successfully.\n");
}
void displayEmployees(FILE *file) {
    struct Employee employee;
    fseek(file, 0, SEEK_SET);
    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        printf("Employee ID: %d\n", employee.empId);
        printf("Employee Name: %s\n", employee.empName);
        printf("Employee Salary: %.2f\n", employee.empSalary);
        printf("-----------------\n");
    }
}
void updateEmployee(FILE *file, int empId, float newSalary) {
    struct Employee employee;
    fseek(file, 0, SEEK_SET);
    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        if (employee.empId == empId) {
            employee.empSalary = newSalary;
            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&employee, sizeof(struct Employee), 1, file);

            printf("Employee record updated successfully.\n");
            return;
        }
    }

    printf("Employee with ID %d not found.\n", empId);
}

int main() {
    FILE *file;
    struct Employee employee;
    file = fopen("employee_data.dat", "rb+");

    if (file == NULL) {
        file = fopen("employee_data.dat", "wb+");
        if (file == NULL) {
            perror("Error opening the file");
            exit(EXIT_FAILURE);
        }
    }
    employee.empId = 101;
    strcpy(employee.empName, "John Doe");
    employee.empSalary = 50000.0;
    addEmployee(file, employee);
    printf("\nEmployee Details:\n");
    displayEmployees(file);
    updateEmployee(file, 101, 55000.0);
    printf("\nEmployee Details After Update:\n");
    displayEmployees(file);
    fclose(file);

    return 0;
}

