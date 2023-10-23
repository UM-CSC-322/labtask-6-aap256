//=============================================================================
#include <stdio.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------
double* input_matrix(int *m_rows, int *m_columns, char *name) {
	
        double *matrix, *row_ptr, *col_ptr;
	
	printf("input number of rows in %s : ", name);
	scanf("%d", m_rows);
	printf("input number of columns in %s : ", name);
	scanf("%d", m_columns);
	
	if ((matrix = (double*) calloc((*m_rows), (*m_columns) * 
				sizeof(double))) == NULL) {
		perror("Cannot calloc");
		exit(EXIT_FAILURE);
	} else {
		row_ptr = (double*) calloc(*m_columns, sizeof(double));
		
		for (int row = 0; row < *m_rows; row++) {

			matrix[(row * (*m_columns))] = *row_ptr;
			
			printf("insert elements for row %d separated by spaces : ", 
				row);	
			for (int col = 0; col < (*m_columns - 1); ++col) {
				
				if ((col_ptr = malloc(sizeof(double))) == NULL) {
					perror("Cannot malloc");
					exit(EXIT_FAILURE);
				} else {
					scanf("%lf ", col_ptr);
					row_ptr[col] = *col_ptr;
				}
			}
			if ((col_ptr = malloc(sizeof(double))) == NULL) {
				perror("Cannot malloc");
				exit(EXIT_FAILURE);
			} else {
				scanf("%lf", col_ptr);
				row_ptr[row * (*m_columns - 1)] = *col_ptr;
			}
		}
    		printf("\n");
		
		return matrix;
	}
}
//-----------------------------------------------------------------------------
void output_matrix(double *m, int m_rows, int m_columns) {
	
	for (int row = 0; row < m_rows; ++row) {
		for (int col = 0; col < m_columns; col++)
			printf("%.1lf ", *(m + row + col));
		printf("\n");
	}
}
//-----------------------------------------------------------------------------
int matrix_multiply(double *m1, int m1_rows, int m1_columns, double *m2,
		int m2_rows, int m2_columns, double *m3) {
	
	if (m1_columns != m2_rows) {
		return 0;
	}
	
	int m3_rows = m1_rows, m3_columns = m2_columns;
	
	for (int m3_row = 0; m3_row < m3_rows; m3_row++) {
		
		for (int m3_column = 0; m3_column < m3_columns; m3_column++) {
			
			double sum = 0;
			
			for (int m3_slot = 0; m3_slot < m1_columns; 
					m3_slot++) {
				sum += (*(m1 + m3_row * m3_columns + 
						m3_slot)) * (*(m2 + m3_column 
						* m3_columns + m3_column));		
			}
			
			*(m3 + m3_row * m3_columns + m3_column) = sum;
		}
	}

	return 1;
}
//-----------------------------------------------------------------------------
int main(void) {
	
    	double *m1,*m2,*m3;
    	int m1_rows,m1_columns,m2_rows,m2_columns;
	
	if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
		((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
		((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
	        printf("Matrix 1\n");
        	output_matrix(m1,m1_rows,m1_columns);
        	printf("Matrix 2\n");
        	output_matrix(m2,m2_rows,m2_columns);
        	if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
            		printf("Product\n");
            		output_matrix(m3,m1_rows,m2_columns);
            		free(m1);
            		free(m2);
            		free(m3);
            		return(0);
        	} else {
        		printf("Error in dimensions\n");
            		free(m1);
            		free(m2);
            		free(m3);
            		return(-1);
    		}
	} else {
        	free(m1);
        	free(m2);
        	free(m3);
        	printf("Error allocating memory\n");
        	return(-2);
    	}
}
//=============================================================================
