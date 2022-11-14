/**
 * File              : strsplit.h
 * Author            : Igor V. Sementsov <ig.kuzm@gmail.com>
 * Date              : 21.02.2022
 * Last Modified Date: 22.10.2022
 * Last Modified By  : Igor V. Sementsov <ig.kuzm@gmail.com>
 */

/* Usage:  
 *
 */


#ifndef k_lib_strsplit_h__
#define k_lib_strsplit_h__

#ifdef __cplusplus
extern "C"{
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// split string with delims, allocate NULL-terminated array of tokens and return array's size
static int strsplit (const char *str, const char *delim, char ***tokens);


/*
 *
 */

int 
strsplit (
		const char *str, 
		const char *delim, 
		char ***tokens
		)
{
	// pointer to string
	char * ptr = (char *)str;

	// alloc array of strings (pointers)
	char **arr = malloc(sizeof(ptr));
	if (!arr)
		return -1;			

	int i = 0; //counter
	// Extract the first token
	char *token = strtok(ptr, delim);
	// loop through the string to extract all other tokens
	while( token != NULL ) {
		arr[i++] = token;
		token = strtok(NULL, delim);
		//realloc array
		arr = realloc(arr, i*sizeof(token) + sizeof(token));
		if (!arr)
			return -1;			
	}

	//NULL terminate array
	arr[i] = NULL;

	// set tokens pointer
	if (tokens)
		*tokens = arr;
	else
		free(arr); // free array

	return i;
}

#ifdef __cplusplus
}
#endif

#endif //k_lib_strsplit_h__
