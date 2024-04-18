/*
 * Copyright 2020 Matthias Brun <matthias.brun@eseo.fr>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file alambix.h
 *
 * @brief Alambix API to develop a multi-thread Alambix.
 *
 * See the modules documentation for more details.
 *
 * @version 0.1
 *
 * @author Matthias Brun (matthias.brun@eseo.fr)
 */

#ifndef ALAMBIX_H_
#define ALAMBIX_H_

#ifndef DOXYGEN
#include <pthread.h>
#endif

/**
 * @defgroup alambix_makefile The Alambix Makefile
 *
 * @brief
 * The Alambix must be compiled using a specific Makefile.
 *
 * The following Makefile gives an example of this kind of specific Makefile.
 *
 * <ul>
 * <li>The <tt>/path/to/alambix/library</tt> (<tt>ALAMBIX_DIR</tt>) gives the path where the Alambix library has been deployed on the computer.
 * It <b>must</b> be changed to match where Alambix is installed on your computer.</li>
 * <li>The <tt>ALAMBIX_UI</tt> specifies the Alambix interface to use (only the <tt>original</tt> version is currently available).</li>
 * <li>The <tt>ALAMBIX_PATH</tt> aims at providing the path to the Alambix library with all space characters escaped.</li>
 * <li>The main purpose is to include the Makefile <tt>\$(ALAMBIX_PATH)/make/Alambix.mk</tt> provided by the Alambix library.</li>
 * </ul>
 *
 * Notice: Only the <tt>gcc</tt> compiler is currently supported to compile the Alambix.
 *
 * @code{.mk}
 * #
 * # Alambix user Makefile
 * #
 *
 * # Alambix install directory
 * ALAMBIX_DIR := $(realpath /path/to/alambix/library)
 *
 * # Alambix user interface
 * ALAMBIX_UI := original
 *
 * # Program name
 * PROG := alambix
 *
 * # Compiler to use
 * CC := gcc
 *
 * # Source files
 * SRC := main.c
 *
 * # File remove tool
 * RM := rm -f
 *
 * #
 * # Generic part of the Makefile
 * #
 * OBJ := $(SRC:.c=.o)
 *
 * # Alambix specific Makefile
 * null :=#
 * esc_space = $(subst $(null) $(null),\ ,$1)
 * ALAMBIX_PATH := $(call esc_space,$(ALAMBIX_DIR))
 * -include $(ALAMBIX_PATH)/make/Alambix.mk
 *
 * # Makefile rules
 * .PHONY: all clean
 *
 * all: $(PROG)
 *
 * .c.o:
 * 	$(CC) -c $(CCFLAGS) $< -o $@
 *
 * $(PROG): $(OBJ)
 * 	$(CC) $(OBJ) -o $(PROG) $(LDFLAGS)
 *
 * clean:
 * 	$(RM) $(PROG) *.o core
 *
 * @endcode
 *
 */

/**
 * @defgroup alambix The Alambix API
 *
 * @brief
 * The Alambix API provides functions and variables making it possible for you to program the Alambix:
 *
 * See the modules documentation for more details.
 */


// defgroup alambix_open_close
/**
 * @defgroup alambix_open_close Open/Close the Alambix
 * @ingroup alambix
 *
 * @brief
 * Functions to open and to close the Alambix.
 *
 * In order to program the Alambix you must have a main source code similar to the following:
 *
 * @code
 *  //
 *  // \file main.c
 *  //
 *  // \brief Source code example for Alambix programming.
 *  //
 *
 *  #include "alambix.h"
 *
 *	void alambix_init()
 *	{
 *		// TODO: Insert initialization code here.
 *	}
 *
 *	int main(int argc, char * argv[])
 *	{
 *		alambix_open();
 *
 *		// TODO: Insert cleanup code here.
 *
 *		return alambix_close();
 *	}
 *
 * @endcode
 *
 * See the \ref alambix_makefile module for details on compilation.
 *
 * @{
 */
/**
 * @fn void alambix_init()
 *
 * @brief Alambix init function used to initialize programming artifacts (must be implemented by the programmer).
 */
