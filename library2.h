/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 2                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library2.h                                                   */
/*                                                                          */
/****************************************************************************/

#ifndef _234218_WET2_
#define _234218_WET2_

#ifdef __cplusplus
extern "C" {
#endif

	/* Return Values
	* ----------------------------------- */
	typedef enum {
		SUCCESS = 0,
		FAILURE = -1,
		ALLOCATION_ERROR = -2,
		INVALID_INPUT = -3
	} StatusType;

	/* Required Interface for the Data Structure
	* -----------------------------------------*/

	void* init(int n, int *clanIDs);

	StatusType addClan(void *DS, int clanID);

	StatusType addPlayer(void *DS, int playerID, int score, int clan);

	StatusType clanFight(void *DS, int clan1, int clan2, int k1, int k2);

	StatusType getMinClan(void *DS, int *clan);

	/* Description:   Quits and deletes the database.
	*                DS should be set to NULL.
	* Input:         DS - A pointer to the data structure.
	* Output:        None.
	* Return Values: None.
	*/
	void quit(void** DS);

#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET2_ */