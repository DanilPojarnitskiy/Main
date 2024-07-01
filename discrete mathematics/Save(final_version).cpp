#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma warning(disable:4996)

char* read_file(const char* file_name, int* logic_base, int* param_count) {
	FILE* input = fopen(file_name, "r");
	if (input == NULL) {
		return NULL;
	}
	fscanf(input, "%d ", logic_base);
	fscanf(input, "%d ", param_count);
	char* buf_string = (char*)malloc(sizeof(char) * pow(*logic_base, *param_count));
	if (buf_string == NULL) {
		return NULL;
	}
	fscanf(input, "%s ", buf_string);
	fclose(input);

	return buf_string;
}

int* to_base_system(int number, int base, int param_count) {

	int* result = (int*)calloc(param_count, sizeof(int));

	int i = 0, t = 0, temp;
	int* mas = (int*)malloc(sizeof(int) * param_count);
	do {
		mas[i] = number % base;
		number = number / base;
		i++;
		t++;
	} while (number != 0);

	for (i = 0; i < t / 2; i++) {
		temp = mas[i];
		mas[i] = mas[t - i - 1]; //reverse funkciya
		mas[t - i - 1] = temp;
	}


	for (i = 0; i < t; i++) {
		result[param_count - t + i] = mas[i];
	}

	return result;
}


// m - apram_count, n - size, k - sgffdgfdgd
// 1 2 3 
// 4 5 6
// 7 8 9


// 0 1 2 3
// 1 0 0 1
// 0 -1 -1 1
int** make_subsets(int* numbers, int logic_base) {
	int size = pow(2, logic_base);
	int** sets = (int**)malloc(sizeof(int*) * size);

	for (int i = 1; i < size - 1; i++) {
		int* buf = to_base_system(i, 2, logic_base);
		//unsigned int size_of_buf = logic_base;
		//int size_of_buf = sizeof(buf) / sizeof(*buf);
		for (int j = 0; j < logic_base; j++) {
			if (buf[j] != 0) {
				buf[j] = numbers[j];
			}
			else {
				buf[j] = -1;
			}
		}
		sets[i - 1] = buf;
	}
	return sets;
}


int if_only(int* example, int* data, int size_example, int size_data) {
	int count = 0;
	int indicate = -2; //не подошел
	for (int i = 0; i < size_data - 1; i++) {
		for (int j = 0; j < size_example; j++) {
			//printf("%d!,%d!", data[i], example[j]);
			if (data[i] == example[j]) {
				count++;
			}
		}
	}
	if (count == size_data - 1) {
		indicate = -1; //подошел, но не сохранился
	}
	for (int j = 0; j < size_example; j++) {
		if (count == size_data - 1 && data[size_data - 1] == example[j]) {
			indicate = 0; //подошел и сохранился
		}
	}
	return indicate;
}

int* copy(int** arr, int param_count, int j) {
	int* buf = (int*)malloc(sizeof(int) * param_count);
	for (int i = 0; i < param_count; i++) {
		buf[i] = arr[i][j];
		//printf("|%d|", buf[i]);
	}

	return buf;
}

void find_conserved_constants(int*** sets, int** table, int logic_base, int param_count) {
	int s = pow(2, logic_base);
	//sets[s] = (int*)calloc(s, sizeof(int));

	for (int i = 0; i < s - 2; i++) {
		for (int j = 0; j < pow(logic_base, param_count); j++) {
			int* buf = copy(table, param_count + 1, j);
			int res = if_only((*sets)[i], buf, logic_base, param_count + 1);
			if (res == -1) {
				(*sets)[i][logic_base] = -1;
			}
			else if (res == 0 && (*sets)[i][logic_base] != -1) {
				(*sets)[i][logic_base] = 0;
			}

		}
	}

}