#ifndef DOXYGEN
__attribute__((weak))
#endif
void alambix_init();

#ifndef DOXYGEN
#define xstr(s) str(s)
#define str(s) #s
#define alambix_open() _alambix_open(xstr(ALAMBIXUI))

void _alambix_open(const char * ui);
#else
/**
 * @fn void alambix_open()
 *
 * @brief Open the Alambix User Interface.
 *
 * This function <b>must</b> be called by the main thread.
 *
 */
void alambix_open();
#endif
/**
 * @fn int alambix_close()
 *
 * @brief Close the Alambix program.
 *
 * This function <b>must</b> be called by the main thread.
 *
 * @return 0 if success, an error code otherwise.
 */
int alambix_close();

/** @} */
// end of alambix_open_close group


// defgroup alambix_help
/**
 * @defgroup alambix_help Help on Alambix
 * @ingroup alambix
 *
 * @brief
 * Functions to obtain instructions to program the Alambix.
 *
 * In order to obtain the full documentation, i.e. the help on the instructions to program the Alambix, you have to develop an #alambix_help function like this:
 *
 * @code
 *	void alambix_help()
 *	{
 *		// TODO: Insert here the code to launch the Alambix help documentation in a browser.
 *	}
 * @endcode
 *
 * This help function corresponds to the "Help" button entry-point in the Alambix graphical interface.<br />
 * This function aims at opening the Alambix help page in a browser (e.g. firefox).
 *
 * Note that a thread may be used to launch the help (if needed): #alambix_help_thread
 *
 * @{
 */

/**
 * @fn void alambix_help()
 *
 * @brief Alambix User Interface Help button entry-point (must be implemented by the programmer).
 *
 */
#ifndef DOXYGEN
__attribute__((weak))
#endif
void alambix_help();

 /**
  * @fn char * alambix_help_html()
  *
  * @brief Get the help index (in HTML format).
  *
  * @return the absolute path to the index.html of the Alambix instructions documentation.
  *
  */
char * alambix_help_html();

/** @} */
// end of alambix_help group


// defgroup alambix_start
/**
 * @defgroup alambix_start Start the Alambix
 * @ingroup alambix
 *
 * @brief
 * Functions to start your threads.
 *
 * In order to start your programming threads you have to develop an #alambix_start function like this:
 *
 * @code
 *	void alambix_start()
 *	{
 *		// TODO: Insert thread startup code here.
 *	}
 * @endcode
 *
 * This start function corresponds to the "Start" button entry-point in the Alambix graphical interface.<br />
 * This function aims at creating and launching your programming threads.
 *
 * The Alambix expected threads are mentioned in: \ref alambix_pthread module documentation.
 *
 * @{
 */

/**
 * @fn void alambix_start()
 *
 * @brief Alambix User Interface Start button entry-point (must be implemented by the programmer).
 */
#ifndef DOXYGEN
__attribute__((weak))
#endif
void alambix_start();

/** @} */
// end of alambix_start group


// defgroup alambix_order_drinks
/**
 * @defgroup alambix_order_drinks Order drinks in Alambix
 * @ingroup alambix
 *
 * @brief
 * Functions to place an order.
 *
 * In order to place an order, a client may follow an algorithm like the following:
 *
 * @code
 *  // order all the client's chosen drinks
 *
 *  char * drink;
 *
 *  while ((drink = alambix_choose_drink()) != NULL)
 *  {
 *      alambix_order_drink(drink);
 *  }
 *
 * @endcode
 *
 * @{
 */

/**
 * @fn void alambix_choose_drink()
 *
 * @brief Choose a drink.
 *
 * Get a drink chosen by an Alambix client (that will be ordered later).<br/>
 * This function <b>must</b> be called by an Alambix client thread (either #alambix_client0_thread or #alambix_client1_thread).
 *
 * @return The next drink that has been chosen by the client, null at the end of the chosen drinks set.
 */
char * alambix_choose_drink();

