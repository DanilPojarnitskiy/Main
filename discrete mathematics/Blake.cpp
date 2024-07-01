#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//0 0 0 | 0 |
//0 0 1 | 0 |
//0 1 0 | 1 |
//0 1 1 | 1 |
//1 0 0 | 0 | 
//1 0 1 | 0 |
//1 1 0 | 1 |
//1 1 1 | 1 |
// F = !x1 * x2 * !x3 + !x1 * x2 * x3 + x1 * x2 * !x3 + x1 * x2 * x3 = x2
//f=x1x2+!x1x2+!x2x3 -> x1x2+!x1x3
#pragma warning(disable:4996)

char** read_file(const char* file_name, int* dis_count, int* param_count) {
	FILE* input = fopen(file_name, "r");
	if (input == NULL) {
		return NULL;
	}
	fscanf(input, "%d ", param_count);
	fscanf(input, "%d ", dis_count);
	char** buf_string = (char**)malloc(sizeof(char*) * *dis_count);
	if (buf_string == NULL) {
		return NULL;
	}
	for (int i = 0; i < *dis_count; i++) {
		buf_string[i] = (char*)malloc(sizeof(char) * *param_count);
		fscanf(input, "%s", buf_string[i]);
	}
	fclose(input);
	return buf_string;
}

void absorption(char* vec_1, char* vec_2, int param_count) {
	int orthogonal_count = 0;
	int orthogonal_ind = 0;
	int equal = 0;
	// ���� ��������� �������
	if ((int)vec_1[0] == 33 || (int)vec_2[0] == 33) {
		return;
	}
	else
	{
		for (int i = 0; i < param_count; i++)
		{
			// ���� ���������������
			if (abs((int)vec_2[i] - (int)vec_1[i]) == 1) {
				orthogonal_ind = i;
				orthogonal_count++;
			}
			// ���� ���������
			if ((int)vec_2[i] == (int)vec_1[i]) {
				equal++;
			}
			// ���� ������ ����: ��������� �� ������ 1011 ������ 1-11
			if (abs((int)vec_2[i] - (int)vec_1[i]) > 2) {
				orthogonal_ind = i;
				orthogonal_count++;
			}
		}
		if (orthogonal_count == 1) {
			vec_1[0] = 33;
			vec_2[orthogonal_ind] = 42;
		}
		else {
			if (equal == param_count) {
				vec_1[0] = 33;
				return;
			}
		}
	}
}

int compare(const void* arg1, const void* arg2) {
	return *(int*)arg1 - *(int*)arg2;
}

int compare_strings(char* str1, char* str2, int param_count) {

	for (int i = 0; i < param_count; i++) {
		if (str1[i] > str2[i] || (str1[i] == '*' && str2[i] != '*')) {
			return 1;
		}
	}
	return -1;
}



char** sort(char** sets, int dis_count, int param_count) {

	for (int i = 0; i < dis_count; i++) {
		for (int j = 0; j < dis_count - 1; j++) {
			if (compare_strings(sets[j], sets[j + 1], param_count) > 0) {
				char* b = sets[j];
				sets[j] = sets[j + 1]; // ������ �������
				sets[j + 1] = b; // �������� ���������
			}
		}
	}

	return sets;
}

char** dnf_processing(char** matrix, int dis_count, int param_count) {

	for (int i = 0; i < dis_count; i++) {
		for (int j = 0; j < dis_count; j++) {
			if (i != j) {
				absorption(matrix[i], matrix[j], param_count);
			}
		}
	}
	matrix = sort(matrix, dis_count, param_count);
	return matrix;
}

bool Printff(const char* file_name, char** matrix, int dis_count, int param_count) {
	FILE* out = fopen(file_name, "w");
	if (out == NULL) {
		return false;
	}
	int count = 0;
	for (int k = 0; k < dis_count; k++) {
		if (matrix[k][0] != 33) {
			count++;
		}
	}
	fprintf(out, "%d %d\n", param_count, count);
	if (count == 0) {
		return false;
	}
	for (int i = 0; i < dis_count; i++) {
		if (matrix[i][0] == 33) {
			continue;
		}
		for (int j = 0; j < param_count; j++) {
			fprintf(out, "%c", matrix[i][j]);
		}
		fprintf(out, "\n");
	}
	fclose(out);
	return true;
}

int main() {
	int dis_count, param_count;
	char** matrix;
	matrix = read_file("input.txt", &dis_count, &param_count);
	if (matrix == NULL) {
		return -1;
	}
	matrix = dnf_processing(matrix, dis_count, param_count);
	if (!Printff("output.txt", matrix, dis_count, param_count)) {
		return -1;
	}
	return 0;
}