int* replace(int* arg, int size, int value1, int value2) {
	for (int i = 0; i < size; i++) {
		if (arg[i] == value1) {
			arg[i] = value2;
		}
	}
	return arg;
}
//1 0
//1 2
int compare(const void* arg1, const void* arg2) {
	return *(int*)arg1 - *(int*)arg2;
}

int compare_strings(int* str1, int* str2, int logic_base) {

	str1 = replace(str1, logic_base, -1, logic_base + 1);
	str2 = replace(str2, logic_base, -1, logic_base + 1);
	qsort(str1, logic_base, sizeof(int), compare);
	qsort(str2, logic_base, sizeof(int), compare);

	for (int i = 0; i < logic_base; i++) {
		if (str1[i] > str2[i] && str1[i] != logic_base + 1 && str2[i] != logic_base + 1) {
			return 1;
		}
	}
	return -1;
}



int** sort(int** sets, int logic_base) {

	int temp = pow(2, logic_base);

	for (int i = 0; i < temp - 2; i++) {
		for (int j = 0; j < temp - 3; j++) {
			if (compare_strings(sets[j], sets[j + 1], logic_base) > 0) {
				int* b = sets[j];
				sets[j] = sets[j + 1]; // меняем местами
				sets[j + 1] = b; // значения элементов
			}
		}
	}

	return sets;
}

void print_file(const char* filename, int** sets, int logic_base) {
	FILE* output = fopen(filename, "w");
	int s = pow(2, logic_base);

	sets = sort(sets, logic_base);

	for (int i = 0; i < s - 2; i++) {
		sets[i] = replace(sets[i], logic_base, logic_base + 1, -1);
		for (int j = 0; j < logic_base; j++) {
			if (sets[i][logic_base] == 0) {
				if (sets[i][j] >= 0) {
					fprintf(output, "%d", sets[i][j]);
				}
				if (j == logic_base - 1 && i != s - 3) {
					fprintf(output, "\n");
				}
			}
		}
	}

}

int** make_sets(int param_count, int logic_base) {

	int* numbers = (int*)malloc(sizeof(int) * logic_base);

	for (int i = 0; i < logic_base; i++) {
		numbers[i] = i;
	}

	int** sets = make_subsets(numbers, logic_base);

	for (int i = 0; i < pow(2, logic_base) - 2; i++) {
		for (int j = 0; j < logic_base; j++) {
			printf("%d ", sets[i][j]);
		}
		printf("\n");
	}

	return sets;
}


int** get_polynom_coefficients(int logic_base, int param_count, char* values_string) {

	int** polynom_coefficients = (int**)malloc(sizeof(int*) * (param_count + 1));


	int size = pow(logic_base, param_count);
	for (int i = 0; i < param_count; i++) {
		(polynom_coefficients)[i] = (int*)calloc(size, sizeof(int));
		for (int j = 0; j < size; j++) {
			int* buf = to_base_system(j, logic_base, param_count);
			(polynom_coefficients)[i][j] = buf[i];
		}
	}
	(polynom_coefficients)[param_count] = (int*)calloc(size, sizeof(int));
	for (int k = 0; k < size; k++) {
		if ((int)values_string[k] > 64) {
			(polynom_coefficients)[param_count][k] = values_string[k] - 55;
		}
		else {
			(polynom_coefficients)[param_count][k] = values_string[k] - 48;
		}
	}

	return polynom_coefficients;
}

int main(int argc, char const* argv[]) {
	int logic_base, param_count;
	char* values_string = read_file("input.txt", &logic_base, &param_count);
	int size = pow(logic_base, param_count);
	int** polynom_coefficients = get_polynom_coefficients(logic_base, param_count, values_string);
	int** sets = make_sets(param_count, logic_base);
	find_conserved_constants(&sets, polynom_coefficients, logic_base, param_count);
	print_file("output.txt", sets, logic_base);


	for (int i = 0; i < param_count + 1; i++) {
		free(polynom_coefficients[i]);
	}

	free(polynom_coefficients);

	return 0;
}