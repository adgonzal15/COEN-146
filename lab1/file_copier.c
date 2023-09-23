//
//  Created by Behnam Dezfouli
//  CSEN, Santa Clara University
//
//
// This program offers two options to the user:
// -- Option 1: enables the user to copy a file to another file.
// The user needs to enter the name of the source and destination files.
// -- Option 2: enables the user to measure the performance of file copy.
// In addition to the name of source and destination files, the user needs to enter the maximum source file size as well as the step size to increment the source file size.
//
//
// double copier(FILE *s_file, FILE *d_file)
// Precondition: s_file is a pointer to a file opened in read mode, d_file is a file pointer opened in write mode
// Postcondition: Copies the contents of the file pointed to by s_file to the file pointed to by d_file
//

#include <stdio.h>
#include <stdlib.h> // For exit()
#include <time.h>
#include <unistd.h>
#include <fcntl.h>


#define SIZE 1
#define DUM_CHAR 'A'

void func_copier(char *s_file, char *d_file)
{
    FILE *src = fopen(s_file,"r");
	FILE *dest = fopen(d_file,"w");
	char buffer[100];
    int bytes_read;
    while (!feof(src)) {
		bytes_read = fread(&buffer, 1, sizeof(buffer), src);
		fwrite(&buffer, 1, bytes_read, dest);
	}
	fclose(src);
	fclose(dest);
}

void sys_copier(char *s_file, char *d_file)
{
	int src = open(s_file, O_RDWR);
	int dest = open(d_file, O_WRONLY | O_CREAT | O_TRUNC);
	char buffer[100];
    int bytes_read, bytes_written;
	while (1) {
  		bytes_read = read(src, buffer, sizeof(buffer));
        if (bytes_read == 0) {
            break;
        }
        bytes_written = write(dest, buffer, bytes_read);
	}
	close(src);
	close(dest);
}

int main()
{
    // Asking the user whether they would like to perform option 1 or 2
    int option;
    printf("Would you like to perform option 1 or 2? (1/2): ");
    scanf("%d", &option);
    if (option == 1) // File copy
    {
        // Getting source file from user
        char source[20];
        printf("Enter the source file: ");
        scanf("%s", source);
        // Getting destination file1 from user
        char destination1[20];
        printf("Enter the destination file1: ");
        scanf("%s", destination1);
        // Getting destination file2 from user
        char destination2[20];
        printf("Enter the destination file2: ");
        scanf("%s", destination2);
        // Copying contents of source file to destination file
        func_copier(source, destination1);
        sys_copier(source, destination2);
    }

    else if (option == 2) // File copy with performance measurement
    {
        // Getting source file from user
        char source[20];
        printf("Enter the source file: ");
        scanf("%s", source);
        // Getting destination file1 from user
        char destination[20];
        printf("Enter the destination file: ");
        scanf("%s", destination);
        // Getting max file size
        int max_size;
        printf("Enter the maximum file size: ");
        scanf("%d", &max_size);
        // Getting step size
        int step_size;
        printf("Enter the step size: ");
        scanf("%d", &step_size);

        int current_size = step_size;
        while (current_size <= max_size)
        {
            clock_t start, end;
            double cpu_time_used;
            start = clock();
            // Create a file of current_size = current_size + step_size;
	        FILE *src = fopen(source,"w");
	        char buffer[current_size];
            for(int i = 0; i < sizeof(buffer); i++) {
                buffer[i] = '8'; 
            }
		    fwrite(&buffer, 1, current_size, src);
	        fclose(src);
            // Copy source file to destination file;
            func_copier(source,destination);
            current_size += step_size;

            end = clock();
            cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
            printf("Time: %d", cpu_time_used);
        }
    }
    else
    {
        printf("Invalid option!");
    }

    return 0;
}
