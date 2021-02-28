#ifndef __DEBUG_INCLUDE_H
#define __DEBUG_INCLUDE_H
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*                          contexte de compile time                                */
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/**
 * Simplement commenter les #define que lon ne veut pas compiler
 */

#define __DEBUG						// active les main de debug
#ifdef  __DEBUG
	#define __DEBUG_PHASE_1			// active le main de debug de la phase 1
	#define __DEBUG_PARSER_H		// active le main de debug du parser.h
	#define __DEBUG_INTERFACE_H		// active le main de debug de interface.h
//    #define __INTERFACE_H_DEBUG_LECTURE
    #define __INTERFACE_H_DEBUG_RESULTAT
//    #define __DEBUG_HASHMAP
#endif
#endif