/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Spring 2018                                     */
/*                                                                         */
/* Homework : Wet 2                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main2.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library2.h"
#include <iostream>
using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

/* The command's strings */
typedef enum {
	NONE_CMD = -2,
	COMMENT_CMD = -1,
	INIT_CMD = 0,
	ADDCLAN_CMD = 1,
	ADDPLAYER_CMD = 2,
	CLANFIGHT_CMD = 3,
	GETMINCLAN_CMD = 4,
	QUIT_CMD = 5
} commandType;

static const int numActions = 10;
static const char *commandStr[] = { "init", "addClan", "addPlayer",
		"clanFight", "getMinClan", "quit" };

static const char* ReturnValToStr(int val) {
	switch (val) {
	case SUCCESS:
		return "SUCCESS";
	case ALLOCATION_ERROR:
		return "ALLOCATION_ERROR";
	case FAILURE:
		return "FAILURE";
	case INVALID_INPUT:
		return "INVALID_INPUT";
	default:
		return "";
	}
}

/* we assume maximum string size is not longer than 256  */
#define MAX_STRING_INPUT_SIZE (255)
#define MAX_BUFFER_SIZE       (255)

#define StrCmp(Src1,Src2) ( strncmp((Src1),(Src2),strlen(Src1)) == 0 )

typedef enum {
	error_free, error
} errorType;
static errorType parser(const char* const command);

#define ValidateRead(read_parameters,required_parameters,ErrorString) \
if ( (read_parameters)!=(required_parameters) ) { printf(ErrorString); return error; }

static bool isInit = false;

///***************************************************************************/
///* main                                                                    */
///***************************************************************************/

int main(int argc, const char**argv) {
	char buffer[MAX_STRING_INPUT_SIZE];

	// Reading commands
	while (fgets(buffer, MAX_STRING_INPUT_SIZE, stdin) != NULL) {
		fflush(stdout);
		if (parser(buffer) == error)
			break;
	};
	return 0;
}
//
///***************************************************************************/
///* Command Checker                                                         */
///***************************************************************************/

static commandType CheckCommand(const char* const command,
		const char** const command_arg) {
	if (command == NULL || strlen(command) == 0 || StrCmp("\n", command))
		return (NONE_CMD);
	if (StrCmp("#", command)) {
		if (strlen(command) > 1)
			printf("%s", command);
		return (COMMENT_CMD);
	};
	for (int index = 0; index < numActions; index++) {
		if (StrCmp(commandStr[index], command)) {
			*command_arg = command + strlen(commandStr[index]) + 1;
			return ((commandType) index);
		};
	};
	return (NONE_CMD);
}

///***************************************************************************/
///* Commands Functions                                                      */
///***************************************************************************/

static errorType OnInit(void** DS, const char* const command);
static errorType OnAddClan(void* DS, const char* const command);
static errorType OnAddPlayer(void* DS, const char* const command);
static errorType OnClanFight(void* DS, const char* const command);
static errorType OnGetMinClan(void* DS, const char* const command);
static errorType OnQuit(void** DS, const char* const command);

///***************************************************************************/
///* Parser                                                                  */
///***************************************************************************/

static errorType parser(const char* const command) {
	static void *DS = NULL; /* The general data structure */
	const char* command_args = NULL;
	errorType rtn_val = error;

	commandType command_val = CheckCommand(command, &command_args);

	switch (command_val) {

	case (INIT_CMD):
		rtn_val = OnInit(&DS, command_args);
		break;
	case (ADDCLAN_CMD):
		rtn_val = OnAddClan(DS, command_args);
		break;
	case (ADDPLAYER_CMD):
		rtn_val = OnAddPlayer(DS, command_args);
		break;
	case (CLANFIGHT_CMD):
		rtn_val = OnClanFight(DS, command_args);
		break;
	case (GETMINCLAN_CMD):
		rtn_val = OnGetMinClan(DS, command_args);
		break;
	case (QUIT_CMD):
		rtn_val = OnQuit(&DS, command_args);
		break;

	case (COMMENT_CMD):
		rtn_val = error_free;
		break;
	case (NONE_CMD):
		rtn_val = error;
		break;
	default:
		assert(false);
		break;
	};
	return (rtn_val);
}

int INIT_n;

//
///***************************************************************************/
///* OnInit                                                                  */
///***************************************************************************/
static errorType OnInit(void** DS, const char* const command) {
	if (isInit) {
		printf("init was already called.\n");
		return (error_free);
	};
	isInit = true;

    ValidateRead( sscanf(command, "%d",&INIT_n), 1, "init failed.\n");
    int* clanIDs = new int[INIT_n];
    char c[MAX_STRING_INPUT_SIZE];
    strcpy(c,command);
    char* l = strtok(c ," ");
    for (int i = 0; i < INIT_n; ++i) {
        l = strtok(NULL ," ");
        ValidateRead( sscanf(l, " %d",clanIDs+i), 1, "init failed.\n");
    }


    *DS = init(INIT_n,clanIDs);
    if (*DS == NULL) {
        printf("init failed.\n");
        return (error);
    };
    printf("init done.\n");
    delete [] clanIDs;
    return error_free;
}

///***************************************************************************/
///* OnAddClan                                                             */
///***************************************************************************/
static errorType OnAddClan(void* DS, const char* const command) {
	int clanID;
	ValidateRead(sscanf(command, "%d", &clanID), 1, "addClan failed.\n");
	StatusType res = addClan(DS, clanID);

	if (res != SUCCESS) {
		printf("addClan: %s\n", ReturnValToStr(res));
		return error_free;
	} else {
		printf("addClan: %s\n", ReturnValToStr(res));
	}

	return error_free;
}

///***************************************************************************/
///* OnAddPlayer                                                          */
///***************************************************************************/
static errorType OnAddPlayer(void* DS, const char* const command) {
	int playerID;
	int score;
	int clan;
	ValidateRead(
			sscanf(command, "%d %d %d", &playerID, &score, &clan),
			3, "addPlayer failed.\n");
	StatusType res = addPlayer(DS, playerID, score, clan);

	if (res != SUCCESS) {
		printf("addPlayer: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("addPlayer: %s\n", ReturnValToStr(res));
	return error_free;
}

///***************************************************************************/
///* OnClanFight                                                            */
///***************************************************************************/
static errorType OnClanFight(void* DS, const char* const command) {
	int clan1;
	int clan2;
	int k1;
	int k2;
	ValidateRead(
			sscanf(command, "%d %d %d %d", &clan1, &clan2, &k1, &k2),
			4, "clanFight failed.\n");
	StatusType res = clanFight(DS, clan1, clan2, k1, k2);

	if (res != SUCCESS) {
		printf("clanFight: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("clanFight: %s\n", ReturnValToStr(res));
	return error_free;
}

/***************************************************************************/
/* OnGetMinClan                                                         */
/***************************************************************************/
static errorType OnGetMinClan(void* DS, const char* const command) {
	int clan;
	StatusType res = getMinClan(DS, &clan);

	if (res != SUCCESS) {
		printf("getMinClan: %s\n", ReturnValToStr(res));
		return error_free;
	}

	printf("getMinClan: %s %d\n", ReturnValToStr(res), clan);
	return error_free;
}

/***************************************************************************/
/* OnQuit                                                                  */
/***************************************************************************/
static errorType OnQuit(void** DS, const char* const command) {
	quit(DS);
	if (*DS != NULL) {
		printf("quit failed.\n");
		return error;
	};

	isInit = false;
	printf("quit done.\n");

	return error_free;
}

#ifdef __cplusplus
}
#endif