#include "bsq.h"
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

# define ERROR "ERROR"

/*
 * funcs: fopen/fclose/fwrite/fclose/malloc/calloc/realloc/printf/getline
 * requires: 9.ox <row-size><empty><obstacle><full>
 * conds: size-line is stable. each-line has br. map-not-empty. each-elem is printable. if-error print "Error: invalid map",
 * when-file-not-provided, read from stdin.
*/

typedef struct s_map {
	char **map;
	size_t col_size;
	size_t row_size;
	char empty;
	char obs;
	char full;
} t_map;

void init_map(t_map *map)
{
	map->map = NULL;
	map->col_size = 0;
	map->row_size = 0;
	map->empty = '\0';
	map->obs = '\0';
	map->full = '\0';
}

void free_darray(void ***arr, size_t size)
{
	if (arr==NULL || *arr==NULL || size==0)
		return ;
	while (size-->0){ // on the premise of NULL init arr.
		// printf("free() : %s\n", (char *)**arr);
		if ((*arr)[size]!=NULL)
			free((*arr)[size]);
	}
	free(*arr);
}

void printFirstLine(t_map *map)
{
	printf("row_size: %zu\n", map->row_size);
	printf("empty: %c\nobs: %c\nfull: %c\n", map->empty, map->obs, map->full);
}

void printMapContent(t_map *map)
{
	for (size_t i=0;i<map->row_size;++i){
		printf("line[%zu]\n", i);
		printf("[ ");
		for (size_t j=0;j<map->col_size;++j){
			printf("%c ", map->map[i][j]);
		}
		printf("]\n");
	}
}

bool ft_isdigit(char c)
{
	if ('0'<=c && c<='9'){
		return true;
	}
	return false;
}

bool ft_isprint(char c)
{
	if (' ' <= c && c<='~'){
		return true;
	}
	return false;
}

bool parseFirstLine(FILE *fs, t_map *map)
{
	char *line = NULL;
	size_t linecap = INT_MAX;
	ssize_t read_bytes = getline(&line,&linecap, fs);
	if (read_bytes<=0 || read_bytes<4){
		fwrite(ERROR, sizeof(ERROR), 1, stdout);
		return false;
	}

	// size should be num
	size_t i=0;
	if (ft_isdigit(line[i])) {
		map->row_size = line[i] - '0';
		++i;
	} else {
		fwrite(ERROR, sizeof(ERROR), 1, stdout);
		return false;
	}

	// empty should be printable char
	// 40(sp) - 176(~)
	if (ft_isprint(line[i])) {
		map->empty = line[i];
		++i;
	} else {
		fwrite(ERROR, sizeof(ERROR), 1, stdout);
		return false;
	}

	// obs should be printable char
	// 40(sp) - 176(~)
	if (ft_isprint(line[i])) {
		map->obs = line[i];
		++i;
	} else {
		fwrite(ERROR, sizeof(ERROR), 1, stdout);
		return false;
	}

	// fullshould be printable char
	// 40(sp) - 176(~)
	if (ft_isprint(line[i])) {
		map->full = line[i];
		++i;
	} else {
		fwrite(ERROR, sizeof(ERROR), 1, stdout);
		return false;
	}
	return true;
}

bool parseMapContent(FILE *fs, t_map *map)
{
	char *line = NULL;
	size_t linecap = INT_MAX;

	for (size_t row=0;row<map->row_size;++row){
		// all the map content line has '\n' at the end.
		ssize_t read_bytes = getline(&line,&linecap, fs);
		if (read_bytes<=0){
			fwrite(ERROR, sizeof(ERROR), 1, stdout);
			return false;
		}

		// for the first line, it is the col_size standard
		if (row==0){
			map->col_size = read_bytes-1;
			for (size_t j=0;j<map->row_size;++j){
				map->map[j] = (char *)malloc(sizeof(char)*map->col_size);
				if (map->map==NULL){
					fwrite(ERROR, sizeof(ERROR), 1, stdout);
					return false;
				}
				for (size_t k=0;k<map->col_size;++k){
					map->map[j][k] = '.';
				}
			}
		}

		// mapping from line to map->map[]
		// printf("line[%zu]: \n", row);
		for (size_t l=0;l<map->col_size;++l){
			map->map[row][l] = line[l];
			// printf("mapped char: %c\n", map->map[row][l]);
		}
	}
	return true;
}

typedef struct s_solution {
	int **hash;
	size_t row_size;
	size_t col_size;
	int max_area;
	int max_row;
	int max_col;
} t_solution;

