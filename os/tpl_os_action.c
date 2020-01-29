/**
 * @file tpl_os_action.h
 *
 * @section desc File description
 *
 * Trampoline Action implementation. Actions are used for alarm action. They
 * are also used by COM for actions.
 *
 * @section copyright Copyright
 *
 * Trampoline RTOS
 *
 * Trampoline is copyright (c) CNRS, University of Nantes, Ecole Centrale de Nantes
 * Trampoline is protected by the French intellectual property law.
 *
 * This software is distributed under the GNU Public Licence V2.
 * Check the LICENSE file in the root directory of Trampoline
 *
 * @section infos File informations
 *
 * $Date$
 * $Rev$
 * $Author$
 * $URL$
 */

#include "tpl_os_definitions.h"
#include "tpl_os_task_kernel.h"
#include "tpl_os_event_kernel.h"
#include "tpl_os_action.h"
#include "tpl_os_error.h"
#include "tpl_os_errorhook.h"

#if (LEVEL_KERNEL_MONITORING >= 4) /* whith kernel monitoring */
#include "../machines/cortex/tpl_fabric_definitions.h"
#endif

#define OS_START_SEC_CODE
#include "tpl_memmap.h"

/**
 *  action function for action call back
 */
FUNC(void, OS_CODE) tpl_action_callback(
  P2CONST(tpl_action, AUTOMATIC, OS_APPL_CONST) _action)
{
  #ifdef VOLATILE_ARGS_AND_LOCALS
    static volatile P2CONST(tpl_action, AUTOMATIC, OS_APPL_CONST) action ;
    action = _action;
  #else
    #define action _action
  #endif
  /*
   * A tpl_action * is cast to a tpl_callback_action *
   * This violate MISRA rule 45. However, since the
   * first member of tpl_callback_action is a tpl_action
   * This cast behaves correctly.
   */
  ((P2CONST(tpl_callback_action, AUTOMATIC, OS_APPL_CONST))action)->callback();
  #ifndef VOLATILE_ARGS_AND_LOCALS
    #undef action
  #endif
}

/**
 *  action function for action by task activation
 */
FUNC(void, OS_CODE) tpl_action_activate_task(
  P2CONST(tpl_action, AUTOMATIC, OS_APPL_CONST) action
)
{
  #ifdef VOLATILE_ARGS_AND_LOCALS
    static volatile P2CONST(tpl_action, AUTOMATIC, OS_APPL_CONST) _action ;
    _action = action;
  #else
    #define _action action
  #endif

  /*
   * A tpl_action * is cast to a tpl_task_activation_action *
   * This violate MISRA rule 45. However, since the
   * first member of tpl_task_activation_action is a tpl_action
   * This cast behaves correctly.
   */
	#if (LEVEL_KERNEL_MONITORING >= 4) /* whith kernel monitoring */
	reg_OS_instru_kernel_functions_5 = HW_FUNC_ACTION_ACTIVATE_TASK_ENTER;
	#endif
  /*  init the error to no error  */
  VAR(StatusType, AUTOMATIC) result_action = E_OK;

  /*  store information for error hook routine    */
  STORE_SERVICE(OSServiceId_ActivateTask)
  STORE_TASK_ID(((P2CONST(tpl_task_activation_action, AUTOMATIC, OS_APPL_CONST))_action)->task_id)

  /* call alarm action and save return value to launch error hook if alarm action goes wrong */
  result_action = tpl_activate_task(
    ((P2CONST(tpl_task_activation_action,
      AUTOMATIC,
      OS_APPL_CONST))_action)->task_id);

  PROCESS_ERROR(result_action)
	#if (LEVEL_KERNEL_MONITORING >= 4) /* whith kernel monitoring */
	reg_OS_instru_kernel_functions_5 = HW_FUNC_ACTION_ACTIVATE_TASK_EXIT;
	#endif

  #ifndef VOLATILE_ARGS_AND_LOCALS
    #undef _action
  #endif
}

/**
 *  action function for action by setting event
 */
#if EVENT_COUNT > 0

FUNC(void, OS_CODE) tpl_action_setevent(
  P2CONST(tpl_action, AUTOMATIC, OS_APPL_CONST) _action)
{
  /*
   * A tpl_action * is cast to a tpl_setevent_action *
   * This violate MISRA rule 45. However, since the
   * first member of tpl_setevent_action is a tpl_action
   * This cast behaves correctly.
   */

	#if (LEVEL_KERNEL_MONITORING >= 4) /* whith kernel monitoring */
	reg_OS_instru_kernel_functions_6 = HW_FUNC_ACTION_SETEVENT_ENTER;
	#endif
  #ifdef VOLATILE_ARGS_AND_LOCALS
    static volatile P2CONST(tpl_action, AUTOMATIC, OS_APPL_CONST) action ;
    action = _action;
    /*  init the error to no error  */
    static volatile VAR(StatusType, AUTOMATIC) result_action ;
    result_action = E_OK;
  #else
    #define action _action
    /*  init the error to no error  */
    VAR(StatusType, AUTOMATIC) result_action = E_OK;
  #endif
   

  /*  store information for error hook routine    */
  STORE_SERVICE(OSServiceId_SetEvent)
  STORE_TASK_ID(((P2CONST(tpl_setevent_action, AUTOMATIC, OS_APPL_CONST))action)->task_id)
  STORE_EVENT_MASK(((P2CONST(tpl_setevent_action, AUTOMATIC, OS_APPL_CONST))action)->mask)
  /* call alarm action and save return value to launch error hook if alarm action goes wrong */
  result_action = tpl_set_event(
      ((P2CONST(tpl_setevent_action, AUTOMATIC, OS_APPL_CONST))action)->task_id,
      ((P2CONST(tpl_setevent_action, AUTOMATIC, OS_APPL_CONST))action)->mask
  );

  PROCESS_ERROR(result_action);
	#if (LEVEL_KERNEL_MONITORING >= 4) /* whith kernel monitoring */
	reg_OS_instru_kernel_functions_6 = HW_FUNC_ACTION_SETEVENT_EXIT;
	#endif  

  #ifndef VOLATILE_ARGS_AND_LOCALS
    #undef action
  #endif
}

#endif

#define OS_STOP_SEC_CODE
#include "tpl_memmap.h"

/* End of file tpl_os_action.c */
