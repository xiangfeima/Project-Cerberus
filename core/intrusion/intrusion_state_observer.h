#ifndef INTRUSION_STATE_OBSERVER_H_
#define INTRUSION_STATE_OBSERVER_H_

#include "status/rot_status.h"


/**
 * Observer for asynchronous changes to the intrusion state.
 */
struct intrusion_state_observer {
	/**
	 * Notification when intrusion has been detected.
	 *
	 * Arguments passed with the notification will never be null.
	 *
	 * @param observer The observer being notified.
	 */
	void (*on_intrusion) (struct intrusion_state_observer *observer);

	/**
	 * Notification when it is known that no intrusion has occurred.
	 *
	 * Arguments passed with the notification will never be null.
	 *
	 * @param observer The observer being notified.
	 */
	void (*on_no_intrusion) (struct intrusion_state_observer *observer);

	/**
	 * Notification of an error determining the intrusion state.
	 *
	 * Arguments passed with the notification will never be null.
	 *
	 * @param observer The observer being notified.
	 */
	void (*on_error) (struct intrusion_state_observer *observer);
};


#define	INTRUSION_STATE_OBSERVER_ERROR(code)		ROT_ERROR (ROT_MODULE_INTRUSION_STATE_OBSERVER, code)

/**
 * Error codes that can be generated by an intrusion state observer.
 */
enum {
	INTRUSION_STATE_OBSERVER_INVALID_ARGUMENT = INTRUSION_STATE_OBSERVER_ERROR (0x00),	/**< Input parameter is null or not valid. */
	INTRUSION_STATE_OBSERVER_NO_MEMORY = INTRUSION_STATE_OBSERVER_ERROR (0x01),			/**< Memory allocation failed. */
};


#endif /* INTRUSION_STATE_OBSERVER_H_ */