/*
******************************************************************************
Project:      OWA EPANET
Module:       extensions.h
Description:  discovery, loading and per-project dispatch of dynamically-loaded
              EPANET extensions (sidecar shared libraries implementing the
              ENEXT_ ABI, see include/enext.h)
******************************************************************************
*/
#ifndef EXTENSIONS_H
#define EXTENSIONS_H

#include "epanet2_2.h"   /* EN_Project */

/* On first use these discover and load the extension libraries once for the
** process, then allocate this project's per-extension data slots and dispatch
** the matching optional callback to every loaded extension. Each returns a
** latched EPANET error code (0 on success, worst fatal >100 preserved) and is
** safe to call with a NULL project. */
int extensions_open(EN_Project pr, const char *inpFile);   /* dispatch ENEXT_open  */
int extensions_init(EN_Project pr);                        /* dispatch ENEXT_init  */
int extensions_run(EN_Project pr);                         /* dispatch ENEXT_run   */
int extensions_next(EN_Project pr);                        /* dispatch ENEXT_next  */
int extensions_close(EN_Project pr);                       /* dispatch ENEXT_close */

/* Releases this project's per-extension slots. Dispatches ENEXT_close first (so
** extensions can tear down per-project state even when EN_closeH was not
** called); ENEXT_close must therefore tolerate being invoked more than once.
** Accepts NULL and is safe to call repeatedly. */
void extensions_free(EN_Project pr);

#endif
