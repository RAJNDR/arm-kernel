#ifndef __SPINLOCK_H__
#define __SPINLOCK_H__

#include <sys/types.h>

typedef struct {
	// Bit 0 is the lock value: 0 for unlocked, 1 for locked
	// Bit 1 stores the status of the interrupt: 1 for enabled, 0 for disabled
	// Bit 2 stores the R/W value for a readers/writers spinlock
	uint32_t lock;
} spinlock_t;

// Initializes a spinlock, MUST always be called on a newly declared spinlock
void spin_init(spinlock_t*);

// Attempt to lock a spinlock
void spin_lock(spinlock_t*);

// Try to lock the spinlock, this will not "spin" if the locking fails
// Returns true if locking succeeded, otherwise false
bool spin_trylock(spinlock_t*);

// Unlock a previously locked spinlock
void spin_unlock(spinlock_t*);

// Same as spin_lock except this also disables interrupts
// This should be used if the object to be locked will be accessed in an 
// interrupt context
void spin_irqlock(spinlock_t*);

// Unlock a spinlock and, if previously enabled, reenables interrupts
void spin_irqunlock(spinlock_t*);

// Read lock, this will allow multiple sources to lock the spinlock
// assuming those sources will only read the locked resource
void spin_readlock(spinlock_t*);

// Indicates when a reader is done using the resource protected by the spinlock
void spin_readunlock(spinlock_t*);

// Write lock, will only allow a single source to access resource and block
// all other sources regardless of whether they will be reading or writing 
// resource
void spin_writelock(spinlock_t*);

// Indicates when a writer is done using the resource protected by the spinlock
void spin_writeunlock(spinlock_t*);

#endif // __SPINLOCK_H__