bool init_solution(t_solution *sol, size_t row_size, size_t col_size)
{
	// init hash map
	sol->hash = (int **)malloc(sizeof(int *)*(row_size+1));
	if (sol->hash==NULL){
		fwrite(ERROR, sizeof(ERROR), 1, stdout);
		return false;
	}
	for (size_t i=0;i<row_size+1;++i){
		sol->hash[i] = NULL;
	}
	// init each row
	for (size_t i=0;i<row_size;++i){
		sol->hash[i] = (int *)malloc(sizeof(int)*(col_size+1));
		if (sol->hash[i]==NULL){
			free_darray((void ***)&sol->hash, sol->row_size);
			fwrite(ERROR, sizeof(ERROR), 1, stdout);
			return false;
		}
	}
	sol->row_size = row_size;
	sol->col_size = col_size;
	sol->max_area = -1;
	sol->max_row = -1;
	sol->max_col = -1;
	return true;
}

void printSolutionHash(t_solution *sol)
{
	for (size_t i=0;i<sol->row_size;++i){
		printf("row[%zu]\n", i);
		printf("[ ");
		for (size_t j=0;j<sol->col_size;++j){
			printf("%d ", sol->hash[i][j]);
		}
		printf("]\n");
	}
}

void printMap(t_map *map)
{
	for (size_t i=0;i<map->row_size;++i){
		for (size_t j=0;j<map->col_size;++j){
			printf("%c", map->map[i][j]);
		}
		printf("\n");
	}
}

void printSolvedMap(t_solution *sol, t_map *map)
{
	/*
		. . . . o
		. . . . .
		. . . . o
		. . . (i,j) .
		. . . . .
	*/
	/* virtical : 
		o
		.
		.
		.
		j
	*/
	size_t i = sol->max_row;
	size_t stepi = 0;
	while (stepi<sol->max_area)
	{	
		size_t j = sol->max_col;
		size_t stepj = 0;
		while (stepj<sol->max_area)
		{
			map->map[i][j] = 'x';
			--j;
			++stepj;
		}
		--i;
		++stepi;
	}
	printMap(map);
}

bool solve(t_map *map)
{
	/*
		. . . 
		o . o
		o o o
		
		if obs 
			area[i] = 0;
		else
			area[i] = min(left, up, up-left) + 1;
	*/
	t_solution sol;
	init_solution(&sol, map->row_size, map->col_size);

	// iterate all rows
	// iterate all cols
	for (size_t i=0;i<map->row_size;++i){
		for (size_t j=0;j<map->col_size;++j){
			if (map->map[i][j]==map->obs){
				sol.hash[i][j] = 0;
			} else {
				// if up or left edge, size is 1
				if (i==0 || j==0){
					sol.hash[i][j] = 1;
				} else {
					// int min = INT_MAX;
					int min = INT_MAX;
					// left
					if (min > sol.hash[i][j-1]){
						min = sol.hash[i][j-1];
					}
					// up
					if (min > sol.hash[i-1][j]){
						min = sol.hash[i-1][j];
					}
					// up-left
					if (min > sol.hash[i-1][j-1]){
						min = sol.hash[i-1][j-1];
					}
					sol.hash[i][j] = min + 1;

					// check and refresh max status
					if (sol.max_area<sol.hash[i][j]){
						sol.max_area = sol.hash[i][j];
						sol.max_row = i;
						sol.max_col = j;
					}
				}
			}
		}
	}
	printSolutionHash(&sol);
	printSolvedMap(&sol, map);
	free_darray((void ***)&sol.hash, sol.row_size);
	return true;
}

int main(int argc, char *argv[])
{
	printf("argc: %d\n", argc);
	if (!(argc==1 || argc==2))
		return 1;
	// branches for file and stdin. FILE stream is external var.
	FILE *fs = NULL;
	if (argc==1){
		fs = stdin;
	} else {
		fs = fopen(argv[1], "r");
		if (fs==NULL)
			return 1;
	}

	t_map map;
	init_map(&map);
	// bool parseFirstLine(FILE *fs, t_map *map)
	if (!parseFirstLine(fs, &map)){
		fclose(fs);
		return 1;
	}
	printFirstLine(&map);

	map.map = (char **)malloc((sizeof(char *)*(map.row_size+1)));
	if (map.map==NULL){
		fwrite(ERROR, sizeof(ERROR), 1, stdout);
		fclose(fs);
		return 1;
	}
	for (size_t j=0;j<map.row_size+1;++j){
		map.map[j] = NULL;
	}
	// bool parseMapContent(FILE *fs, t_map *map)
	if (!parseMapContent(fs,&map)){
		free_darray((void ***)&map.map, map.row_size);
		fclose(fs);
		return 1;
	}

	// free_darray((void ***)&map.map, map.row_size);
	// return 1;

	printMapContent(&map);

	// solve the bsq and print with filled by 'x'
	// bool solve(t_map *map);
	if (!solve(&map)){
		free_darray((void ***)&map.map, map.row_size);
		fclose(fs);
		return 1;
	}
	return 0;
}