/**
 * @fn void alambix_order_drink(char * drink)
 *
 * @brief Order a drink.
 *
 * An Alambix client places an order of a drink.<br/>
 * This function <b>must</b> be called by an Alambix client thread (either #alambix_client0_thread or #alambix_client1_thread).
 *
 * @param drink the drink to order.
 */
void alambix_order_drink(char * drink);

/** @} */
// end of alambix_order_drinks group


// defgroup alambix_take_order
/**
 * @defgroup alambix_take_order Take an order in Alambix
 * @ingroup alambix
 *
 * @brief
 * Function to take an order.
 *
 * @{
 */

/**
 * @fn void alambix_take_order()
 *
 * @brief Take an order.
 *
 * Take the drink order placed by the clients.<br/>
 * This function <b>must</b> be called by an Alambix waiter thread (#alambix_waiter_thread).
 */
void alambix_take_order();

/** @} */
// end of alambix_take_order group

// defgroup alambix_transmit_order
/**
 * @defgroup alambix_transmit_order Transmit an order in Alambix
 * @ingroup alambix
 *
 * @brief
 * Macros and functions to transmit an order to the bartender.
 *
 * Transmission of the order to the bartender is based on a POSIX message queue (@ref ALAMBIX_BARTENDER_MQ).
 *
 * In order to transmit an order, the waiter may follow an algorithm like the following:
 *
 * @code
 *  // transmit the order to the bartender
 *
 *  char * ordered_drink;
 *
 *  while ((ordered_drink = alambix_get_ordered_drink()) != NULL)
 *  {
 *      // send the ordered drink using the bartender message queue
 *  }
 *
 * @endcode
 *
 * In order to receive an order from the waiter, the bartender may follow an algorithm like the following:
 *
 * @code
 *  // receive the order from the waiter
 *
 *  do
 *  {
 *  	// receive the drink order using the bartender message queue
 *  }
 *  while (alambix_has_ordered_drink());
 *
 * @endcode
 *
 * @{
 */

/**
 * @def ALAMBIX_BARTENDER_MQ
 *
 * @brief The name of the Alambix bartender message queue.
 *
 * This name <b>must</b> be used to open the bartender message queue.
 */
#define ALAMBIX_BARTENDER_MQ "/alambix_bartender_mq"

/**
 * @fn void alambix_get_ordered_drink()
 *
 * @brief Get the next ordered drink.
 *
 * Get the next drink ordered by an Alambix client.<br/>
 * This function <b>must</b> be called by an Alambix waiter thread (#alambix_waiter_thread) after the waiter has taken the order.
 *
 * @return The next drink that has been ordered by the client, null at the end of the ordered drinks set.
 */
char * alambix_get_ordered_drink();

/**
 * @fn int alambix_has_ordered_drink()
 *
 * @brief Say if there is another drink to order (to the bartender).
 *
 * This function <b>must</b> be called by an Alambix bartender thread (#alambix_bartender_thread).
 *
 * @return 1 if there is another drink to order to the bartender, 0 otherwise.
 */
int alambix_has_ordered_drink();

/** @} */
// end of alambix_transmit_order group

// defgroup alambix_prepare_order
/**
 * @defgroup alambix_prepare_order Prepare an order in Alambix
 * @ingroup alambix
 *
 * @brief
 * Functions to prepare an order.
 *
 * In order to prepare an order, the bartender may follow an algorithm like this:
 *
 * @code
 *  // prepare an order
 *
 *  char * drink_to_prepare;
 *
 *  alambix_still_start(drink_to_prepare);
 *  // launch a timer to stop the still after 2s
 *
 * @endcode
 *
 * We can notice that the still must be stopped after 2 seconds, using a timer and the function #alambix_still_stop.
 *
 * @{
 */

/**
 * @fn void alambix_still_start(char * drink)
 *
 * @brief Start the still to make the drink.
 *
 * This function <b>must</b> be called by an Alambix bartender thread (#alambix_bartender_thread).
 *
 * Notice: if the still is already started, this function blocks until the still has been stopped.
 *
 * @param drink the drink to make
 */
