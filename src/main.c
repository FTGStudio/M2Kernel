/*
 ============================================================================
 Name        : main.c
 Author      : Michael
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C
 ============================================================================
 */

#include <stdio.h>

/*
 *
 * Print a greeting message on standard output and exit.
 *
 * On embedded platforms this might require semi-hosting or similar.
 *
 * For example, for toolchains derived from GNU Tools for Embedded,
 * to enable semi-hosting, the following was added to the linker:
 *
 * --specs=rdimon.specs -Wl,--start-group -lgcc -lc -lc -lm -lrdimon -Wl,--end-group
 *
 * Adjust it for other toolchains.
 *
 */

void unpriv_to_priv() __attribute__((naked));
void priv_to_unpriv() __attribute__((naked));

int
main(void)
{
  printf("" "\n");
  return 0;
}

/*
 * void unpriv_to_priv()
 *
 * This is a naked function to switch between unpriveleged to
 * priveleged for a thread
 *
 */
void unpriv_to_priv()
{
	asm volatile("MRS R3, CONTROL\n"
	             "AND R3, R3, #0\n"
	             "MSR CONTROL, R3\n"
	             "ISB\n"
				 "BX LR");
}

/*
 * void priv_to_unpriv()
 *
 * This is a naked function to switch between priveleged to
 * unpriveleged for a thread
 *
 */
void priv_to_unpriv()
{
	asm volatile("MRS R3, CONTROL\n"
			   	 "ORR R3, R3, #1\n"
	             "MSR CONTROL, R3\n"
	             "ISB\n"
	             "BX LR");

}
