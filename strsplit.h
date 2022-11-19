/**
 * File              : strsplit.h
 * Author            : Igor V. Sementsov <ig.kuzm@gmail.com>
 * Date              : 21.02.2022
 * Last Modified Date: 19.11.2022
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

// split string with delims, fill NULL-terminated array of tokens and return array's size
static int strsplit (const char *str, const char *delim, char ***tokens);

// split string with delims and return string at index. set index to -1 to return last
static char * strisplit(const char *str, const char *delim, int index);

// return allocated string with contents of str from position pos and lendth len 
static char * strsubstr(const char *str, int pos, int len);

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

char * 
strisplit (
		const char *str, 
		const char *delim, 
		int index
		)
{
	// pointer to string
	char * ptr = (char *)str;

	//pointer to return string
	char * substr = NULL;

	int i = 0; //counter
	// Extract the first token
	char *token = strtok(ptr, delim);
	// loop through the string to extract all other tokens
	while( token != NULL ) {
		if (i == index){
			// allocate string
			substr = malloc(strlen(token) + 1);
			// copy string
			strcpy(substr, token);
			return substr; 
		}
		token = strtok(NULL, delim);
		i++;
	}

	if (i == -1){
		// allocate string
		substr = malloc(strlen(token) + 1);
		// copy string
		strcpy(substr, token);
		return substr;		
	}

	return NULL;
}

char * 
strsubstr(const char *str, int pos, int len){
	char *substr = malloc(len+1);
	if (!substr)
		return NULL;
	
	memcpy(substr, &str[pos], len);
	substr[len] = '\0';

	return substr;
}
#ifdef __cplusplus
}
#endif

#endif //k_lib_strsplit_h__