void alambix_still_start(char * drink);

/**
 * @fn void alambix_still_stop()
 *
 * @brief Stop the still that makes a drink.
 *
 * This function <b>must</b> be called by either a timer thread or an Alambix bartender thread (#alambix_bartender_thread).
 */
void alambix_still_stop();


/** @} */
// end of alambix_prepare_order group

// defgroup alambix_serve_order
/**
 * @defgroup alambix_serve_order Serve an order in Alambix
 * @ingroup alambix
 *
 * @brief
 * Functions to serve an order.
 *
 * @{
 */

/**
 * @fn void alambix_provide_order()
 *
 * @brief Provide the order (to be served by the waiter)
 *
 * This function <b>must</b> be called by an Alambix bartender thread (#alambix_bartender_thread).
 */
void alambix_provide_order();

/**
 * @fn void alambix_serve_order()
 *
 * @brief Serve the order
 *
 * This function <b>must</b> be called by an Alambix waiter thread (#alambix_waiter_thread).
 */
void alambix_serve_order();

/** @} */
// end of alambix_serve_order group

// defgroup alambix_pthread
/**
 * @defgroup alambix_pthread The Alambix pthreads
 * @ingroup alambix
 *
 * @brief
 * Variables to program threads.
 *
 * Alambix provides several threads (more precisely pthreads) that may or must be used in the program.<br />
 * Any other pthread use will be refused and will lead to an Alambix error.
 *
 * Notice: some Alambix pthreads can only be created once. Many creations of these kinds of Alambix pthreads at the same time lead to an Alambix error.
 *
 * @{
 */

/**
 * \var pthread_t alambix_help_thread
 *
 * \brief A thread that may be used to display the help (weak symbol that can be overridden).
 */
#ifndef DOXYGEN
__attribute__((weak))
#endif
extern pthread_t alambix_help_thread;

/**
 * \var pthread_t alambix_client0_thread
 *
 * \brief A thread that <b>must</b> be used to animate the first client (weak symbol that can be overridden). Can be created <b>only once</b>.
 */
#ifndef DOXYGEN
__attribute__((weak))
#endif
extern pthread_t alambix_client0_thread;

/**
 * \var pthread_t alambix_client1_thread
 *
 * \brief A thread that <b>must</b> be used to animate the second client (weak symbol that can be overridden). Can be created <b>only once</b>.
 */
#ifndef DOXYGEN
__attribute__((weak))
#endif
extern pthread_t alambix_client1_thread;

/**
 * \var pthread_t alambix_waiter_thread
 *
 * \brief A thread that <b>must</b> be used to animate the waiter (weak symbol that can be overridden). Can be created <b>only once</b>.
 */
#ifndef DOXYGEN
__attribute__((weak))
#endif
extern pthread_t alambix_waiter_thread;

/**
 * \var pthread_t alambix_bartender_thread
 *
 * \brief A thread that <b>must</b> be used to animate the bartender (weak symbol that can be overridden). Can be created <b>only once</b>.
 */
#ifndef DOXYGEN
__attribute__((weak))
#endif
extern pthread_t alambix_bartender_thread;

/** @} */
// end of alambix_pthread group


/**
 * @defgroup alambix_restrictions The Alambix restrictions
 * @ingroup alambix
 *
 * @brief
 * Forbidden programming usages
 *
 * <p>
 * Unfortunately in the Alambix it is <b>not allowed to sleep</b> (<tt>man 3 sleep</tt>), even for a microsleep (<tt>man 3 usleep</tt>) or a nanosleep (<tt>man 2 nanosleep</tt>).
 * </p>
 *
 * <p>
 * The Alambix <b>cannot execute another program in the main process</b> using an <tt>exec</tt> system call (<tt>man 3 execv</tt>, <tt>man 3 execvp</tt>, <tt>man 3 execvpe</tt>, <tt>man 2 execve</tt>).
 * In order to execute another program from the Alambix, the Alambix must be forked (<tt>man 2 fork</tt>).
 * </p>
 */

#endif /* ALAMBIX_H_ */
